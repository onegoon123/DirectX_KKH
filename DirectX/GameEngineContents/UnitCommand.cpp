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

	CommandRecord.BeforeSubjectItems = Item::SaveItemDataList(SubjectUnit.GetItems());
	CommandRecord.BeforeTargetItems = Item::SaveItemDataList(TargetUnit.GetItems());

	if (nullptr != SubjectUnit.GetCurWeapon() && SubjectUnit.GetCurWeapon()->IsAttackable(_SubjectUnit->GetMapPos(), _TargetUnit->GetMapPos()))
	{
		AttackCommand NewAttack = AttackCalculation(SubjectUnit, TargetUnit);
		NewAttack.SubjectAttack = true;
		AttackList.push_back(NewAttack);
		CommandRecord.RandomNum += 2;

		if (true == TargetUnit.GetIsDie())
		{
			return AttackEnd(AttackList, CommandRecord, SubjectUnit, TargetUnit);
		}
	}

	if (nullptr != TargetUnit.GetCurWeapon() && TargetUnit.GetCurWeapon()->IsAttackable(_SubjectUnit->GetMapPos(), _TargetUnit->GetMapPos()))
	{
		AttackCommand NewAttack = AttackCalculation(TargetUnit, SubjectUnit);
		NewAttack.ChangeOrder();
		AttackList.push_back(NewAttack);
		CommandRecord.RandomNum += 2;

		if (true == SubjectUnit.GetIsDie())
		{
			return AttackEnd(AttackList, CommandRecord, SubjectUnit, TargetUnit);
		}
	}


	if (TargetUnit.GetAttackSpeedPoint() + 4 <= SubjectUnit.GetAttackSpeedPoint())
	{
		if (nullptr != SubjectUnit.GetCurWeapon() && SubjectUnit.GetCurWeapon()->IsAttackable(_SubjectUnit->GetMapPos(), _TargetUnit->GetMapPos()))
		{
			AttackCommand NewAttack = AttackCalculation(SubjectUnit, TargetUnit);
			NewAttack.SubjectAttack = true;
			AttackList.push_back(NewAttack);
			CommandRecord.RandomNum += 2;
		}
	}
	else if (SubjectUnit.GetAttackSpeedPoint() + 4 <= TargetUnit.GetAttackSpeedPoint())
	{
		if (nullptr != TargetUnit.GetCurWeapon() && TargetUnit.GetCurWeapon()->IsAttackable(_SubjectUnit->GetMapPos(), _TargetUnit->GetMapPos()))
		{
			AttackCommand NewAttack = AttackCalculation(TargetUnit, SubjectUnit);
			NewAttack.ChangeOrder();
			AttackList.push_back(NewAttack);
			CommandRecord.RandomNum += 2;
		}
	}

	return AttackEnd(AttackList, CommandRecord, SubjectUnit, TargetUnit);
}

AttackCommand UnitCommand::AttackSimulation(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit)
{
	Unit SubjectUnit = Unit(_SubjectUnit->GetUnitData());
	Unit TargetUnit = Unit(_TargetUnit->GetUnitData());
	AttackCommand NewAttack;

	if (nullptr != SubjectUnit.GetCurWeapon())
	{
		NewAttack = AttackCalculationNoRandom(SubjectUnit, TargetUnit);

		if (true == TargetUnit.GetIsDie())
		{
			return NewAttack;
		}
	}

	if (nullptr != TargetUnit.GetCurWeapon())
	{
		NewAttack = AttackCalculationNoRandom(TargetUnit, SubjectUnit);
		NewAttack.ChangeOrder();

		if (true == SubjectUnit.GetIsDie())
		{
			return NewAttack;
		}
	}


	if (TargetUnit.GetAttackSpeedPoint() + 4 <= SubjectUnit.GetAttackSpeedPoint())
	{
		if (nullptr != SubjectUnit.GetCurWeapon())
		{
			NewAttack = AttackCalculationNoRandom(SubjectUnit, TargetUnit);
			NewAttack.SubjectAttack = true;
			return NewAttack;
		}
	}
	else if (SubjectUnit.GetAttackSpeedPoint() + 4 <= TargetUnit.GetAttackSpeedPoint())
	{
		if (nullptr != TargetUnit.GetCurWeapon())
		{
			NewAttack = AttackCalculationNoRandom(TargetUnit, SubjectUnit);
			NewAttack.ChangeOrder();
			return NewAttack;
		}
	}

	return NewAttack;
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
	NewAttack.IsCritical = FERandom::RandomInt() < CriticalPercentage && NewAttack.IsHit;

	// ���ݷ� ���
	NewAttack.Damage = _SubjectUnit.GetAttackPoint(_TargetUnit.GetClassValue()) + TriangleDamage;	// �󼺿� ���� ����� ����
	NewAttack.Damage -= _TargetUnit.GetDefPoint();	// ���¿� ���� ��ġ ����, ���� ��ġ ����
	NewAttack.Damage *= NewAttack.IsCritical ? 3 : 1;	// ġ��Ÿ �� 3��� ����

	// ������� 0���� �϶�
	if (0 >= NewAttack.Damage)
	{
		// No Damage
		NewAttack.Damage = 0;
	}

	if (true == NewAttack.IsHit)
	{
		_TargetUnit.Damage(NewAttack.Damage);
		_SubjectUnit.GetCurWeapon()->Use();
	}

	NewAttack.TargetUnit = _TargetUnit;
	NewAttack.SubjectUnit = _SubjectUnit;

	return NewAttack;
}

