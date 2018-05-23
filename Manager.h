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
#include"Camera.h"
#include"Light.h"
#include"Material.h"
#include"Scene.h"
#include"Scene2D.h"
#include"Scene3D.h"
#include"SceneModel.h"
#include"Field.h"
#include"Player.h"

//=================================================================================================
//�@�@�@�}�l�[�W���[�N���X                                       
//=================================================================================================
class CManager
{
public:
	static bool Init( HWND hWnd, BOOL bWindow);			//�}�l�[�W���[�N���X��������
	static void Uninit(void);							//�}�l�[�W���[�N���X�I������
	static void Update(void);							//�}�l�[�W���[�N���X�X�V����
	static void Draw(void);								//�}�l�[�W���[�N���X�`�揈��
private:
	static CCamera *m_Camera;
	static CLight *m_Light;
	
};

#endif