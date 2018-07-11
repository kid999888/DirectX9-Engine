//=================================================================================================
//                                                        
//　　　モード処理クラス プログラム[Mode.h]
//      Author:王暁晨(AT-13A-281 04)　2018.07.03      
//                                                        
//=================================================================================================
#ifndef _MODE_H_                                                 //2重インクルード防止のマクロ定義
#define _MODE_H_

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
#include"SceneBillBoard.h"
#include"Field.h"
#include"Player.h"
#include"Number.h"
#include"Particle.h"

//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================
typedef enum
{
	MODE_NONE = -1,			//使えないモード
	MODE_TITLE,				//タイトルモード
	MODE_GAME,				//ゲームモード
	MODE_RESULT,			//リザルトモード
	MODE_MAX				//使えないモード
}MODE_ID;

//=================================================================================================
//　　　モード処理クラス                                       
//=================================================================================================
class CMode
{
public:
	virtual bool Init(void) { return true; };				//モードクラス初期処理
	virtual void Uninit(void) = 0;							//モードクラス終了処理
	virtual void Update(void) = 0;							//モードクラス更新処理
	virtual void Draw(void) = 0;							//モードクラス描画処理
	MODE_ID m_ModeId;										//モードID
	MODE_ID GetModeId(void) { return this->m_ModeId; };		//モードIDの取得
};

//=================================================================================================
//　　　ゲームモードクラス                                       
//=================================================================================================
class CModeGame : public CMode
{
public:
	bool Init(void);												//ゲームモードクラス初期処理
	void Uninit(void);												//ゲームモードクラス終了処理
	void Update(void);												//ゲームモードクラス更新処理
	void Draw(void);												//ゲームモードクラス描画処理
	static CCamera* GetMainCamera(void) { return m_Camera; };		//カメラのアドレスを取得
	static CField* GetField(void) { return m_Field; };				//フィールドのアドレスを取得
	static CPlayer* GetMainPlayer(void) { return m_Player; };		//プレーヤーのアドレスを取得
private:
	static CCamera *m_Camera;										//カメラのアドレスポインタを声明
	static CLight *m_Light;											//ライトのアドレスポインタを声明
	static CField * m_Field;										//フィールドのアドレスポインタを声明
	static CPlayer * m_Player;										//プレーヤーのアドレスポインタを声明
	static CScene3D * m_Scene3D;									//3Dキューブのアドレスポインタを声明
	static CNumber * m_Number;										//スコア数字のアドレスポインタを声明
	static CScenePolygon  * m_ScenePolygon;							//3Dポリゴンのアドレスポインタを声明
	static CSceneBillBoard  * m_SceneBillBoard;						//ビルボードのアドレスポインタを声明
};

//=================================================================================================
//　　　タートルモードクラス                                       
//=================================================================================================
class CModeTitle : public CMode
{
public:
	bool Init(void);												//タートルモードクラス初期処理
	void Uninit(void);												//タートルモードクラス終了処理
	void Update(void);												//タートルモードクラス更新処理
	void Draw(void);												//タートルモードクラス描画処理
private:
	static CCamera* m_Camera;										//カメラのアドレスポインタを声明
	static CLight* m_Light;											//ライトのアドレスポインタを声明
	static CScene2D* m_Scene2D;										//2D画像のアドレスポインタを声明
};

//=================================================================================================
//　　　リザルトモードクラス                                       
//=================================================================================================
class CModeResult : public CMode
{
public:
	bool Init(void);												//リザルトモードクラス初期処理
	void Uninit(void);												//リザルトモードクラス終了処理
	void Update(void);												//リザルトモードクラス更新処理
	void Draw(void);												//リザルトモードクラス描画処理
private:
	static CCamera* m_Camera;										//カメラのアドレスポインタを声明
	static CLight* m_Light;											//ライトのアドレスポインタを声明
	static CScene2D* m_Scene2D;										//2D画像のアドレスポインタを声明
};

#endif