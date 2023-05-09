#include "PrecompileHeader.h"
#include "BattleLevel.h"
#include <queue>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "BattleMap.h"
#include "MapCursor.h"
#include "BattleUnit.h"
#include "TileRender.h"
#include "ArrowRender.h"
#include "ContentsEnum.h"
#include "SelectUI.h"
#include "UnitCommandUI.h"
#include "FieldCommandUI.h"
#include "PhaseUI.h"
#include "UICursor.h"
BattleLevel::BattleLevel()
{
	StateUpdate = std::bind(&BattleLevel::PlayerPhaseUpdate, this, std::placeholders::_1);
	StateEnd = std::bind(&BattleLevel::PlayerPhaseEnd, this);

	ArrowPos.reserve(8);

}

BattleLevel::~BattleLevel()
{
}

void BattleLevel::Start()
{
	// ī�޶� ����
	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetWorldPosition({ 448, 288, -554.0f });
	// ���� ����
	MainMap = CreateActor<BattleMap>();

	Tiles = CreateActor<TileRender>();
	Tiles->Create(MainMap->MapScaleInt2);

	Arrows = CreateActor<ArrowRender>();
	Arrows->Create(MainMap->MapScaleInt2);

	MainCursor = CreateActor<MapCursor>();
	MainCursor->SetMapPos({ 0,0 });

	std::shared_ptr<BattleUnit> NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Lyn);
	NewActor->NewWeapon(ItemCode::IronSword);
	NewActor->SetMapPos({ 4, 5 });
	NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	PlayerUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Dorcas);
	NewActor->SetMapPos({ 5, 4 });
	NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	NewActor->NewWeapon(ItemCode::IronAxe);
	PlayerUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Wallace);
	NewActor->SetMapPos({ 6, 5 });
	NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	NewActor->NewWeapon(ItemCode::IronLance);
	PlayerUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Kent);
	NewActor->SetMapPos({ 3, 5 });
	NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	NewActor->NewWeapon(ItemCode::IronAxe);
	PlayerUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewWeapon(ItemCode::IronAxe);
	NewActor->SetMapPos({ 8, 5 });
	NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	EnemyUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewWeapon(ItemCode::IronAxe);
	NewActor->SetMapPos({ 9, 6 });
	NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	EnemyUnits.push_back(NewActor);

	NewActor = CreateActor<BattleUnit>();
	NewActor->SetUnitCode(UnitIdentityCode::Brigand);
	NewActor->NewWeapon(ItemCode::IronAxe);
	NewActor->SetMapPos({ 9, 4 });
	NewActor->SetTerrain(MainMap->TerrainData[NewActor->GetMapPos().y][NewActor->GetMapPos().x]);
	EnemyUnits.push_back(NewActor);

	
	IsMove.resize(MainMap->MapScaleInt2.y);
	for (int i = 0; i < IsMove.size(); i++)
	{
		IsMove[i].resize(MainMap->MapScaleInt2.x);
	}
	IsAttack.resize(MainMap->MapScaleInt2.y);
	for (int i = 0; i < IsAttack.size(); i++)
	{
		IsAttack[i].resize(MainMap->MapScaleInt2.x);
	}

	UITransform.SetParent(GetMainCamera()->GetTransform());
	UITransform.SetLocalPosition({ 0, 0,  554.0f });

	UI_Select = CreateActor<SelectUI>();
	UI_Select->GetTransform()->SetParent(&UITransform);
	UI_Select->GetTransform()->SetLocalPosition(float4::Zero);

	UI_UnitCommand = CreateActor<UnitCommandUI>();
	UI_UnitCommand->GetTransform()->SetParent(&UITransform);
	UI_UnitCommand->GetTransform()->SetLocalPosition(float4::Zero);

	UI_FieldCommand = CreateActor<FieldCommandUI>();
	UI_FieldCommand->GetTransform()->SetParent(&UITransform);
	UI_FieldCommand->GetTransform()->SetLocalPosition(float4::Zero);

	UI_Phase = CreateActor<PhaseUI>();
	UI_Phase->GetTransform()->SetParent(&UITransform);
	UI_Phase->GetTransform()->SetLocalPosition(float4::Zero);

	UI_Cursor = CreateActor<UICursor>();

	//UI_Window = CreateActor<UIWindow>();
	//UI_Window->GetTransform()->SetParent(&UITransform);
	//UI_Window->GetTransform()->SetLocalPosition(float4::Zero);
	//UI_Window->Setting();
	


	UI_UnitCommand->Setting(this);
	UI_FieldCommand->Setting(this);

	CursorDirCheck();
	ChangeState(BattleState::PlayerPhase);
}

void BattleLevel::Update(float _DeltaTime)
{
	StateUpdate(_DeltaTime);
}

