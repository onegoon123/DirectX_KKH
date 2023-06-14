#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>

#include "DebugWindow.h"
TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}


void TitleLevel::Start()
{
	// 키 세팅
	{
		GameEngineInput::CreateKey("Up", VK_UP);
		GameEngineInput::CreateKey("Down", VK_DOWN);
		GameEngineInput::CreateKey("Left", VK_LEFT);
		GameEngineInput::CreateKey("Right", VK_RIGHT);
		GameEngineInput::CreateKey("ButtonA", 'Z');
		GameEngineInput::CreateKey("ButtonB", 'X');
		GameEngineInput::CreateKey("ButtonY", 'C');
		GameEngineInput::CreateKey("ButtonX", 'V');
		GameEngineInput::CreateKey("ButtonL", 'A');
		GameEngineInput::CreateKey("ButtonR", 'S');
		GameEngineInput::CreateKey("Start", VK_ESCAPE);
		GameEngineInput::CreateKey("LeftClick", VK_LBUTTON);
		GameEngineInput::CreateKey("RightClick", VK_RBUTTON);
		GameEngineInput::CreateKey("MiddleClick", VK_MBUTTON);
		GameEngineInput::CreateKey("Cheet", VK_F1);
	}

	// 카메라 세팅
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0, 0, -554.0f });

	// 타이틀 리소스 로딩
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Title");
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".png", });
		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}

	}

	// 타이틀 이미지 생성
	if (nullptr == TitleRenderer)
	{
		std::shared_ptr<GameEngineActor> TitleActor = CreateActor<GameEngineActor>();
		TitleRenderer = TitleActor->CreateComponent<GameEngineUIRenderer>();
		TitleRenderer->SetTexture("TitleImage.png");
		TitleRenderer->GetTransform()->SetWorldScale({ 960, 640 });
	}

	std::shared_ptr<DebugWindow> Window = GameEngineGUI::FindGUIWindowConvert<DebugWindow>("DebugWindow");
	{
		if (nullptr == Window)
		{
			MsgAssert("윈도우 테스트 코드 미작동");
		}

		std::function<void()> Function;
		Function = []() {
			MsgTextBox("버튼누름");
		};

	}

	StateInit();
}

void TitleLevel::Update(float _DeltaTime)
{
	FSM.Update(_DeltaTime);
}

void TitleLevel::StateInit()
{
	FSM.CreateState({ .Name = "Start",
		.Start = [this]
		{
			TitleRenderer->ColorOptionValue.MulColor = float4::Zero;
			Timer = 0;
		},
		.Update = [this](float _DeltaTime)
		{
			Timer += _DeltaTime * 2;
			TitleRenderer->ColorOptionValue.MulColor = float4::One * Timer;
			if (1 < Timer)
			{
				FSM.ChangeState("Wait");
			}
		},
		.End = [this]
		{
			TitleRenderer->ColorOptionValue.MulColor = float4::One;
			Timer = 0;
		}
		});

	FSM.CreateState({ .Name = "Wait",
	.Start = [this]
	{
	},
	.Update = [this](float _DeltaTime)
	{
		if (true == GameEngineInput::IsAnyKey())
		{
			FSM.ChangeState("End");
		}
	},
	.End = [this]
	{
	}
	});

	FSM.CreateState({ .Name = "End",
	.Start = [this]
	{
		Timer = 0;
	},
	.Update = [this](float _DeltaTime)
	{
		Timer += _DeltaTime * 2;
		TitleRenderer->ColorOptionValue.MulColor = float4::One * (1.0f - Timer);
		if (1 < Timer)
		{
			FSM.ChangeState("Start");
		}
	},
	.End = [this]
	{
		GameEngineCore::ChangeLevel("Stage0");
	}
	});

	FSM.ChangeState("Start");
}
