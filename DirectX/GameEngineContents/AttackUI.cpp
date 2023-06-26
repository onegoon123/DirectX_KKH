#include "PrecompileHeader.h"
#include "AttackUI.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "UICursor.h"
#include "BattleLevel.h"
#include "BattleUnit.h"
#include "MapCursor.h"
#include "NumberActor.h"
#include "DoubleIconActor.h"
#include "UIButtonSystem.h"
#include "TextRenderer.h"
AttackUI::AttackUI()
{
}

AttackUI::~AttackUI()
{
}

void AttackUI::Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor)
{
	LevelPtr = _Level;
	Cursor_UI = _Cursor;
	Cursor_Map = _Level->GetMapCursor();
	AttackFunction = std::bind(&BattleLevel::UnitCommand_TargetAttack, _Level, std::placeholders::_1);
	CancelFunction = std::bind(&BattleLevel::UnitCommand_CommandCancel, _Level);

}

void AttackUI::On(std::shared_ptr<BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits)
{
	GameEngineActor::On();

	SelectUnit = _SelectUnit;
	TargetUnits = _TargetUnits;
	Weapons = SelectUnit->GetUnitData().GetWeapons();

	if (Weapons.size() == 0)
	{
		CancelFunction();
		return;
	}
	// ���� ������ŭ UIâ ����
	WindowRender->SetFrame(Weapons.size() - 1);

	// �ʻ�ȭ ����
	std::string TextStr = "Portrait_";
	TextStr += SelectUnit->GetUnitData().GetName();
	TextStr += ".png";
	Portrait->SetTexture(TextStr);

	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);
	CurrentCursor = 0;
	Cursor_UI->On();
	CursorPos = StartCursorPos;
	Cursor_UI->GetTransform()->SetLocalPosition(StartCursorPos);

	IsOnFrame = true;
	IsWeaponSelect = false;
	WeaponSelectStart();

	// ���� ������ ����
	size_t i = 0;
	for (std::shared_ptr<Weapon> _Item : Weapons)
	{
		WeaponeIcon[i]->SetFrame(static_cast<size_t>(_Item->GetItemCode()) - 1);
		WeaponeIcon[i]->On();
		i++;
	}
	for (i = Weapons.size(); i < 5; i++)
	{
		WeaponeIcon[i]->Off();
	}
	std::list<std::shared_ptr<Weapon>>::iterator WeaponIter = Weapons.begin();
	// ���� ������ ǥ��
	for (int i = 0; i < Weapons.size(); i++)
	{
		WeaponUses[i]->On();
		WeaponUses[i]->SetValue((*WeaponIter)->GetUses());
		ButtonCols[i]->On();
		ItemNameTexts[i]->On();
		ItemNameTexts[i]->SetText((*WeaponIter)->GetName());
		WeaponIter++;
	}

	for (size_t i = Weapons.size(); i < 5; i++)
	{
		ButtonCols[i]->Off();
		ItemNameTexts[i]->Off();
	}

}


void AttackUI::Off()
{
	GameEngineActor::Off();
	Cursor_UI->Off();
	WeaponDamage->Off();
	WeaponHit->Off();
	WeaponCritical->Off();
	WeaponWeight->Off();
	for (int i = 0; i < 5; i++)
	{
		WeaponUses[i]->Off();
	}
}

void AttackUI::SetLeft()
{
	BattleEx->GetTransform()->SetLocalPosition({ -318, 62 });
}

void AttackUI::SetRight()
{
	BattleEx->GetTransform()->SetLocalPosition({ 318, 62 });
}

