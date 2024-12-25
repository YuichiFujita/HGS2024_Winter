//============================================================
//
//	�J�n���o��ԏ��� [gameStateStart.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "gameStateStart.h"
#include "gameManager.h"
#include "start.h"

//************************************************************
//	�q�N���X [CGameStateStart] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CGameStateStart::CGameStateStart() :
	m_pStart	(nullptr)	// �J�n���o���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CGameStateStart::~CGameStateStart()
{

}

//============================================================
//	����������
//============================================================
HRESULT CGameStateStart::Init()
{
	// �����o�ϐ���������
	m_pStart = nullptr;	// �J�n���o���

	// �J�n���o�̐���
	m_pStart = CStart::Create();
	if (m_pStart == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CGameStateStart::Uninit()
{
	// �J�n���o�̏I��
	SAFE_UNINIT(m_pStart);

	// ���g�̔j��
	delete this;
}

//============================================================
//	�X�V����
//============================================================
void CGameStateStart::Update(const float fDeltaTime)
{
	// ����s�\��Ԃɂ���
	m_pContext->SetEnableControlOK(false);

	// �J�n���o�̍X�V
	m_pStart->Update(fDeltaTime);

	if (m_pStart->IsStagEnd())
	{ // �J�n���o���I�������ꍇ

		// �^�C�}�[�v���J�n
		m_pContext->TimerStart();

		// �ʏ��Ԃɂ���
		m_pContext->ChangeState(new CGameStateNormal);
	}
}