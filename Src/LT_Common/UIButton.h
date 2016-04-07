#pragma once
#include "UIInterface.h"
#include "DrawImages.h"
#include "UIInfo.h"
#include "ControlClass.h"

class AFX_EXT_CLASS UIButton : public IControl
{
public:
	UIButton(WCHAR *img1,WCHAR *img2=NULL);
	~UIButton(void);
	UIButtonInfo Gbuttoninfo;
	Bitmap * m_pSrcImage1;
	Bitmap * m_pSrcImage2;
	/*ControlEvent controlevent;*/
	void SetControl(HWND hwnd,UIButtonInfo buttoninfo,Bitmap *bt);
	bool IMOUSEMOVE(HWND hwnd,IControl *ts,CPoint point);
	RECT IRECT();
	CString ICLASSNAME();
	CString ICLASSTYPE();
	virtual void IPAINT(HDC&);
	virtual void IPAINT2(HDC&);
    virtual bool IMOUSELEAVE(HWND,bool rp=true);
	bool ILBUTTONDOWN(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,bool&);
	bool ILBUTTONUP(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList);
	virtual bool IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int i=0);
	bool ILBUTTONDBCLICK(HWND hwnd,CPoint point);
	virtual int IWIDTH();
	int IHIGH();
	void IHIDE();
	void ISHOW();
	int GetButtonImg();
	DrawImages Drawimage;
};

