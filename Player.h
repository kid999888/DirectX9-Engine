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

//=================================================================================================
//　　　フィールドクラス                                       
//=================================================================================================
class CPlayer : public CScene
{
public:
	CPlayer(int nPriority) : CScene(nPriority)
	{
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fRotX = 0.0f;
		m_fRotY = 0.0f;
		m_fRotZ = 0.0f;
		m_pTexture = nullptr;
	};												//フィールドコンストラクタ
	~CPlayer();										//フィールドデストラクタ
	bool Init(void);								//フィールド初期処理
	void Uninit(void);								//フィールド終了処理
	void Update(void);								//フィールド更新処理
	void Draw(void);								//フィールド描画処理
	static CPlayer * Create(D3DXVECTOR3 vePosition);					//フィールドのインスタンス生成

private:
	CSceneModel * m_pPlayer;
};

#endif