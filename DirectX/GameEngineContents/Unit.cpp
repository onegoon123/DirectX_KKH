#include "PrecompileHeader.h"
#include "Unit.h"

Unit::Unit()
{
}

Unit::~Unit()
{
}

int Unit::GetRangeStat()
{
	int Return = 0;
	for (std::shared_ptr<Weapon> _Weapon : Weapons)
	{
		Return = Return > _Weapon->GetRange() ? Return : _Weapon->GetRange();
	}
	if (GetClassValue() == BattleClass::Cleric)
	{
		bool Check = false;
		for (std::shared_ptr<Item> _Item : Items)
		{
			if (_Item->GetItemCode() == ItemCode::Heal)
			{
				Check = true;
				break;
			}
		}
		if (Check == true)
		{
			return 1;
		}
	}
	return Return;
}

void Unit::EquipWeapon(std::shared_ptr<Weapon> _Weapon)
{
	std::list<std::shared_ptr<Item>>::iterator ItemIter = std::find(Items.begin(), Items.end(), _Weapon);
	if (ItemIter == Items.end())
	{
		MsgAssert("�����۸���Ʈ�� �ش繫�Ⱑ �������� �ʽ��ϴ�." + std::string(_Weapon->GetName()));
		return;
	}
	std::list<std::shared_ptr<Weapon>>::iterator WeaponIter = std::find(Weapons.begin(), Weapons.end(), _Weapon);
	if (WeaponIter == Weapons.end())
	{
		MsgAssert("���⸮��Ʈ�� �ش繫�Ⱑ �������� �ʽ��ϴ�." + std::string(_Weapon->GetName()));
		return;
	}

	Items.splice(Items.begin(), Items, ItemIter);
	Weapons.splice(Weapons.begin(), Weapons, WeaponIter);

	CurWeapon = _Weapon;
}

void Unit::UseItem(std::list<std::shared_ptr<Item>>::iterator& _ItemIter)
{

	if (Items.end() == _ItemIter)
	{
		MsgAssert("�߸��� Iterator ���Դϴ�.");
	}
	std::shared_ptr<Item> _Item = *_ItemIter;

	switch (_Item->GetItemCode())
	{
	case ItemCode::Vulnerary:
		Recover(10);
		break;
	case ItemCode::Elixir:
		Recover(30);
		break;
	case ItemCode::DoorKey:
	case ItemCode::ChestKey:
	case ItemCode::GoldCard:
	{
		MsgAssert("���� �������� ���� �������Դϴ�.");
	}
	break;
	case ItemCode::MasterSeal:
	default:
		break;
	}

	// �������� ������
	if (true == _Item->Use())
	{
		Items.erase(_ItemIter);
	}
}

void Unit::DropItem(std::list<std::shared_ptr<Item>>::iterator& _ItemIter)
{
	if (Items.end() == _ItemIter)
	{
		MsgAssert("�߸��� Iterator ���Դϴ�.");
	}
	if ((*_ItemIter)->GetItemType() == ItemType::Weapon)
	{
		std::shared_ptr<Weapon> _Weapon = std::dynamic_pointer_cast<Weapon>(*_ItemIter);
		if (true == _Weapon->IsUseWeapon(UnitStat.ClassValue))
		{
			std::list<std::shared_ptr<Weapon>>::iterator WeaponIter = std::find(Weapons.begin(), Weapons.end(), *_ItemIter);
			if (CurWeapon == *WeaponIter)
			{
				CurWeapon = nullptr;
			}
			Weapons.erase(WeaponIter);
			if (0 != Weapons.size())
			{
				CurWeapon = Weapons.front();
			}
		}
	}
	Items.erase(_ItemIter);
}

