//=================================================================================================
//                                                        
//　　　DebugGUIクラスプログラム[Renderer.h]
//      Author:王暁晨(AT-13A-281 04)　2018.06.13      
//                                                        
//=================================================================================================
#if defined(DEBUG)
#ifndef _DEBUGGUI_H_                                                 //2重インクルード防止のマクロ定義
#define _DEBUGGUI_H_
#include"main.h"
#include"Player.h"
#include"Camera.h"
#include"Manager.h"

//=================================================================================================
//　　　DirectX初期化クラス                                      
//=================================================================================================
class CDebugGUI
{
public:
	static bool Init(void);						//DebugGUI初期処理
	static void UpdateWindow(void);				//DebugGUIウィンドウズ更新処理
	static void SetPlayer(CPlayer* pPlayer)		//プレーヤーのアドレスの設定
	{ 
		m_pPlayer = pPlayer; 
	};
	static void SetMainCamera(CCamera* pCamera) //カメラのアドレスの設定
	{
		m_pCamera = pCamera; 
	};
	static void SetField(CField* pField)		//フィールドのアドレスの設定
	{
		m_pField = pField; 
	};

private:
	static bool m_bshow_demo_window;			//Demoウィンドウのフラッグを声明する
	static CPlayer* m_pPlayer;					//プレーヤーのアドレスを声明する
	static CCamera* m_pCamera;					//カメラのアドレスを声明する
	static CField * m_pField;					//フィールドのアドレスを声明する

};
#endif
#endif//defined(DEBUG)