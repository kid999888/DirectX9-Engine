//=================================================================================================
//                                                        
//　　　モーションクラスプログラム[Motion.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.23      
//                                                        
//=================================================================================================
#pragma once
#include "Scene.h"
#include "SceneModel.h"

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

struct KEY
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Rotation;
};
struct KEY_FRAME
{
	int Frame;
	KEY key[10];
};

class CMotion : public CScene
{
public:
	CMotion(int nPriority) : CScene(nPriority) 
	{
		m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	};
	~CMotion();
	bool Init(void);									//モーション初期処理
	void Uninit(void);									//モーション終了処理
	void Update(void);									//モーション更新処理
	void Draw(void);									//モーション描画処理
	static CMotion * Create(void);						//モーションのインスタンス生成
	PART GetPart(int nCount);							//パート情報に取得する

private:
	PART m_Part[10];
	bool m_bPlay;
	KEY_FRAME *m_KeyFrame;
	int m_Key;
	int m_Frame;
	KEY_FRAME *m_NextKeyFrame;
	int m_NextKey;
	int m_NextFrame;

	int m_BlendFrame;
	float m_fBlendRate;
};

