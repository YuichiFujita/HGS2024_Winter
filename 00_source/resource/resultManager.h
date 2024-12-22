//============================================================
//
//	���U���g�}�l�[�W���[�w�b�_�[ [resultManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _RESULTMANAGER_H_
#define _RESULTMANAGER_H_

//************************************************************
//	�O���錾
//************************************************************
class CResultState;	// ���U���g��ԃN���X

//************************************************************
//	�N���X��`
//************************************************************
// ���U���g�}�l�[�W���[�N���X
class CResultManager
{
public:
	// �R���X�g���N�^
	CResultManager();

	// �f�X�g���N�^
	~CResultManager();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update(const float fDeltaTime);		// �X�V
	HRESULT ChangeState(CResultState* pState);	// ��ԕύX
	void TransRanking();	// �����L���O��ʑJ��

	// �ÓI�����o�֐�
	static CResultManager* Create();	// ����
	static void Release(CResultManager*& prResultManager);	// �j��

private:
	// �����o�ϐ�
	CResultState* m_pState;	// ���
};

#endif	// _RESULTMANAGER_H_
