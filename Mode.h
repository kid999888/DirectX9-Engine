//=================================================================================================
//                                                        
//�@�@�@���[�h�����N���X �v���O����[Mode.h]
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.03      
//                                                        
//=================================================================================================
#ifndef _MODE_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _MODE_H_

#include "main.h"
#include "Renderer.h"
#include "Camera.h"
#include "Light.h"
#include "Xorshift.h"
#include "Material.h"
#include "Scene.h"
#include "Scene2D.h"
#include "Scene3D.h"
#include "SceneModel.h"
#include "ScenePolygon.h"
#include "SceneBillBoard.h"
#include "SceneShadow.h"
#include "Field.h"
#include "Player.h"
#include "Number.h"
#include "Particle.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Map.h"
#include "Motion.h"
#include "Grid.h"
#include "LifeBar.h"

class CCamera;
class CField;
class CPlayer;
class CEnemy;
class CMap;

//=================================================================================================
//�@�@�@�\���̒�`                                         
//=================================================================================================
typedef enum
{
	MODE_NONE = -1,			//�g���Ȃ����[�h
	MODE_TITLE,				//�^�C�g�����[�h
	MODE_GAME,				//�Q�[�����[�h
	MODE_RESULT,			//���U���g���[�h
	MODE_GAMEOVER,			//�Q�[���I�[�o�[���[�h
	MODE_TRAINING,			//�g���[�j���O���[�h
	MODE_MOTION_EDITING,	//���[�V�����ҏW���[�h
	MODE_TEST,				//�e�X�g���[�h
	MODE_MAX				//�g���Ȃ����[�h
}MODE_ID;

//=================================================================================================
//�@�@�@���[�h�����N���X                                       
//=================================================================================================
class CMode
{
public:
	virtual bool Init(void) { return true; };				//���[�h�N���X��������
	virtual void Uninit(void) = 0;							//���[�h�N���X�I������
	virtual void Update(void) = 0;							//���[�h�N���X�X�V����
	virtual void Draw(void) = 0;							//���[�h�N���X�`�揈��
	MODE_ID m_ModeId;										//���[�hID
	MODE_ID GetModeId(void) { return this->m_ModeId; };		//���[�hID�̎擾
	virtual CCamera* GetMainCamera(void) = 0;
	virtual CField* GetField(void) { return nullptr; };
};

//=================================================================================================
//�@�@�@�Q�[�����[�h�N���X                                       
//=================================================================================================
class CModeGame : public CMode
{
public:
	CModeGame()
	{
		m_nClipNum = 0;
		m_nClipNumLimit = 10;
		m_nMoney = 0;
	};
	~CModeGame(void) {};
	bool Init(void);												//�Q�[�����[�h�N���X��������
	void Uninit(void);												//�Q�[�����[�h�N���X�I������
	void Update(void);												//�Q�[�����[�h�N���X�X�V����
	void Draw(void);												//�Q�[�����[�h�N���X�`�揈��										//
	
private:
	CCamera *m_Camera;												//�J�����̃A�h���X�|�C���^�𐺖�
	CField * m_Field;												//�t�B�[���h�̃A�h���X�|�C���^�𐺖�
	CPlayer * m_Player;												//�v���[���[�̃A�h���X�|�C���^�𐺖�
	CEnemy* m_Enemy;												//
	CLight *m_Light;											//���C�g�̃A�h���X�|�C���^�𐺖�
	CXorshift* m_Xorshift;									//
	CSceneModel * m_SceneModelEnemy;							//�G���f�����O�̃A�h���X�|�C���^�𐺖�
	CSceneModel * m_SceneModelBuliding;						//���f�����O�̃A�h���X�|�C���^�𐺖�
	CNumber * m_Number;										//�X�R�A�����̃A�h���X�|�C���^�𐺖�
	CScenePolygon  * m_ScenePolygon;							//3D�|���S���̃A�h���X�|�C���^�𐺖�
	CSceneBillBoard  * m_SceneBillBoard;						//�r���{�[�h�̃A�h���X�|�C���^�𐺖�
	CSceneModel* m_SceneModel;								//
	CBullet* m_Bullet;										//
	CEnemy* m_Bulid;											//
	CMap* m_Map;
	int m_nEnemyCount;												//�G�L��
	int m_nClipNum;													//
	int m_nClipNumLimit;											//
	int m_nMoney;													//
public:
	CCamera * GetMainCamera(void) { return m_Camera; };		//�J�����̃A�h���X���擾
	CField* GetField(void) { return m_Field; };				//�t�B�[���h�̃A�h���X���擾
	CPlayer* GetMainPlayer(void) { return m_Player; };		//�v���[���[�̃A�h���X���擾
	CEnemy* GetMainEnemy(void) { return m_Enemy; };			//�v���[���[�̃A�h���X���擾

};

//=================================================================================================
//�@�@�@�^�[�g�����[�h�N���X                                       
//=================================================================================================
class CModeTitle : public CMode
{
public:
	bool Init(void);												//�^�[�g�����[�h�N���X��������
	void Uninit(void);												//�^�[�g�����[�h�N���X�I������
	void Update(void);												//�^�[�g�����[�h�N���X�X�V����
	void Draw(void);												//�^�[�g�����[�h�N���X�`�揈��
	CCamera* GetMainCamera(void) { return m_Camera; };				//�J�����̃A�h���X���擾
private:
	CCamera* m_Camera;										//�J�����̃A�h���X�|�C���^�𐺖�
	CLight* m_Light;											//���C�g�̃A�h���X�|�C���^�𐺖�
	CScene2D* m_Scene2D;										//2D�摜�̃A�h���X�|�C���^�𐺖�
	CSceneModel* m_Model;											//
	CSceneModel* m_ModelSkyBox;										//
};

