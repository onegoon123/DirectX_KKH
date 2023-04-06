#pragma once
#include <string>

// ���� Ŭ����
// ��Ʋ �� ȭ�鿡 ��Ÿ�� �÷��̾�, ��, ��Ÿ ������Ʈ�� �θ� Ŭ����
class Unit
{
public:
	// constructer destructer
	Unit();
	~Unit();

	// delete Function
	Unit(const Unit& _Other) = delete;
	Unit(Unit&& _Other) = delete;
	Unit& operator=(const Unit& _Other) = delete;
	Unit& operator=(Unit&& _Other) = delete;

protected:

private:
	int IdentityCode = 0;
	std::string UnitName = "";
	//Stat UnitStat;
};

// ���� ����
// �������� ������ �ɷ�ġ��
class MainStat
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

enum class BattleClass
{
	Lord,		// �ε�
	BladeLord,	// ���̵� �ε� *
	Cavalier,	// �Ҽȳ���Ʈ
	Paladin,	// �ȶ�� * 
	PegasusKnight,// �䰡���� ����Ʈ
	Archer,		// ����
	Fighter,	// ����
	Warrior,	// ������ *
	Cleric,		// �ý���
	Bishop,		// ��� *
	Mage,		// ������
	Nomad,		// �����
	Thief,		// ����
	Assassin,	// ��ؽ� *
	Dancer,		// ����
	Monk,		// �·�
	Knight,		// �Ƹӳ���Ʈ
	Brigand,	// ����
	Soldier,	// ����
};

// ���� Ŭ����
// ������ ���� ������ �����ϴ� Ŭ����
class Stat
{
private:
	int Level;			// ����
	BattleClass ClassValue;
	MainStat MainStatValue;
	int Experience;				// ����ġ
	int GrowthRates_HP;			// ü�� �����
	int GrowthRates_Strength;	// ��   �����
	int GrowthRates_Magic;		// ���� �����
	int GrowthRates_Dexterity;	// ��� �����
	int GrowthRates_Speed;		// �ӵ� �����
	int GrowthRates_Defense;	// ���� �����
	int GrowthRates_Resistance;	// ���� �����
	int GrowthRates_Luck;		// ��� �����

public:
	// ���� ���� ����
	void SetIdentity(int _IdentityCode);
	// ����ġ ���� (������ �� true)
	bool AddExperience(int _Experience);
	// ���� �� (����ġ ���� �� ���� ����, ������ �ɷ�ġ�� ��ȯ)
	MainStat LevelUp();


private:
	void SetStat_Lyn();
	void SetStat_Sain();
	void SetStat_Kent();
	void SetStat_Fiora();
	void SetStat_Wil();
	void SetStat_Dorcas();
	void SetStat_Serra();
	void SetStat_Erk();
	void SetStat_Rath();
	void SetStat_Matthew();
	void SetStat_Ninian();
	void SetStat_Lucius();
	void SetStat_Wallace();
};