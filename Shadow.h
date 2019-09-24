#pragma once
#include "Scene.h"
#include "Field.h"
#include "SceneModel.h"
#include "Scene2D.h"

class CSceneShadow :
	public CScene
{
public:
	CSceneShadow(int nPriority, CField* pField);
	~CSceneShadow();
	bool Init(void);										//3Dポリゴンクラス初期処理
	void Uninit(void);										//3Dポリゴンクラス終了処理
	void Update(void);										//3Dポリゴンクラス更新処理
	void Draw(void);										//3Dポリゴンクラス描画処理
	static CSceneShadow * Create(CField* pField);					//3Dポリゴンのインスタンス生成
private:
	CField * m_Field;												//フィールドのアドレスポインタを声明
	CSceneModel* m_Model;											//
	CScene2D* m_ShadowShade;										//
};

