//=================================================================================================
//                                                        
//�@�@�@�v���[���[�N���X�v���O����[Player.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.05.23      
//                                                        
//=================================================================================================
#ifndef _CPLAYER_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _CPLAYER_H_
#include "Scene.h"
#include "SceneModel.h"
#include "Mode.h"


#include "Camera.h"
#include "Bullet.h"
#include<vector>
using namespace std;
class CMode;

//=================================================================================================
//�@�@�@�t�B�[���h�N���X                                       
//=================================================================================================
class CPlayer : public CScene
{
public:
	CPlayer(CMode* Mode,int nPriority);		//�v���[���[�R���X�g���N�^
	~CPlayer();											//�v���[���[�f�X�g���N�^
	bool Init(void);									//�v���[���[��������
	void Uninit(void);									//�v���[���[�I������
	void Update(void);									//�v���[���[�X�V����
	void Draw(void);									//�v���[���[�`�揈��
	static CPlayer * Create(CMode* Mode, D3DXVECTOR3 vePosition);	//�v���[���[�̃C���X�^���X����
	D3DXVECTOR3 GetPlayerFront(void)					//�v���[���[�̌����x�N�g�����擾
	{
		return m_vePlayerFront;
	};
	D3DXVECTOR3 GetPlayerMouse(void)
	{
		return m_vePlayerMousePoint;
	}
	int GetPlayerHp(void) {return _nHp;};
	void SetPlayerHp(int nHp) { _nHp = nHp; };

private:
	CMode* m_CurrentMode;
	CSceneModel * m_pPlayer;							//�v���[���[�̃��f�����O�Ǘ�����A�h���X�𐺖�
	CCamera *m_Camera;									//�J�����Ǘ����郁���o�[�A�h���X�𐺖�
	D3DXVECTOR3 m_vePlayerFront;						//�v���[���[�̌����x�N�g��
	D3DXVECTOR3 m_vePlayerMousePoint;						//�v���[���[�̌����x�N�g��
	float m_fMoveSpeed;									//�ړ��X�r�[�g
	float m_fRotYSpeed;									//��]�X�r�[�g
	float m_fRotOnce;									//�v���[���[����]�p�x
	int m_fRotYExactly;									//��]���E
	int _nHp;
};

#endif