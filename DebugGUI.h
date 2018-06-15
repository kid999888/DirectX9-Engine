//=================================================================================================
//                                                        
//�@�@�@DebugGUI�N���X�v���O����[Renderer.h]
//      Author:���ŝ�(AT-13A-281 04)�@2018.06.13      
//                                                        
//=================================================================================================
#if defined(DEBUG)
#ifndef _DEBUGGUI_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _DEBUGGUI_H_
#include"main.h"
#include"Player.h"
#include"Camera.h"
#include"Manager.h"

//=================================================================================================
//�@�@�@DirectX�������N���X                                      
//=================================================================================================
class CDebugGUI
{
public:
	static bool Init(void);				//DebugGUI��������
	static void UpdateWindow(void);		//DebugGUI�E�B���h�E�Y�X�V����
	static void SetPlayerPoint(CPlayer* pPlayer) { m_pPlayer = pPlayer; };
	static void SetMainCameraPoint(CCamera* pCamera) { m_Camera = pCamera; };

private:

	static bool m_bshow_demo_window;
	static ImVec4 m_v4clear_color;
	static CPlayer* m_pPlayer;
	static CCamera* m_Camera;

};
#endif
#endif//defined(DEBUG)