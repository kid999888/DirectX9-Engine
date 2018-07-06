//=================================================================================================
//                                                        
//�@�@�@�Q�[���t���[�����[�N���C���v���O����[main.cpp]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.13          
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include"main.h"
#include"Manager.h"
#include"input.h"
#include"DebugGUI.h"
#include <crtdbg.h>

//=================================================================================================
//		�}�N����`                                        
//=================================================================================================
#define CLASS_NAME			"�T���v��"
#define WINDOW_NAME			"�E�B���h�E�\��"

//=================================================================================================
//		�v���g�^�C�v�錾                                  
//=================================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=================================================================================================
//�@�@�@�O���[�o���ϐ�                                    
//=================================================================================================
float g_fStartWidth = 0.0f;
float g_fStartHeight = 0.0f;
RECT g_UserRectSize;
static HWND g_hWnd;
#if defined(DEBUG)
//ImGUI���̃R���g���[���[
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif//defined(DEBUG)

//=================================================================================================
//�@�@�@�\���̒�`                                         
//=================================================================================================

//=================================================================================================
//�@�@�@�ÓI�C���X�^���X                           
//=================================================================================================
CInputKeyboard* g_pInputKeyboard;
CInputMouse* g_pInputMouse;
CInputJoypad* g_pInputJoypad;

//=================================================================================================
//�@�@�@���C���֐�                                        
//=================================================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)					//int Main(void)�Ɠ���
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(0);				//���������[�N�̌����A0�̓G���[�A��̃u���b�N�i���o�[�B

	//�\���̐錾
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),								//�\���̂̃T�C�Y
		CS_VREDRAW | CS_HREDRAW,						//�X�^�C��
		WndProc,
		0,
		0,
		hInstance,
		NULL,											//�A�C�R��
		LoadCursor(NULL, IDC_ARROW),					//�J�\��
		(HBRUSH)(COLOR_WINDOW + 1),						//�w�i
		NULL,											//���j���[�̐ݒ�Ȃ�
		CLASS_NAME,                                     //�N���X��
		NULL                                            //�{�^���Ȃ�
	};

	RegisterClassEx(&wcex);
	RECT wr = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT dr;                                          //�f�X�N�g�b�v�T�C�Y<�E�C���h�E�T�C�Y�@�H�@0:�E�C���h�E
	AdjustWindowRect(&wr, (WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX) ^ WS_THICKFRAME, false);

	GetWindowRect(GetDesktopWindow(), &dr);
	g_fStartWidth = (dr.right - wr.right) / 2;
	g_fStartHeight = (dr.bottom - wr.bottom) / 2;

	

	//�E�B���h�n���h���^
	g_hWnd = CreateWindowEx(
		0,
		CLASS_NAME, 									//�N���X��
		WINDOW_NAME,									//�E�C���h�E�̃^�C�g����
		(WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX) ^ WS_THICKFRAME,							//�E�B���h�X�^�C��    // WS_POPUP //fullscreen //(WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX) ^ WS_THICKFRAME
		g_fStartWidth,									//�E�B���h�̍�����WX
		g_fStartHeight,                                  //�E�B���h�̍�����WY
		SCREEN_WIDTH,									//�t���C�����܂߂��E�B���h�̕�
		SCREEN_HEIGHT,                                   //�t���C�����܂߂��E�B���h�̍���
		NULL,											//�e���Ȃ�
		NULL,											//���j���[���Ȃ�
		hInstance,
		NULL
	);

	//���[�U�[���擾�Aleft���[�U�[���J�nY���W�Atop���[�U�[���J�nX���W�Aright���[�U�[��敝�Abottom���[�U�[��捂��
	GetClientRect(g_hWnd, &g_UserRectSize);
	g_UserRectSize.left = g_fStartWidth - wr.left;
	g_UserRectSize.top = g_fStartHeight - wr.top;
	
	

	//�E�B���h�\��
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	

	//���b�Z�[�W���[�v
	MSG msg;											//���b�Z�[�W���󂯎��ϐ�


	//�Q�[�����[�v
	DWORD dwCurrentTime = timeGetTime();                       //���̎���
	DWORD dwFPSLastTime = 0;                                   //�O�̃t���[���̎���




	//��������
	if (!CManager::Init(g_hWnd, TRUE))
	{
		MessageBox(g_hWnd, "�G���[", "�������G���[", MB_OK);
		return -1;
	}
	//���͏����̏�����
	/*InitKeyboard(hInstance, g_hWnd);*/
	g_pInputKeyboard = new CInputKeyboard;
	g_pInputKeyboard->Init(hInstance, g_hWnd);
	g_pInputMouse = new CInputMouse;
	g_pInputMouse->Init(hInstance, g_hWnd);
	g_pInputJoypad = new CInputJoypad;
	g_pInputJoypad->Init(hInstance, g_hWnd);

