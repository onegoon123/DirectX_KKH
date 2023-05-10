#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"
class MapCursor;
class UICursor;
class SpriteRenderer;
class BattleLevel;
class Weapon;
class BattleUnit;
class Item;
class ItemUI : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemUI();
	~ItemUI();

	// delete Function
	ItemUI(const ItemUI& _Other) = delete;
	ItemUI(ItemUI&& _Other) noexcept = delete;
	ItemUI& operator=(const ItemUI& _Other) = delete;
	ItemUI& operator=(ItemUI&& _Other) noexcept = delete;

	void Setting(BattleLevel* _Level);
	void On(std::shared_ptr<BattleUnit> _SelectUnit);
	void Off();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	void ItemSelectUpdate(float _DeltaTime);
	void ItemSelect();
	void ItemUseUpdate(float _DeltaTime);

	void Equipment();
	void Drop();
	void Use();

	BattleLevel* LevelPtr = nullptr;
	std::function<void(ItemCode)> UseFunction;
	std::function<void()> CancelFunction;
	std::vector<std::function<void()>> UseFunctions;

	std::shared_ptr<UICursor> UICursor = nullptr;	// Ŀ��
	std::shared_ptr<SpriteRenderer> SelectRender = nullptr; // ���ù��
	std::shared_ptr<SpriteRenderer> WindowRender = nullptr;	// ���â
	std::shared_ptr<SpriteRenderer> InfoRender = nullptr;	// ������ ����
	std::shared_ptr<SpriteRenderer> Portrait = nullptr;		// �ʻ�ȭ
	std::shared_ptr<SpriteRenderer> ItemUseWindow = nullptr;	// ������ ��� â
	std::shared_ptr<SpriteRenderer> ItemUseSelect = nullptr;	// ������ ��� ����
	std::list<std::shared_ptr<SpriteRenderer>> Icons;
	std::list<std::shared_ptr<Item>> Items;
	std::shared_ptr<Item> SelectItem;
	std::shared_ptr<BattleUnit> SelectUnit = nullptr;;

	const float4 StartCursorPos = { -432, 192 };
	const float4 StartSelectPos = { -232, 192 };
	float4 StartUseCursorPos = {0,0};
	float4 StartUseSelectPos = {0,0};

	float4 UseCursorPos;
	float4 CursorPos;
	size_t CurrentCursor = 0;
	size_t CurrentUseCursor = 0;
	float CursorTimer = 0;

	const float PreesTime = 0.2f;
	bool PressOK = false;
	bool IsOnFrame = false;	// UI�� �� �������ΰ�
	bool IsItemSelect = false;// �������� �����ߴ°�
};

