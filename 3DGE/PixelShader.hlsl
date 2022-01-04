struct PS_Input
{
	float4 position: SV_Position;
	float3 color: Color;
	float3 color1: Color1;
};

cbuffer CONSTANT: register(b0)
{
	row_major float4x4 WORLD;
	row_major float4x4 VIEW;
	row_major float4x4 PROJECTION_MATRIX;

	unsigned int TIME;
}


float4 PixelShaderMain(PS_Input input): SV_Target
{
	return float4(lerp(input.color, input.color1, (float)((sin((float)(TIME / (float)500.0f)) + 1.0f) / 2.0f)),1.0f);
}