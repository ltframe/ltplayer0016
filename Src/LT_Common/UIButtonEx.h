#pragma once
#include "UIButton.h"

class AFX_EXT_CLASS UIButtonEx :public UIButton
{
public:
	int RuntimeWidht,LeftW,RightW,TextX,TextY;
	WCHAR * ButtonStr;
	COLORREF TextColor,TextHoverColor;
	UIButtonEx(WCHAR *img1,WCHAR *img2 =NULL);
	~UIButtonEx(void);
	void IPAINT(HDC&);
	void IPAINT2(HDC&);
	bool IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int i=0);
	bool IMOUSELEAVE(HWND,bool rp=true);
	int IWIDTH();
private:
	COLORREF CurrentTextColor;
};
