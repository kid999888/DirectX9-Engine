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
	CBullet(int nPriority) : CScene(nPriority)						//バレットコンストラクタ
	{
		m_veScale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_veMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_nLife = 0;
	};												
	~CBullet();														//バレットデストラクタ
	bool Init(void);												//バレット初期処理
	void Uninit(void);												//バレット終了処理
	void Update(void);												//バレット更新処理
	void Draw(void);												//バレット描画処理
	static CBullet * Create(D3DXVECTOR3 Pos, D3DXVECTOR3 At);		//バレットのインスタンス生成
	static int GeTBullerLife(void) { return m_nLife; };				//バレットの寿命をもらう

private:
	CSceneModel * m_pBullet;										//バレットモデリング管理するアドレス
	static D3DXVECTOR3 m_vePosition;								//バレットの位置を声明する
	static D3DXVECTOR3 m_veMove;									//バレットの加速度を声明する
	static int m_nLife;												//バレットの寿命

};

#endif