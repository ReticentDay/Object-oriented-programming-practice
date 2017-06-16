#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <fstream>
#include <sstream>
#include "audio.h"
#include "gamelib.h"
#include "CreateMapInformation.h"

namespace game_framework {
	//類別初始化
	CreatMapInformation::CreatMapInformation()
	{
	}

	//讀入檔案資訊
	void CreatMapInformation::ReadInMapInfo(int level)
	{
		stringstream formatStream;
		formatStream << "Source/map_information_" << level <<".txt";
		string filename;
 		formatStream >> filename;
		ifstream infoStream(filename);
		int put;
		_listData.clear();
		while ((infoStream >> put)) {
			listData putData;
			putData.x = put;
			infoStream >> putData.y >> putData.height >> putData.weight >> putData.mode >> putData.type;
			_listData.push_back(putData);
		}
		infoStream.close();
	}

	//依讀入資訊生成物件
	void CreatMapInformation::MakeObjetOnMap(vector<Monster*>& monsterList, vector<Obstacle*>& obstacleList)
	{

		for (vector<listData>::iterator i = _listData.begin();i != _listData.end();i++) {
			//物件類別生成
			if ((*i).mode == "obstacle") {														
				Obstacle* put;
				if ((*i).type == "rock")
					put = new Obstacle((*i).x, (*i).y, IDB_ROCK, (*i).height, (*i).weight);
				else if ((*i).type == "rock1")
					put = new Obstacle((*i).x, (*i).y, IDB_ROCK1, (*i).height, (*i).weight);
				else if ((*i).type == "wood1")
					put = new Obstacle((*i).x, (*i).y, IDB_WOOD1, (*i).height, (*i).weight);
				else if ((*i).type == "wood2")
					put = new Obstacle((*i).x, (*i).y, IDB_WOOD2, (*i).height, (*i).weight);
				else if ((*i).type == "pot")
					put = new Obstacle((*i).x, (*i).y, IDB_POT, (*i).height, (*i).weight);
				else if ((*i).type == "piranha")
					put = new Obstacle((*i).x, (*i).y, IDB_PIRANHA, (*i).height, (*i).weight);
				else if ((*i).type == "bush1")
					put = new Obstacle((*i).x, (*i).y, IDB_BUSH1, (*i).height, (*i).weight);
				else if ((*i).type == "bush2")
					put = new Obstacle((*i).x, (*i).y, IDB_BUSH2, (*i).height, (*i).weight);
				else if ((*i).type == "snowBush")
					put = new Obstacle((*i).x, (*i).y, IDB_SNOW_BUSH, (*i).height, (*i).weight);
				else if ((*i).type == "snowPot")
					put = new Obstacle((*i).x, (*i).y, IDB_SNOW_POT, (*i).height, (*i).weight);
				else if ((*i).type == "snowRock")
					put = new Obstacle((*i).x, (*i).y, IDB_SNOW_ROCK, (*i).height, (*i).weight);
				else
					put = new Obstacle((*i).x, (*i).y, IDB_Obstacle, (*i).height, (*i).weight);
				put->LoadBitmapA();
				obstacleList.push_back(put);
			}
			//怪物類別生成
			else if ((*i).mode == "monster") {														
				Monster* put = new Monster((*i).x, (*i).y);
				if ((*i).type == "wolf")
					put->LoadBitmapA(0);
				else if ((*i).type == "chicken")
					put->LoadBitmapA(1);
				else if ((*i).type == "snowman")
					put->LoadBitmapA(2);
				else
					put->LoadBitmapA(-1);
				monsterList.push_back(put);
			}
		}
	}

	//解構
	CreatMapInformation::~CreatMapInformation()
	{
		_listData.clear();
	}
}