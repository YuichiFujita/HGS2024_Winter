//============================================================
//
//	エディットマネージャー処理 [editManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "editManager.h"
#include "main.h"
#include "manager.h"
#include "actor.h"
#include "collision.h"
#include "sceneGame.h"
#include "gameManager.h"

//************************************************************
//	マクロ定義
//************************************************************
#define KEY_DOUBLE		(DIK_LCONTROL)	// 二重化キー
#define NAME_DOUBLE		("LCTRL")		// 二重化表示
#define KEY_REVERSE		(DIK_LCONTROL)	// 逆転キー
#define NAME_REVERSE	("LCTRL")		// 逆転表示
#define KEY_TRIGGER		(DIK_LSHIFT)	// トリガー化キー
#define NAME_TRIGGER	("LSHIFT")		// トリガー化表示

#define KEY_CREATE		(DIK_0)		// 生成キー
#define NAME_CREATE		("0")		// 生成表示
#define KEY_RELEASE		(DIK_9)		// 破棄キー
#define NAME_RELEASE	("9")		// 破棄表示
#define KEY_TYPE		(DIK_1)		// 種類変更キー
#define NAME_TYPE		("1")		// 種類変更表示
#define KEY_SAVE		(DIK_F9)	// 保存キー
#define NAME_SAVE		("F9")		// 保存表示

#define KEY_FAR		(DIK_W)	// 奥移動キー
#define NAME_FAR	("W")	// 奥移動表示
#define KEY_NEAR	(DIK_S)	// 手前移動キー
#define NAME_NEAR	("S")	// 手前移動表示
#define KEY_RIGHT	(DIK_D)	// 右移動キー
#define NAME_RIGHT	("D")	// 右移動表示
#define KEY_LEFT	(DIK_A)	// 左移動キー
#define NAME_LEFT	("A")	// 左移動表示
#define KEY_UP		(DIK_E)	// 上移動キー
#define NAME_UP		("E")	// 上移動表示
#define KEY_DOWN	(DIK_Q)	// 下移動キー
#define NAME_DOWN	("Q")	// 下移動表示

#define KEY_ROTA_RIGHT	(DIK_Z)	// 右回転キー
#define NAME_ROTA_RIGHT	("Z")	// 右回転表示
#define KEY_ROTA_LEFT	(DIK_C)	// 左回転キー
#define NAME_ROTA_LEFT	("C")	// 左回転表示

#define KEY_SCALE_UP	(DIK_T)	// 拡大キー
#define NAME_SCALE_UP	("T")	// 拡大表示
#define KEY_SCALE_DOWN	(DIK_G)	// 縮小キー
#define NAME_SCALE_DOWN	("G")	// 縮小表示

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char*	SAVE_TXT = "data\\TXT\\save_actor.txt";	// 保存テキスト
	const float	INIT_ALPHA = 0.5f;	// 配置前のα値
	const float	MOVE = 1.5f;		// 移動量
	const float	ROTMOVE = 0.02f;	// 向き移動量
	const float	SCALEMOVE = 0.1f;	// 拡大量
}

//************************************************************
//	親クラス [CEditManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CEditManager::CEditManager() :
	m_pCreateActor	(nullptr)	// 生成アクター情報
{

}

