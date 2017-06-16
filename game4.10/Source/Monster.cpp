#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "touchBox.h"
#include "hitBox.h"
#include "Monster.h"

namespace game_framework {
	Monster::Monster(int x, int y) :_setX(x), _setY(y), _direction(0)
	{
		step = 0;
		move_lone = 2;
		_orangeX = _setX;
		_orangeY = _setY;
		_HP = 10;
		_hitBit = 0;
		_monsterBody = new touchBox(_setX, _setY, _setX + PLAYER_WEIGHT, _setY + PLYAER_HIGHT,true);
		_monsterEyes = new touchBox(_setX - 30, _setY + PLYAER_HIGHT, _setX + PLAYER_WEIGHT + 30, _setY + PLYAER_HIGHT + EYES_LONG, true);
		_monsterHitEyes = new touchBox(_setX - 20, _setY + PLYAER_HIGHT, _setX + PLAYER_WEIGHT + 20, _setY + PLYAER_HIGHT + EYES_LONG, true);
	}

	int Monster::getType()
	{
		return type;
	}

	//依怪物種類讀入圖檔
	void Monster::LoadBitmap(int i)
	{
		if (i == 0) {
			type = 0;
			_monster.LoadBitmapA(IDB_MONSTER_DOWN1, RGB(255, 255, 255));

			_monsterLeft.AddBitmap(IDB_MONSTER_LEFT1, RGB(255, 255, 255));
			_monsterLeft.AddBitmap(IDB_MONSTER_LEFT2, RGB(255, 255, 255));
			_monsterLeft.AddBitmap(IDB_MONSTER_LEFT3, RGB(255, 255, 255));
			_monsterLeft.AddBitmap(IDB_MONSTER_LEFT4, RGB(255, 255, 255));

			_monsterUp.AddBitmap(IDB_MONSTER_UP1, RGB(255, 255, 255));
			_monsterUp.AddBitmap(IDB_MONSTER_UP2, RGB(255, 255, 255));
			_monsterUp.AddBitmap(IDB_MONSTER_UP3, RGB(255, 255, 255));
			_monsterUp.AddBitmap(IDB_MONSTER_UP4, RGB(255, 255, 255));

			_monsterDown.AddBitmap(IDB_MONSTER_DOWN1, RGB(255, 255, 255));
			_monsterDown.AddBitmap(IDB_MONSTER_DOWN2, RGB(255, 255, 255));
			_monsterDown.AddBitmap(IDB_MONSTER_DOWN3, RGB(255, 255, 255));
			_monsterDown.AddBitmap(IDB_MONSTER_DOWN4, RGB(255, 255, 255));

			_monsterRight.AddBitmap(IDB_MONSTER_RIGHT1, RGB(255, 255, 255));
			_monsterRight.AddBitmap(IDB_MONSTER_RIGHT2, RGB(255, 255, 255));
			_monsterRight.AddBitmap(IDB_MONSTER_RIGHT3, RGB(255, 255, 255));
			_monsterRight.AddBitmap(IDB_MONSTER_RIGHT4, RGB(255, 255, 255));
		}
		else if (i == 1) {
			type = 1;
			_monster.LoadBitmapA(IDB_CHICKEN_DOWN1, RGB(255, 255, 255));

			_monsterLeft.AddBitmap(IDB_CHICKEN_LEFT1, RGB(255, 255, 255));
			_monsterLeft.AddBitmap(IDB_CHICKEN_LEFT2, RGB(255, 255, 255));
			_monsterLeft.AddBitmap(IDB_CHICKEN_LEFT3, RGB(255, 255, 255));
			_monsterLeft.AddBitmap(IDB_CHICKEN_LEFT2, RGB(255, 255, 255));

			_monsterUp.AddBitmap(IDB_CHICKEN_UP1, RGB(255, 255, 255));
			_monsterUp.AddBitmap(IDB_CHICKEN_UP2, RGB(255, 255, 255));
			_monsterUp.AddBitmap(IDB_CHICKEN_UP3, RGB(255, 255, 255));
			_monsterUp.AddBitmap(IDB_CHICKEN_UP2, RGB(255, 255, 255));

			_monsterDown.AddBitmap(IDB_CHICKEN_DOWN1, RGB(255, 255, 255));
			_monsterDown.AddBitmap(IDB_CHICKEN_DOWN2, RGB(255, 255, 255));
			_monsterDown.AddBitmap(IDB_CHICKEN_DOWN3, RGB(255, 255, 255));
			_monsterDown.AddBitmap(IDB_CHICKEN_DOWN2, RGB(255, 255, 255));

			_monsterRight.AddBitmap(IDB_CHICKEN_RIGHT1, RGB(255, 255, 255));
			_monsterRight.AddBitmap(IDB_CHICKEN_RIGHT2, RGB(255, 255, 255));
			_monsterRight.AddBitmap(IDB_CHICKEN_RIGHT3, RGB(255, 255, 255));
			_monsterRight.AddBitmap(IDB_CHICKEN_RIGHT2, RGB(255, 255, 255));
		}
		else if (i == 2) {
			type = 2;
			_monster.LoadBitmapA(IDB_SNOWMAN_DOWN1, RGB(255, 255, 255));

			_monsterLeft.AddBitmap(IDB_SNOWMAN_LEFT1, RGB(255, 255, 255));
			_monsterLeft.AddBitmap(IDB_SNOWMAN_LEFT2, RGB(255, 255, 255));
			_monsterLeft.AddBitmap(IDB_SNOWMAN_LEFT3, RGB(255, 255, 255));
			_monsterLeft.AddBitmap(IDB_SNOWMAN_LEFT2, RGB(255, 255, 255));

			_monsterUp.AddBitmap(IDB_SNOWMAN_UP1, RGB(255, 255, 255));
			_monsterUp.AddBitmap(IDB_SNOWMAN_UP2, RGB(255, 255, 255));
			_monsterUp.AddBitmap(IDB_SNOWMAN_UP3, RGB(255, 255, 255));
			_monsterUp.AddBitmap(IDB_SNOWMAN_UP2, RGB(255, 255, 255));

			_monsterDown.AddBitmap(IDB_SNOWMAN_DOWN1, RGB(255, 255, 255));
			_monsterDown.AddBitmap(IDB_SNOWMAN_DOWN2, RGB(255, 255, 255));
			_monsterDown.AddBitmap(IDB_SNOWMAN_DOWN3, RGB(255, 255, 255));
			_monsterDown.AddBitmap(IDB_SNOWMAN_DOWN2, RGB(255, 255, 255));

			_monsterRight.AddBitmap(IDB_SNOWMAN_RIGHT1, RGB(255, 255, 255));
			_monsterRight.AddBitmap(IDB_SNOWMAN_RIGHT2, RGB(255, 255, 255));
			_monsterRight.AddBitmap(IDB_SNOWMAN_RIGHT3, RGB(255, 255, 255));
			_monsterRight.AddBitmap(IDB_SNOWMAN_RIGHT2, RGB(255, 255, 255));
		}
		else {
			_monster.LoadBitmapA(IDB_MONSTER_DOWN1, RGB(255, 255, 255));

			_monsterLeft.AddBitmap(IDB_MONSTER_LEFT1, RGB(255, 255, 255));
			_monsterLeft.AddBitmap(IDB_MONSTER_LEFT2, RGB(255, 255, 255));
			_monsterLeft.AddBitmap(IDB_MONSTER_LEFT3, RGB(255, 255, 255));
			_monsterLeft.AddBitmap(IDB_MONSTER_LEFT4, RGB(255, 255, 255));

			_monsterUp.AddBitmap(IDB_MONSTER_UP1, RGB(255, 255, 255));
			_monsterUp.AddBitmap(IDB_MONSTER_UP2, RGB(255, 255, 255));
			_monsterUp.AddBitmap(IDB_MONSTER_UP3, RGB(255, 255, 255));
			_monsterUp.AddBitmap(IDB_MONSTER_UP4, RGB(255, 255, 255));

			_monsterDown.AddBitmap(IDB_MONSTER_DOWN1, RGB(255, 255, 255));
			_monsterDown.AddBitmap(IDB_MONSTER_DOWN2, RGB(255, 255, 255));
			_monsterDown.AddBitmap(IDB_MONSTER_DOWN3, RGB(255, 255, 255));
			_monsterDown.AddBitmap(IDB_MONSTER_DOWN4, RGB(255, 255, 255));

			_monsterRight.AddBitmap(IDB_MONSTER_RIGHT1, RGB(255, 255, 255));
			_monsterRight.AddBitmap(IDB_MONSTER_RIGHT2, RGB(255, 255, 255));
			_monsterRight.AddBitmap(IDB_MONSTER_RIGHT3, RGB(255, 255, 255));
			_monsterRight.AddBitmap(IDB_MONSTER_RIGHT4, RGB(255, 255, 255));
		}
	}