void Unit::DropItem(std::shared_ptr<Item> _Item)
{
	if (_Item->GetItemType() == ItemType::Weapon)
	{
		std::shared_ptr<Weapon> _Weapon = std::dynamic_pointer_cast<Weapon>(_Item);
		if (true == _Weapon->IsUseWeapon(UnitStat.ClassValue))
		{
			std::list<std::shared_ptr<Weapon>>::iterator WeaponIter = std::find(Weapons.begin(), Weapons.end(), _Item);
			if (CurWeapon == *WeaponIter)
			{
				CurWeapon = nullptr;
			}
			Weapons.erase(WeaponIter);
			if (0 != Weapons.size())
			{
				CurWeapon = Weapons.front();
			}
		}
	}
	std::list<std::shared_ptr<Item>>::iterator ItemIter = std::find(Items.begin(), Items.end(), _Item);
	Items.erase(ItemIter);
}


void Unit::NewItem(ItemCode _Code)
{
	if (Items.size() == 5) { return; }
	std::shared_ptr <Item> NewItem = Item::CreateItem(_Code);
	Items.push_back(NewItem);
	if (NewItem->GetItemType() == ItemType::Weapon)
	{
		std::shared_ptr<Weapon> NewWeapon = std::dynamic_pointer_cast<Weapon>(NewItem);

		if (NewWeapon->IsUseWeapon(UnitStat.ClassValue))
		{
			Weapons.push_back(NewWeapon);
			if (nullptr == CurWeapon)
			{
				EquipWeapon(NewWeapon);
			}
		}

	}
	return;
}

void Unit::AddItem(std::shared_ptr<Item> _Item)
{
	if (Items.size() == 5) { return; }

	Items.push_back(_Item);
	if (_Item->GetItemType() == ItemType::Weapon)
	{
		std::shared_ptr<Weapon> NewWeapon = std::dynamic_pointer_cast<Weapon>(_Item);

		if (NewWeapon->IsUseWeapon(UnitStat.ClassValue))
		{
			Weapons.push_back(NewWeapon);
			if (nullptr == CurWeapon)
			{
				EquipWeapon(NewWeapon);
			}
		}
	}
	return;
}

void Unit::ChangeItem(std::shared_ptr<Item> _Item, int _Index)
{
	std::list<std::shared_ptr<Item>>::iterator ItemIter = Items.begin();
	std::advance(ItemIter, _Index);

	if ((*ItemIter)->GetItemType() == ItemType::Weapon)
	{
		std::shared_ptr<Weapon> _Weapon = std::dynamic_pointer_cast<Weapon>(*ItemIter);
		if (true == _Weapon->IsUseWeapon(UnitStat.ClassValue))
		{
			std::list<std::shared_ptr<Weapon>>::iterator WeaponIter = std::find(Weapons.begin(), Weapons.end(), _Weapon);
			if (CurWeapon == *WeaponIter)
			{
				CurWeapon = nullptr;
			}
			Weapons.erase(WeaponIter);
			if (0 != Weapons.size())
			{
				CurWeapon = Weapons.front();
			}
		}
	}

	*ItemIter = _Item;
	if (_Item->GetItemType() == ItemType::Weapon)
	{
		std::shared_ptr<Weapon> NewWeapon = std::dynamic_pointer_cast<Weapon>(_Item);

		if (NewWeapon->IsUseWeapon(UnitStat.ClassValue))
		{
			Weapons.push_back(NewWeapon);
			if (nullptr == CurWeapon)
			{
				EquipWeapon(NewWeapon);
			}
		}
	}
}

void Unit::LoadItemData(std::list<Item>& _Data)
{
	Items.clear();
	Weapons.clear();
	CurWeapon = nullptr;

	for (Item _Item : _Data)
	{

		std::shared_ptr<Item> NewItem = Item::CreateItem(_Item.GetItemCode());
		NewItem->operator=(_Item);
		Items.push_back(NewItem);
		if (NewItem->GetItemType() == ItemType::Weapon)
		{
			std::shared_ptr<Weapon> NewWeapon = std::dynamic_pointer_cast<Weapon>(NewItem);
			if (NewWeapon->IsUseWeapon(UnitStat.ClassValue))
			{
				Weapons.push_back(NewWeapon);
				if (nullptr == CurWeapon)
				{
					EquipWeapon(NewWeapon);
				}
			}
		}

	}
	if (Weapons.size() == 0)
	{
		int a = 0;
	}
}