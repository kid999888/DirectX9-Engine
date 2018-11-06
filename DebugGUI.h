//=================================================================================================
//                                                        
//�@�@�@DebugGUI�N���X�v���O����[Renderer.h]
//      Author:���ŝ�(AT-13A-281 04)�@2018.06.13      
//                                                        
//=================================================================================================
#if defined(_DEBUG)
#ifndef __DEBUGGUI_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define __DEBUGGUI_H_
#include "main.h"
#include "Player.h"
#include "Camera.h"
#include "Motion.h"
#include "Manager.h"
#include "input.h"

//=================================================================================================
//�@�@�@DirectX�������N���X                                      
//=================================================================================================
class CDebugGUI
{
public:
	static bool Init(void);						//DebugGUI��������
	static void UpdateWindow(void);				//DebugGUI�E�B���h�E�Y�X�V����
	static void SetPlayer(CPlayer* pPlayer)		//�v���[���[�̃A�h���X�̐ݒ�
	{ 
		m_pPlayer = pPlayer; 
	};
	static void SetMainCamera(CCamera* pCamera) //�J�����̃A�h���X�̐ݒ�
	{
		m_pCamera = pCamera; 
	};
	static void SetField(CField* pField)		//�t�B�[���h�̃A�h���X�̐ݒ�
	{
		m_pField = pField; 
	};
	static void SetMotion(CMotion* pMotion)		//
	{
		m_Motion = pMotion;
	};

private:
	static bool m_bshow_demo_window;			//Demo�E�B���h�E�̃t���b�O�𐺖�����
	static bool m_bshow_Motion_window;			//Demo�E�B���h�E�̃t���b�O�𐺖�����
	static CPlayer* m_pPlayer;					//�v���[���[�̃A�h���X�𐺖�����
	static CCamera* m_pCamera;					//�J�����̃A�h���X�𐺖�����
	static CField * m_pField;					//�t�B�[���h�̃A�h���X�𐺖�����
	static CMotion* m_Motion;								//

};
#endif
#endif//defined(_DEBUG)