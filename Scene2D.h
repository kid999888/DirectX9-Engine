//=================================================================================================
//                                                        
//�@�@�@2D�|���S���v���O����[Scene2D.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================
#ifndef _SCENE2D_H_                                                 //2�d�C���N���[�h�h�~�̃}�N����`
#define _SCENE2D_H_
#include"Scene.h"
#include<string>

//=================================================================================================
//�@�@�@2D�|���S���N���X                                       
//=================================================================================================
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority, std::string stFileName, int nNx, int nNy) : CScene(nPriority)
	{
		m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_vePosition = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		m_nTextureNumber.x = 0;
		m_nTextureNumber.y = 0;
		m_npTLimitNum.x = nNx;
		m_npTLimitNum.y = nNy;
		m_pTexture = nullptr;
		m_pVertexBuffer = NULL;
		stFileNameModel = stFileName;
	};																		//2D�|���S���R���X�g���N�^
	~CScene2D();															//2D�|���S���f�X�g���N�^
	bool Init(void);														//2D�|���S����������
	void Uninit(void);														//2D�|���S���I������
	void Update(void);														//2D�|���S���X�V����
	void Draw(void);														//2D�|���S���`�揈��
	static CScene2D * Create(int nPriority, std::string stFileName, int nNx, int nNy);		//2D�|���S���̃C���X�^���X����
	void SetTextureNum(int nX, int nY);										//2D�|���S���̃e�N�X�`���i���o�[�̐ݒ�
	int Get2DObjectHeight(void)												//�e�N�X�`���̍��x���擾
	{
		return m_D3DTextureInfo.Height;
	};
	int Get2DObjectWidth(void)												//�e�N�X�`���̕����擾
	{
		return m_D3DTextureInfo.Width;
	};

private:
	Point2DI m_nTextureNumber;												//2D�|���S���̌���UV�i�����j
	Point2DI m_npTLimitNum;													//2D�|���S����UV����
	D3DXIMAGE_INFO m_D3DTextureInfo;										//�e�N�X�`�����̊Ǘ�������
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;								//���_�o�b�t�@�Ǘ����郁����
	void CreateVertexAffine(D3DCOLOR color, int tCx, int tCy);				//���_�o�b�t�@����
	std::string stFileNameModel;											//�t�@�C���p�X�̊Ǘ�������
};

#endif