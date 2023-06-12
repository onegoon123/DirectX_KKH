#include "PrecompileHeader.h"
#include "NumberActor.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
NumberActor::NumberActor() 
{
}

NumberActor::~NumberActor() 
{
}

void NumberActor::NumberCreate(int _Order)
{
	if (nullptr == GameEngineSprite::Find("NumFont.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Battle");
		Dir.Move("UI");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("NumFont.png").GetFullPath(), 10, 1);
	}

	Renders.resize(3);
	for (int i = 0; i < 3; i++)
	{
		Renders[i] = CreateComponent<GameEngineUIRenderer>(_Order);
		Renders[i]->SetSprite("NumFont.png", 0);
		Renders[i]->GetTransform()->SetLocalScale({ 32, 40 });
		Renders[i]->GetTransform()->SetLocalPosition({ -32.0f * i, 0 });
	}
}

void NumberActor::Setting(int _Value)
{
	if (0 == Renders.size()) { NumberCreate(); }
	SetValue(_Value);
	IsLerp = false;
}

void NumberActor::SetValue(int _Value)
{
	if (0 == Renders.size()) { NumberCreate(); }
	Value = _Value;
	if (1000 <= _Value)
	{
		MsgAssert("���� 4�ڸ����� ǥ������ ���մϴ�.");
		return;
	}
	if (100 <= _Value)
	{
		for (int i = 0; i < 3; i++)
		{
			Renders[i]->GetTransform()->SetLocalPosition({ -24.0f * i, 0 });
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			Renders[i]->GetTransform()->SetLocalPosition({ -32.0f * i, 0 });
		}
	}
	int i = 0;
	do 
	{
		int Num = _Value % 10;
		_Value /= 10;
		Renders[i]->SetFrame(Num);
		Renders[i]->On();
		i++;
	} while (0 < _Value);
	for (; i < Renders.size(); i++)
	{
		Renders[i]->Off();
	}

}

void NumberActor::SetValueLerp(int _Value)
{
	if (0 == Renders.size()) { NumberCreate(); }
	if (Value == _Value) { return; }
	IsPlus = Value < _Value;
	TargetValue = _Value;
	Timer = Time;
	IsLerp = true;
}

void NumberActor::SetBlackFont()
{
	if (0 == Renders.size()) { NumberCreate(); }
	if (nullptr == GameEngineSprite::Find("NumFontBlack.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Battle");
		Dir.Move("UI");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("NumFontBlack.png").GetFullPath(), 10, 1);
	}
	for (int i = 0; i < 3; i++)
	{
		Renders[i]->SetSprite("NumFontBlack.png", 0);
	}
}

void NumberActor::SetDamageFont()
{
	if (0 == Renders.size()) { NumberCreate(); }
	if (nullptr == GameEngineSprite::Find("NumFontDamage.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Battle");
		Dir.Move("UI");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("NumFontDamage.png").GetFullPath(), 10, 1);
	}
	for (int i = 0; i < 3; i++)
	{
		Renders[i]->SetSprite("NumFontDamage.png", 0);
	}
}

void NumberActor::Start()
{

}

void NumberActor::Update(float _DeltaTime)
{
	if (false == IsLerp) { return; }

	Timer -= _DeltaTime;
	if (Timer < 0)
	{
		if (IsPlus)
		{
			SetValue(Value + 1);
		}
		else
		{
			SetValue(Value - 1);
		}
		
		if (TargetValue == Value)
		{
			IsLerp = false;
		}
		Timer = Time;
	}

}

