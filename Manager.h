//=================================================================================================
//                                                        
//　　　マネージャープログラム[Manager.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.19      
//                                                        
//=================================================================================================
#ifndef _MANAGER_H_                                                 //2重インクルード防止のマクロ定義
#define _MANAGER_H_

#include"main.h"
#include"Renderer.h"
#include"Camera.h"
#include"Light.h"
#include"Material.h"
#include"Scene.h"
#include"Scene2D.h"
#include"Scene3D.h"
#include"SceneModel.h"
#include"ScenePolygon.h"
#include"Field.h"
#include"Player.h"

#include"Number.h"

//=================================================================================================
//　　　マネージャークラス                                       
//=================================================================================================
class CManager
{
public:
	static bool Init( HWND hWnd, BOOL bWindow);			//マネージャークラス初期処理
	static void Uninit(void);							//マネージャークラス終了処理
	static void Update(void);							//マネージャークラス更新処理
	static void Draw(void);								//マネージャークラス描画処理
	static CField* GetField(void);
	static CCamera* GetMainCamera(void) { return m_Camera; };				//
	static CPlayer* GetMainPlayer(void) { return m_Player; };				//
private:
	static CCamera *m_Camera;
	static CLight *m_Light;
	static CField * m_Field;
	static CPlayer * m_Player;
	static CScene3D * m_Scene3D;
	static CNumber * m_Number;
};

#endif