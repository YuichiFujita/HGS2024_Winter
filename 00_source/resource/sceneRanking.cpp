//============================================================
//
//	�����L���O��ʏ��� [sceneRanking.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "sceneRanking.h"
#include "manager.h"
#include "sound.h"
#include "camera.h"
#include "rankingManager.h"

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CRankingManager* CSceneRanking::m_pRankingManager = nullptr;	// �����L���O�}�l�[�W���[

//************************************************************
//	�q�N���X [CSceneRanking] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CSceneRanking::CSceneRanking(const EMode mode) : CScene(mode)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CSceneRanking::~CSceneRanking()
{

}

//============================================================
//	����������
//============================================================
HRESULT CSceneRanking::Init()
{
	// �V�[���̏�����
	if (FAILED(CScene::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �����L���O�}�l�[�W���[�̐���
	m_pRankingManager = CRankingManager::Create();
	if (m_pRankingManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// TODO�F�J�����ݒ�
#if 0
	// �Œ�J�����ɂ���
	CCamera* pCamera = GET_MANAGER->GetCamera();	// �J�������
	pCamera->SetState(CCamera::STATE_NONE);			// �Œ��Ԃ�ݒ�
#endif

	// BGM�̍Đ�
	PLAY_SOUND(CSound::LABEL_BGM_GENERAL);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CSceneRanking::Uninit()
{
	// �����L���O�}�l�[�W���[�̔j��
	SAFE_REF_RELEASE(m_pRankingManager);

	// �V�[���̏I��
	CScene::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CSceneRanking::Update(const float fDeltaTime)
{
	// �����L���O�}�l�[�W���[�̍X�V
	assert(m_pRankingManager != nullptr);
	m_pRankingManager->Update(fDeltaTime);
}

//============================================================
//	�����L���O�}�l�[�W���[�擾����
//============================================================
CRankingManager* CSceneRanking::GetRankingManager()
{
	// �C���X�^���X���g�p
	assert(m_pRankingManager != nullptr);

	// �����L���O�}�l�[�W���[�̃|�C���^��Ԃ�
	return m_pRankingManager;
}