//============================================================
//
//	アクター処理 [actor.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "actor.h"

//************************************************************
//	定数宣言
//************************************************************
namespace
{
	// モデル情報構造体
	struct SModelInfo
	{
		// デフォルトコンストラクタ
		SModelInfo() :
			pFilePath	(nullptr),	// ファイルパス
			fRadius		(0.0f)		// 判定半径
		{}

		// 引数付きコンストラクタ
		SModelInfo(const char* in_pFilePath, const float in_fRadius) :
			pFilePath	(in_pFilePath),	// ファイルパス
			fRadius		(in_fRadius)	// 判定半径
		{}

		// デストラクタ
		~SModelInfo() {}

		// メンバ変数
		const char* pFilePath;	// ファイルパス
		float fRadius;			// 判定半径
	};
	const SModelInfo MODEL_FILE[] =	// サウンドファイル
	{
		SModelInfo("data\\MODEL\\ACTOR\\wood000.x", 30.0f),		// 木00
		SModelInfo("data\\MODEL\\ACTOR\\stone000.x", 30.0f),	// 石00
	};

	const int PRIORITY = 3;	// アクターの優先順位
}

//************************************************************
//	静的メンバ変数宣言
//************************************************************
CListManager<CActor>* CActor::m_pList = nullptr;	// オブジェクトリスト

//************************************************************
//	子クラス [CActor] のメンバ関数
//************************************************************
//============================================================
//	コンストラクタ
//============================================================
CActor::CActor() : CObjectModel(CObject::LABEL_ACTOR, CObject::DIM_3D, PRIORITY),
	m_type	(TYPE_WOOD)	// 種類
{

}

//============================================================
//	デストラクタ
//============================================================
CActor::~CActor()
{

}

//============================================================
//	初期化処理
//============================================================
HRESULT CActor::Init()
{
	// メンバ変数を初期化
	m_type = TYPE_WOOD;	// 種類

	// オブジェクトキャラクターの初期化
	if (FAILED(CObjectModel::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		assert(false);
		return E_FAIL;
	}

	if (m_pList == nullptr)
	{ // リストマネージャーが存在しない場合

		// リストマネージャーの生成
		m_pList = CListManager<CActor>::Create();
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
void CActor::Uninit()
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
void CActor::Update(const float fDeltaTime)
{

}

//============================================================
//	描画処理
//============================================================
void CActor::Draw(CShader* pShader)
{
	// オブジェクトキャラクターの描画
	CObjectModel::Draw(pShader);
}

//============================================================
//	生成処理
//============================================================
CActor* CActor::Create
(
	const EType type,		// 種類
	const VECTOR3& rPos,	// 位置
	const VECTOR3& rRot,	// 向き
	const VECTOR3& rScale	// 拡大率
)
{
	// アクターの生成
	CActor* pActor = new CActor;
	if (pActor == nullptr)
	{ // 生成に失敗した場合

		return nullptr;
	}
	else
	{ // 生成に成功した場合

		// アクターの初期化
		if (FAILED(pActor->Init()))
		{ // 初期化に失敗した場合

			// アクターの破棄
			SAFE_DELETE(pActor);
			return nullptr;
		}

		// 種類を設定
		pActor->SetType(type);

		// 位置を設定
		pActor->SetVec3Position(rPos);

		// 向きを設定
		pActor->SetVec3Rotation(rRot);

		// 拡大率を設定
		pActor->SetVec3Scale(rScale);

		// 確保したアドレスを返す
		return pActor;
	}
}

//============================================================
//	リスト取得処理
//============================================================
CListManager<CActor>* CActor::GetList()
{
	// オブジェクトリストを返す
	return m_pList;
}

//============================================================
//	種類の設定処理
//============================================================
void CActor::SetType(const EType type)
{
	// 種類を保存
	m_type = type;

	// モデルの割当
	BindModel(MODEL_FILE[m_type].pFilePath);
}

//============================================================
//	半径の取得処理
//============================================================
float CActor::GetRadius() const
{
	// 半径を返す
	return MODEL_FILE[m_type].fRadius;
}
