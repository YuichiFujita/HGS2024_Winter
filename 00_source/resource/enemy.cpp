//============================================================
//
//	敵処理 [enemy.cpp]
//	Author：小原立暉
//	Adder ：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "enemy.h"
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
#include "presentLand.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const char* SETUP_TXT = "data\\CHARACTER\\santa_black.txt";	// セットアップテキスト相対パス
	const int	PRIORITY = 3;		// プレイヤーの優先順位
	const float	GRAVITY = 3600.0f;	// 重力
	const float	RADIUS = 20.0f;	// 半径
	const float HEIGHT = 80.0f;	// 身長
	const float	REV_ROTA = 9.0f;	// 向き変更の補正係数
	const float	JUMP_REV = 0.16f;	// 通常状態時の空中の移動量の減衰係数
	const float	LAND_REV = 0.16f;	// 通常状態時の地上の移動量の減衰係数
	const float	JUMP_HEIGHT = 1000.0f;	// ジャンプの最高到達点
	const float	JUMP_TIME = 0.65f;		// ジャンプ時間
	const float	CHANGE_ATK = 700.0f;	// 攻撃変更距離

	const float LAND_NUM_TIME = 50.0f;		// 設置型プレゼントが増える基準
	const int LAND_NUM_MAX = 3;				// 設置型プレゼントの最大数
	const float LAND_NUM_RANGE = 50.0f;		// 設置型プレゼントの範囲の

	namespace motion
	{
		const int BLEND_FRAME_OTHER = 5;	// モーションの基本的なブレンドフレーム
	}
}

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CListManager<CEnemy>* CEnemy::m_pList = nullptr;	// オブジェクトリスト
CEnemy::AFuncState CEnemy::m_aFuncState[] =			// 状態更新関数リスト
{
	&CEnemy::UpdateIdol,	// 待機状態の更新
	&CEnemy::UpdateJump,	// ジャンプ状態の更新
	&CEnemy::UpdateAttack,	// 攻撃状態の更新
};

//************************************************************
//	子クラス [CEnemy] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CEnemy::CEnemy() : CObjectChara(CObject::LABEL_ENEMY, CObject::DIM_3D, PRIORITY),
m_state(STATE_IDOL),		// 状態
m_oldPos(VEC3_ZERO),		// 過去位置
m_jumpPosStart(VEC3_ZERO),	// ジャンプ開始位置
m_jumpPosEnd(VEC3_ZERO),	// ジャンプ終了位置
m_move(VEC3_ZERO),			// 移動量
m_destRot(VEC3_ZERO),		// 目標向き
m_bJump(false),				// ジャンプ状況
m_fStateTime(0.0f)			// 状態管理時間
{
	// スタティックアサート
	static_assert(NUM_ARRAY(m_aFuncState) == CEnemy::STATE_MAX, "ERROR : State Count Mismatch");
}