void AttackUI::Start()
{
	WindowRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	WindowRender->GetTransform()->SetWorldScale({ 420, 356, 1 });
	WindowRender->GetTransform()->SetLocalPosition({ -224, 64 });
	WindowRender->SetSprite("ItemUI.png", 2);

	SelectRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	SelectRender->GetTransform()->SetWorldScale({ 368, 20 });
	SelectRender->GetTransform()->SetLocalPosition(StartSelectPos);
	SelectRender->SetTexture("ItemSelect.png");

	InfoRender = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	InfoRender->GetTransform()->SetWorldScale({ 420, 356 });
	InfoRender->GetTransform()->SetLocalPosition({ 224, -224 });
	InfoRender->SetTexture("UnitInfo.png");

	Portrait = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	Portrait->GetTransform()->SetWorldScale({ 384, 320 });
	Portrait->GetTransform()->SetLocalPosition({ 224, 114 });
	Portrait->SetTexture("Portrait_Lyn.png");

	BattleEx = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	BattleEx->GetTransform()->SetLocalScale({ 292, 484, 1 });
	BattleEx->GetTransform()->SetLocalPosition({ -318, 62 });
	BattleEx->SetTexture("BattleExUI.png");

	WeaponeIcon.resize(5);
	for (int i = 0; i < 5; i++)
	{
		WeaponeIcon[i] = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
		WeaponeIcon[i]->SetSprite("Items.png", 0);

		WeaponeIcon[i]->GetTransform()->SetWorldScale({ 64, 64 });
		WeaponeIcon[i]->GetTransform()->SetLocalPosition({ -386.0f, 198.0f - (64.0f * i) });

		WeaponeIcon[i]->Off();
	}

	{
		// ���� ������
		SubjectWeapon = CreateComponent<GameEngineUIRenderer>(RenderOrder::UICursor);
		SubjectWeapon->SetSprite("Items.png", 0);
		SubjectWeapon->GetTransform()->SetLocalPosition({ -224, 264 });
		SubjectWeapon->GetTransform()->SetLocalRotation(float4::Zero);
		SubjectWeapon->GetTransform()->SetLocalScale({ 64, 64, 1 });
		SubjectWeapon->GetTransform()->SetParent(BattleEx->GetTransform());
		SubjectWeapon->Off();
		TargetWeapon = CreateComponent<GameEngineUIRenderer>(RenderOrder::UICursor);
		TargetWeapon->SetSprite("Items.png", 0);
		TargetWeapon->GetTransform()->SetLocalPosition({ -412, -68 });
		TargetWeapon->GetTransform()->SetLocalRotation(float4::Zero);
		TargetWeapon->GetTransform()->SetLocalScale({ 64, 64, 1 });
		TargetWeapon->GetTransform()->SetParent(BattleEx->GetTransform());
		TargetWeapon->Off();

		SubjectName = CreateComponent<TextRenderer>(RenderOrder::UIText);
		SubjectName->GetTransform()->SetLocalPosition({ -350, 284 });
		SubjectName->GetTransform()->SetWorldRotation(float4::Zero);
		SubjectName->GetTransform()->SetWorldScale(float4::One);
		SubjectName->GetTransform()->SetParent(BattleEx->GetTransform());
		SubjectName->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);

		TargetName = CreateComponent<TextRenderer>(RenderOrder::UIText);
		TargetName->GetTransform()->SetLocalPosition({ -286, -38});
		TargetName->GetTransform()->SetWorldRotation(float4::Zero);
		TargetName->GetTransform()->SetWorldScale(float4::One);
		TargetName->GetTransform()->SetParent(BattleEx->GetTransform());
		TargetName->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);

		TargetWeaponName = CreateComponent<TextRenderer>(RenderOrder::UIText);
		TargetWeaponName->GetTransform()->SetLocalPosition({ -286, -102 });
		TargetWeaponName->GetTransform()->SetWorldRotation(float4::Zero);
		TargetWeaponName->GetTransform()->SetWorldScale(float4::One);
		TargetWeaponName->GetTransform()->SetParent(BattleEx->GetTransform());
		TargetWeaponName->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Center);

		// ���� �� �̹���
		SubjectTriangle = CreateComponent<GameEngineUIRenderer>(RenderOrder::UICursor);
		SubjectTriangle->CreateAnimation({ .AnimationName = "Advantage", .SpriteName = "Triangle.png", .Start = 0, .End = 2, .FrameInter = 0.15f });
		SubjectTriangle->CreateAnimation({ .AnimationName = "Disadvantage", .SpriteName = "Triangle.png", .Start = 3, .End = 5, .FrameInter = 0.15f });
		SubjectTriangle->ChangeAnimation("Advantage");
		SubjectTriangle->GetTransform()->SetLocalPosition({-202, 250});
		SubjectTriangle->GetTransform()->SetWorldRotation(float4::Zero);
		SubjectTriangle->GetTransform()->SetWorldScale({28, 40});
		SubjectTriangle->GetTransform()->SetParent(BattleEx->GetTransform());

		TargetTriangle = CreateComponent<GameEngineUIRenderer>(RenderOrder::UICursor);
		TargetTriangle->CreateAnimation({ .AnimationName = "Advantage", .SpriteName = "Triangle.png", .Start = 0, .End = 2, .FrameInter = 0.15f });
		TargetTriangle->CreateAnimation({ .AnimationName = "Disadvantage", .SpriteName = "Triangle.png", .Start = 3, .End = 5, .FrameInter = 0.15f });
		TargetTriangle->ChangeAnimation("Advantage");
		TargetTriangle->GetTransform()->SetLocalPosition({ -386, -86 });
		TargetTriangle->GetTransform()->SetWorldRotation(float4::Zero);
		TargetTriangle->GetTransform()->SetWorldScale({ 28, 40 });
		TargetTriangle->GetTransform()->SetParent(BattleEx->GetTransform());

	}

	{
		// ���� ������
		WeaponUses.resize(5);
		for (int i = 0; i < 5; i++)
		{
			WeaponUses[i] = GetLevel()->CreateActor<NumberActor>();
			WeaponUses[i]->GetTransform()->SetLocalPosition({ -52, 192.0f - i * 64});
			WeaponUses[i]->GetTransform()->SetParent(WindowRender->GetTransform());
			WeaponUses[i]->SetValue(0);
			WeaponUses[i]->Off();
		}
	}
	{
		// ���� ��ġ
		WeaponDamage = GetLevel()->CreateActor<NumberActor>();
		WeaponDamage->GetTransform()->SetLocalPosition({ 198, -156 });

		WeaponHit = GetLevel()->CreateActor<NumberActor>();
		WeaponHit->GetTransform()->SetLocalPosition({ 198, -220 });

		WeaponCritical = GetLevel()->CreateActor<NumberActor>();
		WeaponCritical->GetTransform()->SetLocalPosition({ 384, -156 });

		WeaponWeight = GetLevel()->CreateActor<NumberActor>();
		WeaponWeight->GetTransform()->SetLocalPosition({ 384, -220 });
	}
	{
		// ���� ��� ����
		SubjectHP = GetLevel()->CreateActor<NumberActor>();
		SubjectHP->GetTransform()->SetLocalPosition({ -68 - 318, 128 + 62, 0 });
		SubjectHP->GetTransform()->SetWorldRotation(float4::Zero);
		SubjectHP->GetTransform()->SetWorldScale({ 1, 1, 1 });
		SubjectHP->GetTransform()->SetParent(BattleEx->GetTransform());

		SubjectDamage = GetLevel()->CreateActor<NumberActor>();
		SubjectDamage->GetTransform()->SetLocalPosition({ -68 - 318, 64 + 62, 0 });
		SubjectDamage->GetTransform()->SetWorldRotation(float4::Zero);
		SubjectDamage->GetTransform()->SetWorldScale({ 1, 1, 1 });
		SubjectDamage->GetTransform()->SetParent(BattleEx->GetTransform());

		SubjectDoubleAttack = GetLevel()->CreateActor<DoubleIconActor>();
		SubjectDoubleAttack->GetTransform()->SetLocalPosition({ -48 - 318, 48 + 62, 0 });
		SubjectDoubleAttack->GetTransform()->SetWorldRotation(float4::Zero);
		SubjectDoubleAttack->GetTransform()->SetWorldScale({ 1, 1, 1 });
		SubjectDoubleAttack->GetTransform()->SetParent(BattleEx->GetTransform());

		SubjectHit = GetLevel()->CreateActor<NumberActor>();
		SubjectHit->GetTransform()->SetLocalPosition({ -68 - 318, 62, 0 });
		SubjectHit->GetTransform()->SetWorldRotation(float4::Zero);
		SubjectHit->GetTransform()->SetWorldScale({ 1, 1, 1 });
		SubjectHit->GetTransform()->SetParent(BattleEx->GetTransform());

		SubjectCritical = GetLevel()->CreateActor<NumberActor>();
		SubjectCritical->GetTransform()->SetLocalPosition({ -68 - 318, -64 + 62, 0 });
		SubjectCritical->GetTransform()->SetWorldRotation(float4::Zero);
		SubjectCritical->GetTransform()->SetWorldScale({ 1, 1, 1 });
		SubjectCritical->GetTransform()->SetParent(BattleEx->GetTransform());

		TargetHP = GetLevel()->CreateActor<NumberActor>();
		TargetHP->GetTransform()->SetLocalPosition({ 118 - 318, 128 + 62, 0 });
		TargetHP->GetTransform()->SetWorldRotation(float4::Zero);
		TargetHP->GetTransform()->SetWorldScale({ 1, 1, 1 });
		TargetHP->GetTransform()->SetParent(BattleEx->GetTransform());

		TargetDamage = GetLevel()->CreateActor<NumberActor>();
		TargetDamage->GetTransform()->SetLocalPosition({ 118 - 318, 64 + 62, 0 });
		TargetDamage->GetTransform()->SetWorldRotation(float4::Zero);
		TargetDamage->GetTransform()->SetWorldScale({ 1, 1, 1 });
		TargetDamage->GetTransform()->SetParent(BattleEx->GetTransform());

		TargetDoubleAttack = GetLevel()->CreateActor<DoubleIconActor>();
		TargetDoubleAttack->GetTransform()->SetLocalPosition({ 138 - 318, 48 + 62, 0 });
		TargetDoubleAttack->GetTransform()->SetWorldRotation(float4::Zero);
		TargetDoubleAttack->GetTransform()->SetWorldScale({ 1, 1, 1 });
		TargetDoubleAttack->GetTransform()->SetParent(BattleEx->GetTransform());

		TargetHit = GetLevel()->CreateActor<NumberActor>();
		TargetHit->GetTransform()->SetLocalPosition({ 118 - 318, 62, 0 });
		TargetHit->GetTransform()->SetWorldRotation(float4::Zero);
		TargetHit->GetTransform()->SetWorldScale({ 1, 1, 1 });
		TargetHit->GetTransform()->SetParent(BattleEx->GetTransform());

		TargetCritical = GetLevel()->CreateActor<NumberActor>();;
		TargetCritical->GetTransform()->SetLocalPosition({ 118 - 318, -64 + 62, 0 });
		TargetCritical->GetTransform()->SetWorldRotation(float4::Zero);
		TargetCritical->GetTransform()->SetWorldScale({ 1, 1, 1 });
		TargetCritical->GetTransform()->SetParent(BattleEx->GetTransform());

	}

	ButtonSystem = GetLevel()->CreateActor<UIButtonSystem>();
	ButtonSystem->GetTransform()->SetParent(GetTransform());

	ButtonCols.resize(5);
	ItemNameTexts.resize(5);
	for (int i = 0; i < 5; i++)
	{
		ButtonCols[i] = CreateComponent<GameEngineCollision>(CollisionOrder::Button);
		ButtonCols[i]->GetTransform()->SetLocalPosition({ -250, 192.0f - (64 * i) });
		ButtonCols[i]->GetTransform()->SetLocalScale({ 400, 64 });
		ButtonCols[i]->SetColType(ColType::AABBBOX2D);
		ButtonSystem->NewButton(ButtonCols[i],
			[=] {
				if (CurrentCursor != i)
				{
					CurrentCursor = i;
					SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
					CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
					SetWeapon();
					GameEngineSound::Play("CommandMove.wav");
				}
			},
			[this]
			{
				IsClick = true;
			}
		);
		ItemNameTexts[i] = CreateComponent<TextRenderer>(RenderOrder::UIText);
		ItemNameTexts[i]->GetTransform()->SetLocalPosition({ -332, 220.0f - (64 * i) });
		ItemNameTexts[i]->Setting("Silhoua14", 55, float4::White, float4::Black, FontAligned::Left);
		ItemNameTexts[i]->Off();
	}

	GameEngineActor::Off();
}

