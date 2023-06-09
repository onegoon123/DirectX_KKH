#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "ContentsEnum.h"
// ���� :
class NumberActor : public GameEngineActor
{
public:
	// constrcuter destructer
	NumberActor();
	~NumberActor();

	// delete Function
	NumberActor(const NumberActor& _Other) = delete;
	NumberActor(NumberActor&& _Other) noexcept = delete;
	NumberActor& operator=(const NumberActor& _Other) = delete;
	NumberActor& operator=(NumberActor&& _Other) noexcept = delete;
	
	void NumberCreate()
	{
		NumberCreate(RenderOrder::UIText);
	}
	template <typename EnumType>
	void NumberCreate(EnumType _Order)
	{
		NumberCreate(static_cast<int>(_Order));
	}
	void NumberCreate(int _Order);

	void Setting(int _Value);
	void SetValue(int _Value, bool _ChangeSize = false);
	void SetValueLerp(int _Value);
	void StopLerp()
	{
		IsLerp = false;
	}
	void SetBlackFont();
	void SetDamageFont();
	bool GetIsLerp()
	{
		return IsLerp;
	}

	int GetValue()
	{
		return Value;
	}

	void SetTime(float _Time)
	{
		Time = _Time;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	std::vector<std::shared_ptr<class GameEngineUIRenderer>> Renders;

	int Value = 0;
	int TargetValue = 0;
	float Time = 0.05f;
	float Timer = 0;
	bool IsLerp = false;
	bool IsPlus = false;
};

