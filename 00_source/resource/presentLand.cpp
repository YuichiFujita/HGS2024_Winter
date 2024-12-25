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
}

//************************************************************
//	�q�N���X [CPresentLand] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CPresentLand::CPresentLand() : CPresent(),
m_destPos(VEC3_ZERO),	// �ړI�̈ʒu
m_state(STATE_NONE)		// ���
{

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
	UpdateState();
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
// ��ԏ���
//============================================================
void CPresentLand::UpdateState(void)
{
	switch (m_state)
	{
	case CPresentLand::STATE_NONE:

		break;

	case CPresentLand::STATE_FLY:

		UpdateFly();
		break;

	case CPresentLand::STATE_FALL:

		UpdateFall();
		break;

	default:

		assert(false);
		break;
	}
}

//============================================================
// ��я�Ԃ̏���
//============================================================
void CPresentLand::UpdateFly(void)
{
	CPlayer* pPlayer = CScene::GetPlayer();

	if (pPlayer == nullptr) { return; }

	// �ړI�̈ʒu��ݒ肷��
	m_destPos = pPlayer->GetVec3Position();

	// �ړI�̍������Đݒ肷��
	m_destPos.y = 600.0f;
}

//============================================================
// ������Ԃ̏���
//============================================================
void CPresentLand::UpdateFall(void)
{

}
