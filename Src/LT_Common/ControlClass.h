#pragma once
#include "UIInterface.h"

class AFX_EXT_CLASS ControlClass
{
public:
	ControlClass(void);
	~ControlClass(void);
	RECT GetRect(int x,int y,int srcwidth,int srcheight);
	IControl* FindControl(POINT point,CArray<LPIControl,LPIControl&> *ArrayList,int *i=NULL); 
	IControl* FindControl(CString cname,CArray<LPIControl,LPIControl&> *ArrayList);
	IControl* FindControl(RECT rect,CArray<LPIControl,LPIControl&> *ArrayList);
	IControl* FindControlIntersectRect(RECT rect,CArray<LPIControl,LPIControl&> *ArrayList);
	void ResetAllBtControl(HWND hwnd,CArray<LPVOID,LPVOID&> *ArrayList,int percontrolnameid,CPoint &point);
	Rect RECT2Rect(RECT rect);
	static void ConsoleWrite(CString cs);
	static CString IntFormatCString(CString c,int i);
	static CString IntFormatCString(CString c,CString i);
	static bool IsStrInStrAarry(CString e,CString str);
	static void SpliteCString(CString str,CArray<CString,CString&> &arrays,CString);
	RECT GetListBarRect(int,int,int,int);
	
};
