//=================================================================================================
//                                                        
//　　　ライトクラスプログラム[Light.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _LIGHT_H_                                                 //2重インクルード防止のマクロ定義
#define _LIGHT_H_
#include "main.h"
//=================================================================================================
//　　　マクロ定義                                        
//=================================================================================================

//=================================================================================================
//　　　3Dポリゴンクラス                                       
//=================================================================================================
class CLight
{
public:
	CLight();													//ライトクラスコンストラクタ
	~CLight();													//ライトクラスデストラクタ
	bool Init(void);											//ライトクラス初期化
	void Update(void);											//ライトクラス更新処理
	void Draw(void);											//ライトクラス描画処理
	void SetDir(D3DXVECTOR3 vecDir);							//ライト方向設定
	void SetAmbient(float r, float g, float b, float a);		//環境光（影に現れる色）色の設定
	void SetDiffuse(float r, float g, float b, float a);		//拡散光（光のメイン色）色の設定
	void SetSpecular(float r, float g, float b, float a);		//反射光の設定

private:
	D3DLIGHT9 m_Light;											//DirectXのライト情報
	D3DXVECTOR4 m_lightDir;										
};
#endif