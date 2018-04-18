//=================================================================================================
//                                                        
//　　　3Dモデルクラスプログラム[SceneModel.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENEMODEL_H_                                                 //2重インクルード防止のマクロ定義
#define _SCENEMODEL_H_
#include"main.h"
#include "Scene.h"
//=================================================================================================
//　　　マクロ定義                                        
//=================================================================================================

//=================================================================================================
//　　　3Dポリゴンクラス                                       
//=================================================================================================
class CSceneModel : public CScene
{
public:
	CSceneModel();											//3Dモデルクラスコンストラクタ
	~CSceneModel();											//3Dモデルクラスデストラクタ
	bool Init(void);										//3Dモデルクラス初期処理
	void Uninit(void);										//3Dモデルクラス終了処理
	void Update(void);										//3Dモデルクラス更新処理
	void Draw(void);										//3Dモデルクラス描画処理

private:

	LPD3DXMESH m_pMesh;										//メッシュを受け取る変数
	DWORD  m_nMaterialNum;									//Xモデルのマテリアル数
	LPD3DXBUFFER m_pMaterial;								//Xモデルのマテリアル情報
	int m_nMaterialPointNum;								//マテリアルポインタの番号
	D3DXVECTOR3 m_XmodelAt;									//Xモデルの注視点
	D3DXMATRIX m_mtxWorld;									//ワールド行列変数
	D3DXMATRIX m_mtxWorldR;									//ワールド キューブの回転行列
	D3DXMATRIX m_mtxWorldRX;								//ワールド キューブのX方向回転行列
	D3DXMATRIX m_mtxWorldRY;								//ワールド キューブのY方向回転行列
	D3DXMATRIX m_mtxWorldRZ;								//ワールド キューブのZ方向回転行列
	D3DXMATRIX m_mtxWorldT;									//ワールド キューブの平行移動行列
	D3DXMATRIX m_mtxWorldS;									//ワールド キューブの平行移動行列
	float m_fRotX;											//3DキューブのX回転
	float m_fRotY;											//3DキューブのY回転
	float m_fRotZ;											//3DキューブのZ回転
};

#endif