#pragma once

#include "Item.h"
#include "ContentsEnum.h"
enum class WeaponType
{
	None,
	Sword,		// ��
	LanceReaver,
	Lance,		// â
	AxeReaver,
	Axe,		// ����
	SwordReaver,
	Bow,		// Ȱ
	AnimaTome,	// �Ӽ�����
	DarkTome,	// �渶��
	LightTome,	// ������
};


// ���� :
class Weapon : public Item
{
	//friend class Stat;
public:
	// constrcuter destructer
	Weapon();
	Weapon(ItemCode _Code);
	~Weapon();

	Weapon(const Weapon& _Other)
	{
		SetName(_Other.GetName());
		Damage = _Other.Damage;
		Hit = _Other.Hit;
		Critical = _Other.Critical;
		Weight = _Other.Weight;
		Range = _Other.Range;
		Uses = _Other.Uses;
		WeaponTypeValue = _Other.WeaponTypeValue;
		ValidArmour = _Other.ValidArmour;
		ValidHorse = _Other.ValidHorse;
		IsReaver = _Other.IsReaver;
	}

	Weapon operator=(const Weapon& _Other)
	{
		return Weapon(_Other);
	}

	static std::shared_ptr<Weapon> CreateWeapon(ItemCode _Code);

	// ������ ���� üũ�ϴ� �Լ� (��ȯ���� 1 : ����, 0 : �Ϲ�, -1 : �Ҹ�)
	static int GetWeaponeTriangle(std::shared_ptr<Weapon> _SubjectWeapon, std::shared_ptr<Weapon> _TargetWeapon);

	// �ش� Ŭ������ �� ���⸦ ��� �����Ѱ�?
	bool IsUseWeapon(BattleClass _Class);

	WeaponType GetWeaponTypeValue()
	{
		return WeaponTypeValue;
	}

	int GetDamage() 
	{
		return Damage;
	}

	int GetHit()
	{
		return Hit;
	}

	int GetCritical()
	{
		return Critical;
	}

	int GetWeight()
	{
		return Weight;
	}

	int GetRange()
	{
		return Range;
	}

	bool GetValidArmour()
	{
		return ValidArmour;
	}

	bool GetValidHorse()
	{
		return ValidHorse;
	}

	bool GetIsReaver()
	{
		return IsReaver;
	}

protected:

private:
	WeaponType WeaponTypeValue = WeaponType::None;

	int Damage = 0;		// ���ݷ�
	int Hit = 0;		// ���߷�
	int Critical = 0;	// ġ��Ÿ
	int Weight = 0;		// ����
	int Range = 0;		// ��Ÿ�
	//int Uses = 0;		// ������

	bool ValidArmour = false;
	bool ValidHorse = false;
	bool IsReaver = false;

	void SetWeapon_SlimSword();
	void SetWeapon_IronSword();
	void SetWeapon_SteelSword();
	void SetWeapon_Lancereaver();
	void SetWeapon_Armourslayer();
	void SetWeapon_KillingSword();
	void SetWeapon_ManiKatti();

	void SetWeapon_SlimLance();
	void SetWeapon_IronLance();
	void SetWeapon_SteelLance();
	void SetWeapon_SilverLance();
	void SetWeapon_KillerLance();
	void SetWeapon_Axereaver();
	void SetWeapon_Horseslayer();

	void SetWeapon_HandAxe();
	void SetWeapon_IronAxe();
	void SetWeapon_Swordreaver();
	void SetWeapon_Hammer();

	void SetWeapon_ShortBow();
	void SetWeapon_IronBow();
	void SetWeapon_Ballista();


	void SetWeapon_Fire();
	void SetWeapon_Flux();
	void SetWeapon_Lightning();


};

