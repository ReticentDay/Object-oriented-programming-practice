#pragma once
#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "controlGame.h"
#include <vector>

namespace game_framework {
	//物件初始化
	controlGame::controlGame() :_playerInX(10), _playerInY(10),_playerDisplayX(0),_playerDisplayY(0),_mapDisplayX(0),_mapDisplayY(0){
		isGoDown = isGoLeft = isGoRight = isGoUp = false;
		_mapMaxSizeX = _mapMaxSizeY = 1440;
		_CMI = new CreatMapInformation();
		_DrawList = new DrawBox();
		
	}

	//物件初始化
	void controlGame::OnIt()
	{
		CAudio::Instance()->Load(4, "Sounds\\hit.mp3");
		_player.LoadBitmapA();
	}
	
	//關卡開始初始化
	void controlGame::StartLevel(int levelNow)
	{
		_NowLevel = levelNow + 1;
		MOVE_LONG = 5;
		power = 20;
		for (vector<Obstacle*>::iterator i = _obstacleList.begin();i != _obstacleList.end();i++) 
			delete *i;
		_obstacleList.clear();
		_touchBoxList.clear();
		for (vector<Monster*>::iterator i = _monsterList.begin();i != _monsterList.end();i++)
			delete *i;
		_monsterList.clear();
		_CMI->ReadInMapInfo(_NowLevel);
		_CMI->MakeObjetOnMap(_monsterList,_obstacleList);
		for (vector<Obstacle*>::iterator i = _obstacleList.begin();i != _obstacleList.end();i++)
			_touchBoxList.push_back((*i)->getTouchBox());
		
		_moveDoor = new Obstacle(720, 1380, IDB_MoveIt, 48, 48);
		_moveDoor->LoadBitmapA();
		int mapType[5] = { 1,2,3,1,2 };
		_gameMap = new GameMap(mapType[levelNow]);
		_gameMap->LoadBitmapA();
		_playerInX = _playerInY = 10;
		_playerDisplayX = _playerDisplayY = 0;
		_mapDisplayX = _mapDisplayY = 0;
		isGoDown = isGoLeft = isGoRight = isGoUp = isRun = isSkip = false;
		if(_NowLevel == 1)
			_player.playerReset();
	}

