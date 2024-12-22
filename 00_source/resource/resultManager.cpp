//============================================================
//
//	リザルトマネージャー処理 [resultManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "resultManager.h"
#include "resultState.h"
#include "manager.h"

//************************************************************
//	親クラス [CResultManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CResultManager::CResultManager() :
	m_pState	(nullptr)	// 状態
{

}

//============================================================
//	デストラクタ
//============================================================
CResultManager::~CResultManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CResultManager::Init()
{
	// メンバ変数を初期化
	m_pState = nullptr;	// 状態

	// 通常状態にする
	ChangeState(new CResultStateNormal);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CResultManager::Uninit()
{
	// 状態の終了
	SAFE_UNINIT(m_pState);
}

//============================================================
//	更新処理
//============================================================
void CResultManager::Update(const float fDeltaTime)
{
	// 状態ごとの更新
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	状態の変更処理
//============================================================
HRESULT CResultManager::ChangeState(CResultState* pState)
{
	// 状態の生成に失敗している場合抜ける
	if (pState == nullptr) { assert(false); return E_FAIL; }

	// 状態インスタンスを終了
	SAFE_UNINIT(m_pState);

	// 状態インスタンスを変更
	assert(m_pState == nullptr);
	m_pState = pState;

	// 状態にコンテキストを設定
	m_pState->SetContext(this);

	// 状態インスタンスを初期化
	if (FAILED(m_pState->Init()))
	{ // 初期化に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	ランキング画面遷移処理
//============================================================
void CResultManager::TransRanking()
{
	// ランキング画面に遷移する
	GET_MANAGER->SetLoadScene(CScene::MODE_RANKING);
}

//============================================================
//	生成処理
//============================================================
CResultManager* CResultManager::Create()
{
	// リザルトマネージャーの生成
	CResultManager* pResultManager = new CResultManager;
	if (pResultManager == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// リザルトマネージャーの初期化
		if (FAILED(pResultManager->Init()))
		{ // 初期化に失敗した場合

			// リザルトマネージャーの破棄
			SAFE_DELETE(pResultManager);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pResultManager;
	}
}

//============================================================
//	破棄処理
//============================================================
void CResultManager::Release(CResultManager*& prResultManager)
{
	// リザルトマネージャーの終了
	assert(prResultManager != nullptr);
	prResultManager->Uninit();

	// メモリ開放
	SAFE_DELETE(prResultManager);
}
