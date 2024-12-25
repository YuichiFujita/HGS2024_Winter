//============================================================
//
//	設置型プレゼント処理 [presentLand.cpp]
//	Author：小原立暉
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
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

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const float	GRAVITY = 3600.0f;	// 重力
	const float	RADIUS = 20.0f;	// 半径
	const float HEIGHT = 80.0f;	// 身長

	// 飛行状態の定数
	namespace fly
	{
		const float DEST_POS_Y = 600.0f;	// 目的の高さ
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
// 無し状態処理
//============================================================
void CPresentLand::UpdateNone(const float fDeltaTime)
{
	// プレイヤーがいない場合、抜ける
	CPlayer* pPlayer = CScene::GetPlayer();
	if (pPlayer == nullptr) { return; }

	// 目的の位置を設定する
	m_destPos = pPlayer->GetVec3Position();

	// 高さを再設定する
	m_destPos.y = fly::DEST_POS_Y;

	// 飛び状態にする
	m_state = STATE_FLY;
}

//============================================================
// 飛び状態処理
//============================================================
void CPresentLand::UpdateFly(const float fDeltaTime)
{
	CPlayer* pPlayer = CScene::GetPlayer();

	if (pPlayer == nullptr) { return; }

	// 目的の位置を設定する
	m_destPos = pPlayer->GetVec3Position();

	// 目的の高さを再設定する
	m_destPos.y = fly::DEST_POS_Y;

	// 透明度を設定する
	SetAlpha(fly::ALPHA);
}

//============================================================
// 落下状態処理
//============================================================
void CPresentLand::UpdateFall(const float fDeltaTime)
{
	D3DXVECTOR3 pos = GetVec3Position();

	// 重力をかける
	m_move.y += GRAVITY * fDeltaTime;

	// 移動する
	pos += m_move;

	// 位置を設定する
	SetVec3Position(pos);
}
