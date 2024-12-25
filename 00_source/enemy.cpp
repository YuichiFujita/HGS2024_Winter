//============================================================
//
//	�G���� [enemy.cpp]
//	Author�F��������
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "fade.h"
#include "stage.h"
#include "sceneGame.h"
#include "gameManager.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* SETUP_TXT = "data\\CHARACTER\\player.txt";	// �Z�b�g�A�b�v�e�L�X�g���΃p�X
	const int	PRIORITY = 3;		// �v���C���[�̗D�揇��
	const float	GRAVITY = 3600.0f;	// �d��
	const float	RADIUS = 20.0f;	// ���a
	const float HEIGHT = 80.0f;	// �g��
	const float	REV_ROTA = 9.0f;		// �����ύX�̕␳�W��
	const float	JUMP_REV = 0.16f;	// �ʏ��Ԏ��̋󒆂̈ړ��ʂ̌����W��
	const float	LAND_REV = 0.16f;	// �ʏ��Ԏ��̒n��̈ړ��ʂ̌����W��

	namespace motion
	{
		const int BLEND_FRAME_OTHER = 5;	// ���[�V�����̊�{�I�ȃu�����h�t���[��
	}
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CListManager<CEnemy>* CEnemy::m_pList = nullptr;	// �I�u�W�F�N�g���X�g

//************************************************************
//	�q�N���X [CEnemy] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CEnemy::CEnemy() : CObjectChara(CObject::LABEL_ENEMY, CObject::DIM_3D, PRIORITY),
m_oldPos(VEC3_ZERO),	// �ߋ��ʒu
m_move(VEC3_ZERO),	// �ړ���
m_destRot(VEC3_ZERO),	// �ڕW����
m_bJump(false)			// �W�����v��
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CEnemy::~CEnemy()
{

}

