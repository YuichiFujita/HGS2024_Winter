//============================================================
//
//	�����L���O�}�l�[�W���[���� [rankingManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "rankingManager.h"
#include "rankingState.h"
#include "manager.h"

//************************************************************
//	�e�N���X [CRankingManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CRankingManager::CRankingManager() :
	m_pState	(nullptr)	// ���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CRankingManager::~CRankingManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CRankingManager::Init()
{
	// �����o�ϐ���������
	m_pState = nullptr;	// ���

	// �ʏ��Ԃɂ���
	ChangeState(new CRankingStateNormal);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CRankingManager::Uninit()
{
	// ��Ԃ̏I��
	SAFE_UNINIT(m_pState);
}

//============================================================
//	�X�V����
//============================================================
void CRankingManager::Update(const float fDeltaTime)
{
	// ��Ԃ��Ƃ̍X�V
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	��Ԃ̕ύX����
//============================================================
HRESULT CRankingManager::ChangeState(CRankingState* pState)
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
//	��������
//============================================================
CRankingManager* CRankingManager::Create()
{
	// �����L���O�}�l�[�W���[�̐���
	CRankingManager* pRankingManager = new CRankingManager;
	if (pRankingManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �����L���O�}�l�[�W���[�̏�����
		if (FAILED(pRankingManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �����L���O�}�l�[�W���[�̔j��
			SAFE_DELETE(pRankingManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pRankingManager;
	}
}

//============================================================
//	�j������
//============================================================
void CRankingManager::Release(CRankingManager*& prRankingManager)
{
	// �����L���O�}�l�[�W���[�̏I��
	assert(prRankingManager != nullptr);
	prRankingManager->Uninit();

	// �������J��
	SAFE_DELETE(prRankingManager);
}
