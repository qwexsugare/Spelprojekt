Texture2D depthTexture;

struct VSIn
{
	float3 Pos	: POS;
	float2 UVCoord : UVCOORD;
};

cbuffer cBuffer
{
	float screenWidth = 1920/4;
	float screenHeight = 1080/4;
}

struct PSIn
{
	float4 Pos  : SV_Position;
	float2 UVCoord : UVCOORD;
};

SamplerState linearSampler 
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

BlendState NoBlend
{
   BlendEnable[0]           = FALSE;
   SrcBlend                 = SRC_ALPHA;
   DestBlend                = INV_SRC_ALPHA;
   BlendOp                  = ADD;
   SrcBlendAlpha            = ONE;
   DestBlendAlpha           = ZERO;
   BlendOpAlpha             = ADD;
   RenderTargetWriteMask[0] = 0x0F;
};

BlendState SrcAlphaBlend
{
   BlendEnable[0]           = TRUE;
   SrcBlend                 = SRC_ALPHA;
   DestBlend                = INV_SRC_ALPHA;
   BlendOp                  = ADD;
   SrcBlendAlpha            = ONE;
   DestBlendAlpha           = ZERO;
   BlendOpAlpha             = ADD;
   RenderTargetWriteMask[0] = 0x0F;
};

BlendState AdditiveBlending
{
	AlphaToCoverageEnable	= FALSE;
	BlendEnable[0]			= TRUE;
	SrcBlend				= SRC_ALPHA;
	DestBlend				= ONE;
	BlendOp					= ADD;
	SrcBlendAlpha			= 1;
	DestBlendAlpha			= ZERO;
	BlendOpAlpha			= ADD;
	RenderTargetWriteMask[0]= 0x0F;
};

DepthStencilState DisableDepth
{
    DepthEnable = FALSE;
    DepthWriteMask = ZERO;
};

RasterizerState rs
{
	FillMode = Solid;
	CullMode = None;
};


PSIn VSGlow( VSIn input )
{
	PSIn output = (PSIn)0;
	output.Pos = float4(input.Pos, 1.0f);
	output.UVCoord = input.UVCoord;
	return output;
}

float4 PSUpSample(PSIn input) : SV_Target
{
	float4 color = depthTexture.Sample(linearSampler, input.UVCoord);
	float dep = 1/color.x;
	float dep2 = 1 / color.g;
	float dep3 = 1/color.b;
	float dep4 = 1/color.w;
	//return float4(1, 1, 1, 1);
	//return float4(dep, dep3, dep4, 1);
	color.r *= 0.5;
	return color;
}

float4 PSHorizontalGlow(PSIn input) : SV_Target
{   
	float weight0, weight1, weight2, weight3, weight4;

	float texSize = 1.0f / screenWidth;

	weight0 = 1.0f;
    weight1 = 0.9f;
    weight2 = 0.55f;
    weight3 = 0.18f;
    weight4 = 0.1f;

	float normalization = (weight0 + 2.0f * (weight1 + weight2 + weight3 + weight4));
    // Normalize the weights.
    weight0 = weight0 / normalization;
    weight1 = weight1 / normalization;
    weight2 = weight2 / normalization;
    weight3 = weight3 / normalization;
    weight4 = weight4 / normalization;

	float4 color = float4(0, 0, 0, 0);

	float2 tex0, tex1, tex2, tex3, tex4, tex5, tex6, tex7, tex8;

	tex0 =  input.UVCoord + float2(texSize * -4.0f, 0.0f);
	tex1 =  input.UVCoord + float2(texSize * -3.0f, 0.0f);
	tex2 =  input.UVCoord + float2(texSize * -2.0f, 0.0f);
	tex3 =  input.UVCoord + float2(texSize * -1.0f, 0.0f);
	tex4 =  input.UVCoord + float2(texSize * 0.0f, 0.0f);
	tex5 =  input.UVCoord + float2(texSize * 1.0f, 0.0f);
	tex6 =  input.UVCoord + float2(texSize * 2.0f, 0.0f);
	tex7 =  input.UVCoord + float2(texSize * 3.0f, 0.0f);
	tex8 =  input.UVCoord + float2(texSize * 4.0f, 0.0f);

	color += depthTexture.Sample(linearSampler, tex0) * weight4;
    color += depthTexture.Sample(linearSampler, tex1) * weight3;
    color += depthTexture.Sample(linearSampler, tex2) * weight2;
    color += depthTexture.Sample(linearSampler, tex3) * weight1;
    color += depthTexture.Sample(linearSampler, tex4) * weight0;
    color += depthTexture.Sample(linearSampler, tex5) * weight1;
    color += depthTexture.Sample(linearSampler, tex6) * weight2;
    color += depthTexture.Sample(linearSampler, tex7) * weight3;
    color += depthTexture.Sample(linearSampler, tex8) * weight4;

	color.a = 1.0f;

	return color;
}

