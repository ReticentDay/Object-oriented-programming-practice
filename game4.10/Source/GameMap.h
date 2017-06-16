#pragma once
namespace game_framework {
	//地圖物件
	class  GameMap
	{
	public:
		GameMap(int mapStyle);
		void SetMapStyle(int mapStyle);
		void LoadBitmap();
		void OnMove(int x, int y);
		void OnShow();
		int GetStyle();
		~GameMap();
	protected:

	private:
		vector<CMovingBitmap*> _land;
		vector<CMovingBitmap*> _dessert;
		vector<CMovingBitmap*> _snow;
		CMovingBitmap _dessertSet[5][5];
		CMovingBitmap _landSet[5][5];
		CMovingBitmap _snowSet[5][5];
		int _setX, _setY;
		int _mapStyle;
	};
}