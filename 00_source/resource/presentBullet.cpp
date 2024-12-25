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
#include "particle3D.h"
#include "collision.h"
#include "effect3D.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* MODEL = "data\\MODEL\\PRESENT\\PresentBag.x";	// ���f��
	const float	RADIUS = 50.0f;	// ���a
	const float HEIGHT = 80.0f;	// �g��
	const float SPEED = 570.0f;	// ���x
	const float	REV_ROTA = 0.06f;	// �����ύX�̕␳�W��
	const float SUB_SPEED = 230.0f;	// ���x�̌��Z��

	// �ړ����
	namespace move
	{
		const float TIME = 1.0f;	// �ړ���Ԃ̎���
	}

	// �G�t�F�N�g
	namespace effect
	{
		const float RADIUS = 20.0f;		// ���a
		const int LIFE = 10;			// ����
		const float SUB_SIZE = 0.1f;	// ���a�̌��Z��
	}
}

//************************************************************
// �ÓI�����o�ϐ��錾
//************************************************************
CPresentBullet::AFuncState CPresentBullet::m_aFuncState[] =		// ��ԍX�V�֐����X�g
{
	&CPresentBullet::UpdateHoming,		// �z�[�~���O���
	&CPresentBullet::UpdateMove,		// �ړ����
	&CPresentBullet::UpdateDeath,		// ���S���
};

//************************************************************
//	�q�N���X [CPresentBullet] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CPresentBullet::CPresentBullet() : CPresent(),
m_state(STATE_HOMING),	// ���
m_destRot(VEC3_ZERO),	// �ړI�̌���
m_fStateTime(0.0f),		// ��Ԏ���
m_fSpeed(0.0f)			// ���x
{
	// �X�^�e�B�b�N�A�T�[�g
	static_assert(NUM_ARRAY(m_aFuncState) == CPresentBullet::STATE_MAX, "ERROR : State Count Mismatch");
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
	m_fStateTime = 1.0f;	// ��Ԏ���
	m_fSpeed = SPEED;		// ���x

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
	// ��ԏ���
	(this->*(m_aFuncState[m_state]))(fDeltaTime);

	// �����蔻��
	Collision();
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
// ��������
//============================================================
CPresentBullet* CPresentBullet::Create
( // ����
	const VECTOR3& rPos,	// �ʒu
	const float fRotY		// ����
)
{
	// �v���[���g�̐���
	CPresentBullet* pPresent = new CPresentBullet;

	if (pPresent == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �v���[���g�̏�����
		if (FAILED(pPresent->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �v���[���g�̔j��
			SAFE_DELETE(pPresent);
			return nullptr;
		}

		// �ʒu��ݒ�
		pPresent->SetVec3Position(rPos);

		// ������ݒ�
		pPresent->SetVec3Rotation(VECTOR3(0.0f, fRotY, 0.0f));

		// �m�ۂ����A�h���X��Ԃ�
		return pPresent;
	}
}

//============================================================
// �����蔻��
//============================================================
void CPresentBullet::Collision()
{
	// �v���C���[�����Ȃ��ꍇ�A������
	CPlayer* pPlayer = CScene::GetPlayer();
	if (pPlayer == nullptr) { return; }

	// �ʒu��ݒ肷��
	VECTOR3 pos = GetVec3Position();
	VECTOR3 sizeMaxPlayer = VECTOR3(pPlayer->GetRadius(), pPlayer->GetHeight(), pPlayer->GetRadius());
	VECTOR3 sizeMinPlayer = VECTOR3(pPlayer->GetRadius(), 0.0f, pPlayer->GetRadius());

	if (collision::Box3D(pos, pPlayer->GetVec3Position(), sizeMaxPlayer, GetModelData().vtxMax, sizeMinPlayer, -GetModelData().vtxMin))
	{ // ���������ꍇ

		// �q�b�g����
		pPlayer->Hit();
	}
}

//============================================================
// �z�[�~���O����
//============================================================
void CPresentBullet::UpdateHoming(const float fDeltaTime)
{
	// ��Ԏ��Ԃ�0�����̏ꍇ�A�ړ���Ԃɂ���
	if (m_fStateTime <= 0.0f) { m_fStateTime = 0.0f; m_state = STATE_MOVE; return; }

	// �v���C���[�� NULL �̏ꍇ�A������
	CPlayer* pPlayer = CScene::GetPlayer();
	if (pPlayer == nullptr) { return; }

	// �ړI�̈ʒu��ݒ肷��
	VECTOR3 posPlayer = pPlayer->GetVec3Position();

	// �ړI�̌�����ݒ肷��
	D3DXVECTOR3 pos = GetVec3Position();
	D3DXVECTOR3 rot = GetVec3Rotation();
	m_destRot.y = atan2f(posPlayer.x - pos.x, posPlayer.z - pos.z);

	// �ʒu���ړ�����
	pos.x += sinf(rot.y) * m_fSpeed * fDeltaTime;
	pos.z += cosf(rot.y) * m_fSpeed * fDeltaTime;
	SetVec3Position(pos);

	// �����̍X�V����
	UpdateRotation(fDeltaTime);

	// ��Ԏ��Ԃ����Z����
	m_fStateTime -= fDeltaTime;

	// �G�t�F�N�g�𐶐�����
	CEffect3D::Create(pos, effect::RADIUS, CEffect3D::TYPE_NORMAL, effect::LIFE, VECTOR3(), VECTOR3(), color::Purple(), effect::SUB_SIZE);
}

//============================================================
// �ړ�����
//============================================================
void CPresentBullet::UpdateMove(const float fDeltaTime)
{
	// ��Ԏ��Ԃ𑪂�
	m_fStateTime += fDeltaTime;

	// �����̍X�V����
	UpdateRotation(fDeltaTime);

	// �ʒu���ړ�����
	D3DXVECTOR3 pos = GetVec3Position();
	D3DXVECTOR3 rot = GetVec3Rotation();
	pos.x += sinf(rot.y) * m_fSpeed * fDeltaTime;
	pos.z += cosf(rot.y) * m_fSpeed * fDeltaTime;
	SetVec3Position(pos);

	if (m_fStateTime >= move::TIME)
	{ // ��莞�Ԍo�߂����ꍇ

		// ��Ԏ��Ԃ����Z�b�g����
		m_fStateTime = 0.0f;

		// ���S��Ԃɂ���
		m_state = STATE_DEATH;
	}

	// �G�t�F�N�g�𐶐�����
	CEffect3D::Create(pos, effect::RADIUS, CEffect3D::TYPE_NORMAL, effect::LIFE, VECTOR3(), VECTOR3(), color::Purple(), effect::SUB_SIZE);
}

//============================================================
// ���S����
//============================================================
void CPresentBullet::UpdateDeath(const float fDeltaTime)
{
	// ���x�������Ă���
	m_fSpeed -= SUB_SPEED * fDeltaTime;

	// �ʒu���ړ�����
	D3DXVECTOR3 pos = GetVec3Position();
	D3DXVECTOR3 rot = GetVec3Rotation();
	pos.x += sinf(rot.y) * m_fSpeed * fDeltaTime;
	pos.z += cosf(rot.y) * m_fSpeed * fDeltaTime;
	SetVec3Position(pos);

	if (m_fSpeed > 0.0f) { return; }

	// ����������
	CParticle3D::Create(CParticle3D::TYPE_SMALL_EXPLOSION, GetVec3Position());

	// �I������
	Uninit();
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