//============================================================
//	デストラクタ
//============================================================
CEditManager::~CEditManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CEditManager::Init()
{
	// メンバ変数を初期化
	m_pCreateActor = nullptr;	// 生成アクター情報

	// 障害物の生成
	m_pCreateActor = CActor::Create(CActor::TYPE_WOOD, VEC3_ZERO, VEC3_ZERO, VEC3_ONE);
	if (m_pCreateActor == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 透明度を設定
	m_pCreateActor->SetAlpha(INIT_ALPHA);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CEditManager::Uninit()
{
	// 未設置アクターの終了
	SAFE_UNINIT(m_pCreateActor);
}

//============================================================
//	更新処理
//============================================================
void CEditManager::Update(const float fDeltaTime)
{
	// 操作可能フラグをOFFにする
	CSceneGame::GetGameManager()->SetEnableControlOK(false);

	// 位置の更新
	UpdatePosition(fDeltaTime);

	// 向きの更新
	UpdateRotation(fDeltaTime);

	// 拡大率の更新
	UpdateScale(fDeltaTime);

	// 種類の更新
	UpdateType();

	// アクターの生成
	CreateActor();

	// アクターの破棄
	ReleaseActor();

	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(KEY_SAVE))
	{
		// アクターの保存
		SaveActor();
	}
}

//============================================================
//	生成処理
//============================================================
CEditManager* CEditManager::Create()
{
	// エディットマネージャーの生成
	CEditManager* pEditManager = new CEditManager;
	if (pEditManager == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// エディットマネージャーの初期化
		if (FAILED(pEditManager->Init()))
		{ // 初期化に失敗した場合

			// エディットマネージャーの破棄
			SAFE_DELETE(pEditManager);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pEditManager;
	}
}

//============================================================
//	破棄処理
//============================================================
void CEditManager::Release(CEditManager*& prEditManager)
{
	// エディットマネージャーの終了
	assert(prEditManager != nullptr);
	prEditManager->Uninit();

	// メモリ開放
	SAFE_DELETE(prEditManager);
}

//============================================================
//	位置の更新処理
//============================================================
void CEditManager::UpdatePosition(const float fDeltaTime)
{
	float fDeltaRate = fDeltaTime / (1.0f / (float)main::FPS);	// 経過時間の割合

	// 位置を変更
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
	VECTOR3 posActor = m_pCreateActor->GetVec3Position();	// 位置
	if (!pKey->IsPress(KEY_TRIGGER))
	{
		if (pKey->IsPress(KEY_FAR))
		{
			posActor.z += MOVE * fDeltaRate;
		}
		if (pKey->IsPress(KEY_NEAR))
		{
			posActor.z -= MOVE * fDeltaRate;
		}
		if (pKey->IsPress(KEY_RIGHT))
		{
			posActor.x += MOVE * fDeltaRate;
		}
		if (pKey->IsPress(KEY_LEFT))
		{
			posActor.x -= MOVE * fDeltaRate;
		}
		if (pKey->IsPress(KEY_UP))
		{
			posActor.y += MOVE * fDeltaRate;
		}
		if (pKey->IsPress(KEY_DOWN))
		{
			posActor.y -= MOVE * fDeltaRate;
		}
	}
	else
	{
		if (pKey->IsTrigger(KEY_FAR))
		{
			posActor.z += MOVE * fDeltaRate;
		}
		if (pKey->IsTrigger(KEY_NEAR))
		{
			posActor.z -= MOVE * fDeltaRate;
		}
		if (pKey->IsTrigger(KEY_RIGHT))
		{
			posActor.x += MOVE * fDeltaRate;
		}
		if (pKey->IsTrigger(KEY_LEFT))
		{
			posActor.x -= MOVE * fDeltaRate;
		}
		if (pKey->IsTrigger(KEY_UP))
		{
			posActor.y += MOVE * fDeltaRate;
		}
		if (pKey->IsTrigger(KEY_DOWN))
		{
			posActor.y -= MOVE * fDeltaRate;
		}
	}

	// 位置を反映
	m_pCreateActor->SetVec3Position(posActor);
}

//============================================================
//	向きの更新処理
//============================================================
void CEditManager::UpdateRotation(const float fDeltaTime)
{
	float fDeltaRate = fDeltaTime / (1.0f / (float)main::FPS);	// 経過時間の割合

	// 向きを変更
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
	VECTOR3 rotActor = m_pCreateActor->GetVec3Rotation();	// 向き
	if (pKey->IsPress(KEY_ROTA_RIGHT))
	{
		rotActor.y += ROTMOVE * fDeltaRate;
	}
	if (pKey->IsPress(KEY_ROTA_LEFT))
	{
		rotActor.y -= ROTMOVE * fDeltaRate;
	}

	// 向きを反映
	m_pCreateActor->SetVec3Rotation(rotActor);
}

//============================================================
//	拡大率の更新処理
//============================================================
void CEditManager::UpdateScale(const float fDeltaTime)
{
	float fDeltaRate = fDeltaTime / (1.0f / (float)main::FPS);	// 経過時間の割合

	// 拡大率を変更
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
	VECTOR3 scaleActor = m_pCreateActor->GetVec3Scale();	// 拡大率
	if (pKey->IsPress(KEY_SCALE_UP))
	{
		scaleActor += SCALEMOVE * fDeltaRate;
	}
	if (pKey->IsPress(KEY_SCALE_DOWN))
	{
		scaleActor -= SCALEMOVE * fDeltaRate;
	}

	// 拡大率を反映
	m_pCreateActor->SetVec3Scale(scaleActor);
}

//============================================================
//	種類の更新処理
//============================================================
void CEditManager::UpdateType()
{
	// 種類を変更
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsPress(KEY_REVERSE))
	{
		if (pKey->IsTrigger(KEY_TYPE))
		{
			// 種類を変更
			CActor::EType type = (CActor::EType)(( + (CActor::TYPE_MAX - 1)) % CActor::TYPE_MAX);

			// 種類を反映
			m_pCreateActor->SetType(type);
			m_pCreateActor->SetAlpha(INIT_ALPHA);	// 透明度を再設定
		}
	}
	else
	{
		if (pKey->IsTrigger(KEY_TYPE))
		{
			// 種類を変更
			CActor::EType type = (CActor::EType)((m_pCreateActor->GetType() + 1) % CActor::TYPE_MAX);

			// 種類を反映
			m_pCreateActor->SetType(type);
			m_pCreateActor->SetAlpha(INIT_ALPHA);	// 透明度を再設定
		}
	}
}

//============================================================
//	アクターの生成処理
//============================================================
void CEditManager::CreateActor()
{
	CActor::EType typeOld = m_pCreateActor->GetType();		// 元の種類
	D3DXVECTOR3 posOld = m_pCreateActor->GetVec3Position();	// 元の位置
	D3DXVECTOR3 rotOld = m_pCreateActor->GetVec3Rotation();	// 元の向き
	D3DXVECTOR3 scaleOld = m_pCreateActor->GetVec3Scale();	// 元の拡大率

	// アクターの配置
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(KEY_CREATE))
	{
		//----------------------------------------------------
		//	アクターの情報を配置用に変更
		//----------------------------------------------------
		// 自動更新・自動描画をONにする
		m_pCreateActor->SetEnableUpdate(true);
		m_pCreateActor->SetEnableDraw(true);

		// マテリアルを再設定
		m_pCreateActor->ResetMaterial();

		//----------------------------------------------------
		//	新しいアクターの生成
		//----------------------------------------------------
		// アクターの生成
		m_pCreateActor = CActor::Create(typeOld, posOld, rotOld, scaleOld);
		assert(m_pCreateActor != nullptr);

		// 透明度を設定
		m_pCreateActor->SetAlpha(INIT_ALPHA);
	}
}

