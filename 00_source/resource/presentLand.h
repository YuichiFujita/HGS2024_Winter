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
#include "present.h"

//************************************************************
//	クラス定義
//************************************************************
// 設置型プレゼントクラス
class CPresentLand : public CPresent
{
public:

	// 状態
	enum EState
	{
		STATE_NONE = 0,		// 無し状態
		STATE_FLY,			// 飛ぶ状態
		STATE_SENSOR,		// センサー状態
		STATE_DELETE,		// 削除状態
		STATE_MAX			// この列挙型の総数
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
	float GetRadius() const override;					// 半径取得
	float GetHeight() const override;					// 縦幅取得

private:
	// エイリアス定義
	typedef void(CPresentLand::* AFuncState)(const float);	// 状態更新関数ポインタ

	// 関数配列
	static AFuncState m_aFuncState[];	// 状態更新関数リスト

	// メンバ関数
	void SpeedCalc();							// 速度計算処理
	bool FieldCollision();						// フィールドの当たり判定
	bool AttackSensor();						// センサー判定

	void UpdateNone(const float fDeltaTime);	// 無し状態処理
	void UpdateFly(const float fDeltaTime);		// 飛ぶ状態処理
	void UpdateSensor(const float fDeltaTime);	// センサー状態処理
	void UpdateDelete(const float fDeltaTime);	// 削除状態処理

	// メンバ変数
	float m_fStateTime;			// 状態の時間
	VECTOR3	m_oldPos;			// 過去位置
	VECTOR3 m_originPos;		// 初期位置
	VECTOR3 m_destPos;			// 目的の位置
	VECTOR3 m_move;				// 移動量
	EState m_state;				// 状態
};

#endif	// _PRESENT_LAND_H_
