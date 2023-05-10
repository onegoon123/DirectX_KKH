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

	if (nullptr != SubjectUnit.UnitStat.EquipWeapon)
	{
		AttackList.push_back(AttackCalculation(SubjectUnit, TargetUnit));
		CommandRecord.RandomNum += 2;

		if (true == TargetUnit.IsDie)
		{
			CommandRecord.AfterSubjectUnit = SubjectUnit;
			CommandRecord.AfterSubjectUnit.IsTurnEnd = true;
			CommandRecord.AfterTargetUnit = TargetUnit;
			CommandList.push_back(CommandRecord);
			return AttackList;
		}
	}

	if (nullptr != TargetUnit.UnitStat.EquipWeapon)
	{
		AttackList.push_back(AttackCalculation(TargetUnit, SubjectUnit).ChangeOrder());
		CommandRecord.RandomNum += 2;

		if (true == SubjectUnit.IsDie)
		{
			CommandRecord.AfterSubjectUnit = SubjectUnit;
			CommandRecord.AfterSubjectUnit.IsTurnEnd = true;
			CommandRecord.AfterTargetUnit = TargetUnit;
			CommandList.push_back(CommandRecord);
			return AttackList;
		}
	}


	if (TargetUnit.UnitStat.GetAttackSpeedPoint() + 4 <= SubjectUnit.UnitStat.GetAttackSpeedPoint())
	{
		if (nullptr != SubjectUnit.UnitStat.EquipWeapon)
		{
			AttackList.push_back(AttackCalculation(SubjectUnit, TargetUnit));
			CommandRecord.RandomNum += 2;
		}
	}
	else if (SubjectUnit.UnitStat.GetAttackSpeedPoint() + 4 <= TargetUnit.UnitStat.GetAttackSpeedPoint())
	{
		if (nullptr != TargetUnit.UnitStat.EquipWeapon)
		{
			AttackList.push_back(AttackCalculation(TargetUnit, SubjectUnit).ChangeOrder());
			CommandRecord.RandomNum += 2;
		}
	}

	CommandRecord.AfterSubjectUnit = SubjectUnit;
	CommandRecord.AfterSubjectUnit.IsTurnEnd = true;
	CommandRecord.AfterTargetUnit = TargetUnit;
	CommandList.push_back(CommandRecord);
	return AttackList;
}

AttackCommand UnitCommand::AttackCalculation(Unit& _SubjectUnit, Unit& _TargetUnit)
{

	AttackCommand NewAttack;

	// ���� ȸ�� ����
	int UnitHit = _SubjectUnit.UnitStat.GetHitPoint();
	int TargetDodge = _TargetUnit.UnitStat.GetDodgePoint();

	//  ����
	int TerrainDodge = _TargetUnit.TerrainDodge;
	int TerrainDeffence = _TargetUnit.TerrainDeffence;

	// ���� ��
	int Triangle = 0;
	int TriangleDamage = 0;
	int TriangleHit = 0;

	if (nullptr != _TargetUnit.UnitStat.EquipWeapon)
	{
		Triangle = Weapon::GetWeaponeTriangle(_SubjectUnit.UnitStat.EquipWeapon, _TargetUnit.UnitStat.EquipWeapon);
		TriangleDamage = Triangle;
		TriangleHit = Triangle * 15;
	}

	// ���߷�, ġ��Ÿ Ȯ�� ���
	int HitPercentage = UnitHit + TriangleHit - (TargetDodge + TerrainDodge);
	int CriticalPercentage = _SubjectUnit.UnitStat.GetCriticalPoint() - _TargetUnit.UnitStat.GetCriticalDodgePoint();

	NewAttack.IsHit = FERandom::RandomInt() < HitPercentage;
	NewAttack.IsCritical = FERandom::RandomInt() < CriticalPercentage;

	// ���ݷ� ���
	int Damage = _SubjectUnit.UnitStat.GetAttackPoint(_TargetUnit.UnitStat.ClassValue) + TriangleDamage;	// �󼺿� ���� ����� ����
	Damage -= _TargetUnit.UnitStat.MainStatValue.Defense + TerrainDeffence;	// ���¿� ���� ��ġ ����, ���� ��ġ ����
	Damage *= NewAttack.IsCritical ? 3 : 1;	// ġ��Ÿ �� 3��� ����

	// ������� 0���� �϶�
	if (0 >= Damage)
	{
		// No Damage
		Damage = 0;
	}

	if (true == NewAttack.IsHit)
	{
		_TargetUnit.CurrentHP -= Damage;
		_SubjectUnit.UnitStat.EquipWeapon->Uses--;

		if (0 >= _TargetUnit.CurrentHP)
		{
			_TargetUnit.CurrentHP = 0;
			_TargetUnit.IsDie = true;
		}
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
	CommandRecord.AfterSubjectUnit.IsTurnEnd = true;
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

