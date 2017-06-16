#pragma once
namespace game_framework {
	//¸I¼²¤è¶ôÃþ§O
	class  touchBox
	{
	public:
		touchBox(int upX,int upY, int downX, int downY,bool drawB);
		void setBox(int upX, int upY, int downX, int downY);
		void drawB(CDC *pDC);
		bool checkTouch(touchBox *B);
		bool checkTouch(touchBox *B,int x,int y);
		int getPathX1(touchBox *B);
		int getPathX2(touchBox *B);
		int getPathY1(touchBox *B);
		int getPathY2(touchBox *B);
		~touchBox();
	protected:

	private:
		int _upX, _upY,_downX,_downY;
		bool _boxShow;
	};
}