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
	Items.erase(_ItemIter);
	if ((*_ItemIter)->GetItemType() == ItemType::Weapon)
	{
		std::list<std::shared_ptr<Weapon>>::iterator WeaponIter = std::find(Weapons.begin(), Weapons.end(), *_ItemIter);
		Weapons.erase(WeaponIter);
	}
}


void Unit::NewItem(ItemCode _Code)
{
	if (_Code <= ItemCode::Lightning)
	{
		// ���� ����
		std::shared_ptr<Weapon> NewWeapon = Weapon::CreateWeapon(_Code);
		Items.push_back(NewWeapon);	// ������ ����Ʈ�� �߰�
		// ��밡���� ������
		if (NewWeapon->IsUseWeapon(UnitStat.ClassValue))
		{
			// ���� ����Ʈ�� �߰�
			Weapons.push_back(NewWeapon);
			// ������� ���Ⱑ ���ٸ�
			if (nullptr == CurWeapon)
			{
				// ���� ���
				CurWeapon = NewWeapon;
				std::list<std::shared_ptr<Item>>::iterator Iter = std::find(Items.begin(), Items.end(), CurWeapon);
				Items.splice(Items.begin(), Items, Iter);
			}
		}
		return;
	}
	

	Items.push_back(Item::CreateItem(_Code));

}

