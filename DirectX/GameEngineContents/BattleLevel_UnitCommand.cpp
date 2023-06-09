#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include "BattleUnit.h"
#include "UnitCommand.h"
#include "Item.h"
#include "BattleLevelUI.h"
#include "MapCursor.h"
#include "BattleAnimationLevel.h"
#include "TileRender.h"
void BattleLevel::UnitCommand_Item()
{
	Tiles->Clear();
	BattleUI->ItemOn(SelectUnit);
}

void BattleLevel::UnitCommand_Wait()
{
	UnitCommand::Wait(SelectUnit);
	SelectUnit->SetIsTurnEnd(true);
	ChangeState(BattleState::Select);
}

void BattleLevel::UnitCommand_Attack()
{
	BattleUI->AttackOn(SelectUnit, AttackableUnits);
}

void BattleLevel::UnitCommand_Heal()
{
	BattleUI->HealOn(SelectUnit, CloseUnits);
}

void BattleLevel::UnitCommand_Dance()
{
	BattleUI->DanceOn(CloseUnits);
}

void BattleLevel::UnitCommand_Exchange()
{
	Tiles->Clear();
	BattleUI->ExchangeOn(SelectUnit, CloseUnits);
}
void BattleLevel::UnitCommand_ExchangeEnd(std::shared_ptr<BattleUnit> _Target)
{
	UnitCommand::Wait(SelectUnit);
	MainCursor->SetMapPos(SelectUnit->GetMapPos());
	SelectUnit->SetIsTurnEnd(true);
	ChangeState(BattleState::Select);
}
void BattleLevel::UnitCommand_Cancel()
{
	//BattleUI->AllOff();
	SelectUnit->SetMapPos(BeforePos);
	ChangeState(BattleState::Move);
}

void BattleLevel::UnitCommand_CommandCancel()
{
	if (SelectUnit->GetUnitData().GetClassValue() == BattleClass::Cleric || SelectUnit->GetUnitData().GetClassValue() == BattleClass::Dancer)
	{
		Tiles->SetTileHeal(IsAttack);
	}
	else
	{
		Tiles->SetTileAttack(IsAttack);
	}
	BattleUI->UnitCommandOn();
}

void BattleLevel::UnitCommand_TargetAttack(std::shared_ptr<BattleUnit> _Target)
{
	TargetUnit = _Target;
	ChangeState(BattleState::Battle);
	return;
}
void BattleLevel::UnitCommand_TargetHeal(std::shared_ptr<BattleUnit> _Target, std::list<std::shared_ptr<Item>>::iterator& _ItemIter)
{
	TargetUnit = _Target;
	UseItem = _ItemIter;
	ChangeState(BattleState::Heal);
	return;
}
void BattleLevel::UnitCommand_TargetDance(std::shared_ptr<BattleUnit> _Target)
{
	BattleAnimationLevel::SetDance(SelectUnit, _Target, GetName());
	UnitCommand::Dance(SelectUnit, _Target);
	SelectUnit->SetIsTurnEnd(true);
	_Target->SetIsTurnEnd(false);
	MainCursor->Off();
	ChangeState(BattleState::ClassChange);
}
void BattleLevel::UnitCommand_ItemUse(std::list<std::shared_ptr<Item>>::iterator& _ItemIter)
{
	ItemCode _ItemCode = (*_ItemIter)->GetItemCode();
	UseItem = _ItemIter;
	switch (_ItemCode)
	{
	case ItemCode::Vulnerary:
	case ItemCode::Elixir:
		ChangeState(BattleState::Potion);
		break;
	case ItemCode::MasterSeal:
	{
		UnitIdentityCode Before = SelectUnit->GetUnitData().GetIdentityCode();
		UnitIdentityCode After;
		BattleClass AfterClass;
		switch (Before)
		{
		case UnitIdentityCode::Lyn:
			After = UnitIdentityCode::BladeLordLyn;
			AfterClass = BattleClass::BladeLord;
			break;
		case UnitIdentityCode::Dorcas:
			After = UnitIdentityCode::WarriorDorcas;
			AfterClass = BattleClass::Warrior;
			break;
		case UnitIdentityCode::Matthew:
			After = UnitIdentityCode::AssassinMatthew;
			AfterClass = BattleClass::Assassin;
			break;
		case UnitIdentityCode::Wallace:
			After = UnitIdentityCode::GeneralWallace;
			AfterClass = BattleClass::General;
			break;
		default:
			return;
		}
		BattleAnimationLevel::SetClassChange(SelectUnit, AfterClass, GetName());
		UnitCommand::ClassChange(SelectUnit, AfterClass, UseItem);
		ChangeState(BattleState::ClassChange);
		break;
	}
	default:
		break;
	}
}

void BattleLevel::UnitCommand_Conquer()
{
	ChangeState(BattleState::Clear);
}

void BattleLevel::UnitCommand_Store()
{
	ChangeState(BattleState::Store);
}

void BattleLevel::UnitCommand_StoreEnd(std::list<std::shared_ptr<class Item>> _BeforeItems, int _Money)
{
	UnitCommand::StoreUse(SelectUnit, _BeforeItems, _Money);
	ChangeState(BattleState::Select);
}
