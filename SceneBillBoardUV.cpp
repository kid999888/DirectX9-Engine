//=================================================================================================
//                                                        
//�@�@�@�r���{�[�h�N���X�v���O����[SceneBillBoard.cpp]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.07.09      
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��
//=================================================================================================
#include "SceneBillBoardUV.h"
#include "Renderer.h"
#include "Camera.h"

//=================================================================================================
//		�}�N����`
//=================================================================================================
//FVF�̐錾
#define FVF_VERTEX_BILLBOARD ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)    //3D�|���S���̒��_���
//�e�N�X�`���t�@�C���p�X
#define TEXTUREFILENAME000	        "Data\\Texture\\Circle.png"	

//=================================================================================================
//�@�@�@�\���̒�`
//=================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;            //XYZW���W
	D3DXVECTOR3 fs;				//�@��
	D3DCOLOR color;             //�F���
	D3DXVECTOR2 texcoord;       //�e�N�X�`�����W
}VERTEX_BILLBOARD;

CSceneBillBoardUV::CSceneBillBoardUV(CCamera* pCamera,int nPriority, std::string stFileName) : CScene(nPriority)
{
	m_pCamera = pCamera;
	m_veScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_veRotation = D3DXVECTOR3(-90.0f, 0.0f, 0.0f);
	m_vePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pTexture = nullptr;
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;
	m_fU0 = 0.0f;
	m_fV0 = 0.0f;
	m_fU1 = 1.0f;
	m_fV1 = 1.0f;
	stFileNameModel = stFileName;
}

//=================================================================================================
//�@�@�@�r���{�[�h�N���X�f�X�g���N�^                                       
//=================================================================================================
CSceneBillBoardUV::~CSceneBillBoardUV()
{
}

