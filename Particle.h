//=================================================================================================
//                                                        
//　　　パーティクルクラスプログラム[Particle.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.07.09      
//                                                        
//=================================================================================================
#ifndef _CPARTICLE_H_                                                 //2重インクルード防止のマクロ定義
#define _CPARTICLE_H_
#include "Scene.h"
#include "SceneBillBoard.h"

//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================
typedef struct
{
	int status;					//状態
	D3DXVECTOR3 vePos;			//現在の座標
	D3DXVECTOR3 veMov;			//速度ベクトル
	D3DXVECTOR3 veAcc;			//加速度ベクトル
	int nLife;					//寿命
}PARTICLE;

#define PARTICLE_NUM (200)

//=================================================================================================
//　　　フィールドクラス                                       
//=================================================================================================
class CParticle : public CScene
{
public:
	CParticle(int nPriority) : CScene(nPriority)						//パーティクルコンストラクタ
	{
		m_veScale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fSpeed = 1.0f;
		m_nLifeLimit = 100;
	};
	~CParticle();													//パーティクルデストラクタ
	bool Init(void);												//パーティクル初期処理
	void Uninit(void);												//パーティクル終了処理
	void Update(void);												//パーティクル更新処理
	void Draw(void);												//パーティクル描画処理
	static CParticle * Create(CSceneBillBoard* pBillBoard,
		D3DXVECTOR3 vePosition, float fSpeed, int nLife,int GenerateTime,bool bGravity = false);			//パーティクルのインスタンス生成
	static void LoadBillBoard(CSceneBillBoard* pBillBoard);			//パーティクルのビルボードを読み込む


private:
	PARTICLE m_Particle[PARTICLE_NUM];								//パーティクル情報の管理
	static CSceneBillBoard* m_pBillBoard;							//パーティクルビルボード管理するアドレス
	static D3DXVECTOR3 m_vePosition;								//パーティクル発生の位置を声明する
	static float m_fSpeed;											//パーティクルの移動スビートを声明する
	static int m_nLifeLimit;										//パーティクルの寿命限界を声明する
	int m_nGenerateTime;											//パーティクルの生成時間
	static int m_nGenerateTimeLimit;								//パーティクルの寿命限界を声明する
	static bool m_bGravityType;										//パーティクルが重力の影響を受けるか
};

#endif