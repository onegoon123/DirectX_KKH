#pragma once
#include <GameEngineCore/GameEngineActor.h>
// ���� :
// ������ �������� ǥ���ϱ����� ����
class StatBar : public GameEngineActor
{
public:
	// constrcuter destructer
	StatBar();
	~StatBar();

	// delete Function
	StatBar(const StatBar& _Other) = delete;
	StatBar(StatBar&& _Other) noexcept = delete;
	StatBar& operator=(const StatBar& _Other) = delete;
	StatBar& operator=(StatBar&& _Other) noexcept = delete;

	void SetSize(float _Value);
	void SetValue(float _Value);

protected:
	void Start() override;
private:
	std::shared_ptr<class GameEngineUIRenderer> Left = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Center = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Fill = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Right = nullptr;
};

