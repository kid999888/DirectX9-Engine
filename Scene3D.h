//=================================================================================================
//                                                        
//�@�@�@3D�L���[�u�N���X�v���O����[Scene3D.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENE3D_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _SCENE3D_H_
#include"main.h"
#include "Scene.h"
//=================================================================================================
//�@�@�@�}�N����`                                        
//=================================================================================================

//=================================================================================================
//�@�@�@3D�|���S���N���X                                       
//=================================================================================================
class CScene3D : public CScene
{
public:
	CScene3D();												//3D�L���[�u�N���X�R���X�g���N�^
	~CScene3D();											//3D�L���[�u�N���X�f�X�g���N�^
	bool Init(void);										//3D�L���[�u�N���X��������
	void Uninit(void);										//3D�L���[�u�N���X�I������
	void Update(void);										//3D�L���[�u�N���X�X�V����
	void Draw(void);										//3D�L���[�u�N���X�`�揈��

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//���_�o�b�t�@�Ǘ����郁����
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//�C���f�b�N�X�o�b�t�@�Ǘ����郁��
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
