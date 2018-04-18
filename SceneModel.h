//=================================================================================================
//                                                        
//�@�@�@3D���f���N���X�v���O����[SceneModel.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENEMODEL_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _SCENEMODEL_H_
#include"main.h"
#include "Scene.h"
//=================================================================================================
//�@�@�@�}�N����`                                        
//=================================================================================================

//=================================================================================================
//�@�@�@3D�|���S���N���X                                       
//=================================================================================================
class CSceneModel : public CScene
{
public:
	CSceneModel();											//3D���f���N���X�R���X�g���N�^
	~CSceneModel();											//3D���f���N���X�f�X�g���N�^
	bool Init(void);										//3D���f���N���X��������
	void Uninit(void);										//3D���f���N���X�I������
	void Update(void);										//3D���f���N���X�X�V����
	void Draw(void);										//3D���f���N���X�`�揈��

private:

	LPD3DXMESH m_pMesh;										//���b�V�����󂯎��ϐ�
	DWORD  m_nMaterialNum;									//X���f���̃}�e���A����
	LPD3DXBUFFER m_pMaterial;								//X���f���̃}�e���A�����
	int m_nMaterialPointNum;								//�}�e���A���|�C���^�̔ԍ�
	D3DXVECTOR3 m_XmodelAt;									//X���f���̒����_
	D3DXMATRIX m_mtxWorld;									//���[���h�s��ϐ�
	D3DXMATRIX m_mtxWorldR;									//���[���h �L���[�u�̉�]�s��
	D3DXMATRIX m_mtxWorldRX;								//���[���h �L���[�u��X������]�s��
	D3DXMATRIX m_mtxWorldRY;								//���[���h �L���[�u��Y������]�s��
	D3DXMATRIX m_mtxWorldRZ;								//���[���h �L���[�u��Z������]�s��
	D3DXMATRIX m_mtxWorldT;									//���[���h �L���[�u�̕��s�ړ��s��
	D3DXMATRIX m_mtxWorldS;									//���[���h �L���[�u�̕��s�ړ��s��
	float m_fRotX;											//3D�L���[�u��X��]
	float m_fRotY;											//3D�L���[�u��Y��]
	float m_fRotZ;											//3D�L���[�u��Z��]
};

#endif