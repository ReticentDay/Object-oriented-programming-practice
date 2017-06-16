#pragma once
#include "Player.h"
#include "Obstacle.h"
#include "GameMap.h"
#include "Monster.h"
#include "hitBox.h"
#include "CreateMapInformation.h"
#include "DrawBox.h"
#include "GameInfoList.h"
#include "infoShowList.h"

namespace game_framework {
	//¹CÀ¸±±¨î¤¤¼Ï
	class  controlGame
	{
	public:
		controlGame();
		void OnIt();
		void StartLevel(int);
		int OnMove(vector<GameInfoList*> &list);
		void OnShow();
		void enterGoRight(bool);
		void enterRun(bool);
		void enterSkip(bool);
		void enterGoLeft(bool);
		void enterGoUp(bool);
		void enterGoDown(bool);
		void addTheHit();
		void clearList();
		~controlGame();
	protected:
		
	private:
		const int _displayMaxX = 640, _displayMaxY = 480;
		int _playerInX, _playerInY;
		int _playerDisplayX, _playerDisplayY;
		int _mapDisplayX, _mapDisplayY;
		int _mapMaxSizeX, _mapMaxSizeY;
		int _NowLevel;
		bool isGoUp, isGoDown, isGoLeft, isGoRight,isRun,isSkip;
		Player _player;
		GameMap* _gameMap;
		int obstacleXYList[5][2];
		Obstacle* _moveDoor;
		vector<touchBox*> _touchBoxList;
		vector<Obstacle*> _obstacleList;
		CreatMapInformation *_CMI;
		vector<Monster*> _monsterList;
		vector<hitBox*> _hitBoxList;
		vector<hitBox*> _monsterHitBoxList;
		infoShowList _infoShowList;
		int MOVE_LONG = 5;
		int power = 20;
		DrawBox* _DrawList;
	};
}