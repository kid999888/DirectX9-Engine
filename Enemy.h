//=================================================================================================
//                                                        
//　　　敵クラスプログラム[Enemy.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.07.16      
//                                                        
//=================================================================================================
#ifndef _CENEMY_H_                                                 //2重インクルード防止のマクロ定義
#define _CENEMY_H_
#include "Scene.h"
#include "Scene3D.h"
#include "SceneModel.h"
#include "Player.h"
class CPlayer;
//=================================================================================================
//　　　構造体定義                                         
//=================================================================================================
typedef enum
{
	ENEMY_TYPES_ZAKU,				//ザグ敵型
	ENEMY_TYPES_BULIDING,			//建物敵型
}ENEMY_TYPES_ID;


typedef struct
{
	int status;					//状態
	D3DXVECTOR3 vePos;			//現在の座標
	D3DXVECTOR3 veMov;			//速度ベクトル
	int nLife;					//寿命
	ENEMY_TYPES_ID EnemyType;	//敵型
	CSceneModel* SceneModel;
	D3DXVECTOR3 veScale;
}ENEMY;

#define ENEMY_NUM (100)



//=================================================================================================
//　　　フィールドクラス                                       
//=================================================================================================
class CEnemy : public CScene
{
public:
	CEnemy(int nPriority);														//敵コンストラクタ
	~CEnemy();														//敵デストラクタ
	bool Init(void);												//敵初期処理
	void Uninit(void);												//敵終了処理
	void Update(void);												//敵更新処理
	void Draw(void);												//敵描画処理
	static CEnemy * Create(void);									//敵のインスタンス生成
	void Generate(ENEMY_TYPES_ID EnemyType, D3DXVECTOR3 vePosition,
		CSceneModel* pSceneModel, D3DXVECTOR3 veScale);				//新しい敵を生成
	void Destory(int nNum);									//敵を廃棄する
	void SetEnemyLife(int nNum, int nLife);					//敵HPを設定
	void SetEnemyPosition(int nNum, D3DXVECTOR3 vePos);					//敵HPを設定
	ENEMY GetEnemyManager(int nNum)							//ナンバーの敵の情報をくれ
	{
		return m_Enemy[nNum];
	};
	void SetPlayer(CPlayer* Player);
private:
	ENEMY m_Enemy[ENEMY_NUM];								//敵情報の管理
	D3DXVECTOR3 GetMovePattern(int nNum);					//敵移動パターン
	CPlayer* m_Player;
};

#endif