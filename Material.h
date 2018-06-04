//=================================================================================================
//                                                        
//　　　マテリアルクラスプログラム[Material.h]                   
//      Author:王暁晨(AT-13A-281 04)　2018.04.17      
//                                                        
//=================================================================================================
#ifndef _MATERIAL_H_                                                 //2重インクルード防止のマクロ定義
#define _MATERIAL_H_
#include"main.h"

//=================================================================================================
//　　　3Dポリゴンクラス                                       
//=================================================================================================
class CMaterial
{
public:
	CMaterial();												//マテリアルクラスコンストラクタ
	~CMaterial();												//マテリアルクラスデストラクタ
	void Update(void);											//マテリアルクラス更新処理
	void SetAmbient(float r, float g, float b, float a);		//マテリアル環境光（影に現れる色）色の設定
	void SetDiffuse(float r, float g, float b, float a);		//マテリアル拡散光（光のメイン色）色の設定
	void SetSpecular(float r, float g, float b, float a);		//マテリアル反射光の設定
	void MatCopy(D3DMATERIAL9 MatCpy);							//マテリアル反射光の設定

private:
	D3DMATERIAL9 m_Mat;											//DirectXのマテリアル情報
};
#endif