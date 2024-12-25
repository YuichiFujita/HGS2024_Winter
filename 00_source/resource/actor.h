//============================================================
//
//	�A�N�^�[�w�b�_�[ [actor.h]
//	Author�F���c�E��
// 
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _ACTOR_H_
#define _ACTOR_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectModel.h"

//************************************************************
//	�N���X��`
//************************************************************
// �A�N�^�[�N���X
class CActor : public CObjectModel
{
public:
	// ��ޗ�
	enum EType
	{
		TYPE_WOOD = 0,	// ��
		TYPE_STONE,		// ��
		TYPE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CActor();

	// �f�X�g���N�^
	~CActor() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CActor* Create	// ����
	( // ����
		const EType type,		// ���
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rRot,	// ����
		const VECTOR3& rScale	// �g�嗦
	);
	static CListManager<CActor>* GetList();	// ���X�g�擾

	// �����o�֐�
	void SetType(const EType type);	// ��ސݒ�
	float GetRadius() const;		// ���a�擾
	inline EType GetType() const	{ return m_type; }	// ��ގ擾

private:
	// �ÓI�����o�ϐ�
	static CListManager<CActor>* m_pList;	// �I�u�W�F�N�g���X�g

	// �����o�ϐ�
	CListManager<CActor>::AIterator m_iterator;	// �C�e���[�^�[
	EType m_type;	// ���
};

#endif	// _ACTOR_H_
