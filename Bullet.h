//=================================================================================================
//                                                        
//　　　バレットクラスプログラム[Bullet.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.23      
//                                                        
//=================================================================================================
#ifndef _CBULLET_H_                                                 //2重インクルード防止のマクロ定義
#define _CBULLET_H_
#include "Scene.h"
#include "SceneModel.h"

typedef struct
{
	int status;					//状態
	D3DXVECTOR3 vePos;			//現在の座標
	D3DXVECTOR3 veMov;			//速度ベクトル
	int nLife;					//寿命
}BULLET;

#define BULLET_NUM (100)

//=================================================================================================
//　　　フィールドクラス                                       
//=================================================================================================
class CBullet : public CScene
{
public:
	CBullet(int nPriority) : CScene(nPriority)						//バレットコンストラクタ
	{
		m_veScale = D3DXVECTOR3(0.15f, 0.15f, 0.15f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_bDraw = true;
	};												
	~CBullet();														//バレットデストラクタ
	bool Init(void);												//バレット初期処理
	void Uninit(void);												//バレット終了処理
	void Update(void);												//バレット更新処理
	void Draw(void);												//バレット描画処理
	static CBullet * Create(CSceneModel* pBullet);					//バレットのインスタンス生成
	static void Load(CSceneModel* pBullet);							//バレットのモデリングを読み込む
	static void Shoot(D3DXVECTOR3 vePosition, D3DXVECTOR3 veVec);	//新しいバレットをでる
	static void Destory(int nNum);									//バレットを廃棄
	static BULLET GetBulletManager(int nNum)						//パーティクル情報を取得
	{
		return m_Bullet[nNum];
	};
private:
	static BULLET m_Bullet[BULLET_NUM];								//パーティクル情報の管理
	static CSceneModel* m_pBullet;									//バレットモデリング管理するアドレス
};

#endif