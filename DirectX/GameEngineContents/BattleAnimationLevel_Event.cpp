#include "PrecompileHeader.h"
#include "BattleAnimationLevel.h"
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "ContentsEnum.h"
#include "EventSystem.h"
#include "BattleAnimationUI.h"

void BattleAnimationLevel::NewPlayerDeathEvent(UnitIdentityCode _Code ,std::string _Name, std::vector<std::wstring_view> _Script)
{
	std::shared_ptr<EventSystem> NewEvent = CreateActor<EventSystem>();
	NewEvent->PushEvent([=] {
		UI->Off();
		BgmPlayer.SoundFadeOut(0.5f);
		BgmPlayer = GameEngineSound::Play("DieBGM.mp3");
		BgmPlayer.SetLoop();
		NewEvent->Portrait1->SetTexture("Portrait_" + _Name + ".png");
		NewEvent->Portrait1->On();
		NewEvent->Dialogue->SetSize({ 20, 5 });
		NewEvent->Dialogue->SetFadeIn(0.5f);
		NewEvent->Dialogue->GetTransform()->SetLocalPosition({ -132, -160 });

		}
	, false, 0.5f);

	for (int i = 0; i < _Script.size(); i++)
	{
		NewEvent->PushEvent([=] {
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

void BattleAnimationLevel::NewEnemyDeathEvent(UnitIdentityCode _Code, std::string _Name, std::vector<std::wstring_view> _Script)
{
	std::shared_ptr<EventSystem> NewEvent = CreateActor<EventSystem>();
	NewEvent->PushEvent([=] {
		UI->Off();
		NewEvent->Portrait2->SetTexture("Portrait_" + _Name + ".png");
		NewEvent->Portrait2->On();
		NewEvent->Dialogue->SetSize({ 20, 5 });
		NewEvent->Dialogue->SetFadeIn(0.5f);
		NewEvent->Dialogue->GetTransform()->SetLocalPosition({ -396, -160 });
		}
	, false, 0.5f);

	for (int i = 0; i < _Script.size(); i++)
	{
		NewEvent->PushEvent([=] {
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

void BattleAnimationLevel::NewEncounterEvent(UnitIdentityCode _Code, std::string _Name, std::vector<std::wstring_view> _Script)
{
	std::shared_ptr<EventSystem> NewEvent = CreateActor<EventSystem>();
	NewEvent->PushEvent([=] {
		UI->Off();
		NewEvent->Portrait2->SetTexture("Portrait_" + _Name + ".png");
		NewEvent->Portrait2->On();
		NewEvent->Dialogue->SetSize({ 20, 5 });
		NewEvent->Dialogue->SetFadeIn(0.5f);
		NewEvent->Dialogue->GetTransform()->SetLocalPosition({ -396, -160 });
		}
	, false, 0.5f);

	for (int i = 0; i < _Script.size(); i++)
	{
		NewEvent->PushEvent([=] {
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
	NewPlayerDeathEvent(UnitIdentityCode::Lyn, "Lyn", { L"...���� �� ��\n�̾���... ��ũ...", L"�ٵ�... �뼭����......" });
	NewPlayerDeathEvent(UnitIdentityCode::BladeLordLyn, "Lyn", { L"...���� �� ��\n�̾���... ��ũ...", L"�ٵ�... �뼭����......" });
	NewPlayerDeathEvent(UnitIdentityCode::Kent, "Kent", { L"��... ���� ���ٴ�..." });
	NewPlayerDeathEvent(UnitIdentityCode::Sain, "Sain", { L"���� �Ҹ�ŭ �߾�...\n �ڴ� �ñ��" });
	NewPlayerDeathEvent(UnitIdentityCode::Florina, "Florina", { L"���ƾƾƾ�!!!", L"�� �̾���... ���� �����Ұ�"});
	NewPlayerDeathEvent(UnitIdentityCode::Wil, "Wil", { L"��... ������..."});
	NewPlayerDeathEvent(UnitIdentityCode::Dorcas, "Dorcas", { L"Ū... ������� �ΰ�"});
	NewPlayerDeathEvent(UnitIdentityCode::WarriorDorcas, "Dorcas", { L"Ū... ������� �ΰ�"});
	NewPlayerDeathEvent(UnitIdentityCode::Serra, "Serra", { L"�̷�! ��°�� ���� �����ϴ°ž�?", L"�ϴ� �����Ұ�!"});
	NewPlayerDeathEvent(UnitIdentityCode::Erk, "Erk", { L"��... �뼭���ּ���..\n��� ����߰ھ��"});
	NewPlayerDeathEvent(UnitIdentityCode::Rath, "Rath", { L"�̷�����..."});
	NewPlayerDeathEvent(UnitIdentityCode::Matthew, "Matthew", { L"����... ���ǰ�..."});
	NewPlayerDeathEvent(UnitIdentityCode::AssassinMatthew, "Matthew", { L"����... ���ǰ�..."});
	NewPlayerDeathEvent(UnitIdentityCode::Lucius, "Lucius", { L"�ƾ�... ���̽ÿ�..."});
	NewPlayerDeathEvent(UnitIdentityCode::Ninian, "Ninian", { L"�̾��ؿ�... ��..."});
	NewPlayerDeathEvent(UnitIdentityCode::Wallace, "Wallace", { L"��! ���ʿ� �ʹ� �����߳�����", L"��... �̾��ϴ�"});

	NewEncounterEvent(UnitIdentityCode::Batta, "Batta", { L"�� ��Ÿ���� �̱� �� �����Ŷ�\n�����ϴ°ų�?"});
	NewEnemyDeathEvent(UnitIdentityCode::Batta, "Batta", { L"���� �� ��...\n���� ���ٴ�..."});
	NewEncounterEvent(UnitIdentityCode::Zugu, "Zugu", { L"���ھ�, ��� ���\n�������� �����ϱ��...!"});
	NewEnemyDeathEvent(UnitIdentityCode::Zugu, "Zugu", { L"��, ���ھ�", L"���� �� ���̶��...\n�߾��ݾƾ�..."});
	NewEncounterEvent(UnitIdentityCode::Glass, "Glass", { L"�ʰ� ������ ������ ���ɼ���\n�󸶳� �ȴٰ� �����ϴ°ž�?"});
	NewEnemyDeathEvent(UnitIdentityCode::Glass, "Glass", { L"��... ��... ����"});
	NewEncounterEvent(UnitIdentityCode::Migal, "Migal", { L"������!", L"���� �ͼ� ����ص�\n�뼭 ����!"});
	NewEnemyDeathEvent(UnitIdentityCode::Migal, "Migal", { L"��... ��ȸ�ϰ� ���ָ�...", L"�� ������... ���÷� ��������\n������ ���̴�."});
	NewEncounterEvent(UnitIdentityCode::Carjiga, "Carjiga", { L"�̳༮ ���ϴ�..\n���� ������ �ҷ���!"});
	NewEnemyDeathEvent(UnitIdentityCode::Carjiga, "Carjiga", { L"����..."});
	NewEncounterEvent(UnitIdentityCode::Bool, "Bool", { L"�̳༮�� ����� �������...", L"���� ó���ϰڴ�!"});
	NewEnemyDeathEvent(UnitIdentityCode::Bool, "Bool", { L"�̷�����... ���׷���..."});
	NewEncounterEvent(UnitIdentityCode::Yogi, "Yogi", { L"�� �ϴ°�!\n� �����ָ� ��ƶ�!"});
	NewEnemyDeathEvent(UnitIdentityCode::Yogi, "Yogi", { L"�̷�����... ���׷���..."});
	NewEncounterEvent(UnitIdentityCode::Eagler, "Eagler", { L"���ฦ ��Ī�ϴ� �༮��\n�� �̱۷��� ó���Ѵ�!"});
	NewEnemyDeathEvent(UnitIdentityCode::Eagler, "Eagler", { L"� ����...", L"���۴���...\nŰ�ƶ��� ��Ź�Ѵ�..."});
	NewEncounterEvent(UnitIdentityCode::Lundgren, "Lundgren", { L"�� ������\n�������� ���ͼ���...", L"��Ƽ� ���⼭\n������ ������ ����!"});
	NewEnemyDeathEvent(UnitIdentityCode::Lundgren, "Lundgren", { L"�߸��� ������ ����...\n���ڴ� ���� ���ε�..."});

}

