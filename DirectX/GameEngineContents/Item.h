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
	static Item SaveItemData(std::shared_ptr<Item> _Item);
	static std::list<Item> SaveItemDataList(std::list<std::shared_ptr<Item>> _ItemList);
	static void LoadItemDataList(std::list<std::shared_ptr<Item>>& _ItemList, std::list<Item>& _LoadList);

	Item(const Item& _Other)
	{
		SetName(_Other.GetName());
		IdentityCode = _Other.IdentityCode;
		Code = _Other.Code;
		TypeValue = _Other.TypeValue;
		Uses = _Other.Uses;
		MaxUses = _Other.MaxUses;
	}
	Item operator=(const Item& _Other)
	{
		Item NewItem;
		NewItem.SetName(_Other.GetName());
		NewItem.IdentityCode = _Other.IdentityCode;
		NewItem.Code = _Other.Code;
		NewItem.TypeValue = _Other.TypeValue;
		NewItem.Uses = _Other.Uses;
		NewItem.MaxUses = _Other.MaxUses;
		return NewItem;
	}

	ItemType GetItemType()
	{
		return TypeValue;
	}
	ItemCode GetItemCode()
	{
		return Code;
	}
	int GetItemCodeToInt()
	{
		return static_cast<int>(Code);
	}
	int GetUses()
	{
		return Uses;
	}
	int GetMaxUses()
	{
		return MaxUses;
	}
	// �������� �Ҹ��մϴ�. ��� ������ true�� �����մϴ�
	bool Use()
	{
		return 0 == --Uses;
	}

	static Item GetItemData(ItemCode _Code);

protected:
	int IdentityCode = 0;
	ItemCode Code = ItemCode::None;
	ItemType TypeValue = ItemType::None;
	int Uses = 0;		// ������
	int MaxUses = 0;

};

