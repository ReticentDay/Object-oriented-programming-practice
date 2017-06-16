#pragma once
#include "touchBox.h"
#include <vector>
#include "DrawBox.h"
#include "hitBox.h"
namespace game_framework {
	//怪物物件
	class  Monster
	{
	public:
		Monster(int x, int y);
		void LoadBitmap(int i);
		bool OnMove(int x, int y,const vector<touchBox*> &list, touchBox* player,vector<hitBox*> &hitList, vector<hitBox*> &monsterHitList);
		bool checkTheTouch(touchBox* listss);
		bool checkTheTouch(vector<touchBox*> listss);
		bool checkTheTouch(vector<touchBox*> listss, int x, int y);
		hitBox* addHitBox(int x, int y);
		void OnShow(DrawBox *drawList);
		int Monster::getType();
		void DrawIt();
		~Monster();
	protected:

	private:
		const int PLYAER_HIGHT = 48, PLAYER_WEIGHT = 48;
		const int EYES_LONG = 100;
		int type;
		CMovingBitmap _monster;
		CAnimation _monsterLeft;
		CAnimation _monsterUp;
		CAnimation _monsterDown;
		CAnimation _monsterRight;
		int _direction;
		int move_lone;
		touchBox *_monsterBody;		//怪物本體碰撞方塊
		touchBox *_monsterEyes;		//怪物視野碰撞方塊
		touchBox *_monsterHitEyes;	//怪物攻擊範圍碰撞方塊
		int _hitBit;
		int _setX, _setY;
		int _orangeX, _orangeY;
		int step;
		int _HP;
	};
}