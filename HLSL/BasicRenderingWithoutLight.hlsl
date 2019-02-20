
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
	float4	color		: COLOR0;
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
	output.color = input.color;
	output.position	= mul(float4(input.position, 1.0f), _mtxAll);
	output.texcoord0	= input.texcoord0;	
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
	output.color = saturate(input.color * tex_color);  

	return output;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
