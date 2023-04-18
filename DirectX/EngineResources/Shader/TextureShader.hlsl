// ���̴��� ¥�ԵǸ� ������ ��Ģ�� ���Ѿ� �Ѵ�.

// 0~ 16�� ���� 
cbuffer TransformData : register(b0)
{
    float4x4 WorldMatrix;
}

// � ������ ������ ����ü��
// ��� �������̰� ��� ���̰�
// �̸� �������
struct Input
{
	// �ø�ƽ      ������� �������� 
    float4 Pos : POSITION;
    float4 Color : COLOR;
};

struct OutPut
{
    // �����Ͷ��������� ����
    // w���� ����  ����Ʈ ���ϰ� �ȼ� �������� �������� ����
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};


// �������������

OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldMatrix);
    // OutPutValue.Pos = _Value.Pos;
    OutPutValue.Color = _Value.Color;
	
	// �����ܰ迡�� ����� ������.
    // OutPutValue.Pos *= �������������;

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