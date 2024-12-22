//============================================================
//
//	���U���g�}�l�[�W���[���� [resultManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "resultManager.h"
#include "resultState.h"
#include "manager.h"

//************************************************************
//	�e�N���X [CResultManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CResultManager::CResultManager() :
	m_pState	(nullptr)	// ���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CResultManager::~CResultManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CResultManager::Init()
{
	// �����o�ϐ���������
	m_pState = nullptr;	// ���

	// �ʏ��Ԃɂ���
	ChangeState(new CResultStateNormal);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CResultManager::Uninit()
{
	// ��Ԃ̏I��
	SAFE_UNINIT(m_pState);
}

//============================================================
//	�X�V����
//============================================================
void CResultManager::Update(const float fDeltaTime)
{
	// ��Ԃ��Ƃ̍X�V
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	��Ԃ̕ύX����
//============================================================
HRESULT CResultManager::ChangeState(CResultState* pState)
{
	// ��Ԃ̐����Ɏ��s���Ă���ꍇ������
	if (pState == nullptr) { assert(false); return E_FAIL; }

	// ��ԃC���X�^���X���I��
	SAFE_UNINIT(m_pState);

	// ��ԃC���X�^���X��ύX
	assert(m_pState == nullptr);
	m_pState = pState;

	// ��ԂɃR���e�L�X�g��ݒ�
	m_pState->SetContext(this);

	// ��ԃC���X�^���X��������
	if (FAILED(m_pState->Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	return S_OK;
}

//============================================================
//	�����L���O��ʑJ�ڏ���
//============================================================
void CResultManager::TransRanking()
{
	// �����L���O��ʂɑJ�ڂ���
	GET_MANAGER->SetLoadScene(CScene::MODE_RANKING);
}

//============================================================
//	��������
//============================================================
CResultManager* CResultManager::Create()
{
	// ���U���g�}�l�[�W���[�̐���
	CResultManager* pResultManager = new CResultManager;
	if (pResultManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ���U���g�}�l�[�W���[�̏�����
		if (FAILED(pResultManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ���U���g�}�l�[�W���[�̔j��
			SAFE_DELETE(pResultManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pResultManager;
	}
}

//============================================================
//	�j������
//============================================================
void CResultManager::Release(CResultManager*& prResultManager)
{
	// ���U���g�}�l�[�W���[�̏I��
	assert(prResultManager != nullptr);
	prResultManager->Uninit();

	// �������J��
	SAFE_DELETE(prResultManager);
}
