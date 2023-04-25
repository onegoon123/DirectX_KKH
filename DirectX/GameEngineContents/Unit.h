#pragma once
#include "Stat.h"
class Unit
{
	friend class BattleUnit;
	friend class UnitCommand;
	friend class BattleLevel;
public:
	// constrcuter destructer
	Unit();
	~Unit();

	Unit(const Unit& _Other)
	{
		UnitCode = _Other.UnitCode;
		UnitStat = Stat(_Other.UnitStat);
		CurrentHP = _Other.CurrentHP;
		TerrainDeffence = _Other.TerrainDeffence;
		TerrainDodge = _Other.TerrainDodge;
		IsTurnEnd = _Other.IsTurnEnd;
		IsDie = _Other.IsDie;
	}

	std::string ToString()
	{
		std::string Str;
		Str += "ü�� : " + std::to_string(CurrentHP) + " / " + std::to_string(UnitStat.MainStatValue.HP) + '\n';
		Str += "���ݷ� : " + std::to_string(UnitStat.GetAttackPoint());

		return Str;
	}

private:
	int UnitCode = 0;
	Stat UnitStat;
	int CurrentHP = 0;
	int TerrainDeffence = 0;
	int TerrainDodge = 0;
	bool IsTurnEnd = false;
	bool IsDie = false;
};

