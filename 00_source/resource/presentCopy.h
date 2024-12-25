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
#include "objectChara.h"

//************************************************************
//	�N���X��`
//************************************************************
// �v���[���g�N���X
class CPresent : public CObjectChara
{
public:

	// ���
	enum EType
	{
		TYPE_LAND = 0,	// �ݒu�^
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

	// �ÓI�����o�֐�
	static CPresent* Create	// ����
	( // ����
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rRot,	// ����
		const EType type		// ���
	);
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

#endif	// _PLAYER_H_
