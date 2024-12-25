//============================================================
//
//	�J�n���o�w�b�_�[ [start.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _START_H_
#define _START_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "object2D.h"

//************************************************************
//	�N���X��`
//************************************************************
// �J�n���o�N���X
class CStart : public CObject2D
{
public:
	// �R���X�g���N�^
	CStart();

	// �f�X�g���N�^
	~CStart() override;

	// �I�[�o�[���C�h�֐�
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update(const float fDeltaTime) override;	// �X�V
	void Draw(CShader* pShader = nullptr) override;	// �`��

	// �ÓI�����o�֐�
	static CStart* Create();

	// �����o�֐�
	bool IsStagEnd() const;	// ���o�I���t���O�擾

	/*
		@brief	easeOutBack�֐�
		@details https://easings.net/ja#easeInBack
		@param	start		[in]	�����l
		@param	end			[in]	�ڕW�l
		@param	startTime	[in]	�J�n����
		@param	endTime		[in]	�I������
		@param	currentTime	[in]	���݂̎���
		@param	c			[in]	�o�b�N�̋���
		@return	�␳���ꂽfloat�l
	*/
	inline float EaseOutBack(float start, float end, float startTime, float endTime, float currentTime, float c = 1.70158f)
	{
		// ����
		float ratio = (currentTime - startTime) / (endTime - startTime);
		useful::LimitNum(ratio, 0.0f, 1.0f);

		ratio -= 1; // t �� (t - 1) �ɕϊ�

		float cal = ratio * ratio * ((c + 1) * ratio + c) + 1;
		return start + (end - start) * cal;
	}

private:
	// �����o�ϐ�
	float m_fStateTime;	// �o�ߎ���
};

#endif	// _START_H_
