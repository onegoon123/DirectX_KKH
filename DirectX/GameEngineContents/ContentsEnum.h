#pragma once

enum class RenderOrder
{
	Map,	// �� (���)
	Tile,	// Ÿ�� (�̵�, ���� ����)
	Unit,	// ����
	Arrow,	// ȭ��ǥ (�̵� ����)
	SelectUnit, // ���õ� ����
	MapCursor,
	Effect, // ȿ��

	UIBackground,
	UI,		// UI
	UIText,		// UI
	UICursor,	// UI�� ǥ�õǴ� �̹���

	UI2,
	UI3,
	UI4,
	UI5,
	UI6,
	UI7,
	UI8,
	UI9,
	Fade,
};
enum class CollisionOrder
{
	Cursor,
	Button
};
enum class UIDir
{
	None,
	LeftUp,
	LeftDown,
	RightUp,
	RightDown
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
	BladeLordLyn,
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
	GeneralWallaceAxe,

	Brigand,
	Soldier,
	Mercenary,
	Archer,
	Knight,
	Mage,

	Batta,
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


enum class Terrain
{
	Plain,	//����
	Floor,	//�ٴ�
	Road,	//��
	None,	//�̵��Ұ�����
	Forest,	//��
	Cliff,	//����
	Mountain,	//��
	Peak,		//���� ��
	Door,		//�� �̵��Ұ�
	Gate,		//�� ����Ʈ �̵�����
	Ruins,		//����
	House,		//�ΰ�
	Shop,		//���� (������)
	Sea,		//�ٴ�
	Lake,		//ȣ��
	River,		//��
	Bridge,		//�ٸ�
	Wall,		//��
	Fort,		//���
	Pillar,		//���
	Throne,		//����
};