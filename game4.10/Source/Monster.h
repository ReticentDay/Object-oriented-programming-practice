#pragma once
#include "touchBox.h"
#include <vector>
#include "DrawBox.h"
#include "hitBox.h"
namespace game_framework {
	//�Ǫ�����
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
		touchBox *_monsterBody;		//�Ǫ�����I�����
		touchBox *_monsterEyes;		//�Ǫ������I�����
		touchBox *_monsterHitEyes;	//�Ǫ������d��I�����
		int _hitBit;
		int _setX, _setY;
		int _orangeX, _orangeY;
		int step;
		int _HP;
	};
}