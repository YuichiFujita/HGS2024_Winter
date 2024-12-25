//============================================================
//
//	敵処理 [enemy.cpp]
//	Author：小原立暉
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "fade.h"
#include "stage.h"
#include "sceneGame.h"
#include "gameManager.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* SETUP_TXT = "data\\CHARACTER\\player.txt";	// セットアップテキスト相対パス
	const int	PRIORITY = 3;		// プレイヤーの優先順位
	const float	GRAVITY = 3600.0f;	// 重力
	const float	RADIUS = 20.0f;	// 半径
	const float HEIGHT = 80.0f;	// 身長
	const float	REV_ROTA = 9.0f;		// 向き変更の補正係数
	const float	JUMP_REV = 0.16f;	// 通常状態時の空中の移動量の減衰係数
	const float	LAND_REV = 0.16f;	// 通常状態時の地上の移動量の減衰係数

	namespace motion
	{
		const int BLEND_FRAME_OTHER = 5;	// モーションの基本的なブレンドフレーム
	}
}

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CListManager<CEnemy>* CEnemy::m_pList = nullptr;	// オブジェクトリスト

//************************************************************
//	子クラス [CEnemy] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CEnemy::CEnemy() : CObjectChara(CObject::LABEL_ENEMY, CObject::DIM_3D, PRIORITY),
m_oldPos(VEC3_ZERO),	// 過去位置
m_move(VEC3_ZERO),	// 移動量
m_destRot(VEC3_ZERO),	// 目標向き
m_bJump(false)			// ジャンプ状況
{

}

