//============================================================
//
//	�G�f�B�b�g�}�l�[�W���[���� [editManager.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "editManager.h"
#include "main.h"
#include "manager.h"
#include "actor.h"
#include "collision.h"
#include "sceneGame.h"
#include "gameManager.h"

//************************************************************
//	�}�N����`
//************************************************************
#define KEY_DOUBLE		(DIK_LCONTROL)	// ��d���L�[
#define NAME_DOUBLE		("LCTRL")		// ��d���\��
#define KEY_REVERSE		(DIK_LCONTROL)	// �t�]�L�[
#define NAME_REVERSE	("LCTRL")		// �t�]�\��
#define KEY_TRIGGER		(DIK_LSHIFT)	// �g���K�[���L�[
#define NAME_TRIGGER	("LSHIFT")		// �g���K�[���\��

#define KEY_CREATE		(DIK_0)		// �����L�[
#define NAME_CREATE		("0")		// �����\��
#define KEY_RELEASE		(DIK_9)		// �j���L�[
#define NAME_RELEASE	("9")		// �j���\��
#define KEY_TYPE		(DIK_1)		// ��ޕύX�L�[
#define NAME_TYPE		("1")		// ��ޕύX�\��
#define KEY_SAVE		(DIK_F9)	// �ۑ��L�[
#define NAME_SAVE		("F9")		// �ۑ��\��

#define KEY_FAR		(DIK_W)	// ���ړ��L�[
#define NAME_FAR	("W")	// ���ړ��\��
#define KEY_NEAR	(DIK_S)	// ��O�ړ��L�[
#define NAME_NEAR	("S")	// ��O�ړ��\��
#define KEY_RIGHT	(DIK_D)	// �E�ړ��L�[
#define NAME_RIGHT	("D")	// �E�ړ��\��
#define KEY_LEFT	(DIK_A)	// ���ړ��L�[
#define NAME_LEFT	("A")	// ���ړ��\��
#define KEY_UP		(DIK_E)	// ��ړ��L�[
#define NAME_UP		("E")	// ��ړ��\��
#define KEY_DOWN	(DIK_Q)	// ���ړ��L�[
#define NAME_DOWN	("Q")	// ���ړ��\��

#define KEY_ROTA_RIGHT	(DIK_Z)	// �E��]�L�[
#define NAME_ROTA_RIGHT	("Z")	// �E��]�\��
#define KEY_ROTA_LEFT	(DIK_C)	// ����]�L�[
#define NAME_ROTA_LEFT	("C")	// ����]�\��

#define KEY_SCALE_UP	(DIK_T)	// �g��L�[
#define NAME_SCALE_UP	("T")	// �g��\��
#define KEY_SCALE_DOWN	(DIK_G)	// �k���L�[
#define NAME_SCALE_DOWN	("G")	// �k���\��

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char*	SAVE_TXT = "data\\TXT\\save_actor.txt";	// �ۑ��e�L�X�g
	const float	INIT_ALPHA = 0.5f;	// �z�u�O�̃��l
	const float	MOVE = 1.5f;		// �ړ���
	const float	ROTMOVE = 0.02f;	// �����ړ���
	const float	SCALEMOVE = 0.1f;	// �g���
}

//************************************************************
//	�e�N���X [CEditManager] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CEditManager::CEditManager() :
	m_pCreateActor	(nullptr)	// �����A�N�^�[���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CEditManager::~CEditManager()
{

}