void AttackUI::Update(float _DeltaTime)
{
	if (true == IsWeaponSelect)
	{
		TargetSelectUpdate(_DeltaTime);
		return;
	}
	WeaponSelectUpdate(_DeltaTime);
}

void AttackUI::WeaponSelectStart()
{
	IsWeaponSelect = false;
	SelectRender->On();
	WindowRender->On();
	InfoRender->On();
	Portrait->On();
	Cursor_UI->On();
	BattleEx->Off();

	// ���� ���� ǥ��
	WeaponDamage->On();
	WeaponHit->On();
	WeaponCritical->On();
	WeaponWeight->On();

	WeaponDamage->SetValue(SelectUnit->GetUnitData().GetCurWeapon()->GetDamage());
	WeaponHit->SetValue(SelectUnit->GetUnitData().GetCurWeapon()->GetHit());
	WeaponCritical->SetValue(SelectUnit->GetUnitData().GetCurWeapon()->GetCritical());
	WeaponWeight->SetValue(SelectUnit->GetUnitData().GetCurWeapon()->GetWeight());

	for (int i = 0; i < Weapons.size(); i++)
	{
		WeaponeIcon[i]->On();
	}
	SubjectWeapon->Off();
	TargetWeapon->Off();
	SetWeapon();

	for (int i = 0; i < Weapons.size(); i++)
	{
		ButtonCols[i]->On();
		ItemNameTexts[i]->On();
	}
	for (size_t i = Weapons.size(); i < 5; i++)
	{
		ButtonCols[i]->Off();
		ItemNameTexts[i]->Off();
	}
}

