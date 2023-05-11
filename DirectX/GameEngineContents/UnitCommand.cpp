#include "PrecompileHeader.h"
#include "UnitCommand.h"
#include "FERandom.h"
std::list<UnitCommand> UnitCommand::CommandList = std::list<UnitCommand>();

UnitCommand::UnitCommand()
{
}

UnitCommand::~UnitCommand()
{
}

std::list<AttackCommand> UnitCommand::Attack(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit)
{
	std::list<AttackCommand> AttackList;
	UnitCommand CommandRecord;
	Unit SubjectUnit = Unit(_SubjectUnit->GetUnitData());
	Unit TargetUnit = Unit(_TargetUnit->GetUnitData());

	CommandRecord.TypeValue = CommandType::Attack;
	CommandRecord.BeforeSubjectUnit = Unit(SubjectUnit);
	CommandRecord.BeforeTargetUnit = Unit(TargetUnit);
	CommandRecord.BeforeSubjectUnitPos = _SubjectUnit->GetBeforeMapPos();
	CommandRecord.AfterSubjectUnitPos = _SubjectUnit->GetMapPos();
	CommandRecord.Record = std::string(_SubjectUnit->GetName()) + "��(��) �����ߴ�.";

	if (nullptr != SubjectUnit.GetCurWeapon())
	{
		AttackList.push_back(AttackCalculation(SubjectUnit, TargetUnit));
		CommandRecord.RandomNum += 2;

		if (true == TargetUnit.GetIsDie())
		{
			CommandRecord.AfterSubjectUnit = SubjectUnit;
			CommandRecord.AfterSubjectUnit.SetIsTurnEnd(true);
			CommandRecord.AfterTargetUnit = TargetUnit;
			CommandList.push_back(CommandRecord);
			return AttackList;
		}
	}

	if (nullptr != TargetUnit.GetCurWeapon())
	{
		AttackList.push_back(AttackCalculation(TargetUnit, SubjectUnit).ChangeOrder());
		CommandRecord.RandomNum += 2;

		if (true == SubjectUnit.GetIsDie())
		{
			CommandRecord.AfterSubjectUnit = SubjectUnit;
			CommandRecord.AfterSubjectUnit.SetIsTurnEnd(true);
			CommandRecord.AfterTargetUnit = TargetUnit;
			CommandList.push_back(CommandRecord);
			return AttackList;
		}
	}


	if (TargetUnit.GetAttackSpeedPoint() + 4 <= SubjectUnit.GetAttackSpeedPoint())
	{
		if (nullptr != SubjectUnit.GetCurWeapon())
		{
			AttackList.push_back(AttackCalculation(SubjectUnit, TargetUnit));
			CommandRecord.RandomNum += 2;
		}
	}
	else if (SubjectUnit.GetAttackSpeedPoint() + 4 <= TargetUnit.GetAttackSpeedPoint())
	{
		if (nullptr != TargetUnit.GetCurWeapon())
		{
			AttackList.push_back(AttackCalculation(TargetUnit, SubjectUnit).ChangeOrder());
			CommandRecord.RandomNum += 2;
		}
	}

	CommandRecord.AfterSubjectUnit = SubjectUnit;
	CommandRecord.AfterSubjectUnit.SetIsTurnEnd(true);
	CommandRecord.AfterTargetUnit = TargetUnit;
	CommandList.push_back(CommandRecord);
	return AttackList;
}

AttackCommand UnitCommand::AttackCalculation(Unit& _SubjectUnit, Unit& _TargetUnit)
{

	AttackCommand NewAttack;

	// ���� ȸ�� ����
	int UnitHit = _SubjectUnit.GetHitPoint();
	int TargetDodge = _TargetUnit.GetDodgePoint();

	// ���� ��
	int Triangle = 0;
	int TriangleDamage = 0;
	int TriangleHit = 0;

	if (nullptr != _TargetUnit.GetCurWeapon())
	{
		Triangle = Weapon::GetWeaponeTriangle(_SubjectUnit.GetCurWeapon(), _TargetUnit.GetCurWeapon());
		TriangleDamage = Triangle;
		TriangleHit = Triangle * 15;
	}

	// ���߷�, ġ��Ÿ Ȯ�� ���
	int HitPercentage = UnitHit + TriangleHit - TargetDodge;
	int CriticalPercentage = _SubjectUnit.GetCriticalPoint() - _TargetUnit.GetCriticalDodgePoint();

	NewAttack.IsHit = FERandom::RandomInt() < HitPercentage;
	NewAttack.IsCritical = FERandom::RandomInt() < CriticalPercentage;

	// ���ݷ� ���
	int Damage = _SubjectUnit.GetAttackPoint(_TargetUnit.GetClassValue()) + TriangleDamage;	// �󼺿� ���� ����� ����
	Damage -= _TargetUnit.GetDefPoint();	// ���¿� ���� ��ġ ����, ���� ��ġ ����
	Damage *= NewAttack.IsCritical ? 3 : 1;	// ġ��Ÿ �� 3��� ����

	// ������� 0���� �϶�
	if (0 >= Damage)
	{
		// No Damage
		Damage = 0;
	}

	if (true == NewAttack.IsHit)
	{
		_TargetUnit.Damage(Damage);
		_SubjectUnit.GetCurWeapon()->Use();
	}

	NewAttack.TargetUnit = _TargetUnit;
	NewAttack.SubjectUnit = _SubjectUnit;

	return NewAttack;
}

void UnitCommand::Wait(std::shared_ptr<BattleUnit> _SubjectUnit)
{
	UnitCommand CommandRecord;
	CommandRecord.TypeValue = CommandType::Wait;
	CommandRecord.BeforeSubjectUnit = Unit(_SubjectUnit->GetUnitData());
	CommandRecord.AfterSubjectUnit = CommandRecord.BeforeSubjectUnit;
	CommandRecord.AfterSubjectUnit.SetIsTurnEnd(true);
	CommandRecord.BeforeSubjectUnitPos = _SubjectUnit->GetBeforeMapPos();
	CommandRecord.AfterSubjectUnitPos = _SubjectUnit->GetMapPos();
	CommandRecord.Record = std::string(_SubjectUnit->GetName()) + "��(��) ����ߴ�";
	CommandList.push_back(CommandRecord);
}

void UnitCommand::PhaseStart(Faction _Faction)
{
	UnitCommand CommandRecord;
	switch (_Faction)
	{
	case Faction::None:
	{
		MsgAssert("Faction�� �������� �ʾҽ��ϴ�.");
		break;
	}
	case Faction::Player:
		CommandRecord.TypeValue = CommandType::PlayerPhaseStart;
		CommandRecord.Record = "PLAYER PHASE ����";
		break;
	case Faction::Enemy:
		CommandRecord.TypeValue = CommandType::EnemyPhaseStart;
		CommandRecord.Record = "ENEMY PHASE ����";
		break;
	default:
		break;
	}
	CommandList.push_back(CommandRecord);
}

