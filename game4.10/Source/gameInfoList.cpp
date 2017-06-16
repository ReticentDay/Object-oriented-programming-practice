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
	//��J�ٸ�
	GameInfoString::GameInfoString(string name)
	{
		_name = name;
		
	}
	string GameInfoString::showInfo()
	{
		return "��o�ٸ��G" + _name;
	}
	//��J�ٸ�
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
		stream << "�A" << _name << _count << _backInfo;
		string out; 
		stream >> out;
		return out;
	}
}