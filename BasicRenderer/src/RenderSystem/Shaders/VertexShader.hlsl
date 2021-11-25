struct VSOut
{
	float3 color    : Color;
	float4 position : SV_POSITION;	
};

VSOut main( float2 position : Position, float3 color : Color )
{
	VSOut vsout;

	vsout.position = float4( position.x, position.y, 0.0f, 1.0f );
	vsout.color    = color;

	return vsout;
}