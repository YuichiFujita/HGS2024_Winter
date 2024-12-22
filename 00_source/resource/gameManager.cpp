//============================================================
//
//	�Q�[���}�l�[�W���[���� [gameManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "gameManager.h"
#include "gameState.h"
#include "manager.h"

//************************************************************
//	�e�N���X [CGameManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CGameManager::CGameManager() :
	m_pState	 (nullptr),	// ���
	m_bControlOK (false)	// ����\�t���O
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CGameManager::~CGameManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CGameManager::Init()
{
	// �����o�ϐ���������
	m_pState	 = nullptr;	// ���
	m_bControlOK = true;	// ����\�t���O

	// �ʏ��Ԃɂ���
	ChangeState(new CGameStateNormal);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CGameManager::Uninit()
{
	// ��Ԃ̏I��
	SAFE_UNINIT(m_pState);
}

//============================================================
//	�X�V����
//============================================================
void CGameManager::Update(const float fDeltaTime)
{
	// ��Ԃ��Ƃ̍X�V
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);
}

//============================================================
//	��Ԃ̕ύX����
//============================================================
HRESULT CGameManager::ChangeState(CGameState* pState)
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
//	���U���g��ʑJ�ڏ���
//============================================================
void CGameManager::TransResult()
{
	// ���U���g��ʂɑJ�ڂ���
	GET_MANAGER->SetLoadScene(CScene::MODE_RESULT);
}

//============================================================
//	�ʏ��Ԃ��̊m�F����
//============================================================
bool CGameManager::IsNormal() const
{
	// �ʏ��Ԃ��𔻒肵�Ԃ�
	return (typeid(*m_pState) == typeid(CGameStateNormal));
}

//============================================================
//	��������
//============================================================
CGameManager* CGameManager::Create()
{
	// �Q�[���}�l�[�W���[�̐���
	CGameManager* pGameManager = new CGameManager;
	if (pGameManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �Q�[���}�l�[�W���[�̏�����
		if (FAILED(pGameManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �Q�[���}�l�[�W���[�̔j��
			SAFE_DELETE(pGameManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pGameManager;
	}
}

//============================================================
//	�j������
//============================================================
void CGameManager::Release(CGameManager*& prGameManager)
{
	// �Q�[���}�l�[�W���[�̏I��
	assert(prGameManager != nullptr);
	prGameManager->Uninit();

	// �������J��
	SAFE_DELETE(prGameManager);
}
