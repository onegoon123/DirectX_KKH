#pragma once
#include <GameEngineBase/GameEngineRandom.h>
static const int Seed = 0;
class FERandom
{
public:
	// constructer destructer
	FERandom()
	{
		GameEngineRandom::MainRandom.SetSeed(Seed);
	}
	~FERandom() {}

	// 0~99 ��ȯ ���� ��ġ�� ��ȯ�� ���� ������ �����Դϴ�.
	static int RandomInt()
	{
		RandomCount++;
		return GameEngineRandom::MainRandom.RandomInt(0, 99);
	}
	// ������ _Count��° ������ �����մϴ�
	static void SetRandomCount(int _Count)
	{
		RandomCount = 0;
		GameEngineRandom::MainRandom.SetSeed(Seed);
		for (int i = 0; i < _Count; i++)
		{
			RandomInt();
		}
	}
	// ���� ���° �������� ��ȯ�մϴ�
	static int GetRandomCount()
	{
		return RandomCount;
	}

	// delete Function
	FERandom(const FERandom& _Other) = delete;
	FERandom(FERandom&& _Other) = delete;
	FERandom& operator=(const FERandom& _Other) = delete;
	FERandom& operator=(FERandom&& _Other) = delete;

protected:

private:
	static int RandomCount;	// ������ ������ Ƚ��
};

