//=================================================================================================
//                                                        
//�@�@�@���[�V�����N���X�v���O����[Motion.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.05.23      
//                                                        
//=================================================================================================
#pragma once
#include"Scene.h"
#include"SceneModel.h"

struct PART
{
	LPD3DXMESH mesh;
	DWORD  MaterialNum;										//X���f���̃}�e���A����
	LPD3DXBUFFER Material;									//X���f���̃}�e���A�����
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;
	D3DXMATRIX Matrix;
	PART *Parent;
};
class CMotion : public CScene
{
public:
	CMotion(int nPriority) : CScene(nPriority) 
	{
		m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	};
	~CMotion();
	bool Init(void);									//�v���[���[��������
	void Uninit(void);									//�v���[���[�I������
	void Update(void);									//�v���[���[�X�V����
	void Draw(void);									//�v���[���[�`�揈��
	static CMotion * Create(void);			//�v���[���[�̃C���X�^���X����
private:
	PART m_Part[10];
};

