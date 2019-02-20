
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

	float3	N;		// ワールド空間上の法線ベクトル
	float3	L;		// 光の差し込む方向
	float3	V;		// （カメラ座標ー頂点座標）ベクトル
	float3  R;      // （カメラ座標ー頂点座標）ベクトルを法線ベクトル方向に反射させる
	float3  H;		//  ハーフベクトル（視線ベクトルと光の方向ベクトル）

	//VS輸出データ初期化
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
	// テクスチャの色と頂点の色を掛け合わせる
	output.color = saturate(input.color * tex_color);  

	return output;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
