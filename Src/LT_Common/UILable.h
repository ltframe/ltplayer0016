#pragma once
#include "UIInterface.h"
#include "DrawImages.h"
#include "UILable.h"
#include "ControlClass.h"

class AFX_EXT_CLASS UILable : public IControl
{
public:
	UILable(void);
	~UILable(void);
	UILableInfo Glableinfo;
	void SetControl(HWND hwnd,UILableInfo lableinfo,Bitmap *bt);
	bool IMOUSEMOVE(HWND hwnd,IControl *ts,CPoint point);
	RECT IRECT();
	CString ICLASSNAME();
	CString ICLASSTYPE();
	void IPAINT(HDC&);
	void IPAINT2(HDC&);
	int IWIDTH();
	int IHIGH();
	void IHIDE();
	void ISHOW();
	bool IMOUSELEAVE(HWND,bool rp=true);
	bool ILBUTTONDOWN(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,bool&);
	bool ILBUTTONUP(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList);
	bool IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int i=0);
	bool ILBUTTONDBCLICK(HWND hwnd,CPoint point);
	void EmptyString();
	int GetStrWidht();
private:
	int currentstrwdith;
	StringFormat *format;
	Font *myFont;
	SolidBrush *blackBrush;
	PointF origin;
	DrawImages Drawimage;
};

