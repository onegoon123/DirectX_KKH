#pragma once
#include <string>
#include <math.h>
#include <GameEngineBase/GameEngineMath.h>
class int2
{
public:
	static const int2 Left;
	static const int2 Right;
	static const int2 Up;
	static const int2 Down;
	static const int2 Zero;

public:
	int x = 0;
	int y = 0;

	int2();
	int2(int _x);
	int2(int _x, int _y);
	~int2();

	bool IsZero() const
	{
		return x == 0 && y == 0;
	}

	int2 operator+(const int2& _Other) const
	{
		int2 Copy = int2();
		Copy.x = this->x + _Other.x;
		Copy.y = this->y + _Other.y;
		return Copy;
	}

	int2 operator-(const int2& _Other) const
	{
		int2 Copy = int2();
		Copy.x = this->x - _Other.x;
		Copy.y = this->y - _Other.y;
		return Copy;
	}

	int2 operator*(const int _Value) const
	{
		int2 Copy = int2();
		Copy.x = this->x * _Value;
		Copy.y = this->y * _Value;
		return Copy;
	}

	int2 operator*(const float _Value) const
	{
		int2 Copy = int2();
		Copy.x = static_cast<int>(this->x * _Value);
		Copy.y = static_cast<int>(this->y * _Value);
		return Copy;
	}

	int2& operator+=(const int2& _Other)
	{
		this->x += _Other.x;
		this->y += _Other.y;
		return *this;
	}

	int2& operator-=(const int2& _Other)
	{
		this->x -= _Other.x;
		this->y -= _Other.y;
		return *this;
	}

	int2& operator*=(const int _Value)
	{
		this->x *= _Value;
		this->y *= _Value;
		return *this;
	}

	int2& operator*=(const float _Value)
	{
		this->x = static_cast<int>(this->x * _Value);
		this->y = static_cast<int>(this->y * _Value);
		return *this;
	}

	bool operator==(const int2& _Other) const
	{
		return this->x == _Other.x && this->y == _Other.y;
	}

	bool operator!=(const int2& _Other) const
	{
		return !(*this == _Other);
	}

	int GetDistance(const int2& _Other) const
	{
		return abs(this->x - _Other.x) + abs(this->y - _Other.y);
	}

	static int GetDistance(const int2& _This, const int2& _Other)
	{
		return abs(_This.x - _Other.x) + abs(_This.y - _Other.y);
	}

	static int2 Float4ToInt2(const float4& _Value)
	{
		return int2(static_cast<int>(_Value.x), static_cast<int>(_Value.y));
	}

	int2 Normalize()
	{
		int2 Return = int2(x, y);
		Return.x = std::min<int>(std::max<int>(x, -1), 1);
		Return.y = std::min<int>(std::max<int>(y, -1), 1);
		return Return;
	}

	std::string ToString()
	{
		char ArrReturn[256];

		sprintf_s(ArrReturn, "x: %d, y: %d", x, y);

		return std::string(ArrReturn);
	}
	operator float4() const
	{
		return float4(static_cast<float>(x), static_cast<float>(y));
	}
protected:

private:

};