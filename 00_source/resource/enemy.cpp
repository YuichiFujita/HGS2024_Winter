//============================================================
//
//	�G���� [enemy.cpp]
//	Author�F��������
//	Adder �F���c�E��
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
#include "player.h"
#include "presentLand.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* SETUP_TXT = "data\\CHARACTER\\santa_black.txt";	// �Z�b�g�A�b�v�e�L�X�g���΃p�X
	const int	PRIORITY = 3;		// �v���C���[�̗D�揇��
	const float	GRAVITY = 3600.0f;	// �d��
	const float	RADIUS = 20.0f;	// ���a
	const float HEIGHT = 80.0f;	// �g��
	const float	REV_ROTA = 9.0f;	// �����ύX�̕␳�W��
	const float	JUMP_REV = 0.16f;	// �ʏ��Ԏ��̋󒆂̈ړ��ʂ̌����W��
	const float	LAND_REV = 0.16f;	// �ʏ��Ԏ��̒n��̈ړ��ʂ̌����W��
	const float	JUMP_HEIGHT = 1000.0f;	// �W�����v�̍ō����B�_
	const float	JUMP_TIME = 0.65f;		// �W�����v����
	const float	CHANGE_ATK = 700.0f;	// �U���ύX����

	const float LAND_NUM_TIME = 50.0f;		// �ݒu�^�v���[���g��������
	const int LAND_NUM_MAX = 3;				// �ݒu�^�v���[���g�̍ő吔
	const float LAND_NUM_RANGE = 50.0f;		// �ݒu�^�v���[���g�͈̔͂�

	namespace motion
	{
		const int BLEND_FRAME_OTHER = 5;	// ���[�V�����̊�{�I�ȃu�����h�t���[��
	}
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CListManager<CEnemy>* CEnemy::m_pList = nullptr;	// �I�u�W�F�N�g���X�g
CEnemy::AFuncState CEnemy::m_aFuncState[] =			// ��ԍX�V�֐����X�g
{
	&CEnemy::UpdateIdol,	// �ҋ@��Ԃ̍X�V
	&CEnemy::UpdateJump,	// �W�����v��Ԃ̍X�V
	&CEnemy::UpdateAttack,	// �U����Ԃ̍X�V
};