#if defined(DEBUG)
	//DebugGUI��������
	CDebugGUI::Init();
#endif//defined(DEBUG)

	timeBeginPeriod(1);											//����\��ݒ�

	for (;;)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W����
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//���Ԃ̍X�V����
			dwCurrentTime = timeGetTime();
			//�Q�[������
			if ((dwCurrentTime - dwFPSLastTime) >= (1000 / 60))
			{
				dwFPSLastTime = dwCurrentTime;

#if defined(DEBUG)
				//ImGUI����
				CDebugGUI::UpdateWindow();
#endif//defined(DEBUG)

				//�X�V����
				CManager::Update();
				//���͏����̍X�V����
				/*UpdateKeyboard();*/						
				g_pInputKeyboard->Update();
				g_pInputMouse->Update();
				g_pInputJoypad->Update();
				//�`�揈��
				CManager::Draw();


			}
		}
	}

	timeEndPeriod(1);									//����\��߂�

	CManager::Uninit();									//�㏈��
	//���͏����̏I������
	/*UninitKeyboard();*/									
	g_pInputKeyboard->Uninit();
	delete g_pInputKeyboard;
	g_pInputMouse->Uninit();
	delete g_pInputMouse;
	g_pInputJoypad->Uninit();
	delete g_pInputJoypad;

	//�I�� �߂�l�ݒ�
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#if defined(DEBUG)
	//ImGui��Windowsandler����
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;
#endif//defined(DEBUG)

	switch (uMsg)
	{
#if defined(DEBUG)
	case WM_SIZE:
		if (CRenderer::GetD3DDevice() != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			CRenderer::SetBackBuffer(lParam);
			HRESULT hr = CRenderer::GetD3DDevice()->Reset(&CRenderer::GetD3DPARAMETERS());
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		return 0;
#endif//defined(DEBUG)
	case WM_DESTROY: PostQuitMessage(0);										//�E�C���h�E����Ẵ��b�Z�[�W
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			//[ESC]�L�[�������ꂽ
			int nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);         //���b�Z�[�W
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}
			break;
		}

		}
		break;

	case WM_RBUTTONDOWN:
		//�}�E�X�̉E�L�[�������ꂽ
		MessageBox(g_hWnd, "�}�E�X�̉E�L�[", "�{�[�_�[���b�Z�[�W�^�C�g��", MB_OK);							//���b�Z�[�W
		break;

	case WM_CLOSE:
	{
		//�I�����b�Z�[�W
		int nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_DEFBUTTON2);			//���b�Z�[�W
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;
	}
	//�}�E�X�̕\���ݒ�
	case WM_SETCURSOR:
	{
		if (LOWORD(lParam) == HTCLIENT)
		{
			//SetCursor(NULL);								//�}�E�X�̏���
			CRenderer::GetD3DDevice()->ShowCursor(true);	//false�̓}�E�X��\������Ȃ�

			return true;
		}
		break;
	}
	case WM_NCPAINT:
	{
		HDC hdc;
		hdc = GetDCEx(hWnd, (HRGN)wParam, DCX_WINDOW | DCX_INTERSECTRGN);
		// Paint into this DC
		InvalidateRect(hWnd, 0, false);
		UpdateWindow(hWnd);

		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_PAINT:
	{
		InvalidateRect(hWnd, 0, false);
		UpdateWindow(hWnd);
		break;
	}
	default: break;                                     //���̏ꍇ��switch�ɏo��
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

RECT GetUserWindowsSize(void)
{
	return g_UserRectSize;
}
