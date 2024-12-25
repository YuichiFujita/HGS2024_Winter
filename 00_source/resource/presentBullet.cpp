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

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* MODEL = "data\\MODEL\\PLAYER\\01_body.x";	// モデル
	const float SPEED = 500.0f;	// 速度
	const float	RADIUS = 20.0f;	// 半径
	const float HEIGHT = 80.0f;	// 身長
	const float	REV_ROTA = 0.04f;	// 向き変更の補正係数
}

//************************************************************
//	子クラス [CPresentBullet] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CPresentBullet::CPresentBullet() : CPresent(),
m_destPos(VEC3_ZERO),	// 目的の位置
m_fHomingTime(0.0f)	// ホーミングする時間
{

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
	m_fHomingTime = 1.0f;	// ホーミングする時間

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
	// ホーミング処理
	Homing(fDeltaTime);

	// 向きの更新処理
	UpdateRotation(fDeltaTime);
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
// ホーミング処理
//============================================================
void CPresentBullet::Homing(const float fDeltaTime)
{
	// ホーミングタイムが0未満の場合、抜ける
	if (m_fHomingTime < 0.0f) { return; }

	// プレイヤーが NULL の場合、抜ける
	CPlayer* pPlayer = CScene::GetPlayer();
	if (pPlayer == nullptr) { return; }

	// 目的の位置を設定する
	m_destPos = pPlayer->GetVec3Position();

	// 目的の向きを設定する
	D3DXVECTOR3 pos = GetVec3Position();
	D3DXVECTOR3 rot = GetVec3Rotation();
	m_destRot.y = atan2f(m_destPos.x - pos.x, m_destPos.z - pos.z);

	// 位置を移動する
	pos.x += sinf(rot.y) * SPEED * fDeltaTime;
	pos.z += cosf(rot.y) * SPEED * fDeltaTime;
	SetVec3Position(pos);
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
