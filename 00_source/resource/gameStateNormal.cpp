//============================================================
//
//	�ʏ��ԏ��� [gameStateNormal.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "gameStateNormal.h"
#include "gameManager.h"

//************************************************************
//	�q�N���X [CGameStateNormal] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CGameStateNormal::CGameStateNormal()
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CGameStateNormal::~CGameStateNormal()
{

}

//============================================================
//	����������
//============================================================
HRESULT CGameStateNormal::Init()
{
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CGameStateNormal::Uninit()
{
	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CGameStateNormal::Update(const float fDeltaTime)
{
	// ����\��Ԃɂ���
	m_pContext->SetEnableControlOK(true);
}