//============================================================
//	アクターの破棄処理
//============================================================
void CEditManager::ReleaseActor()
{
	// アクターの削除
	CInputKeyboard *pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsTrigger(KEY_RELEASE))
	{
		// アクターがない場合抜ける
		CListManager<CActor>* pList = CActor::GetList();
		if (pList == nullptr) { return; }

		// リストマネージャーからリストを取得
		std::list<CActor*> listTimer = pList->GetList();

		for (auto& rList : listTimer)
		{ // リスト内の要素数分繰り返す

			// 自身の場合抜ける
			if (rList == m_pCreateActor) { continue; }

			bool bHit = collision::Circle2D
			( // 引数
				m_pCreateActor->GetVec3Position(),
				rList->GetVec3Position(),
				30.0f,
				30.0f
			);
			if (bHit)
			{ // 削除範囲内の場合

				// アクターの終了
				SAFE_UNINIT(rList);
			}
		}
	}
}

//============================================================
//	アクターの保存処理
//============================================================
void CEditManager::SaveActor(void)
{
	// ファイルを書き出し形式で開く
	FILE* pFile = fopen(SAVE_TXT, "w");
	if (pFile != nullptr)
	{ // ファイルが開けた場合

		// 見出しを書き出し
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	アクターセーブテキスト [save_actor.txt]\n");
		fprintf(pFile, "#	Author : 藤田勇一\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "---------->--<---------- ここから下を コピーし貼り付け ---------->--<----------\n");
		fprintf(pFile, "\n");

		// 情報開始地点を書き出し
		fprintf(pFile, "STAGE_ACTORSET\n\n");

		CListManager<CActor>* pList = CActor::GetList();
		if (pList != nullptr)
		{ // アクターがある場合

			// リストマネージャーからリストを取得
			std::list<CActor*> listTimer = pList->GetList();
			for (auto& rList : listTimer)
			{ // リスト内の要素数分繰り返す

				// 自身の場合抜ける
				if (rList == m_pCreateActor) { continue; }

				VECTOR3 posActor = rList->GetVec3Position();	// アクター位置
				VECTOR3 rotActor = rList->GetVec3Rotation();	// アクター向き
				VECTOR3 scaleActor = rList->GetVec3Scale();		// アクター拡大率

				// 情報を書き出し
				fprintf(pFile, "	ACTORSET\n");
				fprintf(pFile, "		TYPE = %d\n", rList->GetType());
				fprintf(pFile, "		POS = %.2f %.2f %.2f\n", posActor.x, posActor.y, posActor.z);
				fprintf(pFile, "		ROT = %.2f %.2f %.2f\n", rotActor.x, rotActor.y, rotActor.z);
				fprintf(pFile, "		SCALE = %.2f %.2f %.2f\n", scaleActor.x, scaleActor.y, scaleActor.z);
				fprintf(pFile, "	END_ACTORSET\n\n");
			}
		}

		// 情報終了地点を書き出し
		fprintf(pFile, "END_STAGE_ACTORSET\n\n");

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{ // ファイルが開けなかった場合

		// エラーメッセージボックス
		MessageBox(NULL, "アクターセーブファイルの書き出しに失敗！", "警告！", MB_ICONWARNING);
	}
}