	bool Monster::OnMove(int x, int y, const vector<touchBox*> &list,touchBox* player, vector<hitBox*> &hitList, vector<hitBox*> &monsterHitList)
	{
		step--;
		//怪物位置移動計算
		switch (_direction)
		{
		case 1:
			if (_orangeY + move_lone + 48 < 1440 && !this->checkTheTouch(list, 0, move_lone))
				_orangeY += move_lone;
			else
				step = 0;
			break;
		case 2:
			if (_orangeY - move_lone > 0 && !this->checkTheTouch(list, 0, -move_lone))
				_orangeY -= move_lone;
			else
				step = 0;
			break;
		case 3:
			if (_orangeX - move_lone > 0 && !this->checkTheTouch(list, -move_lone, 0))
				_orangeX -= move_lone;
			else
				step = 0;
			break;
		case 4:
			if (_orangeX + move_lone + 48 < 1440 && !this->checkTheTouch(list, move_lone, 0))
				_orangeX += move_lone;
			else
				step = 0;
			break;
		default:
			break;
		}

		_setX = x + _orangeX;
		_setY = y + _orangeY;
		//碰撞位置設置
		_monsterBody->setBox(_setX, _setY, _setX + PLAYER_WEIGHT, _setY + PLYAER_HIGHT);
		switch (_direction)
		{
		case 1:
			_monsterEyes->setBox(_setX - 50, _setY + PLYAER_HIGHT, _setX + PLAYER_WEIGHT + 50, _setY + PLYAER_HIGHT + EYES_LONG);
			_monsterHitEyes->setBox(_setX , _setY + PLYAER_HIGHT, _setX + PLAYER_WEIGHT , _setY + PLYAER_HIGHT + 20);
			break;
		case 2:
			_monsterEyes->setBox(_setX - 50, _setY - EYES_LONG, _setX + PLAYER_WEIGHT + 50, _setY);
			_monsterHitEyes->setBox(_setX , _setY - 20, _setX + PLAYER_WEIGHT, _setY);
			break;
		case 3:
			_monsterEyes->setBox(_setX - EYES_LONG, _setY - 50, _setX, _setY + PLYAER_HIGHT + 50);
			_monsterHitEyes->setBox(_setX - 20, _setY, _setX, _setY + PLYAER_HIGHT);
			break;
		case 4:
			_monsterEyes->setBox(_setX + PLAYER_WEIGHT, _setY - 50, _setX + PLAYER_WEIGHT + EYES_LONG, _setY + PLYAER_HIGHT + 50);
			_monsterHitEyes->setBox(_setX + PLAYER_WEIGHT, _setY, _setX + PLAYER_WEIGHT + 20, _setY + PLYAER_HIGHT);
			break;
		default:
			break;
		}
		_monsterDown.OnMove();
		_monsterUp.OnMove();
		_monsterLeft.OnMove();
		_monsterRight.OnMove();

		//怪物攻擊
		if (_monsterHitEyes->checkTouch(player) && _hitBit <= 0) {
			monsterHitList.push_back(addHitBox(_orangeX, _orangeY));
			_hitBit = 10;
		}
		if (_hitBit >= 0)
			_hitBit--;

		//怪物位移判斷
		//玩家進入視野判斷
		if (_monsterEyes->checkTouch(player)) {
			int xtt = _setX + (PLAYER_WEIGHT / 2);
			int ytt = _setY + (PLYAER_HIGHT / 2);
			int x1 = _monsterEyes->getPathX1(player);
			int x2 = _monsterEyes->getPathX2(player);
			int y1 = _monsterEyes->getPathY1(player);
			int y2 = _monsterEyes->getPathY2(player);
			int xm = abs(xtt - x1) > abs(xtt - x2) ? (xtt - x1): (xtt - x2);
			int ym = abs(ytt - y1) > abs(ytt - y2) ? (ytt - y1) : (ytt - y2);
			if (abs(xm) > abs(ym)) {
				if (xm > 0) {
					_direction = 3;
					step = abs(xm) / move_lone + 1;
				}
				else {
					_direction = 4;
					step = abs(xm) / move_lone + 1;
				}
			}
			else {
				if (ym > 0) {
					_direction = 2;
					step = abs(ym) / move_lone + 1;
				}
				else {
					_direction = 1;
					step = abs(ym) / move_lone + 1;
				}
			}
			move_lone = 10;
		}
		//隨機走動
		else {
			srand((int)time(NULL));

			if (step <= 0) {
				_direction = (int)(rand() % 4) + 1;
				step = (int)(rand() % 500) + 1;
			}
			move_lone = 1;
		}

		//偵測是否被攻擊
		for (vector<hitBox*>::iterator i = hitList.begin(); i != hitList.end();i++) {
			if (this->checkTheTouch((*i)->getTouchBox())) {
				(*i)->beHit();
				_HP--;
			}
		}
		//回傳死亡資訊
		if (_HP <= 0)
			return 1;
		return 0;
	}

