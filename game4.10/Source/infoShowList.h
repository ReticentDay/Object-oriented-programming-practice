#pragma once
#include "DrawBox.h"

namespace game_framework {
	//成就顯示類別
	class  infoShowList
	{
	public:
		void showBox(DrawBox * drawList);
		void addShowBox(int x1,int y1,CString);
	private:
		struct show
		{
			int x1, y1;
			CString line;
			int flag = 1;
			int count = 5;
		};
		vector<show*> list;
	};
}