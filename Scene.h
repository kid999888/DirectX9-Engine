//=================================================================================================
//                                                        
//�@�@�@�I�u�W�F�N�g�����N���X �v���O����[Scene.h]
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENE_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _SCENE_H_
#include"main.h"
#include"Material.h"

//=================================================================================================
//�@�@�@�񋓑�                                      
//=================================================================================================
enum SCENE_TYPE
{
	SCENE_TYPE_NONE,
	SCENE_TYPE_2D,
	SCENE_TYPE_3D,
	SCENE_TYPE_PLAYER,
	SCENE_TYPE_ENEMY,
	SCENE_TYPE_BULLET,
};

//=================================================================================================
//�@�@�@�I�u�W�F�N�g�����N���X                                       
//=================================================================================================
class CScene
{
public:
	CScene(int nPriorty);
	CScene(void);
	virtual ~CScene() {};
	virtual bool Init(void) { return true; };			//�I�u�W�F�N�g��������
	virtual void Uninit(void) = 0;						//�I�u�W�F�N�g�I������
	virtual void Update(void) = 0;						//�I�u�W�F�N�g�X�V����
	virtual void Draw(void) = 0;						//�I�u�W�F�N�g�`�揈��

	void SetScale(D3DXVECTOR3 veScale);					//�I�u�W�F�N�g�̊g�k�{���ݒ�
	void SetScaleX(float fX);							//�I�u�W�F�N�g�̊g�k�{��X�ݒ�
	void SetScaleY(float fY);							//�I�u�W�F�N�g�̊g�k�{��Y�ݒ�
	void SetScaleZ(float fZ);							//�I�u�W�F�N�g�̊g�k�{��Z�ݒ�
	void SetRotation(D3DXVECTOR3 veRotation);			//�I�u�W�F�N�g�̎���]�l�ݒ�
	void SetRotationX(float fX);						//�I�u�W�F�N�g��X����]�l�ݒ�
	void SetRotationY(float fY);						//�I�u�W�F�N�g��Y����]�l�ݒ�
	void SetRotationZ(float fZ);						//�I�u�W�F�N�g��Z����]�l�ݒ�
	void SetPosition(D3DXVECTOR3 vePosition);			//�I�u�W�F�N�g�̈ʒu�ݒ�
	void SetPositionX(float fX);						//�I�u�W�F�N�g�̈ʒuX�ݒ�
	void SetPositionY(float fY);						//�I�u�W�F�N�g�̈ʒuY�ݒ�
	void SetPositionZ(float fZ);						//�I�u�W�F�N�g�̈ʒuZ�ݒ�

	D3DXVECTOR3 GetScale(void);							//�I�u�W�F�N�g�̊g�k�{���擾
	float GetScaleX(void);								//�I�u�W�F�N�g�̊g�k�{��X�擾
	float GetScaleY(void);								//�I�u�W�F�N�g�̊g�k�{��Y��
	float GetScaleZ(void);								//�I�u�W�F�N�g�̊g�k�{��Z��
	D3DXVECTOR3 GetRotation(void);						//�I�u�W�F�N�g�̎���]�l�擾
	float GetRotationX(void);							//�I�u�W�F�N�g��X����]�l�擾
	float GetRotationY(void);							//�I�u�W�F�N�g��Y����]�l�擾
	float GetRotationZ(void);							//�I�u�W�F�N�g��Z����]�l�擾
	D3DXVECTOR3 GetPosition(void);						//�I�u�W�F�N�g�̈ʒu�擾
	float GetPositionX(void);							//�I�u�W�F�N�g�̈ʒuX�擾
	float GetPositionY(void);							//�I�u�W�F�N�g�̈ʒuY�擾
	float GetPositionZ(void);							//�I�u�W�F�N�g�̈ʒuZ�擾
	
	void Release(void);									//�I�u�W�F�N�g�̃����[�X
	static void UpdateAll(void);						//�I�u�W�F�N�g�S�̍X�V����
	static void DrawAll(void);							//�I�u�W�F�N�g�S�̕`�揈��	
	static void ReleaseAll(void);						//�I�u�W�F�N�g�̑S�̃����[�X����
	static CScene *m_Scene[3][30];						//�V�[���̊Ǘ������o�[�֐�
	SCENE_TYPE m_Type;
	SCENE_TYPE GetType(void)
	{
		return this->m_Type;
	};

protected:
	D3DXVECTOR3 m_veScale;								//�I�u�W�F�N�g�̊g�k�{��
	D3DXVECTOR3 m_veRotation;							//�I�u�W�F�N�g�̎���]
	D3DXVECTOR3 m_vePosition;							//�I�u�W�F�N�g�̈ʒu
	LPDIRECT3DTEXTURE9* m_pTexture;						//�e�N�X�`���Ǘ����郁����
	CMaterial *m_Material;								//�}�e���A���̊Ǘ����郁����
	D3DXMATRIX m_mtxWorld;								//�I�u�W�F�N�g���[���h�s��ϐ�
	D3DXMATRIX m_mtxWorldR;								//�I�u�W�F�N�g���[���h �L���[�u�̉�]�s��
	D3DXMATRIX m_mtxWorldRX;							//�I�u�W�F�N�g���[���h �L���[�u��X������]�s��
	D3DXMATRIX m_mtxWorldRY;							//�I�u�W�F�N�g���[���h �L���[�u��Y������]�s��
	D3DXMATRIX m_mtxWorldRZ;							//�I�u�W�F�N�g���[���h �L���[�u��Z������]�s��
	D3DXMATRIX m_mtxWorldT;								//�I�u�W�F�N�g���[���h �L���[�u�̕��s�ړ��s��
	D3DXMATRIX m_mtxWorldS;								//�I�u�W�F�N�g���[���h �L���[�u�̕��s�ړ��s��
	bool m_bDraw;										//�I�u�W�F�N�g�`�攻�f�ϐ�
};

#endif