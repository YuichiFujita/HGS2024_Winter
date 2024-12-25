//============================================================
//
//	爆弾処理 [present.cpp]
//	Author：小原立暉
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "bomb.h"
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

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* MODEL = "data\\MODEL\\PLAYER\\01_body.x";	// モデル
	const int	PRIORITY = 3;	// 爆弾の優先順位
	const float	DEST_RANGE = 130.0f;	// 目的位置の範囲
	const float RADIUS = 80.0f;	// 半径
	const float FLY_HEIGHT = 90.0f;	// 飛ぶときの最高到達点
	const float FLY_TIME = 1.0f;	// 飛ぶ時間
	const float DAMAGE_TIME = 1.5f;	// ダメージ時間
}

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CListManager<CBomb>* CBomb::m_pList = nullptr;	// オブジェクトリスト

//************************************************************
// 静的メンバ変数宣言
//************************************************************
CBomb::AFuncState CBomb::m_aFuncState[] =		// 状態更新関数リスト
{
	&CBomb::UpdateFly,			// 飛び状態
	&CBomb::UpdateDamage,		// ダメージ状態
};

//************************************************************
//	子クラス [CBomb] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CBomb::CBomb() : CObjectModel(CObject::LABEL_BOMB, CObject::DIM_3D, PRIORITY),
m_state(STATE_FLY),	// 状態
m_fStateTime(0.0f),	// 飛ぶ時間
m_oldPos(VEC3_ZERO),	// 過去位置
m_originPos(VEC3_ZERO),	// 初期位置
m_destPos(VEC3_ZERO)	// 目的位置
{
	// スタティックアサート
	static_assert(NUM_ARRAY(m_aFuncState) == CBomb::STATE_MAX, "ERROR : State Count Mismatch");
}

