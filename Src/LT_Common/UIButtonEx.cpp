#include "StdAfx.h"
#include "UIButtonEx.h"

UIButtonEx::UIButtonEx(WCHAR *img1,WCHAR *img2):UIButton(img1,img2),RuntimeWidht(0),ButtonStr(L""),CurrentTextColor(RGB(0,0,1))
{
	
}

UIButtonEx::~UIButtonEx(void)
{

}

void UIButtonEx::IPAINT(HDC& dc)
{
	if (!isshow)
	{
		return;
	}

	Drawimage.BitDrawStretchButton(Gbuttoninfo.currentcontrolimage,dc,0,0,LeftW,RightW,RuntimeWidht,Gbuttoninfo.srcwidth,Gbuttoninfo.srcheight,Gbuttoninfo.srcx,Gbuttoninfo.srcy,TextX,TextY,ButtonStr,CurrentTextColor);
}

void UIButtonEx::IPAINT2(HDC& dc)
{
	if (!isshow)
	{
		return;
	}
	Drawimage.BitDrawStretchButton(Gbuttoninfo.currentcontrolimage,dc,Gbuttoninfo.x,Gbuttoninfo.y,LeftW,RightW,RuntimeWidht,Gbuttoninfo.srcwidth,Gbuttoninfo.srcheight,Gbuttoninfo.srcx,Gbuttoninfo.srcy,TextX,TextY,ButtonStr,CurrentTextColor,2);
}

int UIButtonEx::IWIDTH()
{
	return this->RuntimeWidht;
}

bool UIButtonEx::IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int i)
{
	CurrentTextColor =this->TextHoverColor;
	return UIButton::IMOUSEHOVER(hwnd,ts,ArrayList,point,i);;
}

bool UIButtonEx::IMOUSELEAVE(HWND hwnd,bool rp)
{
	CurrentTextColor =this->TextColor;
	return UIButton::IMOUSELEAVE(hwnd,rp);
}