//============================================================
//
//	�ݒu�^�v���[���g�w�b�_�[ [presentLand.h]
//	Author�F��������
// 
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PRESENT_LAND_H_
#define _PRESENT_LAND_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "presentCopy.h"

//************************************************************
//	�N���X��`
//************************************************************
// �ݒu�^�v���[���g�N���X
class CPresentLand : public CPresent
{
public:

	// ���f����
	enum EModel
	{
		MODEL_WAIST = 0,	// ��
		MODEL_BODY,			// ��
		MODEL_HEAD,			// ��
		MODEL_ARMUL,		// ����r
		MODEL_ARMUR,		// �E��r
		MODEL_ARMDL,		// �����r
		MODEL_ARMDR,		// �E���r
		MODEL_HANDL,		// ����
		MODEL_HANDR,		// �E��
		MODEL_LEGUL,		// ��������
		MODEL_LEGUR,		// �E������
		MODEL_LEGDL,		// ����
		MODEL_LEGDR,		// �E��
		MODEL_FOOTL,		// ����
		MODEL_FOOTR,		// �E��
		MODEL_MAX			// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CPresentLand();

	// �f�X�g���N�^
	~CPresentLand() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetEnableUpdate(const bool bUpdate) override;	// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;		// �`��󋵐ݒ�

private:
	// �����o�֐�

	// �����o�ϐ�
	CListManager<CPresent>::AIterator m_iterator;	// �C�e���[�^�[
};

#endif	// _PLAYER_H_