//============================================================
//	デストラクタ
//============================================================
CEnemy::~CEnemy()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CEnemy::Init()
{
	// メンバ変数を初期化
	m_state = STATE_IDOL;		// 状態
	m_oldPos = VEC3_ZERO;		// 過去位置
	m_jumpPosStart = VEC3_ZERO;	// ジャンプ開始位置
	m_jumpPosEnd = VEC3_ZERO;	// ジャンプ終了位置
	m_move = VEC3_ZERO;			// 移動量
	m_destRot = VEC3_ZERO;		// 目標向き
	m_bJump = true;				// ジャンプ状況
	m_fStateTime = 0.0f;		// 状態管理時間

	// オブジェクトキャラクターの初期化
	if (FAILED(CObjectChara::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	// キャラクター情報の割当
	BindCharaData(SETUP_TXT);

	// 初期モーションの割当
	SetMotion(MOTION_IDOL);

	if (m_pList == nullptr)
	{ // リストマネージャーが存在しない場合

		// リストマネージャーの生成
		m_pList = CListManager<CEnemy>::Create();
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
void CEnemy::Uninit()
{
	// リストから自身のオブジェクトを削除
	m_pList->DelList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // オブジェクトが一つもない場合

		// リストマネージャーの破棄
		m_pList->Release(m_pList);
	}

	// オブジェクトキャラクターの終了
	CObjectChara::Uninit();
}

//============================================================
//	更新処理
//============================================================
void CEnemy::Update(const float fDeltaTime)
{
	// 過去位置の更新
	UpdateOldPosition();

	// 状態の更新
	EMotion curMotion = (this->*(m_aFuncState[m_state]))(fDeltaTime);

	// モーション・オブジェクトキャラクターの更新
	UpdateMotion(curMotion, fDeltaTime);
}

//============================================================
//	描画処理
//============================================================
void CEnemy::Draw(CShader* pShader)
{
	// オブジェクトキャラクターの描画
	CObjectChara::Draw(pShader);
}

//============================================================
//	更新状況の設定処理
//============================================================
void CEnemy::SetEnableUpdate(const bool bUpdate)
{
	// 引数の更新状況を設定
	CObject::SetEnableUpdate(bUpdate);	// 自身
}

//============================================================
//	描画状況の設定処理
//============================================================
void CEnemy::SetEnableDraw(const bool bDraw)
{
	// 引数の描画状況を設定
	CObject::SetEnableDraw(bDraw);	// 自身
}

//============================================================
//	生成処理
//============================================================
CEnemy* CEnemy::Create
(
	const VECTOR3& rPos,	// 位置
	const VECTOR3& rRot		// 向き
)
{
	// プレイヤーの生成
	CEnemy* pEnemy = new CEnemy;
	if (pEnemy == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// プレイヤーの初期化
		if (FAILED(pEnemy->Init()))
		{ // 初期化に失敗した場合

			// プレイヤーの破棄
			SAFE_DELETE(pEnemy);
			return nullptr;
		}

		// 位置を設定
		pEnemy->SetVec3Position(rPos);
		pEnemy->m_oldPos = rPos;	// 過去位置も同一の位置にする

		// 向きを設定
		pEnemy->SetVec3Rotation(rRot);
		pEnemy->m_destRot = rRot;	// 目標向きも同一の向きにする

		// 確保したアドレスを返す
		return pEnemy;
	}
}

//============================================================
//	リスト取得処理
//============================================================
CListManager<CEnemy>* CEnemy::GetList()
{
	// オブジェクトリストを返す
	return m_pList;
}

//============================================================
//	半径取得処理
//============================================================
float CEnemy::GetRadius() const
{
	// 半径を返す
	return RADIUS;
}

//============================================================
//	縦幅取得処理
//============================================================
float CEnemy::GetHeight() const
{
	// 縦幅を返す
	return HEIGHT;
}

//============================================================
//	待機時間の計算処理
//============================================================
float CEnemy::CalcIdolTime()
{
	float fCurGameTime = CSceneGame::GetGameManager()->GetGameTime();	// 現在の経過時間

	// 経過時間から待機時間を早くする
	float fRate = easing::InCubic(fCurGameTime, 0.0f, 10.0f);

	// 
	return useful::RateToValue(fRate, 2.0f, 0.5f);
}

//============================================================
//	攻撃モーションフラグ取得処理
//============================================================
bool CEnemy::IsAttack()
{
	// 攻撃モーション中かを返す
	return (MOTION_ATK_UP || MOTION_ATK_SIDE);
}

//============================================================
//	状態の設定処理
//============================================================
void CEnemy::SetState(const EState state)
{
	// 引数状態の設定
	m_state = state;

	// タイマーの初期化
	m_fStateTime = 0.0f;
}

//============================================================
//	ジャンプの設定処理
//============================================================
void CEnemy::SetJump(const VECTOR3& rCurPos, const VECTOR3& rJumpPos)
{
	// ジャンプ開始/終了位置を保存
	m_jumpPosStart = rCurPos;
	m_jumpPosEnd = rJumpPos;

	// ジャンプ状態にする
	SetState(STATE_JUMP);
}

//============================================================
//	攻撃の設定処理
//============================================================
void CEnemy::SetAttack(const VECTOR3& rCurPos, const VECTOR3& rPlayerPos)
{
	// 二点間の距離を計算
	float fDisPlayer = sqrtf((rCurPos.x - rPlayerPos.x) * (rCurPos.x - rPlayerPos.x)
						   + (rCurPos.z - rPlayerPos.z) * (rCurPos.z - rPlayerPos.z));

	if (fDisPlayer > CHANGE_ATK)
	{ // 遠い場合

		// 上投げの音
		PLAY_SOUND(CSound::LABEL_SE_THROW_TOP);

		// 上投げモーションにする
		SetMotion(MOTION_ATK_UP);
	}
	else
	{ // 近い場合

		// 横投げの音
		PLAY_SOUND(CSound::LABEL_SE_THROW_SIDE);
		
		// 横投げモーションにする
		SetMotion(MOTION_ATK_SIDE);
	}

	// 攻撃状態にする
	SetState(STATE_ATK);
}

//============================================================
//	待機状態時の更新処理
//============================================================
CEnemy::EMotion CEnemy::UpdateIdol(const float fDeltaTime)
{
	CPlayer* pPlayer = CScene::GetPlayer();			// プレイヤー情報
	VECTOR3 posPlayer = pPlayer->GetVec3Position();	// プレイヤー位置
	VECTOR3 posEnemy = GetVec3Position();	// 敵位置
	VECTOR3 rotEnemy = GetVec3Rotation();	// 敵向き

	// 重力の更新
	UpdateGravity(fDeltaTime);

	// 位置更新
	UpdatePosition(&posEnemy, fDeltaTime);

	// 着地判定
	UpdateLanding(&posEnemy, fDeltaTime);

	// 位置補正
	CStage* pStage = GET_MANAGER->GetStage();	// ステージ情報
	pStage->LimitPosition(posEnemy, RADIUS);

	// 目標向きを設定
	m_destRot.y = atan2f(posEnemy.x - posPlayer.x, posEnemy.z - posPlayer.z);

	// 向き更新
	UpdateRotation(&rotEnemy, fDeltaTime);

	// 経過時間を加算
	m_fStateTime += fDeltaTime;
	if (m_fStateTime >= CalcIdolTime())
	{ // 時間が経過しきった場合

		// ジャンプ状態にする
		SetJump(posEnemy, GET_MANAGER->GetStage()->GetRandomPositionInLimit(RADIUS));
	}

	// 位置を反映
	SetVec3Position(posEnemy);

	// 向きを反映
	SetVec3Rotation(rotEnemy);

	// 現在のモーションを返す
	return MOTION_IDOL;
}

//============================================================
//	ジャンプ状態時の更新処理
//============================================================
CEnemy::EMotion CEnemy::UpdateJump(const float fDeltaTime)
{
	VECTOR3 posEnemy = GetVec3Position();	// 敵位置
	VECTOR3 rotEnemy = GetVec3Rotation();	// 敵向き

	// 経過時間を加算
	m_fStateTime += fDeltaTime;

	// ジャンプさせる
	posEnemy = useful::GetParabola3D(m_jumpPosStart, m_jumpPosEnd, JUMP_HEIGHT, JUMP_TIME, m_fStateTime);
	if (m_fStateTime >= JUMP_TIME)
	{ // 時間が経過しきった場合

		// 攻撃状態にする
		CPlayer* pPlayer = CScene::GetPlayer();	// プレイヤー情報
		SetAttack(posEnemy, pPlayer->GetVec3Position());
	}

	// 位置補正
	CStage* pStage = GET_MANAGER->GetStage();	// ステージ情報
	pStage->LimitPosition(posEnemy, RADIUS);

	// 目標向きを設定
	m_destRot.y = atan2f(m_jumpPosStart.x - m_jumpPosEnd.x, m_jumpPosStart.z - m_jumpPosEnd.z);

	// 向き更新
	UpdateRotation(&rotEnemy, fDeltaTime);

	// 位置を反映
	SetVec3Position(posEnemy);

	// 向きを反映
	SetVec3Rotation(rotEnemy);

	// 現在のモーションを返す
	return MOTION_IDOL;
}

//============================================================
//	攻撃状態時の更新処理
//============================================================
CEnemy::EMotion CEnemy::UpdateAttack(const float fDeltaTime)
{
	CPlayer* pPlayer = CScene::GetPlayer();			// プレイヤー情報
	VECTOR3 posPlayer = pPlayer->GetVec3Position();	// プレイヤー位置
	VECTOR3 posEnemy = GetVec3Position();	// 敵位置
	VECTOR3 rotEnemy = GetVec3Rotation();	// 敵向き

	// 攻撃モーションじゃない場合エラー
	assert(IsAttack());

	// 攻撃させる
	if (GetMotionComboFrame() == GetMotionWholeCounter())
	{ // コンボフレームの瞬間の場合

		switch (GetMotionType())
		{ // モーション種類ごとの処理
		case MOTION_ATK_UP:

			// 設置型プレゼント処理
			LandAttack(fDeltaTime);
			break;

		case MOTION_ATK_SIDE:

			// 弾型プレゼントを飛ばす
			CPresentLand::Create(GetVec3Position(), VEC3_ZERO, CPresent::TYPE_BULLET);
			break;
		};
	}

	// 重力の更新
	UpdateGravity(fDeltaTime);

	// 位置更新
	UpdatePosition(&posEnemy, fDeltaTime);

	// 着地判定
	UpdateLanding(&posEnemy, fDeltaTime);

	// 位置補正
	CStage* pStage = GET_MANAGER->GetStage();	// ステージ情報
	pStage->LimitPosition(posEnemy, RADIUS);

	// 目標向きを設定
	m_destRot.y = atan2f(posEnemy.x - posPlayer.x, posEnemy.z - posPlayer.z);

	// 向き更新
	UpdateRotation(&rotEnemy, fDeltaTime);

	// 位置を反映
	SetVec3Position(posEnemy);

	// 向きを反映
	SetVec3Rotation(rotEnemy);

	// 現在のモーションを返す
	return MOTION_IDOL;
}

//============================================================
// 設置型プレゼント処理
//============================================================
void CEnemy::LandAttack(const float fDeltaTime)
{
	int nNum = (int)(CSceneGame::GetGameManager()->GetGameTime() / LAND_NUM_TIME);	// 現在の経過時間

	// 最大数を3に抑える
	useful::LimitMaxNum(nNum, LAND_NUM_MAX);

	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		// 設置型プレゼントを飛ばす
		CPresentLand::Create(GetVec3Position(), VEC3_ZERO, 30.0f * nCnt);
	}
}

//============================================================
//	過去位置の更新処理
//============================================================
void CEnemy::UpdateOldPosition()
{
	// 過去位置を更新
	m_oldPos = GetVec3Position();
}

//============================================================
//	重力の更新処理
//============================================================
void CEnemy::UpdateGravity(const float fDeltaTime)
{
	// 重力を加算
	m_move.y -= GRAVITY * fDeltaTime;
}

//============================================================
//	着地状況の更新処理
//============================================================
bool CEnemy::UpdateLanding(VECTOR3* pPos, const float fDeltaTime)
{
	CStage* pStage = GET_MANAGER->GetStage();	// ステージ情報
	bool bLand = false;	// 着地フラグ

	// 地面・制限位置着地判定
	if (pStage->LandFieldPosition(*pPos, m_oldPos, m_move)
		|| pStage->LandLimitPosition(*pPos, m_move, 0.0f))
	{ // プレイヤーが着地していた場合

		// 着地している状態にする
		bLand = true;

		// ジャンプしていない状態にする
		m_bJump = false;
	}

	// 着地フラグを返す
	return bLand;
}

//============================================================
//	位置の更新処理
//============================================================
void CEnemy::UpdatePosition(VECTOR3* pPos, const float fDeltaTime)
{
	// 移動量を加算
	*pPos += m_move * fDeltaTime;

	// 移動量を減衰
	if (m_bJump)
	{ // 空中の場合

		m_move.x += (0.0f - m_move.x) * JUMP_REV;
		m_move.z += (0.0f - m_move.z) * JUMP_REV;
	}
	else
	{ // 地上の場合

		m_move.x += (0.0f - m_move.x) * LAND_REV;
		m_move.z += (0.0f - m_move.z) * LAND_REV;
	}
}

//============================================================
//	向きの更新処理
//============================================================
void CEnemy::UpdateRotation(VECTOR3* pRot, const float fDeltaTime)
{
	// 変数を宣言
	float fDiffRot = 0.0f;	// 差分向き

	// 目標向きの正規化
	useful::NormalizeRot(m_destRot.y);

	// 目標向きまでの差分を計算
	fDiffRot = m_destRot.y - pRot->y;

	// 差分向きの正規化
	useful::NormalizeRot(fDiffRot);

	// 向きの更新
	pRot->y += fDiffRot * fDeltaTime * REV_ROTA;

	// 向きの正規化
	useful::NormalizeRot(pRot->y);
}

//============================================================
//	モーション/キャラクターの更新処理
//============================================================
void CEnemy::UpdateMotion(int nMotion, const float fDeltaTime)
{
	// 死んでたら抜ける
	if (IsDeath()) { return; }

	int nAnimMotion = GetMotionType();	// 現在再生中のモーション
	if (nMotion != NONE_IDX)
	{ // モーションが設定されている場合

		if (IsMotionLoop())
		{ // ループするモーション中の場合

			if (nAnimMotion != nMotion)
			{ // 現在のモーションが再生中のモーションと一致しない場合

				// 現在のモーションの設定
				SetMotion(nMotion, motion::BLEND_FRAME_OTHER);
			}
		}
		else
		{ // ループしないモーション中の場合

#if 0
			switch (GetMotionType())
			{ // モーションごとの処理
			case MOTION_:

				if (nMotion != MOTION_IDOL)
				{ // 待機モーション以外の場合

					// 現在のモーションの設定
					SetMotion(nMotion, motion::BLEND_FRAME_OTHER);
				}
				break;
			}
#endif
		}
	}

	// オブジェクトキャラクターの更新
	CObjectChara::Update(fDeltaTime);

	switch (GetMotionType())
	{ // モーションの種類ごとの処理
	case MOTION_IDOL:
		break;

	case MOTION_ATK_UP:
	case MOTION_ATK_SIDE:

		if (IsMotionFinish())
		{ // モーションが終了した場合

			// 待機状態にする
			SetMotion(MOTION_IDOL, motion::BLEND_FRAME_OTHER);
			SetState(STATE_IDOL);
		}
		break;
	}
}
