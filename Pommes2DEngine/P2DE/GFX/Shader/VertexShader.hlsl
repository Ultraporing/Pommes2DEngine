struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

struct VertexInput
{
	float3 iPosition : POSITION;
	float4 iColor    : COLOR;
};


VOut main(VertexInput vIn)
{
	VOut output;

	output.position = float4(vIn.iPosition, 1.0f);
	output.color = vIn.iColor;

	return output;
}