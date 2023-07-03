#include "PrecompileHeader.h"
#include "BattleAnimationLevel.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
#include "EventSystem.h"
#include "BattleAnimationUI.h"

void BattleAnimationLevel::NewPlayerDeathEvent(UnitIdentityCode _Code, std::vector<std::wstring_view> _Script)
{
	std::shared_ptr<EventSystem> NewEvent = CreateActor<EventSystem>();
	NewEvent->PushEvent([=] {
		UI->Off();
		BgmPlayer.SoundFadeOut(0.5f);
		BgmPlayer = GameEngineSound::Play("DieBGM.mp3");
		BgmPlayer.SetLoop();
		NewEvent->Portrait1->SetPortrait(_Code);
		NewEvent->Portrait1->On();
		NewEvent->Dialogue->SetSize({ 20, 5 });
		NewEvent->Dialogue->SetFadeIn(0.5f);
		NewEvent->Dialogue->GetTransform()->SetLocalPosition({ -132, -160 });

		}
	, false, 0.5f);

	for (int i = 0; i < _Script.size(); i++)
	{
		NewEvent->PushEvent([=] {
			NewEvent->Portrait1->SetLipAnimation(1.0f);
			NewEvent->Dialogue->Text->SetTextAnim(_Script[i]);
			}
		, true, 0.5f);
	}

	NewEvent->PushEvent([=] {
		TimeEvent.AddEvent(0.1f, std::bind(&BattleAnimationLevel::FadeOut, this, 0.15f));
		TimeEvent.AddEvent(0.4f, std::bind(&BattleAnimationLevel::End, this));
		}
	, false, 0.3f);

	NewEvent->PushEvent([=] {
		NewEvent->Portrait1->Off();
		NewEvent->Dialogue->Off();
		UI->On();
		}
	, false, 0.0f);
	DeathEvent.insert(std::pair<UnitIdentityCode, std::shared_ptr<EventSystem>>(_Code, NewEvent));
}

void BattleAnimationLevel::NewEnemyDeathEvent(UnitIdentityCode _Code, std::vector<std::wstring_view> _Script)
{
	std::shared_ptr<EventSystem> NewEvent = CreateActor<EventSystem>();
	NewEvent->PushEvent([=] {
		UI->Off();
		NewEvent->Portrait2->SetPortrait(_Code);
		NewEvent->Portrait2->On();
		NewEvent->Dialogue->SetSize({ 20, 5 });
		NewEvent->Dialogue->SetFadeIn(0.5f);
		NewEvent->Dialogue->GetTransform()->SetLocalPosition({ -396, -160 });
		}
	, false, 0.5f);

	for (int i = 0; i < _Script.size(); i++)
	{
		NewEvent->PushEvent([=] {
			NewEvent->Portrait2->SetLipAnimation(1.0f);
			NewEvent->Dialogue->Text->SetTextAnim(_Script[i]);
			}
		, true, 0.5f);
	}

	NewEvent->PushEvent([=] {
		TimeEvent.AddEvent(0.1f, std::bind(&BattleAnimationLevel::FadeOut, this, 0.15f));
		TimeEvent.AddEvent(0.4f, std::bind(&BattleAnimationLevel::End, this));
		}
	, false, 0.3f);

	NewEvent->PushEvent([=] {
		NewEvent->Portrait2->Off();
		NewEvent->Dialogue->Off();
		UI->On();
		}
	, false, 0.0f);
	DeathEvent.insert(std::pair<UnitIdentityCode, std::shared_ptr<EventSystem>>(_Code, NewEvent));
}

void BattleAnimationLevel::NewEncounterEvent(UnitIdentityCode _Code, std::vector<std::wstring_view> _Script)
{
	std::shared_ptr<EventSystem> NewEvent = CreateActor<EventSystem>();
	NewEvent->PushEvent([=] {
		UI->Off();
		NewEvent->Portrait2->SetPortrait(_Code);
		NewEvent->Portrait2->On();
		NewEvent->Dialogue->SetSize({ 20, 5 });
		NewEvent->Dialogue->SetFadeIn(0.5f);
		NewEvent->Dialogue->GetTransform()->SetLocalPosition({ -396, -160 });
		}
	, false, 0.5f);

	for (int i = 0; i < _Script.size(); i++)
	{
		NewEvent->PushEvent([=] {
			NewEvent->Portrait2->SetLipAnimation(1.0f);
			NewEvent->Dialogue->Text->SetTextAnim(_Script[i]);
			}
		, true, 0.5f);
	}

	NewEvent->PushEvent([=] {
		NewEvent->Portrait2->Off();
		NewEvent->Dialogue->Off();
		UI->On();
		PlayAttack();
		}
	, false, 0.0f);
	EncounterEvent.insert(std::pair<UnitIdentityCode, std::shared_ptr<EventSystem>>(_Code, NewEvent));
}

