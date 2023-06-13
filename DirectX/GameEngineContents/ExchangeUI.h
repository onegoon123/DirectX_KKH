#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Int2.h"
class MapCursor;
class UICursor;
class GameEngineUIRenderer;
class BattleLevel;
class Item;
class BattleUnit;
class ExchangeUI : public GameEngineActor
{
public:
	// constrcuter destructer
	ExchangeUI();
	~ExchangeUI();

	// delete Function
	ExchangeUI(const ExchangeUI& _Other) = delete;
	ExchangeUI(ExchangeUI&& _Other) noexcept = delete;
	ExchangeUI& operator=(const ExchangeUI& _Other) = delete;
	ExchangeUI& operator=(ExchangeUI&& _Other) noexcept = delete;

	void Setting(BattleLevel* _Level, std::shared_ptr<UICursor> _Cursor);
	void On(std::shared_ptr<BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits);
	void Off();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	void TargetSelectStart();
	void TargetSelectUpdate(float _DeltaTime);
	void ExchangeStart();
	void ExchangeUpdate(float _DeltaTime);

	BattleLevel* LevelPtr = nullptr;
	std::function<void(std::shared_ptr<BattleUnit>)> ExchangeFunction;
	std::function<void()> CancelFunction;

	std::shared_ptr<MapCursor> Cursor_Map = nullptr;	// Ŀ��
	std::shared_ptr<UICursor> Cursor_UI = nullptr;	// Ŀ��
	std::shared_ptr<GameEngineUIRenderer> SelectRender = nullptr; // ���ù��
	std::shared_ptr<GameEngineUIRenderer> LeftWindow = nullptr;	// ���â
	std::shared_ptr<GameEngineUIRenderer> RightWindow = nullptr;	// ���â
	std::shared_ptr<GameEngineUIRenderer> LeftPortrait = nullptr;		// �ʻ�ȭ
	std::shared_ptr<GameEngineUIRenderer> RightPortrait = nullptr;		// �ʻ�ȭ
	std::vector<std::shared_ptr<GameEngineUIRenderer>> LeftIcons;
	std::vector<std::shared_ptr<GameEngineUIRenderer>> RightIcons;
	std::vector<std::shared_ptr<class NumberActor>> LeftUses;
	std::vector<std::shared_ptr<class NumberActor>> RightUses;

	std::shared_ptr<BattleUnit> LeftUnit = nullptr;;
	std::shared_ptr<BattleUnit> RightUnit = nullptr;;
	std::list<std::shared_ptr<BattleUnit>> TargetUnits;
	std::list<std::shared_ptr<Item>> LeftItems;
	std::list<std::shared_ptr<Item>> RightItems;
	std::shared_ptr<Item> SelectItem;
	std::shared_ptr<Item> ChangeItem;

	std::list<std::shared_ptr<BattleUnit>>::iterator TargetIter;

	std::shared_ptr<class UIButtonSystem> ButtonSystem;
	std::vector<std::shared_ptr<class GameEngineCollision>> ButtonCols;

	const float4 StartCursorPos = { -432, -4 };
	const float4 LeftSelectPos = { -232, 192 };
	const float4 RightCursorPos = { -232, 192 };
	const float4 RightSelectPos = { -232, 192 };

	float4 CursorPos;
	int2 CurrentCursor = 0;
	float CursorTimer = 0;

	const float PreesTime = 0.2f;
	bool PressOK = false;
	bool IsOnFrame = false;	// UI�� �� �������ΰ�
	bool IsUnitSelect = false;// ���⸦ �����ߴ°�
	bool IsClick = false;

	void SetTarget();
};

