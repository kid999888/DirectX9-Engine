//=================================================================================================
//                                                        
//　　　スコア数字表示処理[Number.h]                   
//      Author:王暁晨(AT-12B-242 04)　2018.06.12   
//                                                        
//=================================================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "Scene.h"
#include "Scene2D.h"

class CNumber : public CScene
{
public:
	CNumber(int nPriority, int nNumber, int nDigLimit);			//数字表示のコンストラクタ
	~CNumber();													//数字表示のデストラクタ
	bool Init(void);											//数字表示初期処理
	void Uninit(void);											//数字表示終了処理
	void Update(void);											//数字表示更新処理
	void Draw(void);											//数字表示描画処理
	static CNumber * Create(int nNum, int nDigLimit = 5);				//数字表示のインスタンス生成
	void SetNumber(int nNum)						//数字の設定
	{
		m_nNumber = nNum;
	};
	int GetNumber(void)								//数字の取得
	{
		return m_nNumber;
	};

private:
	int m_nNumber;									//数字表示の内容
	int m_nDig;										//数字桁数の実際内容
	int m_nDigX;									//数字桁数の表示内容
	bool m_bZero;									//ゼロの表示
	CScene2D* Scene2DNumber[5];						//2Dオブジェクトの管理メモ帳
};

#endif //_NUMBER_H_