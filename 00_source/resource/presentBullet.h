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

	// ���
	enum EState
	{
		STATE_HOMING = 0,	// �z�[�~���O���
		STATE_MOVE,			// �ړ����
		STATE_DEATH,		// ���S���
		STATE_MAX			// ���̗񋓌^�̑���
	};

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

	// �ÓI�����o�֐�
	static CPresentBullet* Create	// ����
	( // ����
		const VECTOR3& rPos,	// �ʒu
		const float fRotY		// ����
	);

private:
	// �G�C���A�X��`
	typedef void(CPresentBullet::* AFuncState)(const float);	// ��ԍX�V�֐��|�C���^

	// �֐��z��
	static AFuncState m_aFuncState[];	// ��ԍX�V�֐����X�g

	// �����o�֐�
	void Collision();							// �����蔻��

	void UpdateHoming(const float fDeltaTime);			// �z�[�~���O����
	void UpdateMove(const float fDeltaTime);			// �ړ�����
	void UpdateDeath(const float fDeltaTime);			// ���S����
	void UpdateRotation(const float fDeltaTime);		// �����̍X�V����

	// �����o�ϐ�
	EState m_state;			// ���
	VECTOR3 m_destRot;		// �ړI�̌���
	float m_fStateTime;		// ��Ԏ���
	float m_fSpeed;			// ���x
};

#endif	// _PRESENT_BULLET_H_
