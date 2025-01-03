//============================================================
//
//	ゲームマネージャー処理 [gameManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "gameManager.h"
#include "gameState.h"
#include "manager.h"
#include "retention.h"
#include "rankingManager.h"

#ifdef SCORE
#include "multiValue.h"
#else TIMER
#include "timerUI.h"
#endif

#include "player.h"
#include "enemy.h"
#include "camera.h"

#ifdef _DEBUG
#include "editManager.h"
#endif // DEBUG

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
	namespace timer
	{
		const float TIME_START	 = 0.0f;				// 開始時間
		const CValue::EType TYPE = CValue::TYPE_NORMAL;	// 数字種類
		const VECTOR3 POS		 = VECTOR3(740.0f, 50.0f, 0.0f);				// タイマー位置
		const VECTOR3 VAL_SIZE	 = VECTOR3(52.8f, 62.4f, 0.0f) * 1.4f;			// タイマー数字大きさ
		const VECTOR3 PART_SIZE	 = VECTOR3(27.3f, 62.4f, 0.0f) * 1.2f;			// タイマー区切り大きさ
		const VECTOR3 VAL_SPACE	 = VECTOR3(VAL_SIZE.x * 0.85f, 0.0f, 0.0f);		// タイマー数字空白
		const VECTOR3 PART_SPACE = VECTOR3(PART_SIZE.x * 0.85f, 0.0f, 0.0f);	// タイマー区切り空白
	}
#endif

	namespace title
	{
		const char*		TEXTURE	= "data\\TEXTURE\\timer_title000.png";	// テクスチャパス
		const VECTOR3	POS		= VECTOR3(350.0f, timer::POS.y, 0.0f);	// 位置
		const float		HEIGHT	= timer::VAL_SIZE.y;	// 縦幅
	}

	namespace camera
	{
		const CCamera::SSwing HIT_SWING = CCamera::SSwing(8.0f, 1.8f, 0.14f);	// ヒット時のカメラ揺れ
	}
}

//************************************************************
//	親クラス [CGameManager] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CGameManager::CGameManager() :
#ifdef _DEBUG
	m_pEditManager	(nullptr),	// エディットマネージャー
#endif // DEBUG
#ifdef SCORE
	m_pScore	 (nullptr),	// スコア情報
#else TIMER
	m_pTimer	 (nullptr),	// タイマー情報
#endif
	m_pTitle	 (nullptr),	// タイトル情報
	m_pState	 (nullptr),	// 状態
	m_bControlOK (false)	// 操作可能フラグ
{

}

