#include "PrecompileHeader.h"
#include "BattleAnimationUI.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
#include "Unit.h"
#include "NumberActor.h"
#include "BattleHPBar.h"
#include "EXPBar.h"
BattleAnimationUI::BattleAnimationUI() 
{
}

BattleAnimationUI::~BattleAnimationUI() 
{
}

void BattleAnimationUI::SetFadeIn(float _Timer)
{
	FadeSpeed = 1 / _Timer;
	FadeTimer = 1;
	IsFadeIn = true;
	IsFadeOut = false;
	FadeRenderer->ColorOptionValue.MulColor.a = 1;
}

void BattleAnimationUI::SetFadeOut(float _Timer)
{
	FadeSpeed = 1 / _Timer;
	FadeTimer = 0;
	IsFadeOut = true;
	IsFadeIn = false;
	FadeRenderer->ColorOptionValue.MulColor.a = 0;
}

void BattleAnimationUI::SetData(Unit& _Unit1, Unit& _Unit2)
{
	Unit& Player = _Unit1.GetIsPlayer() == true ? _Unit1 : _Unit2;
	Unit& Enemy = _Unit2.GetIsPlayer() == true ? _Unit1 : _Unit2;

	PlayerHPBar->Setting(Player.GetHP(), Player.GetMaxHP());

	Number_PlayerHP->Setting(Player.GetHP());
	Number_PlayerDamage->SetValue(Player.GetAttackPoint(Enemy));
	Number_PlayerHit->SetValue(Player.GetHitPoint(Enemy));
	Number_PlayerCritical->SetValue(Player.GetCriticalPoint(Enemy));

	EnemyHPBar->Setting(Enemy.GetHP(), Enemy.GetMaxHP());

	Number_EnemyHP->Setting(Enemy.GetHP());
	Number_EnemyDamage->SetValue(Enemy.GetAttackPoint(Player));
	Number_EnemyHit->SetValue(Enemy.GetHitPoint(Player));
	Number_EnemyCritical->SetValue(Enemy.GetCriticalPoint(Player));

	if (nullptr == Player.GetCurWeapon())
	{
		PlayerWeaponIcon->Off();
	}
	else
	{
		PlayerWeaponIcon->On();
		PlayerWeaponIcon->SetFrame(Player.GetCurWeapon()->GetItemCodeToInt() - 1);
	}
	if (nullptr == Enemy.GetCurWeapon())
	{
		EnemyWeaponIcon->Off();
	}
	else
	{
		EnemyWeaponIcon->On();
		EnemyWeaponIcon->SetFrame(Enemy.GetCurWeapon()->GetItemCodeToInt() - 1);
	}

	// 무기 상성 값
	int TriangleValue = Weapon::GetWeaponeTriangle(Player.GetCurWeapon(), Enemy.GetCurWeapon());
	switch (TriangleValue)
	{
	case 0:
		PlayerTriangle->Off();
		EnemyTriangle->Off();
		break;
	case 1:
		PlayerTriangle->On();
		PlayerTriangle->ChangeAnimation("Advantage");
		EnemyTriangle->On();
		EnemyTriangle->ChangeAnimation("Disadvantage");
		break;
	case -1:
		PlayerTriangle->On();
		PlayerTriangle->ChangeAnimation("Disadvantage");
		EnemyTriangle->On();
		EnemyTriangle->ChangeAnimation("Advantage");
		break;
	default:
		break;
	}
}

void BattleAnimationUI::SetDamage(Unit& _Unit)
{
	if (true == _Unit.GetIsPlayer())
	{
		Number_PlayerHP->SetValueLerp(_Unit.GetHP());
		PlayerHPBar->SetHPAnimation(_Unit.GetHP());
	}
	else
	{
		Number_EnemyHP->SetValueLerp(_Unit.GetHP());
		EnemyHPBar->SetHPAnimation(_Unit.GetHP());
	}
}

void BattleAnimationUI::SetEXP(int _Before, int _Get)
{
	EXPUI->SetEXP(_Before);
	EXPUI->AddEXP(_Get);
	EXPUI->On();
}

bool BattleAnimationUI::IsTurnEnd()
{
	return false == PlayerHPBar->GetIsLerp() && false == Number_PlayerHP->GetIsLerp() && false == EnemyHPBar->GetIsLerp() && false == Number_EnemyHP->GetIsLerp();
}


