#pragma once

namespace game_framework {
	//§ðÀ»Ãþ§O
	class  hitBox
	{
	public:
		hitBox(int X, int Y, int height, int weight, int moveX, int moveY);
		bool OnMove(int x, int y);
		void beHit();
		touchBox* getTouchBox();
		void OnShow();
		~hitBox();
	protected:

	private:
		int _upX, _upY, _height, _weight;
		int _orangeX, _orangeY;
		int _moveX, _moveY;
		bool _boxShow;
		bool _beHit;
		int _moveStep;
		touchBox* hitPath;
		CMovingBitmap _hitBit;
	};
}
