cbuffer CBuf
{
	matrix transform;
};

struct VSOut
{
	float4 color    : Color;
	float4 position : SV_Position;
};

VSOut main( float3 position : Position, float4 color : Color )
{
	VSOut vso;

	vso.position = mul( float4( position, 1.0f ), transform );
	vso.color    = color;

	return vso;
}