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

void NumberActor::SetValue(int _Value)
{
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

void NumberActor::SetBlackFont()
{
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

void NumberActor::Start()
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
		Renders[i] = CreateComponent<GameEngineUIRenderer>(static_cast<int>(RenderOrder::UIText));
		Renders[i]->SetSprite("NumFont.png", 0);
		Renders[i]->GetTransform()->SetLocalScale({ 32, 40 });
		Renders[i]->GetTransform()->SetLocalPosition({ -32.0f * i, 0});
	}
}