//============================================================
//	デストラクタ
//============================================================
CGameManager::~CGameManager()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CGameManager::Init()
{
	// メンバ変数を初期化
#ifdef _DEBUG
	m_pEditManager = nullptr;	// エディットマネージャー
#endif // DEBUG
#ifdef SCORE
	m_pScore	 = nullptr;	// スコア情報
#else TIMER
	m_pTimer	 = nullptr;	// タイマー情報
#endif
	m_pTitle	 = nullptr;	// タイトル情報
	m_pState	 = nullptr;	// 状態
	m_bControlOK = true;	// 操作可能フラグ

	// 通常状態にする
	ChangeState(new CGameStateStart);

#ifdef SCORE
	// スコアの生成
	m_pScore = CMultiValue::Create
	( // 引数
		score::TYPE,	// 数字種類
		0,				// 数字
		score::DIGIT,	// 桁数
		score::POS,		// 位置
		score::SIZE,	// 大きさ
		score::SPACE	// 空白
	);
	if (m_pScore == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}
#else TIMER
	// タイマーの生成
	m_pTimer = CTimerUI::Create
	( // 引数
		timer::TIME_START,	// 開始時間
		0.0f,				// 制限時間
		timer::POS,			// 位置
		timer::VAL_SIZE,	// 数字の大きさ
		timer::PART_SIZE,	// 区切りの大きさ
		timer::VAL_SPACE,	// 数字の空白
		timer::PART_SPACE,	// 区切りの空白
		timer::TYPE			// 数字種類
	);
	if (m_pTimer == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}
#endif

	// タイトルの生成
	m_pTitle = CObject2D::Create(title::POS);
	if (m_pTitle == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 自動ラベルを設定
	m_pTitle->SetLabel(CObject::LABEL_UI);

	// タイトルテクスチャの割当
	m_pTitle->BindTexture(title::TEXTURE);

	// タイトル大きさの設定
	float fTitleWidth = useful::GetTexWidthFromAspect(title::HEIGHT, title::TEXTURE);	// テクスチャ基準の横幅
	m_pTitle->SetVec3Size(VECTOR3(fTitleWidth, title::HEIGHT, 0.0f));

	// プレイヤーの生成
	if (CPlayer::Create(VECTOR3(0.0f, 0.0f, -300.0f), VECTOR3(0.0f, D3DX_PI, 0.0f)) == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	// 敵の生成
	if (CEnemy::Create(VECTOR3(0.0f, 0.0f, 300.0f), VECTOR3(0.0f, 0.0f, 0.0f)) == nullptr)
	{ // 生成に失敗した場合

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CGameManager::Uninit()
{
	// 状態の終了
	SAFE_UNINIT(m_pState);

#ifdef SCORE
	// スコアの終了
	//SAFE_UNINIT(m_pScore);
#else TIMER
	// タイマーの終了
	//SAFE_UNINIT(m_pTimer);
#endif

#ifdef _DEBUG
	// エディットマネージャーの破棄
	SAFE_REF_RELEASE(m_pEditManager);
#endif // DEBUG
}

//============================================================
//	更新処理
//============================================================
void CGameManager::Update(const float fDeltaTime)
{
	// 状態ごとの更新
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);

#ifdef SCORE
#ifdef _DEBUG
	// TODO：スコア加算
	m_pScore->AddNum((int)(100.0f * fDeltaTime));
#endif
	// スコアの更新
	//m_pScore->Update(fDeltaTime);
#else TIMER
	// タイマーの更新
	//m_pTimer->Update(fDeltaTime);
#endif

#ifdef _DEBUG
	// エディットマネージャーの更新
	if (m_pEditManager != nullptr) { m_pEditManager->Update(fDeltaTime); }
#endif // DEBUG
}

//============================================================
//	状態の変更処理
//============================================================
HRESULT CGameManager::ChangeState(CGameState* pState)
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
//	リザルト画面遷移処理
//============================================================
void CGameManager::TransResult()
{
	CRetention* pRetention = GET_MANAGER->GetRetention();	// データ保存マネージャー

	// フェード中の場合抜ける
	if (GET_MANAGER->GetFade()->IsFade()) { return; }

#ifdef SCORE
	// タイムの取得
	int nScore = m_pScore->GetNum();

	// スコアの保存
	pRetention->SetScore(nScore);

	// ランキングの更新
	pRetention->SetUpdateRankIdx(CRankingManager::SetRank(nScore));	// ランキング更新インデックスの保存
#else TIMER
	// タイマーの計測終了
	m_pTimer->End();

	// タイムの取得
	float fTime = m_pTimer->GetTime();

	// タイムの保存
	pRetention->SetTime(fTime);

	// ランキングの更新
	pRetention->SetUpdateRankIdx(CRankingManager::SetRank(fTime));	// ランキング更新インデックスの保存
#endif

	GET_MANAGER->GetCamera()->SetSwing(camera::HIT_SWING);

	// リザルト画面に遷移する
	GET_MANAGER->SetLoadScene(CScene::MODE_RESULT, 1.0f);
}

//============================================================
//	タイマーの計測開始処理
//============================================================
void CGameManager::TimerStart()
{
	// タイマーの計測開始
	m_pTimer->Start();
}

//============================================================
//	通常状態かの確認処理
//============================================================
bool CGameManager::IsNormal() const
{
	// 通常状態かを判定し返す
	return (typeid(*m_pState) == typeid(CGameStateNormal));
}

//============================================================
//	ゲーム時間取得処理
//============================================================
float CGameManager::GetGameTime() const
{
	return m_pTimer->GetTime();
}

//============================================================
//	生成処理
//============================================================
CGameManager* CGameManager::Create()
{
	// ゲームマネージャーの生成
	CGameManager* pGameManager = new CGameManager;
	if (pGameManager == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// ゲームマネージャーの初期化
		if (FAILED(pGameManager->Init()))
		{ // 初期化に失敗した場合

			// ゲームマネージャーの破棄
			SAFE_DELETE(pGameManager);
			return nullptr;
		}

		// 確保したアドレスを返す
		return pGameManager;
	}
}

//============================================================
//	破棄処理
//============================================================
void CGameManager::Release(CGameManager*& prGameManager)
{
	// ゲームマネージャーの終了
	assert(prGameManager != nullptr);
	prGameManager->Uninit();

	// メモリ開放
	SAFE_DELETE(prGameManager);
}

#ifdef _DEBUG
//============================================================
//	エディットモードの変更処理
//============================================================
void CGameManager::ChangeEnableEdit()
{
	if (m_pEditManager == nullptr)
	{
		// エディットマネージャーの生成
		m_pEditManager = CEditManager::Create();
	}
	else
	{
		// エディットマネージャーの破棄
		SAFE_REF_RELEASE(m_pEditManager);
	}
}
#endif // DEBUG
