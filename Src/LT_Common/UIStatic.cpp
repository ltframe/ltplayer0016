#include "StdAfx.h"
#include "UIStatic.h"


UIStatic::UIStatic(WCHAR *img1)
{
	Drawimage.LoadResImage(img1,L"AAAAAA",m_pSrcImage1);
	isshow=true;
}


UIStatic::~UIStatic(void)
{
}

void UIStatic::SetControl(HWND hwnd,UIStaticInfo cbuttoninfo,Bitmap *bt)
{

}

RECT UIStatic::IRECT()
{
	//UILable *tempbutton=static_cast<UILable*>(ts);
	return this->Gstaticinfo.rect;
}

CString UIStatic::ICLASSTYPE()
{
	return CString("UIStatic");
}

CString UIStatic::ICLASSNAME()
{
	return this->Gstaticinfo.classname;
}

bool UIStatic::IMOUSEMOVE(HWND hwnd,IControl *ts,CPoint point)
{
	return false;
}
void UIStatic::IPAINT(HDC& dc)
{
	if (!isshow)
	{
		return;
	}
	Drawimage.DrawControl2(m_pSrcImage1,dc,0,0,Gstaticinfo.width,Gstaticinfo.high,0,0);
}

void UIStatic::IPAINT2(HDC& dc)
{
	if (!isshow)
	{
		return;
	}
	Drawimage.BitDrawControl(m_pSrcImage1,dc,Gstaticinfo.x,Gstaticinfo.y,Gstaticinfo.width,Gstaticinfo.high,0,0);
	//Drawimage.DrawControl2();
}

bool UIStatic::ILBUTTONDOWN(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,bool & m_bMouseTracking)
{
	return false;
}
bool UIStatic::ILBUTTONUP(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList)
{
return false;
}

bool UIStatic::IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int controlid)
{
	return false;
}

bool UIStatic::IMOUSELEAVE(HWND hwnd,bool rp)
{
	return false;

}

bool UIStatic::ILBUTTONDBCLICK(HWND hwnd,CPoint point)
{
	return false;
}
int UIStatic::IWIDTH()
{
	return this->Gstaticinfo.width;
}
int UIStatic::IHIGH()
{
	return this->Gstaticinfo.high;
}
void UIStatic::IHIDE()
{
	this->Gstaticinfo.rect.left=-1;
	this->Gstaticinfo.rect.top=-1;
	this->Gstaticinfo.rect.right=-1;
	this->Gstaticinfo.rect.bottom=-1;
}
void UIStatic::ISHOW()
{
	ControlClass *controlclass=new ControlClass();
	this->Gstaticinfo.rect = controlclass->GetRect(Gstaticinfo.x,Gstaticinfo.y,Gstaticinfo.width,Gstaticinfo.high);
	delete controlclass;
}
