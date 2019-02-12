//=================================================================================================
//                                                        
//　　　プレーヤークラスプログラム[Player.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.05.23      
//                                                        
//=================================================================================================
#ifndef _CPLAYER_H_                                                 //2重インクルード防止のマクロ定義
#define _CPLAYER_H_
#include "Scene.h"
#include "SceneModel.h"
#include "Mode.h"


#include "Camera.h"
#include "Bullet.h"
#include<vector>
using namespace std;
class CMode;

//=================================================================================================
//　　　フィールドクラス                                       
//=================================================================================================
class CPlayer : public CScene
{
public:
	CPlayer(CMode* Mode,int nPriority);		//プレーヤーコンストラクタ
	~CPlayer();											//プレーヤーデストラクタ
	bool Init(void);									//プレーヤー初期処理
	void Uninit(void);									//プレーヤー終了処理
	void Update(void);									//プレーヤー更新処理
	void Draw(void);									//プレーヤー描画処理
	static CPlayer * Create(CMode* Mode, D3DXVECTOR3 vePosition);	//プレーヤーのインスタンス生成
	D3DXVECTOR3 GetPlayerFront(void)					//プレーヤーの向きベクトルを取得
	{
		return m_vePlayerFront;
	};
	D3DXVECTOR3 GetPlayerMouse(void)
	{
		return m_vePlayerMousePoint;
	}
	int GetPlayerHp(void) {return _nHp;};
	void SetPlayerHp(int nHp) { _nHp = nHp; };

private:
	CMode* m_CurrentMode;
	CSceneModel * m_pPlayer;							//プレーヤーのモデリング管理するアドレスを声明
	CCamera *m_Camera;									//カメラ管理するメンバーアドレスを声明
	D3DXVECTOR3 m_vePlayerFront;						//プレーヤーの向きベクトル
	D3DXVECTOR3 m_vePlayerMousePoint;						//プレーヤーの向きベクトル
	float m_fMoveSpeed;									//移動スビート
	float m_fRotYSpeed;									//回転スビート
	float m_fRotOnce;									//プレーヤー一回回転角度
	int m_fRotYExactly;									//回転限界
	int _nHp;
};

#endif