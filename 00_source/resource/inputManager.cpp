//============================================================
//
//	����}�l�[�W���[���� [inputManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "inputManager.h"
#include "manager.h"

//************************************************************
//	������
//************************************************************
//============================================================
//	�m�葀��
//============================================================
bool input::Decide()
{
	CInputKeyboard* pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	CInputPad* pPad = GET_INPUTPAD;			// �p�b�h���
	return (pKey->IsTrigger(DIK_SPACE) || pKey->IsTrigger(DIK_RETURN) || pPad->IsTrigger(CInputPad::KEY_A) || pPad->IsTrigger(CInputPad::KEY_B) || pPad->IsTrigger(CInputPad::KEY_X) || pPad->IsTrigger(CInputPad::KEY_Y));
}