//=================================================================================================
//�@�@�@�r���{�[�h�N���X��������             
//=================================================================================================
bool CSceneBillBoardUV::Init(void)
{
	HRESULT hr[2];
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	hr[0] = D3DXCreateTextureFromFile(
		pDevice,
		stFileNameModel.c_str(),
		&m_pTexture);

	if (FAILED(hr[0]))
	{
		MessageBox(NULL, "�G���[", "�e�N�X�`�����ǂݍ��߂Ȃ��B", MB_OK);
		return false;
	}

	//�e�N�X�`���̏���ǂݍ���
	hr[0] = D3DXGetImageInfoFromFile(stFileNameModel.c_str(), &m_D3DTextureInfo);

	static WORD index[] = {
		0,1,2,
		2,3,0,
	};

	//���_�̍쐬
	VERTEX_BILLBOARD v[] = {
		{ D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(0.0f,0.0f) },		//0
		{ D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(1.0f,0.0f) },		//1
		{ D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(1.0f,1.0f) },		//2
		{ D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 255, 255, 255) ,D3DXVECTOR2(0.0f,1.0f) },		//3
	};

	//���_Vertex�o�b�t�@�����
	hr[0] = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_BILLBOARD) * 4,						//���_���̈�m��
		D3DUSAGE_WRITEONLY,							//�g�p�p�r(��������ł���)
		FVF_VERTEX_BILLBOARD,								//FVF�A�O�ł����v
		D3DPOOL_MANAGED,							//���_�o�b�t�@�̊Ǘ����@(Device�ɊǗ�����)
		&m_pVertexBuffer,							//�Ǘ��҂̃������ꏊ
		NULL);

	//�C���f�b�N�X�o�b�t�@�����
	hr[1] = pDevice->CreateIndexBuffer(
		sizeof(WORD) * 6,							//���[���h�s����̈�m��
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

	VERTEX_BILLBOARD* pV;
	m_pVertexBuffer->Lock(0, 0,						//���_�o�b�t�@���b�N(�n�܂�A�̈�Avoid�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		(void**)&pV,								//���_�o�b�t�@���b�N(void�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		D3DLOCK_DISCARD);

	//���_����pV�ɏ��������
	//�@���܂ł̔z����g�p�cPV��V�̓��e�R�s�[����B�imemcpy�g�p���āj
	memcpy(&pV[0], &v[0], sizeof(VERTEX_BILLBOARD) * 4);

	//�A���ڏ���

	m_pVertexBuffer->Unlock();


	LPWORD pIndex;
	m_pIndexBuffer->Lock(0, 0,						//���_�o�b�t�@���b�N(�n�܂�A�̈�Avoid�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		(void**)&pIndex,							//���_�o�b�t�@���b�N(void�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		D3DLOCK_DISCARD);

	//�C���f�b�N�X��pIndex�ɏ��������
	//�@���܂ł̔z����g�p�cPV��V�̓��e�R�s�[����B�imemcpy�g�p���āj
	memcpy(&pIndex[0], &index[0], sizeof(WORD) * 6);
	//�A���ڏ���

	m_pIndexBuffer->Unlock();

	//�}�e���A���̃C���X�^���X����&�ݒ�
	m_Material = new CMaterial();

	return true;
}

//=================================================================================================
//�@�@�@�r���{�[�h�N���X�I������
//=================================================================================================
void CSceneBillBoardUV::Uninit(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_Material);
}

//=================================================================================================
//�@�@�@�r���{�[�h�N���X�X�V����
//=================================================================================================
void CSceneBillBoardUV::Update(void)
{
	D3DXMATRIX mtxView;
	mtxView = m_pCamera->GetCameraView();
	D3DXMatrixTranspose(&m_mtxTranspose, &mtxView);
	m_mtxTranspose._41 = 0.0f;
	m_mtxTranspose._42 = 0.0f;
	m_mtxTranspose._43 = 0.0f;
	m_mtxTranspose._14 = 0.0f;
	m_mtxTranspose._24 = 0.0f;
	m_mtxTranspose._34 = 0.0f;
}

//=================================================================================================
//�@�@�@�r���{�[�h�N���X�`�揈��
//=================================================================================================
void CSceneBillBoardUV::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	CreateVertexAffine(D3DCOLOR_RGBA(255, 255, 255, 255));

	//�g��k���s������
	D3DXMatrixScaling(&m_mtxWorldS, m_veScale.x, m_veScale.y, m_veScale.z);

	//��]�s������
	D3DXMatrixRotationX(&m_mtxWorldRX, D3DXToRadian(m_veRotation.x));
	D3DXMatrixRotationY(&m_mtxWorldRY, D3DXToRadian(m_veRotation.y));
	D3DXMatrixRotationZ(&m_mtxWorldRZ, D3DXToRadian(m_veRotation.z));

	//��]�s�������	
	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldRX, &m_mtxWorldRY);
	D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldR, &m_mtxWorldRZ);

	//���s�ړ��s��̍���
	D3DXMatrixTranslation(&m_mtxWorldT, m_vePosition.x, m_vePosition.y, m_vePosition.z);

	//�s�񍇐�	
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorldS, &m_mtxWorldR);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTranspose);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldT);


	pDevice->SetStreamSource(0,
		m_pVertexBuffer, 0, sizeof(VERTEX_BILLBOARD));

	pDevice->SetIndices(m_pIndexBuffer);


	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_BILLBOARD);

	//���C�gOFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 96);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���[���h�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�}�e���A���̍X�V
	m_Material->Update();

	//�e�N�X�`���\��t����
	pDevice->SetTexture(0, m_pTexture);

	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//�o�b�t�@�g����
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,			//Primitive�`��^�C�v
		0,
		0,							//�C���f�b�N�X�̍ŏ��l	
		4,							//���_�̐�
		0,
		2);							//���@�[�e�b�N�X�f�[�^�̃T�C�Y

	//���C�gON
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=================================================================================================
//�@�@�@�r���{�[�h�̃C���X�^���X����
//=================================================================================================
CSceneBillBoardUV * CSceneBillBoardUV::Create(CCamera* pCamera, std::string stFileName)
{
	CSceneBillBoardUV *SceneBillBoardUV = new CSceneBillBoardUV(pCamera,1, stFileName);
	SceneBillBoardUV->Init();
	return SceneBillBoardUV;
}

void CSceneBillBoardUV::SetTextureUV(float U0, float V0, float U1, float V1)
{
	m_fU0 = U0;
	m_fV0 = V0;
	m_fU1 = U1;
	m_fV1 = V1;
}

