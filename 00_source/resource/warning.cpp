//============================================================
//
//	警告処理 [warning.cpp]
//	Author：小原立暉
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "warning.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* TEXTURE_FILE = "data\\TEXTURE\\";
	const VECTOR3 RADIUS = VECTOR3(40.0f, 40.0f, 0.0f);	// 半径

	const int PRIORITY = 4;	// エフェクト3Dの優先順位
}

//************************************************************
//	子クラス [CWarning] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CWarning::CWarning() : CObject3D(CObject::LABEL_EFFECT, CObject::DIM_3D, PRIORITY)
{

}

//============================================================
//	デストラクタ
//============================================================
CWarning::~CWarning()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CWarning::Init()
{
	// オブジェクト3Dの初期化
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// レンダーステートの情報を取得
	CRenderState* pRenderState = GetRenderState();

	// Zテストの設定
	pRenderState->SetZFunc(D3DCMP_ALWAYS);

	// Zバッファの使用状況の設定
	pRenderState->SetZUpdate(false);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CWarning::Uninit()
{
	// オブジェクト3Dの終了
	CObject3D::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CWarning::Update(const float fDeltaTime)
{
	// オブジェクト3Dの更新
	CObject3D::Update(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CWarning::Draw(CShader* pShader)
{
	// オブジェクト3Dの描画
	CObject3D::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CWarning* CWarning::Create
(
	const VECTOR3& rPos				// 位置
)
{
	// エフェクト3Dの生成
	CWarning* pEffect3D = new CWarning;
	if (pEffect3D == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// エフェクト3Dの初期化
		if (FAILED(pEffect3D->Init()))
		{ // 初期化に失敗した場合

			// エフェクト3Dの破棄
			SAFE_DELETE(pEffect3D);
			return nullptr;
		}

		// テクスチャを登録・割当
		pEffect3D->BindTexture(GET_MANAGER->GetTexture()->Regist(TEXTURE_FILE));

		// 位置を設定
		pEffect3D->SetVec3Position(rPos);

		// 大きさを設定
		pEffect3D->SetVec3Size(RADIUS);

		// 確保したアドレスを返す
		return pEffect3D;
	}
}
