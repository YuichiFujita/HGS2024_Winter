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

#ifdef SCORE
class CMultiValue;	// �}���`�����N���X
#else TIMER
class CTimeUI;		// �^�C��UI�N���X
#endif

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
#ifdef SCORE
	CMultiValue* m_pScore;	// �X�R�A���
#else TIMER
	CTimeUI* m_pTime;		// �^�C�����
#endif
	CResultState* m_pState;	// ���
};

#endif	// _RESULTMANAGER_H_