	//偵測碰撞
	bool Monster::checkTheTouch(touchBox * listss)
	{
		if (_monsterBody->checkTouch(listss)) {
			return true;
		}
		return false;
	}
	bool Monster::checkTheTouch(vector<touchBox*> listss)
	{
		for (vector<touchBox*>::iterator i = listss.begin(); i != listss.end(); i++)
		{
			if (_monsterBody->checkTouch(*i)) {
				return true;
			}
		}
		return false;
	}
	bool Monster::checkTheTouch(vector<touchBox*> listss, int x, int y)
	{
		for (vector<touchBox*>::iterator i = listss.begin(); i != listss.end(); i++)
		{
			if (_monsterBody->checkTouch(*i, x, y)) {
				return true;
			}
		}
		return false;
	}

	//進行攻擊
	hitBox * Monster::addHitBox(int _setX, int _setY)
	{
		hitBox * put;
		CAudio::Instance()->Play(4, false);
		if (_direction == 1 || (_direction == 0)) {
			put = new hitBox(_setX, _setY + PLYAER_HIGHT, 24, 48, 0, 3);
		}
		else if (_direction == 2 || (_direction == 0)) {
			put = new hitBox(_setX, _setY - 24, 24, 48, 0, -3);
		}
		else if (_direction == 3 || (_direction == 0)) {
			put = new hitBox(_setX - 24, _setY + 9, 48, 24, -3, 0);
		}
		else if (_direction == 4 || (_direction == 0 )) {
			put = new hitBox(_setX + PLAYER_WEIGHT, _setY + 9, 48, 24, 3, 0);
		}
		return put;
	}

