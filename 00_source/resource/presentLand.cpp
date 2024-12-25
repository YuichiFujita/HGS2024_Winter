//============================================================
//
//	設置型プレゼント処理 [presentLand.cpp]
//	Author：小原立暉
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "main.h"
#include "presentLand.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "fade.h"
#include "stage.h"
#include "sceneGame.h"
#include "gameManager.h"
#include "player.h"
#include "enemy.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* MODEL = "data\\MODEL\\PLAYER\\02_head.x";	// モデルの情報
	const float	GRAVITY = 1.0f;	// 重力
	const float	RADIUS = 20.0f;	// 半径
	const float HEIGHT = 80.0f;	// 身長

	// 無し状態の定数
	namespace none
	{
		const float DEST_POS_Y = 300.0f;	// 目的の高さ
	}

	// 飛行状態の定数
	namespace fly
	{
		const float ADD_HEIGHT = 50.0f;	// 追加の高さ
		const float END_TIME = 4.0f;	// 終了までの時間
		const float ALPHA = 0.5f;	// 透明度
	}
}

//************************************************************
// 静的メンバ変数宣言
//************************************************************
CPresentLand::AFuncState CPresentLand::m_aFuncState[] =		// 状態更新関数リスト
{
	&CPresentLand::UpdateNone,	// 無し状態の更新
	&CPresentLand::UpdateFly,	// 飛び状態の更新
	&CPresentLand::UpdateFall,	// 落下状態の更新
};

//************************************************************
//	子クラス [CPresentLand] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CPresentLand::CPresentLand() : CPresent(),
m_fFlyTime(0.0f),		// 飛ぶ時間
m_originPos(VEC3_ZERO),	// 初期位置
m_destPos(VEC3_ZERO),	// 目的の位置
m_move(VEC3_ZERO),		// 移動量
m_state(STATE_NONE)		// 状態
{
	// スタティックアサート
	static_assert(NUM_ARRAY(m_aFuncState) == CPresentLand::STATE_MAX, "ERROR : State Count Mismatch");
}

//============================================================
//	デストラクタ
//============================================================
CPresentLand::~CPresentLand()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CPresentLand::Init()
{
	m_destPos = VEC3_ZERO;	// 目的の位置
	m_move = VEC3_ZERO;		// 移動量
	m_state = STATE_NONE;	// 状態

	// オブジェクトキャラクターの初期化
	if (FAILED(CPresent::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// モデルの割り当て処理
	BindModel(MODEL);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CPresentLand::Uninit()
{
	// オブジェクトキャラクターの終了
	CPresent::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CPresentLand::Update(const float fDeltaTime)
{
	// 状態処理
	(this->*(m_aFuncState[m_state]))(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CPresentLand::Draw(CShader* pShader)
{
	// オブジェクトキャラクターの描画
	CPresent::Draw(pShader);
}

//============================================================
//	更新状況の設定処理
//============================================================
void CPresentLand::SetEnableUpdate(const bool bUpdate)
{
	// 引数の更新状況を設定
	CObject::SetEnableUpdate(bUpdate);	// 自身
}

//============================================================
//	描画状況の設定処理
//============================================================
void CPresentLand::SetEnableDraw(const bool bDraw)
{
	// 引数の描画状況を設定
	CObject::SetEnableDraw(bDraw);	// 自身
}

//============================================================
// 半径取得
//============================================================
float CPresentLand::GetRadius() const
{
	// 半径を返す
	return RADIUS;
}

//============================================================
// 縦幅取得
//============================================================
float CPresentLand::GetHeight() const
{
	// 高さを返す
	return HEIGHT;
}

//============================================================
// 速度計算処理
//============================================================
void CPresentLand::SpeedCalc()
{

}

//============================================================
// 無し状態処理
//============================================================
void CPresentLand::UpdateNone(const float fDeltaTime)
{
	// 初期位置を設定する
	m_originPos = GetVec3Position();

	// プレイヤーがいない場合、抜ける
	CPlayer* pPlayer = CScene::GetPlayer();
	if (pPlayer == nullptr) { return; }

	// 目的の位置を設定する
	m_destPos = pPlayer->GetVec3Position();

	// 高さを再設定する
	m_destPos.y = none::DEST_POS_Y;

	// 飛び状態にする
	m_state = STATE_FLY;
}

//============================================================
// 飛び状態処理
//============================================================
void CPresentLand::UpdateFly(const float fDeltaTime)
{
	D3DXVECTOR3 pos = GetVec3Position();

	// 放物線処理
	pos = useful::GetParabola3D(m_originPos, m_destPos, m_destPos.y + fly::ADD_HEIGHT, fly::END_TIME, m_fFlyTime);

	// 飛んでいる時間を更新
	m_fFlyTime += fDeltaTime;

	// 一定時間飛んだ場合、落下状態にする
	if (m_fFlyTime >= fly::END_TIME) { m_state = STATE_FALL; }

	// 位置を反映する
	SetVec3Position(pos);
}

//============================================================
// 落下状態処理
//============================================================
void CPresentLand::UpdateFall(const float fDeltaTime)
{
	float fDeltaRate = fDeltaTime / (1.0f / (float)main::FPS);	// 経過時間の割合
	D3DXVECTOR3 pos = GetVec3Position();

	// 重力をかける
	m_move.y -= GRAVITY * fDeltaRate;

	// 移動する
	pos += m_move;

	// 位置を設定する
	SetVec3Position(pos);

	// 透明度を設定する
	SetAlpha(fly::ALPHA);
}
