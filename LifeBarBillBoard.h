#pragma once
#include "Scene.h"
#include "Camera.h"
#include "SceneBillBoard.h"
#include "SceneBillBoardUV.h"
class CLifeBarBillBoard : public CScene
{
public:
	CLifeBarBillBoard(int nPriority);
	~CLifeBarBillBoard();
	bool Init(CCamera* pCamera);										//
	void Uninit(void);										//
	void Update(void);										//
	void Draw(void);										//
	static CLifeBarBillBoard * Create(CCamera* pCamera);
private:
	CSceneBillBoard * m_LifeBar;
	CSceneBillBoardUV * m_LifeBarHP;
};

