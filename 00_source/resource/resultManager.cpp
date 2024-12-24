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
#include "retention.h"

#ifdef SCORE
#include "multiValue.h"
#else TIMER
#include "timeUI.h"
#endif

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
#ifdef SCORE
	namespace score
	{
		const CValue::EType TYPE = CValue::TYPE_NORMAL;	// �������
		const float DIGIT	= 8;			// �X�R�A����
		const VECTOR3 POS	= SCREEN_CENT;	// �X�R�A�ʒu
		const VECTOR3 SIZE	= VECTOR3(52.8f, 62.4f, 0.0f) * 1.4f;	// �X�R�A�����傫��
		const VECTOR3 SPACE	= VECTOR3(SIZE.x * 0.85f, 0.0f, 0.0f);	// �X�R�A������
	}
#else TIMER
	namespace time
	{
		const CValue::EType TYPE = CValue::TYPE_NORMAL;	// �������
		const VECTOR3 POS		 = SCREEN_CENT;			// �^�C�}�[�ʒu
		const VECTOR3 VAL_SIZE	 = VECTOR3(52.8f, 62.4f, 0.0f) * 1.4f;			// �^�C�}�[�����傫��
		const VECTOR3 PART_SIZE	 = VECTOR3(27.3f, 62.4f, 0.0f) * 1.2f;			// �^�C�}�[��؂�傫��
		const VECTOR3 VAL_SPACE	 = VECTOR3(VAL_SIZE.x * 0.85f, 0.0f, 0.0f);		// �^�C�}�[������
		const VECTOR3 PART_SPACE = VECTOR3(PART_SIZE.x * 0.85f, 0.0f, 0.0f);	// �^�C�}�[��؂��
	}
#endif
}

//************************************************************
//	�e�N���X [CResultManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CResultManager::CResultManager() :
#ifdef SCORE
	m_pScore	(nullptr),	// �X�R�A���
#else TIMER
	m_pTime		(nullptr),	// �^�C�����
#endif
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
	CRetention* pRetention = GET_MANAGER->GetRetention();	// �f�[�^�ۑ��}�l�[�W���[

	// �����o�ϐ���������
#ifdef SCORE
	m_pScore = nullptr;	// �X�R�A���
#else TIMER
	m_pTime = nullptr;	// �^�C�����
#endif
	m_pState = nullptr;	// ���

	// �ʏ��Ԃɂ���
	ChangeState(new CResultStateNormal);

#ifdef SCORE
	// �X�R�A�̐���
	m_pScore = CMultiValue::Create
	( // ����
		score::TYPE,			// �������
		pRetention->GetScore(),	// ����
		score::DIGIT,			// ����
		score::POS,				// �ʒu
		score::SIZE,			// �傫��
		score::SPACE			// ��
	);
	if (m_pScore == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}
#else TIMER
	// �^�C���̐���
	m_pTime = CTimeUI::Create
	( // ����
		pRetention->GetTime(),	// ����
		time::POS,				// �ʒu
		time::VAL_SIZE,			// �����̑傫��
		time::PART_SIZE,		// ��؂�̑傫��
		time::VAL_SPACE,		// �����̋�
		time::PART_SPACE,		// ��؂�̋�
		time::TYPE				// �������
	);
	if (m_pTime == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}
#endif

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CResultManager::Uninit()
{
	// ��Ԃ̏I��
	SAFE_UNINIT(m_pState);

#ifdef SCORE
	// �X�R�A�̏I��
	//SAFE_UNINIT(m_pScore);
#else TIMER
	// �^�C���̏I��
	//SAFE_UNINIT(m_pTimer);
#endif
}

//============================================================
//	�X�V����
//============================================================
void CResultManager::Update(const float fDeltaTime)
{
	// ��Ԃ��Ƃ̍X�V
	assert(m_pState != nullptr);
	m_pState->Update(fDeltaTime);

	if (input::Decide())
	{
		// �����L���O��ʂɑJ�ڂ���
		TransRanking();
	}

#ifdef SCORE
	// �X�R�A�̍X�V
	//m_pScore->Update(fDeltaTime);
#else TIMER
	// �^�C���̍X�V
	//m_pTime->Update(fDeltaTime);
#endif
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
	// �t�F�[�h���̏ꍇ������
	if (GET_MANAGER->GetFade()->IsFade()) { return; }

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
