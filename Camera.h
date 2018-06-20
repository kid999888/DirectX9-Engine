//=================================================================================================
//                                                        
//�@�@�@�J�����N���X�v���O����[Camera.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _CAMERA_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _CAMERA_H_
#include"main.h"
//=================================================================================================
//�@�@�@�}�N����`                                        
//=================================================================================================

//=================================================================================================
//�@�@�@3D�|���S���N���X                                       
//=================================================================================================
class CCamera
{
public:
	CCamera();											//�J�����N���X�R���X�g���N�^
	~CCamera();											//�J�����N���X�f�X�g���N�^
	void Update(void);									//�J�����N���X�X�V����
	static void SetCameraPos(D3DXVECTOR3 veEyePos);		//�J�����ʒu�̐ݒ�
	static void SetCameraAtPos(D3DXVECTOR3 veAtPos);	//�J���������_�̐ݒ�
	static D3DXVECTOR3 GetCameraPos(void)				//�J�����ʒu�̎擾
	{ return m_eye; };									
	static D3DXVECTOR3 GetCameraAtPos(void)				//�J���������_�̎擾
	{ return m_at; };									

private:
	static D3DXVECTOR3 m_eye;							//�J�����ꏊ�𐺖�
	static D3DXVECTOR3 m_at;							//�J���������_�𐺖�
	static D3DXVECTOR3 m_up;							//��̏ꏊ�𐺖�
	D3DXMATRIX m_mtxView;								//�r���[�s��
	D3DXMATRIX m_mtxProjection;							//�v���W�F�N�V�����s��
};
#endif