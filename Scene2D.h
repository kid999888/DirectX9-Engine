//=================================================================================================
//                                                        
//　　　2Dポリゴンプログラム[Scene2D.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENE2D_H_                                                 //2重インクルード防止のマクロ定義
#define _SCENE2D_H_
#include"Scene.h"

//=================================================================================================
//　　　2Dポリゴンクラス                                       
//=================================================================================================
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority, int nNx, int nNy) : CScene(nPriority)
	{
		m_veScale = D3DXVECTOR3(0.25f, 0.25f, 1.0f);
		/*m_veScaleOffset = D3DXVECTOR2(0.0f, 0.0f);
		m_veRotationOffset = D3DXVECTOR2(0.0f, 0.0f);
		m_fRotationAngle = 0.0f;*/
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		
		m_npTLimitNum.x = nNx;
		m_npTLimitNum.y = nNy;
		m_pTexture = nullptr;
		m_pVertexBuffer = NULL;
	};												//2Dポリゴンコンストラクタ
	~CScene2D();									//2Dポリゴンデストラクタ
	bool Init(void);								//2Dポリゴン初期処理
	void Uninit(void);								//2Dポリゴン終了処理
	void Update(void);								//2Dポリゴン更新処理
	void Draw(void);								//2Dポリゴン描画処理
	static CScene2D * Create(int nNx, int nNy);		//2Dポリゴンのインスタンス生成

private:
	/*D3DXVECTOR2 m_veScaleOffset;
	D3DXVECTOR2 m_veRotationOffset;
	float m_fRotationAngle;*/
	Point2DI m_npTLimitNum;
	D3DXIMAGE_INFO m_D3DTextureInfo;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;						//頂点バッファ管理するメモ帳
	void CreateVertexAffine(D3DCOLOR color, int tCx, int tCy);		//頂点バッファ
};

#endif