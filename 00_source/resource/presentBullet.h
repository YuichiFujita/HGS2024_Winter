//============================================================
//
//	弾型プレゼントヘッダー [presentBullet.h]
//	Author：小原立暉
// 
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _PRESENT_BULLET_H_
#define _PRESENT_BULLET_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "present.h"

//************************************************************
//	クラス定義
//************************************************************
// 弾型プレゼントクラス
class CPresentBullet : public CPresent
{
public:

	// コンストラクタ
	CPresentBullet();

	// デストラクタ
	~CPresentBullet() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;		// 更新
	void Draw(CShader* pShader = nullptr) override;		// 描画
	void SetEnableUpdate(const bool bUpdate) override;	// 更新状況設定
	void SetEnableDraw(const bool bDraw) override;		// 描画状況設定
	float GetRadius() const override;					// 半径取得
	float GetHeight() const override;					// 縦幅取得

private:
	// メンバ関数


	// メンバ変数
};

#endif	// _PLAYER_H_
