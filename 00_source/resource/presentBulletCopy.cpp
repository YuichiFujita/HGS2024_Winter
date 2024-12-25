//============================================================
//
//	弾型プレゼント処理 [presentBullet.cpp]
//	Author：小原立暉
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "presentBulletCopy.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "fade.h"
#include "stage.h"
#include "sceneGame.h"
#include "gameManager.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	const float	GRAVITY = 3600.0f;	// 重力
	const float	RADIUS = 20.0f;	// 半径
	const float HEIGHT = 80.0f;	// 身長
}

//************************************************************
//	子クラス [CPresentBullet] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CPresentBullet::CPresentBullet() : CPresent()
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
