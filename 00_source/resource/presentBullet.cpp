//============================================================
//
//	弾型プレゼント処理 [presentBullet.cpp]
//	Author：小原立暉
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "presentBullet.h"
#include "main.h"
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
#include "particle3D.h"
#include "collision.h"
#include "effect3D.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* MODEL = "data\\MODEL\\PRESENT\\PresentBag.x";	// モデル
	const float	RADIUS = 50.0f;	// 半径
	const float HEIGHT = 80.0f;	// 身長
	const float SPEED = 570.0f;	// 速度
	const float	REV_ROTA = 0.06f;	// 向き変更の補正係数
	const float SUB_SPEED = 230.0f;	// 速度の減算量

	// 移動状態
	namespace move
	{
		const float TIME = 1.0f;	// 移動状態の時間
	}

	// エフェクト
	namespace effect
	{
		const float RADIUS = 20.0f;		// 半径
		const int LIFE = 10;			// 寿命
		const float SUB_SIZE = 0.1f;	// 半径の減算量
	}
}

//************************************************************
// 静的メンバ変数宣言
//************************************************************
CPresentBullet::AFuncState CPresentBullet::m_aFuncState[] =		// 状態更新関数リスト
{
	&CPresentBullet::UpdateHoming,		// ホーミング状態
	&CPresentBullet::UpdateMove,		// 移動状態
	&CPresentBullet::UpdateDeath,		// 死亡状態
};

//************************************************************
//	子クラス [CPresentBullet] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CPresentBullet::CPresentBullet() : CPresent(),
m_state(STATE_HOMING),	// 状態
m_destRot(VEC3_ZERO),	// 目的の向き
m_fStateTime(0.0f),		// 状態時間
m_fSpeed(0.0f)			// 速度
{
	// スタティックアサート
	static_assert(NUM_ARRAY(m_aFuncState) == CPresentBullet::STATE_MAX, "ERROR : State Count Mismatch");
}

