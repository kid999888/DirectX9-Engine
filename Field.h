//=================================================================================================
//                                                        
//�@�@�@�t�B�[���h�v���O����[Field.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _CFIELD_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _CFIELD_H_
#include"Scene.h"

//=================================================================================================
//�@�@�@�t�B�[���h�N���X                                       
//=================================================================================================
class CField: public CScene
{
public:
	CField(int nPriority) : CScene(nPriority)
	{
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fRotX = 0.0f;
		m_fRotY = 0.0f;
		m_fRotZ = 0.0f;
		m_pTexture = nullptr;
		m_pVertexBuffer = NULL;
		m_pIndexBuffer = NULL;
	};												//�t�B�[���h�R���X�g���N�^
	~CField();										//�t�B�[���h�f�X�g���N�^
	bool Init(void);								//�t�B�[���h��������
	void Uninit(void);								//�t�B�[���h�I������
	void Update(void);								//�t�B�[���h�X�V����
	void Draw(void);								//�t�B�[���h�`�揈��
	static CField * Create(void);					//�t�B�[���h�̃C���X�^���X����

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//���_�o�b�t�@�Ǘ����郁����
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//�C���f�b�N�X�o�b�t�@�Ǘ����郁��
	int m_FiledPosNumber;									//���_��
	int m_FiledIndexNumber;									//�C���f�b�N�X��
	int m_FiledPrimitiveNumber;								//Primitive��
};

#endif
