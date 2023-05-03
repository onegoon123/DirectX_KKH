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
const float PreesTime = 0.2f;
bool PressOK = false;
void BattleLevel::CursorMove()
{
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

		// Ŀ���� �̵����� �ƴϸ� �̵��� ���� �� ���� �ƴ϶��
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Up))
		{
			MoveValue += int2::Up;
		}

	}
	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		// Ŀ���� �̵����� �ƴϸ� �̵��� ���� �� ���� �ƴ϶��
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Down))
		{
			MoveValue += int2::Down;
		}
	}
	if (GameEngineInput::IsDown("Left") || (GameEngineInput::IsPress("Left") && PressOK))
	{
		// Ŀ���� �̵����� �ƴϸ� �̵��� ���� �� ���� �ƴ϶��
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Left))
		{
			MoveValue += int2::Left;
		}
	}
	if (GameEngineInput::IsDown("Right") || (GameEngineInput::IsPress("Right") && PressOK))
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
}

void BattleLevel::CursorAndArrowMove()
{

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

		// Ŀ���� �̵����� �ƴϸ� �̵��� ���� �� ���� �ƴ϶��
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Up))
		{
			MoveValue += int2::Up;
		}

	}
	if (GameEngineInput::IsDown("Down") || (GameEngineInput::IsPress("Down") && PressOK))
	{
		// Ŀ���� �̵����� �ƴϸ� �̵��� ���� �� ���� �ƴ϶��
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Down))
		{
			MoveValue += int2::Down;
		}
	}
	if (GameEngineInput::IsDown("Left") || (GameEngineInput::IsPress("Left") && PressOK))
	{
		// Ŀ���� �̵����� �ƴϸ� �̵��� ���� �� ���� �ƴ϶��
		if (false == MainCursor->GetIsMove() && false == IsMapOut(CursorPos + MoveValue + int2::Left))
		{
			MoveValue += int2::Left;
		}
	}
	if (GameEngineInput::IsDown("Right") || (GameEngineInput::IsPress("Right") && PressOK))
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
	if (GameEngineInput::IsDown("ButtonA")) {

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
				SelectUnit->GetRenderer()->SetLerp({1.0f, 0.0f, 0.5f}, 0.3f);
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
}

void BattleLevel::SetUI_UnitData()
{
	UI_Select->SetUnitData(SelectUnit);
}

