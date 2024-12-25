//============================================================
//
//	�e�^�v���[���g�w�b�_�[ [presentBullet.h]
//	Author�F��������
// 
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PRESENT_BULLET_H_
#define _PRESENT_BULLET_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "present.h"

//************************************************************
//	�N���X��`
//************************************************************
// �e�^�v���[���g�N���X
class CPresentBullet : public CPresent
{
public:

	// �R���X�g���N�^
	CPresentBullet();

	// �f�X�g���N�^
	~CPresentBullet() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetEnableUpdate(const bool bUpdate) override;	// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;		// �`��󋵐ݒ�
	float GetRadius() const override;					// ���a�擾
	float GetHeight() const override;					// �c���擾

private:
	// �����o�֐�


	// �����o�ϐ�
};

#endif	// _PLAYER_H_
