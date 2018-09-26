//=================================================================================================
//                                                        
//　　　DirectX初期化クラスプログラム[Renderer.h]
//      Author:王暁晨(AT-13A-281 04)　2018.04.25      
//                                                        
//=================================================================================================
#ifndef _RENDERER_H_                                                 //2重インクルード防止のマクロ定義
#define _RENDERER_H_
#include "main.h"

//=================================================================================================
//　　　DirectX初期化クラス                                      
//=================================================================================================
class CRenderer
{
public:
	static bool Init(HWND hWnd, BOOL bWindow);				//DirectX初期化クラス初期処理
	static void Uninit(void);								//DirectX初期化クラス終了処理
	static void DrawBegin(void);							//DirectX初期化クラス描画開始処理
	static void DrawEnd(void);								//DirectX初期化クラス描画終了処理
	static LPDIRECT3DDEVICE9  GetD3DDevice(void);			//D3DDeviceの伝達
	static LPD3DXEFFECT  GetD3DEffect(void);				//D3DXEFFECTの伝達
	static void SetD3DEffect(LPD3DXEFFECT D3DEffect);		//D3DXEFFECTの設定
#if defined(DEBUG)
	static D3DPRESENT_PARAMETERS  GetD3DPARAMETERS(void);	//D3DPARAMETERSの伝達
	static void SetBackBuffer(LPARAM lParam);				//D3DPARAMETERSのBackBufferの設定
#endif//defined(DEBUG)
	
private:
	static LPDIRECT3D9        m_pD3D;						//DirectXインターフェース
	static LPDIRECT3DDEVICE9  m_pD3DDevice;					//デバイスのIDirect3Device9インタフェース
	static LPD3DXEFFECT m_pEffect;							//
#if defined(DEBUG)
	static D3DPRESENT_PARAMETERS m_d3dpp;					//DirectXプレゼンテーションパラメータ
#endif//defined(DEBUG)
};
#endif