AttackCommand UnitCommand::AttackCalculationNoRandom(Unit& _SubjectUnit, Unit& _TargetUnit)
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

	NewAttack.IsHit = 0 < HitPercentage;
	NewAttack.IsCritical = 50 < CriticalPercentage && NewAttack.IsHit;

	// ���ݷ� ���
	NewAttack.Damage = _SubjectUnit.GetAttackPoint(_TargetUnit.GetClassValue()) + TriangleDamage;	// �󼺿� ���� ����� ����
	NewAttack.Damage -= _TargetUnit.GetDefPoint();	// ���¿� ���� ��ġ ����, ���� ��ġ ����
	NewAttack.Damage *= NewAttack.IsCritical ? 3 : 1;	// ġ��Ÿ �� 3��� ����

	// ������� 0���� �϶�
	if (0 >= NewAttack.Damage)
	{
		// No Damage
		NewAttack.Damage = 0;
	}

	if (true == NewAttack.IsHit)
	{
		_TargetUnit.Damage(NewAttack.Damage);
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

void UnitCommand::ItemUse(std::shared_ptr<BattleUnit> _SubjectUnit, std::list<std::shared_ptr<Item>>::iterator& _ItemIter)
{
	UnitCommand CommandRecord;
	CommandRecord.TypeValue = CommandType::Item;
	CommandRecord.BeforeSubjectUnit = Unit(_SubjectUnit->GetUnitData());
	CommandRecord.BeforeSubjectUnitPos = _SubjectUnit->GetBeforeMapPos();
	CommandRecord.BeforeSubjectItems = Item::SaveItemDataList(CommandRecord.BeforeSubjectUnit.GetItems());

	CommandRecord.Record = std::string(_SubjectUnit->GetName()) + "��(��) " + std::string((*_ItemIter)->GetName()) + "��(��) ����ߴ�.";
	_SubjectUnit->GetUnitData().UseItem(_ItemIter);

	CommandRecord.AfterSubjectItems = Item::SaveItemDataList(_SubjectUnit->GetUnitData().GetItems());
	CommandRecord.AfterSubjectUnit = CommandRecord.BeforeSubjectUnit;
	CommandRecord.AfterSubjectUnitPos = _SubjectUnit->GetMapPos();
	CommandRecord.AfterSubjectUnit.SetIsTurnEnd(true);
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

std::list<AttackCommand>& UnitCommand::AttackEnd(std::list<AttackCommand>& _AttackList, UnitCommand& _CommandRecord, Unit& _SubjectUnit, Unit& _TargetUnit)
{
	_CommandRecord.AfterSubjectUnit = _SubjectUnit;
	_CommandRecord.AfterSubjectUnit.SetIsTurnEnd(true);
	_CommandRecord.AfterTargetUnit = _TargetUnit;
	_CommandRecord.AfterSubjectItems = Item::SaveItemDataList(_SubjectUnit.GetItems());
	_CommandRecord.AfterTargetItems = Item::SaveItemDataList(_TargetUnit.GetItems());
	CommandList.push_back(_CommandRecord);

	// ����ġ ���
	int SumDamage = 0;
	for (AttackCommand _Attack : _AttackList)
	{
		if (true == _Attack.SubjectAttack && false == _SubjectUnit.GetIsPlayer()) { continue; }
		if (false == _Attack.SubjectAttack && true == _SubjectUnit.GetIsPlayer()) { continue; }
		// �÷��̾� ������ ������ ������� ����
		SumDamage += _Attack.Damage;
	}

	Unit& Player = _AttackList.back().SubjectUnit.GetIsPlayer() == true ? _AttackList.back().SubjectUnit : _AttackList.back().TargetUnit;
	Unit& Enemy = _AttackList.back().SubjectUnit.GetIsPlayer() == false ? _AttackList.back().SubjectUnit : _AttackList.back().TargetUnit;

	if (1 <= SumDamage)
	{
		_AttackList.back().Exp = SumDamage + Enemy.GetLevel() - Player.GetLevel() + 20;
	}
	_AttackList.back().IsLevelUp = Player.AddExp(_AttackList.back().Exp);

	return _AttackList;

}

