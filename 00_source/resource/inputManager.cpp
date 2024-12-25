//============================================================
//
//	操作マネージャー処理 [inputManager.cpp]
//	Author：藤田勇一
//
//============================================================
//************************************************************
//	インクルードファイル
//************************************************************
#include "inputManager.h"
#include "manager.h"

//************************************************************
//	操作空間
//************************************************************
//============================================================
//	確定操作
//============================================================
bool input::Decide()
{
	CInputKeyboard* pKey = GET_INPUTKEY;	// キーボード情報
	CInputPad* pPad = GET_INPUTPAD;			// パッド情報
	return (pKey->IsTrigger(DIK_SPACE) || pKey->IsTrigger(DIK_RETURN) || pPad->IsTrigger(CInputPad::KEY_A) || pPad->IsTrigger(CInputPad::KEY_B) || pPad->IsTrigger(CInputPad::KEY_X) || pPad->IsTrigger(CInputPad::KEY_Y));
}