void CSceneBillBoardUV::CreateVertexAffine(D3DCOLOR color)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	float dx = m_vePosition.x;
	float dy = m_vePosition.y;

	int tw = m_D3DTextureInfo.Width;
	int th = m_D3DTextureInfo.Height;

	int dw = m_D3DTextureInfo.Width * m_fU1;
	int dh = m_D3DTextureInfo.Height * m_fV1;

	dw *= m_veScale.x;
	dh *= m_veScale.y;

	float u0 = m_fU0;
	float v0 = m_fV0;
	float u1 = m_fU1;
	float v1 = m_fV1;

	static WORD index[] = {
		0,1,2,
		2,3,0,
	};

	//���_�̍쐬
	VERTEX_BILLBOARD v[] = {
		{ D3DXVECTOR3(dx - (dw / 2.0f) - 0.5f,0.5f,dy + (dh / 2.0f) - 0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),color,D3DXVECTOR2(m_fU0,m_fV0) },		//0
		{ D3DXVECTOR3(dx + (dw / 2.0f) - 0.5f,0.5f,dy + (dh / 2.0f) - 0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),color,D3DXVECTOR2(m_fU1,m_fV0) },		//1
		{ D3DXVECTOR3(dx + (dw / 2.0f) - 0.5f,0.5f,dy - (dh / 2.0f) - 0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),color,D3DXVECTOR2(m_fU1,m_fV1) },		//2
		{ D3DXVECTOR3(dx - (dw / 2.0f) - 0.5f,0.5f,dy - (dh / 2.0f) - 0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),color ,D3DXVECTOR2(m_fU0,m_fV1) },		//3
	};

	HRESULT hr;
	//���_Vertex�o�b�t�@�����
	hr = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_BILLBOARD) * 4,						//���_���̈�m��
		D3DUSAGE_WRITEONLY,							//�g�p�p�r(��������ł���)
		FVF_VERTEX_BILLBOARD,								//FVF�A�O�ł����v
		D3DPOOL_MANAGED,							//���_�o�b�t�@�̊Ǘ����@(Device�ɊǗ�����)
		&m_pVertexBuffer,							//�Ǘ��҂̃������ꏊ
		NULL);

	//���_�o�b�t�@NULL�`�F�b�N
	if (FAILED(hr))
	{
		MessageBox(NULL, "���_�o�b�t�@�����Ȃ�", "�G���[", MB_OK);							//���_�o�b�t�@�G���[���b�Z�[�W
		return;
	}

	VERTEX_BILLBOARD* pV;
	m_pVertexBuffer->Lock(0, 0,						//���_�o�b�t�@���b�N(�n�܂�A�̈�Avoid�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		(void**)&pV,								//���_�o�b�t�@���b�N(void�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		D3DLOCK_DISCARD);

	//���_����pV�ɏ��������
	//�@���܂ł̔z����g�p�cPV��V�̓��e�R�s�[����B�imemcpy�g�p���āj
	memcpy(&pV[0], &v[0], sizeof(VERTEX_BILLBOARD) * 4);

	//�A���ڏ���

	m_pVertexBuffer->Unlock();

	//�C���f�b�N�X�o�b�t�@�����
	hr = pDevice->CreateIndexBuffer(
		sizeof(WORD) * 6,							//���[���h�s����̈�m��
		D3DUSAGE_WRITEONLY,							//�g�p�p�r(��������ł���)
		D3DFMT_INDEX16,								//FMT,DWORD�̏ꍇ��D3DFMT_INDEX32
		D3DPOOL_MANAGED,							//���_�o�b�t�@�̊Ǘ����@(Device�ɊǗ�����)
		&m_pIndexBuffer,							//�C���f�b�N�X�o�b�t�@�Ǘ����郁����
		NULL);

	//�C���f�b�N�X�o�b�t�@NULL�`�F�b�N
	if (FAILED(hr))
	{
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�����Ȃ�", "�G���[", MB_OK);							//���_�o�b�t�@�G���[���b�Z�[�W
		return ;
	}

	LPWORD pIndex;
	m_pIndexBuffer->Lock(0, 0,						//���_�o�b�t�@���b�N(�n�܂�A�̈�Avoid�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		(void**)&pIndex,							//���_�o�b�t�@���b�N(void�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		D3DLOCK_DISCARD);

	//�C���f�b�N�X��pIndex�ɏ��������
	//�@���܂ł̔z����g�p�cPV��V�̓��e�R�s�[����B�imemcpy�g�p���āj
	memcpy(&pIndex[0], &index[0], sizeof(WORD) * 6);
	//�A���ڏ���

	m_pIndexBuffer->Unlock();
}