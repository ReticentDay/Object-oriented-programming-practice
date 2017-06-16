#pragma once
#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <vector>
#include "infoShowList.h"
#include <sstream>

namespace game_framework {
	//將要顯示之物件放入繪圖駐列中
	void infoShowList::showBox(DrawBox * drawList)
	{
		for (vector<show*>::iterator i = list.begin();i != list.end();)
		{
			drawList->AddIt((*i)->x1, (*i)->y1 + 6, RGB(0, 0, 0), 140, (*i)->line);
			drawList->AddIt((*i)->x1, (*i)->y1, (*i)->x1 + 300, (*i)->y1 + 40, RGB(255, 255, 0), RGB(255, 255, 0));
			
			if ((*i)->flag == 1)
				(*i)->y1 += 1;
			else if ((*i)->flag == 0)
				(*i)->count--;
			else if ((*i)->flag == -1)
				(*i)->y1 -= 1;

			if ((*i)->y1 > 0)
				(*i)->flag = 0;
			if((*i)->count < 0)
				(*i)->flag = -1;

			if ((*i)->y1 < -60)
				i = list.erase(i);
			else
				i++;
		}
	}
	//增加要繪製之成就方塊
	void infoShowList::addShowBox(int x1, int y1, CString line)
	{
		show *put = new show();
		put->x1 = x1;put->y1 = y1;
		put->line = line;
		put->flag = 1;
		put->count = 30;
		list.push_back(put);
	}
}