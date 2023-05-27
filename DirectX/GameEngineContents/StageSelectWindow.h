#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <functional>
// ���� :
class StageSelectWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	StageSelectWindow();
	~StageSelectWindow();

	// delete Function
	StageSelectWindow(const StageSelectWindow& _Other) = delete;
	StageSelectWindow(StageSelectWindow&& _Other) noexcept = delete;
	StageSelectWindow& operator=(const StageSelectWindow& _Other) = delete;
	StageSelectWindow& operator=(StageSelectWindow&& _Other) noexcept = delete;

	std::vector<std::function<void()>> Funcions = std::vector<std::function<void()>>(10);

	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;

protected:

private:

};

