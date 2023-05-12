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
		Return = Return > _Weapon->Range ? Return : _Weapon->Range;
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
	case ItemCode::MasterSeal:
	{
		MsgAssert("���� �������� ���� �������Դϴ�.");
	}
	break;
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
		std::list<std::shared_ptr<Weapon>>::iterator WeaponIter = std::find(Weapons.begin(), Weapons.end(), *_ItemIter);
		Weapons.erase(WeaponIter);
	}
	Items.erase(_ItemIter);
}


void Unit::NewItem(ItemCode _Code)
{
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

}