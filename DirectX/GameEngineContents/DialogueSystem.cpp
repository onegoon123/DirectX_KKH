#include "PrecompileHeader.h"
#include "DialogueSystem.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
DialogueSystem::DialogueSystem() 
{
}

DialogueSystem::~DialogueSystem() 
{
}

void DialogueSystem::SetFadeIn(float _Timer)
{
	FadeSpeed = 1 / _Timer;
	FadeTimer = 1;
	IsFadeIn = true;
	for (std::shared_ptr<GameEngineUIRenderer> _Render : DialogueBoxRenders)
	{
		_Render->ColorOptionValue.MulColor.a = 1;
	}
}

void DialogueSystem::SetFadeOut(float _Timer)
{
	On();

	FadeSpeed = 1 / _Timer;
	FadeTimer = 0;
	IsFadeOut = true;
	for (std::shared_ptr<GameEngineUIRenderer> _Render : DialogueBoxRenders)
	{
		_Render->ColorOptionValue.MulColor.a = 0;
	}
}

void DialogueSystem::SetSize(float4 _Size)
{
	DialogueBoxRenders[1]->GetTransform()->SetLocalPosition({ 24.0f * _Size.x * 0.5f + 12.0f, 0 });
	DialogueBoxRenders[1]->GetTransform()->SetLocalScale({ 24.0f * _Size.x , 24 });

	DialogueBoxRenders[2]->GetTransform()->SetLocalPosition({ 24.0f * (_Size.x + 1), 0 });
	DialogueBoxRenders[2]->GetTransform()->SetLocalScale({ 24, 24 });

	DialogueBoxRenders[3]->GetTransform()->SetLocalPosition({ 0, -24.0f * _Size.y * 0.5f - 12.0f });
	DialogueBoxRenders[3]->GetTransform()->SetLocalScale({ 24.0f, 24.0f * _Size.y });

	DialogueBoxRenders[4]->GetTransform()->SetLocalPosition({ 24.0f * _Size.x * 0.5f + 12.0f, -24.0f * _Size.y * 0.5f - 12.0f });
	DialogueBoxRenders[4]->GetTransform()->SetLocalScale({ 24.0f * _Size.x , 24.0f * _Size.y });

	DialogueBoxRenders[5]->GetTransform()->SetLocalPosition({ 24.0f * (_Size.x + 1), -24.0f * _Size.y * 0.5f - 12.0f });
	DialogueBoxRenders[5]->GetTransform()->SetLocalScale({ 24.0f, 24.0f * _Size.y });

	DialogueBoxRenders[6]->GetTransform()->SetLocalPosition({ 0, -24.0f * (_Size.y + 1) });
	DialogueBoxRenders[6]->GetTransform()->SetLocalScale({ 24, 24 });

	DialogueBoxRenders[7]->GetTransform()->SetLocalPosition({ 24.0f * _Size.x * 0.5f + 12.0f, -24.0f * (_Size.y + 1) });
	DialogueBoxRenders[7]->GetTransform()->SetLocalScale({ 24.0f * _Size.x , 24 });

	DialogueBoxRenders[8]->GetTransform()->SetLocalPosition({ 24.0f * (_Size.x + 1), -24.0f * (_Size.y + 1) });
	DialogueBoxRenders[8]->GetTransform()->SetLocalScale({ 24, 24 });
}

void DialogueSystem::Start()
{
	DialogueBoxRenders.resize(9);
	if (nullptr == GameEngineSprite::Find("DialogueBox.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Event");
		Dir.Move("UI");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("DialogueBox.png").GetFullPath(), 3, 3);
	}

	DialogueBoxRenders[0] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[0]->SetSprite("DialogueBox.png", 0);
	DialogueBoxRenders[0]->GetTransform()->SetLocalScale({ 24, 24 });

	DialogueBoxRenders[1] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[1]->SetSprite("DialogueBox.png", 1);

	DialogueBoxRenders[2] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[2]->SetSprite("DialogueBox.png", 2);
	
	DialogueBoxRenders[3] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[3]->SetSprite("DialogueBox.png", 3);

	DialogueBoxRenders[4] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[4]->SetSprite("DialogueBox.png", 4);

	DialogueBoxRenders[5] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[5]->SetSprite("DialogueBox.png", 5);

	DialogueBoxRenders[6] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[6]->SetSprite("DialogueBox.png", 6);

	DialogueBoxRenders[7] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[7]->SetSprite("DialogueBox.png", 7);

	DialogueBoxRenders[8] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	DialogueBoxRenders[8]->SetSprite("DialogueBox.png", 8);
}

void DialogueSystem::Update(float _DeltaTime)
{
	if (true == IsFadeIn)
	{
		FadeTimer -= _DeltaTime * FadeSpeed;
		if (FadeTimer < 0)
		{
			IsFadeIn = false;
			for (std::shared_ptr<GameEngineUIRenderer> _Render : DialogueBoxRenders)
			{
				_Render->ColorOptionValue.MulColor.a = 0;
			}
			return;
		}
		for (std::shared_ptr<GameEngineUIRenderer> _Render : DialogueBoxRenders)
		{
			_Render->ColorOptionValue.MulColor.a = FadeTimer;
		}
	}

	if (true == IsFadeOut)
	{
		FadeTimer += _DeltaTime * FadeSpeed;
		if (FadeTimer > 1)
		{
			IsFadeOut = false;
			for (std::shared_ptr<GameEngineUIRenderer> _Render : DialogueBoxRenders)
			{
				_Render->ColorOptionValue.MulColor.a = 1;
			}
			return;
		}
		for (std::shared_ptr<GameEngineUIRenderer> _Render : DialogueBoxRenders)
		{
			_Render->ColorOptionValue.MulColor.a = FadeTimer;
		}
	}
}
