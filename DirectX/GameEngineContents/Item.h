#pragma once
#include <GameEngineCore/GameEngineNameObject.h>
#include "ContentsEnum.h"
enum class ItemType 
{
	None,
	Weapon,	// ����
	Stave,	// ������
	Potion,	// ����
	Key
};

// ���� :
class Item : public GameEngineNameObject
{
public:
	// constrcuter destructer
	Item();
	virtual ~Item();

	static std::shared_ptr<Item> CreateItem(ItemCode _Code);

	ItemType GetItemType()
	{
		return TypeValue;
	}
	ItemCode GetItemCode()
	{
		return Code;
	}
	int GetUses()
	{
		return Uses;
	}
	int GetMaxUses()
	{
		return MaxUses;
	}
	bool Use()
	{
		return 0 == --Uses;
	}
protected:
	ItemCode Code = ItemCode::None;
	ItemType TypeValue = ItemType::None;
	int Uses = 0;		// ������
	int MaxUses = 0;
private:

};

