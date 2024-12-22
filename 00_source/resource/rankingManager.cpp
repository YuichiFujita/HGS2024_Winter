//============================================================
//
//	ランキングマネージャー処理 [rankingManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "rankingManager.h"
#include "rankingState.h"
#include "manager.h"

//************************************************************
//	親クラス [CRankingManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CRankingManager::CRankingManager() :
	m_pState	(nullptr)	// 状態
{

}

//============================================================
//	デストラクタ
//============================================================
CRankingManager::~CRankingManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CRankingManager::Init()
{
	// メンバ変数を初期化
	m_pState = nullptr;	// 状態

	// 通常状態にする
	ChangeState(new CRankingStateNormal);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CRankingManager::Uninit()
{
	// 状態の終了
	SAFE_UNINIT(m_pState);
}

//============================================================
//	更新処理
//============================================================
void CRankingManager::Update(const float fDeltaTime)
{
	// 状態ごとの更新
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	状態の変更処理
//============================================================
HRESULT CRankingManager::ChangeState(CRankingState* pState)
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
//	生成処理
//============================================================
CRankingManager* CRankingManager::Create()
{
	// ランキングマネージャーの生成
	CRankingManager* pRankingManager = new CRankingManager;
	if (pRankingManager == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// ランキングマネージャーの初期化
		if (FAILED(pRankingManager->Init()))
		{ // 初期化に失敗した場合

			// ランキングマネージャーの破棄
			SAFE_DELETE(pRankingManager);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pRankingManager;
	}
}

//============================================================
//	破棄処理
//============================================================
void CRankingManager::Release(CRankingManager*& prRankingManager)
{
	// ランキングマネージャーの終了
	assert(prRankingManager != nullptr);
	prRankingManager->Uninit();

	// メモリ開放
	SAFE_DELETE(prRankingManager);
}