	int controlGame::OnMove(vector<GameInfoList*> &list)
	{
		int direction = 0;
		
		//判斷玩家是否奔跑
		if (isRun && power <= 0) {
			isRun = false;
			power = -20;
		}
		else if (!isRun && power <= 20)
			power++;
		else if (isRun)
			power--;

		if (isRun) {
			MOVE_LONG = 7;
		}
		else {
			MOVE_LONG = 5;
		}

		//玩家移動與計算位置
		if (isGoDown) {
			if(_playerInY + MOVE_LONG + 49 < _mapMaxSizeY && !_player.checkTheTouch(_touchBoxList,0, MOVE_LONG))
				_playerInY += MOVE_LONG;
			direction = 1;
		}
		if (isGoUp) {
			if (_playerInY - MOVE_LONG > 0 && !_player.checkTheTouch(_touchBoxList, 0, -MOVE_LONG))
				_playerInY -= MOVE_LONG;
			direction = 2;
		}
		if (isGoLeft) {
			if (_playerInX - MOVE_LONG > 0 && !_player.checkTheTouch(_touchBoxList, -MOVE_LONG, 0))
				_playerInX -= MOVE_LONG;
			direction = 3;
		}
		if (isGoRight) {
			if (_playerInX + MOVE_LONG +31 < _mapMaxSizeX && !_player.checkTheTouch(_touchBoxList, MOVE_LONG, 0))
				_playerInX += MOVE_LONG;
			direction = 4;
		}
		if (_playerInX <= _displayMaxX/2) {
			_playerDisplayX = _playerInX;
			_mapDisplayX = 0;
		}
		else if (_playerInX >= _mapMaxSizeX - _displayMaxX / 2) {
			_playerDisplayX = _playerInX - (_mapMaxSizeX - _displayMaxX);
			_mapDisplayX = _mapMaxSizeX - _displayMaxX;
		}
		else 
		{
			_playerDisplayX = _displayMaxX / 2;
			_mapDisplayX = _playerInX - _displayMaxX / 2;
		}
		if (_playerInY <= _displayMaxY / 2) {
			_playerDisplayY = _playerInY;
			_mapDisplayY = 0;
		}
		else if (_playerInY >= _mapMaxSizeY - _displayMaxY / 2) {
			_playerDisplayY = _playerInY - (_mapMaxSizeY - _displayMaxY);
			_mapDisplayY = _mapMaxSizeY - _displayMaxY;
		}
		else
		{
			_playerDisplayY = _displayMaxY / 2;
			_mapDisplayY = _playerInY - _displayMaxY / 2;
		}

		//攻擊物件(玩家)位移與偵測其存在
		for (vector<hitBox*>::iterator i = _hitBoxList.begin();i != _hitBoxList.end();) {
			if ((*i)->OnMove(-1 * _mapDisplayX, -1 * _mapDisplayY)) {
				delete *i;
				i = _hitBoxList.erase(i);
			}
			else
				i++;
		}

		//攻擊物件(怪物)位移與偵測其存在
		for (vector<hitBox*>::iterator i = _monsterHitBoxList.begin();i != _monsterHitBoxList.end();) {
			if ((*i)->OnMove(-1 * _mapDisplayX, -1 * _mapDisplayY)) {
				delete *i;
				i = _monsterHitBoxList.erase(i);
			}
			else
				i++;
		}

		//物件移動
		for (vector<Obstacle*>::iterator i = _obstacleList.begin();i != _obstacleList.end();i++)
			(*i)->OnMove(-1 * _mapDisplayX, -1 * _mapDisplayY, _hitBoxList);

		//怪物位移、偵測存在、成就產生
		for (vector<Monster*>::iterator i = _monsterList.begin();i != _monsterList.end();) {
			if ((*i)->OnMove(-1 * _mapDisplayX, -1 * _mapDisplayY, _touchBoxList, _player.getPlayerTouchBox(), _hitBoxList, _monsterHitBoxList)) {
				int type = (*i)->getType();
				delete *i;
				i = _monsterList.erase(i);
				if (type == 0) {
					list[0]->setCount(list[0]->returnCount() + 1);
					if (list[0]->returnCount() == 1) {
						GameInfoString * put = new GameInfoString("第一次的殺生");
						_infoShowList.addShowBox(170, -39, "獲得稱號：第一次的殺生");
						list.push_back(put);
					}
					else if (list[0]->returnCount() == 10) {
						GameInfoString * put = new GameInfoString("熟練切肉");
						_infoShowList.addShowBox(170, -39, "獲得稱號：熟練切肉");
						list.push_back(put);
					}
					else if (list[0]->returnCount() == 30) {
						GameInfoString * put = new GameInfoString("血腥小紅帽");
						_infoShowList.addShowBox(170, -39, "獲得稱號：血腥小紅帽");
						list.push_back(put);
					}
					else if (list[0]->returnCount() == 100) {
						GameInfoString * put = new GameInfoString("狼族絕種保護協會");
						_infoShowList.addShowBox(170, -39, "獲得稱號：狼族絕種保護協會");
						list.push_back(put);
					}
				}
				else if (type == 1) {
					list[1]->setCount(list[1]->returnCount() + 1);
					if (list[1]->returnCount() == 1) {
						GameInfoString * put = new GameInfoString("雞肉！！！");
						_infoShowList.addShowBox(170, -39, "獲得稱號：雞肉！！！");
						list.push_back(put);
					}
					else if (list[1]->returnCount() == 10) {
						GameInfoString * put = new GameInfoString("我不是素食者");
						_infoShowList.addShowBox(170, -39, "獲得稱號：我不是素食者");
						list.push_back(put);
					}
					else if (list[1]->returnCount() == 30) {
						GameInfoString * put = new GameInfoString("肯德基超讚Der！");
						_infoShowList.addShowBox(170, -39, "獲得稱號：肯德基超讚Der！");
						list.push_back(put);
					}
					else if (list[1]->returnCount() == 100) {
						GameInfoString * put = new GameInfoString("速食大亨");
						_infoShowList.addShowBox(170, -39, "獲得稱號：速食大亨");
						list.push_back(put);
					}
				}
				else if (type == 2) {
					list[2]->setCount(list[2]->returnCount() + 1);
					if (list[2]->returnCount() == 1) {
						GameInfoString * put = new GameInfoString("未確認生物");
						_infoShowList.addShowBox(170, -39, "獲得稱號：未確認生物");
						list.push_back(put);
					}
					else if (list[2]->returnCount() == 10) {
						GameInfoString * put = new GameInfoString("天不怕地不怕");
						_infoShowList.addShowBox(170, -39, "獲得稱號：天不怕地不怕");
						list.push_back(put);
					}
					else if (list[2]->returnCount() == 30) {
						GameInfoString * put = new GameInfoString("雪怪很友善，真的");
						_infoShowList.addShowBox(170, -39, "獲得稱號：雪怪很友善，真的");
						list.push_back(put);
					}
					else if (list[2]->returnCount() == 100) {
						GameInfoString * put = new GameInfoString("冰雪騎猿 ");
						_infoShowList.addShowBox(170, -39, "獲得稱號：冰雪騎猿");
						list.push_back(put);
					}
				}
			}
			else {
				i++;
			}
		}

		//傳送門位移
		_moveDoor->OnMove(-1 * _mapDisplayX, -1 * _mapDisplayY, _hitBoxList);

		//玩家位移與遊戲結束狀況判斷(玩家死亡)
		if (_player.OnMove(_playerDisplayX, _playerDisplayY, direction, _monsterHitBoxList)) {
			GameInfoString * put = new GameInfoString("菜兵");
			list.push_back(put);
			return -99;
			clearList();
		}
		
		//地圖位移
		_gameMap->OnMove(-1 * _mapDisplayX,-1 * _mapDisplayY);

		//遊戲結束狀況判斷(進入下一關)
		if (_player.checkTheTouch(_moveDoor->getTouchBox()) || (_playerInX <= 5  && _playerInY <= 5 && isSkip))
			return 1;

		return  0;
	}

