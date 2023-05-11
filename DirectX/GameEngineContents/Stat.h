#pragma once
#include "Weapon.h"
#include "ContentsEnum.h"
// ���� ����
// �������� ������ �ɷ�ġ��
struct MainStat
{
	int HP = 0;				// ü��
	int Strength = 0;		// ��
	int Magic = 0;			// ����
	int Dexterity = 0;		// ���
	int Speed = 0;			// �ӵ�
	int Defense = 0;		// ����
	int Resistance = 0;		// ����
	int Luck = 0;			// ���
	int Constitution = 0;	// ü��
};


// ���� Ŭ����
// ������ ���� ������ �����ϴ� Ŭ����
class Stat
{

public:
	Stat();
	~Stat();
	Stat(const Stat& _Other)
	{
		ClassValue = _Other.ClassValue;
		EquipWeapon = _Other.EquipWeapon;
		MainStatValue = _Other.MainStatValue;
		Level = _Other.Level;			// ����
		Movement = _Other.Movement;				// �̵���
		Experience = _Other.Experience;			// ����ġ
		GrowthRates_HP = _Other.GrowthRates_HP;			// ü�� �����
		GrowthRates_Strength = _Other.GrowthRates_Strength;	// ��   �����
		GrowthRates_Magic = _Other.GrowthRates_Magic;		// ���� �����
		GrowthRates_Dexterity = _Other.GrowthRates_Dexterity;	// ��� �����
		GrowthRates_Speed = _Other.GrowthRates_Speed;		// �ӵ� �����
		GrowthRates_Defense = _Other.GrowthRates_Defense;	// ���� �����
		GrowthRates_Resistance = _Other.GrowthRates_Resistance;	// ���� �����
		GrowthRates_Luck = _Other.GrowthRates_Luck;		// ��� �����
	}

	BattleClass ClassValue = BattleClass::Lord;
	std::shared_ptr<Weapon> EquipWeapon = nullptr;		// ����� ����
	MainStat MainStatValue;
	int Level = 0;			// ����
	int Movement = 0;				// �̵���
	int Experience = 0;			// ����ġ
	int GrowthRates_HP = 0;			// ü�� �����
	int GrowthRates_Strength = 0;	// ��   �����
	int GrowthRates_Magic = 0;		// ���� �����
	int GrowthRates_Dexterity = 0;	// ��� �����
	int GrowthRates_Speed = 0;		// �ӵ� �����
	int GrowthRates_Defense = 0;	// ���� �����
	int GrowthRates_Resistance = 0;	// ���� �����
	int GrowthRates_Luck = 0;		// ��� �����


	// ���� ���� ����
	void SetIdentity(int _IdentityCode);
	void SetIdentity(UnitIdentityCode _IdentityCode);
	// ����ġ ���� (������ �� true)
	bool AddExperience(int _Experience);
	// ���� �� (����ġ ���� �� ���� ����, ������ �ɷ�ġ�� ��ȯ)
	MainStat LevelUp();

	int GetAttackPoint() const;
	int GetAttackPoint(BattleClass _TargetClass) const;
	int GetAttackPoint(const class Unit& _Other) const;
	int GetMagicAttackPoint() const;
	int GetHitPoint() const;
	int GetHitPoint(const class Unit& _Other) const;
	int GetCriticalPoint() const;
	int GetCriticalPoint(const class Unit& _Other) const;
	int GetAttackSpeedPoint() const;
	int GetDodgePoint() const;
	int GetCriticalDodgePoint() const;
	bool IsDoubleAttack(const class Unit& _Other) const;


private:
	void SetStat_Lyn();
	void SetStat_Sain();
	void SetStat_Kent();
	void SetStat_Florina();
	void SetStat_Wil();
	void SetStat_Dorcas();
	void SetStat_Serra();
	void SetStat_Erk();
	void SetStat_Rath();
	void SetStat_Matthew();
	void SetStat_Ninian();
	void SetStat_Lucius();
	void SetStat_Wallace();

	void ClassChange_BladeLord();
	void ClassChange_Warrior();
	void ClassChange_Assassin();
	void ClassChange_General();

	void SetStat_Brigand();
	void SetStat_Soldier();
	void SetStat_Mercenary();
	void SetStat_Archer();
	void SetStat_Knight();
	void SetStat_Mage();

};
