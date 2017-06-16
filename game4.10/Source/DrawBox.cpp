#pragma once
#include "StdAfx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "DrawBox.h"
#include <vector>

namespace game_framework {
	DrawBox::DrawBox()
	{
	}
	//新增繪圖資訊(方塊)
	void DrawBox::AddIt(int X1, int Y1, int X2, int Y2, COLORREF Pen, COLORREF Brush)
	{
		XYRGB put;
		put.X1 = X1;put.Y1 = Y1;
		put.X2 = X2;put.Y2 = Y2;
		put._Pen = Pen;put._Brush = Brush;
		_drawList.push_back(put);
	}
	//新增繪圖資訊(文字)
	void DrawBox::AddIt(int X1, int Y1, COLORREF Pen,int size, CString list)
	{
		stringBox put;
		put.X1 = X1;put.Y1 = Y1;
		put._Pen = Pen;
		put.line = list;
		put.size = size;
		List.push_back(put);
	}
	//全數繪出
	void DrawBox::DrawIt()
	{
		CDC *pDC = CDDraw::GetBackCDC();
		CPen* pOldPen;
		CBrush* pOldBrush;
		for each (XYRGB i in _drawList)
		{
			CPen pNewPen;
			pNewPen.CreatePen(PS_SOLID, 2, i._Pen);
			CBrush pNewBrush;
			pNewBrush.CreateSolidBrush(i._Brush);
			pOldPen = pDC->SelectObject(&pNewPen);
			pOldBrush = pDC->SelectObject(&pNewBrush);
			pDC->Rectangle(i.X1, i.Y1, i.X2, i.Y2);
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldBrush);
		}
		for each (stringBox i in List)
		{
			CFont f, *fp;
			f.CreatePointFont(i.size, "Times New Roman");
			fp = pDC->SelectObject(&f);	
			pDC->SetBkColor(RGB(255, 255, 0));
			pDC->SetTextColor(i._Pen);
			CString p = i.line;
			pDC->TextOut(i.X1, i.Y1, p);
			pDC->SelectObject(fp); 
		}
		CDDraw::ReleaseBackCDC();
		_drawList.clear();
		List.clear();
	}

	DrawBox::~DrawBox()
	{
	}
}