	//顯示全物件
	void controlGame::OnShow()
	{
		
		_gameMap->OnShow();
		_moveDoor->OnShow();
		for (vector<Obstacle*>::iterator i = _obstacleList.begin();i != _obstacleList.end();i++)
			(*i)->OnShow();
		for (vector<Monster*>::iterator i = _monsterList.begin();i != _monsterList.end();i++)
			(*i)->OnShow(_DrawList);
		for (vector<hitBox*>::iterator i = _hitBoxList.begin();i != _hitBoxList.end();i++)
			(*i)->OnShow();
		for (vector<hitBox*>::iterator i = _monsterHitBoxList.begin();i != _monsterHitBoxList.end();i++)
			(*i)->OnShow();
		_DrawList->AddIt(20, 430, 220, 440, RGB(255, 255, 0), RGB(255, 255, 255));
		_DrawList->AddIt(20, 430, 20 + 10 * (power < 0 ? 0 : power), 440, RGB(255, 255, 0), RGB(0, 255, 0));
		_infoShowList.showBox(_DrawList);
		_player.OnShow(_DrawList);
		_DrawList->DrawIt();
		
	}

	//按鍵偵測與傳送資訊
	void controlGame::enterGoRight(bool flag)
	{
		isGoRight = flag;
	}
	void controlGame::enterRun(bool flag)
	{
		isRun = flag;
	}
	void controlGame::enterSkip(bool flag)
	{
		isSkip = flag;
	}
	void controlGame::enterGoLeft(bool flag)
	{
		isGoLeft = flag;
	}
	void controlGame::enterGoUp(bool flag)
	{
		isGoUp = flag;
	}
	void controlGame::enterGoDown(bool flag)
	{
		isGoDown = flag;
	}
	void controlGame::addTheHit()
	{
		CAudio::Instance()->Play(4,false);
		_hitBoxList.push_back(_player.addHitBox(_playerInX,_playerInY));
	}

	//解構
	controlGame::~controlGame()
	{
		clearList();
	}

	//物件清理
	void controlGame::clearList()
	{
		delete _gameMap;
		delete _moveDoor;
		for (vector<Obstacle*>::iterator i = _obstacleList.begin();i != _obstacleList.end();i++)
			delete *i;
		_touchBoxList.clear();
		_obstacleList.clear();
		delete _CMI;
		for (vector<Monster*>::iterator i = _monsterList.begin();i != _monsterList.end();i++)
			delete *i;
		_monsterList.clear();
	}
}