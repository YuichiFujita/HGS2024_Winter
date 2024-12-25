//============================================================
//
//	設置型プレゼントヘッダー [presentLand.h]
//	Author：小原立暉
// 
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _PRESENT_LAND_H_
#define _PRESENT_LAND_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "presentCopy.h"

//************************************************************
//	クラス定義
//************************************************************
// 設置型プレゼントクラス
class CPresentLand : public CPresent
{
public:

	// モデル列挙
	enum EModel
	{
		MODEL_WAIST = 0,	// 腰
		MODEL_BODY,			// 体
		MODEL_HEAD,			// 頭
		MODEL_ARMUL,		// 左上腕
		MODEL_ARMUR,		// 右上腕
		MODEL_ARMDL,		// 左下腕
		MODEL_ARMDR,		// 右下腕
		MODEL_HANDL,		// 左手
		MODEL_HANDR,		// 右手
		MODEL_LEGUL,		// 左太もも
		MODEL_LEGUR,		// 右太もも
		MODEL_LEGDL,		// 左脛
		MODEL_LEGDR,		// 右脛
		MODEL_FOOTL,		// 左足
		MODEL_FOOTR,		// 右足
		MODEL_MAX			// この列挙型の総数
	};

	// コンストラクタ
	CPresentLand();

	// デストラクタ
	~CPresentLand() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetEnableUpdate(const bool bUpdate) override;	// 更新状況設定
	void SetEnableDraw(const bool bDraw) override;		// 描画状況設定

private:
	// メンバ関数

	// メンバ変数
	CListManager<CPresent>::AIterator m_iterator;	// イテレーター
};

#endif	// _PLAYER_H_
