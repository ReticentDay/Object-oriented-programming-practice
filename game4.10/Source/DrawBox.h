#pragma once
namespace game_framework {
	//�|�����O
	class  DrawBox
	{
	public:
		DrawBox();
		void AddIt(int X1, int Y1, int X2, int Y2, COLORREF Pen, COLORREF Brush);
		void AddIt(int X1, int Y1, COLORREF Pen, int size, CString list);
		void DrawIt();
		~DrawBox();
	protected:

	private:
		//�x�}ø�ϸ�T
		struct XYRGB
		{
			int X1, Y1, X2, Y2;
			COLORREF _Pen;
			COLORREF _Brush;
		};
		//��rø�ϸ�T
		struct stringBox
		{
			int X1, Y1;
			CString line;
			COLORREF _Pen;
			int size;
		};
		vector<XYRGB> _drawList;
		vector<stringBox> List;
	};
}