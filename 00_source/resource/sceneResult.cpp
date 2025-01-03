//============================================================
//
//	リザルト画面処理 [sceneResult.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "sceneResult.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"
#include "resultManager.h"

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CResultManager* CSceneResult::m_pResultManager = nullptr;	// リザルトマネージャー

//************************************************************
//	子クラス [CSceneResult] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSceneResult::CSceneResult(const EMode mode) : CScene(mode)
{

}

//============================================================
//	デストラクタ
//============================================================
CSceneResult::~CSceneResult()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSceneResult::Init()
{
	// シーンの初期化
	if (FAILED(CScene::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// リザルトマネージャーの生成
	m_pResultManager = CResultManager::Create();
	if (m_pResultManager == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 回転カメラにする
	CCamera* pCamera = GET_MANAGER->GetCamera();	// カメラ情報
	pCamera->SetState(CCamera::STATE_ROTATE);		// 回転状態を設定

	// BGMの再生
	PLAY_SOUND(CSound::LABEL_BGM_RESULT_000);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CSceneResult::Uninit()
{
	// リザルトマネージャーの破棄
	SAFE_REF_RELEASE(m_pResultManager);

	// シーンの終了
	CScene::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CSceneResult::Update(const float fDeltaTime)
{
	// リザルトマネージャーの更新
	assert(m_pResultManager != nullptr);
	m_pResultManager->Update(fDeltaTime);
}

//============================================================
//	リザルトマネージャー取得処理
//============================================================
CResultManager* CSceneResult::GetResultManager()
{
	// インスタンス未使用
	assert(m_pResultManager != nullptr);

	// リザルトマネージャーのポインタを返す
	return m_pResultManager;
}
