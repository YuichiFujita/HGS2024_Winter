//============================================================
//
//	�A�N�^�[���� [actor.cpp]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "actor.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	// ���f�����\����
	struct SModelInfo
	{
		// �f�t�H���g�R���X�g���N�^
		SModelInfo() :
			pFilePath	(nullptr),	// �t�@�C���p�X
			fRadius		(0.0f)		// ���蔼�a
		{}

		// �����t���R���X�g���N�^
		SModelInfo(const char* in_pFilePath, const float in_fRadius) :
			pFilePath	(in_pFilePath),	// �t�@�C���p�X
			fRadius		(in_fRadius)	// ���蔼�a
		{}

		// �f�X�g���N�^
		~SModelInfo() {}

		// �����o�ϐ�
		const char* pFilePath;	// �t�@�C���p�X
		float fRadius;			// ���蔼�a
	};
	const SModelInfo MODEL_FILE[] =	// �T�E���h�t�@�C��
	{
		SModelInfo("data\\MODEL\\ACTOR\\wood000.x", 30.0f),		// ��00
		SModelInfo("data\\MODEL\\ACTOR\\stone000.x", 30.0f),	// ��00
	};

	const int PRIORITY = 3;	// �A�N�^�[�̗D�揇��
}

//************************************************************
//	�ÓI�����o�ϐ��錾
//************************************************************
CListManager<CActor>* CActor::m_pList = nullptr;	// �I�u�W�F�N�g���X�g

//************************************************************
//	�q�N���X [CActor] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CActor::CActor() : CObjectModel(CObject::LABEL_ACTOR, CObject::DIM_3D, PRIORITY),
	m_type	(TYPE_WOOD)	// ���
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CActor::~CActor()
{

}

//============================================================
//	����������
//============================================================
HRESULT CActor::Init()
{
	// �����o�ϐ���������
	m_type = TYPE_WOOD;	// ���

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
		m_pList = CListManager<CActor>::Create();
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
void CActor::Uninit()
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
void CActor::Update(const float fDeltaTime)
{

}

//============================================================
//	�`�揈��
//============================================================
void CActor::Draw(CShader* pShader)
{
	// �I�u�W�F�N�g�L�����N�^�[�̕`��
	CObjectModel::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CActor* CActor::Create
(
	const EType type,		// ���
	const VECTOR3& rPos,	// �ʒu
	const VECTOR3& rRot,	// ����
	const VECTOR3& rScale	// �g�嗦
)
{
	// �A�N�^�[�̐���
	CActor* pActor = new CActor;
	if (pActor == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �A�N�^�[�̏�����
		if (FAILED(pActor->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �A�N�^�[�̔j��
			SAFE_DELETE(pActor);
			return nullptr;
		}

		// ��ނ�ݒ�
		pActor->SetType(type);

		// �ʒu��ݒ�
		pActor->SetVec3Position(rPos);

		// ������ݒ�
		pActor->SetVec3Rotation(rRot);

		// �g�嗦��ݒ�
		pActor->SetVec3Scale(rScale);

		// �m�ۂ����A�h���X��Ԃ�
		return pActor;
	}
}

//============================================================
//	���X�g�擾����
//============================================================
CListManager<CActor>* CActor::GetList()
{
	// �I�u�W�F�N�g���X�g��Ԃ�
	return m_pList;
}

//============================================================
//	��ނ̐ݒ菈��
//============================================================
void CActor::SetType(const EType type)
{
	// ��ނ�ۑ�
	m_type = type;

	// ���f���̊���
	BindModel(MODEL_FILE[m_type].pFilePath);
}

//============================================================
//	���a�̎擾����
//============================================================
float CActor::GetRadius() const
{
	// ���a��Ԃ�
	return MODEL_FILE[m_type].fRadius;
}
