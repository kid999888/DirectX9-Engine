//=================================================================================================
//                                                        
//　　　モーションクラスプログラム[Motion.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.23      
//                                                        
//=================================================================================================
#pragma once
#include"Scene.h"
#include"SceneModel.h"

struct PART
{
	LPD3DXMESH mesh;
	DWORD  MaterialNum;										//Xモデルのマテリアル数
	LPD3DXBUFFER Material;									//Xモデルのマテリアル情報
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;
	D3DXMATRIX Matrix;
	PART *Parent;
};
class CMotion : public CScene
{
public:
	CMotion(int nPriority) : CScene(nPriority) 
	{
		m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	};
	~CMotion();
	bool Init(void);									//プレーヤー初期処理
	void Uninit(void);									//プレーヤー終了処理
	void Update(void);									//プレーヤー更新処理
	void Draw(void);									//プレーヤー描画処理
	static CMotion * Create(void);			//プレーヤーのインスタンス生成
private:
	PART m_Part[10];
};

