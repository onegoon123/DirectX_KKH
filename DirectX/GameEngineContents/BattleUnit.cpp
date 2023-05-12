#include "PrecompileHeader.h"
#include "BattleUnit.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "Stat.h"
#include "Weapon.h"
#include "SpriteRenderer.h"
BattleUnit::BattleUnit() 
{
}

BattleUnit::~BattleUnit() 
{
}

void BattleUnit::SetIsTurnEnd(bool _Value)
{
	UnitData.IsTurnEnd = _Value;

	if (_Value == true)
	{
		Renderer->SetGrayScale(true);
	}
	else
	{
		Renderer->SetGrayScale(false);
	}
}

bool BattleUnit::GetIsTurnEnd()
{
	return UnitData.IsTurnEnd;
}


void BattleUnit::SetUnitCode(int _Code)
{
	SetUnitCode(static_cast<UnitIdentityCode>(_Code));
}

static int EnemyNum = 0;
void BattleUnit::SetUnitCode(UnitIdentityCode _Code)
{
	UnitData.UnitCode = static_cast<int>(_Code);
	UnitData.UnitStat.SetIdentity(_Code);
	UnitData.CurrentHP = UnitData.UnitStat.MainStatValue.HP;
	IsShortWalk = false;
	switch (_Code)
	{
	case UnitIdentityCode::Lyn:
		SetName("��");
		UnitData.SetName("Lyn");
		MapSpriteName = "Map_Lyn.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Sain:
		break;
	case UnitIdentityCode::Kent:
		SetName("��Ʈ");
		UnitData.SetName("Kent");
		MapSpriteName = "Map_Cavalier.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Florina:
		break;
	case UnitIdentityCode::Wil:
		break;
	case UnitIdentityCode::Dorcas:
		SetName("��ī��");
		UnitData.SetName("Dorcas");
		MapSpriteName = "Map_Dorcas.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Serra:
		break;
	case UnitIdentityCode::Erk:
		break;
	case UnitIdentityCode::Rath:
		break;
	case UnitIdentityCode::Matthew:
		break;
	case UnitIdentityCode::Ninian:
		break;
	case UnitIdentityCode::Lucius:
		break;
	case UnitIdentityCode::Wallace:
		SetName("������");
		UnitData.SetName("Wallace");
		MapSpriteName = "Map_Wallace.png";
		UnitData.IsPlayer = true;
		break;
	case UnitIdentityCode::Brigand:
		UnitData.UnitCode += EnemyNum++;
		SetName("����");
		UnitData.SetName("Enemy");
		MapSpriteName = "Map_EnemyBrigand.png";
		IsShortWalk = true;
		UnitData.IsPlayer = false;
		break;
	case UnitIdentityCode::Soldier:
		break;
	case UnitIdentityCode::Mercenary:
		break;
	case UnitIdentityCode::Archer:
		break;
	case UnitIdentityCode::Knight:
		break;
	case UnitIdentityCode::Mage:
		break;
	default:
		break;
	}

	//std::string_view AnimationName = "";
	//std::string_view SpriteName = "";
	//size_t Start = static_cast<size_t>(-1);
	//size_t End = static_cast<size_t>(-1);
	//float FrameInter = 0.1f;
	//bool Loop = true;
	//bool ScaleToTexture = false;
	if (nullptr == GameEngineSprite::Find(MapSpriteName))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Character");
		Dir.Move("Map");
		if (true == IsShortWalk)
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName(MapSpriteName).GetFullPath(), 3, 5);
		}
		else
		{
			GameEngineSprite::LoadSheet(Dir.GetPlusFileName(MapSpriteName).GetFullPath(), 3, 6);
		}
	}


	Renderer->CreateAnimation({ "Idle", MapSpriteName, 0, 2, 0.2f, true, false});
	Renderer->CreateAnimation({ "Select", MapSpriteName, 3, 5, 0.2f, true, false});
	if (true == IsShortWalk)
	{
		Renderer->CreateAnimation({ "Left", MapSpriteName, 6, 8, 0.2f, true, false });
		Renderer->CreateAnimation({ "Down", MapSpriteName, 9, 11, 0.2f, true, false });
		Renderer->CreateAnimation({ "Up", MapSpriteName, 12, 14, 0.2f, true, false });

	}
	else
	{
		Renderer->CreateAnimation({ "Left", MapSpriteName, 6, 9, 0.2f, true, false });
		Renderer->CreateAnimation({ "Down", MapSpriteName, 10, 13, 0.2f, true, false });
		Renderer->CreateAnimation({ "Up", MapSpriteName, 14, 17, 0.2f, true, false });
	} 

	Renderer->ChangeAnimation("Idle");
}


void BattleUnit::Start()
{
	Renderer = CreateComponent<SpriteRenderer>();
	Renderer->SetWorldScale({ 192,192 });
	SetMapPos({ 0,0 });
}

void BattleUnit::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("ButtonA"))
	{
		Renderer->ChangeAnimation("Select");
	}
	if (GameEngineInput::IsDown("ButtonB"))
	{
		Renderer->ChangeAnimation("Idle");
	}
	if (GameEngineInput::IsDown("Left"))
	{
		Renderer->ChangeAnimation("Left");
	}
	if (GameEngineInput::IsDown("Up"))
	{
		Renderer->ChangeAnimation("Up");
	}
	if (GameEngineInput::IsDown("Down"))
	{
		Renderer->ChangeAnimation("Down");
	}
}

