#pragma once
#include "Stat.h"
#include "Weapon.h"
#include "ContentsEnum.h"
#include "BattleMap.h"
class Unit : public GameEngineNameObject
{
	friend class BattleUnit;
public:

	Unit();
	~Unit();
	Unit(const Unit& _Other)
	{
		UnitCode = _Other.UnitCode;
		UnitStat = Stat(_Other.UnitStat);
		CurrentHP = _Other.CurrentHP;
		TerrainData = _Other.TerrainData;
		TerrainDeffence = _Other.TerrainDeffence;
		TerrainDodge = _Other.TerrainDodge;
		IsTurnEnd = _Other.IsTurnEnd;
		IsDie = _Other.IsDie;
		IsPlayer = _Other.IsPlayer;
		Items = _Other.Items;
		Weapons = _Other.Weapons;
		CurWeapon = _Other.CurWeapon;
	}
	void operator=(const Unit& _Other)
	{
		UnitCode = _Other.UnitCode;
		UnitStat = Stat(_Other.UnitStat);
		CurrentHP = _Other.CurrentHP;
		TerrainData = _Other.TerrainData;
		TerrainDeffence = _Other.TerrainDeffence;
		TerrainDodge = _Other.TerrainDodge;
		IsTurnEnd = _Other.IsTurnEnd;
		IsDie = _Other.IsDie;
		IsPlayer = _Other.IsPlayer;
		Items = _Other.Items;
		Weapons = _Other.Weapons;
		CurWeapon = _Other.CurWeapon;
	}
	std::string ToString() const
	{
		std::string Str;
		Str += "ü�� : " + std::to_string(CurrentHP) + " / " + std::to_string(UnitStat.MainStatValue.HP) + '\n';
		Str += "���ݷ� : " + std::to_string(GetAttackPoint());
		return Str;
	}

	void LevelUp()
	{
		MainStat UpStat = UnitStat.LevelUp();
		if (1 <= UpStat.HP)
		{
			CurrentHP += UpStat.HP;
		}
	}
	void LevelUp(int _Value)
	{
		for (int i = 0; i < _Value; i++)
		{
			MainStat UpStat = UnitStat.LevelUp();
			if (1 <= UpStat.HP)
			{
				CurrentHP += UpStat.HP;
			}
		}
	}

	int GetUnitCode()
	{
		return UnitCode;
	}
	UnitIdentityCode GetIdentityCode()
	{
		return IdentityCode;
	}
	bool GetIsPlayer()
	{
		return IsPlayer;
	}
	// ü�� ����

	// ȸ��
	void Recover(int _Value)
	{
		CurrentHP += _Value;
		if (UnitStat.MainStatValue.HP < CurrentHP)
		{
			CurrentHP = UnitStat.MainStatValue.HP;
		}
	}
	// ���� ȸ��
	void RecoverPersent(float _Value)
	{
		Recover(static_cast<int>(std::roundf(UnitStat.MainStatValue.HP * _Value)));
	}
	// ���� ü��
	int GetHP()
	{
		return CurrentHP;
	}
	// �ִ� ü��
	int GetMaxHP()
	{
		return UnitStat.MainStatValue.HP;
	}
	// �����
	bool Damage(int _Value)
	{
		CurrentHP -= _Value;
		if (0 >= CurrentHP)
		{
			CurrentHP = 0;
			IsDie = true;
			return true;
		}
		return false;
	}


	// ����
	int GetRangeStat();
	// ��ƲŬ����
	BattleClass GetClassValue()
	{
		return UnitStat.ClassValue;
	}
	void ClassChange(BattleClass _Value)
	{
		switch (_Value)
		{
		case BattleClass::BladeLord:
			CurrentHP += 3;
			UnitStat.ClassChange_BladeLord();
			break;
		case BattleClass::Warrior:
			CurrentHP += 3;
			UnitStat.ClassChange_Warrior();
			break;
		case BattleClass::Assassin:
			CurrentHP += 3;
			UnitStat.ClassChange_Assassin();
			break;
		case BattleClass::General:
			CurrentHP += 4;
			UnitStat.ClassChange_General();
			break;
		default:
			break;
		}
	}
	int GetLevel()
	{
		return UnitStat.Level;
	}
	MainStat GetMainStat()
	{
		return UnitStat.MainStatValue;
	}
	MainStat GetMaximumStat()
	{
		return UnitStat.MaximumStat;
	}
	int GetExp()
	{
		return UnitStat.Experience;
	}

	// ����

	// �׾��°�
	bool GetIsDie()
	{
		return IsDie;
	}
	// �� ���� �ߴ°�
	void SetIsTurnEnd(bool _Value)
	{
		IsTurnEnd = _Value;
	}
	bool GetIsTurnEnd()
	{
		return IsTurnEnd;
	}


	// ��������

	Terrain GetTerrainData()
	{
		return TerrainData;
	}

	// �������Լ���

	// ������ �߰�
	void NewItem(ItemCode _Code);
	// ������ ���
	void UseItem(std::list<std::shared_ptr<Item>>::iterator& _ItemIter);
	// ������ ������
	void DropItem(std::list<std::shared_ptr<Item>>::iterator& _ItemIter);
	// ������ ���
	void EquipWeapon(std::shared_ptr<Weapon> _Weapon);
	// ���� ����Ʈ�ޱ�
	const std::list<std::shared_ptr<Weapon>>& GetWeapons()
	{
		return Weapons;
	}
	// ������ ����Ʈ �ޱ�
	std::list<std::shared_ptr<Item>>& GetItems()
	{
		return Items;
	}
	// ������� ����
	std::shared_ptr<Weapon> GetCurWeapon()
	{
		return CurWeapon;
	}
	// ������� ������ Ÿ�� (������� ���Ⱑ ������ None����)
	WeaponType GetWeaponTypeValue()
	{
		if (nullptr == CurWeapon)
		{
			return WeaponType::None;
		}
		return CurWeapon->GetWeaponTypeValue();
	}

	void LoadItemData(std::list<Item>& _Data);

	int GetAttackPoint() const;
	int GetAttackPoint(BattleClass _TargetClass) const;
	int GetAttackPoint(const class Unit& _Other) const;
	int GetDefPoint() const;
	int GetMagicAttackPoint() const;
	int GetHitPoint() const;
	int GetHitPoint(const class Unit& _Other) const;
	int GetCriticalPoint() const;
	int GetCriticalPoint(const class Unit& _Other) const;
	int GetAttackSpeedPoint() const;
	int GetDodgePoint() const;
	int GetCriticalDodgePoint() const;
	bool IsDoubleAttack(const class Unit& _Other) const;

private:


	// ���� ������
	int UnitCode = -1;
	UnitIdentityCode IdentityCode;
	int CurrentHP = 0;
	Stat UnitStat;

	// ���� ������
	Terrain TerrainData = Terrain::None;
	int TerrainDeffence = 0;
	int TerrainDodge = 0;
	
	// ����
	bool IsTurnEnd = false;
	bool IsDie = false;
	bool IsPlayer = false;

	// ������
	std::list<std::shared_ptr<Item>> Items = std::list<std::shared_ptr<Item>>();
	std::list<std::shared_ptr<Weapon>> Weapons = std::list<std::shared_ptr<Weapon>>();
	std::shared_ptr<Weapon> CurWeapon = nullptr;		// ����� ����

};

