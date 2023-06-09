#include "PrecompileHeader.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShader::GameEngineVertexShader()
{
	Type = ShaderType::Vertex;
}

GameEngineVertexShader::~GameEngineVertexShader()
{
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}

void GameEngineVertexShader::ShaderLoad(const std::string_view& _Path
	, const std::string_view& _EntryPoint
	, UINT _VersionHigh /*= 5*/
	, UINT _VersionLow /*= 0*/)
{
	CreateVersion("vs", _VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);

	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	// 상수버퍼에 float4x4 크기의 데이터를 넣으면 
	// 전치된 느낌으로 들어간다.
	// 행렬을 넣을때.

	// 내가 1 2 3 4

	// 쉐이더 1 
	//        2
	//         3
	//         4

	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* Error;

	std::wstring UniCodePath = GameEngineString::AnsiToUniCode(_Path);

	if (S_OK != D3DCompileFromFile
	(
		UniCodePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		EntryPoint.c_str(),
		Version.c_str(),
		Flag,
		0,
		&BinaryCode,
		&Error
	)
		)
	{

		// 에러를 텍스트로 알려줍니다.
		std::string ErrorString = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgAssert(ErrorString);
		return;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader
	(
		BinaryCode->GetBufferPointer(),
		BinaryCode->GetBufferSize(),
		nullptr,
		&ShaderPtr
	)
		)
	{
		MsgAssert("버텍스 쉐이더 핸들 생성에 실패했습니다");
	}

	ShaderResCheck();
}

void GameEngineVertexShader::Setting()
{
	if (nullptr == ShaderPtr)
	{
		MsgAssert("버텍스 쉐이더가 존재하지 않습니다 세팅에 실패했습니다.");
	}

	GameEngineDevice::GetContext()->VSSetShader(ShaderPtr, nullptr, 0);
}