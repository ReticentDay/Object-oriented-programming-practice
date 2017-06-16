#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "touchBox.h"
#include "Obstacle.h"

namespace game_framework {
	Obstacle::Obstacle(int x,int y,int i,int height,int weight) :_orangeX(x), _orangeY(y),obstacle_height(height),obstacle_weith(weight),mapName(i)
	{
		_setX = _orangeX;
		_setY = _orangeY;
		_obstacleBody = new touchBox(_setX, _setY, _setX + obstacle_weith, _setY + obstacle_height,true);
	}

	void Obstacle::LoadBitmap()
	{
		_obstacle.LoadBitmapA(mapName,RGB(255,255,255));
	}

	//回傳物件本體碰撞方塊
	touchBox * Obstacle::getTouchBox()
	{
		return _obstacleBody;
	}

	void Obstacle::OnMove(int x, int y, vector<hitBox*> &_hitBoxList)
	{
		_setX = x + _orangeX;_setY = y + _orangeY;
		_obstacleBody->setBox(_setX, _setY, _setX + obstacle_weith, _setY + obstacle_height); 
		for (vector<hitBox*>::iterator i = _hitBoxList.begin(); i != _hitBoxList.end(); i++) {
			if (_obstacleBody->checkTouch((*i)->getTouchBox())) {
				(*i)->beHit();
			}
		}
	}

	void Obstacle::OnShow()
	{
		_obstacle.SetTopLeft(_setX, _setY);
		_obstacle.ShowBitmap();
	}
	
	Obstacle::~Obstacle()
	{
		delete _obstacleBody;
	}
}