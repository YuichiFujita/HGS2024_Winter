//============================================================
//
//	プレゼントヘッダー [present.h]
//	Author：小原立暉
// 
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _PRESENT_H_
#define _PRESENT_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "objectChara.h"

//************************************************************
//	クラス定義
//************************************************************
// プレゼントクラス
class CPresent : public CObjectChara
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
	CPresent();

	// デストラクタ
	~CPresent() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetEnableUpdate(const bool bUpdate) override;	// 更新状況設定
	void SetEnableDraw(const bool bDraw) override;		// 描画状況設定

	// 静的メンバ関数
	static CPresent* Create	// 生成
	( // 引数
		const VECTOR3& rPos,	// 位置
		const VECTOR3& rRot		// 向き
	);
	static CListManager<CPresent>* GetList();	// リスト取得

	// メンバ関数

private:
	// メンバ関数

	// 静的メンバ変数
	static CListManager<CPresent>* m_pList;	// オブジェクトリスト

	// メンバ変数
	CListManager<CPresent>::AIterator m_iterator;	// イテレーター
};

#endif	// _PLAYER_H_
