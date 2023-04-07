#pragma once
#include <string>
#include "Stat.h"
// ���� Ŭ����
// ��Ʋ �� ȭ�鿡 ��Ÿ�� �÷��̾�, ��, ��Ÿ ������Ʈ�� �θ� Ŭ����
class Unit
{
public:
	// constructer destructer
	Unit();
	~Unit();

	

	// delete Function
	Unit(const Unit& _Other) = delete;
	Unit(Unit&& _Other) = delete;
	Unit& operator=(const Unit& _Other) = delete;
	Unit& operator=(Unit&& _Other) = delete;

protected:

private:
	int IdentityCode = 0;
	std::string UnitName = "";
	Stat UnitStat;
};

