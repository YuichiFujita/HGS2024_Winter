//============================================================
//
//	���e�w�b�_�[ [bomb.h]
//	Author�F��������
// 
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _BOMB_H_
#define _BOMB_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectModel.h"

//************************************************************
//	�N���X��`
//************************************************************
// ���e�N���X
class CBomb : public CObjectModel
{
public:

	// �R���X�g���N�^
	CBomb();

	// �f�X�g���N�^
	~CBomb() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetEnableUpdate(const bool bUpdate) override;	// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;		// �`��󋵐ݒ�
	float GetRadius() const;							// ���a�擾

	// �ÓI�����o�֐�
	static CBomb* Create(const VECTOR3& rPos);	// ����
	static CListManager<CBomb>* GetList();	// ���X�g�擾

private:

	// �����o�֐�
	void SetDestPos();	// �ړI�ʒu�̐ݒ菈��
	bool FieldCollision();	// �t�B�[���h�̓����蔻��
	void Fly(const float fDeltaTime);	// ��s����

	// �ÓI�����o�ϐ�
	static CListManager<CBomb>* m_pList;	// �I�u�W�F�N�g���X�g

	// �����o�ϐ�
	CListManager<CBomb>::AIterator m_iterator;	// �C�e���[�^�[
	float m_fFlyTime;	// ��Ԏ���
	VECTOR3	m_oldPos;	// �ߋ��ʒu
	VECTOR3 m_originPos;	// �����ʒu
	VECTOR3 m_destPos;	// �ړI�ʒu
};

#endif	// _PRESENT_H_