//************************************************************
//	�q�N���X [CEnemy] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CEnemy::CEnemy() : CObjectChara(CObject::LABEL_ENEMY, CObject::DIM_3D, PRIORITY),
m_state(STATE_IDOL),		// ���
m_oldPos(VEC3_ZERO),		// �ߋ��ʒu
m_jumpPosStart(VEC3_ZERO),	// �W�����v�J�n�ʒu
m_jumpPosEnd(VEC3_ZERO),	// �W�����v�I���ʒu
m_move(VEC3_ZERO),			// �ړ���
m_destRot(VEC3_ZERO),		// �ڕW����
m_bJump(false),				// �W�����v��
m_fStateTime(0.0f)			// ��ԊǗ�����
{
	// �X�^�e�B�b�N�A�T�[�g
	static_assert(NUM_ARRAY(m_aFuncState) == CEnemy::STATE_MAX, "ERROR : State Count Mismatch");
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
	m_state = STATE_IDOL;		// ���
	m_oldPos = VEC3_ZERO;		// �ߋ��ʒu
	m_jumpPosStart = VEC3_ZERO;	// �W�����v�J�n�ʒu
	m_jumpPosEnd = VEC3_ZERO;	// �W�����v�I���ʒu
	m_move = VEC3_ZERO;			// �ړ���
	m_destRot = VEC3_ZERO;		// �ڕW����
	m_bJump = true;				// �W�����v��
	m_fStateTime = 0.0f;		// ��ԊǗ�����

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
	EMotion curMotion = (this->*(m_aFuncState[m_state]))(fDeltaTime);

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
//	�ҋ@���Ԃ̌v�Z����
//============================================================
float CEnemy::CalcIdolTime()
{
	float fCurGameTime = CSceneGame::GetGameManager()->GetGameTime();	// ���݂̌o�ߎ���

	// �o�ߎ��Ԃ���ҋ@���Ԃ𑁂�����
	float fRate = easing::InCubic(fCurGameTime, 0.0f, 10.0f);

	// 
	return useful::RateToValue(fRate, 2.0f, 0.5f);
}

//============================================================
//	�U�����[�V�����t���O�擾����
//============================================================
bool CEnemy::IsAttack()
{
	// �U�����[�V����������Ԃ�
	return (MOTION_ATK_UP || MOTION_ATK_SIDE);
}

//============================================================
//	��Ԃ̐ݒ菈��
//============================================================
void CEnemy::SetState(const EState state)
{
	// ������Ԃ̐ݒ�
	m_state = state;

	// �^�C�}�[�̏�����
	m_fStateTime = 0.0f;
}

//============================================================
//	�W�����v�̐ݒ菈��
//============================================================
void CEnemy::SetJump(const VECTOR3& rCurPos, const VECTOR3& rJumpPos)
{
	// �W�����v�J�n/�I���ʒu��ۑ�
	m_jumpPosStart = rCurPos;
	m_jumpPosEnd = rJumpPos;

	// �W�����v��Ԃɂ���
	SetState(STATE_JUMP);
}

//============================================================
//	�U���̐ݒ菈��
//============================================================
void CEnemy::SetAttack(const VECTOR3& rCurPos, const VECTOR3& rPlayerPos)
{
	// ��_�Ԃ̋������v�Z
	float fDisPlayer = sqrtf((rCurPos.x - rPlayerPos.x) * (rCurPos.x - rPlayerPos.x)
						   + (rCurPos.z - rPlayerPos.z) * (rCurPos.z - rPlayerPos.z));

	if (fDisPlayer > CHANGE_ATK)
	{ // �����ꍇ

		// �㓊���̉�
		PLAY_SOUND(CSound::LABEL_SE_THROW_TOP);

		// �㓊�����[�V�����ɂ���
		SetMotion(MOTION_ATK_UP);
	}
	else
	{ // �߂��ꍇ

		// �������̉�
		PLAY_SOUND(CSound::LABEL_SE_THROW_SIDE);
		
		// ���������[�V�����ɂ���
		SetMotion(MOTION_ATK_SIDE);
	}

	// �U����Ԃɂ���
	SetState(STATE_ATK);
}

//============================================================
//	�ҋ@��Ԏ��̍X�V����
//============================================================
CEnemy::EMotion CEnemy::UpdateIdol(const float fDeltaTime)
{
	CPlayer* pPlayer = CScene::GetPlayer();			// �v���C���[���
	VECTOR3 posPlayer = pPlayer->GetVec3Position();	// �v���C���[�ʒu
	VECTOR3 posEnemy = GetVec3Position();	// �G�ʒu
	VECTOR3 rotEnemy = GetVec3Rotation();	// �G����

	// �d�͂̍X�V
	UpdateGravity(fDeltaTime);

	// �ʒu�X�V
	UpdatePosition(&posEnemy, fDeltaTime);

	// ���n����
	UpdateLanding(&posEnemy, fDeltaTime);

	// �ʒu�␳
	CStage* pStage = GET_MANAGER->GetStage();	// �X�e�[�W���
	pStage->LimitPosition(posEnemy, RADIUS);

	// �ڕW������ݒ�
	m_destRot.y = atan2f(posEnemy.x - posPlayer.x, posEnemy.z - posPlayer.z);

	// �����X�V
	UpdateRotation(&rotEnemy, fDeltaTime);

	// �o�ߎ��Ԃ����Z
	m_fStateTime += fDeltaTime;
	if (m_fStateTime >= CalcIdolTime())
	{ // ���Ԃ��o�߂��������ꍇ

		// �W�����v��Ԃɂ���
		SetJump(posEnemy, GET_MANAGER->GetStage()->GetRandomPositionInLimit(RADIUS));
	}

	// �ʒu�𔽉f
	SetVec3Position(posEnemy);

	// �����𔽉f
	SetVec3Rotation(rotEnemy);

	// ���݂̃��[�V������Ԃ�
	return MOTION_IDOL;
}

//============================================================
//	�W�����v��Ԏ��̍X�V����
//============================================================
CEnemy::EMotion CEnemy::UpdateJump(const float fDeltaTime)
{
	VECTOR3 posEnemy = GetVec3Position();	// �G�ʒu
	VECTOR3 rotEnemy = GetVec3Rotation();	// �G����

	// �o�ߎ��Ԃ����Z
	m_fStateTime += fDeltaTime;

	// �W�����v������
	posEnemy = useful::GetParabola3D(m_jumpPosStart, m_jumpPosEnd, JUMP_HEIGHT, JUMP_TIME, m_fStateTime);
	if (m_fStateTime >= JUMP_TIME)
	{ // ���Ԃ��o�߂��������ꍇ

		// �U����Ԃɂ���
		CPlayer* pPlayer = CScene::GetPlayer();	// �v���C���[���
		SetAttack(posEnemy, pPlayer->GetVec3Position());
	}

	// �ʒu�␳
	CStage* pStage = GET_MANAGER->GetStage();	// �X�e�[�W���
	pStage->LimitPosition(posEnemy, RADIUS);

	// �ڕW������ݒ�
	m_destRot.y = atan2f(m_jumpPosStart.x - m_jumpPosEnd.x, m_jumpPosStart.z - m_jumpPosEnd.z);

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
//	�U����Ԏ��̍X�V����
//============================================================
CEnemy::EMotion CEnemy::UpdateAttack(const float fDeltaTime)
{
	CPlayer* pPlayer = CScene::GetPlayer();			// �v���C���[���
	VECTOR3 posPlayer = pPlayer->GetVec3Position();	// �v���C���[�ʒu
	VECTOR3 posEnemy = GetVec3Position();	// �G�ʒu
	VECTOR3 rotEnemy = GetVec3Rotation();	// �G����

	// �U�����[�V��������Ȃ��ꍇ�G���[
	assert(IsAttack());

	// �U��������
	if (GetMotionComboFrame() == GetMotionWholeCounter())
	{ // �R���{�t���[���̏u�Ԃ̏ꍇ

		switch (GetMotionType())
		{ // ���[�V������ނ��Ƃ̏���
		case MOTION_ATK_UP:

			// �ݒu�^�v���[���g����
			LandAttack(fDeltaTime);
			break;

		case MOTION_ATK_SIDE:

			// �e�^�v���[���g���΂�
			CPresentLand::Create(GetVec3Position(), VEC3_ZERO, CPresent::TYPE_BULLET);
			break;
		};
	}

	// �d�͂̍X�V
	UpdateGravity(fDeltaTime);

	// �ʒu�X�V
	UpdatePosition(&posEnemy, fDeltaTime);

	// ���n����
	UpdateLanding(&posEnemy, fDeltaTime);

	// �ʒu�␳
	CStage* pStage = GET_MANAGER->GetStage();	// �X�e�[�W���
	pStage->LimitPosition(posEnemy, RADIUS);

	// �ڕW������ݒ�
	m_destRot.y = atan2f(posEnemy.x - posPlayer.x, posEnemy.z - posPlayer.z);

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
// �ݒu�^�v���[���g����
//============================================================
void CEnemy::LandAttack(const float fDeltaTime)
{
	int nNum = (int)(CSceneGame::GetGameManager()->GetGameTime() / LAND_NUM_TIME);	// ���݂̌o�ߎ���

	// �ő吔��3�ɗ}����
	useful::LimitMaxNum(nNum, LAND_NUM_MAX);

	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		// �ݒu�^�v���[���g���΂�
		CPresentLand::Create(GetVec3Position(), VEC3_ZERO, 30.0f * nCnt);
	}
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

	case MOTION_ATK_UP:
	case MOTION_ATK_SIDE:

		if (IsMotionFinish())
		{ // ���[�V�������I�������ꍇ

			// �ҋ@��Ԃɂ���
			SetMotion(MOTION_IDOL, motion::BLEND_FRAME_OTHER);
			SetState(STATE_IDOL);
		}
		break;
	}
}
