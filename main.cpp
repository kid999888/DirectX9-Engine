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
#include<windows.h>
#include "Scene2D.h"
#include "Scene3D.h"
#include "SceneModel.h"

//=================================================================================================
//		�}�N����`                                        
//=================================================================================================
#define CLASS_NAME			"�T���v��"
#define WINDOW_NAME			"�E�B���h�E�\��"

//=================================================================================================
//		�v���g�^�C�v�錾                                  
//=================================================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);         //�Q�[�����[�v��������
void Uninit(void);                                                  //�Q�[�����[�v�I������
void Update(void);                                                  //�Q�[�����[�v�X�V����
void Draw(void);                                                    //�Q�[�����[�v�`�揈��

//=================================================================================================
//�@�@�@�O���[�o���ϐ�                                    
//=================================================================================================
static HWND g_hWnd;

CScene2D		*g_Scene2D;
CScene3D		*g_Scene3D;
CSceneModel		*g_SceneModel;
CCamera			*g_Camera;
CLight			*g_Light;

//=================================================================================================
//�@�@�@�\���̒�`                                         
//=================================================================================================

//=================================================================================================
//�@�@�@���C���֐�                                        
//=================================================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)					//int Main(void)�Ɠ���
{
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
	RECT dr;                                            //�f�X�N�g�b�v�T�C�Y<�E�C���h�E�T�C�Y�@�H�@0:�E�C���h�E
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);

	GetWindowRect(GetDesktopWindow(), &dr);

	//�E�B���h�n���h���^
	g_hWnd = CreateWindowEx(
		0,
		CLASS_NAME, 									//�N���X��
		WINDOW_NAME,									//�E�C���h�E�̃^�C�g����
		(WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX) ^ WS_THICKFRAME,							//�E�B���h�X�^�C��    // WS_POPUP //fullscreen
		CW_USEDEFAULT,									//�E�B���h�̍�����W
		CW_USEDEFAULT,                                  //�E�B���h�̉E�����W
		SCREEN_WIDTH,									//�t���C�����܂߂��E�B���h�̕�
		SCREEN_HEIGHT,                                   //�t���C�����܂߂��E�B���h�̍���
		NULL,											//�e���Ȃ�
		NULL,											//���j���[���Ȃ�
		hInstance,
		NULL
	);

	//�E�B���h�\��
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	//���b�Z�[�W���[�v
	MSG msg;											//���b�Z�[�W���󂯎��ϐ�


	//�Q�[�����[�v
	DWORD dwCurrentTime = timeGetTime();                       //���̎���
	DWORD dwFPSLastTime = 0;                                   //�O�̃t���[���̎���

															   //��������
	if (!Init(hInstance, g_hWnd, TRUE))
	{
		MessageBox(g_hWnd, "�G���[", "������", MB_OK);
		return -1;
	}


	timeBeginPeriod(1);									      //����\��ݒ�

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
				//�X�V����
				Update();
				//�`�揈��
				Draw();
			}
		}
	}

	timeEndPeriod(1);									//����\��߂�

	Uninit();                                           //�㏈��

	//�I�� �߂�l�ݒ�
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
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
	//
	case WM_SETCURSOR:
	{
		if (LOWORD(lParam) == HTCLIENT)
		{
			SetCursor(NULL);
			CRenderer::GetD3DDevice()->ShowCursor(false);

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

//=================================================================================================
//�@�@�@�Q�[�����[�v��������
//=================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//DirectX�������N���X��������
	CRenderer::Init(hWnd, bWindow);
	g_Camera = new CCamera();
	g_Light = new CLight();
	g_Scene2D = new CScene2D();
	g_Scene2D->Init();
	g_Scene3D = new CScene3D();
	g_Scene3D->Init();
	g_SceneModel = new CSceneModel();
	g_SceneModel->Init();
	
	return true;
}

//=================================================================================================
//�@�@�@�Q�[�����[�v�I������
//=================================================================================================
void Uninit(void)
{
	delete g_Camera;
	delete g_Light;
	g_Scene2D->Uninit();
	delete g_Scene2D;
	g_Scene3D->Uninit();
	delete g_Scene3D;
	g_SceneModel->Uninit();
	delete g_SceneModel;
	//DirectX�������N���X�I������
	CRenderer::Uninit();
}

//=================================================================================================
//�@�@�@�Q�[�����[�v�X�V����
//=================================================================================================
void Update(void)
{
	g_Scene2D->Update();
	g_Scene3D->Update();
	g_SceneModel->Update();
}

//=================================================================================================
//�@�@�@�Q�[�����[�v�`�揈��
//=================================================================================================
void Draw(void)
{
	//DirectX�������N���X�`��J�n���� 
	CRenderer::DrawBegin();

	//Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(CRenderer::GetD3DDevice()->BeginScene()))
	{
		g_Camera->Update();
		g_Light->Update();
		//2D�|���S���`��
		g_Scene2D->Draw();
		//3D�|���S���`��
		g_Scene3D->Draw();
		//3D�|���S���`��
		g_SceneModel->Draw();
		//Present�̏I������
		CRenderer::GetD3DDevice()->EndScene();
	}
	//DirectX�������N���X�`��I������ 
	CRenderer::DrawEnd();
}
