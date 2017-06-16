#pragma once
#include "touchBox.h"
#include "hitBox.h"
#include <vector>
#include "DrawBox.h"

namespace game_framework {
	//玩家類別
	class  Player
	{
	public:
		Player();
		void LoadBitmap();
		void playerReset();
		int OnMove(int x,int y,int direction, vector<hitBox*> &monsterHitList);
		bool checkTheTouch(touchBox* listss);
		bool checkTheTouch(vector<touchBox*> listss);
		bool checkTheTouch(vector<touchBox*> listss,int x,int y);
		touchBox* getPlayerTouchBox();
		hitBox* addHitBox(int x, int y);
		void OnShow(DrawBox *drawList);
		~Player();
	protected:
		
	private:
		const int PLYAER_HIGHT = 49, PLAYER_WEIGHT = 31;	//玩家長寬
		CMovingBitmap _playerDownB;
		CMovingBitmap _playerLeftB;
		CMovingBitmap _playerUpB;
		CMovingBitmap _playerRightB;
		CAnimation _playerLeft;
		CAnimation _playerUp;
		CAnimation _playerDown;
		CAnimation _playerRight;
		int upType;											//玩家上個走動方向
		int _direction;										//玩家目前走動方向
		touchBox *_playerBody;
		bool _touchBoxShow;
		int _setX, _setY;
		int _playerLife;									//玩家血量
	};
}