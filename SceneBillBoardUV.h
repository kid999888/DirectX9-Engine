//=================================================================================================
//                                                        
//�@�@�@�r���{�[�h�N���X�v���O����[SceneBillBoard.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.09      
//                                                        
//=================================================================================================
#ifndef _SCENEBILLBOARDUV_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _SCENEBILLBOARDUV_H_
#include "Scene.h"
#include "Camera.h"
#include<string>

//=================================================================================================
//�@�@�@�r���{�[�h�N���X                                       
//=================================================================================================
class CSceneBillBoardUV : public CScene
{
public:
	CSceneBillBoardUV(CCamera* pCamera,int nPriority, std::string stFileName);							//�r���{�[�h�N���X�R���X�g���N�^
	~CSceneBillBoardUV();										//�r���{�[�h�N���X�f�X�g���N�^
	bool Init(void);										//�r���{�[�h�N���X��������
	void Uninit(void);										//�r���{�[�h�N���X�I������
	void Update(void);										//�r���{�[�h�N���X�X�V����
	void Draw(void);										//�r���{�[�h�N���X�`�揈��
	static CSceneBillBoardUV * Create(CCamera* pCamera, std::string stFileName);					//�r���{�[�h�̃C���X�^���X����
	void SetTextureUV(float U0, float V0, float U1, float V1);				//�r���{�[�h�̃e�N�X�`��UV�̐ݒ�
	float GetU0(void) { return m_fU0; };
	float GetV0(void) { return m_fV0; };
	float GetU1(void) { return m_fU1; };
	float GetV1(void) { return m_fV1; };

private:
	std::string stFileNameModel;											//�t�@�C���p�X�̊Ǘ�������
	D3DXIMAGE_INFO m_D3DTextureInfo;										//�e�N�X�`�����̊Ǘ�������
	void CreateVertexAffine(D3DCOLOR color);
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;				//���_�o�b�t�@�Ǘ����郁����
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;					//�C���f�b�N�X�o�b�t�@�Ǘ����郁��
	D3DXMATRIX m_mtxTranspose;								//�r���[�s��̓]�u�s��
	CCamera* m_pCamera;										//
	float m_fU0;
	float m_fV0;
	float m_fU1;
	float m_fV1;
};

#endif