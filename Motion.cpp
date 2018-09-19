#include "Motion.h"
#include "input.h"

PART CMotion::m_Part[10] = {};

KEY_FRAME g_KeyFrameWalk[3] =
{
	{ 300,
		{
			//à íu							//âÒì]	
			{ D3DXVECTOR3(0.0f, 5.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//0
			{ D3DXVECTOR3(0.0f, 3.0f,0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },		//1
			{ D3DXVECTOR3(1.0f, 2.4f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//2
			{ D3DXVECTOR3(2.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//3
			{ D3DXVECTOR3(-1.0f, 2.4f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//4
			{ D3DXVECTOR3(-2.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//5
			{ D3DXVECTOR3(1.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//6
			{ D3DXVECTOR3(0.0f, -2.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//7
			{ D3DXVECTOR3(-1.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//8
			{ D3DXVECTOR3(0.0f, -2.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) }	//9
		} 
	},
	{ 300,
		{
			//à íu							//âÒì]	
			{ D3DXVECTOR3(0.0f, 5.0f, 0.0f),D3DXVECTOR3(0.0f, 225.0f, 0.0f) },	//0
			{ D3DXVECTOR3(0.0f, 3.0f,0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },		//1
			{ D3DXVECTOR3(1.0f, 2.4f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//2
			{ D3DXVECTOR3(2.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 45.0f) },	//3
			{ D3DXVECTOR3(-1.0f, 2.4f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//4
			{ D3DXVECTOR3(-2.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, -45.0f) },	//5
			{ D3DXVECTOR3(1.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 45.0f) },	//6
			{ D3DXVECTOR3(0.0f, -2.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, -45.0f) },	//7
			{ D3DXVECTOR3(-1.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, -45.0f) },	//8
			{ D3DXVECTOR3(0.0f, -2.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 45.0f) }	//9
		} 
	},
	{ 300,
		{
			//à íu							//âÒì]	
			{ D3DXVECTOR3(0.0f, 5.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//0
			{ D3DXVECTOR3(0.0f, 3.0f,0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },		//1
			{ D3DXVECTOR3(1.0f, 2.4f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//2
			{ D3DXVECTOR3(2.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//3
			{ D3DXVECTOR3(-1.0f, 2.4f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//4
			{ D3DXVECTOR3(-2.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//5
			{ D3DXVECTOR3(1.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//6
			{ D3DXVECTOR3(0.0f, -2.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//7
			{ D3DXVECTOR3(-1.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//8
			{ D3DXVECTOR3(0.0f, -2.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) }	//9
		} 
	}
};

KEY_FRAME g_KeyFrameRun[2] =
{
	{ 300,
		{
			//à íu							//âÒì]	
			{ D3DXVECTOR3(0.0f, 5.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//0
			{ D3DXVECTOR3(0.0f, 3.0f,0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },		//1
			{ D3DXVECTOR3(1.0f, 2.4f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//2
			{ D3DXVECTOR3(2.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//3
			{ D3DXVECTOR3(-1.0f, 2.4f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//4
			{ D3DXVECTOR3(-2.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//5
			{ D3DXVECTOR3(1.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//6
			{ D3DXVECTOR3(0.0f, -2.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//7
			{ D3DXVECTOR3(-1.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//8
			{ D3DXVECTOR3(0.0f, -2.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) }	//9
		} 
	},
	{ 300,
		{
			//à íu							//âÒì]	
			{ D3DXVECTOR3(0.0f, 5.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//0
			{ D3DXVECTOR3(0.0f, 3.0f,0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },		//1
			{ D3DXVECTOR3(1.0f, 2.4f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//2
			{ D3DXVECTOR3(2.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//3
			{ D3DXVECTOR3(-1.0f, 2.4f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//4
			{ D3DXVECTOR3(-2.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//5
			{ D3DXVECTOR3(1.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//6
			{ D3DXVECTOR3(0.0f, -2.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//7
			{ D3DXVECTOR3(-1.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) },	//8
			{ D3DXVECTOR3(0.0f, -2.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f) }	//9
		} 
	}
};


CMotion::~CMotion()
{
}

bool CMotion::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();
	LPD3DXBUFFER pAdjacencyBuffer;
	HRESULT hr;

	hr = D3DXLoadMeshFromX("Data\\Model\\body.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[0].Material,
		NULL,
		&m_Part[0].MaterialNum,
		&m_Part[0].mesh);

	hr = D3DXLoadMeshFromX("Data\\Model\\head.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[1].Material,
		NULL,
		&m_Part[1].MaterialNum,
		&m_Part[1].mesh);

	hr = D3DXLoadMeshFromX("Data\\Model\\arm_r.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[2].Material,
		NULL,
		&m_Part[2].MaterialNum,
		&m_Part[2].mesh);
	hr = D3DXLoadMeshFromX("Data\\Model\\hand_r.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[3].Material,
		NULL,
		&m_Part[3].MaterialNum,
		&m_Part[3].mesh);

	hr = D3DXLoadMeshFromX("Data\\Model\\arm_l.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[4].Material,
		NULL,
		&m_Part[4].MaterialNum,
		&m_Part[4].mesh);
	hr = D3DXLoadMeshFromX("Data\\Model\\hand_l.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[5].Material,
		NULL,
		&m_Part[5].MaterialNum,
		&m_Part[5].mesh);

	hr = D3DXLoadMeshFromX("Data\\Model\\thigh_r.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[6].Material,
		NULL,
		&m_Part[6].MaterialNum,
		&m_Part[6].mesh);
	hr = D3DXLoadMeshFromX("Data\\Model\\smallthigh_r.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[7].Material,
		NULL,
		&m_Part[7].MaterialNum,
		&m_Part[7].mesh);

	hr = D3DXLoadMeshFromX("Data\\Model\\thigh_l.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[8].Material,
		NULL,
		&m_Part[8].MaterialNum,
		&m_Part[8].mesh);
	hr = D3DXLoadMeshFromX("Data\\Model\\smallthigh_l.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&pAdjacencyBuffer,
		&m_Part[9].Material,
		NULL,
		&m_Part[9].MaterialNum,
		&m_Part[9].mesh);

	//êeéqä÷åW
	m_Part[0].Parent = NULL;
	m_Part[1].Parent = &m_Part[0];
	m_Part[2].Parent = &m_Part[0];
	m_Part[3].Parent = &m_Part[2];
	m_Part[4].Parent = &m_Part[0];
	m_Part[5].Parent = &m_Part[4];
	m_Part[6].Parent = &m_Part[0];
	m_Part[7].Parent = &m_Part[6];
	m_Part[8].Parent = &m_Part[0];
	m_Part[9].Parent = &m_Part[8];

	m_Part[0].Position = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	m_Part[0].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Part[1].Position = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	m_Part[1].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Part[2].Position = D3DXVECTOR3(1.0f, 2.4f, 0.0f);
	m_Part[2].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Part[3].Position = D3DXVECTOR3(2.0f, 0.0f, 0.0f);
	m_Part[3].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Part[4].Position = D3DXVECTOR3(-1.0f, 2.4f, 0.0f);
	m_Part[4].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Part[5].Position = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
	m_Part[5].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Part[6].Position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_Part[6].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Part[7].Position = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
	m_Part[7].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Part[8].Position = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	m_Part[8].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Part[9].Position = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
	m_Part[9].Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_KeyFrame = g_KeyFrameWalk;
	m_Key = 0;
	m_Frame = 0;


	return true;
}

void CMotion::Uninit(void)
{
}

void CMotion::Update(void)
{
	float rate = 0.0f;
	D3DXVECTOR3 curPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 nextPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 curRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 nextRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0;nCount < 10;nCount++)
	{
		float rate = (float)m_Frame / m_KeyFrame[m_Key].Frame;
		curPos = m_KeyFrame[m_Key].key[nCount].Position;
		nextPos = m_KeyFrame[m_Key + 1].key[nCount].Position;
		curRot = m_KeyFrame[m_Key].key[nCount].Rotation;
		nextRot = m_KeyFrame[m_Key + 1].key[nCount].Rotation;
		m_Part[nCount].Position = curPos * (1.0f - rate) + nextPos * rate;
		m_Part[nCount].Rotation = curRot * (1.0f - rate) + nextRot * rate;
	}
	m_Frame++;
	if (m_Frame >= m_KeyFrame[m_Key].Frame)
	{
		m_Key++;
		m_Frame = 0;
	}
	if (m_Key >= 2)
	{
		m_Key = 0;
		m_Frame = 0;
	}

	if (CInputKeyboard::GetKeyPress(DIK_Q))
	{
		m_KeyFrame = g_KeyFrameWalk;
		m_Key = 0;
		m_Frame = 0;
		for (int nCount = 0;nCount < 10;nCount++)
		{
			m_Part[nCount].Position = m_KeyFrame[0].key[nCount].Position;
			m_Part[nCount].Rotation = m_KeyFrame[0].key[nCount].Rotation;
		}
	}

	if (CInputKeyboard::GetKeyPress(DIK_E))
	{
		m_KeyFrame = g_KeyFrameRun;
		m_Key = 0;
		m_Frame = 0;
		for (int nCount = 0;nCount < 10;nCount++)
		{
			m_Part[nCount].Position = m_KeyFrame[0].key[nCount].Position;
			m_Part[nCount].Rotation = m_KeyFrame[0].key[nCount].Rotation;
		}
	}
}

void CMotion::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CRenderer::GetD3DDevice();

	for (int nCount = 0;nCount < 10;nCount++)
	{
		D3DXMatrixIdentity(&m_mtxWorld);
		D3DXMatrixIdentity(&m_mtxWorldR);
		D3DXMatrixIdentity(&m_mtxWorldRX);
		D3DXMatrixIdentity(&m_mtxWorldRY);
		D3DXMatrixIdentity(&m_mtxWorldRZ);
		D3DXMatrixRotationYawPitchRoll(&m_mtxWorldR, D3DXToRadian(m_Part[nCount].Rotation.y), D3DXToRadian(m_Part[nCount].Rotation.x), D3DXToRadian(m_Part[nCount].Rotation.z));
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldR);

		////âÒì]çsóÒÇçÏÇÈ
		//D3DXMatrixRotationX(&m_mtxWorldRX, D3DXToRadian(m_Part[nCount].Rotation.x));
		//D3DXMatrixRotationY(&m_mtxWorldRY, D3DXToRadian(m_Part[nCount].Rotation.y));
		//D3DXMatrixRotationZ(&m_mtxWorldRZ, D3DXToRadian(m_Part[nCount].Rotation.z));

		////âÒì]çsóÒÇçáê¨	
		//D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldRX, &m_mtxWorldRY);
		//D3DXMatrixMultiply(&m_mtxWorldR, &m_mtxWorldR, &m_mtxWorldRZ);

		//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldR);

		D3DXMatrixTranslation(&m_mtxWorldT, m_Part[nCount].Position.x, m_Part[nCount].Position.y, m_Part[nCount].Position.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxWorldT);

		if (m_Part[nCount].Parent != NULL)
		{
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_Part[nCount].Parent->Matrix);
		}
		m_Part[nCount].Matrix = m_mtxWorld;
		//ÉèÅ[ÉãÉhçsóÒÇÃê›íË
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//ÉÇÉfÉãï`âÊ
		m_Part[nCount].mesh->DrawSubset(0);
	}
	//ÉâÉCÉgOFF
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}

CMotion * CMotion::Create(void)
{
	CMotion *Motion = new CMotion(1);
	Motion->Init();
	return Motion;
}

PART CMotion::GetPart(int nCount)
{
	return m_Part[nCount];
}
