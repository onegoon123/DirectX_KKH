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

	// delete Function
	Weapon(const Weapon& _Other) = delete;
	Weapon(Weapon&& _Other) noexcept = delete;
	Weapon& operator=(const Weapon& _Other) = delete;
	Weapon& operator=(Weapon&& _Other) noexcept = delete;

protected:

private:
	int Damage = 0;		// ���ݷ�
	int Hit = 0;		// ���߷�
	int Critical = 0;	// ġ��Ÿ
	int Weight = 0;		// ����
	int Range = 0;		// ��Ÿ�
	int Uses = 0;		// ������
};

