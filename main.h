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
#include<windows.h>
#if defined(DEBUG)
#include"Renderer.h"
#include "./GUI/imgui.h"
#include "./GUI/imgui_impl_dx9.h"
#endif//defined(DEBUG)

//=================================================================================================
//　　　マクロ定義                                        
//=================================================================================================
#define SAFE_RELEASE(p)			if(p){ p->Release(); p=NULL; }					//安全リリースマクロ
#define SAFE_DELETE(p)			if(p){ delete      (p); (p) = nullptr; }		//安全消しマクロ
#define SAFE_DELETE_ARRAY(p)	if(p){ delete[]    (p); (p) = nullptr; }		//安全配列消しマクロ
#define SCREEN_WIDTH		(1280)							//スクリーンの幅
#define SCREEN_HEIGHT		(720)							//スクリーンの高さ

//デフォルトベクトル
static const D3DXVECTOR4 v4One(1, 1, 1, 1);
static const D3DXVECTOR3 v3One(1, 1, 1);
static const D3DXVECTOR2 v2One(1, 1);
static const D3DXVECTOR3 v3Right(1, 0, 0);
static const D3DXVECTOR3 v3Down(0, -1, 0);
static const D3DXVECTOR3 v3In(0, 0, 1);
static const D3DXVECTOR3 v3Left(-1, 0, 0);
static const D3DXVECTOR3 v3Up(0, 1, 0);
static const D3DXVECTOR3 v3Out(0, 0, -1);
static const D3DXVECTOR2 v2Right(1, 0);
static const D3DXVECTOR2 v2Down(0, 1);
static const D3DXVECTOR2 v2Left(-1, 0);
static const D3DXVECTOR2 v2Up(0, -1);
static const D3DXVECTOR4 v4Zero(0, 0, 0, 0);
static const D3DXVECTOR3 v3Zero(0, 0, 0);
static const D3DXVECTOR2 v2Zero(0, 0);

//----------------------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------------------
struct Point2DI
{
	int x, y;
};
struct Point3DI
{
	int x, y, z;
};
struct Point4DI
{
	int x, y, z, w;
};

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
struct Point2DF
{
	float x, y;
};
struct Point3DF
{
	float x, y, z;
};
struct Point4DF
{
	float x, y, z, w;
};

#endif		//_MAIN_H_