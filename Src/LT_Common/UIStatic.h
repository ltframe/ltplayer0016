#pragma once
#include "UIInterface.h"
#include "DrawImages.h"
#include "ControlClass.h"

class AFX_EXT_CLASS UIStatic : public IControl
{
public:
	DrawImages Drawimage;;
	Bitmap * m_pSrcImage1;
	UIStatic(WCHAR *img1);
	~UIStatic(void);
	UIStaticInfo Gstaticinfo;
	void SetControl(HWND hwnd,UIStaticInfo staticinfo,Bitmap *bt);
	bool IMOUSEMOVE(HWND hwnd,IControl *ts,CPoint point);
	RECT IRECT();
	CString ICLASSNAME();
	CString ICLASSTYPE();
	virtual void IPAINT(HDC&);
	virtual void IPAINT2(HDC&);
	int IWIDTH();
	int IHIGH();
	void IHIDE();
	void ISHOW();
	bool IMOUSELEAVE(HWND,bool rp=true);
	bool ILBUTTONDOWN(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,bool&);
	bool ILBUTTONUP(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList);
	bool IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int i=0);
	bool ILBUTTONDBCLICK(HWND hwnd,CPoint point);
private:

};

