//============================================================
//
//	便利関数処理 [useful.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "useful.h"
#include "manager.h"
#include "texture.h"
#include <regex>

//************************************************************
//	通常関数
//************************************************************
//	便利関数空間
//************************************************************
//============================================================
//	数値の桁数ごとの分解
//============================================================
//	スコア表示の際などに使用
//============================================================
void useful::DivideDigitNum
(
	int* pNumDivide,	// 分解結果の格納配列
	const int nNum,		// 分解する数値
	const int nMaxDigit	// 分解する数字の桁数
)
{
	int nDigit = 1;	// 各桁の数値の計算用
	for (int nCntDigit = 0; nCntDigit < nMaxDigit; nCntDigit++)
	{ // 桁の最大数分繰り返す

		// 桁数分乗算する
		nDigit *= 10;
	}

	for (int nCntTex = nMaxDigit - 1; nCntTex >= 0; nCntTex--, pNumDivide++)
	{ // 桁数の最大から桁数の最小まで繰り返す

		// 桁数ごとの数値を求める
		*pNumDivide = (nNum % nDigit) / (nDigit / 10);

		// 除算して次の桁数に合わせる
		nDigit /= 10;
	}
}

//============================================================
//	法線の正規化
//============================================================
void useful::NormalizeNormal
(
	const VECTOR3& rPosLeft,	// 左位置
	const VECTOR3& rPosCenter,	// 中心位置
	const VECTOR3& rPosRight,	// 右位置
	VECTOR3& rNor				// 法線
)
{
	VECTOR3 vecLine[2];	// 辺ベクトル

	// 辺ベクトルを求める
	vecLine[0] = rPosLeft - rPosCenter;
	vecLine[1] = rPosRight - rPosCenter;

	// 法線を計算
	rNor.x = (vecLine[0].y * vecLine[1].z) - (vecLine[0].z * vecLine[1].y);
	rNor.y = (vecLine[0].z * vecLine[1].x) - (vecLine[0].x * vecLine[1].z);
	rNor.z = (vecLine[0].x * vecLine[1].y) - (vecLine[0].y * vecLine[1].x);

	// 法線を正規化
	D3DXVec3Normalize(&rNor, &rNor);
}

//============================================================
//	文字列内の連続文字の置換
//============================================================
void useful::ReplaceConsecChar
(
	std::string* pDestStr,		// 置き換えを行う文字列
	const char cRepChar,		// 検出する文字
	const std::string& rRepStr,	// 置き換える文字列
	const int nRepStrLength		// 置き換える文字列の長さ (通常はstringのsize)

)
{
	int nStartIdx = 0;	// 文字検出の開始インデックス
	while (1)
	{ // 区切り文字が見つかった場合

		// 文字列内から引数の文字を検出
		int nFindIdx = pDestStr->find(cRepChar, nStartIdx);	// 検出インデックス

		// 引数の文字が検出されなかった場合ループを抜ける
		if ((size_t)nFindIdx == std::string::npos) { break; }

		// 置き換えの先頭まで文字列を削除する
		std::string sFindStr = *pDestStr;	// 置き換え文字列を代入
		sFindStr.erase(0, nFindIdx);		// 検出インデックスまで文字列削除

		int nCntConsec = 0;	// 文字連続カウンター
		for (char cChar : sFindStr)
		{ // 文字列の長さ分繰り返す

			if (cChar != cRepChar)
			{ // 検出文字と別の文字になった場合

				// 連続文字をすべて削除し、置き換え文字列を代入
				pDestStr->replace(nFindIdx, nCntConsec, rRepStr);

				// 文字検出の開始インデックスを設定
				nStartIdx = nFindIdx + nRepStrLength;

				break;
			}

			// 文字連続数を加算
			nCntConsec++;
		}
	}
}

