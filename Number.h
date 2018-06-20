//=================================================================================================
//                                                        
//�@�@�@�X�R�A�����\������[Number.h]                   
//      Author:���ŝ�(AT-12B-242 04)�@2018.06.12   
//                                                        
//=================================================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include"Scene.h"
#include"Scene2D.h"

class CNumber : public CScene
{
public:
	CNumber(int nPriority,int nNumber) : CScene(nPriority)
	{
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f,-1.0f);
		m_nNumber = nNumber;
		m_nDig = 0;
		m_nDigX = 5;
		m_bZero = true;
	};												//�����\���̃R���X�g���N�^
	~CNumber();										//�����\���̃f�X�g���N�^
	bool Init(void);								//�����\����������
	void Uninit(void);								//�����\���I������
	void Update(void);								//�����\���X�V����
	void Draw(void);								//�����\���`�揈��
	static CNumber * Create(int nNum);				//�����\���̃C���X�^���X����
	void SetNumber(int nNum)
	{
		m_nNumber = nNum;
	};
	int GetNumber(void)
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