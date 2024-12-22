//============================================================
//
//	ランキング画面ヘッダー [sceneRanking.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _SCENE_RANKING_H_
#define _SCENE_RANKING_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "scene.h"

//************************************************************
//	前方宣言
//************************************************************
class CRankingManager;	// ランキングマネージャークラス

//************************************************************
//	クラス定義
//************************************************************
// ランキング画面クラス
class CSceneRanking : public CScene
{
public:
	// コンストラクタ
	explicit CSceneRanking(const EMode mode);

	// デストラクタ
	~CSceneRanking() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新

	// 静的メンバ関数
	static CRankingManager* GetRankingManager();	// ランキングマネージャー取得

private:
	// 静的メンバ変数
	static CRankingManager* m_pRankingManager;	// ランキングマネージャー
};

#endif	// _SCENE_RANKING_H_
