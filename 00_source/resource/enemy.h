//============================================================
//
//	�G�w�b�_�[ [enemy.h]
//	Author�F��������
//	Adder �F���c�E��
// 
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _ENEMY_H_
#define _ENEMY_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "objectChara.h"

//************************************************************
//	�N���X��`
//************************************************************
// �v���C���[�N���X
class CEnemy : public CObjectChara
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

	// ���[�V������
	enum EMotion
	{
		MOTION_IDOL = 0,	// �ҋ@���[�V����
		MOTION_ATK_UP,		// �㓊�����[�V����
		MOTION_ATK_SIDE,	// ���������[�V����
		MOTION_MAX			// ���̗񋓌^�̑���
	};

	// ��ԗ�
	enum EState
	{
		STATE_IDOL = 0,	// �ҋ@���
		STATE_JUMP,		// �W�����v���
		STATE_ATK,		// �U�����
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CEnemy();

	// �f�X�g���N�^
	~CEnemy() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;		// �X�V
	void Draw(CShader* pShader = nullptr) override;		// �`��
	void SetEnableUpdate(const bool bUpdate) override;	// �X�V�󋵐ݒ�
	void SetEnableDraw(const bool bDraw) override;		// �`��󋵐ݒ�

	// �ÓI�����o�֐�
	static CEnemy* Create	// ����
	( // ����
		const VECTOR3& rPos,	// �ʒu
		const VECTOR3& rRot		// ����
	);
	static CListManager<CEnemy>* GetList();	// ���X�g�擾

	// �����o�֐�
	inline void SetDestRotation(const VECTOR3& rRot)	{ m_destRot = rRot; }	// �ڕW�����ݒ�
	inline VECTOR3 GetDestRotation() const				{ return m_destRot; }	// �ڕW�����擾
	inline void SetMove(const VECTOR3& rMove)			{ m_move = rMove; }		// �ړ��ʐݒ�
	inline VECTOR3 GetMove() const						{ return m_move; }		// �ړ��ʎ擾
	inline void SetEnableJump(const bool bJump)			{ m_bJump = bJump; }	// �W�����v�󋵐ݒ�
	inline bool IsJump() const							{ return m_bJump; }		// �W�����v�󋵐ݒ�
	float GetRadius() const;	// ���a�擾
	float GetHeight() const;	// �c���擾

private:
	// �G�C���A�X��`
	typedef EMotion(CEnemy::*AFuncState)(const float);	// ��ԍX�V�֐��|�C���^

	// �֐��z��
	static AFuncState m_aFuncState[];	// ��ԍX�V�֐����X�g

	// �����o�֐�
	float CalcIdolTime();	// �ҋ@���Ԍv�Z
	bool IsAttack();		// �U�����[�V�����t���O�擾
	void SetState(const EState state);	// ��Ԑݒ�
	void SetJump(const VECTOR3& rCurPos, const VECTOR3& rJumpPos);		// �W�����v�ݒ�
	void SetAttack(const VECTOR3& rCurPos, const VECTOR3& rPlayerPos);	// �U���ݒ�
	EMotion UpdateIdol(const float fDeltaTime);		// �ҋ@��Ԏ��̍X�V
	EMotion UpdateJump(const float fDeltaTime);		// �W�����v��Ԏ��̍X�V
	EMotion UpdateAttack(const float fDeltaTime);	// �U����Ԏ��̍X�V
	void UpdateOldPosition();						// �ߋ��ʒu�̍X�V
	void UpdateGravity(const float fDeltaTime);		// �d�͂̍X�V
	bool UpdateLanding(VECTOR3* pPos, const float fDeltaTime);	// ���n�󋵂̍X�V
	void UpdatePosition(VECTOR3* pPos, const float fDeltaTime);	// �ʒu�̍X�V
	void UpdateRotation(VECTOR3* pRot, const float fDeltaTime);	// �����̍X�V
	void UpdateMotion(int nMotion, const float fDeltaTime);		// ���[�V����/�L�����N�^�[�̍X�V

	// �ÓI�����o�ϐ�
	static CListManager<CEnemy>* m_pList;	// �I�u�W�F�N�g���X�g

	// �����o�ϐ�
	CListManager<CEnemy>::AIterator m_iterator;	// �C�e���[�^�[
	EState m_state;		// ���
	VECTOR3	m_oldPos;	// �ߋ��ʒu
	VECTOR3	m_move;		// �ړ���
	VECTOR3	m_destRot;	// �ڕW����
	bool	m_bJump;	// �W�����v��
	float	m_fStateTime;	// ��ԊǗ�����
	VECTOR3	m_jumpPosStart;	// �W�����v�J�n�ʒu
	VECTOR3	m_jumpPosEnd;	// �W�����v�I���ʒu
};

#endif	// _PLAYER_H_