void AttackUI::WeaponSelectUpdate(float _DeltaTime)
{
	if (true == IsOnFrame)
	{
		IsOnFrame = false;
		return;
	}

	if (GameEngineInput::IsDown("ButtonA") || true == IsClick)
	{
		GameEngineSound::Play("CommandSelect.wav");
		IsClick = false;
		WeaponSelectEnd();
		TargetSelectStart();
		return;
	}
	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		GameEngineSound::Play("Cancel.wav");
		CancelFunction();
		return;
	}

	CursorTimer += _DeltaTime * 10;
	Cursor_UI->GetTransform()->SetLocalPosition(float4::Lerp(Cursor_UI->GetTransform()->GetLocalPosition(), CursorPos, _DeltaTime * 20));

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
			CurrentCursor = Weapons.size() - 1;
			SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
			CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
			SetWeapon();
			return;
		}
		CurrentCursor--;
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
		CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
		SetWeapon();
		return;
	}

	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK) || GameEngineInput::IsUp("MiddleClick"))
	{
		GameEngineSound::Play("CommandMove.wav");
		CursorTimer = 0;
		if (CurrentCursor == Weapons.size() - 1)
		{
			if (false == GameEngineInput::IsDown("Down") && false == GameEngineInput::IsUp("MiddleClick")) { return; }
			CurrentCursor = 0;
			SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
			CursorPos = StartCursorPos;
			SetWeapon();
			return;
		}
		CurrentCursor++;
		SelectRender->GetTransform()->SetLocalPosition(StartSelectPos + float4::Down * (64.0f * CurrentCursor));
		CursorPos = StartCursorPos + float4::Down * (64.0f * CurrentCursor);
		SetWeapon();
		return;
	}

}

