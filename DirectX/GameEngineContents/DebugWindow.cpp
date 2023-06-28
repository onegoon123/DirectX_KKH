#include "PrecompileHeader.h"
#include "DebugWindow.h"
#include <GameEngineBase/GameEngineString.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "MapCursor.h"
#include "FERandom.h"
DebugWindow::DebugWindow() 
{
}

DebugWindow::~DebugWindow() 
{
}

void DebugWindow::OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime)
{
	if (Text == "") { return; }
	ImGui::Text(GameEngineString::AnsiToUTF8(Text).c_str());
	ImGui::Text(GameEngineString::AnsiToUTF8("���۹�\n �̵� : ����Ű\n Ȯ�� : z  ��� : x  �������� : a  �������� : s\n").c_str());
	ImGui::Text(GameEngineString::AnsiToUTF8("ġƮ ���\n").c_str());
	ImGui::Text(GameEngineString::AnsiToUTF8("F1: ���ΰ� �����̵�, F2: �������� ���̱�, F3: ���ΰ� ����\nF4: �������� ����Ŭ����, 1: �������� ������").c_str());
	
	// ���콺 ��ǥ ��ī������ ��ȯ
	float4 MousePos = GameEngineInput::GetMousePosition();
	float4 LocalPos = float4(MousePos.x - 480, 320 - MousePos.y);
	ImGui::Text(LocalPos.ToString().data());

	if (nullptr == Cursor) { return; }
	ImGui::Text(Cursor->WorldPos.ToString().data());

	static std::vector<int> Frames;
	static int FrameAverage;
	static float Timer = 0;
	Timer += _DeltaTime;
	Frames.push_back(static_cast<int>(1 / _DeltaTime));
	if (1.0f < Timer)
	{
		int Sum = 0;
		for (int Num : Frames)
		{
			Sum += Num;
		}
		FrameAverage = Sum / static_cast<int>(Frames.size());
		Frames.clear();
		Timer = 0;
	}

	ImGui::Text((std::to_string(FrameAverage) + " fps").data());
	ImGui::Text(("RandomCount: " + std::to_string(FERandom::GetRandomCount())).data());

}

