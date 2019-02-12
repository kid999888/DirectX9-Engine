#pragma once
#include "Scene.h"
#include "Types.h"
#include "main.h"

typedef enum
{
	PERFORMANCE_NONE = -1,			//使えない演出型
	PERFORMANCE_MOVE,			//移動演出型
	PERFORMANCE_MAX			//使えない演出型
}PERFORMANCE_ID;
class CPerformance : public CScene
{
public:
	CPerformance(int nPriority, PERFORMANCE_ID PerformanceMode, CScene* PerformanceObject, D3DXVECTOR3 vePosEnd, int nFrameCount);
	~CPerformance();
	bool Init(void) { return true; };												//初期処理
	void Uninit(void) {};															//終了処理
	void Update(void);																//更新処理
	void Draw(void) {};																//
	static CPerformance * Create(PERFORMANCE_ID PerformanceMode, CScene* PerformanceObject, D3DXVECTOR3 vePosEnd, int nFrameCount);		//インスタンス生成
	bool GetFinishFlag(void) { return _bFinish; };
private:
	PERFORMANCE_ID _PerformanceMode;
	D3DXVECTOR3 _pveObjectPos;
	D3DXVECTOR3 _veObjectEndPos;
	unsigned int _nFrameCount;
	unsigned int _nFrameCountNow;
	CScene* _PerformanceObject;
	bool _bFinish;
};