void BattleAnimationUI::Start()
{
	UIRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::UI);
	UIRenderer->SetTexture("BattleUI.png");
	UIRenderer->GetTransform()->SetLocalScale({ 1024, 640 });

	FadeRenderer = CreateComponent<GameEngineUIRenderer>(RenderOrder::Fade);
	FadeRenderer->ColorOptionValue.MulColor.a = 0;
	FadeRenderer->SetTexture("Black.png");
	FadeRenderer->GetTransform()->SetLocalScale({ 960, 640 });

	PlayerHPBar = GetLevel()->CreateActor<BattleHPBar>();
	PlayerHPBar->GetTransform()->SetParent(GetTransform());
	PlayerHPBar->GetTransform()->SetLocalPosition({ -324, -272 });
	PlayerHPBar->GetTransform()->SetWorldRotation(float4::Zero);
	PlayerHPBar->GetTransform()->SetWorldScale(float4::One);

	EnemyHPBar = GetLevel()->CreateActor<BattleHPBar>();
	EnemyHPBar->GetTransform()->SetParent(GetTransform());
	EnemyHPBar->GetTransform()->SetLocalPosition({ 164, -272 });
	EnemyHPBar->GetTransform()->SetWorldRotation(float4::Zero);
	EnemyHPBar->GetTransform()->SetWorldScale(float4::One);

	Number_PlayerHP = GetLevel()->CreateActor<NumberActor>();
	Number_PlayerHP->SetDamageFont();
	Number_PlayerHP->GetTransform()->SetParent(GetTransform());
	Number_PlayerHP->GetTransform()->SetLocalPosition({ -360, -272 });
	Number_PlayerHP->GetTransform()->SetWorldRotation(float4::Zero);
	Number_PlayerHP->GetTransform()->SetWorldScale({ 1, 0.8f });

	Number_EnemyHP = GetLevel()->CreateActor<NumberActor>();
	Number_EnemyHP->SetDamageFont();
	Number_EnemyHP->GetTransform()->SetParent(GetTransform());
	Number_EnemyHP->GetTransform()->SetLocalPosition({ 128, -272 });
	Number_EnemyHP->GetTransform()->SetWorldRotation(float4::Zero);
	Number_EnemyHP->GetTransform()->SetWorldScale({ 1, 0.8f });

	Number_PlayerDamage = GetLevel()->CreateActor<NumberActor>();
	Number_PlayerDamage->SetDamageFont();
	Number_PlayerDamage->GetTransform()->SetParent(GetTransform());
	Number_PlayerDamage->GetTransform()->SetLocalPosition({ -341, -144 });
	Number_PlayerDamage->GetTransform()->SetWorldRotation(float4::Zero);
	Number_PlayerDamage->GetTransform()->SetWorldScale({1, 0.8f});

	Number_PlayerHit = GetLevel()->CreateActor<NumberActor>();
	Number_PlayerHit->SetDamageFont();
	Number_PlayerHit->GetTransform()->SetParent(GetTransform());
	Number_PlayerHit->GetTransform()->SetLocalPosition({ -341, -176 });
	Number_PlayerHit->GetTransform()->SetWorldRotation(float4::Zero);
	Number_PlayerHit->GetTransform()->SetWorldScale({ 1, 0.8f });

	Number_PlayerCritical = GetLevel()->CreateActor<NumberActor>();
	Number_PlayerCritical->SetDamageFont();
	Number_PlayerCritical->GetTransform()->SetParent(GetTransform());
	Number_PlayerCritical->GetTransform()->SetLocalPosition({ -341, -208 });
	Number_PlayerCritical->GetTransform()->SetWorldRotation(float4::Zero);
	Number_PlayerCritical->GetTransform()->SetWorldScale({ 1, 0.8f });

	Number_EnemyDamage = GetLevel()->CreateActor<NumberActor>();
	Number_EnemyDamage->SetDamageFont();
	Number_EnemyDamage->GetTransform()->SetParent(GetTransform());
	Number_EnemyDamage->GetTransform()->SetLocalPosition({ 456, -144 });
	Number_EnemyDamage->GetTransform()->SetWorldRotation(float4::Zero);
	Number_EnemyDamage->GetTransform()->SetWorldScale({ 1, 0.8f });

	Number_EnemyHit = GetLevel()->CreateActor<NumberActor>();
	Number_EnemyHit->SetDamageFont();
	Number_EnemyHit->GetTransform()->SetParent(GetTransform());
	Number_EnemyHit->GetTransform()->SetLocalPosition({ 456, -176 });
	Number_EnemyHit->GetTransform()->SetWorldRotation(float4::Zero);
	Number_EnemyHit->GetTransform()->SetWorldScale({ 1, 0.8f });

	Number_EnemyCritical = GetLevel()->CreateActor<NumberActor>();
	Number_EnemyCritical->SetDamageFont();
	Number_EnemyCritical->GetTransform()->SetParent(GetTransform());
	Number_EnemyCritical->GetTransform()->SetLocalPosition({ 456, -208 });
	Number_EnemyCritical->GetTransform()->SetWorldRotation(float4::Zero);
	Number_EnemyCritical->GetTransform()->SetWorldScale({ 1, 0.8f });

	PlayerWeaponIcon = CreateComponent<GameEngineUIRenderer>(RenderOrder::UICursor);
	PlayerWeaponIcon->GetTransform()->SetLocalPosition({ -272, -200 });
	PlayerWeaponIcon->GetTransform()->SetLocalScale({ 64, 64 });
	PlayerWeaponIcon->SetSprite("Items.png", 0);

	EnemyWeaponIcon = CreateComponent<GameEngineUIRenderer>(RenderOrder::UICursor);
	EnemyWeaponIcon->GetTransform()->SetLocalPosition({ 48, -200 });
	EnemyWeaponIcon->GetTransform()->SetLocalScale({ 64, 64 });
	EnemyWeaponIcon->SetSprite("Items.png", 0);

	// 무기 상성 이미지
	PlayerTriangle = CreateComponent<GameEngineUIRenderer>(RenderOrder::UICursor);
	PlayerTriangle->CreateAnimation({ .AnimationName = "Advantage", .SpriteName = "Triangle.png", .Start = 0, .End = 2, .FrameInter = 0.15f });
	PlayerTriangle->CreateAnimation({ .AnimationName = "Disadvantage", .SpriteName = "Triangle.png", .Start = 3, .End = 5, .FrameInter = 0.15f });
	PlayerTriangle->ChangeAnimation("Advantage");
	PlayerTriangle->GetTransform()->SetLocalPosition({ -248, -214 });
	PlayerTriangle->GetTransform()->SetWorldScale({ 28, 40 });

	EnemyTriangle = CreateComponent<GameEngineUIRenderer>(RenderOrder::UICursor);
	EnemyTriangle->CreateAnimation({ .AnimationName = "Advantage", .SpriteName = "Triangle.png", .Start = 0, .End = 2, .FrameInter = 0.15f });
	EnemyTriangle->CreateAnimation({ .AnimationName = "Disadvantage", .SpriteName = "Triangle.png", .Start = 3, .End = 5, .FrameInter = 0.15f });
	EnemyTriangle->ChangeAnimation("Advantage");
	EnemyTriangle->GetTransform()->SetLocalPosition({ 72, -214 });
	EnemyTriangle->GetTransform()->SetWorldScale({ 28, 40 });

	EXPUI = GetLevel()->CreateActor<EXPBar>();
	EXPUI->GetTransform()->SetParent(GetTransform());
	EXPUI->GetTransform()->SetLocalPosition({ 0, -108 });
	EXPUI->Off();

}

void BattleAnimationUI::Update(float _DeltaTime)
{
	if (true == IsFadeIn)
	{
		FadeTimer -= _DeltaTime * FadeSpeed;
		if (FadeTimer < 0)
		{
			IsFadeIn = false;
			FadeRenderer->ColorOptionValue.MulColor.a = 0;
			return;
		}
		FadeRenderer->ColorOptionValue.MulColor.a = FadeTimer;
	}

	if (true == IsFadeOut)
	{
		FadeTimer += _DeltaTime * FadeSpeed;
		if (FadeTimer > 1)
		{
			IsFadeOut = false;
			FadeRenderer->ColorOptionValue.MulColor.a = 1;
			return;
		}
		FadeRenderer->ColorOptionValue.MulColor.a = FadeTimer;
	}
}

