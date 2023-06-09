#include "PrecompileHeader.h"
#include "UnitCommandUI.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "BattleLevel.h"
#include "UICursor.h"
#include "UIButtonSystem.h"
#include "TextRenderer.h"
UnitCommandUI::UnitCommandUI()
{
	CommandFunctions.reserve(5);
}

UnitCommandUI::~UnitCommandUI()
{
	LevelPtr = nullptr;
}

void UnitCommandUI::Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor)
{
	LevelPtr = _Level;
	CancelFunction = std::bind(&BattleLevel::UnitCommand_Cancel, LevelPtr);
	Cursor = _Cursor;
}

void UnitCommandUI::SetCommand(bool _IsAttackable, bool _IsCloseUnit, bool _IsItem)
{
	CommandFunctions.clear();
	std::vector<std::string_view> Texts;
	Texts.reserve(5);

	if (true == _IsAttackable)
	{
		CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Attack, LevelPtr));	// 공격 커맨드
		Texts.push_back("공격");
	}
	if (true == _IsItem)
	{
		CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Item, LevelPtr));		// 소지품 커맨드
		Texts.push_back("소지품");
	}
	if (true == _IsCloseUnit)
	{
		CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Exchange, LevelPtr));// 교환 커맨드
		Texts.push_back("교환");
	}

	CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Wait, LevelPtr));// 대기 커맨드
	Texts.push_back("대기");

	WindowRender->SetFrame(CommandFunctions.size() - 1);

	for (int i = 0; i < CommandFunctions.size(); i++)
	{
		ButtonCols[i]->On();
	}
	for (size_t i = CommandFunctions.size(); i < 5; i++)
	{
		ButtonCols[i]->Off();
	}

	
	for (int i = 0; i < Texts.size(); i++)
	{
		FontRenders[i]->On();
		FontRenders[i]->SetText(Texts[i]);
	}
	for (size_t i = Texts.size(); i < 5; i++)
	{
		FontRenders[i]->Off();
	}
}

void UnitCommandUI::SetCommandHeal(bool _IsCloseUnit, bool _IsItem)
{
	CommandFunctions.clear();
	std::vector<std::string_view> Texts;
	Texts.reserve(5);

	if (true == _IsCloseUnit)
	{
		CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Heal, LevelPtr)); // 지팡이 커맨드
		Texts.push_back("지팡이");
	}
	if (true == _IsItem)
	{
		CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Item, LevelPtr));		// 소지품 커맨드
		Texts.push_back("소지품");
	}
	if (true == _IsCloseUnit)
	{
		CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Exchange, LevelPtr)); // 교환 커맨드
		Texts.push_back("교환");
	}

	CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Wait, LevelPtr));// 대기 커맨드
	Texts.push_back("대기");

	WindowRender->SetFrame(CommandFunctions.size() - 1);

	for (int i = 0; i < CommandFunctions.size(); i++)
	{
		ButtonCols[i]->On();
	}
	for (size_t i = CommandFunctions.size(); i < 5; i++)
	{
		ButtonCols[i]->Off();
	}

	for (int i = 0; i < Texts.size(); i++)
	{
		FontRenders[i]->On();
		FontRenders[i]->SetText(Texts[i]);
	}
	for (size_t i = Texts.size(); i < 5; i++)
	{
		FontRenders[i]->Off();
	}
}

void UnitCommandUI::SetCommandDance(bool _IsCloseUnit, bool _IsItem)
{
	CommandFunctions.clear();
	std::vector<std::string_view> Texts;
	Texts.reserve(5);

	if (true == _IsCloseUnit)
	{
		CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Dance, LevelPtr)); // 지팡이 커맨드
		Texts.push_back("춤");
	}
	if (true == _IsItem)
	{
		CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Item, LevelPtr));		// 소지품 커맨드
		Texts.push_back("소지품");
	}
	if (true == _IsCloseUnit)
	{
		CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Exchange, LevelPtr)); // 교환 커맨드
		Texts.push_back("교환");
	}

	CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Wait, LevelPtr));// 대기 커맨드
	Texts.push_back("대기");

	WindowRender->SetFrame(CommandFunctions.size() - 1);

	for (int i = 0; i < CommandFunctions.size(); i++)
	{
		ButtonCols[i]->On();
	}
	for (size_t i = CommandFunctions.size(); i < 5; i++)
	{
		ButtonCols[i]->Off();
	}

	for (int i = 0; i < Texts.size(); i++)
	{
		FontRenders[i]->On();
		FontRenders[i]->SetText(Texts[i]);
	}
	for (size_t i = Texts.size(); i < 5; i++)
	{
		FontRenders[i]->Off();
	}
}

void UnitCommandUI::SetConquer()
{
	CommandFunctions.clear();

	CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Conquer, LevelPtr));

	WindowRender->SetFrame(0);


	ButtonCols[0]->On();
	for (int i = 1; i < 5; i++)
	{
		ButtonCols[i]->Off();
	}
	FontRenders[0]->On();
	FontRenders[0]->SetText("제압");
	for (size_t i = 1; i < 5; i++)
	{
		FontRenders[i]->Off();
	}
}