//=================================================================================================
//�@�@�@���U���g���[�h�N���X                                       
//=================================================================================================
class CModeResult : public CMode
{
public:
	CModeResult(int nMoney)
	{
		m_nMoney = nMoney;
	};
	bool Init(void);												//���U���g���[�h�N���X��������
	void Uninit(void);												//���U���g���[�h�N���X�I������
	void Update(void);												//���U���g���[�h�N���X�X�V����
	void Draw(void);												//���U���g���[�h�N���X�`�揈��
	CCamera* GetMainCamera(void) { return m_Camera; };				//�J�����̃A�h���X���擾
private:
	CCamera* m_Camera;										//�J�����̃A�h���X�|�C���^�𐺖�
	CLight* m_Light;											//���C�g�̃A�h���X�|�C���^�𐺖�
	CScene2D* m_Scene2D;										//2D�摜�̃A�h���X�|�C���^�𐺖�
	CNumber* m_Money;
	int m_nMoney;
};

//=================================================================================================
//�@�@�@�Q�[���I�[�o�[���[�h�N���X                                       
//=================================================================================================
class CModeGameOver : public CMode
{
public:
	CModeGameOver(int nMoney)
	{
		m_nMoney = nMoney;
	};
	bool Init(void);												//�Q�[���I�[�o�[���[�h�N���X��������
	void Uninit(void);												//�Q�[���I�[�o�[���[�h�N���X�I������
	void Update(void);												//�Q�[���I�[�o�[���[�h�N���X�X�V����
	void Draw(void);												//�Q�[���I�[�o�[���[�h�N���X�`�揈��
	CCamera* GetMainCamera(void) { return m_Camera; };				//�J�����̃A�h���X���擾
private:
	CCamera* m_Camera;										//�J�����̃A�h���X�|�C���^�𐺖�
	CLight* m_Light;											//���C�g�̃A�h���X�|�C���^�𐺖�
	CScene2D* m_Scene2D;										//2D�摜�̃A�h���X�|�C���^�𐺖�
	CNumber* m_Money;
	int m_nMoney;
};

//=================================================================================================
//�@�@�@�g���[�j���O���[�h�N���X                                       
//=================================================================================================
class CModeTraining : public CMode
{
public:
	bool Init(void);												//�g���[�j���O���[�h�N���X��������
	void Uninit(void);												//�g���[�j���O���[�h�N���X�I������
	void Update(void);												//�g���[�j���O���[�h�N���X�X�V����
	void Draw(void);												//�g���[�j���O���[�h�N���X�`�揈��
	CCamera* GetMainCamera(void) { return m_Camera; };				//�J�����̃A�h���X���擾
private:
	CCamera* m_Camera;										//�J�����̃A�h���X�|�C���^�𐺖�
	CLight* m_Light;											//���C�g�̃A�h���X�|�C���^�𐺖�
	CScene2D* m_Scene2D;										//2D�摜�̃A�h���X�|�C���^�𐺖�
};

//=================================================================================================
//�@�@�@���[�V�����ҏW���[�h�N���X                                       
//=================================================================================================
class CModeMotionEditing : public CMode
{
public:
	bool Init(void);												//�g���[�j���O���[�h�N���X��������
	void Uninit(void);												//�g���[�j���O���[�h�N���X�I������
	void Update(void);												//�g���[�j���O���[�h�N���X�X�V����
	void Draw(void);												//�g���[�j���O���[�h�N���X�`�揈��
	CCamera* GetMainCamera(void) { return m_Camera; };				//�J�����̃A�h���X���擾
private:
	CCamera* m_Camera;												//�J�����̃A�h���X�|�C���^�𐺖�
	CLight* m_Light;												//���C�g�̃A�h���X�|�C���^�𐺖�
	CGrid* m_Grid;													//�O���b�h�̃A�h���X�|�C���^�𐺖�
	CMotion* m_Motion;												//
};

//=================================================================================================
//�@�@�@�e�X�g���[�h�N���X                                       
//=================================================================================================
class CModeTest : public CMode
{
public:
	bool Init(void);												//�g���[�j���O���[�h�N���X��������
	void Uninit(void);												//�g���[�j���O���[�h�N���X�I������
	void Update(void);												//�g���[�j���O���[�h�N���X�X�V����
	void Draw(void);												//�g���[�j���O���[�h�N���X�`�揈��
	CCamera* GetMainCamera(void) { return m_Camera; };				//�J�����̃A�h���X���擾
private:
	CCamera* m_Camera;												//�J�����̃A�h���X�|�C���^�𐺖�
	CLight* m_Light;												//���C�g�̃A�h���X�|�C���^�𐺖�
	CField * m_Field;												//�t�B�[���h�̃A�h���X�|�C���^�𐺖�
	CSceneModel* m_Model;											//
	CSceneShadow* m_Shadow;											//
	CSceneModel* m_ModelSkyBox;										//
	
};


#endif