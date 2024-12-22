//============================================================
//
//	ランキングマネージャーヘッダー [rankingManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _RANKINGMANAGER_H_
#define _RANKINGMANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CRankingState;	// ランキング状態クラス

//************************************************************
//	クラス定義
//************************************************************
// ランキングマネージャークラス
class CRankingManager
{
public:
	// コンストラクタ
	CRankingManager();

	// デストラクタ
	~CRankingManager();

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update(const float fDeltaTime);		// 更新
	HRESULT ChangeState(CRankingState* pState);	// 状態変更

	// 静的メンバ関数
	static CRankingManager* Create();	// 生成
	static void Release(CRankingManager*& prRankingManager);	// 破棄

private:
	// メンバ変数
	CRankingState* m_pState;	// 状態
};

#endif	// _RANKINGMANAGER_H_
