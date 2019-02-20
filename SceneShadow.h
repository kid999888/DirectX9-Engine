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
	bool Init(void);										//3D�|���S���N���X��������
	void Uninit(void);										//3D�|���S���N���X�I������
	void Update(void);										//3D�|���S���N���X�X�V����
	void Draw(void);										//3D�|���S���N���X�`�揈��
	static CSceneShadow * Create(CField* pField);					//3D�|���S���̃C���X�^���X����
private:
	CField * m_Field;												//�t�B�[���h�̃A�h���X�|�C���^�𐺖�
	CSceneModel* m_Model;											//
	CScene2D* m_ShadowShade;										//
};

