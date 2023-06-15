#pragma once
#include "Weapon.h"
#include "ContentsEnum.h"
// ���� ����
// �������� ������ �ɷ�ġ��
struct MainStat
{
	union
	{
		struct
		{
			int HP;				// ü��
			int Strength;		// ��
			int Magic;			// ����
			int Dexterity;		// ���
			int Speed;			// �ӵ�
			int Defense;		// ����
			int Resistance;		// ����
			int Luck;			// ���
			int Constitution;	// ü��
		};
		int Array[9];
	};

	MainStat()
	{
		Array[0] = 0;
		HP = 0;
		Strength = 0;
		Magic = 0;
		Dexterity = 0;
		Speed = 0;
		Defense = 0;
		Resistance = 0;
		Luck = 0;
		Constitution = 0;
	}
	MainStat operator-(MainStat& _Other)
	{
		MainStat ReturnStat;
		ReturnStat.HP = HP - _Other.HP;
		ReturnStat.Strength = Strength - _Other.Strength;
		ReturnStat.Magic = Magic - _Other.Magic;
		ReturnStat.Dexterity = Dexterity - _Other.Dexterity;
		ReturnStat.Speed = Speed - _Other.Speed;
		ReturnStat.Defense = Defense - _Other.Defense;
		ReturnStat.Resistance = Resistance - _Other.Resistance;
		ReturnStat.Luck = Luck - _Other.Luck;
		ReturnStat.Constitution = Constitution - _Other.Constitution;
		return ReturnStat;
	}
	void operator+=(MainStat& _Other)
	{
		HP += _Other.HP;
		Strength += _Other.Strength;
		Magic += _Other.Magic;
		Dexterity +=  _Other.Dexterity;
		Speed += _Other.Speed;
		Defense += _Other.Defense;
		Resistance += _Other.Resistance;
		Luck += _Other.Luck;
		Constitution +=  _Other.Constitution;
	}

public:
	int GetAttackStat(WeaponType _Value) const;

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
		MainStatValue = _Other.MainStatValue;
		MaximumStat = _Other.MaximumStat;
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
	MainStat MainStatValue;
	MainStat MaximumStat;

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



	MainStat ClassChange_BladeLord();
	MainStat ClassChange_Warrior();
	MainStat ClassChange_Assassin();
	MainStat ClassChange_General();

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


	void SetStat_Brigand();
	void SetStat_Soldier();
	void SetStat_Mercenary();
	void SetStat_Archer();
	void SetStat_Knight();
	void SetStat_Mage();

	void SetStat_Batta();
	void SetStat_Zugu();
	void SetStat_Glass();
	void SetStat_Migal();
	void SetStat_Carjiga();

};
