#pragma once
#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <vector>
#include "GameInfoList.h"
#include <sstream>
#include "DrawBox.h"

namespace game_framework {
	GameInfoList::GameInfoList()
	{
	}
	string GameInfoList::showInfo()
	{
		return string();
	}
	void GameInfoList::setCount(int count)
	{
	}
	int GameInfoList::returnCount()
	{
		return 0;
	}
	//輸入稱號
	GameInfoString::GameInfoString(string name)
	{
		_name = name;
		
	}
	string GameInfoString::showInfo()
	{
		return "獲得稱號：" + _name;
	}
	//輸入稱號
	GameInfoCount::GameInfoCount(string name, int count , string backInfo)
	{
		_name = name;
		_count = count;
		_backInfo = backInfo;
	}
	void GameInfoCount::setCount(int count)
	{
		_count = count;
	}
	int GameInfoCount::returnCount()
	{
		return _count;
	}
	string GameInfoCount::showInfo()
	{
		stringstream stream;
		stream << "你" << _name << _count << _backInfo;
		string out; 
		stream >> out;
		return out;
	}
}