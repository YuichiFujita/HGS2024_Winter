//============================================================
//
//	�ݒu�^�v���[���g���� [presentLand.cpp]
//	Author�F��������
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
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

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const float	GRAVITY = 3600.0f;	// �d��
	const float	RADIUS = 20.0f;	// ���a
	const float HEIGHT = 80.0f;	// �g��

	// ��s��Ԃ̒萔
	namespace fly
	{
		const float DEST_POS_Y = 600.0f;	// �ړI�̍���
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
	&CPresentLand::UpdateFall,	// ������Ԃ̍X�V
};

//************************************************************
//	�q�N���X [CPresentLand] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CPresentLand::CPresentLand() : CPresent(),
m_destPos(VEC3_ZERO),	// �ړI�̈ʒu
m_move(VEC3_ZERO),		// �ړ���
m_state(STATE_NONE)		// ���
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
// ������ԏ���
//============================================================
void CPresentLand::UpdateNone(const float fDeltaTime)
{
	// �v���C���[�����Ȃ��ꍇ�A������
	CPlayer* pPlayer = CScene::GetPlayer();
	if (pPlayer == nullptr) { return; }

	// �ړI�̈ʒu��ݒ肷��
	m_destPos = pPlayer->GetVec3Position();

	// �������Đݒ肷��
	m_destPos.y = fly::DEST_POS_Y;

	// ��я�Ԃɂ���
	m_state = STATE_FLY;
}

//============================================================
// ��я�ԏ���
//============================================================
void CPresentLand::UpdateFly(const float fDeltaTime)
{
	CPlayer* pPlayer = CScene::GetPlayer();

	if (pPlayer == nullptr) { return; }

	// �ړI�̈ʒu��ݒ肷��
	m_destPos = pPlayer->GetVec3Position();

	// �ړI�̍������Đݒ肷��
	m_destPos.y = fly::DEST_POS_Y;

	// �����x��ݒ肷��
	SetAlpha(fly::ALPHA);
}

//============================================================
// ������ԏ���
//============================================================
void CPresentLand::UpdateFall(const float fDeltaTime)
{
	D3DXVECTOR3 pos = GetVec3Position();

	// �d�͂�������
	m_move.y += GRAVITY * fDeltaTime;

	// �ړ�����
	pos += m_move;

	// �ʒu��ݒ肷��
	SetVec3Position(pos);
}
