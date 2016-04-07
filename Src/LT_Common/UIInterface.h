#pragma once
#include "stdafx.h"

#ifndef _TESTTITLE_H
#include "IControlEvent.h"


#define WM_LAYERPAINT_MESSAGE  (WM_USER+200)

typedef struct tagControlSlider_bar
{
	CString classname;
	CString bar_image;
	INT bar_x;
	INT bar_y;
	INT bar_srcx;
	int bar_srcy;

	CString bar_circleiamge;

}ControlSlider_bar;

typedef struct tagUiBgSkinInfo
{
	CString id;
	INT maskcolor;
	CString fname;
}UiSkinInfo;


typedef struct tagCurrentMouseEven
{
	CString currentcontrol;
	int MouseType;
	RECT rect;
}CurrentMouseEven;

typedef enum CONTROLTYPE_UI
{
	CUI_BUTTON=0,
	CUI_SLIDERB,
	CUI_SLIDERC
}aaa;

typedef enum EVENTTYPE_UI
{
	UIEVENT__FIRST = 0,
	UIEVENT_MOUSEMOVE,
	UIEVENT_MOUSELEAVE,
	UIEVENT_MOUSEENTER,
	UIEVENT_MOUSEHOVER,
	UIEVENT_KEYDOWN,
	UIEVENT_KEYUP,
	UIEVENT_CHAR,
	UIEVENT_SYSKEY,
	UIEVENT_KILLFOCUS,
	UIEVENT_SETFOCUS,
	UIEVENT_BUTTONDOWN,
	UIEVENT_BUTTONUP,
	UIEVENT_DBLCLICK,
	UIEVENT_CONTEXTMENU,
	UIEVENT_VSCROLL,
	UIEVENT_HSCROLL,
	UIEVENT_SCROLLWHEEL,
	UIEVENT_WINDOWSIZE,
	UIEVENT_SETCURSOR,
	UIEVENT_MEASUREITEM,
	UIEVENT_DRAWITEM,
	UIEVENT_TIMER,
	UIEVENT_NOTIFY,
	UIEVENT_COMMAND,
	UIEVENT__LAST
};

#endif
class AFX_EXT_CLASS IControl
{
public:
	//ControlPosition pos;
	IControlEventS *icontrolevent;
	bool isshow;
	bool responseWM;
	CString tipstr;
	IControl(void)
	{};
	virtual RECT IRECT()=0;
	virtual CString ICLASSTYPE()=0;
	virtual bool IMOUSEMOVE(HWND hwnd,IControl *ts,CPoint point)=0;
	virtual void IPAINT(HDC&)=0;
	virtual void IPAINT2(HDC&)=0;
	virtual CString ICLASSNAME()=0;
	virtual bool ILBUTTONDOWN(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,bool&)=0;
	virtual bool ILBUTTONUP(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList)=0;
	virtual bool IMOUSELEAVE(HWND hwnd,bool rp=TRUE)=0;
	virtual bool IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int i=0)=0;
	virtual bool ILBUTTONDBCLICK(HWND hwnd,CPoint point)=0;
	virtual void IEVENTADD(IControlEventS *ice){icontrolevent=ice;};
	virtual int IWIDTH()=0;
	virtual int IHIGH()=0;
	virtual void IHIDE()=0;
	virtual void ISHOW()=0;
};

typedef  IControl* LPIControl; 