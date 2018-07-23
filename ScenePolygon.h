//=================================================================================================
//                                                        
//�@�@�@3D�|���S���N���X�v���O����[ScenePolygon.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.06.08      
//                                                        
//=================================================================================================
#ifndef _SCENEPOLYGON_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _SCENEPOLYGON_H_
#include"Scene.h"

//=================================================================================================
//�@�@�@3D�|���S���N���X                                       
//=================================================================================================
class CScenePolygon : public CScene
{
public:
	CScenePolygon(int nPriority) : CScene(nPriority)
	{
		m_veScale = D3DXVECTOR3(40.0f, 1.0f, 0.25f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pTexture = nullptr;
		m_pVertexBuffer = NULL;
		m_pIndexBuffer = NULL;
	};														//3D�L���[�u�N���X�R���X�g���N�^
	~CScenePolygon();										//3D�L���[�u�N���X�f�X�g���N�^
	bool Init(void);										//3D�L���[�u�N���X��������
	void Uninit(void);										//3D�L���[�u�N���X�I������
	void Update(void);										//3D�L���[�u�N���X�X�V����
	void Draw(void);										//3D�L���[�u�N���X�`�揈��
	static CScenePolygon * Create(void);					//3D�L���[�u�̃C���X�^���X����

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//���_�o�b�t�@�Ǘ����郁����
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//�C���f�b�N�X�o�b�t�@�Ǘ����郁��
};

#endif
