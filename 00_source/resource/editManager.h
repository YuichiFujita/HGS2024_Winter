//============================================================
//
//	エディットマネージャーヘッダー [editManager.h]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _EDIT_MANAGER_H_
#define _EDIT_MANAGER_H_

//************************************************************
//	前方宣言
//************************************************************
class CActor;	// アクタークラス

//************************************************************
//	クラス定義
//************************************************************
// エディットマネージャークラス
class CEditManager
{
public:
	// コンストラクタ
	CEditManager();

	// デストラクタ
	~CEditManager();

	// メンバ関数
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update(const float fDeltaTime);	// 更新

	// 静的メンバ関数
	static CEditManager* Create();	// 生成
	static void Release(CEditManager*& prEditManager);	// 破棄

private:
	// メンバ関数
	void UpdatePosition(const float fDeltaTime);	// 位置の更新
	void UpdateRotation(const float fDeltaTime);	// 向きの更新
	void UpdateScale(const float fDeltaTime);		// 拡大率の更新
	void UpdateType();		// 種類の更新
	void CreateActor();		// アクターの生成
	void ReleaseActor();	// アクターの破棄
	void SaveActor();		// アクターの保存

	// メンバ変数
	CActor* m_pCreateActor;	// 生成アクター情報
};

#endif	// _EDIT_MANAGER_H_
