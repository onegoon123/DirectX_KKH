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
		SetName(_Other.GetName());
		IdentityCode = _Other.IdentityCode;
		UnitCode = _Other.UnitCode;
		UnitStat = Stat(_Other.UnitStat);
		LevelUpData = _Other.LevelUpData;
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
		SetName(_Other.GetName());
		IdentityCode = _Other.IdentityCode;
		UnitCode = _Other.UnitCode;
		UnitStat = Stat(_Other.UnitStat);
		LevelUpData = _Other.LevelUpData;
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
		Str += "체력 : " + std::to_string(CurrentHP) + " / " + std::to_string(UnitStat.MainStatValue.HP) + '\n';
		Str += "공격력 : " + std::to_string(GetAttackPoint());
		return Str;
	}

	void LevelUp()
	{
		LevelUpData = UnitStat.LevelUp();
	}
	void LevelUp(int _Value)
	{
		for (int i = 0; i < _Value; i++)
		{
			LevelUpData = UnitStat.LevelUp();
			if (1 <= LevelUpData.HP)
			{
				CurrentHP += LevelUpData.HP;
			}
		}
	}
	bool AddExp(int _Exp)
	{
		UnitStat.Experience += _Exp;
		if (100 <= UnitStat.Experience)
		{
			UnitStat.Experience -= 100;
			LevelUp();
			return true;
		}
		return false;
	}
	MainStat GetLevelUpData()
	{
		return LevelUpData;
	}
	int GetUnitCode()
	{
		return UnitCode;
	}
	UnitIdentityCode GetIdentityCode()
	{
		return IdentityCode;
	}
	bool GetIsPlayer() const
	{
		return IsPlayer;
	}
	// 체력 관련

	// 회복
	void Recover(int _Value)
	{
		CurrentHP += _Value;
		if (UnitStat.MainStatValue.HP < CurrentHP)
		{
			CurrentHP = UnitStat.MainStatValue.HP;
		}
	}
	// 비율 회복
	void RecoverPersent(float _Value)
	{
		Recover(static_cast<int>(std::roundf(UnitStat.MainStatValue.HP * _Value)));
	}
	// 현재 체력
	int GetHP()
	{
		return CurrentHP;
	}
	// 최대 체력
	int GetMaxHP()
	{
		return UnitStat.MainStatValue.HP;
	}
	// 대미지
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


	// 스텟
	int GetRangeStat();
	// 배틀클래스
	BattleClass GetClassValue()
	{
		return UnitStat.ClassValue;
	}
	// 배틀클래스
	std::string_view GetClassValueToString();

	void ClassChange(BattleClass _Value)
	{
		switch (_Value)
		{
		case BattleClass::BladeLord:
			IdentityCode = UnitIdentityCode::BladeLordLyn;
			CurrentHP += 3;
			LevelUpData = UnitStat.ClassChange_BladeLord();
			break;
		case BattleClass::Warrior:
			IdentityCode = UnitIdentityCode::WarriorDorcas;
			CurrentHP += 3;
			LevelUpData = UnitStat.ClassChange_Warrior();
			break;
		case BattleClass::Assassin:
			IdentityCode = UnitIdentityCode::AssassinMatthew;
			CurrentHP += 3;
			LevelUpData = UnitStat.ClassChange_Assassin();
			break;
		case BattleClass::General:
			IdentityCode = UnitIdentityCode::GeneralWallace;
			CurrentHP += 4;
			LevelUpData = UnitStat.ClassChange_General();
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

	// 상태

	// 죽었는가
	bool GetIsDie()
	{
		return IsDie;
	}
	// 턴 종료 했는가
	void SetIsTurnEnd(bool _Value)
	{
		IsTurnEnd = _Value;
	}
	bool GetIsTurnEnd()
	{
		return IsTurnEnd;
	}


	// 지형정보

	Terrain GetTerrainData()
	{
		return TerrainData;
	}

	// 아이템함수들

	// 아이템 추가
	void NewItem(ItemCode _Code);
	// 아이템 등록
	void AddItem(std::shared_ptr<Item> _Item);
	// 아이템 교체
	void ChangeItem(std::shared_ptr<Item> _Item, int _Index);
	// 아이템 사용
	void UseItem(std::list<std::shared_ptr<Item>>::iterator& _ItemIter);
	// 아이템 버리기
	void DropItem(std::list<std::shared_ptr<Item>>::iterator& _ItemIter);
	void DropItem(std::shared_ptr<Item> _Item);
	// 아이템 장비
	void EquipWeapon(std::shared_ptr<Weapon> _Weapon);
	// 무기 리스트받기
	const std::list<std::shared_ptr<Weapon>>& GetWeapons()
	{
		return Weapons;
	}
	// 아이템 리스트 받기
	std::list<std::shared_ptr<Item>>& GetItems()
	{
		return Items;
	}
	// 장비중인 무기
	std::shared_ptr<Weapon> GetCurWeapon()
	{
		return CurWeapon;
	}
	// 장비중인 무기의 타입 (장비중인 무기가 없을시 None리턴)
	WeaponType GetWeaponTypeValue() const
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
	int GetDefPoint(WeaponType _Type) const;
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


	// 유닛 데이터
	int UnitCode = -1;
	UnitIdentityCode IdentityCode;
	int CurrentHP = 0;
	Stat UnitStat;
	MainStat LevelUpData; // 이전 레벨업에 증가된 스텟

	// 지형 데이터
	Terrain TerrainData = Terrain::None;
	int TerrainDeffence = 0;
	int TerrainDodge = 0;
	
	// 상태
	bool IsTurnEnd = false;
	bool IsDie = false;
	bool IsPlayer = false;

	// 아이템
	std::list<std::shared_ptr<Item>> Items = std::list<std::shared_ptr<Item>>();
	std::list<std::shared_ptr<Weapon>> Weapons = std::list<std::shared_ptr<Weapon>>();
	std::shared_ptr<Weapon> CurWeapon = nullptr;		// 장비한 무기

};

