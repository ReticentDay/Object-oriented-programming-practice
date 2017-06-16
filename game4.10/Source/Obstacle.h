#pragma once
#include "touchBox.h"
#include "hitBox.h"
#include <vector>
namespace game_framework {
	//�������O
	class  Obstacle
	{
	public:
		Obstacle(int x,int y, int i, int height, int weight);
		void LoadBitmap();
		touchBox* getTouchBox();
		void OnMove(int x,int y,vector<hitBox*> &_hitBoxList);
		void OnShow();
		~Obstacle();
	protected:

	private:
		int obstacle_height, obstacle_weith ;	//������e
		int mapName;
		CMovingBitmap _obstacle;
		touchBox *_obstacleBody;				//������I�����
		int _setX, _setY;
		int _orangeX, _orangeY;
	};
}