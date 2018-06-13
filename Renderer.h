//=================================================================================================
//                                                        
//�@�@�@DirectX�������N���X�v���O����[Renderer.h]
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.25      
//                                                        
//=================================================================================================
#ifndef _RENDERER_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _RENDERER_H_
#include"main.h"

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
	
private:
	static LPDIRECT3D9        m_pD3D;						//DirectX�C���^�[�t�F�[�X
	static LPDIRECT3DDEVICE9  m_pD3DDevice;					//�f�o�C�X��IDirect3Device9�C���^�t�F�[�X
	static D3DPRESENT_PARAMETERS m_d3dpp;					//DirectX�v���[���e�[�V�����p�����[�^
};
#endif