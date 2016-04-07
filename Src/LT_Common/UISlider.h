#pragma once
#include "UIInterface.h"
#include "DrawImages.h"
#include "UIInfo.h"
#include "ControlClass.h"
class AFX_EXT_CLASS UISlider : public IControl
{
public:
	UISlider(WCHAR *img1,WCHAR *img2,WCHAR *img3);
	~UISlider(void);
	/*ControlEvent controlevent;*/
	UISliderInfo Gsliderinfo;
	DrawImages Drawimage;;
	Bitmap * m_pSrcImage1;
	Bitmap * m_pSrcImage2;
	Bitmap * m_pSrcImage3;
	HDC SingleControl1,SingleControl2;
	void SetControl(Bitmap *bt,int,int,int,int,int,int,Unit,int);
	void DrawImage(HWND hwnd,int width,int height,WCHAR* filename,UISliderInfo sinfo,INT i);
	void LoadResImage(WCHAR* filename,WCHAR * streamname,Image * &pImage);
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
	bool ILBUTTONDOWN(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,bool&);
	bool ILBUTTONDBCLICK(HWND hwnd,CPoint point);
	bool IMOUSELEAVE(HWND,bool rp=true);
	bool ILBUTTONUP(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList);
	bool IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int i=0);
	void SetSingleControl(HDC memdc,int top1cx,int top2cx);
	void SetSingleControl(HDC memdc);
};
