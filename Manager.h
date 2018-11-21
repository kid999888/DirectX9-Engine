//=================================================================================================
//                                                        
//　　　マネージャープログラム[Manager.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.19      
//                                                        
//=================================================================================================
#ifndef _MANAGER_H_                                                 //2重インクルード防止のマクロ定義
#define _MANAGER_H_

#include "main.h"
#include "Renderer.h"
#include "Mode.h"


//=================================================================================================
//　　　マネージャークラス                                       
//=================================================================================================
class CManager
{
public:
	static bool Init( HWND hWnd, BOOL bWindow);						//マネージャークラス初期処理
	static void Uninit(void);										//マネージャークラス終了処理
	static void Update(void);										//マネージャークラス更新処理
	static void Draw(void);											//マネージャークラス描画処理
	static void SetMode(CMode* Mode);								//ゲームモードの設定
	static CMode* GetMode(void) {return m_Mode;};					//
private:
	static CMode* m_Mode;											//ゲームモード
	static CScene2D* m_Scene2D;
	static bool m_bBlur;
};

#endif