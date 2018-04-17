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
LPDIRECT3D9        g_pD3D = NULL;                                   //DirectX�C���^�[�t�F�[�X
LPDIRECT3DDEVICE9  g_pD3DDevice = NULL;                             //�f�o�C�X��IDirect3Device9�C���^�t�F�[�X
static HWND g_hWnd;
CScene2D *g_Scene2D;

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

	default: break;                                     //���̏ꍇ��switch�ɏo��
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=================================================================================================
//�@�@�@�Q�[�����[�v��������
//=================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}


	//���݂̃f�C�X�v���C���[�h��
	D3DDISPLAYMODE d3ddm;

	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;

	}

	//�f�o�C�X�̃v���[���e�[�V����
	D3DPRESENT_PARAMETERS d3dpp;                                      //�f�o�C�X��������
	ZeroMemory(&d3dpp, sizeof(d3dpp));                                //d3dpp�̃������ɏ�����
	d3dpp.BackBufferWidth = SCREEN_WIDTH;                             //�X�N���[���̕�
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                           //�X�N���[���̍���
	d3dpp.BackBufferFormat = d3ddm.Format;                            //�o�b�N�E�o�b�t�@�̃t�H�[�}�b�g(�f�B�X�v���C�E�t�H�[�}�b�g�̎w�肖)
	d3dpp.BackBufferCount = 1;                                        //�O�̂��̂ƌ��̂��̌�������
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                         //�X���b�v�E�G�t�F�N�g
	d3dpp.EnableAutoDepthStencil = TRUE;                              //3D�`�惂�[�h
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                        //
	d3dpp.Windowed = bWindow;                                         //�E�C���h�E���[�h���w��
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;       //Full screen ��FPS�R���g���[��
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;         //�`��FPS�Œ�

	//�f�o�C�X�I�u�W�F�N�g�̐���
	//[�f�o�C�X�쐬����]<�`��>��<���_����>��
	// HAL���[�h��3D�f�o�C�X�쐬
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &g_pD3DDevice)))
		{
			// REF���[�h��3D�f�o�C�X�쐬
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &g_pD3DDevice)))
			{
				if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &g_pD3DDevice)))
				{
					// 3D�f�o�C�X�쐬���s(���̃O���t�B�b�N�{�[�h�ł�DirectX���g���Ȃ�)
					g_pD3D->Release();
					return false;
				}
			}
		}
	}
	
	g_Scene2D = new CScene2D();
	g_Scene2D->Init();

	return true;
}

//=================================================================================================
//�@�@�@�Q�[�����[�v�I������
//=================================================================================================
void Uninit(void)
{
	SAFE_RELEASE(g_pD3DDevice);
	SAFE_RELEASE(g_pD3D);
	g_Scene2D->Uninit();
	delete g_Scene2D;
}

//=================================================================================================
//�@�@�@�Q�[�����[�v�X�V����
//=================================================================================================
void Update(void)
{
	g_Scene2D->Update();
}

//=================================================================================================
//�@�@�@�Q�[�����[�v�`�揈��
//=================================================================================================
void Draw(void)
{
	//�`�揉����
	g_pD3DDevice->Clear(
		0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(32, 64, 192, 100), 1.0f, 0    //�F�͔��ƍ��I���Ȃ��ق���
	);

	//Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//�|���S���`��
		g_Scene2D->Draw();
		//Present�̏I������
		g_pD3DDevice->EndScene();
	}
	//Present�̏I������
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}


//=================================================================================================
//�@�@�@D3DDevice�̓`�B
//=================================================================================================
LPDIRECT3DDEVICE9 GetD3DDevice(void)
{
	return g_pD3DDevice;                                            //D3DDevice�̓`�B
}
