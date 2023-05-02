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
const float PreesTime = 0.2f;
bool PressOK = false;
void BattleLevel::CursorMove()
{

	if (
		PreesTime < GameEngineInput::GetPressTime("UpMove") ||
		PreesTime < GameEngineInput::GetPressTime("DownMove") ||
		PreesTime < GameEngineInput::GetPressTime("LeftMove") ||
		PreesTime < GameEngineInput::GetPressTime("RightMove")
		)
	{
		PressOK = true;
	}
	else if (
		GameEngineInput::IsFree("UpMove") &&
		GameEngineInput::IsFree("DownMove") &&
		GameEngineInput::IsFree("LeftMove") &&
		GameEngineInput::IsFree("RightMove")
		)
	{
		PressOK = false;
	}


	int2 CursorPos = MainCursor->GetMapPos();
	int2 MoveValue = { 0 };

	if (GameEngineInput::IsDown("UpMove") || (GameEngineInput::IsPress("UpMove") && PressOK))
	{

		// Ŀ���� �̵����� �ƴϸ� �̵��� ���� �� ���� �ƴ϶��
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Up))
		{
			MoveValue += int2::Up;
		}

	}
	if (GameEngineInput::IsDown("DownMove") || (GameEngineInput::IsPress("DownMove") && PressOK))
	{
		// Ŀ���� �̵����� �ƴϸ� �̵��� ���� �� ���� �ƴ϶��
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Down))
		{
			MoveValue += int2::Down;
		}
	}
	if (GameEngineInput::IsDown("LeftMove") || (GameEngineInput::IsPress("LeftMove") && PressOK))
	{
		// Ŀ���� �̵����� �ƴϸ� �̵��� ���� �� ���� �ƴ϶��
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Left))
		{
			MoveValue += int2::Left;
		}
	}
	if (GameEngineInput::IsDown("RightMove") || (GameEngineInput::IsPress("RightMove") && PressOK))
	{
		// Ŀ���� �̵����� �ƴϸ� �̵��� ���� �� ���� �ƴ϶��
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Right))
		{
			MoveValue += int2::Right;
		}
	}

	if (MoveValue != int2{ 0 })
	{
		MainCursor->MoveMapPosLerp(MoveValue);
		CursorDirCheck();	// Ŀ���� ����(���߾� ����) üũ

		// Ŀ���� �̵��� ���� �Ʊ� ������ �ִ°�?
		SelectUnit = nullptr;
		for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
		{
			if (_Unit->GetIsDie()) { continue; }
			if (MainCursor->GetMapPos() == _Unit->GetMapPos())
			{
				SelectUnit = _Unit;
				return;
			}
		}
		for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
		{
			if (_Unit->GetIsDie()) { continue; }
			if (MainCursor->GetMapPos() == _Unit->GetMapPos())
			{
				SelectUnit = _Unit;
				return;
			}
		}
	}
}

void BattleLevel::CursorAndArrowMove()
{

	if (
		PreesTime < GameEngineInput::GetPressTime("UpMove") ||
		PreesTime < GameEngineInput::GetPressTime("DownMove") ||
		PreesTime < GameEngineInput::GetPressTime("LeftMove") ||
		PreesTime < GameEngineInput::GetPressTime("RightMove")
		)
	{
		PressOK = true;
	}
	else if (
		GameEngineInput::IsFree("UpMove") &&
		GameEngineInput::IsFree("DownMove") &&
		GameEngineInput::IsFree("LeftMove") &&
		GameEngineInput::IsFree("RightMove")
		)
	{
		PressOK = false;
	}


	int2 CursorPos = MainCursor->GetMapPos();
	int2 MoveValue = { 0 };

	if (GameEngineInput::IsDown("UpMove") || (GameEngineInput::IsPress("UpMove") && PressOK))
	{

		// Ŀ���� �̵����� �ƴϸ� �̵��� ���� �� ���� �ƴ϶��
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Up))
		{
			MoveValue += int2::Up;
		}

	}
	if (GameEngineInput::IsDown("DownMove") || (GameEngineInput::IsPress("DownMove") && PressOK))
	{
		// Ŀ���� �̵����� �ƴϸ� �̵��� ���� �� ���� �ƴ϶��
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Down))
		{
			MoveValue += int2::Down;
		}
	}
	if (GameEngineInput::IsDown("LeftMove") || (GameEngineInput::IsPress("LeftMove") && PressOK))
	{
		// Ŀ���� �̵����� �ƴϸ� �̵��� ���� �� ���� �ƴ϶��
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Left))
		{
			MoveValue += int2::Left;
		}
	}
	if (GameEngineInput::IsDown("RightMove") || (GameEngineInput::IsPress("RightMove") && PressOK))
	{
		// Ŀ���� �̵����� �ƴϸ� �̵��� ���� �� ���� �ƴ϶��
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Right))
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
	if (GameEngineInput::IsDown("OK")) {

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
			}
		}
		else
		{
			// �� �����̶�� ���� ���� Ž��
			ArrowPos.clear();
			ArrowPos.push_back(SelectUnit->GetMapPos());
			MoveSearchForEnemy();
			Tiles->SetTile(IsMove, IsAttack);
		}
		return;
	}

	if (GameEngineInput::IsDown("Cancel"))
	{
		// ���Ű ������ �� ���ݹ��� ǥ�� ��
		Tiles->Clear();
	}

	// AŰ�� ������ �Ʊ������� �ڵ����� ã���ִ� ���
	if (GameEngineInput::IsDown("Next"))
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
						return;
					}
					for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
					{
						if (_Unit->GetIsDie()) { continue; }
						if (_Unit->GetIsTurnEnd()) { continue; }
						if (_Unit->GetUnitCode() == SelectUnit->GetUnitCode()) { continue; }
						SelectUnit = _Unit;
						MainCursor->SetMapPos(SelectUnit->GetMapPos());
						return;
					}
					return;
				}
			}
		}


	}

	// ������ ������ ������ ǥ���ϴ� ���
	if (GameEngineInput::IsDown("Select"))
	{
		if (nullptr == SelectUnit) { return; }
		MsgTextBox(SelectUnit->ToString());
	}
}
