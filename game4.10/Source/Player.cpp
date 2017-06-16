#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "touchBox.h"
#include "Player.h"

namespace game_framework {

	Player::Player() :_setX(0), _setY(0), _direction(0),_touchBoxShow(true)
	{
		_playerBody = new touchBox(_setX, _setY, _setX + PLAYER_WEIGHT, _setY + PLYAER_HIGHT, _touchBoxShow);
		_playerLife = 10;
	}

	void Player::LoadBitmap()
	{
		_playerDownB.LoadBitmapA(IDB_PLAYER_DOWN1, RGB(240, 248, 255));
		_playerLeftB.LoadBitmapA(IDB_PLAYER_LEFT1, RGB(240, 248, 255));
		_playerUpB.LoadBitmapA(IDB_PLAYER_UP1, RGB(240, 248, 255));
		_playerRightB.LoadBitmapA(IDB_PLAYER_RIGHT1, RGB(240, 248, 255));
		
		_playerLeft.AddBitmap(IDB_PLAYER_LEFT1, RGB(240, 248, 255));
		_playerLeft.AddBitmap(IDB_PLAYER_LEFT2, RGB(240, 248, 255));
		_playerLeft.AddBitmap(IDB_PLAYER_LEFT3, RGB(240, 248, 255));
		_playerLeft.AddBitmap(IDB_PLAYER_LEFT4, RGB(240, 248, 255));

		_playerUp.AddBitmap(IDB_PLAYER_UP1, RGB(240, 248, 255));
		_playerUp.AddBitmap(IDB_PLAYER_UP2, RGB(240, 248, 255));
		_playerUp.AddBitmap(IDB_PLAYER_UP3, RGB(240, 248, 255));
		_playerUp.AddBitmap(IDB_PLAYER_UP4, RGB(240, 248, 255));

		_playerDown.AddBitmap(IDB_PLAYER_DOWN1, RGB(240, 248, 255));
		_playerDown.AddBitmap(IDB_PLAYER_DOWN2, RGB(240, 248, 255));
		_playerDown.AddBitmap(IDB_PLAYER_DOWN3, RGB(240, 248, 255));
		_playerDown.AddBitmap(IDB_PLAYER_DOWN4, RGB(240, 248, 255));

		_playerRight.AddBitmap(IDB_PLAYER_RIGHT1, RGB(240, 248, 255));
		_playerRight.AddBitmap(IDB_PLAYER_RIGHT2, RGB(240, 248, 255));
		_playerRight.AddBitmap(IDB_PLAYER_RIGHT3, RGB(240, 248, 255));
		_playerRight.AddBitmap(IDB_PLAYER_RIGHT4, RGB(240, 248, 255));
	}

	//玩家數據初始化
	void Player::playerReset()
	{
		_playerLife = 10;
		upType = 1;
		_direction = 1;
		_setX = _setY = 0;
	}

	int Player::OnMove(int x, int y,int direction, vector<hitBox*> &monsterHitList)
	{
		_setX = x;
		_setY = y;
		_playerBody->setBox(_setX, _setY, _setX + PLAYER_WEIGHT, _setY + PLYAER_HIGHT);
		_direction = direction;
		_playerDown.OnMove();
		_playerUp.OnMove();
		_playerLeft.OnMove();
		_playerRight.OnMove();
		for (vector<hitBox*>::iterator i = monsterHitList.begin(); i != monsterHitList.end();i++) {
			if (this->checkTheTouch((*i)->getTouchBox())) {
				(*i)->beHit();
				_playerLife--;
			}
		}
		if (_playerLife <= 0)
			return 1;
		return 0;
	}

	//碰撞偵測
	bool Player::checkTheTouch(touchBox * listss)
	{
		if (_playerBody->checkTouch(listss)) {
			return true;
		}
		return false;
	}
	bool Player::checkTheTouch(vector<touchBox*> listss)
	{
		for (vector<touchBox*>::iterator i = listss.begin(); i != listss.end(); i++)
		{
			if (_playerBody->checkTouch(*i)) {
				return true;
			}
		}
		return false;
	}
	bool Player::checkTheTouch(vector<touchBox*> listss, int x, int y)
	{
		for (vector<touchBox*>::iterator i = listss.begin(); i != listss.end(); i++)
		{
			if (_playerBody->checkTouch(*i,x,y)) {
				return true;
			}
		}
		return false;
	}

	//回傳玩家本體碰撞方塊
	touchBox* Player::getPlayerTouchBox()
	{
		return _playerBody;
	}

	//玩家攻擊
	hitBox * Player::addHitBox(int _setX,int _setY)
	{
		hitBox * put;
		if (_direction == 1 || (_direction == 0 && upType == 1)) {
			put = new hitBox(_setX - 8, _setY + PLYAER_HIGHT, 24, 48, 0, 3);
		}
		else if (_direction == 2 || (_direction == 0 && upType == 2)) {
			put = new hitBox(_setX - 8, _setY - 24, 24, 48, 0, -3);
		}
		else if (_direction == 3 || (_direction == 0 && upType == 3)) {
			put = new hitBox(_setX - 24, _setY , 48, 24, -3, 0);
		}
		else if (_direction == 4 || (_direction == 0 && upType == 4)) {
			put = new hitBox(_setX + PLAYER_WEIGHT, _setY , 48, 24, 3, 0);
		}
		return put;
	}

	void Player::OnShow(DrawBox *drawList)
	{
		//依照玩家行走方向顯示
		_playerBody->setBox(_setX, _setY, _setX + PLAYER_WEIGHT, _setY + PLYAER_HIGHT);
		if (_direction == 0) {
			if (upType == 1) {
				_playerDownB.SetTopLeft(_setX, _setY);
				_playerDownB.ShowBitmap();
			}else if (upType == 2) {
				_playerUpB.SetTopLeft(_setX, _setY);
				_playerUpB.ShowBitmap();
			}
			else if (upType == 3) {
				_playerLeftB.SetTopLeft(_setX, _setY);
				_playerLeftB.ShowBitmap();
			}
			else if (upType == 4) {
				_playerRightB.SetTopLeft(_setX, _setY);
				_playerRightB.ShowBitmap();
			}
			else {
				_playerDownB.SetTopLeft(_setX, _setY);
				_playerDownB.ShowBitmap();
			}
		}
		else if (_direction == 1) {
			_playerDown.SetTopLeft(_setX, _setY);
			_playerDown.OnShow();
			upType = _direction;
		}
		else if (_direction == 2) {
			_playerUp.SetTopLeft(_setX, _setY);
			_playerUp.OnShow();
			upType = _direction;
		}
		else if (_direction == 3) {
			_playerLeft.SetTopLeft(_setX, _setY);
			_playerLeft.OnShow();
			upType = _direction;
		}
		else if (_direction == 4) {
			_playerRight.SetTopLeft(_setX, _setY);
			_playerRight.OnShow();
			upType = _direction;
		}

		drawList->AddIt(20, 440, 320, 460, RGB(255, 255, 0), RGB(255, 255, 255));
		drawList->AddIt(20, 440, 20 + 30 * _playerLife, 460, RGB(255, 255, 0), RGB(255, 0, 0));
	}

	Player::~Player()
	{
		delete _playerBody;
	}
}