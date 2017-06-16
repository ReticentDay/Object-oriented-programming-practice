
#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "touchBox.h"
#include "hitBox.h"

namespace game_framework {

	hitBox::hitBox(int X, int Y, int height, int weight, int moveX, int moveY) :_upX(X), _upY(Y), _height(height), _weight(weight), _moveX(moveX), _moveY(moveY)
	{
		_orangeX = X;
		_orangeY = Y;
		_beHit = false;
		_moveStep = 7;
		hitPath = new touchBox(X, Y, X + weight, Y + height, true);
		if (moveX < 0) 
			_hitBit.LoadBitmapA(IDB_HITSHORTL,RGB(255,255,255));
		else if(moveX > 0)
			_hitBit.LoadBitmapA(IDB_HITSHORTR, RGB(255, 255, 255));
		else if (moveY < 0)
			_hitBit.LoadBitmapA(IDB_HITSHORTUP, RGB(255, 255, 255));
		else if (moveY > 0)
			_hitBit.LoadBitmapA(IDB_HITSHORTDown, RGB(255, 255, 255));
		else
			_hitBit.LoadBitmapA(IDB_HITSHORTDown, RGB(255, 255, 255));
	}

	bool hitBox::OnMove(int x, int y)
	{
		_orangeX += _moveX;
		_orangeY += _moveY;
		_upX = x + _orangeX;
		_upY = y + _orangeY;
		_moveStep--;
		//碰觸邊界即消滅
		if (_orangeX > 1440 || _orangeY > 1440 || _orangeX < 0 || _orangeY < 0)
			return 1;
		//碰觸物件即消滅
		if (_beHit)
			return 1;
		//飛行距離超過即消滅
		if (_moveStep <= 0)
			return 1;
		return 0;
	}

	//以碰觸設定
	void hitBox::beHit()
	{
		_beHit = true;
	}

	touchBox * hitBox::getTouchBox()
	{
		return hitPath;
	}
	
	void hitBox::OnShow()
	{
		_hitBit.SetTopLeft(_upX, _upY);
		_hitBit.ShowBitmap();
		hitPath->setBox(_upX, _upY, _upX + _height, _upY + _weight);
	}

	hitBox::~hitBox()
	{
		free(hitPath);
	}
}