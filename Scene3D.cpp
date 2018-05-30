//=================================================================================================
//                                                        
//�@�@�@3D�L���[�u�N���X�v���O����[Scene3D.cpp]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.04.17      
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include"Scene3D.h"
#include"Material.h"
#include"Renderer.h"

//=================================================================================================
//		�}�N����`                                        
//=================================================================================================
//FVF�̐錾
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)    //3D�|���S���̒��_���
//�e�N�X�`���t�@�C���p�X
#define TEXTUREFILENAME000	        "Data\\Texture\\horoCube.png"	

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
//�@�@�@3D�L���[�u�N���X�f�X�g���N�^                                     
//=================================================================================================
CScene3D::~CScene3D()
{
}

//=================================================================================================
//�@�@�@3D�L���[�u�N���X��������                                     
//=================================================================================================
bool CScene3D::Init(void)
{
	HRESULT hr[2];
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	m_pTexture = new LPDIRECT3DTEXTURE9[1];

	hr[0] = D3DXCreateTextureFromFile(
		pDevice,
		TEXTUREFILENAME000,
		m_pTexture);

	if (FAILED(hr[0]))
	{
		MessageBox(NULL, "�G���[", "�e�N�X�`�����ǂݍ��߂Ȃ��B", MB_OK);
		return false;
	}

	int tw = 1024;
	int th = 1024;

	float fu0[6], fv0[6], fu1[6], fv1[6];

	for (int nCount = 0;nCount < 6;nCount++)
	{
		fu0[nCount] = 256.0f * (nCount % 4) / tw;
		fv0[nCount] = 256.0f * (nCount / 4) / th;
		fu1[nCount] = ((256.0f * (nCount % 4)) + 256) / tw;
		fv1[nCount] = ((256.0f * (nCount / 4)) + 256) / th;
	}

	static WORD index[] = {
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		8,9,10,
		10,11,8,

		12,13,14,
		14,15,12,

		16,17,18,
		18,19,16,

		20,21,22,
		22,23,20,
	};



	//���_�̍쐬
	VERTEX_3D v[] = {
	// �O�̖ʁi���F�j
	{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(fu0[0],fv0[0]) },	//0
	{ D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(fu1[0],fv0[0]) },		//1
	{ D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(fu1[0],fv1[0]) },		//2
	{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(fu0[0],fv1[0]) },		//3

																																			// ���̖ʁi�ΐF�j
	{ D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(-1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu0[1],fv0[1]) },		//4
	{ D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(-1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu1[1],fv0[1]) },		//5
	{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(-1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu1[1],fv1[1]) },		//6
	{ D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(-1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu0[1],fv1[1]) },		//7

																																			// ���̖ʁi�F�j
	{ D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu0[2],fv0[2]) },			//8
	{ D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu1[2],fv0[2]) },		//9
	{ D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu1[2],fv1[2]) },		//10
	{ D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f, 0.0f, 1.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu0[2],fv1[2]) },		//11

																																		// �E�̖ʁi�ԐF�j
	{ D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu0[3],fv0[3]) },		//12
	{ D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu1[3],fv0[3]) },			//13
	{ D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu1[3],fv1[3]) },		//14
	{ D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(1.0f, 0.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu0[3],fv1[3]) },		//15

																																			// ��̖ʁi���F�j
	{ D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu0[4],fv0[4]) },		//16
	{ D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu1[4],fv0[4]) },		//17
	{ D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(fu1[4],fv1[4]) },		//18
	{ D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu0[4],fv1[4]) },		//19

																																			// ���̖ʁi�ΐF�j
	{ D3DXVECTOR3(0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu0[5],fv0[5]) },		//20
	{ D3DXVECTOR3(-0.5f,-0.5f,0.5f),D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu1[5],fv0[5]) },		//21
	{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu1[5],fv1[5]) },		//22
	{ D3DXVECTOR3(0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f, -1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(fu0[5],fv1[5]) },		//23
	};

	//���_Vertex�o�b�t�@�����
	hr[0] = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 24,						//���_���̈�m��
		D3DUSAGE_WRITEONLY,							//�g�p�p�r(��������ł���)
		FVF_VERTEX_3D,								//FVF�A�O�ł����v
		D3DPOOL_MANAGED,							//���_�o�b�t�@�̊Ǘ����@(Device�ɊǗ�����)
		&m_pVertexBuffer,							//�Ǘ��҂̃������ꏊ
		NULL);

	//�C���f�b�N�X�o�b�t�@�����
	hr[1] = pDevice->CreateIndexBuffer(
		sizeof(WORD) * 36,							//���[���h�s����̈�m��
		D3DUSAGE_WRITEONLY,							//�g�p�p�r(��������ł���)
		D3DFMT_INDEX16,								//FMT,DWORD�̏ꍇ��D3DFMT_INDEX32
		D3DPOOL_MANAGED,							//���_�o�b�t�@�̊Ǘ����@(Device�ɊǗ�����)
		&m_pIndexBuffer,							//�C���f�b�N�X�o�b�t�@�Ǘ����郁����
		NULL);

	//���_�o�b�t�@NULL�`�F�b�N
	if (FAILED(hr[0]))
	{
		MessageBox(NULL, "���_�o�b�t�@�����Ȃ�", "�G���[", MB_OK);							//���_�o�b�t�@�G���[���b�Z�[�W
		return false;
	}

	//�C���f�b�N�X�o�b�t�@NULL�`�F�b�N
	if (FAILED(hr[1]))
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�����Ȃ�", "�G���[", MB_OK);							//���_�o�b�t�@�G���[���b�Z�[�W
		return false;
	}

	VERTEX_3D* pV;
	m_pVertexBuffer->Lock(0, 0,						//���_�o�b�t�@���b�N(�n�܂�A�̈�Avoid�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		(void**)&pV,								//���_�o�b�t�@���b�N(void�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		D3DLOCK_DISCARD);

	//���_����pV�ɏ��������
	//�@���܂ł̔z����g�p�cPV��V�̓��e�R�s�[����B�imemcpy�g�p���āj
	memcpy(&pV[0], &v[0], sizeof(VERTEX_3D) * 24);

	//�A���ڏ���

	m_pVertexBuffer->Unlock();


	LPWORD pIndex;
	m_pIndexBuffer->Lock(0, 0,						//���_�o�b�t�@���b�N(�n�܂�A�̈�Avoid�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		(void**)&pIndex,							//���_�o�b�t�@���b�N(void�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		D3DLOCK_DISCARD);

	//�C���f�b�N�X��pIndex�ɏ��������
	//�@���܂ł̔z����g�p�cPV��V�̓��e�R�s�[����B�imemcpy�g�p���āj
	memcpy(&pIndex[0], &index[0], sizeof(WORD) * 36);
	//�A���ڏ���

	m_pIndexBuffer->Unlock();

	//�C���X�^���X����
	m_Material = new CMaterial();
	m_Material->Init();

	
	

	return true;
}

//=================================================================================================
//�@�@�@3D�L���[�u�N���X�I������                                     
//=================================================================================================
void CScene3D::Uninit(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_DELETE_ARRAY(m_pTexture);
	SAFE_DELETE(m_Material);
}

//=================================================================================================
//�@�@�@3D�L���[�u�N���X�X�V����                                     
//=================================================================================================
void CScene3D::Update(void)
{
	m_Material->Update();
	//m_fRotX += 0.0f;
	m_fRotY += 0.05f;
	//m_fRotZ += 0.0f;
}

//=================================================================================================
//�@�@�@3D�L���[�u�N���X�`�揈��                                     
//=================================================================================================
void CScene3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	//�g��k���s������
	D3DXMatrixScaling(&m_mtxWorldS, 1.0f, 1.0f, 1.0f);

	//��]�s������
	D3DXMatrixRotationX(&m_mtxWorldRX, m_fRotX);
	D3DXMatrixRotationY(&m_mtxWorldRY, m_fRotY);
	D3DXMatrixRotationZ(&m_mtxWorldRZ, m_fRotZ);

	//��]�s�������	
	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldRX, &m_mtxWorldRY);
	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldR, &m_mtxWorldRZ);

	//���s�ړ��s��̍���
	D3DXMatrixTranslation(&m_mtxWorldT, m_vePosition.x, m_vePosition.y, m_vePosition.z);

	//�s��	
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldS, &m_mtxWorldR);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldT);


	pDevice->SetStreamSource(0,
		m_pVertexBuffer, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(m_pIndexBuffer);


	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���C�gOFF
	pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

	//���[���h�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	//�e�N�X�`���\��t����
	pDevice->SetTexture(0, *m_pTexture);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//�o�b�t�@�g����
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,			//Primitive�`��^�C�v
		0,
		0,							//�C���f�b�N�X�̍ŏ��l	
		24,							//���_�̐�
		0,
		12);						//���@�[�e�b�N�X�f�[�^�̃T�C�Y
}

//=================================================================================================
//�@�@�@3D�L���[�u�N���X�̃C���X�^���X����                                   
//=================================================================================================
CScene3D * CScene3D::Create(void)
{
	CScene3D *Scene3D = new CScene3D(1);
	Scene3D->Init();
	return Scene3D;
}
