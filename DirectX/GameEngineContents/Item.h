#pragma once

enum class ItemType
{
	None,
	Weapon,
	Potion,
	Key
};

// ���� :
class Item
{
public:
	// constrcuter destructer
	Item();
	~Item();

protected:

	ItemType TypeValue = ItemType::None;

private:

};

