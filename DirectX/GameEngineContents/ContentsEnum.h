#pragma once

enum class RenderOrder
{
	Map,
	Tile,
	Arrow,
	Player,
	Monster,
	UI,
	UICursor,
};

enum class Faction
{
	None,
	Player,
	Enemy
};

enum class UnitIdentityCode
{
	Lyn,
	BladeLoadLyn,
	Sain,
	SainSword,
	Kent,
	KentSword,
	Florina,
	Wil,
	Dorcas,
	WarriorDorcas,
	Serra,
	Erk,
	Rath,
	Matthew,
	AssassinMatthew,
	Ninian,
	Lucius,
	Wallace,
	GeneralWallace,

	Brigand,
	Soldier,
	Mercenary,
	Archer,
	Knight,
	Mage,
};

enum class ItemCode
{
	None,
	SlimSword,
	IronSword,
	SteelSword,
	Lancereaver,
	Armourslayer,
	KillingSword,
	ManiKatti,

	SlimLance,
	IronLance,
	SteelLance,
	SilverLance,
	KillerLance,
	Axereaver,
	Horseslayer,

	HandAxe,
	IronAxe,
	Swordreaver,
	Hammer,

	ShortBow,
	IronBow,
	Ballista,

	Heal,
	Rescue,

	Fire,
	Flux,
	Lightning,

	DoorKey,
	ChestKey,

	Vulnerary,	// ��ó��
	Elixir,		// ���վ�

	Ring1,
	Ring2,
	Torch,
	GoldCard,
	MasterSeal,
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
