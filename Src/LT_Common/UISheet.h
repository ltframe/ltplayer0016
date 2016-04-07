#pragma once
#include "UIInterface.h"
#include "DrawImages.h"
#include "UIInfo.h"
#include "ControlClass.h"

class AFX_EXT_CLASS UISheet :public IControl
{
public:
	UISheet(void);
	~UISheet(void);
	SolidBrush *blackBrush1;
	UISheetInfo Gsheetinfo;
	CArray<LPIControl,LPIControl&> *uilistarray;
	bool IMOUSEMOVE(HWND hwnd,IControl *ts,CPoint point);
	RECT IRECT();
	CString ICLASSNAME();
	CString ICLASSTYPE();
	void IPAINT(Bitmap*);
	bool IMOUSELEAVE(HWND,bool rp=true);
	bool ILBUTTONDOWN(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,bool&);
	bool ILBUTTONUP(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList);
	bool IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int i=0);
	bool ILBUTTONDBCLICK(HWND hwnd,CPoint point);
	int IWIDTH();
	int IHIGH();
	void AddPage(LPIControl);
};
