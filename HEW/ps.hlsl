// DX21 Pixel Shader Sample Ver.2 - Texture

// Global Variables
Texture2D g_Tex : register(t0);  // texture instance
sampler g_SamplerLinear : register(s0);  // texture sampler instance

/* Pixel shader entrypoint function
 Return value: Color that this pixel to be filled with
 Argument inputPos: Vertex's position, usually no use
 Argument inputTex: Texture coordinates (UV values) to be used on this pixcel*/
 //float4 ps_main( float4 inputPos : POSITION,float4 inputColor:COLOR, float2 inputTex : TEXCOORD ) : SV_Target
 //{
 //	// Texture2D.Sample method gets a color from the texture by calculating using UVs.
 //	float4 pixelColor = g_Tex.Sample(g_SamplerLinear, inputTex);
 //
 //	pixelColor.r = pixelColor.r + 0.2f;
 //	pixelColor.g = pixelColor.g + 0.2f;
 //	pixelColor.b = pixelColor.b + 0.2f;
 //	
 //	pixelColor.a = pixelColor.a*inputColor.a;
 //
 //	return pixelColor;
 //}

float4 ps_main(float4 inputPos : POSITION, float4 inputColor : COLOR, float2 inputTex : TEXCOORD) : SV_Target
{
	// Texture2D.Sample method gets a color from the texture by calculating with UVs.
	float4 pixelColor = g_Tex.Sample(g_SamplerLinear, inputTex);

	pixelColor.r = pixelColor.r*inputColor.r* 1.2f + 0.1f;
	pixelColor.g = pixelColor.g*inputColor.g* 1.2f + 0.1f;
	pixelColor.b = pixelColor.b*inputColor.b* 1.2f + 0.1f;
	pixelColor.a = pixelColor.a*inputColor.a;

	return pixelColor;
}