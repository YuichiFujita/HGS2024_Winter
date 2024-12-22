//============================================================
//
//	�����L���O�}�l�[�W���[�w�b�_�[ [rankingManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _RANKINGMANAGER_H_
#define _RANKINGMANAGER_H_

//************************************************************
//	�O���錾
//************************************************************
class CRankingState;	// �����L���O��ԃN���X

//************************************************************
//	�N���X��`
//************************************************************
// �����L���O�}�l�[�W���[�N���X
class CRankingManager
{
public:
	// �R���X�g���N�^
	CRankingManager();

	// �f�X�g���N�^
	~CRankingManager();

	// �����o�֐�
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update(const float fDeltaTime);		// �X�V
	HRESULT ChangeState(CRankingState* pState);	// ��ԕύX

	// �ÓI�����o�֐�
	static CRankingManager* Create();	// ����
	static void Release(CRankingManager*& prRankingManager);	// �j��

private:
	// �����o�ϐ�
	CRankingState* m_pState;	// ���
};

#endif	// _RANKINGMANAGER_H_