//============================================================
//	����������
//============================================================
HRESULT CEditManager::Init()
{
	// �����o�ϐ���������
	m_pCreateActor = nullptr;	// �����A�N�^�[���

	// ��Q���̐���
	m_pCreateActor = CActor::Create(CActor::TYPE_WOOD, VEC3_ZERO, VEC3_ZERO, VEC3_ONE);
	if (m_pCreateActor == nullptr)
	{ // �����Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �����x��ݒ�
	m_pCreateActor->SetAlpha(INIT_ALPHA);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CEditManager::Uninit()
{
	// ���ݒu�A�N�^�[�̏I��
	SAFE_UNINIT(m_pCreateActor);
}

//============================================================
//	�X�V����
//============================================================
void CEditManager::Update(const float fDeltaTime)
{
	// ����\�t���O��OFF�ɂ���
	CSceneGame::GetGameManager()->SetEnableControlOK(false);

	// �ʒu�̍X�V
	UpdatePosition(fDeltaTime);

	// �����̍X�V
	UpdateRotation(fDeltaTime);

	// �g�嗦�̍X�V
	UpdateScale(fDeltaTime);

	// ��ނ̍X�V
	UpdateType();

	// �A�N�^�[�̐���
	CreateActor();

	// �A�N�^�[�̔j��
	ReleaseActor();

	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(KEY_SAVE))
	{
		// �A�N�^�[�̕ۑ�
		SaveActor();
	}
}

//============================================================
//	��������
//============================================================
CEditManager* CEditManager::Create()
{
	// �G�f�B�b�g�}�l�[�W���[�̐���
	CEditManager* pEditManager = new CEditManager;
	if (pEditManager == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �G�f�B�b�g�}�l�[�W���[�̏�����
		if (FAILED(pEditManager->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �G�f�B�b�g�}�l�[�W���[�̔j��
			SAFE_DELETE(pEditManager);
			return nullptr;
		}

		// �m�ۂ����A�h���X��Ԃ�
		return pEditManager;
	}
}

//============================================================
//	�j������
//============================================================
void CEditManager::Release(CEditManager*& prEditManager)
{
	// �G�f�B�b�g�}�l�[�W���[�̏I��
	assert(prEditManager != nullptr);
	prEditManager->Uninit();

	// �������J��
	SAFE_DELETE(prEditManager);
}

//============================================================
//	�ʒu�̍X�V����
//============================================================
void CEditManager::UpdatePosition(const float fDeltaTime)
{
	float fDeltaRate = fDeltaTime / (1.0f / (float)main::FPS);	// �o�ߎ��Ԃ̊���

	// �ʒu��ύX
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	VECTOR3 posActor = m_pCreateActor->GetVec3Position();	// �ʒu
	if (!pKey->IsPress(KEY_TRIGGER))
	{
		if (pKey->IsPress(KEY_FAR))
		{
			posActor.z += MOVE * fDeltaRate;
		}
		if (pKey->IsPress(KEY_NEAR))
		{
			posActor.z -= MOVE * fDeltaRate;
		}
		if (pKey->IsPress(KEY_RIGHT))
		{
			posActor.x += MOVE * fDeltaRate;
		}
		if (pKey->IsPress(KEY_LEFT))
		{
			posActor.x -= MOVE * fDeltaRate;
		}
		if (pKey->IsPress(KEY_UP))
		{
			posActor.y += MOVE * fDeltaRate;
		}
		if (pKey->IsPress(KEY_DOWN))
		{
			posActor.y -= MOVE * fDeltaRate;
		}
	}
	else
	{
		if (pKey->IsTrigger(KEY_FAR))
		{
			posActor.z += MOVE * fDeltaRate;
		}
		if (pKey->IsTrigger(KEY_NEAR))
		{
			posActor.z -= MOVE * fDeltaRate;
		}
		if (pKey->IsTrigger(KEY_RIGHT))
		{
			posActor.x += MOVE * fDeltaRate;
		}
		if (pKey->IsTrigger(KEY_LEFT))
		{
			posActor.x -= MOVE * fDeltaRate;
		}
		if (pKey->IsTrigger(KEY_UP))
		{
			posActor.y += MOVE * fDeltaRate;
		}
		if (pKey->IsTrigger(KEY_DOWN))
		{
			posActor.y -= MOVE * fDeltaRate;
		}
	}

	// �ʒu�𔽉f
	m_pCreateActor->SetVec3Position(posActor);
}

//============================================================
//	�����̍X�V����
//============================================================
void CEditManager::UpdateRotation(const float fDeltaTime)
{
	float fDeltaRate = fDeltaTime / (1.0f / (float)main::FPS);	// �o�ߎ��Ԃ̊���

	// ������ύX
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	VECTOR3 rotActor = m_pCreateActor->GetVec3Rotation();	// ����
	if (pKey->IsPress(KEY_ROTA_RIGHT))
	{
		rotActor.y += ROTMOVE * fDeltaRate;
	}
	if (pKey->IsPress(KEY_ROTA_LEFT))
	{
		rotActor.y -= ROTMOVE * fDeltaRate;
	}

	// �����𔽉f
	m_pCreateActor->SetVec3Rotation(rotActor);
}

//============================================================
//	�g�嗦�̍X�V����
//============================================================
void CEditManager::UpdateScale(const float fDeltaTime)
{
	float fDeltaRate = fDeltaTime / (1.0f / (float)main::FPS);	// �o�ߎ��Ԃ̊���

	// �g�嗦��ύX
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	VECTOR3 scaleActor = m_pCreateActor->GetVec3Scale();	// �g�嗦
	if (pKey->IsPress(KEY_SCALE_UP))
	{
		scaleActor += SCALEMOVE * fDeltaRate;
	}
	if (pKey->IsPress(KEY_SCALE_DOWN))
	{
		scaleActor -= SCALEMOVE * fDeltaRate;
	}

	// �g�嗦�𔽉f
	m_pCreateActor->SetVec3Scale(scaleActor);
}

//============================================================
//	��ނ̍X�V����
//============================================================
void CEditManager::UpdateType()
{
	// ��ނ�ύX
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsPress(KEY_REVERSE))
	{
		if (pKey->IsTrigger(KEY_TYPE))
		{
			// ��ނ�ύX
			CActor::EType type = (CActor::EType)(( + (CActor::TYPE_MAX - 1)) % CActor::TYPE_MAX);

			// ��ނ𔽉f
			m_pCreateActor->SetType(type);
			m_pCreateActor->SetAlpha(INIT_ALPHA);	// �����x���Đݒ�
		}
	}
	else
	{
		if (pKey->IsTrigger(KEY_TYPE))
		{
			// ��ނ�ύX
			CActor::EType type = (CActor::EType)((m_pCreateActor->GetType() + 1) % CActor::TYPE_MAX);

			// ��ނ𔽉f
			m_pCreateActor->SetType(type);
			m_pCreateActor->SetAlpha(INIT_ALPHA);	// �����x���Đݒ�
		}
	}
}

//============================================================
//	�A�N�^�[�̐�������
//============================================================
void CEditManager::CreateActor()
{
	CActor::EType typeOld = m_pCreateActor->GetType();		// ���̎��
	D3DXVECTOR3 posOld = m_pCreateActor->GetVec3Position();	// ���̈ʒu
	D3DXVECTOR3 rotOld = m_pCreateActor->GetVec3Rotation();	// ���̌���
	D3DXVECTOR3 scaleOld = m_pCreateActor->GetVec3Scale();	// ���̊g�嗦

	// �A�N�^�[�̔z�u
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(KEY_CREATE))
	{
		//----------------------------------------------------
		//	�A�N�^�[�̏���z�u�p�ɕύX
		//----------------------------------------------------
		// �����X�V�E�����`���ON�ɂ���
		m_pCreateActor->SetEnableUpdate(true);
		m_pCreateActor->SetEnableDraw(true);

		// �}�e���A�����Đݒ�
		m_pCreateActor->ResetMaterial();

		//----------------------------------------------------
		//	�V�����A�N�^�[�̐���
		//----------------------------------------------------
		// �A�N�^�[�̐���
		m_pCreateActor = CActor::Create(typeOld, posOld, rotOld, scaleOld);
		assert(m_pCreateActor != nullptr);

		// �����x��ݒ�
		m_pCreateActor->SetAlpha(INIT_ALPHA);
	}
}

//============================================================
//	�A�N�^�[�̔j������
//============================================================
void CEditManager::ReleaseActor()
{
	// �A�N�^�[�̍폜
	CInputKeyboard *pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsTrigger(KEY_RELEASE))
	{
		// �A�N�^�[���Ȃ��ꍇ������
		CListManager<CActor>* pList = CActor::GetList();
		if (pList == nullptr) { return; }

		// ���X�g�}�l�[�W���[���烊�X�g���擾
		std::list<CActor*> listTimer = pList->GetList();

		for (auto& rList : listTimer)
		{ // ���X�g���̗v�f�����J��Ԃ�

			// ���g�̏ꍇ������
			if (rList == m_pCreateActor) { continue; }

			bool bHit = collision::Circle2D
			( // ����
				m_pCreateActor->GetVec3Position(),
				rList->GetVec3Position(),
				30.0f,
				30.0f
			);
			if (bHit)
			{ // �폜�͈͓��̏ꍇ

				// �A�N�^�[�̏I��
				SAFE_UNINIT(rList);
			}
		}
	}
}

//============================================================
//	�A�N�^�[�̕ۑ�����
//============================================================
void CEditManager::SaveActor(void)
{
	// �t�@�C���������o���`���ŊJ��
	FILE* pFile = fopen(SAVE_TXT, "w");
	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		// ���o���������o��
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	�A�N�^�[�Z�[�u�e�L�X�g [save_actor.txt]\n");
		fprintf(pFile, "#	Author : ���c�E��\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "---------->--<---------- �������牺�� �R�s�[���\��t�� ---------->--<----------\n");
		fprintf(pFile, "\n");

		// ���J�n�n�_�������o��
		fprintf(pFile, "STAGE_ACTORSET\n\n");

		CListManager<CActor>* pList = CActor::GetList();
		if (pList != nullptr)
		{ // �A�N�^�[������ꍇ

			// ���X�g�}�l�[�W���[���烊�X�g���擾
			std::list<CActor*> listTimer = pList->GetList();
			for (auto& rList : listTimer)
			{ // ���X�g���̗v�f�����J��Ԃ�

				// ���g�̏ꍇ������
				if (rList == m_pCreateActor) { continue; }

				VECTOR3 posActor = rList->GetVec3Position();	// �A�N�^�[�ʒu
				VECTOR3 rotActor = rList->GetVec3Rotation();	// �A�N�^�[����
				VECTOR3 scaleActor = rList->GetVec3Scale();		// �A�N�^�[�g�嗦

				// ���������o��
				fprintf(pFile, "	ACTORSET\n");
				fprintf(pFile, "		TYPE = %d\n", rList->GetType());
				fprintf(pFile, "		POS = %.2f %.2f %.2f\n", posActor.x, posActor.y, posActor.z);
				fprintf(pFile, "		ROT = %.2f %.2f %.2f\n", rotActor.x, rotActor.y, rotActor.z);
				fprintf(pFile, "		SCALE = %.2f %.2f %.2f\n", scaleActor.x, scaleActor.y, scaleActor.z);
				fprintf(pFile, "	END_ACTORSET\n\n");
			}
		}

		// ���I���n�_�������o��
		fprintf(pFile, "END_STAGE_ACTORSET\n\n");

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// �G���[���b�Z�[�W�{�b�N�X
		MessageBox(NULL, "�A�N�^�[�Z�[�u�t�@�C���̏����o���Ɏ��s�I", "�x���I", MB_ICONWARNING);
	}
}
