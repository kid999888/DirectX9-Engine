
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
// 光
float4		_diffuse_light			: register(vs,c8);		// ディフューズ
float4		_ambient_light			: register(vs,c9);		// 環境光
float4		_specular_light			: register(vs,c10);		// スペキュラー光
float4		_emmisive_light			: register(vs,c11);		// エミッシブ
float4		_dir_light				: register(vs,c12);		// 平行光源の方向

// マテリアル
float4		_diffuse_mat			: register(vs,c13);		// ディフューズ光
float4		_ambient_mat			: register(vs,c14);		// 環境光
float4		_specular_mat			: register(vs,c15);		// スペキュラー
float4		_emmisive_mat			: register(vs,c16);		// エミッシブ光
float4		_power					: register(vs,c17);		// スペキュラー光のパワー値

// スペキュラ光の計算用
float4		_camerapos				: register(vs,c18);		// カメラ位置

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
	output.diffuse = input.color;
	output.position	= mul(float4(input.position, 1.0f), _mtxAll);
	output.texcoord0	= input.texcoord0;	

	// 法線をワールド空間上のベクトルに変換して、単位ベクトル化
	N = normalize(mul(input.normal, (float3x3)_mtxWorld));
	
	// 平行光の差し込む方向	単位ベクトル化
	L = normalize(-_dir_light.xyz);						//方向を反転している
	
	// 反射(視線)ベクトルを求める（カメラ座標 -　ワールド空間上の頂点座標）
	V = _camerapos.xyz - output.position;
	V = normalize(V);
	
	// ハーフベクトルを求める
	H = normalize(V + L);

	// 出力ディフューズカラーを決める
	output.diffuse = _ambient_light * _ambient_mat + _diffuse_light * _diffuse_mat * max(0.0f, dot(L, N));

	// スペキュラー光による色を計算
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
	// テクスチャの色と頂点の色を掛け合わせる
	output.color = saturate(input.diffuse * tex_color+input.specular);  

	return output;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
