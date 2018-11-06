//=================================================================================================
//                                                        
//�@�@�@���[�V�����N���X�v���O����[Motion.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.05.23      
//                                                        
//=================================================================================================
#pragma once
#include "Scene.h"
#include "SceneModel.h"

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

struct KEY
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;
};
struct KEY_FRAME
{
	int Frame;
	KEY key[10];
};

class CMotion : public CScene
{
public:
	CMotion(int nPriority) : CScene(nPriority) 
	{
		m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	};
	~CMotion();
	bool Init(void);									//���[�V������������
	void Uninit(void);									//���[�V�����I������
	void Update(void);									//���[�V�����X�V����
	void Draw(void);									//���[�V�����`�揈��
	static CMotion * Create(void);						//���[�V�����̃C���X�^���X����
	PART GetPart(int nCount);							//�p�[�g���Ɏ擾����

private:
	PART m_Part[10];
	bool m_bPlay;
	KEY_FRAME *m_KeyFrame;
	int m_Key;
	int m_Frame;
	KEY_FRAME *m_NextKeyFrame;
	int m_NextKey;
	int m_NextFrame;

	int m_BlendFrame;
	float m_fBlendRate;
};

