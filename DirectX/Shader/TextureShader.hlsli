struct Input
{
    // �ø�ƽ 
    float4 Pos : POSITION0;
    float4 Color : COLOR;
};

struct OutPut
{
    // w���� ����  ����Ʈ ���ϰ� �ȼ� �������� �� ������ ����
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};

OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.Color = _Value.Color;
	
	// �����ܰ迡�� ����� ������.
    // _Value.Pos *= �������������;

    return OutPutValue;
}