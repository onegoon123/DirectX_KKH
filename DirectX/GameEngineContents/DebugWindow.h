#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class DebugWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	DebugWindow();
	~DebugWindow();

	// delete Function
	DebugWindow(const DebugWindow& _Other) = delete;
	DebugWindow(DebugWindow&& _Other) noexcept = delete;
	DebugWindow& operator=(const DebugWindow& _Other) = delete;
	DebugWindow& operator=(DebugWindow&& _Other) noexcept = delete;

	std::string Text = "���� ����";
	std::shared_ptr<class MapCursor> Cursor = nullptr;

	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;

protected:

private:

};

