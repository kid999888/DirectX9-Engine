//=================================================================================================
//                                                        
//　　　ゲームフレームワークメインプログラム[main.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.13      
//                                                        
//=================================================================================================
#ifndef _MAIN_H_                                                 //2重インクルード防止のマクロ定義
#define _MAIN_H_

//=================================================================================================
//　　　ヘッダファイル           
//=================================================================================================
#include<d3d9.h>
#include<d3dx9.h>


//=================================================================================================
//　　　マクロ定義                                        
//=================================================================================================
#define SAFE_RELEASE(p) if(p){ p->Release(); p=NULL; }		//安全リリースマクロ
#define SCREEN_WIDTH		(800)							//スクリーンの幅
#define SCREEN_HEIGHT		(600)							//スクリーンの高さ

LPDIRECT3DDEVICE9 GetD3DDevice(void);						//D3DDeviceの伝達

#endif		//_MAIN_H_