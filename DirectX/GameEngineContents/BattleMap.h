#pragma once
#include <vector>
#include <GameEngineCore/GameEngineActor.h>
#include "Int2.h"
const static float TileScale = 64.0f;

enum class Terrain
{
	Plain,	//����
	None,	//�̵��Ұ�����
	Forest,	//��
	Cliff,	//����
	Mountain,	//��
	Peak,		//���� ��
	Door,		//�� �̵��Ұ�
	Gate,		//�� ����Ʈ �̵�����
	House,		//�ΰ�
	Sea,		//�ٴ�
	River,		//��
	Bridge,		//�ٸ�
	Wall,		//��
};

class GameEngineRenderer;
class BattleMap : public GameEngineActor
{
public:
	friend class BattleLevel;
	// constrcuter destructer
	BattleMap();
	~BattleMap();

	// delete Function
	BattleMap(const BattleMap& _Other) = delete;
	BattleMap(BattleMap&& _Other) noexcept = delete;
	BattleMap& operator=(const BattleMap& _Other) = delete;
	BattleMap& operator=(BattleMap&& _Other) noexcept = delete;

	float4 MapScaleFloat4 = { 960, 640 };
	int2 MapScaleInt2 = { 15, 10 };


protected:
	void Start() override;

	// �� ����
	std::vector<std::vector<Terrain>> TerrainData;
	// �̹��� �̸�
	std::string_view ImageName;
private:
	std::shared_ptr<GameEngineRenderer> MapRender = nullptr;

};

