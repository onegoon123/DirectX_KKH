#pragma once

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

enum class BattleClass
{
	Lord,		// �ε�
	BladeLord,	// ���̵� �ε� *
	Cavalier,	// �Ҽȳ���Ʈ
	PegasusKnight,// �䰡���� ����Ʈ
	Archer,		// ����
	Fighter,	// ����
	Warrior,	// ������ *
	Cleric,		// �ý���
	Mage,		// ������
	Nomad,		// �����
	Thief,		// ����
	Assassin,	// ��ؽ� *
	Dancer,		// ����
	Monk,		// �·�
	Knight,		// �Ƹӳ���Ʈ
	General,	// ���ʷ� *
	Brigand,	// ���� (������ ��)
	Soldier,	// ���� (â�� ��)
	Mercenary,	// �뺴 (�˵� ��)
};

// ���� Ŭ����
// ������ ���� ������ �����ϴ� Ŭ����
class Stat
{
private:
	int Level;			// ����
	BattleClass ClassValue;
	MainStat MainStatValue;
	int Movement;				// �̵���
	int Experience = 0;			// ����ġ
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
	void SetStat_BladeLord();
	void SetStat_Sain();
	void SetStat_Kent();
	void SetStat_Florina();
	void SetStat_Wil();
	void SetStat_Dorcas();
	void SetStat_Warrior();
	void SetStat_Serra();
	void SetStat_Erk();
	void SetStat_Rath();
	void SetStat_Matthew();
	void SetStat_Assassin();
	void SetStat_Ninian();
	void SetStat_Lucius();
	void SetStat_Wallace();
	void SetStat_General();
	void SetStat_Brigand();
	void SetStat_Soldier();
	void SetStat_Mercenary();


};
