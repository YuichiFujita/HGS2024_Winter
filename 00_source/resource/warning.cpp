//============================================================
//
//	�x������ [warning.cpp]
//	Author�F��������
//
//============================================================
//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "warning.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//************************************************************
//	�萔�錾
//************************************************************
namespace
{
	const char* TEXTURE_FILE = "data\\TEXTURE\\warning000.png";
	const VECTOR3 RADIUS = VECTOR3(40.0f, 40.0f, 0.0f);	// ���a

	const int PRIORITY = 4;	// �G�t�F�N�g3D�̗D�揇��
}

//************************************************************
//	�q�N���X [CWarning] �̃����o�֐�
//************************************************************
//============================================================
//	�R���X�g���N�^
//============================================================
CWarning::CWarning() : CObject3D(CObject::LABEL_EFFECT, CObject::DIM_3D, PRIORITY)
{

}

//============================================================
//	�f�X�g���N�^
//============================================================
CWarning::~CWarning()
{

}

//============================================================
//	����������
//============================================================
HRESULT CWarning::Init()
{
	// �I�u�W�F�N�g3D�̏�����
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		assert(false);
		return E_FAIL;
	}

	// �����_�[�X�e�[�g�̏����擾
	CRenderState* pRenderState = GetRenderState();

	// Z�e�X�g�̐ݒ�
	pRenderState->SetZFunc(D3DCMP_ALWAYS);

	// Z�o�b�t�@�̎g�p�󋵂̐ݒ�
	pRenderState->SetZUpdate(false);

	return S_OK;
}

//============================================================
//	�I������
//============================================================
void CWarning::Uninit()
{
	// �I�u�W�F�N�g3D�̏I��
	CObject3D::Uninit();
}

//============================================================
//	�X�V����
//============================================================
void CWarning::Update(const float fDeltaTime)
{
	// �I�u�W�F�N�g3D�̍X�V
	CObject3D::Update(fDeltaTime);
}

//============================================================
//	�`�揈��
//============================================================
void CWarning::Draw(CShader* pShader)
{
	// �I�u�W�F�N�g3D�̕`��
	CObject3D::Draw(pShader);
}

//============================================================
//	��������
//============================================================
CWarning* CWarning::Create
(
	const VECTOR3& rPos				// �ʒu
)
{
	// �G�t�F�N�g3D�̐���
	CWarning* pEffect3D = new CWarning;
	if (pEffect3D == nullptr)
	{ // �����Ɏ��s�����ꍇ

		return nullptr;
	}
	else
	{ // �����ɐ��������ꍇ

		// �G�t�F�N�g3D�̏�����
		if (FAILED(pEffect3D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �G�t�F�N�g3D�̔j��
			SAFE_DELETE(pEffect3D);
			return nullptr;
		}

		// �e�N�X�`����o�^�E����
		pEffect3D->BindTexture(GET_MANAGER->GetTexture()->Regist(TEXTURE_FILE));

		// �ʒu��ݒ�
		pEffect3D->SetVec3Position(rPos);

		// �傫����ݒ�
		pEffect3D->SetVec3Size(RADIUS);

		// �m�ۂ����A�h���X��Ԃ�
		return pEffect3D;
	}
}