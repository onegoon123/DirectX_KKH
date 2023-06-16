#include "PrecompileHeader.h"
#include "FECore.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineResource.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineFont.h>
#include "TitleLevel.h"
#include "BattleAnimationLevel.h"
#include "FERandom.h"
#include "DebugWindow.h"
#include "StageSelectWindow.h"

#include "Stage0.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Stage5.h"
#include "Stage6.h"
#include "Stage7.h"
#include "Stage8.h"
#include "Stage9.h"
#include "Stage10.h"

FECore::FECore()
{
}

FECore::~FECore()
{
}

void FECore::GameStart()
{
	new int();
	ResourcesCreate();

	GameEngineGUI::GUIWindowCreate<DebugWindow>("DebugWindow");
	GameEngineGUI::GUIWindowCreate<StageSelectWindow>("StageSelectWindow");

	std::shared_ptr<StageSelectWindow> Window = GameEngineGUI::FindGUIWindowConvert<StageSelectWindow>("StageSelectWindow");
	{
		if (nullptr == Window)
		{
			MsgAssert("������ ���� ����");
		}

		Window->Funcions = [](int i) {
			GameEngineCore::ChangeLevel("Stage" + std::to_string(i));
		};

	}


	FERandom::SetSeed(0);
	GameEngineCore::CreateLevel<TitleLevel>();
	GameEngineCore::CreateLevel<BattleAnimationLevel>();
	GameEngineCore::CreateLevel<Stage0>();
	GameEngineCore::CreateLevel<Stage1>();
	GameEngineCore::CreateLevel<Stage2>();
	GameEngineCore::CreateLevel<Stage3>();
	GameEngineCore::CreateLevel<Stage4>();
	GameEngineCore::CreateLevel<Stage5>();
	GameEngineCore::CreateLevel<Stage6>();
	GameEngineCore::CreateLevel<Stage7>();
	GameEngineCore::CreateLevel<Stage8>();
	GameEngineCore::CreateLevel<Stage9>();
	GameEngineCore::CreateLevel<Stage10>();
	GameEngineCore::ChangeLevel("TitleLevel");
}

void FECore::GameEnd()
{

}

void FECore::ResourcesCreate()
{
	GameEngineDirectory NewDir;
	NewDir.MoveParentToDirectory("ContentResources");
	NewDir.Move("ContentResources");
	NewDir.Move("Shader");

	std::shared_ptr<GameEnginePixelShader> Shader = GameEnginePixelShader::Load(NewDir.GetPlusFileName("EffectPixelShader.hlsl").GetFullPath(), "Texture_PS");
	std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTextureEffect");

	//Pipe->SetVertexBuffer("Rect");
	//Pipe->SetIndexBuffer("Rect");
	Pipe->SetVertexShader("TextureShader.hlsl");
	Pipe->SetRasterizer("Engine2DBase");
	Pipe->SetPixelShader("EffectPixelShader.hlsl");
	Pipe->SetBlendState("AlphaBlend");
	Pipe->SetDepthState("EngineDepth");

	GameEngineFont::Load("Silhoua14");
}
