//=================================================================================================
//                                                        
//　　　マップクラスプログラム[Map.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.07.23      
//                                                        
//=================================================================================================
#ifndef _CMAP_H_                                                 //2重インクルード防止のマクロ定義
#define _CMAP_H_
#include"Scene.h"
#include"Scene2D.h"
#include"Enemy.h"
#include"Player.h"

//=================================================================================================
//　　　フィールドクラス                                       
//=================================================================================================
class CMap : public CScene
{
public:
	CMap(int nPriority) : CScene(nPriority)						//マップコンストラクタ
	{
		m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_bDraw = true;
	};
	~CMap();														//マップデストラクタ
	bool Init(void);												//マップ初期処理
	void Uninit(void);												//マップ終了処理
	void Update(void);												//マップ更新処理
	void Draw(void);												//マップ描画処理
	static CMap * Create(void);										//マップのインスタンス生成
private:
	static CScene2D* m_pScene2DMap;									//マップ実体管理するアドレス
	static CScene2D* m_pScene2DBlock;								//マップオブジェクト管理するアドレス
	static CEnemy* m_pEnemy;										//
};

#endif