void BattleAnimationLevel::EventInit()
{
	NewPlayerDeathEvent(UnitIdentityCode::Lyn, { L"...���� �� ��\n�̾���... ��ũ...", L"�ٵ�... �뼭����......" });
	NewPlayerDeathEvent(UnitIdentityCode::BladeLordLyn, { L"...���� �� ��\n�̾���... ��ũ...", L"�ٵ�... �뼭����......" });
	NewPlayerDeathEvent(UnitIdentityCode::Kent, { L"��... ���� ���ٴ�..." });
	NewPlayerDeathEvent(UnitIdentityCode::Sain, { L"���� �Ҹ�ŭ �߾�...\n �ڴ� �ñ��" });
	NewPlayerDeathEvent(UnitIdentityCode::Florina, { L"���ƾƾƾ�!!!", L"�� �̾���... ���� �����Ұ�" });
	NewPlayerDeathEvent(UnitIdentityCode::Wil, { L"��... ������..." });
	NewPlayerDeathEvent(UnitIdentityCode::Dorcas, { L"Ū... ������� �ΰ�" });
	NewPlayerDeathEvent(UnitIdentityCode::WarriorDorcas, { L"Ū... ������� �ΰ�" });
	NewPlayerDeathEvent(UnitIdentityCode::Serra, { L"�̷�! ��°�� ���� �����ϴ°ž�?", L"�ϴ� �����Ұ�!" });
	NewPlayerDeathEvent(UnitIdentityCode::Erk, { L"��... �뼭���ּ���..\n��� ����߰ھ��" });
	NewPlayerDeathEvent(UnitIdentityCode::Rath, { L"�̷�����..." });
	NewPlayerDeathEvent(UnitIdentityCode::Matthew, { L"����... ���ǰ�..." });
	NewPlayerDeathEvent(UnitIdentityCode::AssassinMatthew, { L"����... ���ǰ�..." });
	NewPlayerDeathEvent(UnitIdentityCode::Lucius, { L"�ƾ�... ���̽ÿ�..." });
	NewPlayerDeathEvent(UnitIdentityCode::Ninian, { L"�̾��ؿ�... ��..." });
	NewPlayerDeathEvent(UnitIdentityCode::Wallace, { L"��! ���ʿ� �ʹ� �����߳�����", L"��... �̾��ϴ�" });

	NewEncounterEvent(UnitIdentityCode::Batta, { L"�� ��Ÿ���� �̱� �� �����Ŷ�\n�����ϴ°ų�?" });
	NewEnemyDeathEvent(UnitIdentityCode::Batta, { L"���� �� ��...\n���� ���ٴ�..." });
	NewEncounterEvent(UnitIdentityCode::Zugu, { L"���ھ�, ��� ���\n�������� �����ϱ��...!" });
	NewEnemyDeathEvent(UnitIdentityCode::Zugu, { L"��, ���ھ�", L"���� �� ���̶��...\n�߾��ݾƾ�..." });
	NewEncounterEvent(UnitIdentityCode::Glass, { L"�ʰ� ������ �̱� ���ɼ���\n�󸶳� �ȴٰ� �����ϴ°ž�?" });
	NewEnemyDeathEvent(UnitIdentityCode::Glass, { L"��... ��... ����" });
	NewEncounterEvent(UnitIdentityCode::Migal, { L"������!", L"���� �ͼ� ����ص�\n�뼭 ����!" });
	NewEnemyDeathEvent(UnitIdentityCode::Migal, { L"��... ��ȸ�ϰ� ���ָ�...", L"�� ������... ���÷� ��������\n������ ���̴�." });
	NewEncounterEvent(UnitIdentityCode::Carjiga, { L"�̳༮ ���ϴ�..\n���� ������ �ҷ���!" });
	NewEnemyDeathEvent(UnitIdentityCode::Carjiga, { L"����..." });
	NewEncounterEvent(UnitIdentityCode::Bool, { L"�̳༮�� ����� �������...", L"���� ó���ϰڴ�!" });
	NewEnemyDeathEvent(UnitIdentityCode::Bool, { L"�̷�����... ���׷���..." });
	NewEncounterEvent(UnitIdentityCode::Yogi, { L"�� �ϴ°�!\n� �����ָ� ��ƶ�!" });
	NewEnemyDeathEvent(UnitIdentityCode::Yogi, { L"�̷�����... ���׷���..." });
	NewEncounterEvent(UnitIdentityCode::Eagler, { L"���ฦ ��Ī�ϴ� �༮��\n�� �̱۷��� ó���Ѵ�!" });
	NewEnemyDeathEvent(UnitIdentityCode::Eagler, { L"� ����...", L"���۴���...\nŰ�ƶ��� ��Ź�Ѵ�..." });
	NewEncounterEvent(UnitIdentityCode::Lundgren, { L"�� ������\n�������� ���ͼ���...", L"��Ƽ� ���⼭\n������ ������ ����!" });
	NewEnemyDeathEvent(UnitIdentityCode::Lundgren, { L"�߸��� ������ ����...\n���ڴ� ���� ���ε�..." });

}

