#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "MapCursor.h"
#include "ArrowRender.h"
#include "BattleMap.h"
#include "SelectUI.h"
#include "BattleUnit.h"
#include "TileRender.h"
#include "SpriteRenderer.h"
#include "UnitCommand.h"
#include "FERandom.h"
const float PreesTime = 0.2f;
bool PressOK = false;
void BattleLevel::CursorMove()
{
	if (true == MainCursor->GetIsMove())
	{
		return;
	}

	if (GameEngineInput::IsDown("LeftClick") || GameEngineInput::IsDown("RightClick"))
	{
		IsMouseOn = true;
		float4 MousePos = GameEngineInput::GetMousePosition();
		float4 MouseLocalPos = float4(MousePos.x, 640 - MousePos.y);
		int2 MouseMapPos = int2::Float4ToInt2(MouseLocalPos * 0.015625f);		// 64 ������
		MainCursor->SetMapPos(MouseMapPos);
		CursorDirCheck();	// Ŀ���� ����(���߾� ����) üũ
		CursorUnitSelect();
		return;
	}

	if (
		PreesTime < GameEngineInput::GetPressTime("Up") ||
		PreesTime < GameEngineInput::GetPressTime("Down") ||
		PreesTime < GameEngineInput::GetPressTime("Left") ||
		PreesTime < GameEngineInput::GetPressTime("Right")
		)
	{
		PressOK = true;
	}
	else if (
		GameEngineInput::IsFree("Up") &&
		GameEngineInput::IsFree("Down") &&
		GameEngineInput::IsFree("Left") &&
		GameEngineInput::IsFree("Right")
		)
	{
		PressOK = false;
	}


	int2 CursorPos = MainCursor->GetMapPos();
	int2 MoveValue = { 0 };

	if (GameEngineInput::IsDown("Up") || (GameEngineInput::IsPress("Up") && PressOK))
	{

		// �̵��� ���� �� ���� �ƴ϶��
		if (false == IsMapOut(CursorPos + MoveValue + int2::Up))
		{
			MoveValue += int2::Up;
		}

	}
	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		// �̵��� ���� �� ���� �ƴ϶��
		if (false == IsMapOut(CursorPos + MoveValue + int2::Down))
		{
			MoveValue += int2::Down;
		}
	}
	if (GameEngineInput::IsDown("Left") || (GameEngineInput::IsPress("Left") && PressOK))
	{
		// �̵��� ���� �� ���� �ƴ϶��
		if (false == IsMapOut(CursorPos + MoveValue + int2::Left))
		{
			MoveValue += int2::Left;
		}
	}
	if (GameEngineInput::IsDown("Right") || (GameEngineInput::IsPress("Right") && PressOK))
	{
		// �̵��� ���� �� ���� �ƴ϶��
		if (false == IsMapOut(CursorPos + MoveValue + int2::Right))
		{
			MoveValue += int2::Right;
		}
	}

	if (MoveValue != int2{ 0 })
	{
		MainCursor->MoveMapPosLerp(MoveValue);
		CursorDirCheck();	// Ŀ���� ����(���߾� ����) üũ
		CursorUnitSelect();

	}
}

void BattleLevel::CursorUnitSelect()
{
	// Ŀ���� �̵��� ���� �Ʊ� ������ �ִ°�?
	SelectUnit = nullptr;
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (_Unit->GetIsDie()) { continue; }
		if (MainCursor->GetMapPos() == _Unit->GetMapPos())
		{
			SelectUnit = _Unit;
			SetUI_UnitData();	// ���� ���� UI�� ����
			MoveSearch();	// �̵����� Ž��, �ڵ����� ���ݹ����� Ž��
			Tiles->SetTile(IsMove, IsAttack);
			return;
		}
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		if (_Unit->GetIsDie()) { continue; }
		if (MainCursor->GetMapPos() == _Unit->GetMapPos())
		{
			SelectUnit = _Unit;
			SetUI_UnitData();	// ���� ���� UI�� ����
			MoveSearchForEnemy();	// �̵����� Ž��, �ڵ����� ���ݹ����� Ž��
			Tiles->SetTile(IsMove, IsAttack);
			return;
		}
	}
	Tiles->Clear();
	UI_Select->UnitUIOff();
}

