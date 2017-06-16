#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"
#include <ctime>
#include <cstdlib>

namespace game_framework {
	GameMap::GameMap(int mapStyle):_setX(0),_setY(0)
	{
		_mapStyle = mapStyle;
	}
	void GameMap::SetMapStyle(int mapStyle)
	{
		_mapStyle = mapStyle;
	}
	//讀入全地圖後分割存至陣列
	void GameMap::LoadBitmap()
	{
		const int MAP_RANGE = 5;
		const int ELEMENT_RANGE = 288;

		CMovingBitmap* tempMapLand1 = new CMovingBitmap;
		tempMapLand1->LoadBitmapA(IDB_LAND1);
		_land.push_back(tempMapLand1);

		CMovingBitmap* tempMapLand2 = new CMovingBitmap;
		tempMapLand2->LoadBitmapA(IDB_LAND2);
		_land.push_back(tempMapLand2);

		CMovingBitmap* tempMapLand3 = new CMovingBitmap;
		tempMapLand3->LoadBitmapA(IDB_LAND3);
		_land.push_back(tempMapLand3);

		CMovingBitmap* tempMapLand4 = new CMovingBitmap;
		tempMapLand4->LoadBitmapA(IDB_LAND4);
		_land.push_back(tempMapLand4);

		CMovingBitmap* tempMapLand5 = new CMovingBitmap;
		tempMapLand5->LoadBitmapA(IDB_LAND5);
		_land.push_back(tempMapLand5);

		CMovingBitmap* tempMapDessert1= new CMovingBitmap;
		tempMapDessert1->LoadBitmapA(IDB_DESSERT5);
		_dessert.push_back(tempMapDessert1);

		CMovingBitmap* tempMapDessert2 = new CMovingBitmap;
		tempMapDessert2->LoadBitmapA(IDB_DESSERT2);
		_dessert.push_back(tempMapDessert2);

		CMovingBitmap* tempMapDessert3 = new CMovingBitmap;
		tempMapDessert3->LoadBitmapA(IDB_DESSERT3);
		_dessert.push_back(tempMapDessert3);

		CMovingBitmap* tempMapDessert4 = new CMovingBitmap;
		tempMapDessert4->LoadBitmapA(IDB_DESSERT4);
		_dessert.push_back(tempMapDessert4);

		CMovingBitmap* tempMapDessert5 = new CMovingBitmap;
		tempMapDessert5->LoadBitmapA(IDB_DESSERT5);
		_dessert.push_back(tempMapDessert5);

		CMovingBitmap* tempMapSnow1 = new CMovingBitmap;
		tempMapSnow1->LoadBitmapA(IDB_SNOW1);
		_snow.push_back(tempMapSnow1);

		CMovingBitmap* tempMappSnow2 = new CMovingBitmap;
		tempMappSnow2->LoadBitmapA(IDB_SNOW2);
		_snow.push_back(tempMappSnow2);

		CMovingBitmap* tempMappSnow3 = new CMovingBitmap;
		tempMappSnow3->LoadBitmapA(IDB_SNOW3);
		_snow.push_back(tempMappSnow3);

		CMovingBitmap* tempMappSnow4 = new CMovingBitmap;
		tempMappSnow4->LoadBitmapA(IDB_SNOW4);
		_snow.push_back(tempMappSnow4);

		CMovingBitmap* tempMappSnow5 = new CMovingBitmap;
		tempMappSnow5->LoadBitmapA(IDB_SNOW5);
		_snow.push_back(tempMappSnow5);

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				_landSet[i][j] = *(_land[j % MAP_RANGE]);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				_dessertSet[i][j] = *(_dessert[j % MAP_RANGE]);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				_snowSet[i][j] = *(_snow[j % MAP_RANGE]);
			}
		}
	}
	void GameMap::OnMove(int x, int y)
	{
		_setX = x;
		_setY = y;
	}
	void GameMap::OnShow()
	{
		const int ELEMENT_RANGE = 288;
		int setX = _setX * -1;
		int setY = _setY * -1;
		int i_o = setX / ELEMENT_RANGE;
		int j_o = setY / ELEMENT_RANGE;

		//依資訊判斷顯示地圖
		switch (_mapStyle)
		{
		case 1:
			for (int i = 0;i < ((setX - (ELEMENT_RANGE * i_o)) < 224 ? 3 : 4) && i + i_o < 5;i++) {							//int i_o = setX / ELEMENT_RANGE;
				for (int j = 0;j < ((setY - (ELEMENT_RANGE * j_o)) < 95 ? 2 : 3) && j + j_o < 5;j++) {						//int j_o = setY / ELEMENT_RANGE;
					_landSet[i + i_o][j + j_o].SetTopLeft(_setX + ELEMENT_RANGE * (i_o + i), _setY + ELEMENT_RANGE * (j + j_o));
					_landSet[i + i_o][j + j_o].ShowBitmap();
				}
			}
			break;
		case 2:
			for (int i = 0;i < ((setX - (ELEMENT_RANGE * i_o)) < 224 ? 3 : 4) && i + i_o < 5;i++) {							//int i_o = setX / ELEMENT_RANGE;
				for (int j = 0;j < ((setY - (ELEMENT_RANGE * j_o)) < 95 ? 2 : 3) && j + j_o < 5;j++) {						//int j_o = setY / ELEMENT_RANGE;
					_dessertSet[i + i_o][j + j_o].SetTopLeft(_setX + ELEMENT_RANGE * (i_o + i), _setY + ELEMENT_RANGE * (j + j_o));
					_dessertSet[i + i_o][j + j_o].ShowBitmap();
				}
			}
			break;
		case 3:
			for (int i = 0;i < ((setX - (ELEMENT_RANGE * i_o)) < 224 ? 3 : 4) && i + i_o < 5;i++) {							//int i_o = setX / ELEMENT_RANGE;
				for (int j = 0;j < ((setY - (ELEMENT_RANGE * j_o)) < 95 ? 2 : 3) && j + j_o < 5;j++) {						//int j_o = setY / ELEMENT_RANGE;
					_snowSet[i + i_o][j + j_o].SetTopLeft(_setX + ELEMENT_RANGE * (i_o + i), _setY + ELEMENT_RANGE * (j + j_o));
					_snowSet[i + i_o][j + j_o].ShowBitmap();
				}
			}
			break;
		default:
			break;
		}
	}
	int GameMap::GetStyle()
	{
		return _mapStyle;
	}
	GameMap::~GameMap()
	{
		for (vector<CMovingBitmap*>::iterator i = _land.begin();i != _land.end();i++)
			delete *i;
		for (vector<CMovingBitmap*>::iterator i = _dessert.begin();i != _dessert.end();i++)
			delete *i;
		for (vector<CMovingBitmap*>::iterator i = _snow.begin();i != _snow.end();i++)
			delete *i;
		_land.clear();
		_dessert.clear();
		_snow.clear();
	}
}