//=================================================================================================
//                                                        
//　　　3Dモデルクラスプログラム[SceneModel.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENEMODEL_H_                                                 //2重インクルード防止のマクロ定義
#define _SCENEMODEL_H_
#include"Scene.h"

//=================================================================================================
//　　　3Dポリゴンクラス                                       
//=================================================================================================
class CSceneModel : public CScene
{
public:
	CSceneModel(int nPriority) : CScene(nPriority) 
	{
		m_vePosition = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_fRotX = 0.0f;
		m_fRotY = 0.0f;
		m_fRotZ = 0.0f;
		m_pTexture = nullptr;
	};														//3Dモデルクラスコンストラクタ
	~CSceneModel();											//3Dモデルクラスデストラクタ
	bool Init(void);										//3Dモデルクラス初期処理
	void Uninit(void);										//3Dモデルクラス終了処理
	void Update(void);										//3Dモデルクラス更新処理
	void Draw(void);										//3Dモデルクラス描画処理
	static CSceneModel * Create(void);						//3Dモデルクラスのインスタンス生成

private:
	LPD3DXMESH m_pMesh;										//メッシュを受け取る変数
	DWORD  m_nMaterialNum;									//Xモデルのマテリアル数
	LPD3DXBUFFER m_pMaterial;								//Xモデルのマテリアル情報
	int m_nMaterialPointNum;								//マテリアルポインタの番号
	D3DXVECTOR3 m_XmodelAt;									//Xモデルの注視点
};

#endif