//=================================================================================================
//                                                        
//�@�@�@�X�R�A�����\������[Number.h]                   
//      Author:���ŝ�(AT-12B-242 04)�@2018.06.12   
//                                                        
//=================================================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "Scene.h"
#include "Scene2D.h"

class CNumber : public CScene
{
public:
	CNumber(int nPriority, int nNumber, int nDigLimit);			//�����\���̃R���X�g���N�^
	~CNumber();													//�����\���̃f�X�g���N�^
	bool Init(void);											//�����\����������
	void Uninit(void);											//�����\���I������
	void Update(void);											//�����\���X�V����
	void Draw(void);											//�����\���`�揈��
	static CNumber * Create(int nNum, int nDigLimit = 5);				//�����\���̃C���X�^���X����
	void SetNumber(int nNum)						//�����̐ݒ�
	{
		m_nNumber = nNum;
	};
	int GetNumber(void)								//�����̎擾
	{
		return m_nNumber;
	};

private:
	int m_nNumber;									//�����\���̓��e
	int m_nDig;										//���������̎��ۓ��e
	int m_nDigX;									//���������̕\�����e
	bool m_bZero;									//�[���̕\��
	CScene2D* Scene2DNumber[5];						//2D�I�u�W�F�N�g�̊Ǘ�������
};

#endif //_NUMBER_H_