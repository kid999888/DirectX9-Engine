//=================================================================================================
//                                                        
//�@�@�@���[�h�����N���X �v���O����[Mode.h]
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.03      
//                                                        
//=================================================================================================
#ifndef _MODE_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _MODE_H_

#include"main.h"
#include"Renderer.h"
#include"Camera.h"
#include"Light.h"
#include"Material.h"
#include"Scene.h"
#include"Scene2D.h"
#include"Scene3D.h"
#include"SceneModel.h"
#include"ScenePolygon.h"
#include"SceneBillBoard.h"
#include"Field.h"
#include"Player.h"
#include"Number.h"
#include"Particle.h"

//=================================================================================================
//�@�@�@�\���̒�`                                         
//=================================================================================================
typedef enum
{
	MODE_NONE = -1,			//�g���Ȃ����[�h
	MODE_TITLE,				//�^�C�g�����[�h
	MODE_GAME,				//�Q�[�����[�h
	MODE_RESULT,			//���U���g���[�h
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
};

//=================================================================================================
//�@�@�@�Q�[�����[�h�N���X                                       
//=================================================================================================
class CModeGame : public CMode
{
public:
	bool Init(void);												//�Q�[�����[�h�N���X��������
	void Uninit(void);												//�Q�[�����[�h�N���X�I������
	void Update(void);												//�Q�[�����[�h�N���X�X�V����
	void Draw(void);												//�Q�[�����[�h�N���X�`�揈��
	static CCamera* GetMainCamera(void) { return m_Camera; };		//�J�����̃A�h���X���擾
	static CField* GetField(void) { return m_Field; };				//�t�B�[���h�̃A�h���X���擾
	static CPlayer* GetMainPlayer(void) { return m_Player; };		//�v���[���[�̃A�h���X���擾
private:
	static CCamera *m_Camera;										//�J�����̃A�h���X�|�C���^�𐺖�
	static CLight *m_Light;											//���C�g�̃A�h���X�|�C���^�𐺖�
	static CField * m_Field;										//�t�B�[���h�̃A�h���X�|�C���^�𐺖�
	static CPlayer * m_Player;										//�v���[���[�̃A�h���X�|�C���^�𐺖�
	static CScene3D * m_Scene3D;									//3D�L���[�u�̃A�h���X�|�C���^�𐺖�
	static CNumber * m_Number;										//�X�R�A�����̃A�h���X�|�C���^�𐺖�
	static CScenePolygon  * m_ScenePolygon;							//3D�|���S���̃A�h���X�|�C���^�𐺖�
	static CSceneBillBoard  * m_SceneBillBoard;						//�r���{�[�h�̃A�h���X�|�C���^�𐺖�
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
private:
	static CCamera* m_Camera;										//�J�����̃A�h���X�|�C���^�𐺖�
	static CLight* m_Light;											//���C�g�̃A�h���X�|�C���^�𐺖�
	static CScene2D* m_Scene2D;										//2D�摜�̃A�h���X�|�C���^�𐺖�
};

//=================================================================================================
//�@�@�@���U���g���[�h�N���X                                       
//=================================================================================================
class CModeResult : public CMode
{
public:
	bool Init(void);												//���U���g���[�h�N���X��������
	void Uninit(void);												//���U���g���[�h�N���X�I������
	void Update(void);												//���U���g���[�h�N���X�X�V����
	void Draw(void);												//���U���g���[�h�N���X�`�揈��
private:
	static CCamera* m_Camera;										//�J�����̃A�h���X�|�C���^�𐺖�
	static CLight* m_Light;											//���C�g�̃A�h���X�|�C���^�𐺖�
	static CScene2D* m_Scene2D;										//2D�摜�̃A�h���X�|�C���^�𐺖�
};

#endif