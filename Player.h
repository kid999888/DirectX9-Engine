//=================================================================================================
//                                                        
//�@�@�@�v���[���[�N���X�v���O����[Player.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.05.23      
//                                                        
//=================================================================================================
#ifndef _CPLAYER_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _CPLAYER_H_
#include"Scene.h"
#include"SceneModel.h"

//=================================================================================================
//�@�@�@�t�B�[���h�N���X                                       
//=================================================================================================
class CPlayer : public CScene
{
public:
	CPlayer(int nPriority) : CScene(nPriority)
	{
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fRotX = 0.0f;
		m_fRotY = 0.0f;
		m_fRotZ = 0.0f;
		m_pTexture = nullptr;
	};												//�t�B�[���h�R���X�g���N�^
	~CPlayer();										//�t�B�[���h�f�X�g���N�^
	bool Init(void);								//�t�B�[���h��������
	void Uninit(void);								//�t�B�[���h�I������
	void Update(void);								//�t�B�[���h�X�V����
	void Draw(void);								//�t�B�[���h�`�揈��
	static CPlayer * Create(D3DXVECTOR3 vePosition);					//�t�B�[���h�̃C���X�^���X����

private:
	CSceneModel * m_pPlayer;
};

#endif