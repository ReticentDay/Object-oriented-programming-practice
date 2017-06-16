/*
mygame.cpp: 本檔案儲遊戲本身的class的implementation
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <sstream>


namespace game_framework {
	// 這個class為遊戲的遊戲開頭畫面物件
	vector<GameInfoList*> List;
	int gameType;

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateInit::OnInit()
	{
		ShowInitProgress(0);
		logo.LoadBitmap(IDB_BACKGROUND);
		backGround.LoadBitmap(IDB_BACKGROUNDIMAGE);
		buttomEnter.LoadBitmap(IDB_BUTTOM_ENTER);
		buttomExit.LoadBitmap(IDB_BUTTOM_EXIT);
		buttomHelp.LoadBitmapA(IDB_BUTTOM);
		info.LoadBitmapA(IDB_INFO);
		buttomSelect.LoadBitmapA(IDB_SELECT, RGB(255, 255, 255));
	}

	void CGameStateInit::OnBeginState()
	{
		showHelp = false;
		select = 1;
	}

	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;					// keyboard ESC
		const char KEY_ENTER = 13;					// keyboard ENTER
		const char KEY_LEFT = 0x25;					// keyboard左箭頭
		const char KEY_UP = 0x26;					// keyboard上箭頭
		const char KEY_RIGHT = 0x27;				// keyboard右箭頭
		const char KEY_DOWN = 0x28;					// keyboard下箭頭
		if (nChar == KEY_UP && !showHelp)			// 選項往上移
			if (select > 1)
				select--;
		if (nChar == KEY_DOWN && !showHelp)			// 選項往下移
			if (select < 3)
				select++;
		if (nChar == KEY_ENTER && !showHelp) {		// 選擇選項
			if (select == 1)
				GotoGameState(GAME_STATE_RUN);
			if (select == 2)
				showHelp = true;
			if (select == 3)
				PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
		}
		if (nChar == KEY_ESC)
			if (showHelp)
				showHelp = false;
			else
				PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
	}

	void CGameStateInit::OnShow()
	{
		backGround.SetTopLeft(0, 0);
		backGround.ShowBitmap();
		buttomEnter.SetTopLeft(234, 240);
		buttomEnter.ShowBitmap();
		buttomHelp.SetTopLeft(234, 308);
		buttomHelp.ShowBitmap();
		buttomExit.SetTopLeft(234, 376);
		buttomExit.ShowBitmap();
		buttomSelect.SetTopLeft(234 - 48, 172 + select * 68);
		buttomSelect.ShowBitmap();

		//顯示Help
		if (showHelp == true) {
			CPen* pOldPen;
			CBrush* pOldBrush;
			CDC *pDC = CDDraw::GetBackCDC();
			CPen pNewPen;
			pNewPen.CreatePen(PS_SOLID, 20, RGB(147, 241, 255));
			CBrush pNewBrush;
			pNewBrush.CreateSolidBrush(RGB(255, 255, 255));
			pOldPen = pDC->SelectObject(&pNewPen);
			pOldBrush = pDC->SelectObject(&pNewBrush);
			pDC->Rectangle(50, 50, 590, 430);
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldBrush);
			CDDraw::ReleaseBackCDC();
			info.SetTopLeft(50, 50);
			info.ShowBitmap();
		}
	}
	
	int SLi;
	
	// 這個class為遊戲的結束狀態(Game Over)
	CGameStateOver::CGameStateOver(CGame *g)
	: CGameState(g)
	{
	}

	void CGameStateOver::OnMove()
	{
		counter+=5;
		if (counter >= 480 + SLi * 32)
		{
			CAudio::Instance()->Stop(LOSS_END);
			CAudio::Instance()->Stop(VICTORY_END);
			GotoGameState(GAME_STATE_INIT);
		}
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 0;
		if (gameType == 0)
		{
			CAudio::Instance()->Play(LOSS_END, true);
		}
		else
		{
			CAudio::Instance()->Play(VICTORY_END, true);
		}
	}

	void CGameStateOver::OnInit()
	{
		ShowInitProgress(66);
		CAudio::Instance()->Load(VICTORY_END, "Sounds\\end_win_01.mp3");
		CAudio::Instance()->Load(LOSS_END, "Sounds\\game_maoudamashii_7_event21.mp3");
		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		CDC *pDC = CDDraw::GetBackCDC();
		CFont f,*fp;
		f.CreatePointFont(160,"Times New Roman");
		fp=pDC->SelectObject(&f);
		pDC->SetBkColor(RGB(0,0,0));
		pDC->SetTextColor(RGB(255,255,255));
		char strL[100];
		stringstream stream;
		if (gameType == 0)
		{
			sprintf(strL, "Game Over!");
		}
		else
		{
			sprintf(strL, "You Win!");
		}
		pDC->TextOut(30, 480 - counter, strL);
		int ioos = 1;
		for (vector<GameInfoList*>::iterator i = List.begin();i != List.end();i++){
			char *strrl = new char[100];
			strcpy(strrl,((*i)->showInfo()).c_str());
			pDC->TextOut(30, 480 - counter + ioos * 32, strrl);
			ioos++;
			delete strrl;
		}
		SLi = ioos;
		pDC->SelectObject(fp);
		CDDraw::ReleaseBackCDC();
	}

	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	CGameStateRun::CGameStateRun(CGame *g)
	: CGameState(g)
	{
	}

	CGameStateRun::~CGameStateRun()
	{
		for (vector<GameInfoList*>::iterator i = List.begin();i != List.end();i++) {
			delete *i;
		}
		List.clear();
	}

	void CGameStateRun::OnBeginState()
	{
		_levelNow = 0;
		_control.StartLevel(_levelNow);
		CAudio::Instance()->Play(WILD_GRASS, true);
		for (vector<GameInfoList*>::iterator i = List.begin();i != List.end();i++) {
			delete *i;
		}
		List.clear();
		GameInfoCount* put = new GameInfoCount("殺了", 0, "狼");
		List.push_back(put);
		GameInfoCount* put1 = new GameInfoCount("殺了", 0, "雞");
		List.push_back(put1);
		GameInfoCount* put2 = new GameInfoCount("殺了", 0, "雪怪");
		List.push_back(put2);
	}

	// 移動遊戲元素
	void CGameStateRun::OnMove()
	{
		int catchStage = _control.OnMove(List);
		int musicList[5] = { 0,1,2,0,1 };
		//玩家死亡時
		if (catchStage < 0) {
			CAudio::Instance()->Stop(WILD_GRASS);
			CAudio::Instance()->Stop(DESSERT);
			CAudio::Instance()->Stop(SNOW);
			GotoGameState(GAME_STATE_OVER);
			gameType = 0;
		}
		//狀況持續執行時
		else if (catchStage == 0) 
		{
		
		}
		//遊戲進入下一關時
		else if(catchStage == 1) {
			_levelNow++;
			if (_levelNow >= MAX_LAVEL) {
				CAudio::Instance()->Stop(WILD_GRASS);
				CAudio::Instance()->Stop(DESSERT);
				CAudio::Instance()->Stop(SNOW);
				GotoGameState(GAME_STATE_OVER);
			}
			else {
				CAudio::Instance()->Stop(DESSERT);
				CAudio::Instance()->Stop(WILD_GRASS);
				CAudio::Instance()->Stop(SNOW);
				if(musicList[_levelNow] == 0)
					CAudio::Instance()->Play(WILD_GRASS, true);
				if (musicList[_levelNow] == 1)
					CAudio::Instance()->Play(DESSERT, true);
				if (musicList[_levelNow] == 2)
					CAudio::Instance()->Play(SNOW, true);
				_control.StartLevel(_levelNow);
				gameType = 1;
			}
		}
	}

	// 遊戲的初值及圖形設定
	void CGameStateRun::OnInit() 
	{
		ShowInitProgress(33);
		_levelNow = 0;
		_control.OnIt();
		_control.StartLevel(_levelNow);
		CAudio::Instance()->Load(DESSERT, "Sounds\\BKA.mp3");
		CAudio::Instance()->Load(WILD_GRASS, "Sounds\\BKB.mp3");
		CAudio::Instance()->Load(SNOW, "Sounds\\snow.mp3");
		ShowInitProgress(50);
	}

	//鍵盤按下偵測
	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT  = 0x25;
		const char KEY_UP    = 0x26;
		const char KEY_RIGHT = 0x27;
		const char KEY_DOWN  = 0x28;
		const char KEY_SPACE = 0x20;
		const char KEY_z = 0x5A;
		const char KEY_Q = 0x51;
		const char KEY_ESC = 27;
		if (nChar == KEY_LEFT)
			_control.enterGoLeft(true);
		if (nChar == KEY_UP)
			_control.enterGoUp(true);
		if (nChar == KEY_RIGHT)
			_control.enterGoRight(true);
		if (nChar == KEY_DOWN)
			_control.enterGoDown(true);
		if (nChar == KEY_z)
			_control.enterRun(true);
		if (nChar == KEY_Q)
			_control.enterSkip(true);
 		if (nChar == KEY_SPACE)
			_control.addTheHit();
		if (nChar == KEY_ESC)								
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	
	}

	//鍵盤提起偵測
	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT  = 0x25;
		const char KEY_UP    = 0x26;
		const char KEY_RIGHT = 0x27;
		const char KEY_DOWN  = 0x28;
		const char KEY_z = 0x5A;

		if (nChar == KEY_LEFT)
			_control.enterGoLeft(false);
		if (nChar == KEY_UP)
			_control.enterGoUp(false);
		if (nChar == KEY_RIGHT)
			_control.enterGoRight(false);
		if (nChar == KEY_DOWN)
			_control.enterGoDown(false);
		if (nChar == KEY_z)
			_control.enterRun(false);
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point) 
	{
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)
	{
	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)
	{
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)
	{
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)
	{
	}

	void CGameStateRun::OnShow()
	{
		_control.OnShow();
	}
}