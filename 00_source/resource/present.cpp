//============================================================
//
//	�v���[���g���� [present.cpp]
//	Author�F��������
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "present.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "camera.h"
#include "texture.h"
#include "fade.h"
#include "stage.h"
#include "sceneGame.h"
#include "gameManager.h"

#include "presentLand.h"
#include "presentBullet.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const int	PRIORITY = 3;		// �v���[���g�̗D�揇��
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CListManager<CPresent>* CPresent::m_pList = nullptr;	// �I�u�W�F�N�g���X�g

//************************************************************
//	�q�N���X [CPresent] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CPresent::CPresent() : CObjectModel(CObject::LABEL_PRESENT, CObject::DIM_3D, PRIORITY),
m_type(TYPE_LAND)		// ���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CPresent::~CPresent()
{

}

//============================================================
//	����������
//============================================================
HRESULT CPresent::Init()
{
	m_type = TYPE_LAND;		// ���

	// �I�u�W�F�N�g�L�����N�^�[�̏�����
	if (FAILED(CObjectModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		assert(false);
		return E_FAIL;
	}

	if (m_pList == nullptr)
	{ // ���X�g�}�l�[�W���[�����݂��Ȃ��ꍇ

		// ���X�g�}�l�[�W���[�̐���
		m_pList = CListManager<CPresent>::Create();
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
void CPresent::Uninit()
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
void CPresent::Update(const float fDeltaTime)
{

}

//============================================================
//	�`�揈��
//============================================================
void CPresent::Draw(CShader* pShader)
{
	// �I�u�W�F�N�g�L�����N�^�[�̕`��
	CObjectModel::Draw(pShader);
}

//============================================================
//	�X�V�󋵂̐ݒ菈��
//============================================================
void CPresent::SetEnableUpdate(const bool bUpdate)
{
	// �����̍X�V�󋵂�ݒ�
	CObject::SetEnableUpdate(bUpdate);	// ���g
}

//============================================================
//	�`��󋵂̐ݒ菈��
//============================================================
void CPresent::SetEnableDraw(const bool bDraw)
{
	// �����̕`��󋵂�ݒ�
	CObject::SetEnableDraw(bDraw);	// ���g
}

//============================================================
//	��������
//============================================================
CPresent* CPresent::Create
(
	const VECTOR3& rPos,	// �ʒu
	const VECTOR3& rRot,	// ����
	const EType type		// ���
)
{
	// �v���[���g�̐���
	CPresent* pPresent = nullptr;

	switch (type)
	{
	case CPresent::TYPE_LAND:

		// �ݒu�^�v���[���g�𐶐�
		pPresent = new CPresentLand;

		break;

	case CPresent::TYPE_BULLET:

		// �e���v���[���g�𐶐�
		pPresent = new CPresentBullet;

		break;

	default:

		// ��~
		assert(false);

		break;
	}

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
		pPresent->SetVec3Rotation(rRot);

		// �m�ۂ����A�h���X��Ԃ�
		return pPresent;
	}
}

//============================================================
//	���X�g�擾����
//============================================================
CListManager<CPresent>* CPresent::GetList()
{
	// �I�u�W�F�N�g���X�g��Ԃ�
	return m_pList;
}