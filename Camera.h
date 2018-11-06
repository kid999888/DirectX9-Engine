//=================================================================================================
//                                                        
//�@�@�@�J�����N���X�v���O����[Camera.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _CAMERA_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _CAMERA_H_
#include "main.h"
//=================================================================================================
//�@�@�@�}�N����`                                        
//=================================================================================================
#define PI				(3.141592f)			// �~����

#define	VIEW_ANGLE				(45.0f)					// ����p(45.0f)	
#define	VIEW_NEAR_Z				(10.0f)					// �r���[���ʂ�NearZ�l(10.0f)	
#define	VIEW_FAR_Z				(100000.0f)				// �r���[���ʂ�FarZ�l(100000.0f)	

#define	VALUE_MOVE				(0.2f)					// �J�����̈ړ���
#define	VALUE_ROTATE			(PI * 0.01f)			// �J�����̉�]��
#define	VALUE_MOVE_DRAG			(0.30f)					// �}�E�X�h���b�O���̈ړ���
#define	VALUE_ROTATE_MOUSE		(0.003f)				// �}�E�X�ɂ���]��

#define	CAM_LENGTH_RATE			(20.0f)					// ���_���璍���_�܂ł̋����̔䗦
#define	CAM_LENGTH_LIMIT_MIN	(10.0f)					// ���_���璍���_�܂ł̋����ŏ��l
#define	CAM_LENGTH_LIMIT_MAX	(1600.0f)				// ���_���璍���_�܂ł̋����ő�l

#define	LENGTH_REF_MOVE			(60.0f)					// �v���C���[�ɑ΂��钍���_�̋���(�ړ���)
#define	LENGTH_REF_STOP			(30.0f)					// �v���C���[�ɑ΂��钍���_�̋���(��~��)
#define	HEIGTH_REF				(40.0f)					// �v���C���[�ɑ΂��钍���_�̍���

#define	LENGTH_POS_MOVE			(300.0f)				// �v���C���[�ɑ΂��鎋�_�̋���(�ړ���)
#define	LENGTH_POS_STOP			(300.0f)				// �v���C���[�ɑ΂��鎋�_�̋���(��~��)
#define	HEIGTH_POS				(80.0f)					// �v���C���[�ɑ΂��鎋�_�̍���

#define	ADJUST_ROT				(0.010f)				// ���_�̉�]�p�␳�W��

//=================================================================================================
//�@�@�@3D�|���S���N���X                                       
//=================================================================================================
class CCamera
{
public:
	CCamera();											//�J�����N���X�R���X�g���N�^
	~CCamera();											//�J�����N���X�f�X�g���N�^
	void Update(void);									//�J�����N���X�X�V����
	void SetCameraPos(D3DXVECTOR3 veEyePos);			//�J�����ʒu�̐ݒ�
	void SetCameraAtPos(D3DXVECTOR3 veAtPos);			//�J���������_�̐ݒ�
	D3DXVECTOR3 GetCameraPos(void)						//�J�����ʒu�̎擾
	{ return m_eye; };									
	D3DXVECTOR3 GetCameraAtPos(void)					//�J���������_�̎擾
	{ return m_at; };
	D3DXMATRIX GetCameraProjection(void)				//�J�����v���W�F�N�V�����s��̎擾
	{
		return m_mtxProjection;
	};
	D3DXMATRIX GetCameraView(void)						//�J�����r���[�s��̎擾
	{
		return m_mtxView;
	};
	void CameraViewFlag(bool bFlag)						//���_����t���b�O
	{
		m_bViewChange = bFlag;
	}

private:
	D3DXVECTOR3 m_eye;							//�J�����ꏊ�𐺖�
	D3DXVECTOR3 m_at;							//�J���������_�𐺖�
	D3DXVECTOR3 m_up;							//��̏ꏊ�𐺖�
	D3DXVECTOR3 m_rot;							//�J�����̌���
	D3DXMATRIX m_mtxView;						//�r���[�s��
	D3DXMATRIX m_mtxProjection;					//�v���W�F�N�V�����s��
	bool m_bViewChange;							//���_����t���b�O
	float m_fLengthInterval;							// ���_���璍���_�܂ł̋���
	float m_fLengthIntervalXZ;							// ���_���璍���_�܂ł̋���(XZ����)
	void ViewChange(void);								//���_����
};
#endif