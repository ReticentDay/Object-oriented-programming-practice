#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Monster.h"
#include "Obstacle.h"
namespace game_framework {
	//�����T��
	struct listData
	{
		int x;
		int y;
		int height;
		int weight;
		string mode;
		string type;
	};
	//����ͦ����O
	class  CreatMapInformation
	{
	public:
		CreatMapInformation();
		void ReadInMapInfo(int level);
		void MakeObjetOnMap(vector<Monster*> &monsterList,vector<Obstacle*> &obstacleList);
		~CreatMapInformation();
	private:
		vector<listData> _listData;
	};
}