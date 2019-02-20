
//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
struct VS_INPUT
{
	float3	position	: POSITION;
	float3	normal		: NORMAL;
	float3	binormal	: BINORMAL;
	float3	tangent		: TANGENT;
	float4	color		: COLOR0;
	float2	texcoord0	: TEXCOORD0;
	float2	texcoord1	: TEXCOORD1;
	float2	texcoord2	: TEXCOORD2;
	float2	texcoord3	: TEXCOORD3;
};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
struct VS_to_PS
{
	float4	position	: SV_Position;
	float4	diffuse		: COLOR0;
	float4	specular	: COLOR1;
	float2	texcoord0	: TEXCOORD0;
};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
struct PS_OUTPUT
{
	float4	color		: SV_Target0;
};

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
sampler2D	_SamplerColor	: register(s0);	

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
float4x4	_mtxAll					: register(vs,c0);
float4x4	_mtxWorld				: register(vs,c4);
// ��
float4		_diffuse_light			: register(vs,c8);		// �f�B�t���[�Y
float4		_ambient_light			: register(vs,c9);		// ����
float4		_specular_light			: register(vs,c10);		// �X�y�L�����[��
float4		_emmisive_light			: register(vs,c11);		// �G�~�b�V�u
float4		_dir_light				: register(vs,c12);		// ���s�����̕���

// �}�e���A��
float4		_diffuse_mat			: register(vs,c13);		// �f�B�t���[�Y��
float4		_ambient_mat			: register(vs,c14);		// ����
float4		_specular_mat			: register(vs,c15);		// �X�y�L�����[
float4		_emmisive_mat			: register(vs,c16);		// �G�~�b�V�u��
float4		_power					: register(vs,c17);		// �X�y�L�����[���̃p���[�l

// �X�y�L�������̌v�Z�p
float4		_camerapos				: register(vs,c18);		// �J�����ʒu

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
VS_to_PS vs_main(VS_INPUT input)
{

	float3	N;		// ���[���h��ԏ�̖@���x�N�g��
	float3	L;		// ���̍������ޕ���
	float3	V;		// �i�J�������W�[���_���W�j�x�N�g��
	float3  R;      // �i�J�������W�[���_���W�j�x�N�g����@���x�N�g�������ɔ��˂�����
	float3  H;		//  �n�[�t�x�N�g���i�����x�N�g���ƌ��̕����x�N�g���j

	//VS�A�o�f�[�^������
	VS_to_PS output = (VS_to_PS)0;
	output.diffuse = input.color;
	output.position	= mul(float4(input.position, 1.0f), _mtxAll);
	output.texcoord0	= input.texcoord0;	

	// �@�������[���h��ԏ�̃x�N�g���ɕϊ����āA�P�ʃx�N�g����
	N = normalize(mul(input.normal, (float3x3)_mtxWorld));
	
	// ���s���̍������ޕ���	�P�ʃx�N�g����
	L = normalize(-_dir_light.xyz);						//�����𔽓]���Ă���
	
	// ����(����)�x�N�g�������߂�i�J�������W -�@���[���h��ԏ�̒��_���W�j
	V = _camerapos.xyz - output.position;
	V = normalize(V);
	
	// �n�[�t�x�N�g�������߂�
	H = normalize(V + L);

	// �o�̓f�B�t���[�Y�J���[�����߂�
	output.diffuse = _ambient_light * _ambient_mat + _diffuse_light * _diffuse_mat * max(0.0f, dot(L, N));

	// �X�y�L�����[���ɂ��F���v�Z
	output.specular = _specular_light * _specular_mat * pow(max(0.0f, dot(N, H)), 50) * _power.x;

	return output;										
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
PS_OUTPUT ps_main(VS_to_PS input)
{
	PS_OUTPUT output = (PS_OUTPUT)0;

	float4 tex_color= tex2D(_SamplerColor, input.texcoord0);
	// �e�N�X�`���̐F�ƒ��_�̐F���|�����킹��
	output.color = saturate(input.diffuse * tex_color+input.specular);  

	return output;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
