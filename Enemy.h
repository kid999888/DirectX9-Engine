//=================================================================================================
//                                                        
//　　　敵クラスプログラム[Enemy.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.07.16      
//                                                        
//=================================================================================================
#ifndef _CENEMY_H_                                                 //2重インクルード防止のマクロ定義
#define _CENEMY_H_
#include"Scene.h"
#include"Scene3D.h"
#include"Player.h"


typedef struct
{
	int status;					//状態
	D3DXVECTOR3 vePos;			//現在の座標
	D3DXVECTOR3 veMov;			//速度ベクトル
	int nLife;					//寿命
}ENEMY;

#define ENEMY_NUM (100)

//=================================================================================================
//　　　フィールドクラス                                       
//=================================================================================================
class CEnemy : public CScene
{
public:
	CEnemy(int nPriority) : CScene(nPriority)						//敵コンストラクタ
	{
		m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_veRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_bDraw = true;
	};
	~CEnemy();														//敵デストラクタ
	bool Init(void);												//敵初期処理
	void Uninit(void);												//敵終了処理
	void Update(void);												//敵更新処理
	void Draw(void);												//敵描画処理
	static CEnemy * Create(CScene3D* pScene3D);						//敵のインスタンス生成
	static void Load(CScene3D* pScene3D);							//敵の実体を読み込む
	static void Generate(D3DXVECTOR3 vePosition);					//新しい敵を生成
	static void Destory(int nNum);									//敵を廃棄する
	static void SetEnemyLife(int nNum, int nLife);					//敵HPを設定
	static ENEMY GetEnemyManager(int nNum)							//ナンバーの敵の情報をくれ
	{
		return m_Enemy[nNum];
	};
private:
	static ENEMY m_Enemy[ENEMY_NUM];								//敵情報の管理
	static CScene3D* m_pScene3D;									//敵の実体管理するアドレス
	static D3DXVECTOR3 GetMovePattern(int nNum);					//敵移動パターン
};

#endif