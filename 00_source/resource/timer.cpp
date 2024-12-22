//============================================================
//
//	タイマー処理 [timer.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "timer.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const int PRIORITY = 0;	// タイマーの優先順位
}

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CListManager<CTimer>* CTimer::m_pList = nullptr;	// オブジェクトリスト

//************************************************************
//	子クラス [CTimer] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CTimer::CTimer() : CObject(CObject::LABEL_TIMER, CObject::DIM_3D, PRIORITY),
	m_funcCount	(nullptr),		// 計測関数ポインタ
	m_state		(STATE_NONE),	// 計測状態
	m_fTime		(0.0f),			// 計測時間
	m_fLimit	(0.0f),			// 制限時間
	m_bStop		(false),		// 計測停止状況
	m_lTime		(0),			// 計測ミリ秒
	m_nMin		(0),			// 分
	m_nSec		(0),			// 秒
	m_nMSec		(0)				// ミリ秒
{

}

//============================================================
//	デストラクタ
//============================================================
CTimer::~CTimer()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CTimer::Init()
{
	// メンバ変数を初期化
	m_funcCount = nullptr;		// 計測関数ポインタ
	m_state		= STATE_NONE;	// 計測状態
	m_fTime		= 0.0f;			// 計測時間
	m_fLimit	= 0.0f;			// 制限時間
	m_bStop		= false;		// 計測停止状況
	m_lTime		= 0;			// 計測ミリ秒
	m_nMin		= 0;			// 分
	m_nSec		= 0;			// 秒
	m_nMSec		= 0;			// ミリ秒

	if (m_pList == nullptr)
	{ // リストマネージャーが存在しない場合

		// リストマネージャーの生成
		m_pList = CListManager<CTimer>::Create();
		if (m_pList == nullptr)
		{ // 生成に失敗した場合

			assert(false);
			return E_FAIL;
		}
	}

	// リストに自身のオブジェクトを追加・イテレーターを取得
	m_iterator = m_pList->AddList(this);

	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CTimer::Uninit()
{
	// リストから自身のオブジェクトを削除
	m_pList->DelList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // オブジェクトが一つもない場合

		// リストマネージャーの破棄
		m_pList->Release(m_pList);
	}

	// オブジェクトを破棄
	Release();
}

//============================================================
//	更新処理
//============================================================
void CTimer::Update(const float fDeltaTime)
{
	switch (m_state)
	{ // 計測状態ごとの処理
	case STATE_NONE:
		break;

	case STATE_COUNT:

		// 停止中の場合抜ける
		if (m_bStop) { break; }

		// タイムを計測
		assert(m_funcCount != nullptr);
		m_funcCount(fDeltaTime);

		break;

	case STATE_END:
		break;

	default:	// 例外処理
		assert(false);
		break;
	}

	// 時間の計算
	CalcTime();
}

//============================================================
//	描画処理
//============================================================
void CTimer::Draw(CShader* /*pShader*/)
{

}

//============================================================
//	生成処理
//============================================================
CTimer* CTimer::Create
(
	const float fTime,	// 開始時間
	const float fLimit	// 制限時間
)
{
	// タイマーの生成
	CTimer* pTimer = new CTimer;
	if (pTimer == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// タイマーの初期化
		if (FAILED(pTimer->Init()))
		{ // 初期化に失敗した場合

			// タイマーの破棄
			SAFE_DELETE(pTimer);
			return nullptr;
		}

		// 開始時間を設定
		pTimer->SetTime(fTime);

		// 制限時間を設定
		pTimer->SetLimit(fLimit);

		// 確保したアドレスを返す
		return pTimer;
	}
}

//============================================================
//	リスト取得処理
//============================================================
CListManager<CTimer>* CTimer::GetList()
{
	// オブジェクトリストを返す
	return m_pList;
}

//============================================================
//	全タイマーの計測状況の設定処理
//============================================================
void CTimer::EnableStopAll(const bool bStop)
{
	// タイマーがない場合抜ける
	if (m_pList == nullptr) { return; }

	// リストマネージャーからリストを取得
	std::list<CTimer*> listTimer = m_pList->GetList();

	// 全タイマーオブジェクトの計測状況を設定
	for (auto& rList : listTimer)
	{ // リスト内の要素数分繰り返す

		rList->EnableStop(bStop);
	}
}

//============================================================
//	計測開始処理
//============================================================
void CTimer::Start()
{
	if (m_state != STATE_COUNT)
	{ // タイムの計測中ではない場合

		// 非停止状態にする
		EnableStop(false);

		// 計測開始状態にする
		m_state = STATE_COUNT;
	}
}

//============================================================
//	計測終了処理
//============================================================
void CTimer::End()
{
	if (m_state == STATE_COUNT)
	{ // タイムの計測中の場合

		// 停止状態にする
		EnableStop(true);

		// 計測終了状態にする
		m_state = STATE_END;
	}
}

//============================================================
//	計測停止の有効無効の設定処理
//============================================================
void CTimer::EnableStop(const bool bStop)
{
	// 引数の停止状況を代入
	m_bStop = bStop;
}

//============================================================
//	時間の加算処理
//============================================================
void CTimer::AddTime(const float fTime)
{
	// 時間を加算
	m_fTime += fTime;

	// 時間を補正
	useful::LimitNum(m_fTime, CTimer::TIME_MIN, CTimer::TIME_MAX);
}

//============================================================
//	時間の設定処理
//============================================================
void CTimer::SetTime(const float fTime)
{
	// 時間を設定
	m_fTime = fTime;

	// 時間を補正
	useful::LimitNum(m_fTime, CTimer::TIME_MIN, CTimer::TIME_MAX);
}

//============================================================
//	制限時間の設定処理
//============================================================
void CTimer::SetLimit(const float fLimit)
{
	// 制限時間を保存
	m_fLimit = fLimit;

	// 制限時間を補正
	useful::LimitNum(m_fLimit, CTimer::TIME_MIN, CTimer::TIME_MAX);

	if (m_fLimit <= 0.0f)
	{ // 制限時間がない場合

		// カウントアップ関数を設定
		m_funcCount = std::bind(&CTimer::CountUp, this, std::placeholders::_1);
	}
	else
	{ // 時間制限がある場合

		// 制限の開始時間を設定
		m_fTime = fLimit;

		// カウントダウン関数を設定
		m_funcCount = std::bind(&CTimer::CountDown, this, std::placeholders::_1);
	}
}

//============================================================
//	カウントアップ処理
//============================================================
void CTimer::CountUp(const float fDeltaTime)
{
	// デルタタイムを加算
	m_fTime += fDeltaTime;
}

//============================================================
//	カウントダウン処理
//============================================================
void CTimer::CountDown(const float fDeltaTime)
{
	// デルタタイムを減算
	m_fTime -= fDeltaTime;
	if (m_fTime <= 0.0f)
	{  // カウント終了した場合

		// タイムを補正
		m_fTime = 0.0f;

		// 計測を終了
		End();
	}
}

//============================================================
//	時間の計算処理
//============================================================
void CTimer::CalcTime()
{
	m_lTime	= (DWORD)(m_fTime * 1000.0f);	// 秒をミリ秒に変換
	m_nMin	= (int)(m_lTime / 60000);		// 分を計算
	m_nSec	= (int)(m_lTime / 1000) % 60;	// 秒を計算
	m_nMSec	= (int)(m_lTime % 1000);		// ミリ秒を計算
}
