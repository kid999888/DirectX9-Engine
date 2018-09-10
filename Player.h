//=================================================================================================
//                                                        
//　　　プレーヤークラスプログラム[Player.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.23      
//                                                        
//=================================================================================================
#ifndef _CPLAYER_H_                                                 //2重インクルード防止のマクロ定義
#define _CPLAYER_H_
#include "Scene.h"
#include "SceneModel.h"


#include "Camera.h"
#include "Bullet.h"
#include<vector>
using namespace std;

//=================================================================================================
//　　　フィールドクラス                                       
//=================================================================================================
class CPlayer : public CScene
{
public:
	CPlayer(int nPriority) : CScene(nPriority)
	{
		m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePlayerFront = D3DXVECTOR3(m_vePosition.x, m_vePosition.y, (m_vePosition.z - 1.0f));
		m_vePlayerMousePoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fMoveSpeed = 0.2f;
		m_fRotYSpeed = 5.0f;
		m_fRotOnce = 0.0f;
		m_fRotYExactly = 0;
		m_pTexture = nullptr;
	};													//プレーヤーコンストラクタ
	~CPlayer();											//プレーヤーデストラクタ
	bool Init(void);									//プレーヤー初期処理
	void Uninit(void);									//プレーヤー終了処理
	void Update(void);									//プレーヤー更新処理
	void Draw(void);									//プレーヤー描画処理
	static CPlayer * Create(D3DXVECTOR3 vePosition);	//プレーヤーのインスタンス生成
	static D3DXVECTOR3 GetPlayerPos(void)				
	{
		return m_vePosition;
	}
	D3DXVECTOR3 GetPlayerFront(void)					//プレーヤーの向きベクトルを取得
	{
		return m_vePlayerFront;
	};
	D3DXVECTOR3 GetPlayerMouse(void)
	{
		return m_vePlayerMousePoint;
	}

private:
	CSceneModel * m_pPlayer;							//プレーヤーのモデリング管理するアドレスを声明
	//CBullet m_pBullet;								//管理するアドレスを声明
	//vector<CBullet*> m_vBullet;						//管理するアドレスを声明
	static D3DXVECTOR3 m_vePosition;
	CCamera *m_Camera;									//カメラ管理するメンバーアドレスを声明
	D3DXVECTOR3 m_vePlayerFront;						//プレーヤーの向きベクトル
	D3DXVECTOR3 m_vePlayerMousePoint;						//プレーヤーの向きベクトル
	float m_fMoveSpeed;									//移動スビート
	float m_fRotYSpeed;									//回転スビート
	float m_fRotOnce;									//プレーヤー一回回転角度
	int m_fRotYExactly;									//回転限界
};

#endif