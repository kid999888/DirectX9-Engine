//=================================================================================================
//                                                        
//�@�@�@�I�u�W�F�N�g�����N���X �v���O����[Scene.h]
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENE_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _SCENE_H_
#include"main.h"
//=================================================================================================
//�@�@�@�}�N����`                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�I�u�W�F�N�g�����N���X                                       
//=================================================================================================
class CScene
{
public:
	CScene() {};
	virtual ~CScene() {};
	virtual bool Init(void) { return true; };			//�I�u�W�F�N�g��������
	virtual void Uninit(void) = 0;						//�I�u�W�F�N�g�I������
	virtual void Update(void) = 0;						//�I�u�W�F�N�g�X�V����
	virtual void Draw(void) = 0;						//�I�u�W�F�N�g�`�揈��
	void SetPosition(D3DXVECTOR3 vePosition);			//�I�u�W�F�N�g�̈ʒu�ݒ�
	void Release(void);									//�I�u�W�F�N�g�̃����[�X

protected:
	D3DXVECTOR3 m_vePosition;							//�I�u�W�F�N�g�̈ʒu
	LPDIRECT3DTEXTURE9* m_pTexture;						//�e�N�X�`���Ǘ����郁����
	D3DXMATRIX m_mtxWorld;								//�I�u�W�F�N�g���[���h�s��ϐ�
	D3DXMATRIX m_mtxWorldR;								//�I�u�W�F�N�g���[���h �L���[�u�̉�]�s��
	D3DXMATRIX m_mtxWorldRX;							//�I�u�W�F�N�g���[���h �L���[�u��X������]�s��
	D3DXMATRIX m_mtxWorldRY;							//�I�u�W�F�N�g���[���h �L���[�u��Y������]�s��
	D3DXMATRIX m_mtxWorldRZ;							//�I�u�W�F�N�g���[���h �L���[�u��Z������]�s��
	D3DXMATRIX m_mtxWorldT;								//�I�u�W�F�N�g���[���h �L���[�u�̕��s�ړ��s��
	D3DXMATRIX m_mtxWorldS;								//�I�u�W�F�N�g���[���h �L���[�u�̕��s�ړ��s��
	float m_fRotX;										//�I�u�W�F�N�g��X��]
	float m_fRotY;										//�I�u�W�F�N�g��Y��]
	float m_fRotZ;										//�I�u�W�F�N�g��Z��]
};

#endif