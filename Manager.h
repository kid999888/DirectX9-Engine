//=================================================================================================
//                                                        
//�@�@�@�}�l�[�W���[�v���O����[Manager.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.05.19      
//                                                        
//=================================================================================================
#ifndef _MANAGER_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _MANAGER_H_

#include"main.h"
#include"Renderer.h"
//#include"Camera.h"
//#include"Light.h"
//#include"Material.h"
//#include"Scene.h"
//#include"Scene2D.h"
//#include"Scene3D.h"
//#include"SceneModel.h"
//#include"ScenePolygon.h"
//#include"Field.h"
//#include"Player.h"
//#include"Number.h"
#include "Mode.h"

//=================================================================================================
//�@�@�@�}�l�[�W���[�N���X                                       
//=================================================================================================
class CManager
{
public:
	static bool Init( HWND hWnd, BOOL bWindow);						//�}�l�[�W���[�N���X��������
	static void Uninit(void);										//�}�l�[�W���[�N���X�I������
	static void Update(void);										//�}�l�[�W���[�N���X�X�V����
	static void Draw(void);											//�}�l�[�W���[�N���X�`�揈��
	static void SetMode(CMode* Mode);								//�Q�[�����[�h�̐ݒ�
	static CMode* GetMode(void) {return m_Mode;};					//
private:
	static CMode* m_Mode;											//�Q�[�����[�h
};

#endif