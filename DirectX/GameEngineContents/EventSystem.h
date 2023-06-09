#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include "DialogueSystem.h"
#include "PortraitAnimation.h"

class EventSystem : public GameEngineActor
{
public:
	// constrcuter destructer
	EventSystem();
	~EventSystem();

	// delete Function
	EventSystem(const EventSystem& _Other) = delete;
	EventSystem(EventSystem&& _Other) noexcept = delete;
	EventSystem& operator=(const EventSystem& _Other) = delete;
	EventSystem& operator=(EventSystem&& _Other) noexcept = delete;


	std::shared_ptr<GameEngineUIRenderer> Background = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Foreground = nullptr;
	std::shared_ptr<PortraitAnimation> Portrait1 = nullptr;
	std::shared_ptr<PortraitAnimation> Portrait2 = nullptr;
	std::shared_ptr<PortraitAnimation> Portrait3 = nullptr;
	std::shared_ptr<PortraitAnimation> Portrait4 = nullptr;
	std::shared_ptr<DialogueSystem> Dialogue;
	std::function<void()> SkipFunction;

	void EventStart();
	void PushEvent(std::function<void()> _Function, bool _ButtonCheck = false, float _Timer = 0.0f)
	{
		EventData NewEvent;
		NewEvent.Function = _Function;
		NewEvent.ButtonCheck = _ButtonCheck;
		NewEvent.Timer = _Timer;
		Events.push_back(NewEvent);
	}
	bool GetIsEnd() { return IsEnd; }
	void SetFadeIn(float _Time);
	void SetFadeOut(float _Time);
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void FadeUpdate(float _DeltaTime);
	void Reset();

	struct EventData
	{
		std::function<void()> Function;
		bool ButtonCheck = false;
		float Timer = 0.0f;
	};
	std::vector<EventData> Events;
	size_t EventIndex = 0;
	
	bool IsEnd = false;

	float FadeSpeed = 0.0f;
	float FadeTimer = 0.0f;
	bool IsFadeIn = false;
	bool IsFadeOut = false;
};

