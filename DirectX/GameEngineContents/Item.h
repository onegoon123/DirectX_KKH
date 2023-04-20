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

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

protected:

	ItemType TypeValue = ItemType::None;

private:

};

