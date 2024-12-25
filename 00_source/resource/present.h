//============================================================
//
//	�v���[���g�w�b�_�[ [present.h]
//	Author�F��������
// 
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _PRESENT_H_
#define _PRESENT_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectModel.h"

//************************************************************
//	�N���X��`
//************************************************************
// �v���[���g�N���X
class CPresent : public CObjectModel
{
public:

	// ���
	enum EType
	{
		TYPE_LAND = 0,	// �ݒu�^
		TYPE_BULLET,	// �e�^
		TYPE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CPresent();

	// �f�X�g���N�^
	~CPresent() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetEnableUpdate(const bool bUpdate) override;	// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;		// �`��󋵐ݒ�
	virtual float GetRadius() const = 0;				// ���a�擾
	virtual float GetHeight() const = 0;				// �c���擾

	// �ÓI�����o�֐�
	static CListManager<CPresent>* GetList();	// ���X�g�擾

	// �����o�֐�

private:
	// �����o�֐�

	// �ÓI�����o�ϐ�
	static CListManager<CPresent>* m_pList;	// �I�u�W�F�N�g���X�g

	// �����o�ϐ�
	CListManager<CPresent>::AIterator m_iterator;	// �C�e���[�^�[
	EType m_type;									// ���
};

#endif	// _PRESENT_H_
