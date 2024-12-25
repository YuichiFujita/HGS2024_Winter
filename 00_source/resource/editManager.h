//============================================================
//
//	�G�f�B�b�g�}�l�[�W���[�w�b�_�[ [editManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _EDIT_MANAGER_H_
#define _EDIT_MANAGER_H_

//************************************************************
//	�O���錾
//************************************************************
class CActor;	// �A�N�^�[�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �G�f�B�b�g�}�l�[�W���[�N���X
class CEditManager
{
public:
	// �R���X�g���N�^
	CEditManager();

	// �f�X�g���N�^
	~CEditManager();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update(const float fDeltaTime);	// �X�V

	// �ÓI�����o�֐�
	static CEditManager* Create();	// ����
	static void Release(CEditManager*& prEditManager);	// �j��

private:
	// �����o�֐�
	void UpdatePosition(const float fDeltaTime);	// �ʒu�̍X�V
	void UpdateRotation(const float fDeltaTime);	// �����̍X�V
	void UpdateScale(const float fDeltaTime);		// �g�嗦�̍X�V
	void UpdateType();		// ��ނ̍X�V
	void CreateActor();		// �A�N�^�[�̐���
	void ReleaseActor();	// �A�N�^�[�̔j��
	void SaveActor();		// �A�N�^�[�̕ۑ�

	// �����o�ϐ�
	CActor* m_pCreateActor;	// �����A�N�^�[���
};

#endif	// _EDIT_MANAGER_H_
