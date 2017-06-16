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
	//�����l��
	controlGame::controlGame() :_playerInX(10), _playerInY(10),_playerDisplayX(0),_playerDisplayY(0),_mapDisplayX(0),_mapDisplayY(0){
		isGoDown = isGoLeft = isGoRight = isGoUp = false;
		_mapMaxSizeX = _mapMaxSizeY = 1440;
		_CMI = new CreatMapInformation();
		_DrawList = new DrawBox();
		
	}

	//�����l��
	void controlGame::OnIt()
	{
		CAudio::Instance()->Load(4, "Sounds\\hit.mp3");
		_player.LoadBitmapA();
	}
	
	//���d�}�l��l��
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
		
		//�P�_���a�O�_�b�]
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

		//���a���ʻP�p���m
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

		//��������(���a)�첾�P������s�b
		for (vector<hitBox*>::iterator i = _hitBoxList.begin();i != _hitBoxList.end();) {
			if ((*i)->OnMove(-1 * _mapDisplayX, -1 * _mapDisplayY)) {
				delete *i;
				i = _hitBoxList.erase(i);
			}
			else
				i++;
		}

		//��������(�Ǫ�)�첾�P������s�b
		for (vector<hitBox*>::iterator i = _monsterHitBoxList.begin();i != _monsterHitBoxList.end();) {
			if ((*i)->OnMove(-1 * _mapDisplayX, -1 * _mapDisplayY)) {
				delete *i;
				i = _monsterHitBoxList.erase(i);
			}
			else
				i++;
		}

		//���󲾰�
		for (vector<Obstacle*>::iterator i = _obstacleList.begin();i != _obstacleList.end();i++)
			(*i)->OnMove(-1 * _mapDisplayX, -1 * _mapDisplayY, _hitBoxList);

		//�Ǫ��첾�B�����s�b�B���N����
		for (vector<Monster*>::iterator i = _monsterList.begin();i != _monsterList.end();) {
			if ((*i)->OnMove(-1 * _mapDisplayX, -1 * _mapDisplayY, _touchBoxList, _player.getPlayerTouchBox(), _hitBoxList, _monsterHitBoxList)) {
				int type = (*i)->getType();
				delete *i;
				i = _monsterList.erase(i);
				if (type == 0) {
					list[0]->setCount(list[0]->returnCount() + 1);
					if (list[0]->returnCount() == 1) {
						GameInfoString * put = new GameInfoString("�Ĥ@��������");
						_infoShowList.addShowBox(170, -39, "��o�ٸ��G�Ĥ@��������");
						list.push_back(put);
					}
					else if (list[0]->returnCount() == 10) {
						GameInfoString * put = new GameInfoString("���m����");
						_infoShowList.addShowBox(170, -39, "��o�ٸ��G���m����");
						list.push_back(put);
					}
					else if (list[0]->returnCount() == 30) {
						GameInfoString * put = new GameInfoString("��{�p���U");
						_infoShowList.addShowBox(170, -39, "��o�ٸ��G��{�p���U");
						list.push_back(put);
					}
					else if (list[0]->returnCount() == 100) {
						GameInfoString * put = new GameInfoString("�T�ڵ��ثO�@��|");
						_infoShowList.addShowBox(170, -39, "��o�ٸ��G�T�ڵ��ثO�@��|");
						list.push_back(put);
					}
				}
				else if (type == 1) {
					list[1]->setCount(list[1]->returnCount() + 1);
					if (list[1]->returnCount() == 1) {
						GameInfoString * put = new GameInfoString("���סI�I�I");
						_infoShowList.addShowBox(170, -39, "��o�ٸ��G���סI�I�I");
						list.push_back(put);
					}
					else if (list[1]->returnCount() == 10) {
						GameInfoString * put = new GameInfoString("�ڤ��O������");
						_infoShowList.addShowBox(170, -39, "��o�ٸ��G�ڤ��O������");
						list.push_back(put);
					}
					else if (list[1]->returnCount() == 30) {
						GameInfoString * put = new GameInfoString("�ּw��W�gDer�I");
						_infoShowList.addShowBox(170, -39, "��o�ٸ��G�ּw��W�gDer�I");
						list.push_back(put);
					}
					else if (list[1]->returnCount() == 100) {
						GameInfoString * put = new GameInfoString("�t���j��");
						_infoShowList.addShowBox(170, -39, "��o�ٸ��G�t���j��");
						list.push_back(put);
					}
				}
				else if (type == 2) {
					list[2]->setCount(list[2]->returnCount() + 1);
					if (list[2]->returnCount() == 1) {
						GameInfoString * put = new GameInfoString("���T�{�ͪ�");
						_infoShowList.addShowBox(170, -39, "��o�ٸ��G���T�{�ͪ�");
						list.push_back(put);
					}
					else if (list[2]->returnCount() == 10) {
						GameInfoString * put = new GameInfoString("�Ѥ��Ȧa����");
						_infoShowList.addShowBox(170, -39, "��o�ٸ��G�Ѥ��Ȧa����");
						list.push_back(put);
					}
					else if (list[2]->returnCount() == 30) {
						GameInfoString * put = new GameInfoString("���ǫܤ͵��A�u��");
						_infoShowList.addShowBox(170, -39, "��o�ٸ��G���ǫܤ͵��A�u��");
						list.push_back(put);
					}
					else if (list[2]->returnCount() == 100) {
						GameInfoString * put = new GameInfoString("�B���M�� ");
						_infoShowList.addShowBox(170, -39, "��o�ٸ��G�B���M��");
						list.push_back(put);
					}
				}
			}
			else {
				i++;
			}
		}

		//�ǰe���첾
		_moveDoor->OnMove(-1 * _mapDisplayX, -1 * _mapDisplayY, _hitBoxList);

		//���a�첾�P�C���������p�P�_(���a���`)
		if (_player.OnMove(_playerDisplayX, _playerDisplayY, direction, _monsterHitBoxList)) {
			GameInfoString * put = new GameInfoString("��L");
			list.push_back(put);
			return -99;
			clearList();
		}
		
		//�a�Ϧ첾
		_gameMap->OnMove(-1 * _mapDisplayX,-1 * _mapDisplayY);

		//�C���������p�P�_(�i�J�U�@��)
		if (_player.checkTheTouch(_moveDoor->getTouchBox()) || (_playerInX <= 5  && _playerInY <= 5 && isSkip))
			return 1;

		return  0;
	}

	//��ܥ�����
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

	//���䰻���P�ǰe��T
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

	//�Ѻc
	controlGame::~controlGame()
	{
		clearList();
	}

	//����M�z
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