//============================================================
//
//	リザルトマネージャーヘッダー [resultManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _RESULTMANAGER_H_
#define _RESULTMANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CResultState;	// リザルト状態クラス

#ifdef SCORE
class CMultiValue;	// マルチ数字クラス
#else TIMER
class CTimeUI;		// タイムUIクラス
#endif

//************************************************************
//	クラス定義
//************************************************************
// リザルトマネージャークラス
class CResultManager
{
public:
	// コンストラクタ
	CResultManager();

	// デストラクタ
	~CResultManager();

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update(const float fDeltaTime);		// 更新
	HRESULT ChangeState(CResultState* pState);	// 状態変更
	void TransRanking();	// ランキング画面遷移

	// 静的メンバ関数
	static CResultManager* Create();	// 生成
	static void Release(CResultManager*& prResultManager);	// 破棄

private:
	// メンバ変数
#ifdef SCORE
	CMultiValue* m_pScore;	// スコア情報
#else TIMER
	CTimeUI* m_pTime;		// タイム情報
#endif
	CResultState* m_pState;	// 状態
};

#endif	// _RESULTMANAGER_H_
