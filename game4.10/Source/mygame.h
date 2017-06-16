/*
mygame.h: ���ɮ��x�C��������class��interface
*/

#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "controlGame.h"
#include "GameInfoList.h"

namespace game_framework {
	// Constants
	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		DESSERT,				// 0
		WILD_GRASS,				// 1
		VICTORY_END,			// 2
		LOSS_END,                // 3
		HIT_SOUND,
		SNOW
	};

	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int select;
		bool showHelp;
		CMovingBitmap logo;
		CMovingBitmap backGround;
		CMovingBitmap buttomEnter;
		CMovingBitmap buttomExit;
		CMovingBitmap buttomSelect;
		CMovingBitmap buttomHelp;
		CMovingBitmap info;
	};

	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		const int MAX_LAVEL  = 5;
		controlGame	_control;
		int _levelNow;

	};

	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;
	};

}