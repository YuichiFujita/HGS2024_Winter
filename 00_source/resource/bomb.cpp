//============================================================
//
//	���e���� [present.cpp]
//	Author�F��������
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "bomb.h"
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

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* MODEL = "data\\MODEL\\PLAYER\\01_body.x";	// ���f��
	const int	PRIORITY = 3;	// ���e�̗D�揇��
	const float	DEST_RANGE = 100.0f;	// �ړI�ʒu�͈̔�
	const float RADIUS = 60.0f;	// ���a
	const float FLY_HEIGHT = 90.0f;	// ��ԂƂ��̍ō����B�_
	const float FLY_TIME = 1.0f;	// ��Ԏ���
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CListManager<CBomb>* CBomb::m_pList = nullptr;	// �I�u�W�F�N�g���X�g

//************************************************************
//	�q�N���X [CBomb] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CBomb::CBomb() : CObjectModel(CObject::LABEL_BOMB, CObject::DIM_3D, PRIORITY),
m_fFlyTime(0.0f),	// ��Ԏ���
m_oldPos(VEC3_ZERO),	// �ߋ��ʒu
m_originPos(VEC3_ZERO),	// �����ʒu
m_destPos(VEC3_ZERO)	// �ړI�ʒu
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CBomb::~CBomb()
{

}

//============================================================
//	����������
//============================================================
HRESULT CBomb::Init()
{
	m_fFlyTime = 0.0f;	// ��Ԏ���
	m_oldPos = VEC3_ZERO;	// �ߋ��ʒu
	m_originPos = VEC3_ZERO;	// �����ʒu
	m_destPos = VEC3_ZERO;	// �ړI�ʒu

	// �I�u�W�F�N�g�L�����N�^�[�̏�����
	if (FAILED(CObjectModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	// ���f���̊��蓖�ď���
	BindModel(MODEL);

	if (m_pList == nullptr)
	{ // ���X�g�}�l�[�W���[�����݂��Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̐���
		m_pList = CListManager<CBomb>::Create();
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
void CBomb::Uninit()
{
	// ���X�g���玩�g�̃I�u�W�F�N�g���폜
	m_pList->DelList(m_iterator);

	if (m_pList->GetNumAll() == 0)
	{ // �I�u�W�F�N�g������Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̔j��
		m_pList->Release(m_pList);
	}

	// �I�u�W�F�N�g�L�����N�^�[�̏I��
	CObjectModel::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CBomb::Update(const float fDeltaTime)
{
	// ���������ꍇ�A�j������
	if (Fly(fDeltaTime)) { Uninit(); return; }

	// �n�ʂƂ̓����蔻��
	FieldCollision();
}

//============================================================
//	�`�揈��
//============================================================
void CBomb::Draw(CShader* pShader)
{
	// �I�u�W�F�N�g�L�����N�^�[�̕`��
	CObjectModel::Draw(pShader);
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CBomb::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);	// ���g
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CBomb::SetEnableDraw(const bool bDraw)
{
	// �����̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);	// ���g
}

//============================================================
// ���a�擾
//============================================================
float CBomb::GetRadius() const
{
	// ���a��Ԃ�
	return RADIUS;
}

//============================================================
//	��������
//============================================================
CBomb* CBomb::Create(const VECTOR3& rPos)
{
	// ���e�̐���
	CBomb* pPresent = new CBomb;

	if (pPresent == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// ���e�̏�����
		if (FAILED(pPresent->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ���e�̔j��
			SAFE_DELETE(pPresent);
			return nullptr;
		}

		// �ʒu��ݒ�
		pPresent->SetVec3Position(rPos);
		pPresent->m_originPos = rPos;

		// �ړI�ʒu�ݒ菈��
		pPresent->SetDestPos();

		// �m�ۂ����A�h���X��Ԃ�
		return pPresent;
	}
}

//============================================================
//	���X�g�擾����
//============================================================
CListManager<CBomb>* CBomb::GetList()
{
	// �I�u�W�F�N�g���X�g��Ԃ�
	return m_pList;
}

//============================================================
// �ړI�ʒu�̐ݒ菈��
//============================================================
void CBomb::SetDestPos()
{
	// �ړI�̈ʒu��ݒ�
	VECTOR3 pos = GetVec3Position();
	m_destPos.x = pos.x + sinf(useful::RandomRot()) * DEST_RANGE;
	m_destPos.y = 0.0f;
	m_destPos.z = pos.z + cosf(useful::RandomRot()) * DEST_RANGE;
}

//============================================================
// �t�B�[���h�̓����蔻��
//============================================================
void CBomb::FieldCollision()
{
	CStage* pStage = GET_MANAGER->GetStage();	// �X�e�[�W���
	VECTOR3 pos = GetVec3Position();	// �ʒu
	VECTOR3 move = VEC3_ZERO;			// �����p�ϐ�

	// �n�ʁE�����ʒu���n����
	if (pStage->LandFieldPosition(pos, m_oldPos, move)
		|| pStage->LandLimitPosition(pos, move, 0.0f))
	{ // �v���C���[�����n���Ă����ꍇ

		// �ʒu�𔽉f
		SetVec3Position(pos);
	}
}

//============================================================
// ��s����
//============================================================
bool CBomb::Fly(const float fDeltaTime)
{
	D3DXVECTOR3 pos = GetVec3Position();	// ���݂̈ʒu
	D3DXVECTOR3 posOld = GetVec3Position();	// �ۑ��p�̈ʒu

	// ����������
	pos = useful::GetParabola3D(m_originPos, m_destPos, m_destPos.y + FLY_HEIGHT, FLY_TIME, m_fFlyTime);

	if (pos.y < posOld.y)
	{ // ������n�߂��Ƃ�

		// �����̃p�[�e�B�N�����o��
		CParticle3D::Create(CParticle3D::TYPE_SMALL_EXPLOSION, pos);
		return true;
	}

	// ���ł��鎞�Ԃ��X�V
	m_fFlyTime += fDeltaTime;

	// �ʒu�𔽉f����
	SetVec3Position(pos);

	return false;
}
