//============================================================
//
//	アクターヘッダー [actor.h]
//	Author：藤田勇一
// 
//============================================================
//************************************************************
//	二重インクルード防止
//************************************************************
#ifndef _ACTOR_H_
#define _ACTOR_H_

//************************************************************
//	インクルードファイル
//************************************************************
#include "objectModel.h"

//************************************************************
//	クラス定義
//************************************************************
// アクタークラス
class CActor : public CObjectModel
{
public:
	// 種類列挙
	enum EType
	{
		TYPE_WOOD = 0,	// 木
		TYPE_STONE,		// 石
		TYPE_MAX		// この列挙型の総数
	};

	// コンストラクタ
	CActor();

	// デストラクタ
	~CActor() override;

	// オーバーライド関数
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update(const float fDeltaTime) override;	// 更新
	void Draw(CShader* pShader = nullptr) override;	// 描画

	// 静的メンバ関数
	static CActor* Create	// 生成
	( // 引数
		const EType type,		// 種類
		const VECTOR3& rPos,	// 位置
		const VECTOR3& rRot,	// 向き
		const VECTOR3& rScale	// 拡大率
	);
	static CListManager<CActor>* GetList();	// リスト取得

	// メンバ関数
	void SetType(const EType type);	// 種類設定
	float GetRadius() const;		// 半径取得
	inline EType GetType() const	{ return m_type; }	// 種類取得

private:
	// 静的メンバ変数
	static CListManager<CActor>* m_pList;	// オブジェクトリスト

	// メンバ変数
	CListManager<CActor>::AIterator m_iterator;	// イテレーター
	EType m_type;	// 種類
};

#endif	// _ACTOR_H_
