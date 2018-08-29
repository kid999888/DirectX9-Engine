//=================================================================================================
//                                                        
//�@�@�@3D�|���S���N���X�v���O����[ScenePolygon.h]                   
//      Author:���ŝ�(AT-13A-281 04)�@2018.06.08   
//                                                        
//=================================================================================================

//=================================================================================================
//�@�@�@�w�b�_�t�@�C��           
//=================================================================================================
#include"ScenePolygon.h"
#include"Material.h"
#include"Renderer.h"

//=================================================================================================
//		�}�N����`                                        
//=================================================================================================
//FVF�̐錾
#define FVF_VERTEX_POLYGON ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)    //3D�|���S���̒��_���
//�e�N�X�`���t�@�C���p�X
#define TEXTUREFILENAME000	        "Data\\Texture\\Laser.png"	

//=================================================================================================
//�@�@�@�\���̒�`                                         
//=================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;            //XYZW���W
	D3DXVECTOR3 fs;				//�@��
	D3DCOLOR color;             //�F���
	D3DXVECTOR2 texcoord;       //�e�N�X�`�����W
}VERTEX_POLYGON;

//=================================================================================================
//�@�@�@3D�|���S���N���X�f�X�g���N�^                                     
//=================================================================================================
CScenePolygon::~CScenePolygon()
{
}

//=================================================================================================
//�@�@�@3D�|���S���N���X��������                                    
//=================================================================================================
bool CScenePolygon::Init(void)
{
	HRESULT hr[2];
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	hr[0] = D3DXCreateTextureFromFile(
		pDevice,
		TEXTUREFILENAME000,
		&m_pTexture);

	if (FAILED(hr[0]))
	{
		MessageBox(NULL, "�G���[", "�e�N�X�`�����ǂݍ��߂Ȃ��B", MB_OK);
		return false;
	}

	static WORD index[] = {
		0,1,2,
		2,3,0,
	};

	//���_�̍쐬
	VERTEX_POLYGON v[] = {
		{ D3DXVECTOR3(-0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 0, 0, 128),D3DXVECTOR2(0.0f,0.0f) },		//0
		{ D3DXVECTOR3(0.5f,0.5f,0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 0, 0, 128) ,D3DXVECTOR2(1.0f,0.0f) },		//1
		{ D3DXVECTOR3(0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 0, 0, 128),D3DXVECTOR2(1.0f,1.0f) },		//2
		{ D3DXVECTOR3(-0.5f,0.5f,-0.5f),D3DXVECTOR3(0.0f, 1.0f, 0.0f),D3DCOLOR_RGBA(255, 0, 0, 128) ,D3DXVECTOR2(0.0f,1.0f) },		//3
	};

	//���_Vertex�o�b�t�@�����
	hr[0] = pDevice->CreateVertexBuffer(
		sizeof(VERTEX_POLYGON) * 4,						//���_���̈�m��
		D3DUSAGE_WRITEONLY,							//�g�p�p�r(��������ł���)
		FVF_VERTEX_POLYGON,								//FVF�A�O�ł����v
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

	VERTEX_POLYGON* pV;
	m_pVertexBuffer->Lock(0, 0,						//���_�o�b�t�@���b�N(�n�܂�A�̈�Avoid�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		(void**)&pV,								//���_�o�b�t�@���b�N(void�̃|�C���g�|�C���g�i�܂�[���A�h���X�j) 
		D3DLOCK_DISCARD);

	//���_����pV�ɏ��������
	//�@���܂ł̔z����g�p�cPV��V�̓��e�R�s�[����B�imemcpy�g�p���āj
	memcpy(&pV[0], &v[0], sizeof(VERTEX_POLYGON) * 4);

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
//�@�@�@3D�|���S���N���X�I������
//=================================================================================================
void CScenePolygon::Uninit(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_Material);
}

//=================================================================================================
//�@�@�@3D�|���S���N���X�X�V����                                    
//=================================================================================================
void CScenePolygon::Update(void)
{
	//m_veRotation.x += 0.0f;
	//m_veRotation.y += 0.05f;
	//m_veRotation.z += 0.0f;
}

//=================================================================================================
//�@�@�@3D�|���S���N���X�`�揈��
//=================================================================================================
void CScenePolygon::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

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
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldT);


	pDevice->SetStreamSource(0,
		m_pVertexBuffer, 0, sizeof(VERTEX_POLYGON));

	pDevice->SetIndices(m_pIndexBuffer);


	//FVF�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_POLYGON);

	//���C�gOFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 64);
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
//�@�@�@3D�|���S���̃C���X�^���X����
//=================================================================================================
CScenePolygon * CScenePolygon::Create(void)
{
	CScenePolygon *ScenePolygon = new CScenePolygon(1);
	ScenePolygon->Init();
	return ScenePolygon;
}
