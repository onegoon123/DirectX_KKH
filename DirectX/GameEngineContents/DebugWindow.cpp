#include "PrecompileHeader.h"
#include "DebugWindow.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "MapCursor.h"
DebugWindow::DebugWindow() 
{
}

DebugWindow::~DebugWindow() 
{
}

void DebugWindow::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	if (Text == "") { return; }
	ImGui::Text(GameEngineString::AnsiToUTF8("���۹�\n �̵� : ����Ű\n Ȯ�� : z  ��� : x  �������� : a  �������� : s\n").c_str());
	ImGui::Text(GameEngineString::AnsiToUTF8(Text).c_str());
	
	float4 MousePos = GameEngineInput::GetMousePosition();
	float4 LocalPos = float4(MousePos.x - 480, 320 - MousePos.y);
	ImGui::Text(LocalPos.ToString().data());

	if (nullptr == Cursor) { return; }
	ImGui::Text(Cursor->WorldPos.ToString().data());
}

