//============================================================
//
//	プレゼント処理 [present.cpp]
//	Author：小原立暉
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "presentCopy.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "fade.h"
#include "stage.h"
#include "sceneGame.h"
#include "gameManager.h"

#include "presentLandCopy.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int	PRIORITY = 3;		// プレゼントの優先順位
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
CListManager<CPresent>* CPresent::m_pList = nullptr;	// オブジェクトリスト

//************************************************************
//	子クラス [CPresent] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CPresent::CPresent() : CObjectChara(CObject::LABEL_PRESENT, CObject::DIM_3D, PRIORITY),
m_type(TYPE_LAND)		// 種類
{

}

//============================================================
//	デストラクタ
//============================================================
CPresent::~CPresent()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CPresent::Init()
{
	m_type = TYPE_LAND;		// 種類

	// オブジェクトキャラクターの初期化
	if (FAILED(CObjectChara::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	if (m_pList == nullptr)
	{ // リストマネージャーが存在しない場合

		// リストマネージャーの生成
		m_pList = CListManager<CPresent>::Create();
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
void CPresent::Uninit()
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
void CPresent::Update(const float fDeltaTime)
{

}

//============================================================
//	描画処理
//============================================================
void CPresent::Draw(CShader* pShader)
{
	// オブジェクトキャラクターの描画
	CObjectChara::Draw(pShader);
}

//============================================================
//	更新状況の設定処理
//============================================================
void CPresent::SetEnableUpdate(const bool bUpdate)
{
	// 引数の更新状況を設定
	CObject::SetEnableUpdate(bUpdate);	// 自身
}

//============================================================
//	描画状況の設定処理
//============================================================
void CPresent::SetEnableDraw(const bool bDraw)
{
	// 引数の描画状況を設定
	CObject::SetEnableDraw(bDraw);	// 自身
}

//============================================================
//	生成処理
//============================================================
CPresent* CPresent::Create
(
	const VECTOR3& rPos,	// 位置
	const VECTOR3& rRot,	// 向き
	const EType type		// 種類
)
{
	// プレゼントの生成
	CPresent* pPresent = nullptr;

	switch (type)
	{
	case CPresent::TYPE_LAND:

		// 設置型プレゼントを生成
		pPresent = new CPresentLand;

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	if (pPresent == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// プレゼントの初期化
		if (FAILED(pPresent->Init()))
		{ // 初期化に失敗した場合

			// プレゼントの破棄
			SAFE_DELETE(pPresent);
			return nullptr;
		}

		// 位置を設定
		pPresent->SetVec3Position(rPos);

		// 向きを設定
		pPresent->SetVec3Rotation(rRot);

		// 確保したアドレスを返す
		return pPresent;
	}
}

//============================================================
//	リスト取得処理
//============================================================
CListManager<CPresent>* CPresent::GetList()
{
	// オブジェクトリストを返す
	return m_pList;
}
