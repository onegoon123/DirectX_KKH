#include "PrecompileHeader.h"
#include "Weapon.h"
Weapon::Weapon() 
{
	TypeValue = ItemType::Weapon;
}

Weapon::Weapon(ItemCode _Code)
{
	TypeValue = ItemType::Weapon;
	switch (_Code)
	{
	case ItemCode::SlimSword:
		SetWeapon_SlimSword();
		break;
	case ItemCode::IronSword:
		SetWeapon_IronSword();
		break;
	case ItemCode::SteelSword:
		SetWeapon_SteelSword();
		break;
	case ItemCode::Lancereaver:
		SetWeapon_Lancereaver();
		break;
	case ItemCode::Armourslayer:
		SetWeapon_Armourslayer();
		break;
	case ItemCode::KillingSword:
		SetWeapon_KillingSword();
		break;
	case ItemCode::ManiKatti:
		SetWeapon_ManiKatti();
		break;
	case ItemCode::SlimLance:
		SetWeapon_SlimLance();
		break;
	case ItemCode::IronLance:
		SetWeapon_IronLance();
		break;
	case ItemCode::SteelLance:
		SetWeapon_SteelLance();
		break;
	case ItemCode::SilverLance:
		SetWeapon_SilverLance();
		break;
	case ItemCode::KillerLance:
		SetWeapon_KillerLance();
		break;
	case ItemCode::Axereaver:
		SetWeapon_Axereaver();
		break;
	case ItemCode::Horseslayer:
		SetWeapon_Horseslayer();
		break;
	case ItemCode::HandAxe:
		SetWeapon_HandAxe();
		break;
	case ItemCode::IronAxe:
		SetWeapon_IronAxe();
		break;
	case ItemCode::Swordreaver:
		SetWeapon_Swordreaver();
		break;
	case ItemCode::Hammer:
		SetWeapon_Hammer();
		break;
	case ItemCode::ShortBow:
		SetWeapon_ShortBow();
		break;
	case ItemCode::IronBow:
		SetWeapon_IronBow();
		break;
	case ItemCode::Ballista:
		SetWeapon_Ballista();
		break;
	case ItemCode::Fire:
		SetWeapon_Fire();
		break;
	case ItemCode::Flux:
		SetWeapon_Flux();
		break;
	case ItemCode::Lightning:
		SetWeapon_Lightning();
		break;
	case ItemCode::Heal:
	case ItemCode::Rescue:
	case ItemCode::DoorKey:
	case ItemCode::ChestKey:
	case ItemCode::Vulnerary:
	case ItemCode::Elixir:
	case ItemCode::Ring1:
	case ItemCode::Ring2:
	case ItemCode::Torch:
	case ItemCode::GoldCard:
	case ItemCode::MasterSeal:
	{
		MsgAssert("�߸��� �ڵ��� ���⸦ �����Ϸ� �߽��ϴ�.");
		return;
	}
	default:
		break;
	}
}

Weapon::~Weapon() 
{
}

std::shared_ptr<Weapon> Weapon::CreateWeapon(ItemCode _Code)
{
	return std::make_shared<Weapon>(_Code);
}

void Weapon::SetWeapon_SlimSword()
{
	WeaponTypeValue = WeaponType::Sword;
	SetName("������ ��");
	Damage = 3;
	Hit = 100;
	Critical = 5;
	Weight = 2;
	Range = 1;
	Uses = 30;
}

void Weapon::SetWeapon_IronSword()
{
	WeaponTypeValue = WeaponType::Sword;
	SetName("ö�� ��");
	Damage = 5;
	Hit = 90;
	Critical = 0;
	Weight = 5;
	Range = 1;
	Uses = 46;
}

void Weapon::SetWeapon_SteelSword()
{
	WeaponTypeValue = WeaponType::Sword;
	SetName("��ö�� ��");
	Damage = 10;
	Hit = 75;
	Critical = 0;
	Weight = 8;
	Range = 1;
	Uses = 30;
}

void Weapon::SetWeapon_Lancereaver()
{
	WeaponTypeValue = WeaponType::Sword;
	SetName("���� ������");
	IsReaver = true;
	Damage = 9;
	Hit = 75;
	Critical = 5;
	Weight = 9;
	Range = 1;
	Uses = 15;
}

void Weapon::SetWeapon_Armourslayer()
{
	WeaponTypeValue = WeaponType::Sword;
	SetName("�Ƹ� ų��");
	ValidArmour = true;
	Damage = 8;
	Hit = 80;
	Critical = 0;
	Weight = 11;
	Range = 1;
	Uses = 18;
}

void Weapon::SetWeapon_KillingSword()
{
	WeaponTypeValue = WeaponType::Sword;
	SetName("ų�ҵ�");
	Damage = 9;
	Hit = 75;
	Critical = 30;
	Weight = 7;
	Range = 1;
	Uses = 20;
}

