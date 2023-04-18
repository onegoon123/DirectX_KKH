// 쉐이더를 짜게되면 다음의 규칙을 지켜야 한다.

// 0~ 16번 슬롯 
cbuffer TransformData : register(b0)
{
    float4x4 WorldMatrix;
}

// 어떤 정보가 들어올지 구조체로
// 어디가 포지션이고 어디가 컬이고
// 이름 마음대로
struct Input
{
	// 시맨틱      어떤역할을 가졌는지 
    float4 Pos : POSITION;
    float4 Color : COLOR;
};

struct OutPut
{
    // 레스터라이저에게 보냄
    // w나눈 다음  뷰포트 곱하고 픽셀 건져낼때 쓸포지션 정보
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};


// 월드뷰프로젝션

OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldMatrix);
    // OutPutValue.Pos = _Value.Pos;
    OutPutValue.Color = _Value.Color;
	
	// 다음단계에서 사용할 정보들.
    // OutPutValue.Pos *= 월드뷰프로젝션;

    return OutPutValue;
}

cbuffer OutPixelColor : register(b0)
{
    float4 OutColor;
}


float4 Texture_PS(OutPut _Value) : SV_Target0
{
    return OutColor;
}