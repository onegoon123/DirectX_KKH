#include "PrecompileHeader.h"
#include "Stage10.h"
#include "FEData.h"
Stage10::Stage10()
{
	StartPos.push_back({ 4, 15 });
	StartPos.push_back({ 5, 14 });
	StartPos.push_back({ 4, 14 });
	StartPos.push_back({ 5, 16 });
	StartPos.push_back({ 3, 15 });
	StartPos.push_back({ 2, 16 });
	StartPos.push_back({ 6, 15 });
	StartPos.push_back({ 2, 15 });
	StartPos.push_back({ 4, 16 });
	StartPos.push_back({ 5, 13 });
	StartPos.push_back({ 5, 17 });
	StartPos.push_back({ 5, 15 });
}

Stage10::~Stage10()
{
}

void Stage10::StageSetting()
{
	SetStage(10);
	ClearTarget = BattleClearTarget::Conquer;
	ConquerPos = { 2, 1 };
	ClearTargetText = "��ǥ:��� ����";

	OpeningEventInit();
	ClearEventInit();
	NewPlayerUnit(UnitIdentityCode::Lyn, 10, { 4, 15 }, { ItemCode::ManiKatti, ItemCode::Vulnerary, ItemCode::MasterSeal });
	NewPlayerUnit(UnitIdentityCode::Kent, 8, { 5, 14 }, { ItemCode::IronLance, ItemCode::IronSword, ItemCode::Vulnerary });
	NewPlayerUnit(UnitIdentityCode::Florina, 8, { 4, 14 }, { ItemCode::SlimLance});
	NewPlayerUnit(UnitIdentityCode::Serra, 8, { 5, 16 }, { ItemCode::Heal });
	NewPlayerUnit(UnitIdentityCode::Erk, 8, { 3, 15 }, { ItemCode::Fire, ItemCode::Flux });
	NewPlayerUnit(UnitIdentityCode::Wil, 8, { 2, 16 }, { ItemCode::IronBow });
	NewPlayerUnit(UnitIdentityCode::Wallace, 1, { 6, 15 }, { ItemCode::IronLance, ItemCode::IronAxe, ItemCode::MasterSeal });

	NewEnemyUnit(UnitIdentityCode::Soldier, 5, { 14, 14 }, { ItemCode::IronLance });
	NewEnemyUnit(UnitIdentityCode::Mage, 1, { 15, 15 }, { ItemCode::Fire });
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 13, 16 }, { ItemCode::IronAxe })->SetDetectionRange(6);
	NewEnemyUnit(UnitIdentityCode::Archer, 3, { 16, 13 }, { ItemCode::IronBow });
	NewEnemyUnit(UnitIdentityCode::Archer, 3, { 14, 9 }, { ItemCode::IronBow })->SetDetectionRange(8);
	NewEnemyUnit(UnitIdentityCode::DarkMage, 3, { 15, 3 }, { ItemCode::Flux });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 3, { 9, 7 }, { ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Mercenary, 3, { 8, 8 }, { ItemCode::IronSword });
	NewEnemyUnit(UnitIdentityCode::Archer, 3, { 7, 4 }, { ItemCode::IronBow })->SetDetectionRange(8);
	NewEnemyUnit(UnitIdentityCode::Brigand, 2, { 7, 6 }, { ItemCode::IronAxe })->SetDetectionRange(7);
	NewEnemyUnit(UnitIdentityCode::Knight, 3, { 2, 0 }, { ItemCode::IronLance })->SetDetectionRange(3);
	NewEnemyUnit(UnitIdentityCode::PegasusKnight, 3, { 1, 7 }, { ItemCode::IronLance });
	NewEnemyUnit(UnitIdentityCode::PegasusKnight, 3, { 13, 0 }, { ItemCode::IronLance })->SetDetectionRange(10);
	NewEnemyUnit(UnitIdentityCode::PegasusKnight, 3, { 15, 0 }, { ItemCode::IronLance })->SetDetectionRange(10);
	NewEnemyUnit(UnitIdentityCode::Lundgren, 1, { 2, 1 }, { ItemCode::SilverLance })->SetDetectionRange(1);
}

