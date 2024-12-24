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
#include "retention.h"

#ifdef SCORE
#include "multiValue.h"
#else TIMER
#include "timeUI.h"
#endif

//************************************************************
//	定数宣言
//************************************************************
namespace
{
#ifdef SCORE
	namespace score
	{
		const CValue::EType TYPE = CValue::TYPE_NORMAL;	// 数字種類
		const float DIGIT	= 8;			// スコア桁数
		const VECTOR3 POS	= SCREEN_CENT;	// スコア位置
		const VECTOR3 SIZE	= VECTOR3(52.8f, 62.4f, 0.0f) * 1.4f;	// スコア数字大きさ
		const VECTOR3 SPACE	= VECTOR3(SIZE.x * 0.85f, 0.0f, 0.0f);	// スコア数字空白
	}
#else TIMER
	namespace time
	{
		const CValue::EType TYPE = CValue::TYPE_NORMAL;	// 数字種類
		const VECTOR3 POS		 = SCREEN_CENT;			// タイマー位置
		const VECTOR3 VAL_SIZE	 = VECTOR3(52.8f, 62.4f, 0.0f) * 1.4f;			// タイマー数字大きさ
		const VECTOR3 PART_SIZE	 = VECTOR3(27.3f, 62.4f, 0.0f) * 1.2f;			// タイマー区切り大きさ
		const VECTOR3 VAL_SPACE	 = VECTOR3(VAL_SIZE.x * 0.85f, 0.0f, 0.0f);		// タイマー数字空白
		const VECTOR3 PART_SPACE = VECTOR3(PART_SIZE.x * 0.85f, 0.0f, 0.0f);	// タイマー区切り空白
	}
#endif
}

//************************************************************
//	親クラス [CResultManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CResultManager::CResultManager() :
#ifdef SCORE
	m_pScore	(nullptr),	// スコア情報
#else TIMER
	m_pTime		(nullptr),	// タイム情報
#endif
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
	CRetention* pRetention = GET_MANAGER->GetRetention();	// データ保存マネージャー

	// メンバ変数を初期化
#ifdef SCORE
	m_pScore = nullptr;	// スコア情報
#else TIMER
	m_pTime = nullptr;	// タイム情報
#endif
	m_pState = nullptr;	// 状態

	// 通常状態にする
	ChangeState(new CResultStateNormal);

#ifdef SCORE
	// スコアの生成
	m_pScore = CMultiValue::Create
	( // 引数
		score::TYPE,			// 数字種類
		pRetention->GetScore(),	// 数字
		score::DIGIT,			// 桁数
		score::POS,				// 位置
		score::SIZE,			// 大きさ
		score::SPACE			// 空白
	);
	if (m_pScore == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}
#else TIMER
	// タイムの生成
	m_pTime = CTimeUI::Create
	( // 引数
		pRetention->GetTime(),	// 時間
		time::POS,				// 位置
		time::VAL_SIZE,			// 数字の大きさ
		time::PART_SIZE,		// 区切りの大きさ
		time::VAL_SPACE,		// 数字の空白
		time::PART_SPACE,		// 区切りの空白
		time::TYPE				// 数字種類
	);
	if (m_pTime == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}
#endif

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CResultManager::Uninit()
{
	// 状態の終了
	SAFE_UNINIT(m_pState);

#ifdef SCORE
	// スコアの終了
	//SAFE_UNINIT(m_pScore);
#else TIMER
	// タイムの終了
	//SAFE_UNINIT(m_pTimer);
#endif
}

//============================================================
//	更新処理
//============================================================
void CResultManager::Update(const float fDeltaTime)
{
	// 状態ごとの更新
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);

	if (input::Decide())
	{
		// ランキング画面に遷移する
		TransRanking();
	}

#ifdef SCORE
	// スコアの更新
	//m_pScore->Update(fDeltaTime);
#else TIMER
	// タイムの更新
	//m_pTime->Update(fDeltaTime);
#endif
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
	// フェード中の場合抜ける
	if (GET_MANAGER->GetFade()->IsFade()) { return; }

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
