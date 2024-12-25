//============================================================
//
//	プレゼント処理 [present.cpp]
//	Author：小原立暉
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "present.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "fade.h"
#include "stage.h"
#include "sceneGame.h"
#include "gameManager.h"

#include "presentLand.h"
#include "presentBullet.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int	PRIORITY = 3;		// プレゼントの優先順位
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
CPresent::CPresent() : CObjectModel(CObject::LABEL_PRESENT, CObject::DIM_3D, PRIORITY),
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
	if (FAILED(CObjectModel::Init()))
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
	CObjectModel::Uninit();
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
	CObjectModel::Draw(pShader);
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

	case CPresent::TYPE_BULLET:

		// 弾方プレゼントを生成
		pPresent = new CPresentBullet;

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
