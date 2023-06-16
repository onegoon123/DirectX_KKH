#include "PrecompileHeader.h"
#include "GameEngineFont.h"


IFW1Factory* GameEngineFont::Factory = nullptr;

class FontFactoryCreator
{
public:
	FontFactoryCreator()
	{
		FW1CreateFactory(FW1_VERSION, &GameEngineFont::Factory);
	}

	~FontFactoryCreator()
	{
		if (nullptr != GameEngineFont::Factory)
		{
			// �ٽ� ����Ҷ� ����ִٴ°��� �˷��ֱ� ���ؼ�
			// ���α׷��� ����ɶ� �Ǵ°�.
			GameEngineFont::Factory->Release();
			GameEngineFont::Factory = nullptr;
		}
	}
};

FontFactoryCreator InitFont;

GameEngineFont::GameEngineFont()
{
}

GameEngineFont::~GameEngineFont()
{
	if (nullptr != Font)
	{
		Font->Release();
		Font = nullptr;
	}

}

void GameEngineFont::LoadFont(const std::string_view& _Path)
{
	std::wstring WPath = GameEngineString::AnsiToUniCode(_Path.data());

	if (S_OK != GameEngineFont::Factory->CreateFontWrapper(GameEngineDevice::GetDevice(), WPath.c_str(), &Font))
	{
		MsgAssert("��Ʈ ���� ����");
		return;
	}
}

void GameEngineFont::FontDraw(const std::string_view& _Text, const float4& _Pos, float _FontScale, const float4& _Color)
{
	FontDraw(_Text, _Pos, _FontScale, _Color, FontAligned::Center);
}

void GameEngineFont::FontDraw(const std::string_view& _Text, const float4& _Pos, float _FontScale, const float4& _Color, FontAligned _Aligned)
{
	std::wstring Text = GameEngineString::AnsiToUniCode(_Text);

	float4 Color = { 1.0f, 0.0f, 0.0f, 1.0f };
	FW1_TEXT_FLAG Aligned;
	switch (_Aligned)
	{
	case FontAligned::Left:
		Aligned = FW1_LEFT;
		break;
	case FontAligned::Center:
		Aligned = FW1_CENTER;
		break;
	case FontAligned::Right:
		Aligned = FW1_RIGHT;
		break;
	case FontAligned::Top:
		Aligned = FW1_TOP;
		break;
	case FontAligned::Bottom:
		Aligned = FW1_BOTTOM;
		break;
	default:
		break;
	}
	Font->DrawString(GameEngineDevice::GetContext(), Text.c_str(), _FontScale, _Pos.x, _Pos.y, _Color.ColorToUint(), Aligned);
}