void UnitCommandUI::SetStore()
{
	CommandFunctions.clear();

	CommandFunctions.push_back(std::bind(&BattleLevel::UnitCommand_Store, LevelPtr));

	WindowRender->SetFrame(0);


	ButtonCols[0]->On();
	for (int i = 1; i < 5; i++)
	{
		ButtonCols[i]->Off();
	}
	FontRenders[0]->On();
	FontRenders[0]->SetText("상점");
	for (size_t i = 1; i < 5; i++)
	{
		FontRenders[i]->Off();
	}
}

void UnitCommandUI::On()
{
	GameEngineActor::On();
	Cursor->On();
	CurrentCursor = 0;
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);

	Cursor->GetTransform()->SetLocalPosition(StartCursorPos);
	CursorPos = StartCursorPos;
}

void UnitCommandUI::Start()
{
	WindowRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	WindowRender->GetTransform()->SetLocalScale({ 196, 356 });
	WindowRender->GetTransform()->SetLocalPosition({ 334, 36 });
	WindowRender->SetSprite("CommandUI.png", 0);

	SelectRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	SelectRender->GetTransform()->SetLocalScale({ 144, 20 });
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);
	SelectRender->SetTexture("CommandSelect.png");

	CursorPos = StartCursorPos;

	ButtonSystem = GetLevel()->CreateActor<UIButtonSystem>();
	ButtonSystem->GetTransform()->SetParent(GetTransform());

	ButtonCols.resize(5);
	FontRenders.resize(5);
	for (int i = 0; i < 5; i++)
	{
		ButtonCols[i] = CreateComponent<GameEngineCollision>(CollisionOrder::Button);
		ButtonCols[i]->GetTransform()->SetLocalPosition({ 330, 164.0f - (64 * i) });
		ButtonCols[i]->GetTransform()->SetLocalScale({ 200, 64 });
		ButtonCols[i]->SetColType(ColType::AABBBOX2D);
		ButtonSystem->NewButton(ButtonCols[i],
			[=] {
				if (i != CurrentCursor)
				{
					CurrentCursor = i;
					SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
					CursorPos = { StartCursorPos + float4::Down * (64.0f * CurrentCursor) };
					GameEngineSound::Play("CommandMove.wav");
				}
			},
			[this] {
				GameEngineSound::Play("CommandSelect.wav");
				CommandFunctions[CurrentCursor]();
			}
		);
		FontRenders[i] = CreateComponent<TextRenderer>(RenderOrder::UIText);
		FontRenders[i]->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);
		FontRenders[i]->GetTransform()->SetLocalPosition({ 328, 190.0f - (64 * i) });
		FontRenders[i]->Off();
	}


	for (int i = 0; i < 5; i++)
	{
		
	}

	GameEngineActor::Off();
}	

void UnitCommandUI::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("ButtonA"))
	{
		CommandFunctions[CurrentCursor]();
		GameEngineSound::Play("CommandSelect.wav");
		return;
	}

	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		CancelFunction();
		GameEngineSound::Play("Cancel.wav");
		return;
	}

	CursorTimer += _DeltaTime * 10;
	Cursor->GetTransform()->SetLocalPosition(float4::Lerp(Cursor->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));

	if (CursorTimer < 1) { return; }



	if (PreesTime < GameEngineInput::GetPressTime("Up") || PreesTime < GameEngineInput::GetPressTime("Down"))
	{
		PressOK = true;
	}
	else if (GameEngineInput::IsFree("Up") && GameEngineInput::IsFree("Down"))
	{
		PressOK = false;
	}

	if (GameEngineInput::IsDown("Up") || (GameEngineInput::IsPress("Up") && PressOK))
	{
		GameEngineSound::Play("CommandMove.wav");
		CursorTimer = 0;
		if (CurrentCursor == 0)
		{
			if (false == GameEngineInput::IsDown("Up")) { return; }
			CurrentCursor = CommandFunctions.size() - 1;
			SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
			CursorPos = { StartCursorPos + float4::Down * (64.0f * CurrentCursor) };
			return;
		}
		CurrentCursor--;
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
		CursorPos = { StartCursorPos + float4::Down * (64.0f * CurrentCursor) };

		return;
	}

	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		GameEngineSound::Play("CommandMove.wav");
		CursorTimer = 0;
		if (CurrentCursor == CommandFunctions.size() - 1)
		{
			if (false == GameEngineInput::IsDown("Down")) { return; }
			CurrentCursor = 0;
			SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
			CursorPos = StartCursorPos;
			return;
		}
		CurrentCursor++;
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
		CursorPos = { StartCursorPos + float4::Down * (64.0f * CurrentCursor) };

		return;
	}

}