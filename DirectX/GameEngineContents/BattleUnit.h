#pragma once
#include "MapUnit.h"
#include "Stat.h"
#include "Unit.h"
#include "ContentsEnum.h"
class BattleUnit : public MapUnit
{
public:

	BattleUnit();
	~BattleUnit();

	BattleUnit(const BattleUnit& _Other) = delete;
	BattleUnit(BattleUnit&& _Other) noexcept = delete;
	BattleUnit& operator=(const BattleUnit& _Other) = delete;
	BattleUnit& operator=(BattleUnit&& _Other) noexcept = delete;

	void Select();
	void SetIdle();

	// ������ �Ͽ��� ���θ� �����ϴ� �Լ�
	void SetIsTurnEnd(bool _Value);
	// ������ �Ͽ��� ���θ� ��ȯ
	bool GetIsTurnEnd();
	// ������ ������� ����
	void SetIsDie(bool _Value)
	{
		UnitData.IsDie = _Value;
	}
	// ������ ������� ��ȯ
	bool GetIsDie()
	{
		return UnitData.IsDie;
	}
	// ������ �÷��̾��� �������� ��ȯ
	bool GetIsPlayer()
	{
		return UnitData.IsPlayer;
	}

	// �����ڵ带 ���� (�ʱ� ���� ����)
	void SetUnitCode(int _Code);
	// �����ڵ带 ���� (�ʱ� ���� ����)
	void SetUnitCode(UnitIdentityCode _Code);
	// �����ڵ带 ��ȯ (���ֺ� ���п�)
	int GetUnitCode()
	{
		return UnitData.UnitCode;
	}

	// ���� �����͸� ����
	void SetUnitData(Unit _Value)
	{
		UnitData = _Value;
		if (false == UnitData.IsDie)
		{
			On();
		}
		SetIsTurnEnd(GetIsTurnEnd());
	}
	// ���� �����͸� ��ȯ
	Unit& GetUnitData()
	{
		return UnitData;
	}

	// ������ �̵����� ��ȯ
	int GetMoveStat()
	{
		return UnitData.UnitStat.Movement;
	}
	// ������ ��Ÿ��� ��ȯ
	int GetRangeStat() {
		return UnitData.GetRangeStat();
	}
	// �� ������ �ٸ� ������ ���� ���ݰ��������� ��ȯ. �� ������ �Ÿ��� �ʿ�
	bool IsAttackable(int _Distance);
	// �� ������ �ٸ� ������ ���� ���ݰ��������� ��ȯ. �ٸ� ������ ������ �ʿ�
	bool IsAttackable(std::shared_ptr<BattleUnit> _Other);
	// �� ������ �ٸ� ������ ���� ���ݰ��������� ��ȯ. �ٸ� ������ ��ġ �ʿ�
	bool IsAttackable(int2 _Other);

	// ������ ����
	void SetTerrain(Terrain _TerrainData)
	{
		UnitData.TerrainData = _TerrainData;
		UnitData.TerrainDodge = BattleMap::GetTerrainDodge(_TerrainData);
		UnitData.TerrainDeffence = BattleMap::GetTerrainDef(_TerrainData);
	}

	// �������� �߰�
	void NewItem(ItemCode _Code)
	{
		UnitData.NewItem(_Code);
	}

	// ������ ��ȯ
	std::shared_ptr<class SpriteRenderer> GetRenderer()
	{
		return Renderer;
	}
	std::string_view GetMapSpriteName()
	{
		return MapSpriteName;
	}

	// (�� ����) ���ݹ��� ǥ�ÿ��� ��ȯ
	bool GetIsCheckTile() { return IsCheckTile; }
	// (�� ����) ���ݹ��� ǥ�ÿ��� ����
	void SetIsCheckTile(bool _Value) { IsCheckTile = _Value; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SetMoveDir(int2 _Dir) override;

	std::shared_ptr<class SpriteRenderer> Renderer = nullptr;
	std::shared_ptr<class SpriteRenderer> FrontRenderer = nullptr;
	std::string_view MapSpriteName = "";
private:
	Unit UnitData;

	bool IsCheckTile = false;
};

