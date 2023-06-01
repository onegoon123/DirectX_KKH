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
	ImGui::Text(GameEngineString::AnsiToUTF8(Text).c_str());
	ImGui::Text(GameEngineString::AnsiToUTF8("조작법\n 이동 : 방향키\n 확인 : z  취소 : x  다음유닛 : a  유닛정보 : s\n").c_str());
	
	// 마우스 좌표 데카르르로 변환
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

}

