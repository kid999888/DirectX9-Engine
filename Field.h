//=================================================================================================
//                                                        
//�@�@�@�t�B�[���h�v���O����[Field.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _CFIELD_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _CFIELD_H_
#include "main.h"
#include "Scene.h"

//=================================================================================================
//�@�@�@�\���̒�`                                         
//=================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;            //XYZW���W
	D3DXVECTOR3 fs;				//�@��
	D3DCOLOR color;             //�F���
	D3DXVECTOR2 texcoord;       //�e�N�X�`�����W
}VERTEX_3D;

//=================================================================================================
//�@�@�@�t�B�[���h�N���X                                       
//=================================================================================================
class CField: public CScene
{
public:
	CField(int nPriority, int nNumX, int nNumZ, bool bNeat = false);														//�t�B�[���h�R���X�g���N�^
	~CField();												//�t�B�[���h�f�X�g���N�^
	bool Init(void);										//�t�B�[���h��������
	void Uninit(void);										//�t�B�[���h�I������
	void Update(void);										//�t�B�[���h�X�V����
	void Draw(void);										//�t�B�[���h�`�揈��
	static CField * Create(int nNumX, int nNumZ, bool bNeat = false);			//�t�B�[���h�̃C���X�^���X����
	int GetBlockNumX(void)									//�t�B�[���hX�����u���b�N�����擾
	{
		return m_nNumX;
	};
	int GetBlockNumZ(void)									//�t�B�[���hZ�����u���b�N�����擾
	{
		return m_nNumZ;
	};
	VERTEX_3D* GetFiledPos(void)							//���_���Ǘ����������擾
	{
		return m_pvMeshFiledPos;
	};							

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//���_�o�b�t�@�Ǘ����郁����
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//�C���f�b�N�X�o�b�t�@�Ǘ����郁��
	VERTEX_3D *m_pvMeshFiledPos;							//���_���Ǘ�������
	int m_nFiledPosNumber;									//���_��
	int m_nFiledIndexNumber;								//�C���f�b�N�X��
	int m_nFiledPrimitiveNumber;							//Primitive��
	int m_nNumX;											//�t�B�[���h��X�u���b�N��
	int m_nNumZ;											//�t�B�[���h��Z�u���b�N��
	float m_fheightScale;									//�t�@�C�����x���k���W��
	bool m_bNeat;											//
};

#endif
