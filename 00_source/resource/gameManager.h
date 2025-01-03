//============================================================
//
//	ゲームマネージャーヘッダー [gameManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CGameState;	// ゲーム状態クラス

#ifdef SCORE
class CMultiValue;	// マルチ数字クラス
#else TIMER
class CTimerUI;		// タイマーUIクラス
#endif

class CObject2D;	// オブジェクト2Dクラス

#ifdef _DEBUG
class CEditManager;	// エディットマネージャークラス
#endif // _DEBUG

//************************************************************
//	クラス定義
//************************************************************
// ゲームマネージャークラス
class CGameManager
{
public:
	// コンストラクタ
	CGameManager();

	// デストラクタ
	~CGameManager();

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update(const float fDeltaTime);		// 更新
	HRESULT ChangeState(CGameState* pState);	// 状態変更
	void TransResult();		// リザルト画面遷移
	void TimerStart();		// タイマー計測開始
	bool IsNormal() const;	// 通常状態確認
	inline void SetEnableControlOK(const bool bOK)	{ m_bControlOK = bOK; }		// 操作可能フラグ設定
	inline bool IsControlOK() const					{ return m_bControlOK; }	// 操作可能フラグ取得

#ifdef TIMER
	float GetGameTime() const;	// タイム取得
#endif

#ifdef _DEBUG
	void ChangeEnableEdit();	// エディットモード変更
#endif // DEBUG

	// 静的メンバ関数
	static CGameManager* Create();	// 生成
	static void Release(CGameManager*& prGameManager);	// 破棄

private:
	// メンバ変数
#ifdef SCORE
	CMultiValue* m_pScore;	// スコア情報
#else TIMER
	CTimerUI* m_pTimer;		// タイマー情報
#endif
	CObject2D* m_pTitle;	// タイトル情報
	CGameState* m_pState;	// 状態
	bool m_bControlOK;		// 操作可能フラグ

#ifdef _DEBUG
	CEditManager* m_pEditManager;	// エディットマネージャー
#endif // DEBUG
};

#endif	// _GAMEMANAGER_H_