//============================================================
//	デストラクタ
//============================================================
CBomb::~CBomb()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CBomb::Init()
{
	m_state = STATE_FLY;	// 状態
	m_fStateTime = 0.0f;	// 飛ぶ時間
	m_oldPos = VEC3_ZERO;	// 過去位置
	m_originPos = VEC3_ZERO;	// 初期位置
	m_destPos = VEC3_ZERO;	// 目的位置

	// オブジェクトキャラクターの初期化
	if (FAILED(CObjectModel::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// モデルの割り当て処理
	BindModel(MODEL);

	if (m_pList == nullptr)
	{ // リストマネージャーが存在しない場合

		// リストマネージャーの生成
		m_pList = CListManager<CBomb>::Create();
		if (m_pList == nullptr)
		{ // 生成に失敗した場合

			// 失敗を返す
			assert(false);
			return E_FAIL;
		}
	}

	// リストに自身のオブジェクトを追加・イテレーターを取得
	m_iterator = m_pList->AddList(this);

	// 成功を返す
	return S_OK;
}

//============================================================
//	終了処理
//============================================================
void CBomb::Uninit()
{
	// リストから自身のオブジェクトを削除
	m_pList->DelList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // オブジェクトが一つもない場合

		// リストマネージャーの破棄
		m_pList->Release(m_pList);
	}

	// オブジェクトキャラクターの終了
	CObjectModel::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CBomb::Update(const float fDeltaTime)
{
	// 状態処理
	(this->*(m_aFuncState[m_state]))(fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CBomb::Draw(CShader* pShader)
{
	// オブジェクトキャラクターの描画
	CObjectModel::Draw(pShader);
}

//============================================================
//	更新状況の設定処理
//============================================================
void CBomb::SetEnableUpdate(const bool bUpdate)
{
	// 引数の更新状況を設定
	CObject::SetEnableUpdate(bUpdate);	// 自身
}

//============================================================
//	描画状況の設定処理
//============================================================
void CBomb::SetEnableDraw(const bool bDraw)
{
	// 引数の描画状況を設定
	CObject::SetEnableDraw(bDraw);	// 自身
}

//============================================================
// 半径取得
//============================================================
float CBomb::GetRadius() const
{
	// 半径を返す
	return RADIUS;
}

//============================================================
//	生成処理
//============================================================
CBomb* CBomb::Create(const VECTOR3& rPos)
{
	// 爆弾の生成
	CBomb* pPresent = new CBomb;

	if (pPresent == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// 爆弾の初期化
		if (FAILED(pPresent->Init()))
		{ // 初期化に失敗した場合

			// 爆弾の破棄
			SAFE_DELETE(pPresent);
			return nullptr;
		}

		// 位置を設定
		pPresent->SetVec3Position(rPos);
		pPresent->m_originPos = rPos;

		// 目的位置設定処理
		pPresent->SetDestPos();

		// 確保したアドレスを返す
		return pPresent;
	}
}

//============================================================
//	リスト取得処理
//============================================================
CListManager<CBomb>* CBomb::GetList()
{
	// オブジェクトリストを返す
	return m_pList;
}

//============================================================
// 当たり判定
//============================================================
void CBomb::Collision()
{
	// プレイヤーがいない場合、抜ける
	CPlayer* pPlayer = CScene::GetPlayer();
	if (pPlayer == nullptr) { return; }

	// 位置を設定する
	VECTOR3 pos = GetVec3Position();

	if (collision::Circle3D(pos, pPlayer->GetVec3Position(), RADIUS, pPlayer->GetRadius()))
	{ // 当たった場合

		// ヒット処理
		pPlayer->Hit();
	}
}

//============================================================
// 目的位置の設定処理
//============================================================
void CBomb::SetDestPos()
{
	// 目的の位置を設定
	VECTOR3 pos = GetVec3Position();
	m_destPos.x = pos.x + sinf(useful::RandomRot()) * DEST_RANGE;
	m_destPos.y = 0.0f;
	m_destPos.z = pos.z + cosf(useful::RandomRot()) * DEST_RANGE;
}

//============================================================
// フィールドの当たり判定
//============================================================
void CBomb::FieldCollision()
{
	CStage* pStage = GET_MANAGER->GetStage();	// ステージ情報
	VECTOR3 pos = GetVec3Position();	// 位置
	VECTOR3 move = VEC3_ZERO;			// 引数用変数

	// 地面・制限位置着地判定
	if (pStage->LandFieldPosition(pos, m_oldPos, move)
		|| pStage->LandLimitPosition(pos, move, 0.0f))
	{ // プレイヤーが着地していた場合

		// 位置を反映
		SetVec3Position(pos);
	}
}

//============================================================
// 飛行処理
//============================================================
void CBomb::UpdateFly(const float fDeltaTime)
{
	D3DXVECTOR3 pos = GetVec3Position();	// 現在の位置
	D3DXVECTOR3 posOld = GetVec3Position();	// 保存用の位置

	// 放物線処理
	pos = useful::GetParabola3D(m_originPos, m_destPos, m_destPos.y + FLY_HEIGHT, FLY_TIME, m_fStateTime);

	if (pos.y < posOld.y)
	{ // 下がり始めたとき

		// 爆発のパーティクルを出す
		CParticle3D::Create(CParticle3D::TYPE_SMALL_EXPLOSION, pos);

		// 状態時間をリセットする
		m_fStateTime = 0.0f;

		// ダメージ状態にする
		m_state = STATE_DAMAGE;
	}

	// 飛んでいる時間を更新
	m_fStateTime += fDeltaTime;

	// 位置を反映する
	SetVec3Position(pos);

	// 地面との当たり判定
	FieldCollision();
}

//============================================================
// ダメージ処理
//============================================================
void CBomb::UpdateDamage(const float fDeltaTime)
{
	// 当たり判定
	Collision();

	// 状態時間を加算する
	m_fStateTime += fDeltaTime;

	if (m_fStateTime >= DAMAGE_TIME)
	{ // 一定時間経過した場合

		// 終了処理
		Uninit();

		return;
	}
}
