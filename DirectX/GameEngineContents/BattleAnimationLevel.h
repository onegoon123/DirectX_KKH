#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "UnitCommand.h"

// ���� :
class BattleAnimationLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BattleAnimationLevel();
	~BattleAnimationLevel();

	// delete Function
	BattleAnimationLevel(const BattleAnimationLevel& _Other) = delete;
	BattleAnimationLevel(BattleAnimationLevel&& _Other) noexcept = delete;
	BattleAnimationLevel& operator=(const BattleAnimationLevel& _Other) = delete;
	BattleAnimationLevel& operator=(BattleAnimationLevel&& _Other) noexcept = delete;

	static void SetBattleData(std::shared_ptr<BattleUnit> _SubjectUnit, std::shared_ptr<BattleUnit> _TargetUnit, const std::list<AttackCommand>& _Data);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
private:
	static std::shared_ptr<BattleUnit> SubjectUnit;
	static std::shared_ptr<BattleUnit> TargetUnit;
	static std::list<AttackCommand> BattleData;
};
