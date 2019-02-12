#include "Performance.h"



CPerformance::CPerformance(int nPriority, PERFORMANCE_ID PerformanceMode, CScene* PerformanceObject, D3DXVECTOR3 vePosEnd, int nFrameCount) : CScene(nPriority)
{
	m_bDraw = false;
	_PerformanceMode = PerformanceMode;
	_PerformanceObject = PerformanceObject;
	_pveObjectPos = PerformanceObject->GetPosition();
	_veObjectEndPos = vePosEnd;
	_nFrameCount = nFrameCount;
	_nFrameCountNow = 0;
	_bFinish = false;
}


CPerformance::~CPerformance()
{
	_PerformanceObject = nullptr;
}

void CPerformance::Update(void)
{
	if (!_bFinish)
	{
		float fFrameProportion = (float)_nFrameCountNow / (float)_nFrameCount;
		if (fFrameProportion <= 1.0f)
		{
			_PerformanceObject->SetPosition(D3DXVECTOR3(
				Lerp(_pveObjectPos.x, _veObjectEndPos.x, fFrameProportion),
				Lerp(_pveObjectPos.y, _veObjectEndPos.y, fFrameProportion),
				Lerp(_pveObjectPos.z, _veObjectEndPos.z, fFrameProportion)
			));
		}
		else
		{
			_bFinish = true;
		}
		_nFrameCountNow++;
	}
	
}

CPerformance * CPerformance::Create(PERFORMANCE_ID PerformanceMode, CScene* PerformanceObject, D3DXVECTOR3 vePosEnd, int nFrameCount)
{
	CPerformance *Performance = new CPerformance(0, PerformanceMode, PerformanceObject, vePosEnd, nFrameCount);
	Performance->Init();
	return Performance;
}
