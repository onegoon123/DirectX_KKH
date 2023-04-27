#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"
#include "Int2.h"

class BattleMap;
class MapCursor;
class BattleUnit;
class TileRender;
class ArrowRender;
class SelectUI;
class UnitCommandUI;
class BattleLevel : public GameEngineLevel
{
public:
	// constructer destructer
	BattleLevel();
	~BattleLevel();

	// delete Function
	BattleLevel(const BattleLevel& _Other) = delete;
	BattleLevel(BattleLevel&& _Other) = delete;
	BattleLevel& operator=(const BattleLevel& _Other) = delete;
	BattleLevel& operator=(BattleLevel&& _Other) = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	// State
	enum class BattleState
	{
		None,
		PlayerPhase,	// �÷��̾� �� ����
		Select,		// Ŀ���� ������ �����ϴ� �ܰ�
		Move,		// ������ �������� �̵��� ��ġ�� ���ϴ� �ܰ�
		MoveWait,	// ������ �̵��ϴ� �ð��� ��ٸ��� �ܰ�
		UnitCommand,	// ������ �ൿ�� ���ϴ� �ܰ�
		FieldCommand,	// Ŀ���� ���� Ŭ���ϸ� ������ �ൿ���� ���ϴ� �ܰ�
		Battle,		// ���ֳ��� ������ �ϴ� �ܰ�

		EnemyPhase,	// ���� ���� ����
		EnemySelect,	// �� ����
		EnemyMove,			// ���� �̵�
		EnemyBattle,		// ���� ����

		GameOver,			// ���� ����
	};
	BattleState CurState = BattleState::None;	// ������Ʈ
	void (BattleLevel::* StateUpdate)(float) = nullptr;		// ������Ʈ ������Ʈ
	void (BattleLevel::* StateEnd)() = nullptr;		// ������Ʈ ����

	// Actor
	std::shared_ptr<BattleMap> MainMap = nullptr;
	std::shared_ptr <MapCursor> MainCursor = nullptr;
	std::list<std::shared_ptr <BattleUnit>> PlayerUnits = std::list< std::shared_ptr <BattleUnit>>();
	std::list< std::shared_ptr <BattleUnit>> EnemyUnits = std::list< std::shared_ptr <BattleUnit>>();
	std::shared_ptr <BattleUnit> SelectUnit = nullptr;
	std::shared_ptr <BattleUnit> TargetUnit = nullptr;

	// Map ����
	std::shared_ptr <TileRender> Tiles = nullptr;
	std::shared_ptr <ArrowRender> Arrows = nullptr;
	std::vector<int2> ArrowPos = std::vector<int2>();
	std::vector<std::vector<bool>> IsMove = std::vector<std::vector<bool>>();
	std::vector<std::vector<bool>> IsAttack = std::vector<std::vector<bool>>();
	bool IsArrowOut = false;

	// UI
	std::shared_ptr <SelectUI> UI_Select = nullptr;
	std::shared_ptr <UnitCommandUI> UI_UnitCommand = nullptr;

	const float MoveSpeed = 10;
	float MoveTimer = 0;
	int MoveIndex = 0;
	float4 MoveStartPos = float4::Zero;
	float4 MoveEndPos = float4::Zero;

	int2 BeforePos = int2::Zero;

#pragma region FSM
	void ChangeState(BattleState _State);

	void PlayerPhaseStart();
	void PlayerPhaseUpdate(float _DeltaTime);
	void PlayerPhaseEnd();

	void SelectStart();
	void SelectUpdate(float _DeltaTime);
	void SelectEnd();

	void MoveStart();
	void MoveUpdate(float _DeltaTime);
	void MoveEnd();

	void MoveWaitStart();
	void MoveWaitUpdate(float _DeltaTime);
	void MoveWaitEnd();

	void UnitCommandStart();
	void UnitCommandUpdate(float _DeltaTime);
	void UnitCommandEnd();

	void FieldCommandStart();
	void FieldCommandUpdate(float _DeltaTime);
	void FieldCommandEnd();

	void BattleStart();
	void BattleUpdate(float _DeltaTime);
	void BattleEnd();

	void EnemyPhaseStart();
	void EnemyPhaseUpdate(float _DeltaTime);
	void EnemyPhaseEnd();

	void EnemySelectStart();
	void EnemySelectUpdate(float _DeltaTime);
	void EnemySelectEnd();

	void EnemyMoveStart();
	void EnemyMoveUpdate(float _DeltaTime);
	void EnemyMoveEnd();

	void EnemyBattleStart();
	void EnemyBattleUpdate(float _DeltaTime);
	void EnemyBattleEnd();

	void GameOverStart();
	void GameOverUpdate(float _DeltaTime);
	void GameOverEnd();

#pragma endregion


#pragma region Map

	// ������ ���ý� �̵������� ������ ǥ���ϴ� ��� (Ž�� ������ ����)
	void MoveSearch();
	// ���ݰ��� ������ ǥ�� (MoveSearch ����� �ڵ����� ����)
	void AttackSearch();
	void AttackSearchBow();

	void MoveSearchForEnemy();
	void AttackSearchForEnemy();
	// ������ �̵���Ű�� ���
	void UnitMove();
	// _Pos���� ���� ����� true�� ��ȯ�ϴ� �Լ�
	inline bool IsMapOut(int2 _Pos);
	// ���� �̵��������� ȭ��ǥ�� ǥ���ϱ����� ȭ��ǥ�� �߰��ϴ� ���
	void AddArrow(int2 _TargetPos);
	// ������ Ŀ���� ��ġ���� �̵��ϴ� ��θ� ȭ��ǥ�� ǥ���ϴ� ��� (AddArrow ����� ���ǿ� ���� �ڵ����� ����)
	void MoveCalculation();
	void MoveCalculationForEnemy();

	// �������ֱ��� ������ ���� �̵� �ڽ�Ʈ�� ���. �̵� �Ұ��� ������ 99�� ��ȯ
	int GetTerrainCostFoot(int2 _Pos);
	int GetTerrainDodge(int2 _Pos);
	int GetTerrainDef(int2 _Pos);


	bool UnitMoveAnim();
#pragma endregion

#pragma region Select


	void CursorMove();
	void CursorAndArrowMove();
	void CursorDirCheck();

	void UnitSelect();

#pragma endregion

};

