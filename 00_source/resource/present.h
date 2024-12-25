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
#include "objectModel.h"

//************************************************************
//	クラス定義
//************************************************************
// プレゼントクラス
class CPresent : public CObjectModel
{
public:

	// 種類
	enum EType
	{
		TYPE_LAND = 0,	// 設置型
		TYPE_BULLET,	// 弾型
		TYPE_MAX		// この列挙型の総数
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
	virtual float GetRadius() const = 0;				// 半径取得
	virtual float GetHeight() const = 0;				// 縦幅取得

	// 静的メンバ関数
	static CListManager<CPresent>* GetList();	// リスト取得

	// メンバ関数

private:
	// メンバ関数

	// 静的メンバ変数
	static CListManager<CPresent>* m_pList;	// オブジェクトリスト

	// メンバ変数
	CListManager<CPresent>::AIterator m_iterator;	// イテレーター
	EType m_type;									// 種類
};

#endif	// _PRESENT_H_
