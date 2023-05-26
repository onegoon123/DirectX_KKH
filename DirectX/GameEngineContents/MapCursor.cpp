#include "PrecompileHeader.h"
#include "MapCursor.h"
#include <iostream>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineMath.h>
#include <math.h>
#include "ContentsEnum.h"
#include "BattleMap.h"

MapCursor::MapCursor()
{
}

MapCursor::~MapCursor()
{
}

void MapCursor::On()
{
	AnimationRender->On();
}

void MapCursor::Off()
{
	AnimationRender->Off();
}

void MapCursor::Start()
{
	if (nullptr == GameEngineSprite::Find("PlayerCursor.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("ContentResources");
		Dir.Move("ContentResources");
		Dir.Move("Battle");
		Dir.Move("Map");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName("PlayerCursor.png").GetFullPath(), 5, 2);
	}
	AnimationRender = CreateComponent<GameEngineSpriteRenderer>(RenderOrder::MapCursor);
	AnimationRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "PlayerCursor.png", .FrameIndex = {1, 2, 3, 4, 3, 2}, .FrameTime = { .5f, .07f, .07f, .07f, .07f, .07f} });
	AnimationRender->CreateAnimation({ .AnimationName = "OnUnit", .SpriteName = "PlayerCursor.png", .Start = 0, .End = 0 });
	AnimationRender->CreateAnimation({ .AnimationName = "Enemy", .SpriteName = "PlayerCursor.png", .FrameIndex = {6, 7, 8, 9, 8, 7}, .FrameTime = { .2f, .05f, .05f, .05f, .05f, .05f} });
	AnimationRender->ChangeAnimation("Idle");
	AnimationRender->GetTransform()->SetWorldScale({ 104, 104 });
	SetMapPos({ 1, 1 });
}
