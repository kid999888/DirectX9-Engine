//=================================================================================================
//                                                        
//　　　プレーヤークラスプログラム[Player.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.23      
//                                                        
//=================================================================================================
#ifndef _CPLAYER_H_                                                 //2重インクルード防止のマクロ定義
#define _CPLAYER_H_
#include"Scene.h"
#include"SceneModel.h"

#include"Camera.h"

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
		m_fMoveSpeed = 0.2f;
		m_pTexture = nullptr;
	};												//プレーヤーコンストラクタ
	~CPlayer();										//プレーヤーデストラクタ
	bool Init(void);								//プレーヤー初期処理
	void Uninit(void);								//プレーヤー終了処理
	void Update(void);								//プレーヤー更新処理
	void Draw(void);								//プレーヤー描画処理
	static CPlayer * Create(D3DXVECTOR3 vePosition);					//プレーヤーのインスタンス生成

private:
	CSceneModel * m_pPlayer;
	CCamera *m_Camera;
	float m_fMoveSpeed;
};

#endif