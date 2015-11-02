struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

float4 main(VOut pIn) : SV_TARGET
{
	return pIn.color;
}