#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"
#include "Int2.h"
#include "UnitCommand.h"
#include "EventSystem.h"

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

	std::shared_ptr <class MapCursor> GetMapCursor()
	{
		return MainCursor;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	virtual void StageSetting() = 0;

	void SetStage(int _StageNum);

	std::vector<int2> StartPos;
	void LoadPlayerUnits(std::list<Unit>& _Units);
	std::shared_ptr<BattleUnit> LoadPlayerUnit(const Unit& _Unit);

	std::shared_ptr<BattleUnit> NewPlayerUnit(UnitIdentityCode _Code, int _Level, int2 _Pos, std::vector<ItemCode> _Items);

	std::shared_ptr<BattleUnit> NewEnemyUnit(UnitIdentityCode _Code, int _Level, int2 _Pos, std::vector<ItemCode> _Items);

	enum class BattleClearTarget
	{
		AllKill,	// �� ����
		Conquer,	// ����
		Survival,	// ����
		BossKill,	// ����óġ
	};

	BattleClearTarget ClearTarget = BattleClearTarget::AllKill;
	int2 ConquerPos = { -1, -1 };

	std::shared_ptr<EventSystem> OpeningEvent;
	std::shared_ptr <EventSystem> ClearEvent;

private:

	// State
	enum class BattleState
	{
		None,
		Opening,		// ���۽� ����ܰ�

		PlayerPhase,	// �÷��̾� �� ����
		Select,		// Ŀ���� ������ �����ϴ� �ܰ�
		Move,		// ������ �������� �̵��� ��ġ�� ���ϴ� �ܰ�
		MoveWait,	// ������ �̵��ϴ� �ð��� ��ٸ��� �ܰ�
		UnitCommand,	// ������ �ൿ�� ���ϴ� �ܰ�
		FieldCommand,	// Ŀ���� ���� Ŭ���ϸ� ������ �ൿ���� ���ϴ� �ܰ�
		Battle,		// ���ֳ��� ������ �ϴ� �ܰ�
		BattleReturn,	// ���ݷ������� ���ƿ�
		Potion,	        // ȸ���� ���
		Heal,	        // �� ���

		EnemyPhase,	// ���� ���� ����
		EnemySelect,	// �� ����
		EnemyMove,			// ���� �̵�
		EnemyBattle,		// ���� ����
		EnemyBattleReturn,	// �� ���ݷ������� ���ƿ�
		EnemyPotion,	    // ȸ���� ���

		Information,		// ���� ����â�� ������
		GameOver,			// ���� ����
		TimeStone,			// �ð��� ���
		Clear,				// Ŭ����
	};
	BattleState CurState = BattleState::None;	// ������Ʈ
	std::function<void(float)> StateUpdate = nullptr;
	std::function<void()> StateEnd = nullptr;

	// Actor
	std::shared_ptr<class GameEngineCamera>	MainCamera = nullptr;
	std::shared_ptr<class BattleMap> MainMap = nullptr;
	std::shared_ptr <class MapCursor> MainCursor = nullptr;
	std::list<std::shared_ptr <class BattleUnit>> PlayerUnits = std::list< std::shared_ptr <BattleUnit>>();		// �÷��̾� ���� ����Ʈ
	std::list< std::shared_ptr <BattleUnit>> EnemyUnits = std::list< std::shared_ptr <BattleUnit>>();		// �� ���� ����Ʈ
	std::list< std::shared_ptr <BattleUnit>> AttackableUnits = std::list< std::shared_ptr <BattleUnit>>();	// ���� ������ ���� ����Ʈ
	std::list< std::shared_ptr <BattleUnit>> CloseUnits = std::list< std::shared_ptr <BattleUnit>>();		// �ֺ��� �ִ� ���� ����Ʈ
	std::shared_ptr <BattleUnit> SelectUnit = nullptr;	// ���õ� ����
	std::shared_ptr <BattleUnit> TargetUnit = nullptr;
	std::shared_ptr <MapUnit> CameraUnit = nullptr;
	std::list<AttackCommand> AttackRecord;

	// Map ����
	std::shared_ptr <class TileRender> Tiles = nullptr;
	std::shared_ptr <class ArrowRender> Arrows = nullptr;
	std::vector<int2> ArrowPos = std::vector<int2>();
	std::vector<std::vector<bool>> IsMove = std::vector<std::vector<bool>>();
	std::vector<std::vector<bool>> IsAttack = std::vector<std::vector<bool>>();
	bool IsArrowOut = false;
	bool IsEnemyRangeCheck = false;
	bool IsMouseOn = false;
	bool IsSkip = false;

	// UI
	std::shared_ptr<class BattleLevelUI> BattleUI = nullptr;
	std::shared_ptr <class UnitInformationUI> InfoUI = nullptr;

	const float MoveSpeed = 10;
	int MoveIndex = 0;

	int2 BeforePos = int2::Zero;
	float4 BeforeCamPos = float4::Zero;

	std::list<std::shared_ptr<Item>>::iterator UseItem;

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

	void BattleReturnStart();
	void BattleReturnUpdate(float _DeltaTime);
	void BattleReturnEnd();

	void HealStart();
	void HealUpdate(float _DeltaTime);
	void HealEnd();

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

	void EnemyBattleReturnStart();
	void EnemyBattleReturnUpdate(float _DeltaTime);
	void EnemyBattleReturnEnd();

	void InformationStart();
	void InformationUpdate(float _DeltaTime);
	void InformationEnd();

	void GameOverStart();
	void GameOverUpdate(float _DeltaTime);
	void GameOverEnd();

	void TimeStoneStart();
	void TimeStoneUpdate(float _DeltaTime);
	void TimeStoneEnd();

	void OpeningStart();
	void OpeningUpdate(float _DeltaTime);
	void OpeningEnd();

	bool GameOverCheck();


	void PotionStart();
	void PotionUpdate(float _DeltaTime);
	void PotionEnd();

	void EnemyPotionStart();
	void EnemyPotionUpdate(float _DeltaTime);
	void EnemyPotionEnd();

	void ClearStart();
	void ClearUpdate(float _DeltaTime);
	void ClearEnd();
#pragma endregion


#pragma region Map

	// ������ ���ý� �̵������� ������ ǥ���ϴ� ��� (Ž�� ������ ����)
	void MoveSearch();
	// ���ݰ��� ������ ǥ�� (MoveSearch ����� �ڵ����� ����)
	void AttackSearch();
	void AttackSearchBow();

	void MoveSearchForEnemy();
	void AttackSearchForEnemy();
	// Ŀ���� ��ġ�� �ٸ� �÷��̾� ������ ���ٸ� MoveWait State�� ��ȯ
	void UnitMove();
	// _Pos���� ���� ����� true�� ��ȯ�ϴ� �Լ�
	inline bool IsMapOut(int2 _Pos);
	// ���� �̵��������� ȭ��ǥ�� ǥ���ϱ����� ȭ��ǥ�� �߰��ϴ� ���
	void AddArrow(int2 _TargetPos);
	// ������ Ŀ���� ��ġ���� �̵��ϴ� ��θ� ȭ��ǥ�� ǥ���ϴ� ��� (AddArrow ����� ���ǿ� ���� �ڵ����� ����)
	void MoveCalculation();
	// ���� ������ ������ ã�Ƽ� ��ȯ�ϴ� ���
	void EnemyFindTarget();
	// ���� ������ ���� �̵���θ� ����ϴ� ���
	void MoveCalculationForEnemyAttack();
	// ���� �̵��� ���� ��θ� ����ϴ� ���
	void MoveCalculationForEnemy();

	// �������� ���� ���� ������ ������ ǥ���ϴ� ��� (IsCheckTile�� true�� �� ����)
	void EnemyTileCheck();

	void SetTile();

	Terrain GetTerrain(int2 _Pos);
	// �������ֱ��� ������ ���� �̵� �ڽ�Ʈ�� ���. �̵� �Ұ��� ������ 99�� ��ȯ
	int GetTerrainCostFoot(int2 _Pos);
	int GetTerrainCostFly(int2 _Pos);
	int GetTerrainDodge(int2 _Pos);
	int GetTerrainDef(int2 _Pos);

	// float4::Lerp �� �̿��Ͽ� �̵��� ��ġ���� ȭ��ǥ�� ���� ������ �̵���Ű�� ���, �������� ���� �� true�� �����մϴ�.
	bool UnitMoveAnim();
#pragma endregion

#pragma region Select
	
	void CursorMove();
	void CursorUnitSelect();
	void CursorAndArrowMove();
	void CursorMoveMouse();
	void CursorAndArrowMoveMouse();

	// Ŀ���� ���� SeledctUI��ġ ����
	void CursorDirCheck(); 

	void UnitSelect();
	// ���õ� ���ֿ� ���� SelectUI ���� ����
	void SetUI_UnitData(); 

#pragma endregion

#pragma region UnitCommand

public:
	void UnitCommand_Item();
	void UnitCommand_Wait();
	void UnitCommand_Attack();
	void UnitCommand_Heal();
	void UnitCommand_Exchange();
	void UnitCommand_ExchangeEnd(std::shared_ptr<BattleUnit> _Target);
	void UnitCommand_Cancel();
	void UnitCommand_CommandCancel();
	void UnitCommand_TargetAttack(std::shared_ptr<BattleUnit> _Target);
	void UnitCommand_TargetHeal(std::shared_ptr<BattleUnit> _Target, std::list<std::shared_ptr<Item>>::iterator& _ItemIter);
	void UnitCommand_ItemUse(std::list<std::shared_ptr<class Item>>::iterator& _ItemIter);
	void UnitCommand_Conquer();
private:

#pragma endregion

#pragma region FieldCommand

public:
	void FieldCommand_TimeStone();
	void FieldCommand_ArmyUnit();
	void FieldCommand_Setting();
	void FieldCommand_Exit();
	void FieldCommand_PhaseEnd();
	void FieldCommand_Cancel();
private:

#pragma endregion

#pragma region UnitInformation

public:
	void UnitInformation_Cancel();

private:

#pragma endregion


	// Ŀ���� ���� ī�޶� ����
	void CameraSetting(int2 _Value);
	void CameraMove(int2 _Value);
	void CameraSetPos();
	void CameraUpdate(float _DeltaTime);
};