	void Monster::OnShow(DrawBox *drawList)
	{
		_monsterBody->setBox(_setX, _setY, _setX + PLAYER_WEIGHT, _setY + PLYAER_HIGHT);
		if (_direction == 0) {
			_monster.SetTopLeft(_setX, _setY);
			_monster.ShowBitmap();
		}
		else if (_direction == 1) {
			_monsterDown.SetTopLeft(_setX, _setY);
			_monsterDown.OnShow();
		}
		else if (_direction == 2) {
			_monsterUp.SetTopLeft(_setX, _setY);
			_monsterUp.OnShow();
		}
		else if (_direction == 3) {
			_monsterLeft.SetTopLeft(_setX, _setY);
			_monsterLeft.OnShow();
		}
		else if (_direction == 4) {
			_monsterRight.SetTopLeft(_setX, _setY);
			_monsterRight.OnShow();
		}
		drawList->AddIt(_setX, _setY + PLYAER_HIGHT, _setX + PLAYER_WEIGHT, _setY + PLYAER_HIGHT + 10, RGB(255, 255, 0), RGB(255, 255, 255));
		drawList->AddIt(_setX, _setY + PLYAER_HIGHT, _setX + (PLAYER_WEIGHT / 10) * _HP, _setY + PLYAER_HIGHT + 10, RGB(255, 255, 0), RGB(255, 0, 0));
	}

	Monster::~Monster()
	{
		delete _monsterBody;
		delete _monsterEyes;
		delete _monsterHitEyes;
	}
}