float4 PSVerticalGlow(PSIn input) : SV_Target
{   
	float weight0, weight1, weight2, weight3, weight4;

	float texSize = 1.0f / screenHeight;

	weight0 = 1.0f;
    weight1 = 0.9f;
    weight2 = 0.55f;
    weight3 = 0.18f;
    weight4 = 0.1f;

	float normalization = (weight0 + 2.0f * (weight1 + weight2 + weight3 + weight4));
    // Normalize the weights.
    weight0 = weight0 / normalization;
    weight1 = weight1 / normalization;
    weight2 = weight2 / normalization;
    weight3 = weight3 / normalization;
    weight4 = weight4 / normalization;

	float4 color = float4(0, 0, 0, 0);

	float2 tex0, tex1, tex2, tex3, tex4, tex5, tex6, tex7, tex8;

	tex0 =  input.UVCoord + float2(0.0f, texSize * -4.0f);
	tex1 =  input.UVCoord + float2(0.0f, texSize * -3.0f);
	tex2 =  input.UVCoord + float2(0.0f, texSize * -2.0f);
	tex3 =  input.UVCoord + float2(0.0f, texSize * -1.0f);
	tex4 =  input.UVCoord + float2(0.0f, texSize * 0.0f);
	tex5 =  input.UVCoord + float2(0.0f, texSize * 1.0f);
	tex6 =  input.UVCoord + float2(0.0f, texSize * 2.0f);
	tex7 =  input.UVCoord + float2(0.0f, texSize * 3.0f);
	tex8 =  input.UVCoord + float2(0.0f, texSize * 4.0f);

	color += depthTexture.Sample(linearSampler, tex0) * weight4;
    color += depthTexture.Sample(linearSampler, tex1) * weight3;
    color += depthTexture.Sample(linearSampler, tex2) * weight2;
    color += depthTexture.Sample(linearSampler, tex3) * weight1;
    color += depthTexture.Sample(linearSampler, tex4) * weight0;
    color += depthTexture.Sample(linearSampler, tex5) * weight1;
    color += depthTexture.Sample(linearSampler, tex6) * weight2;
    color += depthTexture.Sample(linearSampler, tex7) * weight3;
    color += depthTexture.Sample(linearSampler, tex8) * weight4;

	color.a = 1.0f;

	return color;
}

technique10 HorizontalBlur
{
	pass p0
	{
		SetBlendState( NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSGlow() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSHorizontalGlow() ) );

	    SetDepthStencilState( DisableDepth, 0 );
	    SetRasterizerState( rs );
	}
}

technique10 VerticalBlur
{
	pass p0
	{	
		SetBlendState( NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

        SetVertexShader( CompileShader( vs_4_0, VSGlow() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSVerticalGlow() ) );

	    SetDepthStencilState( DisableDepth, 0 );
	    SetRasterizerState( rs );
	}
}

technique10 SSAO
{
	pass p0
	{
		SetBlendState( NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

		SetVertexShader( CompileShader( vs_4_0, VSGlow() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PSUpSample() ) );

	    //SetDepthStencilState( DisableDepth, 0 );
	    SetRasterizerState( rs );
	}	
}