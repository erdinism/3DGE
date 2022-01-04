struct VS_Input
{
	float4 position: Position;
	float3 color: Color;
	float3 color1: Color1;
};

struct VS_Output
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

	unsigned int time;
}

VS_Output VertexShaderMain(VS_Input input)
{
	VS_Output output = (VS_Output)0;

	// output.position = lerp(input.position, input.position1, (sin(ANGLE)+ 1.0f)/ 2.0f);
	
	output.position = mul(input.position, WORLD);
	output.position = mul(output.position, VIEW);
	output.position = mul(output.position, PROJECTION_MATRIX);

	output.color = input.color;
	output.color1 = input.color1;

	return output;
}