#pragma once
#include <GameEngineBase/GameEngineRandom.h>


class FERandom
{
public:

	FERandom();
	~FERandom();

	// 0~99 ��ȯ ���� ��ġ�� ��ȯ�� ���� ������ �����Դϴ�.
	static int RandomInt()
	{
		RandomCount++;
		int result = GameEngineRandom::MainRandom.RandomInt(0, 99);
		return result;
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
	static void AddRandomCount(int _Count)
	{
		SetRandomCount(RandomCount + _Count);
	}
	// ���� ���° �������� ��ȯ�մϴ�
	static int GetRandomCount()
	{
		return RandomCount;
	}

	static void SetSeed(int _Seed)
	{
		Seed = _Seed;
		GameEngineRandom::MainRandom.SetSeed(Seed);
	}

	// delete Function
	FERandom(const FERandom& _Other) = delete;
	FERandom(FERandom&& _Other) = delete;
	FERandom& operator=(const FERandom& _Other) = delete;
	FERandom& operator=(FERandom&& _Other) = delete;

protected:

private:
	static int RandomCount;	// ������ ������ Ƚ��
	static int Seed;

	// constructer destructer
};