void Stage10::OpeningEventInit()
{
	OpeningEvent->PushEvent([this] {
		BgmPlayer = GameEngineSound::Play("Companions.mp3");
		OpeningEvent->SetFadeIn(0.5f);
		}
	, false, 1.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->SetFadeOut(0.5f);
		}
	, false, 0.8f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Background->SetTexture("EventBackground_Plains.png");
		OpeningEvent->Background->On();
		OpeningEvent->Portrait2->SetPortrait(UnitIdentityCode::Lyn);
		OpeningEvent->Portrait2->On();
		OpeningEvent->Portrait3->SetPortrait(UnitIdentityCode::Sain);
		OpeningEvent->Portrait3->On();
		OpeningEvent->Portrait4->SetPortrait(UnitIdentityCode::Kent);
		OpeningEvent->Portrait4->On();
		OpeningEvent->SetFadeIn(0.5f);
		}
	, false, 0.8f);


	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetSize({ 20, 5 });
		OpeningEvent->Portrait4->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"���𽺴�, ���� ��ȸ�ϸ�\nŰ�ƶ����� ���� �̴ϴ�.");
		OpeningEvent->Dialogue->ArrowRender->On();
		OpeningEvent->Dialogue->ArrowRender->SetFlipX();
		OpeningEvent->Dialogue->SetFadeIn(.5f);
		OpeningEvent->Dialogue->GetTransform()->SetLocalPosition({ -324, 164 });
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.3f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetSize({ 13, 5 });
		OpeningEvent->Dialogue->ArrowRender->On();
		OpeningEvent->Dialogue->ArrowRender->SetFlipX();
		OpeningEvent->Dialogue->SetFadeIn(.2f);
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"�Ҿƹ���...");
		OpeningEvent->Dialogue->GetTransform()->SetLocalPosition({ -32, 164 });
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"...���� ��\n���� �� �־��...");
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.3f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeIn(.2f);
		OpeningEvent->Dialogue->SetSize({ 20, 5 });
		OpeningEvent->Dialogue->ArrowRender->On();
		OpeningEvent->Dialogue->ArrowRender->SetFlipX();
		OpeningEvent->Portrait3->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"��� ����\n�� ������ �޷� �ֽ��ϴ�.");
		OpeningEvent->Dialogue->GetTransform()->SetLocalPosition({ -432, 164 });
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait3->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"�ϰ� �ִ� �α� �����κ���\n������ ������ �ʰ� �� ����...");
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait3->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"���׷� ���� ����� ����\n���� �� �״ϱ��!");
		}
	, true, 0.5f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeOut(.2f);
		}
	, false, 0.3f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetSize({ 17, 5 });
		OpeningEvent->Dialogue->ArrowRender->On();
		OpeningEvent->Dialogue->ArrowRender->SetFlipX();
		OpeningEvent->Dialogue->SetFadeIn(.2f);
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"�󸶳� ���� ���� ����\n�� ���� �ʾ�!");
		OpeningEvent->Dialogue->GetTransform()->SetLocalPosition({ 0, 164 });
		}
	, true, 0.5f);
	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"�Ҿƹ�����\n���� �˱� ���ؼ�...");
		}
	, true, 0.5f);
	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"�װ͸��� ���ؼ�\n������� �� �Ŵϱ�!");
		}
	, true, 0.5f);
	OpeningEvent->PushEvent([this] {
		OpeningEvent->Portrait2->SetLipAnimation(1.0f);
		OpeningEvent->Dialogue->Text->SetTextAnim(L"��ε�!\n�ε� ���� ���� ������!!");
		}
	, true, 0.5f);
	OpeningEvent->PushEvent([this] {
		OpeningEvent->Dialogue->SetFadeOut(.2f);
		OpeningEvent->SetFadeOut(0.5f);
		BgmPlayer.SoundFadeOut(1.0f);
		}
	, false, 0.6f);

	OpeningEvent->PushEvent([this] {
		OpeningEvent->Background->Off();
		OpeningEvent->Portrait2->Off();
		OpeningEvent->Portrait3->Off();
		OpeningEvent->Portrait4->Off();
		OpeningEvent->SetFadeIn(.5f);
		}
	, false, 0.5f);

	OpeningEvent->SkipFunction = [this] {
		BgmPlayer.SoundFadeOut(0.3f);
	};
}

void Stage10::ClearEventInit()
{
	ClearEvent->PushEvent([this] {
		ClearEvent->SetFadeOut(0.5f);
		}, false, 1.0f);

	ClearEvent->PushEvent([this] {
		GameEngineCore::ChangeLevel("TitleLevel");
		}, false, .6f);

	ClearEvent->SkipFunction = [this] {
		GameEngineCore::ChangeLevel("TitleLevel");
	};
}
