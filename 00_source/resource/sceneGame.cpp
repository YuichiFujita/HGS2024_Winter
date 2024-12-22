//============================================================
//
//	ゲーム画面処理 [sceneGame.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "sceneGame.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"
#include "gameManager.h"
#include "pause.h"

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CGameManager* CSceneGame::m_pGameManager = nullptr;	// ゲームマネージャー
CPause* CSceneGame::m_pPause = nullptr;	// ポーズ情報
CStage* CSceneGame::m_pStage = nullptr;	// ステージ情報

//************************************************************
//	子クラス [CSceneGame] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CSceneGame::CSceneGame(const EMode mode) : CScene(mode)
{

}

//============================================================
//	デストラクタ
//============================================================
CSceneGame::~CSceneGame()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CSceneGame::Init()
{
	//--------------------------------------------------------
	//	初期生成
	//--------------------------------------------------------
	// シーンの初期化
	if (FAILED(CScene::Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// ゲームマネージャーの生成
	m_pGameManager = CGameManager::Create();
	if (m_pGameManager == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// ポーズの生成
	m_pPause = CPause::Create();
	if (m_pPause == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// TODO：ステージ追加時に修正
#if 0
	// ステージの生成
	m_pStage = CStage::Create();
	if (m_pStage == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}
#endif

	// TODO：カメラ設定
#if 0
	// 追従カメラにする
	CCamera* pCamera = GET_MANAGER->GetCamera();	// カメラ情報
	pCamera->SetState(CCamera::STATE_FOLLOW);		// 追従状態を設定
#endif

	// BGMの再生
	PLAY_SOUND(CSound::LABEL_BGM_GENERAL);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CSceneGame::Uninit()
{
	// ゲームマネージャーの破棄
	SAFE_REF_RELEASE(m_pGameManager);

	// ポーズの破棄
	SAFE_REF_RELEASE(m_pPause);

	// TODO：ステージ追加時に修正
#if 0
	// ステージの破棄
	SAFE_REF_RELEASE(m_pStage);
#endif

	// シーンの終了
	CScene::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CSceneGame::Update(const float fDeltaTime)
{
	// フェード中の場合抜ける
	if (GET_MANAGER->GetFade()->IsFade()) { return; }

	// ゲームマネージャーの更新
	assert(m_pGameManager != nullptr);
	m_pGameManager->Update(fDeltaTime);

	if (m_pGameManager->IsNormal())
	{ // ゲームが通常状態の場合

		// ポーズの更新
		assert(m_pPause != nullptr);
		m_pPause->Update(fDeltaTime);
	}

	if (!m_pPause->IsPause())
	{ // ポーズ中ではない場合

		// シーンの更新
		CScene::Update(fDeltaTime);
	}

#ifdef _DEBUG
	else
	{ // ポーズ中の場合

		if (GET_MANAGER->GetCamera()->GetState() == CCamera::STATE_CONTROL)
		{ // カメラが操作状態の場合

			// カメラの更新
			GET_MANAGER->GetCamera()->Update(fDeltaTime);
		}
	}
#endif	// _DEBUG
}

//============================================================
//	ゲームマネージャー取得処理
//============================================================
CGameManager* CSceneGame::GetGameManager()
{
	// インスタンス未使用
	assert(m_pGameManager != nullptr);

	// ゲームマネージャーのポインタを返す
	return m_pGameManager;
}

//============================================================
//	ポーズ取得処理
//============================================================
CPause* CSceneGame::GetPause()
{
	// インスタンス未使用
	assert(m_pPause != nullptr);

	// ポーズのポインタを返す
	return m_pPause;
}

//============================================================
//	ステージ取得処理
//============================================================
CStage* CSceneGame::GetStage()
{
	// インスタンス未使用
	assert(m_pStage != nullptr);

	// ステージのポインタを返す
	return m_pStage;
}

//============================================================
//	プレイヤー取得処理
//============================================================
CPlayer* CSceneGame::GetPlayer()
{
	// TODO：プレイヤー追加時に修正
#if 0
	CListManager<CPlayer>* pListManager = CPlayer::GetList();	// プレイヤーリストマネージャー
	if (pListManager == nullptr)		{ return nullptr; }		// リスト未使用の場合抜ける
	if (pListManager->GetNumAll() != 1)	{ return nullptr; }		// プレイヤーが1人ではない場合抜ける
	CPlayer* pPlayer = pListManager->GetList().front();			// プレイヤー情報

	// インスタンス未使用
	assert(pPlayer != nullptr);

	// プレイヤーのポインタを返す
	return pPlayer;
#else
	return nullptr;
#endif
}
