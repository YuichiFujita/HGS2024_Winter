//============================================================
//
//	�x���w�b�_�[ [warning.h]
//	Author�F��������
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _WARNING_H_
#define _WARNING_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object3D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �x���N���X
class CWarning : public CObject3D
{
public:
	// �R���X�g���N�^
	CWarning();

	// �f�X�g���N�^
	~CWarning() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CWarning* Create(const VECTOR3& rPos);

private:
	// �����o�ϐ�
};

#endif	// _WARNING_H_
