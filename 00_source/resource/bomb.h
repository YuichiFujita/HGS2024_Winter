//============================================================
//
//	爆弾ヘッダー [bomb.h]
//	Author：小原立暉
// 
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _BOMB_H_
#define _BOMB_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "objectModel.h"

//************************************************************
//	クラス定義
//************************************************************
// 爆弾クラス
class CBomb : public CObjectModel
{
public:

	// コンストラクタ
	CBomb();

	// デストラクタ
	~CBomb() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetEnableUpdate(const bool bUpdate) override;	// 更新状況設定
	void SetEnableDraw(const bool bDraw) override;		// 描画状況設定
	float GetRadius() const;							// 半径取得
	float GetHeight() const;							// 縦幅取得

	// 静的メンバ関数
	static CBomb* Create(const VECTOR3& rPos);	// 生成
	static CListManager<CBomb>* GetList();	// リスト取得

	// メンバ関数

private:
	// メンバ関数

	// 静的メンバ変数
	static CListManager<CBomb>* m_pList;	// オブジェクトリスト

	// メンバ変数
	CListManager<CBomb>::AIterator m_iterator;	// イテレーター
};

#endif	// _PRESENT_H_
