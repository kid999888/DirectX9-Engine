#pragma once
#include "Scene.h"
#include "Types.h"
#include "main.h"

typedef enum
{
	PERFORMANCE_NONE = -1,			//�g���Ȃ����o�^
	PERFORMANCE_MOVE,			//�ړ����o�^
	PERFORMANCE_MAX			//�g���Ȃ����o�^
}PERFORMANCE_ID;
class CPerformance : public CScene
{
public:
	CPerformance(int nPriority, PERFORMANCE_ID PerformanceMode, CScene* PerformanceObject, D3DXVECTOR3 vePosEnd, int nFrameCount);
	~CPerformance();
	bool Init(void) { return true; };												//��������
	void Uninit(void) {};															//�I������
	void Update(void);																//�X�V����
	void Draw(void) {};																//
	static CPerformance * Create(PERFORMANCE_ID PerformanceMode, CScene* PerformanceObject, D3DXVECTOR3 vePosEnd, int nFrameCount);		//�C���X�^���X����
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

