#pragma once

#include "Item.h"

enum class WeaponType
{
	Sword,		// ��
	Lance,		// â
	Axe,		// ����
	Bow,		// Ȱ
	Stave,		// ������
	AnimaTome,	// �Ӽ�����
	LightTome,	// ������
};

// ���� :
class Weapon : public Item
{
	friend class Stat;
public:
	// constrcuter destructer
	Weapon();
	~Weapon();

	Weapon(const Weapon& _Other)
	{
		Damage = _Other.Damage;
		Hit = _Other.Hit;
		Critical = _Other.Critical;
		Weight = _Other.Weight;
		Range = _Other.Range;
		Uses = _Other.Uses;
	}

	int Damage = 0;		// ���ݷ�
	int Hit = 0;		// ���߷�
	int Critical = 0;	// ġ��Ÿ
	int Weight = 0;		// ����
	int Range = 0;		// ��Ÿ�
	int Uses = 0;		// ������
protected:

private:
};