//============================================================
//	経過時間・X移動量・重力から放物線の位置を求める処理
//============================================================
VECTOR2 useful::CalcPosParabola
(
	const float fGravity,	// 重力
	const float fMoveX,		// X移動量
	const float fDestPosX,	// 最大X座標
	const float fDestPosY,	// 最大Y座標
	const float fTime,		// 経過時間
	float* pMaxTime,		// 最大経過時間
	float* pMaxPosY			// 最大到達Y座標
)
{
	const float fMaxTime	= fDestPosX / fMoveX;	// 最大経過時間
	const float fHalfTime	= fMaxTime * 0.5f;		// 半分の最大経過時間
	const float fMoveY		= -0.5f * fGravity * fMaxTime;	// Y移動量
	const float fMaxPosY	= 0.5f * fGravity * (fHalfTime * fHalfTime) + fMoveY * fHalfTime;	// 最大到達Y座標

	if (pMaxTime != nullptr)
	{
		// 最大経過時間を保存
		*pMaxTime = fMaxTime;
	}
	if (pMaxPosY != nullptr)
	{
		// 最大到達Y座標を保存
		*pMaxPosY = fMaxPosY;
	}

	// 現在時間の位置を求める
	VECTOR2 posTime = VEC2_ZERO;
	posTime.x = fMoveX * fTime;
	posTime.y = (0.5f * fGravity * (fTime * fTime) + fMoveY * fTime) * (fDestPosY / fMaxPosY);

	// 現在時間の位置を返す
	return posTime;
}

//============================================================
//	経過時間・X移動量・重力から放物線の移動量を求める処理
//============================================================
VECTOR2 useful::CalcMoveParabola
(
	const float fGravity,	// 重力
	const float fMoveX,		// X移動量
	const float fDestPosX,	// 最大X座標
	const float fDestPosY,	// 最大Y座標
	const float fTime,		// 経過時間
	float* pMaxTime,		// 最大経過時間
	float* pMaxPosY			// 最大到達Y座標
)
{
	const float fMaxTime	= fDestPosX / fMoveX;	// 最大経過時間
	const float fHalfTime	= fMaxTime * 0.5f;		// 半分の最大経過時間
	const float fMoveY		= -0.5f * fGravity * fMaxTime;	// Y移動量
	const float fMaxPosY	= 0.5f * fGravity * (fHalfTime * fHalfTime) + fMoveY * fHalfTime;	// 最大到達Y座標

	if (pMaxTime != nullptr)
	{
		// 最大経過時間を保存
		*pMaxTime = fMaxTime;
	}
	if (pMaxPosY != nullptr)
	{
		// 最大到達Y座標を保存
		*pMaxPosY = fMaxPosY;
	}

	// 現在時間の移動量を求める
	VECTOR2 moveTime = VEC2_ZERO;
	moveTime.x = fMoveX;
	moveTime.y = (fGravity * fTime + fMoveY) * (fDestPosY / fMaxPosY);

	// 現在時間の移動量を返す
	return moveTime;
}

//============================================================
//	放物線の計算処理
//============================================================
VECTOR3 useful::GetParabola3D
(
	const VECTOR3& rPosStart,	// 射出位置
	const VECTOR3& rPosEnd,		// 着弾位置
	const float fMaxHeight,		// 最高到達高さ
	const float fEndTime,		// 終了時間
	const float fCurTime		// 現在時間
)
{
	VECTOR3 pos;	// 位置

	// 経過時間の割合を計算
	float fTimeRate = fCurTime / fEndTime;
	fTimeRate = useful::LimitNum(fTimeRate, 0.0f, 1.0f);	// 割合を補正

	// XZ平面を計算
	pos.x = rPosStart.x + (rPosEnd.x - rPosStart.x) * fTimeRate;
	pos.z = rPosStart.z + (rPosEnd.z - rPosStart.z) * fTimeRate;

	// 高さを計算
	pos.y = rPosStart.y + (rPosEnd.y - rPosStart.y) * fTimeRate + sinf(D3DX_PI * fTimeRate) * fMaxHeight;

	// 位置を返す
	return pos;
}

