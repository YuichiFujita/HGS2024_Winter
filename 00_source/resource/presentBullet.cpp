//============================================================
//
//	�e�^�v���[���g���� [presentBullet.cpp]
//	Author�F��������
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "presentBullet.h"
#include "main.h"
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
	const char* MODEL = "data\\MODEL\\PLAYER\\01_body.x";	// ���f��
	const float SPEED = 500.0f;	// ���x
	const float	RADIUS = 20.0f;	// ���a
	const float HEIGHT = 80.0f;	// �g��
	const float	REV_ROTA = 0.04f;	// �����ύX�̕␳�W��
}

//************************************************************
//	�q�N���X [CPresentBullet] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CPresentBullet::CPresentBullet() : CPresent(),
m_destPos(VEC3_ZERO),	// �ړI�̈ʒu
m_fHomingTime(0.0f)	// �z�[�~���O���鎞��
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CPresentBullet::~CPresentBullet()
{

}

//============================================================
//	����������
//============================================================
HRESULT CPresentBullet::Init()
{
	m_fHomingTime = 1.0f;	// �z�[�~���O���鎞��

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
void CPresentBullet::Uninit()
{
	// �I�u�W�F�N�g�L�����N�^�[�̏I��
	CPresent::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CPresentBullet::Update(const float fDeltaTime)
{
	// �z�[�~���O����
	Homing(fDeltaTime);

	// �����̍X�V����
	UpdateRotation(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CPresentBullet::Draw(CShader* pShader)
{
	// �I�u�W�F�N�g�L�����N�^�[�̕`��
	CPresent::Draw(pShader);
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CPresentBullet::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);	// ���g
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CPresentBullet::SetEnableDraw(const bool bDraw)
{
	// �����̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);	// ���g
}

//============================================================
// ���a�擾
//============================================================
float CPresentBullet::GetRadius() const
{
	// ���a��Ԃ�
	return RADIUS;
}

//============================================================
// �c���擾
//============================================================
float CPresentBullet::GetHeight() const
{
	// ������Ԃ�
	return HEIGHT;
}

//============================================================
// �z�[�~���O����
//============================================================
void CPresentBullet::Homing(const float fDeltaTime)
{
	// �z�[�~���O�^�C����0�����̏ꍇ�A������
	if (m_fHomingTime < 0.0f) { return; }

	// �v���C���[�� NULL �̏ꍇ�A������
	CPlayer* pPlayer = CScene::GetPlayer();
	if (pPlayer == nullptr) { return; }

	// �ړI�̈ʒu��ݒ肷��
	m_destPos = pPlayer->GetVec3Position();

	// �ړI�̌�����ݒ肷��
	D3DXVECTOR3 pos = GetVec3Position();
	D3DXVECTOR3 rot = GetVec3Rotation();
	m_destRot.y = atan2f(m_destPos.x - pos.x, m_destPos.z - pos.z);

	// �ʒu���ړ�����
	pos.x += sinf(rot.y) * SPEED * fDeltaTime;
	pos.z += cosf(rot.y) * SPEED * fDeltaTime;
	SetVec3Position(pos);
}

//============================================================
// �����̍X�V����
//============================================================
void CPresentBullet::UpdateRotation(const float fDeltaTime)
{
	VECTOR3 rot = GetVec3Rotation();
	float fDeltaRate = fDeltaTime / (1.0f / (float)main::FPS);	// �o�ߎ��Ԃ̊���
	float fDiffRot = 0.0f;	// ��������

	// �ڕW�����̐��K��
	useful::NormalizeRot(m_destRot.y);

	// �ڕW�����܂ł̍������v�Z
	fDiffRot = m_destRot.y - rot.y;

	// ���������̐��K��
	useful::NormalizeRot(fDiffRot);

	// �����̍X�V
	rot.y += fDiffRot * REV_ROTA * fDeltaRate;

	// �����̐��K��
	useful::NormalizeRot(rot.y);

	// �����𔽉f
	SetVec3Rotation(rot);
}
