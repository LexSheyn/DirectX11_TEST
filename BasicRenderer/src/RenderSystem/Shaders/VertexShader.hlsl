struct VSOut
{
	float4 color    : Color;
	float4 position : SV_POSITION;	
};

cbuffer CBuf
{
	matrix transform;
};

VSOut main( float2 position : Position, float4 color : Color )
{
	VSOut vsout;

	vsout.position = mul( float4( position.x, position.y, 0.0f, 1.0f ), transform );
	vsout.color    = color;

	return vsout;
}