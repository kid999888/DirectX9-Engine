//=================================================================================================
//                                                        
//　　　ビルボード爆発プログラム[ExplosionBB.h]                   
//      Author:王暁晨(AT-13A-281 04)　2019.09.18      
//                                                        
//=================================================================================================
#pragma once
#include "Scene.h"
#include "SceneBillBoardUV.h"
#include "SceneBillBoard.h"
class CExplosionBB :
	public CScene
{
public:
	CExplosionBB(int nPriority, CCamera* pCamera);
	~CExplosionBB();
	bool Init(CCamera* pCamera, D3DXVECTOR3 vePos);												//パーティクル初期処理
	void Uninit(void);												//パーティクル終了処理
	void Update(void);												//パーティクル更新処理
	void Draw(void);												//パーティクル描画処理
	bool GetStaus(void) { return bFinish; }							//
	static CExplosionBB * Create(int nPriority, CCamera* pCamera, D3DXVECTOR3 vePos);
private:
	CSceneBillBoardUV* ExplosionBB;
	bool bFinish;
	float m_fU0;
	float m_fV0;
	float m_fU1;
	float m_fV1;
	int m_nAnimeCount;
	int m_patternNum;
	int m_patternH;
	int m_patternV;
};

