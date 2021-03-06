//=================================================================================================
//                                                        
//　　　モード処理クラス プログラム[Mode.h]
//      Author:王暁晨(AT-13A-281 04)　2018.07.03      
//                                                        
//=================================================================================================
#ifndef _MODE_H_                                                 //2重インクルード防止のマクロ定義
#define _MODE_H_

#include "main.h"
#include "Renderer.h"
#include "Camera.h"
#include "Light.h"
#include "Xorshift.h"
#include "Material.h"
#include "Scene.h"
#include "Scene2D.h"
#include "Scene3D.h"
#include "SceneModel.h"
#include "ScenePolygon.h"
#include "SceneBillBoard.h"
#include "Shadow.h"
#include "Field.h"
#include "Player.h"
#include "Number.h"
#include "Particle.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Map.h"
#include "Motion.h"
#include "Grid.h"
#include "LifeBar.h"
#include "ExplosionBB.h"

class CCamera;
class CField;
class CPlayer;
class CEnemy;
class CMap;

//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================
typedef enum
{
	MODE_NONE = -1,			//使えないモード
	MODE_TITLE,				//タイトルモード
	MODE_GAME,				//ゲームモード
	MODE_RESULT,			//リザルトモード
	MODE_GAMEOVER,			//ゲームオーバーモード
	MODE_TRAINING,			//トレーニングモード
	MODE_MOTION_EDITING,	//モーション編集モード
	MODE_TEST,				//テストモード
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
	virtual CCamera* GetMainCamera(void) = 0;
	virtual CField* GetField(void) { return nullptr; };
};

//=================================================================================================
//　　　ゲームモードクラス                                       
//=================================================================================================
class CModeGame : public CMode
{
public:
	CModeGame()
	{
		m_nClipNum = 0;
		m_nClipNumLimit = 10;
		m_nMoney = 0;
	};
	~CModeGame(void) {};
	bool Init(void);												//ゲームモードクラス初期処理
	void Uninit(void);												//ゲームモードクラス終了処理
	void Update(void);												//ゲームモードクラス更新処理
	void Draw(void);												//ゲームモードクラス描画処理										//
	
private:
	CCamera *m_Camera;												//カメラのアドレスポインタを声明
	CField * m_Field;												//フィールドのアドレスポインタを声明
	CPlayer * m_Player;												//プレーヤーのアドレスポインタを声明
	CEnemy* m_Enemy;												//
	CLight *m_Light;											//ライトのアドレスポインタを声明
	CXorshift* m_Xorshift;									//
	CSceneModel * m_SceneModelEnemy;							//敵モデリングのアドレスポインタを声明
	CSceneModel * m_SceneModelBuliding;						//モデリングのアドレスポインタを声明
	CNumber * m_Number;										//スコア数字のアドレスポインタを声明
	CNumber * m_NumberEnemyCount;										//スコア数字のアドレスポインタを声明
	CScenePolygon  * m_PolygonLazer;							//3Dポリゴンのアドレスポインタを声明
	CSceneBillBoard  * m_SceneBillBoard;						//ビルボードのアドレスポインタを声明
	CScene2D* m_UFOIcon;									//
	CSceneModel* m_SceneModel;								//
	CBullet* m_Bullet;										//
	CEnemy* m_Bulid;											//
	CMap* m_Map;
	CSceneShadow* m_Shadow;
	bool m_bPause;													//
	int m_nEnemyCount;												//敵記数
	int m_nClipNum;													//
	int m_nClipNumLimit;											//
	int m_nMoney;													//
public:
	CCamera * GetMainCamera(void) { return m_Camera; };		//カメラのアドレスを取得
	CField* GetField(void) { return m_Field; };				//フィールドのアドレスを取得
	CPlayer* GetMainPlayer(void) { return m_Player; };		//プレーヤーのアドレスを取得
	CEnemy* GetMainEnemy(void) { return m_Enemy; };			//プレーヤーのアドレスを取得

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
	CCamera* GetMainCamera(void) { return m_Camera; };				//カメラのアドレスを取得
private:
	CCamera* m_Camera;										//カメラのアドレスポインタを声明
	CLight* m_Light;											//ライトのアドレスポインタを声明
	CScene2D* m_Scene2D;										//2D画像のアドレスポインタを声明
	CSceneModel* m_Model;											//
	CSceneModel* m_ModelSkyBox;										//
	float m_fCameraRot;
};