//============================================================
//	向きの正規化
//============================================================
void useful::NormalizeRot(float& rRot)
{
	if (rRot > D3DX_PI)
	{ // 向きが 3.14 を超えた場合

		// 向きの正規化
		rRot -= D3DX_PI * 2.0f;
	}
	else if (rRot < -D3DX_PI)
	{ // 向きが -3.14 を超えた場合

		// 向きの正規化
		rRot += D3DX_PI * 2.0f;
	}
}

//============================================================
//	三軸向きの正規化
//============================================================
void useful::NormalizeRot(VECTOR3& rRot)
{
	// 全ての向きを正規化
	NormalizeRot(rRot.x);
	NormalizeRot(rRot.y);
	NormalizeRot(rRot.z);
}

//============================================================
//	パスのベースネーム変換
//============================================================
void useful::PathToBaseName(std::string* pPath)
{
	std::filesystem::path fsPath(*pPath);	// パス

	// パスからベースネームを取得
	*pPath = fsPath.stem().string();
}

//============================================================
//	パス区切りの標準化
//============================================================
void useful::StandardizePathPart(std::string* pPath)
{
	// スラッシュを置換
	ReplaceConsecChar
	( // 引数
		pPath,	// 置き換えを行う文字列
		'/',	// 検出する文字
		"\\",	// 置き換える文字列
		1		// 置き換える文字列の長さ (通常文字と違い\は二つで一文字となる)
	);

	// バックスラッシュを置換
	ReplaceConsecChar
	( // 引数
		pPath,	// 置き換えを行う文字列
		'\\',	// 検出する文字
		"\\",	// 置き換える文字列
		1		// 置き換える文字列の長さ (通常文字と違い\は二つで一文字となる)
	);
}

//============================================================
//	文字列の左右追加処理 (マルチバイト文字列)
//============================================================
std::string useful::SandString(const std::string& rTop, const std::string& rMain, const std::string& rCur)
{
	// 左右に追加した文字列を作成し返す
	std::string sTemp;
	sTemp.append(rTop);		// 先頭に追加
	sTemp.append(rMain);	// 中心に追加
	sTemp.append(rCur);		// 最後尾に追加
	return sTemp;
}

//============================================================
//	文字列の左右追加処理 (ワイド文字列)
//============================================================
std::wstring useful::SandString(const std::wstring& rTop, const std::wstring& rMain, const std::wstring& rCur)
{
	// 左右に追加した文字列を作成し返す
	std::wstring wsTemp;
	wsTemp.append(rTop);	// 先頭に追加
	wsTemp.append(rMain);	// 中心に追加
	wsTemp.append(rCur);	// 最後尾に追加
	return wsTemp;
}

//============================================================
//	マルチバイト文字列のワイド文字列変換
//============================================================
std::wstring useful::MultiByteToWide(const std::string& rSrcStr)
{
	int nSrcSize = (int)rSrcStr.size();	// 変換前の文字列のサイズ
	if (nSrcSize <= 0) { return L""; }	// 文字列がない場合抜ける

	// 文字列を変換
	std::wstring wsDest(nSrcSize, L'\0');	// 変換後の文字列
	int nDestSize = MultiByteToWideChar
	( // 引数
		CP_ACP,				// 変換コードページ
		0,					// 変換フラグ
		&rSrcStr.front(),	// 変換前文字列の先頭アドレス
		nSrcSize,			// 変換前文字列のサイズ
		&wsDest.front(),	// 変換後文字列の先頭アドレス
		(int)wsDest.size()	// 変換後文字列のサイズ
	);

	// 文字列サイズを修正
	wsDest.resize(nDestSize);

	// 変換後の文字列を返す
	return wsDest;
}

