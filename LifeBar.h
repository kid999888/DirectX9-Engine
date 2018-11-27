#pragma once
#include "Scene.h"
#include "Scene2D.h"
#include "Scene2DUV.h"
class CLifeBar : public CScene
{
public:
	CLifeBar(int nPriority);
	~CLifeBar();
	bool Init(void);										//
	void Uninit(void);										//
	void Update(void);										//
	void Draw(void);										//
	static CLifeBar * Create(void);
private:
	CScene2D * m_LifeBar;
	CScene2DUV * m_LifeBarHP;
};