void Weapon::SetWeapon_ManiKatti()
{
	WeaponTypeValue = WeaponType::Sword;
	SetName("���� īƼ");
	Damage = 8;
	Hit = 80;
	Critical = 20;
	Weight = 3;
	Range = 1;
	Uses = 45;
}

void Weapon::SetWeapon_SlimLance()
{
	WeaponTypeValue = WeaponType::Lance;
	SetName("������ â");
	Damage = 4;
	Hit = 85;
	Critical = 5;
	Weight = 4;
	Range = 1;
	Uses = 30;
}

void Weapon::SetWeapon_IronLance()
{
	WeaponTypeValue = WeaponType::Lance;
	SetName("ö�� â");
	Damage = 7;
	Hit = 80;
	Critical = 0;
	Weight = 8;
	Range = 1;
	Uses = 45;
}

void Weapon::SetWeapon_SteelLance()
{
	WeaponTypeValue = WeaponType::Lance;
	SetName("��ö�� â");
	Damage = 10;
	Hit = 70;
	Critical = 0;
	Weight = 13;
	Range = 1;
	Uses = 30;
}

void Weapon::SetWeapon_SilverLance()
{
	WeaponTypeValue = WeaponType::Lance;
	SetName("���� â");
	Damage = 14;
	Hit = 75;
	Critical = 0;
	Weight = 10;
	Range = 1;
	Uses = 20;
}

void Weapon::SetWeapon_KillerLance()
{
	WeaponTypeValue = WeaponType::Lance;
	SetName("ų������");
	Damage = 10;
	Hit = 70;
	Critical = 30;
	Weight = 9;
	Range = 1;
	Uses = 20;
}

void Weapon::SetWeapon_Axereaver()
{
	WeaponTypeValue = WeaponType::Lance;
	SetName("���� ������");
	IsReaver = true;
	Damage = 10;
	Hit = 70;
	Critical = 5;
	Weight = 11;
	Range = 1;
	Uses = 15;
}

void Weapon::SetWeapon_Horseslayer()
{
	WeaponTypeValue = WeaponType::Lance;
	SetName("ȣ�� ų��");
	ValidHorse = true;
	Damage = 7;
	Hit = 70;
	Critical = 0;
	Weight = 13;
	Range = 1;
	Uses = 16;
}

void Weapon::SetWeapon_HandAxe()
{
	WeaponTypeValue = WeaponType::Axe;
	SetName("��ô ����");
	Damage = 7;
	Hit = 60;
	Critical = 0;
	Weight = 12;
	Range = 2;
	Uses = 20;
}

void Weapon::SetWeapon_IronAxe()
{
	WeaponTypeValue = WeaponType::Axe;
	SetName("ö�� ����");
	Damage = 8;
	Hit = 75;
	Critical = 0;
	Weight = 10;
	Range = 1;
	Uses = 45;
}

void Weapon::SetWeapon_Swordreaver()
{
	WeaponTypeValue = WeaponType::Axe;
	SetName("�ҵ� ������");
	IsReaver = true;
	Damage = 11;
	Hit = 65;
	Critical = 5;
	Weight = 11;
	Range = 1;
	Uses = 15;
}

void Weapon::SetWeapon_Hammer()
{
	WeaponTypeValue = WeaponType::Axe;
	SetName("�ظ�");
	ValidArmour = true;
	Damage = 10;
	Hit = 55;
	Critical = 0;
	Weight = 15;
	Range = 1;
	Uses = 20;
}

void Weapon::SetWeapon_ShortBow()
{
	WeaponTypeValue = WeaponType::Bow;
	SetName("�ܱ�");
	Damage = 5;
	Hit = 85;
	Critical = 0;
	Weight = 3;
	Range = 2;
	Uses = 22;
}

void Weapon::SetWeapon_IronBow()
{
	WeaponTypeValue = WeaponType::Bow;
	SetName("ö�� Ȱ");
	Damage = 6;
	Hit = 85;
	Critical = 0;
	Weight = 5;
	Range = 2;
	Uses = 45;
}

void Weapon::SetWeapon_Ballista()
{
	WeaponTypeValue = WeaponType::Bow;
	SetName("�߸���Ÿ");
	Damage = 8;
	Hit = 70;
	Critical = 0;
	Weight = 20;
	Range = 8;
	Uses = 5;
}

void Weapon::SetWeapon_Fire()
{
	WeaponTypeValue = WeaponType::AnimaTome;
	SetName("���̾�");
	Damage = 5;
	Hit = 90;
	Critical = 0;
	Weight = 4;
	Range = 2;
	Uses = 40;
}

void Weapon::SetWeapon_Flux()
{
	WeaponTypeValue = WeaponType::DarkTome;
	SetName("��");
	Damage = 7;
	Hit = 80;
	Critical = 0;
	Weight = 8;
	Range = 2;
	Uses = 45;
}

void Weapon::SetWeapon_Lightning()
{
	WeaponTypeValue = WeaponType::LightTome;
	SetName("����Ʈ��");
	Damage = 4;
	Hit = 95;
	Critical = 0;
	Weight = 6;
	Range = 2;
	Uses = 35;
}
