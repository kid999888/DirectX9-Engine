//=================================================================================================
//                                                        
//�@�@�@3D�L���[�u�N���X�v���O����[Scene3D.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENE3D_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _SCENE3D_H_
#include "Scene.h"

//=================================================================================================
//�@�@�@3D�|���S���N���X                                       
//=================================================================================================
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority) : CScene(nPriority) 
	{
		m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 2.0f, 10.0f);
		m_pTexture = nullptr;
		m_pVertexBuffer = NULL;
		m_pIndexBuffer = NULL;
	};														//3D�L���[�u�N���X�R���X�g���N�^
	~CScene3D();											//3D�L���[�u�N���X�f�X�g���N�^
	bool Init(void);										//3D�L���[�u�N���X��������
	void Uninit(void);										//3D�L���[�u�N���X�I������
	void Update(void);										//3D�L���[�u�N���X�X�V����
	void Draw(void);										//3D�L���[�u�N���X�`�揈��
	static CScene3D * Create(void);							//3D�L���[�u�̃C���X�^���X����

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//���_�o�b�t�@�Ǘ����郁����
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//�C���f�b�N�X�o�b�t�@�Ǘ����郁��
};

#endif