//============================================================
//	����������
//============================================================
HRESULT CEnemy::Init()
{
	// �����o�ϐ���������
	m_oldPos = VEC3_ZERO;	// �ߋ��ʒu
	m_move = VEC3_ZERO;	// �ړ���
	m_destRot = VEC3_ZERO;	// �ڕW����
	m_bJump = true;			// �W�����v��

	// �I�u�W�F�N�g�L�����N�^�[�̏�����
	if (FAILED(CObjectChara::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// �L�����N�^�[���̊���
	BindCharaData(SETUP_TXT);

	// �������[�V�����̊���
	SetMotion(MOTION_IDOL);

	if (m_pList == nullptr)
	{ // ���X�g�}�l�[�W���[�����݂��Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̐���
		m_pList = CListManager<CEnemy>::Create();
		if (m_pList == nullptr)
		{ // �����Ɏ��s�����ꍇ

			// ���s��Ԃ�
			assert(false);
			return E_FAIL;
		}
	}

	// ���X�g�Ɏ��g�̃I�u�W�F�N�g��ǉ��E�C�e���[�^�[���擾
	m_iterator = m_pList->AddList(this);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CEnemy::Uninit()
{
	// ���X�g���玩�g�̃I�u�W�F�N�g���폜
	m_pList->DelList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // �I�u�W�F�N�g������Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̔j��
		m_pList->Release(m_pList);
	}

	// �I�u�W�F�N�g�L�����N�^�[�̏I��
	CObjectChara::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CEnemy::Update(const float fDeltaTime)
{
	// �ߋ��ʒu�̍X�V
	UpdateOldPosition();

	// ��Ԃ̍X�V
	EMotion curMotion = UpdateState(fDeltaTime);

	// ���[�V�����E�I�u�W�F�N�g�L�����N�^�[�̍X�V
	UpdateMotion(curMotion, fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CEnemy::Draw(CShader* pShader)
{
	// �I�u�W�F�N�g�L�����N�^�[�̕`��
	CObjectChara::Draw(pShader);
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CEnemy::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);	// ���g
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CEnemy::SetEnableDraw(const bool bDraw)
{
	// �����̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);	// ���g
}

//============================================================
//	��Ԃ̍X�V����
//============================================================
CEnemy::EMotion CEnemy::UpdateState(const float fDeltaTime)
{
	EMotion curMotion = MOTION_IDOL;	// ���݂̃��[�V����
	//switch (m_state)
	//{ // ��Ԃ��Ƃ̏���
	//case STATE_NONE:

	//	// �������Ȃ���Ԏ��̍X�V
	//	curMotion = UpdateNone(fDeltaTime);
	//	break;

	//case STATE_NORMAL:

	//	// �ʏ��Ԃ̍X�V
	//	curMotion = UpdateNormal(fDeltaTime);
	//	break;

	//default:
	//	assert(false);
	//	break;
	//}

	// ���݂̃��[�V������Ԃ�
	return curMotion;
}

//============================================================
//	��������
//============================================================
CEnemy* CEnemy::Create
(
	const VECTOR3& rPos,	// �ʒu
	const VECTOR3& rRot		// ����
)
{
	// �v���C���[�̐���
	CEnemy* pEnemy = new CEnemy;
	if (pEnemy == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �v���C���[�̏�����
		if (FAILED(pEnemy->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �v���C���[�̔j��
			SAFE_DELETE(pEnemy);
			return nullptr;
		}

		// �ʒu��ݒ�
		pEnemy->SetVec3Position(rPos);
		pEnemy->m_oldPos = rPos;	// �ߋ��ʒu������̈ʒu�ɂ���

		// ������ݒ�
		pEnemy->SetVec3Rotation(rRot);
		pEnemy->m_destRot = rRot;	// �ڕW����������̌����ɂ���

		// �m�ۂ����A�h���X��Ԃ�
		return pEnemy;
	}
}

//============================================================
//	���X�g�擾����
//============================================================
CListManager<CEnemy>* CEnemy::GetList()
{
	// �I�u�W�F�N�g���X�g��Ԃ�
	return m_pList;
}

//============================================================
//	���a�擾����
//============================================================
float CEnemy::GetRadius() const
{
	// ���a��Ԃ�
	return RADIUS;
}

//============================================================
//	�c���擾����
//============================================================
float CEnemy::GetHeight() const
{
	// �c����Ԃ�
	return HEIGHT;
}

//============================================================
//	�������Ȃ���Ԏ��̍X�V����
//============================================================
CEnemy::EMotion CEnemy::UpdateNone(const float fDeltaTime)
{
	VECTOR3 posEnemy = GetVec3Position();	// �v���C���[�ʒu
	VECTOR3 rotEnemy = GetVec3Rotation();	// �v���C���[����

	// �d�͂̍X�V
	UpdateGravity(fDeltaTime);

	// �ʒu�X�V
	UpdatePosition(&posEnemy, fDeltaTime);

	// ���n����
	UpdateLanding(&posEnemy, fDeltaTime);

	// �����X�V
	UpdateRotation(&rotEnemy, fDeltaTime);

	// �ʒu�𔽉f
	SetVec3Position(posEnemy);

	// �����𔽉f
	SetVec3Rotation(rotEnemy);

	// ���݂̃��[�V������Ԃ�
	return MOTION_IDOL;
}

//============================================================
//	�ʏ��Ԏ��̍X�V����
//============================================================
CEnemy::EMotion CEnemy::UpdateNormal(const float fDeltaTime)
{
	// ����s�\�ȏꍇ������
	CGameManager* pGameManager = CSceneGame::GetGameManager();	// �Q�[���}�l�[�W���[
	if (pGameManager != nullptr)
	{ // �Q�[���}�l�[�W���[������ꍇ

		if (!pGameManager->IsControlOK()) { return MOTION_IDOL; }
	}

	EMotion curMotion = MOTION_IDOL;		// ���݂̃��[�V����
	VECTOR3 posEnemy = GetVec3Position();	// �v���C���[�ʒu
	VECTOR3 rotEnemy = GetVec3Rotation();	// �v���C���[����

	// �ړ�����
	curMotion = UpdateMove();

	// �d�͂̍X�V
	UpdateGravity(fDeltaTime);

	// �ʒu�X�V
	UpdatePosition(&posEnemy, fDeltaTime);

	// ���n����
	UpdateLanding(&posEnemy, fDeltaTime);

	// �����X�V
	UpdateRotation(&rotEnemy, fDeltaTime);

	// �ʒu�𔽉f
	SetVec3Position(posEnemy);

	// �����𔽉f
	SetVec3Rotation(rotEnemy);

	// ���݂̃��[�V������Ԃ�
	return curMotion;
}

//============================================================
//	�ߋ��ʒu�̍X�V����
//============================================================
void CEnemy::UpdateOldPosition()
{
	// �ߋ��ʒu���X�V
	m_oldPos = GetVec3Position();
}

//============================================================
//	�ړ���/�ڕW�����̍X�V����
//============================================================
CEnemy::EMotion CEnemy::UpdateMove()
{
	EMotion curMotion = MOTION_IDOL;	// ���݂̃��[�V����

	CInputKeyboard* pKey = GET_INPUTKEY;	// �L�[�{�[�h���
	if (pKey->IsPress(DIK_W))
	{
		m_move.z += 30.0f;
		m_destRot.y = D3DX_PI;
		curMotion = MOTION_WALK;
	}
	if (pKey->IsPress(DIK_A))
	{
		m_move.x -= 30.0f;
		m_destRot.y = D3DX_PI * 0.5f;
		curMotion = MOTION_WALK;
	}
	if (pKey->IsPress(DIK_S))
	{
		m_move.z -= 30.0f;
		m_destRot.y = 0.0f;
		curMotion = MOTION_WALK;
	}
	if (pKey->IsPress(DIK_D))
	{
		m_move.x += 30.0f;
		m_destRot.y = -D3DX_PI * 0.5f;
		curMotion = MOTION_WALK;
	}

	// ���[�V������Ԃ�
	return curMotion;
}

//============================================================
//	�d�͂̍X�V����
//============================================================
void CEnemy::UpdateGravity(const float fDeltaTime)
{
	// �d�͂����Z
	m_move.y -= GRAVITY * fDeltaTime;
}

//============================================================
//	���n�󋵂̍X�V����
//============================================================
bool CEnemy::UpdateLanding(VECTOR3* pPos, const float fDeltaTime)
{
	CStage* pStage = GET_MANAGER->GetStage();	// �X�e�[�W���
	bool bLand = false;	// ���n�t���O

	// �n�ʁE�����ʒu���n����
	if (pStage->LandFieldPosition(*pPos, m_oldPos, m_move)
		|| pStage->LandLimitPosition(*pPos, m_move, 0.0f))
	{ // �v���C���[�����n���Ă����ꍇ

		// ���n���Ă����Ԃɂ���
		bLand = true;

		// �W�����v���Ă��Ȃ���Ԃɂ���
		m_bJump = false;
	}

	// ���n�t���O��Ԃ�
	return bLand;
}

//============================================================
//	�ʒu�̍X�V����
//============================================================
void CEnemy::UpdatePosition(VECTOR3* pPos, const float fDeltaTime)
{
	// �ړ��ʂ����Z
	*pPos += m_move * fDeltaTime;

	// �ړ��ʂ�����
	if (m_bJump)
	{ // �󒆂̏ꍇ

		m_move.x += (0.0f - m_move.x) * JUMP_REV;
		m_move.z += (0.0f - m_move.z) * JUMP_REV;
	}
	else
	{ // �n��̏ꍇ

		m_move.x += (0.0f - m_move.x) * LAND_REV;
		m_move.z += (0.0f - m_move.z) * LAND_REV;
	}
}

//============================================================
//	�����̍X�V����
//============================================================
void CEnemy::UpdateRotation(VECTOR3* pRot, const float fDeltaTime)
{
	// �ϐ���錾
	float fDiffRot = 0.0f;	// ��������

	// �ڕW�����̐��K��
	useful::NormalizeRot(m_destRot.y);

	// �ڕW�����܂ł̍������v�Z
	fDiffRot = m_destRot.y - pRot->y;

	// ���������̐��K��
	useful::NormalizeRot(fDiffRot);

	// �����̍X�V
	pRot->y += fDiffRot * fDeltaTime * REV_ROTA;

	// �����̐��K��
	useful::NormalizeRot(pRot->y);
}

//============================================================
//	���[�V����/�L�����N�^�[�̍X�V����
//============================================================
void CEnemy::UpdateMotion(int nMotion, const float fDeltaTime)
{
	// ����ł��甲����
	if (IsDeath()) { return; }

	int nAnimMotion = GetMotionType();	// ���ݍĐ����̃��[�V����
	if (nMotion != NONE_IDX)
	{ // ���[�V�������ݒ肳��Ă���ꍇ

		if (IsMotionLoop())
		{ // ���[�v���郂�[�V�������̏ꍇ

			if (nAnimMotion != nMotion)
			{ // ���݂̃��[�V�������Đ����̃��[�V�����ƈ�v���Ȃ��ꍇ

				// ���݂̃��[�V�����̐ݒ�
				SetMotion(nMotion, motion::BLEND_FRAME_OTHER);
			}
		}
		else
		{ // ���[�v���Ȃ����[�V�������̏ꍇ

#if 0
			switch (GetMotionType())
			{ // ���[�V�������Ƃ̏���
			case MOTION_:

				if (nMotion != MOTION_IDOL)
				{ // �ҋ@���[�V�����ȊO�̏ꍇ

					// ���݂̃��[�V�����̐ݒ�
					SetMotion(nMotion, motion::BLEND_FRAME_OTHER);
				}
				break;
			}
#endif
		}
	}

	// �I�u�W�F�N�g�L�����N�^�[�̍X�V
	CObjectChara::Update(fDeltaTime);

	switch (GetMotionType())
	{ // ���[�V�����̎�ނ��Ƃ̏���
	case MOTION_IDOL:
		break;

	case MOTION_WALK:
		break;
	}
}