void BattleLevel::CursorAndArrowMove()
{

	if (true == MainCursor->GetIsMove())
	{
		return;
	}

	if (GameEngineInput::IsDown("LeftClick") || GameEngineInput::IsDown("RightClick"))
	{
		IsMouseOn = true;
		float4 MousePos = GameEngineInput::GetMousePosition();
		float4 MouseLocalPos = float4(MousePos.x, 640 - MousePos.y);
		int2 MouseMapPos = int2::Float4ToInt2(MouseLocalPos * 0.015625f);
		MainCursor->SetMapPos(MouseMapPos);
		return;
	}

	if (
		PreesTime < GameEngineInput::GetPressTime("Up") ||
		PreesTime < GameEngineInput::GetPressTime("Down") ||
		PreesTime < GameEngineInput::GetPressTime("Left") ||
		PreesTime < GameEngineInput::GetPressTime("Right")
		)
	{
		PressOK = true;
	}
	else if (
		GameEngineInput::IsFree("Up") &&
		GameEngineInput::IsFree("Down") &&
		GameEngineInput::IsFree("Left") &&
		GameEngineInput::IsFree("Right")
		)
	{
		PressOK = false;
	}


	int2 CursorPos = MainCursor->GetMapPos();
	int2 MoveValue = { 0 };

	if (GameEngineInput::IsDown("Up") || (GameEngineInput::IsPress("Up") && PressOK))
	{

		// �̵��� ���� �� ���� �ƴ϶��
		if (false == IsMapOut(CursorPos + MoveValue + int2::Up))
		{
			MoveValue += int2::Up;
		}

	}
	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		// �̵��� ���� �� ���� �ƴ϶��
		if (false == IsMapOut(CursorPos + MoveValue + int2::Down))
		{
			MoveValue += int2::Down;
		}
	}
	if (GameEngineInput::IsDown("Left") || (GameEngineInput::IsPress("Left") && PressOK))
	{
		// �̵��� ���� �� ���� �ƴ϶��
		if (false == IsMapOut(CursorPos + MoveValue + int2::Left))
		{
			MoveValue += int2::Left;
		}
	}
	if (GameEngineInput::IsDown("Right") || (GameEngineInput::IsPress("Right") && PressOK))
	{
		// �̵��� ���� �� ���� �ƴ϶��
		if (false == IsMapOut(CursorPos + MoveValue + int2::Right))
		{
			MoveValue += int2::Right;
		}
	}

	if (MoveValue != int2{ 0 })
	{
		MainCursor->MoveMapPosLerp(MoveValue);
		AddArrow(MainCursor->GetMapPos());
	}
}

void BattleLevel::CursorMoveMouse()
{
	if (
		GameEngineInput::IsDown("Up") ||
		GameEngineInput::IsDown("Down") ||
		GameEngineInput::IsDown("Left") ||
		GameEngineInput::IsDown("Right")
		)
	{
		IsMouseOn = false;
		return;
	}

	if (true == MainCursor->GetIsMove()) { return; }

	int2 CursorPos = MainCursor->GetMapPos();
	float4 MousePos = GameEngineInput::GetMousePosition();
	float4 MouseLocalPos = float4(MousePos.x, 640 - MousePos.y);
	int2 MouseMapPos = int2::Float4ToInt2(MouseLocalPos * 0.015625f);
	if (1 <= CursorPos.GetDistance(MouseMapPos))
	{
		int2 MovePos = MouseMapPos - CursorPos;
		MainCursor->MoveMapPosLerp(MovePos.Normalize());
		CursorUnitSelect();
		CursorDirCheck();
	}


}

void BattleLevel::CursorAndArrowMoveMouse()
{
	if (
		GameEngineInput::IsDown("Up") ||
		GameEngineInput::IsDown("Down") ||
		GameEngineInput::IsDown("Left") ||
		GameEngineInput::IsDown("Right")
		)
	{
		IsMouseOn = false;
		return;
	}

	if (true == MainCursor->GetIsMove()) { return; }

	int2 CursorPos = MainCursor->GetMapPos();
	float4 MousePos = GameEngineInput::GetMousePosition();
	float4 MouseLocalPos = float4(MousePos.x, 640 - MousePos.y);
	int2 MouseMapPos = int2::Float4ToInt2(MouseLocalPos * 0.015625f);

	if (1 <= CursorPos.GetDistance(MouseMapPos))
	{
		int2 MovePos = MouseMapPos - CursorPos;
		MainCursor->MoveMapPosLerp(MovePos.Normalize());
		AddArrow(MainCursor->GetMapPos());
		CursorDirCheck();
	}
}

void BattleLevel::CursorDirCheck()
{
	float4 CursorPos = MainCursor->EndPos;
	static float4 ScreenSize = GameEngineWindow::GetScreenSize() - float4(0, TileScale);
	UIDir CursorDir = UIDir::None;

	if (CursorPos.ix() < ScreenSize.hix())
	{
		// ����
		if (CursorPos.iy() > ScreenSize.hiy())
		{
			// ��
			CursorDir = UIDir::LeftUp;
		}
		else
		{
			// �Ʒ�
			CursorDir = UIDir::LeftDown;
		}
	}
	else
	{
		// ������
		if (CursorPos.iy() > ScreenSize.hiy())
		{
			// ��
			CursorDir = UIDir::RightUp;
		}
		else
		{
			// �Ʒ�
			CursorDir = UIDir::RightDown;
		}
	}

	UI_Select->SetCursorDir(CursorDir);
}