void AttackUI::WeaponSelectEnd()
{
	SelectRender->Off();
	WindowRender->Off();
	InfoRender->Off();
	Portrait->Off();
	Cursor_UI->Off();
	BattleEx->On();
	for (int i = 0; i < Weapons.size(); i++)
	{
		WeaponeIcon[i]->Off();
		ItemNameTexts[i]->Off();
	}
	for (int i = 0; i < 5; i++)
	{
		ButtonCols[i]->Off();
	}
}

void AttackUI::SetWeapon()
{
	std::list<std::shared_ptr<Weapon>>::iterator StartIter = Weapons.begin();
	std::advance(StartIter, CurrentCursor);
	if (StartIter == Weapons.end())
	{
		MsgAssert("������ ���⸦ ���⸮��Ʈ���� ã�� ���߽��ϴ�.");
		return;
	}
	SelectWeapon = *StartIter;

	WeaponDamage->SetValue(SelectWeapon->GetDamage());
	WeaponHit->SetValue(SelectWeapon->GetHit());
	WeaponCritical->SetValue(SelectWeapon->GetCritical());
	WeaponWeight->SetValue(SelectWeapon->GetWeight());
}

void AttackUI::TargetSelectStart()
{
	SelectUnit->GetUnitData().EquipWeapon(SelectWeapon);
	IsWeaponSelect = true;

	TargetIter = TargetUnits.begin();
	Cursor_Map->On();

	SetTarget();
	SubjectWeapon->On();
	TargetWeapon->On();

	WeaponDamage->Off();
	WeaponHit->Off();
	WeaponCritical->Off();
	WeaponWeight->Off();

}

