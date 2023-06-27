#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "MapCursor.h"
#include "ArrowRender.h"
#include "BattleMap.h"
#include "BattleUnit.h"
#include "TileRender.h"
#include "SpriteRenderer.h"
#include "UnitCommand.h"
#include "FERandom.h"
#include "BattleLevelUI.h"
const float PreesTime = 0.2f;
bool PressOK = false;
void BattleLevel::CursorMove()
{
	if (true == MainCursor->GetIsMove())
	{
		return;
	}

	if (GameEngineInput::IsUp("LeftClick") || GameEngineInput::IsUp("RightClick"))
	{
		IsMouseOn = true;
		MainCursor->SetSoundPlay(false);
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


	int2 CursorPos = MainCursor->WorldPos;
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
		CameraMove(MoveValue);
		MainCursor->MoveCursorPosLerp(MoveValue);
		CursorDirCheck();	// Ŀ���� ����(���߾� ����) üũ
		CursorUnitSelect();
		BattleUI->SetTerrain(GetTerrain(MainCursor->WorldPos));
	}
}

void BattleLevel::CursorUnitSelect()
{
	// Ŀ���� �̵��� ���� �Ʊ� ������ �ִ°�?
	SelectUnit = nullptr;
	for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
	{
		if (_Unit->GetIsDie()) { continue; }
		if (MainCursor->WorldPos == _Unit->GetMapPos())
		{
			SelectUnit = _Unit;
			SetUI_UnitData();	// ���� ���� UI�� ����
			MoveSearch();	// �̵����� Ž��, �ڵ����� ���ݹ����� Ž��
			SetTile();
			MainCursor->Select();
			return;
		}
	}
	for (std::shared_ptr<BattleUnit> _Unit : EnemyUnits)
	{
		if (_Unit->GetIsDie()) { continue; }
		if (MainCursor->WorldPos == _Unit->GetMapPos())
		{
			SelectUnit = _Unit;
			SetUI_UnitData();	// ���� ���� UI�� ����
			MoveSearchForEnemy();	// �̵����� Ž��, �ڵ����� ���ݹ����� Ž��
			SetTile();
			return;
		}
	}
	Tiles->Clear();
	BattleUI->UnitUIOff();
	MainCursor->Idle();
}

void BattleLevel::CursorAndArrowMove()
{

	if (true == MainCursor->GetIsMove())
	{
		return;
	}

	if (GameEngineInput::IsUp("LeftClick") || GameEngineInput::IsUp("RightClick"))
	{
		IsMouseOn = true;
		MainCursor->SetSoundPlay(false);
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


	int2 CursorPos = MainCursor->WorldPos;
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
		CameraMove(MoveValue);
		MainCursor->MoveCursorPosLerp(MoveValue);
		AddArrow(MainCursor->WorldPos);
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
		MainCursor->SetSoundPlay(true);
		return;
	}

	if (true == MainCursor->GetIsMove()) { return; }

	int2 CursorPos = MainCursor->WorldPos;
	float4 MousePos = GameEngineInput::GetMousePosition();
	float4 MouseLocalPos = float4(MousePos.x, 640 - MousePos.y);
	int2 MouseMapPos = int2::Float4ToInt2(MouseLocalPos * 0.015625f) + CameraUnit->GetMapPos();
	if (true == IsMapOut(MouseMapPos))
	{
		return;
	}
	if (1 <= CursorPos.GetDistance(MouseMapPos))
	{
		int2 MovePos = MouseMapPos - CursorPos;

		CameraMove(MovePos.Normalize());
		MainCursor->MoveCursorPosLerp(MovePos.Normalize());

		CursorDirCheck();
		CursorUnitSelect();
		BattleUI->SetTerrain(GetTerrain(MainCursor->WorldPos));
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
		MainCursor->SetSoundPlay(true);
		return;
	}

	if (true == MainCursor->GetIsMove()) { return; }

	int2 CursorPos = MainCursor->WorldPos;
	float4 MousePos = GameEngineInput::GetMousePosition();
	float4 MouseLocalPos = float4(MousePos.x, 640 - MousePos.y);
	int2 MouseMapPos = int2::Float4ToInt2(MouseLocalPos * 0.015625f) + CameraUnit->GetMapPos();
	if (true == IsMapOut(MouseMapPos))
	{
		return;
	}
	if (1 <= CursorPos.GetDistance(MouseMapPos))
	{
		int2 MovePos = MouseMapPos - CursorPos;
		CameraMove(MovePos.Normalize());
		MainCursor->MoveCursorPosLerp(MovePos.Normalize());
		CursorDirCheck();
		AddArrow(MainCursor->WorldPos);
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

	BattleUI->SetCursorDir(CursorDir);
}

void BattleLevel::UnitSelect()
{
	// Ȯ�ι�ư �Է½ÿ���
	if (GameEngineInput::IsDown("ButtonA") || GameEngineInput::IsUp("LeftClick")) {

		if (true == IsMapOut(MainCursor->WorldPos)) { return; }

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
				GameEngineSound::Play("UnitSelect.wav");
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
			SetTile();
		}
		return;
	}

	// L��ư(A Ű)�� ������ �Ʊ������� �ڵ����� ã���ִ� ���
	if (GameEngineInput::IsDown("ButtonL"))
	{
		if (true == MainCursor->GetIsMove()) { return; }
		GameEngineSound::Play("Cancel.wav");
		if (nullptr == SelectUnit)
		{
			for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
			{
				if (_Unit->GetIsDie()) { continue; }
				if (_Unit->GetIsTurnEnd()) { continue; }

				SelectUnit = _Unit;
				MainCursor->SetCursorPos(SelectUnit->GetMapPos());
				CameraSetPos();
				CursorDirCheck();
				SetUI_UnitData();
				MoveSearch();
				SetTile();
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
						MainCursor->SetCursorPos(SelectUnit->GetMapPos());
						CameraSetPos();
						CursorDirCheck();
						SetUI_UnitData();
						MoveSearch();
						SetTile();
						return;
					}
					for (std::shared_ptr<BattleUnit> _Unit : PlayerUnits)
					{
						if (_Unit->GetIsDie()) { continue; }
						if (_Unit->GetIsTurnEnd()) { continue; }
						if (_Unit->GetUnitCode() == SelectUnit->GetUnitCode()) { continue; }

						SelectUnit = _Unit;
						MainCursor->SetCursorPos(SelectUnit->GetMapPos());
						CameraSetPos();
						CursorDirCheck();
						SetUI_UnitData();
						MoveSearch();
						SetTile();
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
		SetTile();
		return;

	}
	// ������ ������ ������ ǥ���ϴ� ���
	if (GameEngineInput::IsDown("ButtonR") || GameEngineInput::IsDown("MiddleClick"))
	{
		if (nullptr == SelectUnit) { return; }
		GameEngineSound::Play("UnitSelect.wav");
		ChangeState(BattleState::Information);
		return;
	}


	// �ð���
	if (GameEngineInput::IsDown("ButtonX"))
	{
		ChangeState(BattleState::TimeStone);
		return;

	}
}

void BattleLevel::SetUI_UnitData()
{
	BattleUI->SetUnitData(SelectUnit);
}

