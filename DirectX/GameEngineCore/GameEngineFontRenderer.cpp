#include "PrecompileHeader.h"
#include "GameEngineFontRenderer.h"
#include "GameEngineFont.h"

GameEngineFontRenderer::GameEngineFontRenderer()
{
}

GameEngineFontRenderer::~GameEngineFontRenderer()
{
}

void GameEngineFontRenderer::SetFont(const std::string_view& _Font)
{
	Font = GameEngineFont::Find(_Font);
}

void GameEngineFontRenderer::SetText(const std::string_view& _Text)
{
	Text = GameEngineString::AnsiToUniCode(_Text);
}

void GameEngineFontRenderer::SetText(const std::wstring_view& _Text)
{
	Text = _Text;
}

void GameEngineFontRenderer::Render(float _Delta)
{
	if (nullptr == Font)
	{
		return;
	}

	if (L"" == Text)
	{
		return;
	}

	float4 Pos = GetTransform()->GetWorldPosition();

	GameEngineCamera* Camera = GetCamera();
	Pos *= Camera->GetView();
	Pos *= Camera->GetProjection();
	Pos *= Camera->GetViewPort();

	Font->FontDraw(Text, Pos, FontScale, FontColor, Aligned);

	GameEngineDevice::GetContext()->GSSetShader(nullptr, nullptr, 0);

}

void GameEngineFontRenderer::Start()
{
	PushCameraRender(100);
	//GameEngineRenderer::Start();
}