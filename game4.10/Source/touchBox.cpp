#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "touchBox.h"

namespace game_framework {
	touchBox::touchBox(int upX, int upY, int downX, int downY, bool drawB) : _upX(upX) , _upY(upY), _downX(downX), _downY(downY),_boxShow(drawB)
	{
		
	}
	//設定碰撞方塊大小
	void touchBox::setBox(int upX, int upY, int downX, int downY)
	{
		_upX = upX;
		_upY = upY;
		_downX = downX;
		_downY = downY;
	}

	//偵測碰撞
	bool touchBox::checkTouch(touchBox* B)
	{
		int Xb1 = B->_upX;
		int Xb2 = B->_downX;
		int Yb1 = B->_upY;
		int Yb2 = B->_downY;
		int Xa1 = this->_upX;
		int Xa2 = this->_downX;
		int Ya1 = this->_upY;
		int Ya2 = this->_downY;
		if (abs(Xb2 + Xb1 - Xa2 - Xa1) <= (Xa2 - Xa1 + Xb2 - Xb1) && abs(Yb2 + Yb1 - Ya2 - Ya1) <= Ya2 - Ya1 + Yb2 - Yb1)
			return true;
		return false;
	}
	bool touchBox::checkTouch(touchBox *B, int x, int y)
	{
		int Xb1 = B->_upX;
		int Xb2 = B->_downX;
		int Yb1 = B->_upY;
		int Yb2 = B->_downY;
		int Xa1 = this->_upX + x;
		int Xa2 = this->_downX + x;
		int Ya1 = this->_upY + y;
		int Ya2 = this->_downY + y;
		if (abs(Xb2 + Xb1 - Xa2 - Xa1) <= (Xa2 - Xa1 + Xb2 - Xb1) && abs(Yb2 + Yb1 - Ya2 - Ya1) <= Ya2 - Ya1 + Yb2 - Yb1)
			return true;
		return false;
	}

	//取得碰撞方塊重疊大小
	int touchBox::getPathX1(touchBox * B)
	{
		return max(this->_upX, B->_upX);
	}
	int touchBox::getPathX2(touchBox * B)
	{
		return min(this->_downX, B->_downX);
	}
	int touchBox::getPathY1(touchBox * B)
	{
		return max(this->_upY, B->_upY);
	}
	int touchBox::getPathY2(touchBox * B)
	{
		return min(this->_downY, B->_downY);
	}

	touchBox::~touchBox()
	{
	}
}