//============================================================
//	デストラクタ
//============================================================
CEnemy::~CEnemy()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CEnemy::Init()
{
	// メンバ変数を初期化
	m_oldPos = VEC3_ZERO;	// 過去位置
	m_move = VEC3_ZERO;	// 移動量
	m_destRot = VEC3_ZERO;	// 目標向き
	m_bJump = true;			// ジャンプ状況

	// オブジェクトキャラクターの初期化
	if (FAILED(CObjectChara::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// キャラクター情報の割当
	BindCharaData(SETUP_TXT);

	// 初期モーションの割当
	SetMotion(MOTION_IDOL);

	if (m_pList == nullptr)
	{ // リストマネージャーが存在しない場合

		// リストマネージャーの生成
		m_pList = CListManager<CEnemy>::Create();
		if (m_pList == nullptr)
		{ // 生成に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}
	}

	// リストに自身のオブジェクトを追加・イテレーターを取得
	m_iterator = m_pList->AddList(this);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CEnemy::Uninit()
{
	// リストから自身のオブジェクトを削除
	m_pList->DelList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // オブジェクトが一つもない場合

		// リストマネージャーの破棄
		m_pList->Release(m_pList);
	}

	// オブジェクトキャラクターの終了
	CObjectChara::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CEnemy::Update(const float fDeltaTime)
{
	// 過去位置の更新
	UpdateOldPosition();

	// 状態の更新
	EMotion curMotion = UpdateState(fDeltaTime);

	// モーション・オブジェクトキャラクターの更新
	UpdateMotion(curMotion, fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CEnemy::Draw(CShader* pShader)
{
	// オブジェクトキャラクターの描画
	CObjectChara::Draw(pShader);
}

//============================================================
//	更新状況の設定処理
//============================================================
void CEnemy::SetEnableUpdate(const bool bUpdate)
{
	// 引数の更新状況を設定
	CObject::SetEnableUpdate(bUpdate);	// 自身
}

//============================================================
//	描画状況の設定処理
//============================================================
void CEnemy::SetEnableDraw(const bool bDraw)
{
	// 引数の描画状況を設定
	CObject::SetEnableDraw(bDraw);	// 自身
}

//============================================================
//	状態の更新処理
//============================================================
CEnemy::EMotion CEnemy::UpdateState(const float fDeltaTime)
{
	EMotion curMotion = MOTION_IDOL;	// 現在のモーション
	//switch (m_state)
	//{ // 状態ごとの処理
	//case STATE_NONE:

	//	// 何もしない状態時の更新
	//	curMotion = UpdateNone(fDeltaTime);
	//	break;

	//case STATE_NORMAL:

	//	// 通常状態の更新
	//	curMotion = UpdateNormal(fDeltaTime);
	//	break;

	//default:
	//	assert(false);
	//	break;
	//}

	// 現在のモーションを返す
	return curMotion;
}

//============================================================
//	生成処理
//============================================================
CEnemy* CEnemy::Create
(
	const VECTOR3& rPos,	// 位置
	const VECTOR3& rRot		// 向き
)
{
	// プレイヤーの生成
	CEnemy* pEnemy = new CEnemy;
	if (pEnemy == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// プレイヤーの初期化
		if (FAILED(pEnemy->Init()))
		{ // 初期化に失敗した場合

			// プレイヤーの破棄
			SAFE_DELETE(pEnemy);
			return nullptr;
		}

		// 位置を設定
		pEnemy->SetVec3Position(rPos);
		pEnemy->m_oldPos = rPos;	// 過去位置も同一の位置にする

		// 向きを設定
		pEnemy->SetVec3Rotation(rRot);
		pEnemy->m_destRot = rRot;	// 目標向きも同一の向きにする

		// 確保したアドレスを返す
		return pEnemy;
	}
}

//============================================================
//	リスト取得処理
//============================================================
CListManager<CEnemy>* CEnemy::GetList()
{
	// オブジェクトリストを返す
	return m_pList;
}

//============================================================
//	半径取得処理
//============================================================
float CEnemy::GetRadius() const
{
	// 半径を返す
	return RADIUS;
}

//============================================================
//	縦幅取得処理
//============================================================
float CEnemy::GetHeight() const
{
	// 縦幅を返す
	return HEIGHT;
}

//============================================================
//	何もしない状態時の更新処理
//============================================================
CEnemy::EMotion CEnemy::UpdateNone(const float fDeltaTime)
{
	VECTOR3 posEnemy = GetVec3Position();	// プレイヤー位置
	VECTOR3 rotEnemy = GetVec3Rotation();	// プレイヤー向き

	// 重力の更新
	UpdateGravity(fDeltaTime);

	// 位置更新
	UpdatePosition(&posEnemy, fDeltaTime);

	// 着地判定
	UpdateLanding(&posEnemy, fDeltaTime);

	// 向き更新
	UpdateRotation(&rotEnemy, fDeltaTime);

	// 位置を反映
	SetVec3Position(posEnemy);

	// 向きを反映
	SetVec3Rotation(rotEnemy);

	// 現在のモーションを返す
	return MOTION_IDOL;
}

//============================================================
//	通常状態時の更新処理
//============================================================
CEnemy::EMotion CEnemy::UpdateNormal(const float fDeltaTime)
{
	// 操作不可能な場合抜ける
	CGameManager* pGameManager = CSceneGame::GetGameManager();	// ゲームマネージャー
	if (pGameManager != nullptr)
	{ // ゲームマネージャーがある場合

		if (!pGameManager->IsControlOK()) { return MOTION_IDOL; }
	}

	EMotion curMotion = MOTION_IDOL;		// 現在のモーション
	VECTOR3 posEnemy = GetVec3Position();	// プレイヤー位置
	VECTOR3 rotEnemy = GetVec3Rotation();	// プレイヤー向き

	// 移動操作
	curMotion = UpdateMove();

	// 重力の更新
	UpdateGravity(fDeltaTime);

	// 位置更新
	UpdatePosition(&posEnemy, fDeltaTime);

	// 着地判定
	UpdateLanding(&posEnemy, fDeltaTime);

	// 向き更新
	UpdateRotation(&rotEnemy, fDeltaTime);

	// 位置を反映
	SetVec3Position(posEnemy);

	// 向きを反映
	SetVec3Rotation(rotEnemy);

	// 現在のモーションを返す
	return curMotion;
}

//============================================================
//	過去位置の更新処理
//============================================================
void CEnemy::UpdateOldPosition()
{
	// 過去位置を更新
	m_oldPos = GetVec3Position();
}

//============================================================
//	移動量/目標向きの更新処理
//============================================================
CEnemy::EMotion CEnemy::UpdateMove()
{
	EMotion curMotion = MOTION_IDOL;	// 現在のモーション

	CInputKeyboard* pKey = GET_INPUTKEY;	// キーボード情報
	if (pKey->IsPress(DIK_W))
	{
		m_move.z += 30.0f;
		m_destRot.y = D3DX_PI;
		curMotion = MOTION_WALK;
	}
	if (pKey->IsPress(DIK_A))
	{
		m_move.x -= 30.0f;
		m_destRot.y = D3DX_PI * 0.5f;
		curMotion = MOTION_WALK;
	}
	if (pKey->IsPress(DIK_S))
	{
		m_move.z -= 30.0f;
		m_destRot.y = 0.0f;
		curMotion = MOTION_WALK;
	}
	if (pKey->IsPress(DIK_D))
	{
		m_move.x += 30.0f;
		m_destRot.y = -D3DX_PI * 0.5f;
		curMotion = MOTION_WALK;
	}

	// モーションを返す
	return curMotion;
}

//============================================================
//	重力の更新処理
//============================================================
void CEnemy::UpdateGravity(const float fDeltaTime)
{
	// 重力を加算
	m_move.y -= GRAVITY * fDeltaTime;
}

//============================================================
//	着地状況の更新処理
//============================================================
bool CEnemy::UpdateLanding(VECTOR3* pPos, const float fDeltaTime)
{
	CStage* pStage = GET_MANAGER->GetStage();	// ステージ情報
	bool bLand = false;	// 着地フラグ

	// 地面・制限位置着地判定
	if (pStage->LandFieldPosition(*pPos, m_oldPos, m_move)
		|| pStage->LandLimitPosition(*pPos, m_move, 0.0f))
	{ // プレイヤーが着地していた場合

		// 着地している状態にする
		bLand = true;

		// ジャンプしていない状態にする
		m_bJump = false;
	}

	// 着地フラグを返す
	return bLand;
}

//============================================================
//	位置の更新処理
//============================================================
void CEnemy::UpdatePosition(VECTOR3* pPos, const float fDeltaTime)
{
	// 移動量を加算
	*pPos += m_move * fDeltaTime;

	// 移動量を減衰
	if (m_bJump)
	{ // 空中の場合

		m_move.x += (0.0f - m_move.x) * JUMP_REV;
		m_move.z += (0.0f - m_move.z) * JUMP_REV;
	}
	else
	{ // 地上の場合

		m_move.x += (0.0f - m_move.x) * LAND_REV;
		m_move.z += (0.0f - m_move.z) * LAND_REV;
	}
}

//============================================================
//	向きの更新処理
//============================================================
void CEnemy::UpdateRotation(VECTOR3* pRot, const float fDeltaTime)
{
	// 変数を宣言
	float fDiffRot = 0.0f;	// 差分向き

	// 目標向きの正規化
	useful::NormalizeRot(m_destRot.y);

	// 目標向きまでの差分を計算
	fDiffRot = m_destRot.y - pRot->y;

	// 差分向きの正規化
	useful::NormalizeRot(fDiffRot);

	// 向きの更新
	pRot->y += fDiffRot * fDeltaTime * REV_ROTA;

	// 向きの正規化
	useful::NormalizeRot(pRot->y);
}

//============================================================
//	モーション/キャラクターの更新処理
//============================================================
void CEnemy::UpdateMotion(int nMotion, const float fDeltaTime)
{
	// 死んでたら抜ける
	if (IsDeath()) { return; }

	int nAnimMotion = GetMotionType();	// 現在再生中のモーション
	if (nMotion != NONE_IDX)
	{ // モーションが設定されている場合

		if (IsMotionLoop())
		{ // ループするモーション中の場合

			if (nAnimMotion != nMotion)
			{ // 現在のモーションが再生中のモーションと一致しない場合

				// 現在のモーションの設定
				SetMotion(nMotion, motion::BLEND_FRAME_OTHER);
			}
		}
		else
		{ // ループしないモーション中の場合

#if 0
			switch (GetMotionType())
			{ // モーションごとの処理
			case MOTION_:

				if (nMotion != MOTION_IDOL)
				{ // 待機モーション以外の場合

					// 現在のモーションの設定
					SetMotion(nMotion, motion::BLEND_FRAME_OTHER);
				}
				break;
			}
#endif
		}
	}

	// オブジェクトキャラクターの更新
	CObjectChara::Update(fDeltaTime);

	switch (GetMotionType())
	{ // モーションの種類ごとの処理
	case MOTION_IDOL:
		break;

	case MOTION_WALK:
		break;
	}
}
