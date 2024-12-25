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

	// 状態
	enum EState
	{
		STATE_HOMING = 0,	// ホーミング状態
		STATE_MOVE,			// 移動状態
		STATE_DEATH,		// 死亡状態
		STATE_MAX			// この列挙型の総数
	};

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

	// 静的メンバ関数
	static CPresentBullet* Create	// 生成
	( // 引数
		const VECTOR3& rPos,	// 位置
		const float fRotY		// 方向
	);

private:
	// エイリアス定義
	typedef void(CPresentBullet::* AFuncState)(const float);	// 状態更新関数ポインタ

	// 関数配列
	static AFuncState m_aFuncState[];	// 状態更新関数リスト

	// メンバ関数
	void Collision();							// 当たり判定

	void UpdateHoming(const float fDeltaTime);			// ホーミング処理
	void UpdateMove(const float fDeltaTime);			// 移動処理
	void UpdateDeath(const float fDeltaTime);			// 死亡処理
	void UpdateRotation(const float fDeltaTime);		// 向きの更新処理

	// メンバ変数
	EState m_state;			// 状態
	VECTOR3 m_destRot;		// 目的の向き
	float m_fStateTime;		// 状態時間
	float m_fSpeed;			// 速度
};

#endif	// _PRESENT_BULLET_H_
