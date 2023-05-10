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
protected:
	ItemCode Code = ItemCode::None;
	ItemType TypeValue = ItemType::None;

private:

};

