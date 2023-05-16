#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>
// ���� :
class SpriteRenderer : public GameEngineSpriteRenderer
{
public:
	// constrcuter destructer
	SpriteRenderer();
	~SpriteRenderer();

	// delete Function
	SpriteRenderer(const SpriteRenderer& _Other) = delete;
	SpriteRenderer(SpriteRenderer&& _Other) noexcept = delete;
	SpriteRenderer& operator=(const SpriteRenderer& _Other) = delete;
	SpriteRenderer& operator=(SpriteRenderer&& _Other) noexcept = delete;

	void SetIsBlur(bool _Value)
	{
		EffectDataValue.IsBlur = _Value;
	}
	void SetBlurLevel(float _Value)
	{
		EffectDataValue.BlurLevel = _Value;
	}

	void SetLerp(float4 _Color, float _t)
	{
		EffectDataValue.LerpColor = _Color;
		EffectDataValue.LerpT = _t;
	}
	void OffLerp()
	{
		EffectDataValue.LerpColor = float4::Null;
		EffectDataValue.LerpT = 0;
	}
	void SetLerpT(float _t)
	{
		EffectDataValue.LerpT = _t;
	}

	void SetLocalScale(float4 _Scale)
	{
		GetTransform()->SetLocalScale(_Scale);
		EffectDataValue.Scale = _Scale;
	}
	void SetWorldScale(float4 _Scale)
	{
		GetTransform()->SetWorldScale(_Scale);
		EffectDataValue.Scale = _Scale;
	}


	// ���� ����
	void SetHue(float _Value)
	{
		EffectDataValue.Hue = _Value;
	}
	// ���� ���ϱ�
	void AddHue(float _Value)
	{
		EffectDataValue.Hue += _Value;
	}

	// ä�� ����
	void SetSaturation(float _Value)
	{
		EffectDataValue.Saturation = _Value;
	}
	// ä�� ���ϱ�
	void AddSaturation(float _Value)
	{
		EffectDataValue.Saturation += _Value;
	}

	// ��� ����
	void SetBrightness(float _Value)
	{
		EffectDataValue.Brightness = _Value;
	}
	// ��� ���ϱ�
	void AddBrightness(float _Value)
	{
		EffectDataValue.Brightness += _Value;
	}

	// ������ ����
	void SetOpacity(float _Value)
	{
		EffectDataValue.Opacity = _Value;
	}
	// ������ ���ϱ�
	void AddOpacity(float _Value)
	{
		EffectDataValue.Opacity += _Value;
	}


protected:
	void Start() override;
private:
	struct EffectData
	{
		float4 Scale;
		float4 LerpColor = float4::Null;
		float LerpT = 0.0f;
		int IsBlur = false;
		float BlurLevel = 0;
		float Hue = 0.0f;			// ����
		float Saturation = 1.0f;	// ä��
		float Brightness = 0.0f;	// ���
		float Opacity = 1.0f;		// ������
		float None;
	};
	EffectData EffectDataValue;
};

