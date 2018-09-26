///////////////////////////////////////////////////////////////////////////////////
//�^��`
///////////////////////////////////////////////////////////////////////////////////
struct VS_OUT
{
	float4 position : POSITION;
	float4 normal : TEXCOORD0;
	float2 uv : TEXCOORD2;
	float4 posWorld : TEXCOORD4;
	float4 view : TEXCOORD5;
	float4 light : TEXCOORD6;
};

///////////////////////////////////////////////////////////////////////////////////
//�O���[�o��
///////////////////////////////////////////////////////////////////////////////////
float4x4 g_WVP;
float4x4 g_W;
float4 g_lightDir;
float4 g_eye;

texture g_colorTexture;
sampler2D colorSampler = sampler_state
{
	Texture = (g_colorTexture);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;
	AddressU = Clamp;
	AddressV = Clamp;
};

///////////////////////////////////////////////////////////////////////////////////
//�t�H���@�o�[�e�b�N�X�E�V�F�[�_�[
///////////////////////////////////////////////////////////////////////////////////
VS_OUT PhongVS(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
	VS_OUT Out = (VS_OUT)0;
	Out.position = mul(pos, g_WVP);
	Out.posWorld = normalize(mul(pos, g_W));
	Out.view = g_eye - Out.posWorld;
	Out.normal = mul(normal, g_W);
	Out.uv = uv;
	//���C�g���� �@
	Out.light = g_lightDir;//�������|�C���g�I�I�@�f�B���N�V���i���͂ǂ��ɂ����Ă����������B�ʒu�͖��֌W
	

	return Out;
}
///////////////////////////////////////////////////////////////////////////////////
//�t�H���@�s�N�Z���E�V�F�[�_�[
///////////////////////////////////////////////////////////////////////////////////
float4 PhongPS(VS_OUT In) : COLOR
{
	float3 normal = normalize(In.normal);
	float3 lightDir = normalize(In.light);
	float3 viewDir = normalize(In.view);
	float4 NL = saturate(dot(normal, lightDir));
	float4 texColor = tex2D(colorSampler, In.uv);
	float3 reflect = normalize(2 * NL * normal - lightDir);
	float4 specular = pow(saturate(dot(reflect, viewDir)), 4);

	return texColor*NL + specular;
}
///////////////////////////////////////////////////////////////////////////////////
//�t�H���@�e�N�j�b�N
///////////////////////////////////////////////////////////////////////////////////
technique Phong
{
	pass p0
	{
		VertexShader = compile vs_3_0 PhongVS();
		PixelShader = compile ps_3_0 PhongPS();
	}
}