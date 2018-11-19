//=================================================================================================
//                                                        
//�@�@�@DirectX�������N���X�v���O����[Renderer.h]
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.25      
//                                                        
//=================================================================================================
#ifndef _RENDERER_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _RENDERER_H_
#include "main.h"

//=================================================================================================
//�@�@�@DirectX�������N���X                                      
//=================================================================================================
class CRenderer
{
public:
	static bool Init(HWND hWnd, BOOL bWindow);				//DirectX�������N���X��������
	static void Uninit(void);								//DirectX�������N���X�I������
	static void DrawBegin(void);							//DirectX�������N���X�`��J�n����
	static void DrawEnd(void);								//DirectX�������N���X�`��I������
	static LPDIRECT3DDEVICE9  GetD3DDevice(void);			//D3DDevice�̓`�B
	static LPD3DXEFFECT  GetD3DEffect(void);				//D3DXEFFECT�̓`�B
	static void SetD3DEffect(LPD3DXEFFECT D3DEffect);		//D3DXEFFECT�̐ݒ�
	static LPDIRECT3DTEXTURE9 GetBlurTexture1(void) { return m_BlurTexture1; }
	static LPDIRECT3DSURFACE9 GetBlurSurface1(void) { return m_BlurSurface1; }
	static LPDIRECT3DTEXTURE9 GetBlurTexture2(void) { return m_BlurTexture2; }
	static LPDIRECT3DSURFACE9 GetBlurSurface2(void) { return m_BlurSurface2; }
	static LPDIRECT3DSURFACE9 GetBackBufferSurface(void) { return m_BackBufferSurface; }
#if defined(_DEBUG)
	static D3DPRESENT_PARAMETERS  GetD3DPARAMETERS(void);	//D3DPARAMETERS�̓`�B
	static void SetBackBuffer(LPARAM lParam);				//D3DPARAMETERS��BackBuffer�̐ݒ�
#endif//defined(_DEBUG)
	
private:
	static LPDIRECT3D9        m_pD3D;						//DirectX�C���^�[�t�F�[�X
	static LPDIRECT3DDEVICE9  m_pD3DDevice;					//�f�o�C�X��IDirect3Device9�C���^�t�F�[�X
	static LPD3DXEFFECT m_pEffect;							//
	static LPDIRECT3DTEXTURE9 m_BlurTexture1;
	static LPDIRECT3DSURFACE9 m_BlurSurface1;
	static LPDIRECT3DTEXTURE9 m_BlurTexture2;
	static LPDIRECT3DSURFACE9 m_BlurSurface2;
	static LPDIRECT3DSURFACE9 m_BackBufferSurface;
#if defined(_DEBUG)
	static D3DPRESENT_PARAMETERS m_d3dpp;					//DirectX�v���[���e�[�V�����p�����[�^
#endif//defined(_DEBUG)
};
#endif