void BattleLevel::UnitSelect()
{
	// Ȯ�ι�ư �Է½ÿ���
	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick")) {

		if (true == IsMapOut(MainCursor->GetMapPos())) { return; }

		// ������ ���� ������ ���ٸ�
		if (nullptr == SelectUnit)
		{
			ChangeState(BattleState::FieldCommand);
			return;
		}

		// ������ ������ �÷��̾� �����ΰ�?
		if (true == SelectUnit->GetIsPlayer())
		{
			// ���� ������� �ʾҴٸ�
			if (false == SelectUnit->GetIsTurnEnd())
			{
				ChangeState(BattleState::Move);
				return;
			}
			else
			{
				ChangeState(BattleState::FieldCommand);
				return;
			}
		}
		else
		{
			// �� �����̶�� ���� ���� Ž��
			SelectUnit->SetIsCheckTile(!SelectUnit->GetIsCheckTile());
			if (true == SelectUnit->GetIsCheckTile())
			{
				SelectUnit->GetRenderer()->SetLerp({ 1.0f, 0.0f, 0.5f }, 0.3f);
			}
			else
			{
				SelectUnit->GetRenderer()->OffLerp();
			}
			EnemyTileCheck();
			MoveSearchForEnemy();
			Tiles->SetTile(IsMove, IsAttack);
		}
		return;
	}

	// L��ư(A Ű)�� ������ �Ʊ������� �ڵ����� ã���ִ� ���
	if (GameEngineInput::IsDown("ButtonL"))
	{
		if (true == MainCursor->GetIsMove()) { return; }

		if (nullptr == SelectUnit)
		{
			for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
			{
				if (_Unit->GetIsDie()) { continue; }
				if (_Unit->GetIsTurnEnd()) { continue; }
				SelectUnit = _Unit;
				MainCursor->SetMapPos(SelectUnit->GetMapPos());
				CursorDirCheck();
				SetUI_UnitData();
				return;
			}
		}
		else
		{
			std::list<std::shared_ptr<BattleUnit>>::iterator Start = PlayerUnits.begin();
			std::list<std::shared_ptr<BattleUnit>>::iterator End = PlayerUnits.end();
			for (; Start != End; Start++)
			{
				if ((*Start)->GetUnitCode() == SelectUnit->GetUnitCode())
				{
					Start++;
					for (; Start != End; Start++)
					{
						if ((*Start)->GetIsDie()) { continue; }
						if ((*Start)->GetIsTurnEnd()) { continue; }
						if ((*Start)->GetUnitCode() == SelectUnit->GetUnitCode()) { continue; }

						SelectUnit = *Start;
						MainCursor->SetMapPos(SelectUnit->GetMapPos());
						CursorDirCheck();
						SetUI_UnitData();
						return;
					}
					for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
					{
						if (_Unit->GetIsDie()) { continue; }
						if (_Unit->GetIsTurnEnd()) { continue; }
						if (_Unit->GetUnitCode() == SelectUnit->GetUnitCode()) { continue; }
						SelectUnit = _Unit;
						MainCursor->SetMapPos(SelectUnit->GetMapPos());
						CursorDirCheck();
						SetUI_UnitData();
						return;
					}
					return;
				}
			}
		}


	}

	// Y��ư(C Ű)�� ������ ��� ���� ���� ���� ������ ǥ��
	if (GameEngineInput::IsDown("ButtonY"))
	{
		IsEnemyRangeCheck = !IsEnemyRangeCheck;
		EnemyTileCheck();


		// ������ ������ �ִٸ�
		if (nullptr == SelectUnit) { return; }

		if (true == SelectUnit->GetIsPlayer())
		{
			MoveSearch();
		}
		else
		{
			MoveSearchForEnemy();
		}
		Tiles->SetTile(IsMove, IsAttack);
		return;

	}
	// ������ ������ ������ ǥ���ϴ� ���
	if (GameEngineInput::IsDown("ButtonR"))
	{
		if (nullptr == SelectUnit) { return; }
		MsgTextBox(SelectUnit->ToString());
	}


	// �ð��� �ǵ����� ��� (�׽�Ʈ��)
	if (GameEngineInput::IsDown("ButtonX"))
	{
		ChangeState(BattleState::TimeStone);
		return;

	}
}

void BattleLevel::SetUI_UnitData()
{
	UI_Select->SetUnitData(SelectUnit);
}

