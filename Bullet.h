//=================================================================================================
//                                                        
//　　　バレットクラスプログラム[Bullet.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.23      
//                                                        
//=================================================================================================
#ifndef _CBULLET_H_                                                 //2重インクルード防止のマクロ定義
#define _CBULLET_H_
#include"Scene.h"
#include"SceneModel.h"

//=================================================================================================
//　　　フィールドクラス                                       
//=================================================================================================
class CBullet : public CScene
{
public:
	CBullet(int nPriority) : CScene(nPriority)
	{
		m_veScale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_veMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_nLife = 0;
	};												//プレーヤーコンストラクタ
	~CBullet();										//プレーヤーデストラクタ
	bool Init(void);								//プレーヤー初期処理
	void Uninit(void);								//プレーヤー終了処理
	void Update(void);								//プレーヤー更新処理
	void Draw(void);								//プレーヤー描画処理
	static CBullet * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 At);					//プレーヤーのインスタンス生成
	/*static bool BallJudgement(D3DXVECTOR3 vBall1, D3DXVECTOR3 vBall2, float r1, float r2);*/

private:
	CSceneModel * m_pBullet;							//プレーヤーのモデリング管理するアドレス
	static D3DXVECTOR3 m_vePosition;
	static D3DXVECTOR3 m_veMove;								//
	int m_nLife;

};

#endif