//============================================================
//	デストラクタ
//============================================================
CPresentBullet::~CPresentBullet()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CPresentBullet::Init()
{
	m_fStateTime = 1.0f;	// 状態時間
	m_fSpeed = SPEED;		// 速度

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
void CPresentBullet::Uninit()
{
	// オブジェクトキャラクターの終了
	CPresent::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CPresentBullet::Update(const float fDeltaTime)
{
	// 状態処理
	(this->*(m_aFuncState[m_state]))(fDeltaTime);

	// 当たり判定
	Collision();
}

//============================================================
//	描画処理
//============================================================
void CPresentBullet::Draw(CShader* pShader)
{
	// オブジェクトキャラクターの描画
	CPresent::Draw(pShader);
}

//============================================================
//	更新状況の設定処理
//============================================================
void CPresentBullet::SetEnableUpdate(const bool bUpdate)
{
	// 引数の更新状況を設定
	CObject::SetEnableUpdate(bUpdate);	// 自身
}

//============================================================
//	描画状況の設定処理
//============================================================
void CPresentBullet::SetEnableDraw(const bool bDraw)
{
	// 引数の描画状況を設定
	CObject::SetEnableDraw(bDraw);	// 自身
}

//============================================================
// 半径取得
//============================================================
float CPresentBullet::GetRadius() const
{
	// 半径を返す
	return RADIUS;
}

//============================================================
// 縦幅取得
//============================================================
float CPresentBullet::GetHeight() const
{
	// 高さを返す
	return HEIGHT;
}

//============================================================
// 生成処理
//============================================================
CPresentBullet* CPresentBullet::Create
( // 引数
	const VECTOR3& rPos,	// 位置
	const float fRotY		// 方向
)
{
	// プレゼントの生成
	CPresentBullet* pPresent = new CPresentBullet;

	if (pPresent == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// プレゼントの初期化
		if (FAILED(pPresent->Init()))
		{ // 初期化に失敗した場合

			// プレゼントの破棄
			SAFE_DELETE(pPresent);
			return nullptr;
		}

		// 位置を設定
		pPresent->SetVec3Position(rPos);

		// 向きを設定
		pPresent->SetVec3Rotation(VECTOR3(0.0f, fRotY, 0.0f));

		// 確保したアドレスを返す
		return pPresent;
	}
}

//============================================================
// 当たり判定
//============================================================
void CPresentBullet::Collision()
{
	// プレイヤーがいない場合、抜ける
	CPlayer* pPlayer = CScene::GetPlayer();
	if (pPlayer == nullptr) { return; }

	// 位置を設定する
	VECTOR3 pos = GetVec3Position();
	VECTOR3 sizeMaxPlayer = VECTOR3(pPlayer->GetRadius(), pPlayer->GetHeight(), pPlayer->GetRadius());
	VECTOR3 sizeMinPlayer = VECTOR3(pPlayer->GetRadius(), 0.0f, pPlayer->GetRadius());

	if (collision::Box3D(pos, pPlayer->GetVec3Position(), sizeMaxPlayer, GetModelData().vtxMax, sizeMinPlayer, -GetModelData().vtxMin))
	{ // 当たった場合

		// ヒット処理
		pPlayer->Hit();
	}
}

//============================================================
// ホーミング処理
//============================================================
void CPresentBullet::UpdateHoming(const float fDeltaTime)
{
	// 状態時間が0未満の場合、移動状態にする
	if (m_fStateTime <= 0.0f) { m_fStateTime = 0.0f; m_state = STATE_MOVE; return; }

	// プレイヤーが NULL の場合、抜ける
	CPlayer* pPlayer = CScene::GetPlayer();
	if (pPlayer == nullptr) { return; }

	// 目的の位置を設定する
	VECTOR3 posPlayer = pPlayer->GetVec3Position();

	// 目的の向きを設定する
	D3DXVECTOR3 pos = GetVec3Position();
	D3DXVECTOR3 rot = GetVec3Rotation();
	m_destRot.y = atan2f(posPlayer.x - pos.x, posPlayer.z - pos.z);

	// 位置を移動する
	pos.x += sinf(rot.y) * m_fSpeed * fDeltaTime;
	pos.z += cosf(rot.y) * m_fSpeed * fDeltaTime;
	SetVec3Position(pos);

	// 向きの更新処理
	UpdateRotation(fDeltaTime);

	// 状態時間を減算する
	m_fStateTime -= fDeltaTime;

	// エフェクトを生成する
	CEffect3D::Create(pos, effect::RADIUS, CEffect3D::TYPE_NORMAL, effect::LIFE, VECTOR3(), VECTOR3(), color::Purple(), effect::SUB_SIZE);
}

//============================================================
// 移動処理
//============================================================
void CPresentBullet::UpdateMove(const float fDeltaTime)
{
	// 状態時間を測る
	m_fStateTime += fDeltaTime;

	// 向きの更新処理
	UpdateRotation(fDeltaTime);

	// 位置を移動する
	D3DXVECTOR3 pos = GetVec3Position();
	D3DXVECTOR3 rot = GetVec3Rotation();
	pos.x += sinf(rot.y) * m_fSpeed * fDeltaTime;
	pos.z += cosf(rot.y) * m_fSpeed * fDeltaTime;
	SetVec3Position(pos);

	if (m_fStateTime >= move::TIME)
	{ // 一定時間経過した場合

		// 状態時間をリセットする
		m_fStateTime = 0.0f;

		// 死亡状態にする
		m_state = STATE_DEATH;
	}

	// エフェクトを生成する
	CEffect3D::Create(pos, effect::RADIUS, CEffect3D::TYPE_NORMAL, effect::LIFE, VECTOR3(), VECTOR3(), color::Purple(), effect::SUB_SIZE);
}

//============================================================
// 死亡処理
//============================================================
void CPresentBullet::UpdateDeath(const float fDeltaTime)
{
	// 速度を下げていく
	m_fSpeed -= SUB_SPEED * fDeltaTime;

	// 位置を移動する
	D3DXVECTOR3 pos = GetVec3Position();
	D3DXVECTOR3 rot = GetVec3Rotation();
	pos.x += sinf(rot.y) * m_fSpeed * fDeltaTime;
	pos.z += cosf(rot.y) * m_fSpeed * fDeltaTime;
	SetVec3Position(pos);

	if (m_fSpeed > 0.0f) { return; }

	// 爆発させる
	CParticle3D::Create(CParticle3D::TYPE_SMALL_EXPLOSION, GetVec3Position());

	// 終了処理
	Uninit();
}

//============================================================
// 向きの更新処理
//============================================================
void CPresentBullet::UpdateRotation(const float fDeltaTime)
{
	VECTOR3 rot = GetVec3Rotation();
	float fDeltaRate = fDeltaTime / (1.0f / (float)main::FPS);	// 経過時間の割合
	float fDiffRot = 0.0f;	// 差分向き

	// 目標向きの正規化
	useful::NormalizeRot(m_destRot.y);

	// 目標向きまでの差分を計算
	fDiffRot = m_destRot.y - rot.y;

	// 差分向きの正規化
	useful::NormalizeRot(fDiffRot);

	// 向きの更新
	rot.y += fDiffRot * REV_ROTA * fDeltaRate;

	// 向きの正規化
	useful::NormalizeRot(rot.y);

	// 向きを反映
	SetVec3Rotation(rot);
}
