//=================================================================================================
//                                                        
//�@�@�@DirectX�������N���X�v���O����[Scene.cpp]
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.25      
//                                                        
//=================================================================================================
#include"Renderer.h"

LPDIRECT3D9 CRenderer::m_pD3D = NULL;
LPDIRECT3DDEVICE9 CRenderer::m_pD3DDevice = NULL;

//=================================================================================================
//�@�@�@DirectX�������N���X��������                                     
//=================================================================================================
bool CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	//Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�C�X�v���C���[�h��
	D3DDISPLAYMODE d3ddm;

	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
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
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_MIXED_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &m_pD3DDevice)))
		{
			// REF���[�h��3D�f�o�C�X�쐬
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &m_pD3DDevice)))
			{
				if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED, &d3dpp, &m_pD3DDevice)))
				{
					// 3D�f�o�C�X�쐬���s(���̃O���t�B�b�N�{�[�h�ł�DirectX���g���Ȃ�)
					m_pD3D->Release();
					return false;
				}
			}
		}
	}
	return true;
}

//=================================================================================================
//�@�@�@DirectX�������N���X�I������                                       
//=================================================================================================
void CRenderer::Uninit(void)
{
	SAFE_RELEASE(m_pD3DDevice);
	SAFE_RELEASE(m_pD3D);
}

//=================================================================================================
//�@�@�@DirectX�������N���X�`��J�n����                                     
//=================================================================================================
void CRenderer::DrawBegin(void)
{
	//�`�揉����
	m_pD3DDevice->Clear(
		0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(32, 64, 192, 100), 1.0f, 0    //�F�͔��ƍ��I���Ȃ��ق���
	);
}

//=================================================================================================
//�@�@�@DirectX�������N���X�`��I������                                    
//=================================================================================================
void CRenderer::DrawEnd(void)
{
	//Present�̏I������
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=================================================================================================
//�@�@�@D3DDevice�̓`�B                                    
//=================================================================================================
LPDIRECT3DDEVICE9 CRenderer::GetD3DDevice(void)
{
	return m_pD3DDevice;
}