//=================================================================================================
//　　　リザルトモードクラス                                       
//=================================================================================================
class CModeResult : public CMode
{
public:
	CModeResult(int nMoney)
	{
		m_nMoney = nMoney;
	};
	bool Init(void);												//リザルトモードクラス初期処理
	void Uninit(void);												//リザルトモードクラス終了処理
	void Update(void);												//リザルトモードクラス更新処理
	void Draw(void);												//リザルトモードクラス描画処理
	CCamera* GetMainCamera(void) { return m_Camera; };				//カメラのアドレスを取得
private:
	CCamera* m_Camera;										//カメラのアドレスポインタを声明
	CLight* m_Light;											//ライトのアドレスポインタを声明
	CScene2D* m_Scene2D;										//2D画像のアドレスポインタを声明
	CNumber* m_Money;
	int m_nMoney;
};

//=================================================================================================
//　　　ゲームオーバーモードクラス                                       
//=================================================================================================
class CModeGameOver : public CMode
{
public:
	CModeGameOver(int nMoney)
	{
		m_nMoney = nMoney;
	};
	bool Init(void);												//ゲームオーバーモードクラス初期処理
	void Uninit(void);												//ゲームオーバーモードクラス終了処理
	void Update(void);												//ゲームオーバーモードクラス更新処理
	void Draw(void);												//ゲームオーバーモードクラス描画処理
	CCamera* GetMainCamera(void) { return m_Camera; };				//カメラのアドレスを取得
private:
	CCamera* m_Camera;										//カメラのアドレスポインタを声明
	CLight* m_Light;											//ライトのアドレスポインタを声明
	CScene2D* m_Scene2D;										//2D画像のアドレスポインタを声明
	CNumber* m_Money;
	int m_nMoney;
};

//=================================================================================================
//　　　トレーニングモードクラス                                       
//=================================================================================================
class CModeTraining : public CMode
{
public:
	bool Init(void);												//トレーニングモードクラス初期処理
	void Uninit(void);												//トレーニングモードクラス終了処理
	void Update(void);												//トレーニングモードクラス更新処理
	void Draw(void);												//トレーニングモードクラス描画処理
	CCamera* GetMainCamera(void) { return m_Camera; };				//カメラのアドレスを取得
private:
	CCamera* m_Camera;										//カメラのアドレスポインタを声明
	CLight* m_Light;											//ライトのアドレスポインタを声明
	CScene2D* m_Scene2D;										//2D画像のアドレスポインタを声明
};

//=================================================================================================
//　　　モーション編集モードクラス                                       
//=================================================================================================
class CModeMotionEditing : public CMode
{
public:
	bool Init(void);												//トレーニングモードクラス初期処理
	void Uninit(void);												//トレーニングモードクラス終了処理
	void Update(void);												//トレーニングモードクラス更新処理
	void Draw(void);												//トレーニングモードクラス描画処理
	CCamera* GetMainCamera(void) { return m_Camera; };				//カメラのアドレスを取得
private:
	CCamera* m_Camera;												//カメラのアドレスポインタを声明
	CLight* m_Light;												//ライトのアドレスポインタを声明
	CGrid* m_Grid;													//グリッドのアドレスポインタを声明
	CMotion* m_Motion;												//
};

//=================================================================================================
//　　　テストモードクラス                                       
//=================================================================================================
class CModeTest : public CMode
{
public:
	bool Init(void);												//トレーニングモードクラス初期処理
	void Uninit(void);												//トレーニングモードクラス終了処理
	void Update(void);												//トレーニングモードクラス更新処理
	void Draw(void);												//トレーニングモードクラス描画処理
	CCamera* GetMainCamera(void) { return m_Camera; };				//カメラのアドレスを取得
private:
	CCamera* m_Camera;												//カメラのアドレスポインタを声明
	CLight* m_Light;												//ライトのアドレスポインタを声明
	CField * m_Field;												//フィールドのアドレスポインタを声明
	CSceneModel* m_Model;											//
	CSceneShadow* m_Shadow;											//
	CSceneModel* m_ModelSkyBox;										//
	CExplosionBB* m_ExplosionBB;									//
	
};


#endif