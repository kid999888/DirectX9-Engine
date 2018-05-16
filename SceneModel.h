//=================================================================================================
//                                                        
//�@�@�@3D���f���N���X�v���O����[SceneModel.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENEMODEL_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _SCENEMODEL_H_
#include"Scene.h"

//=================================================================================================
//�@�@�@3D�|���S���N���X                                       
//=================================================================================================
class CSceneModel : public CScene
{
public:
	CSceneModel(int nPriority) : CScene(nPriority) 
	{
		m_vePosition = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_fRotX = 0.0f;
		m_fRotY = 0.0f;
		m_fRotZ = 0.0f;
		m_pTexture = nullptr;
	};														//3D���f���N���X�R���X�g���N�^
	~CSceneModel();											//3D���f���N���X�f�X�g���N�^
	bool Init(void);										//3D���f���N���X��������
	void Uninit(void);										//3D���f���N���X�I������
	void Update(void);										//3D���f���N���X�X�V����
	void Draw(void);										//3D���f���N���X�`�揈��
	static CSceneModel * Create(void);						//3D���f���N���X�̃C���X�^���X����

private:
	LPD3DXMESH m_pMesh;										//���b�V�����󂯎��ϐ�
	DWORD  m_nMaterialNum;									//X���f���̃}�e���A����
	LPD3DXBUFFER m_pMaterial;								//X���f���̃}�e���A�����
	int m_nMaterialPointNum;								//�}�e���A���|�C���^�̔ԍ�
	D3DXVECTOR3 m_XmodelAt;									//X���f���̒����_
};

#endif