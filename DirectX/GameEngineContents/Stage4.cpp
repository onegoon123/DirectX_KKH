#include "PrecompileHeader.h"
#include "Stage4.h"

Stage4::Stage4()
{
	StartPos.push_back({ 7, 8 });
	StartPos.push_back({ 5, 6 });
	StartPos.push_back({ 9, 6 });
	StartPos.push_back({ 6, 7 });
	StartPos.push_back({ 8, 7 });
}

Stage4::~Stage4()
{
}

void Stage4::StageSetting()
{
	SetStage(4);

	// 윌
	NewPlayerUnit(UnitIdentityCode::Wil, 2, { 8, 7 }, { ItemCode::IronBow });

	// 돌카스 (적대)
	NewEnemyUnit(UnitIdentityCode::Dorcas, 3, { 13, 6 }, { ItemCode::HandAxe });

	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 8, 3 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 7, 2 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 4, 2 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 6, 0 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 10, 1 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 0, 10 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 14, 13 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 3, { 9, 0 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 1, { 1, 1 }, { ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 2, { 1, 8 }, { ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Archer, 1, { 1, 4 }, { ItemCode::IronBow });
	NewEnemyUnit(UnitIdentityCode::Archer, 1, { 12, 0 }, { ItemCode::IronBow });
	// 카지가
	NewEnemyUnit(UnitIdentityCode::Brigand, 9, { 13, 0 }, { ItemCode::IronAxe });
}

