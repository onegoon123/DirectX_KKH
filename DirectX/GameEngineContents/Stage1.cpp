#include "PrecompileHeader.h"
#include "Stage1.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
Stage1::Stage1()
{
	StartPos.push_back({ 2, 1 });
	StartPos.push_back({ 0, 2 });
	StartPos.push_back({ 0, 4 });
	StartPos.push_back({ 0, 0 });

	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
	StartPos.push_back({ 0, 0 });
}

Stage1::~Stage1()
{
}

void Stage1::StageSetting()
{
	SetStage(1);
	ClearTarget = BattleClearTarget::AllKill;
	ClearTargetText = "목표:적 전멸";

	// 켄트, 세인
	NewPlayerUnit(UnitIdentityCode::Kent, 1, { 0, 2 }, { ItemCode::IronSword, ItemCode::IronLance, ItemCode::Vulnerary })->GetUnitData().AddExp(99);
	NewPlayerUnit(UnitIdentityCode::Sain, 1, { 0, 4 }, { ItemCode::IronLance });

	// 산적
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 4, 3 }, { ItemCode::IronAxe});
	NewEnemyUnit(UnitIdentityCode::Brigand, 1, { 9, 0 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 12, 8 }, { ItemCode::IronAxe });
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 13, 4 }, { ItemCode::IronAxe })->SetDetectionRange(5);
	// 주그
	NewEnemyUnit(UnitIdentityCode::Zugu, 1, { 13, 8 }, { ItemCode::IronAxe })->SetDetectionRange(3);

	OpeningEventInit();
	ClearEventInit();
}

void Stage1::OpeningEventInit()
{
	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeIn(1.0f);
		}
	, false, 1.0f);

}

void Stage1::ClearEventInit()
{
	ClearEvent->PushEvent([this] {
		ClearEvent->SetFadeOut(0.5f);
		}, false, 1.0f);

	ClearEvent->PushEvent([this] {
		GameEngineCore::ChangeLevel("Stage2");
		}, false, .6f);

	ClearEvent->SkipFunction = [this] {
		GameEngineCore::ChangeLevel("Stage2");
	};
}

