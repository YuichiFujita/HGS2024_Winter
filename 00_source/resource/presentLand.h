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
#include "present.h"

//************************************************************
//	�N���X��`
//************************************************************
// �ݒu�^�v���[���g�N���X
class CPresentLand : public CPresent
{
public:

	// ���
	enum EState
	{
		STATE_NONE = 0,		// �������
		STATE_FLY,			// ��ԏ��
		STATE_STOP,			// ��~���
		STATE_MAX			// ���̗񋓌^�̑���
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
	float GetRadius() const override;					// ���a�擾
	float GetHeight() const override;					// �c���擾

private:
	// �G�C���A�X��`
	typedef void(CPresentLand::* AFuncState)(const float);	// ��ԍX�V�֐��|�C���^

	// �֐��z��
	static AFuncState m_aFuncState[];	// ��ԍX�V�֐����X�g

	// �����o�֐�
	void SpeedCalc();							// ���x�v�Z����
	bool FieldCollision();						// �t�B�[���h�̓����蔻��

	void UpdateNone(const float fDeltaTime);	// ������ԏ���
	void UpdateFly(const float fDeltaTime);		// ��ԏ�ԏ���
	void UpdateStop(const float fDeltaTime);	// ��~��ԏ���

	// �����o�ϐ�
	float m_fFlyTime;			// ��Ԏ���
	VECTOR3	m_oldPos;			// �ߋ��ʒu
	VECTOR3 m_originPos;		// �����ʒu
	VECTOR3 m_destPos;			// �ړI�̈ʒu
	VECTOR3 m_move;				// �ړ���
	EState m_state;				// ���
};

#endif	// _PRESENT_LAND_H_