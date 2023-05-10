#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MapCursor;
class UICursor;
class SpriteRenderer;
class BattleLevel;
class Weapon;
class BattleUnit;
class AttackUI : public GameEngineActor
{
public:
	// constrcuter destructer
	AttackUI();
	~AttackUI();

	// delete Function
	AttackUI(const AttackUI& _Other) = delete;
	AttackUI(AttackUI&& _Other) noexcept = delete;
	AttackUI& operator=(const AttackUI& _Other) = delete;
	AttackUI& operator=(AttackUI&& _Other) noexcept = delete;

	void Setting(BattleLevel* _Level);
	void On(std::shared_ptr<BattleUnit> _SelectUnit, std::list<std::shared_ptr<BattleUnit>>& _TargetUnits);
	//void On();
	void Off();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	void WeaponSelectStart();
	void WeaponSelectUpdate(float _DeltaTime);
	void WeaponSelectEnd();
	void TargetSelectStart();
	void TargetSelectUpdate(float _DeltaTime);
	void TargetSelectEnd();
	void SetTarget();
	BattleLevel* LevelPtr = nullptr;
	std::function<void(std::shared_ptr<BattleUnit>)> AttackFunction;
	std::function<void()> CancelFunction;

	std::shared_ptr<MapCursor> Cursor = nullptr;	// Ŀ��
	std::shared_ptr<UICursor> UICursor = nullptr;	// Ŀ��
	std::shared_ptr<SpriteRenderer> SelectRender = nullptr; // ���ù��
	std::shared_ptr<SpriteRenderer> WindowRender = nullptr;	// ���â
	std::shared_ptr<SpriteRenderer> InfoRender = nullptr;	// ���� ����
	std::shared_ptr<SpriteRenderer> Portrait = nullptr;		// �ʻ�ȭ
	std::shared_ptr<SpriteRenderer> BattleEx = nullptr;		// ���� ����
	std::list<std::shared_ptr<SpriteRenderer>> WeaponeIcon;


	std::shared_ptr<BattleUnit> SelectUnit = nullptr;;
	std::list<std::shared_ptr<BattleUnit>> TargetUnits;
	std::list<std::shared_ptr<Weapon>> Weapons;
	std::shared_ptr<Weapon> SelectWeapon;
	std::list<std::shared_ptr<BattleUnit>> Targets;
	std::list<std::shared_ptr<BattleUnit>>::iterator TargetIter;
	std::shared_ptr<BattleUnit> TargetUnit;

	const float4 StartCursorPos = { -432, 192 };
	const float4 StartSelectPos = { -232, 192 };
	float4 CursorPos;
	size_t CurrentCursor = 0;
	float CursorTimer = 0;

	const float PreesTime = 0.2f;
	bool PressOK = false;
	bool IsOnFrame = false;	// UI�� �� �������ΰ�
	bool IsWeaponSelect = false;// ���⸦ �����ߴ°�
};

