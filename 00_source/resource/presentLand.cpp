//============================================================
//
//	�ݒu�^�v���[���g���� [presentLand.cpp]
//	Author�F��������
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "presentLand.h"
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
#include "enemy.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* MODEL = "data\\MODEL\\PLAYER\\02_head.x";	// ���f���̏��
	const float	GRAVITY = 0.6f;	// �d��
	const float	RADIUS = 20.0f;	// ���a
	const float HEIGHT = 80.0f;	// �g��

	// ��s��Ԃ̒萔
	namespace fly
	{
		const float HEIGHT = 200.0f;	// ����
		const float END_TIME = 1.0f;	// �I���܂ł̎���
		const float ALPHA = 0.5f;	// �����x
	}
}

//************************************************************
// �ÓI�����o�ϐ��錾
//************************************************************
CPresentLand::AFuncState CPresentLand::m_aFuncState[] =		// ��ԍX�V�֐����X�g
{
	&CPresentLand::UpdateNone,	// ������Ԃ̍X�V
	&CPresentLand::UpdateFly,	// ��я�Ԃ̍X�V
	& CPresentLand::UpdateStop,	// ��~��Ԃ̍X�V
};

//************************************************************
//	�q�N���X [CPresentLand] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CPresentLand::CPresentLand() : CPresent(),
m_fFlyTime(0.0f),	// ��Ԏ���
m_oldPos(VEC3_ZERO),	// �ߋ��ʒu
m_originPos(VEC3_ZERO),	// �����ʒu
m_destPos(VEC3_ZERO),	// �ړI�̈ʒu
m_move(VEC3_ZERO),	// �ړ���
m_state(STATE_NONE)	// ���
{
	// �X�^�e�B�b�N�A�T�[�g
	static_assert(NUM_ARRAY(m_aFuncState) == CPresentLand::STATE_MAX, "ERROR : State Count Mismatch");
}

//============================================================
//	�f�X�g���N�^
//============================================================
CPresentLand::~CPresentLand()
{

}

//============================================================
//	����������
//============================================================
HRESULT CPresentLand::Init()
{
	m_oldPos = VEC3_ZERO;	// �ߋ��ʒu
	m_destPos = VEC3_ZERO;	// �ړI�̈ʒu
	m_move = VEC3_ZERO;		// �ړ���
	m_state = STATE_NONE;	// ���

	// �I�u�W�F�N�g�L�����N�^�[�̏�����
	if (FAILED(CPresent::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���f���̊��蓖�ď���
	BindModel(MODEL);

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CPresentLand::Uninit()
{
	// �I�u�W�F�N�g�L�����N�^�[�̏I��
	CPresent::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CPresentLand::Update(const float fDeltaTime)
{
	// ���x��������
	SpeedCalc();

	// ��ԏ���
	(this->*(m_aFuncState[m_state]))(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CPresentLand::Draw(CShader* pShader)
{
	// �I�u�W�F�N�g�L�����N�^�[�̕`��
	CPresent::Draw(pShader);
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CPresentLand::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);	// ���g
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CPresentLand::SetEnableDraw(const bool bDraw)
{
	// �����̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);	// ���g
}

//============================================================
// ���a�擾
//============================================================
float CPresentLand::GetRadius() const
{
	// ���a��Ԃ�
	return RADIUS;
}

//============================================================
// �c���擾
//============================================================
float CPresentLand::GetHeight() const
{
	// ������Ԃ�
	return HEIGHT;
}

//============================================================
// ���x�v�Z����
//============================================================
void CPresentLand::SpeedCalc()
{

}

//============================================================
// �t�B�[���h�̓����蔻��
//============================================================
bool CPresentLand::FieldCollision()
{
	CStage* pStage = GET_MANAGER->GetStage();	// �X�e�[�W���
	VECTOR3 pos = GetVec3Position();	// �ʒu

	// �n�ʁE�����ʒu���n����
	if (pStage->LandFieldPosition(pos, m_oldPos, m_move)
		|| pStage->LandLimitPosition(pos, m_move, 0.0f))
	{ // �v���C���[�����n���Ă����ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//============================================================
// ������ԏ���
//============================================================
void CPresentLand::UpdateNone(const float fDeltaTime)
{
	// �����ʒu��ݒ肷��
	m_originPos = GetVec3Position();

	// �v���C���[�����Ȃ��ꍇ�A������
	CPlayer* pPlayer = CScene::GetPlayer();
	if (pPlayer == nullptr) { return; }

	// �ړI�̈ʒu��ݒ肷��
	m_destPos = pPlayer->GetVec3Position();

	// ��я�Ԃɂ���
	m_state = STATE_FLY;
}

//============================================================
// ��я�ԏ���
//============================================================
void CPresentLand::UpdateFly(const float fDeltaTime)
{
	D3DXVECTOR3 pos = GetVec3Position();

	// ����������
	pos = useful::GetParabola3D(m_originPos, m_destPos, fly::HEIGHT, fly::END_TIME, m_fFlyTime);

	// ���ł��鎞�Ԃ��X�V
	m_fFlyTime += fDeltaTime;

	// ���n�����Ƃ��A��~��Ԃɂ���
	if (FieldCollision()) { m_state = STATE_STOP; }

	// �ʒu�𔽉f����
	SetVec3Position(pos);
}

//============================================================
// ��~��ԏ���
//============================================================
void CPresentLand::UpdateStop(const float fDeltaTime)
{
	// �t�B�[���h�̓����蔻��
	FieldCollision();
}