void AttackUI::TargetSelectUpdate(float _DeltaTime)
{
	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick"))
	{
		GameEngineSound::Play("CommandSelect.wav");
		AttackFunction(TargetUnit);
		Cursor_Map->Off();
		Off();
		return;
	}

	if (GameEngineInput::IsDown("ButtonB") || GameEngineInput::IsUp("RightClick"))
	{
		GameEngineSound::Play("Cancel.wav");
		WeaponSelectStart();
		Cursor_Map->SetCursorPos(SelectUnit->GetMapPos());
		Cursor_Map->Off();
		return;
	}
	if (Cursor_Map->GetIsMove()) { return; }


	if (GameEngineInput::IsDown("Up") || GameEngineInput::IsDown("Left"))
	{
		GameEngineSound::Play("CommandMove.wav");
		if (TargetIter == TargetUnits.begin())
		{
			TargetIter = TargetUnits.end();
		}
		TargetIter--;
		SetTarget();
		return;
	}
	if (GameEngineInput::IsDown("Down") || GameEngineInput::IsDown("Right") || GameEngineInput::IsUp("MiddleClick"))
	{
		GameEngineSound::Play("CommandMove.wav");
		TargetIter++;
		if (TargetIter == TargetUnits.end())
		{
			TargetIter = TargetUnits.begin();
		}
		SetTarget();
		return;
	}
}

void AttackUI::TargetSelectEnd()
{
}

void AttackUI::SetTarget()
{

	TargetUnit = *TargetIter;
	Cursor_Map->SetCursorPos(TargetUnit->GetMapPos());

	// Ÿ�� ���ý� ����Ǵ� UI ����� ó��
	SubjectWeapon->SetFrame(static_cast<size_t>(SelectWeapon->GetItemCode()) - 1);
	TargetWeapon->SetFrame(static_cast<size_t>(TargetUnit->GetUnitData().GetCurWeapon()->GetItemCode()) - 1);

	SubjectName->SetText(SelectUnit->GetName());
	TargetName->SetText(TargetUnit->GetName());
	TargetWeaponName->SetText(TargetUnit->GetUnitData().GetCurWeapon()->GetName());
	// ü��
	SubjectHP->SetValue(SelectUnit->GetUnitData().GetHP());
	// ������ �����Ѱ� (��Ÿ�)
	if (SelectUnit->IsAttackable(TargetUnit))
	{
		SubjectDamage->SetValue(SelectUnit->GetUnitData().GetAttackPoint(TargetUnit->GetUnitData()));
		SubjectHit->SetValue(SelectUnit->GetUnitData().GetHitPoint(TargetUnit->GetUnitData()));
		SubjectCritical->SetValue(SelectUnit->GetUnitData().GetCriticalPoint(TargetUnit->GetUnitData()));
	}
	else
	{
		// ���� �Ұ��� �� 0
		SubjectDamage->SetValue(0);
		SubjectHit->SetValue(0);
		SubjectCritical->SetValue(0);
	}
	// �߰��� �ߵ��ϴ°�
	if (SelectUnit->GetUnitData().IsDoubleAttack(TargetUnit->GetUnitData()))
	{
		SubjectDoubleAttack->On();
	}
	else
	{
		SubjectDoubleAttack->Off();
	}

	TargetHP->SetValue(TargetUnit->GetUnitData().GetHP());
	if (TargetUnit->IsAttackable(SelectUnit))
	{
		TargetDamage->SetValue(TargetUnit->GetUnitData().GetAttackPoint(SelectUnit->GetUnitData()));
		TargetHit->SetValue(TargetUnit->GetUnitData().GetHitPoint(SelectUnit->GetUnitData()));
		TargetCritical->SetValue(TargetUnit->GetUnitData().GetCriticalPoint(SelectUnit->GetUnitData()));
	}
	else
	{
		TargetDamage->SetValue(0);
		TargetHit->SetValue(0);
		TargetCritical->SetValue(0);
	}
	if (TargetUnit->GetUnitData().IsDoubleAttack(SelectUnit->GetUnitData()))
	{
		TargetDoubleAttack->On();
	}
	else
	{
		TargetDoubleAttack->Off();
	}

	// ���� �� ��
	int TriangleValue = Weapon::GetWeaponeTriangle(SelectUnit->GetUnitData().GetCurWeapon(), TargetUnit->GetUnitData().GetCurWeapon());
	switch (TriangleValue)
	{
	case 0:
		SubjectTriangle->Off();
		TargetTriangle->Off();
		break;
	case 1:
		SubjectTriangle->On();
		SubjectTriangle->ChangeAnimation("Advantage");
		TargetTriangle->On();
		TargetTriangle->ChangeAnimation("Disadvantage");
		break;
	case -1:
		SubjectTriangle->On();
		SubjectTriangle->ChangeAnimation("Disadvantage");
		TargetTriangle->On();
		TargetTriangle->ChangeAnimation("Advantage");
		break;
	default:
		break;
	}

}