//============================================================
//	ワイド文字列のマルチバイト文字列変換
//============================================================
std::string useful::WideToMultiByte(const std::wstring& rSrcStr)
{
	int nSrcSize = (int)rSrcStr.size();	// 変換前の文字列のサイズ
	if (nSrcSize <= 0) { return ""; }	// 文字列がない場合抜ける

	// 変換後の文字列サイズを取得
	int nDestSize = WideCharToMultiByte
	( // 引数
		CP_ACP,				// 変換コードページ
		0,					// 変換フラグ
		&rSrcStr.front(),	// 変換前文字列の先頭アドレス
		nSrcSize,			// 変換前文字列のサイズ
		nullptr,			// 変換後文字列の先頭アドレス
		0,					// 変換後文字列のサイズ
		nullptr,			// 変換不可時の置換文字
		nullptr				// 変換不可な文字が存在したか
	);

	// 文字列を変換
	std::string sDest(nDestSize, '\0');	// 変換後の文字列
	WideCharToMultiByte
	( // 引数
		CP_ACP,				// 変換コードページ
		0,					// 変換フラグ
		&rSrcStr.front(),	// 変換前文字列の先頭アドレス
		nSrcSize,			// 変換前文字列のサイズ
		&sDest.front(),		// 変換後文字列の先頭アドレス
		(int)sDest.size(),	// 変換後文字列のサイズ
		nullptr,			// 変換不可時の置換文字
		nullptr				// 変換不可な文字が存在したか
	);

	// 変換後の文字列を返す
	return sDest;
}

//============================================================
//	ベクトルの向き変換
//============================================================
void useful::VecToRot(const VECTOR3& rVec, float* pPhi, float* pTheta)
{
	// 方位角の計算
	*pPhi = atan2f(rVec.y, rVec.x);

	// 仰角の計算
	*pTheta = atan2f(sqrtf((rVec.x * rVec.x) + (rVec.y * rVec.y)), rVec.z);
}

//============================================================
//	向きのベクトル変換
//============================================================
void useful::RotToVec(const float fPhi, const float fTheta, VECTOR3* pVec)
{
	// ベクトルの計算
	pVec->x = sinf(fTheta) * cosf(fPhi);
	pVec->y = sinf(fTheta) * sinf(fPhi);
	pVec->z = cosf(fTheta);
}

//============================================================
//	縦幅からテクスチャのアスペクト比を考慮した横幅の取得処理
//============================================================
float useful::GetTexWidthFromAspect(const float fHeight, const char* pTexturePath)
{
	// アスペクト比から計算した横幅を返す
	return GetTexWidthFromAspect(fHeight, GET_MANAGER->GetTexture()->Regist(pTexturePath));
}

//============================================================
//	縦幅からテクスチャのアスペクト比を考慮した横幅の取得処理
//============================================================
float useful::GetTexWidthFromAspect(const float fHeight, const int nTexIdx)
{
	// テクスチャアスペクト比を取得
	VECTOR2 aspect = GET_MANAGER->GetTexture()->GetInfo(nTexIdx).aspect;

	// アスペクト比から計算した横幅を返す
	return fHeight * aspect.x;
}

//============================================================
//	横幅からテクスチャのアスペクト比を考慮した縦幅の取得処理
//============================================================
float useful::GetTexHeightFromAspect(const float fWidth, const char* pTexturePath)
{
	// アスペクト比から計算した縦幅を返す
	return GetTexHeightFromAspect(fWidth, GET_MANAGER->GetTexture()->Regist(pTexturePath));
}

//============================================================
//	横幅からテクスチャのアスペクト比を考慮した縦幅の取得処理
//============================================================
float useful::GetTexHeightFromAspect(const float fWidth, const int nTexIdx)
{
	// テクスチャアスペクト比を取得
	VECTOR2 aspect = GET_MANAGER->GetTexture()->GetInfo(nTexIdx).aspect;

	// アスペクト比から計算した縦幅を返す
	return fWidth * aspect.y;
}

//============================================================
//	ランダム向き取得
//============================================================
float useful::RandomRot()
{
	// ランダム向きを返す
	return (float)(rand() % 629 - 314) * 0.01f;
}
