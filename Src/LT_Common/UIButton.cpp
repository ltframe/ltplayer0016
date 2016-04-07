#include "StdAfx.h"
#include "UIButton.h"



UIButton::UIButton(WCHAR *img1,WCHAR *img2)
{
	Drawimage.LoadResImage(img1,L"AAAAAA",m_pSrcImage1);
	if (img2==NULL)
	{
		m_pSrcImage2=m_pSrcImage1;
	} 
	else
	{
	   Drawimage.LoadResImage(img2,L"AAAAAA",m_pSrcImage2);
	}
	//playbutton->Gbuttoninfo.controlimages1="res\\play.png";
	//playbutton->Gbuttoninfo.currentcontrolimage="res\\play.png";
	//playbutton->Gbuttoninfo.controlimages2="res\\stop.png";
	this->Gbuttoninfo.controlimages1=m_pSrcImage1;
	this->Gbuttoninfo.controlimages2=m_pSrcImage2;
	this->Gbuttoninfo.currentcontrolimage=m_pSrcImage1;
	isshow=true;
}


UIButton::~UIButton(void)
{

}


void UIButton::SetControl(HWND hwnd,UIButtonInfo cbuttoninfo,Bitmap *bt)
{
	//Bitmap bitmap(cbuttoninfo.srcwidth,cbuttoninfo.srcheight);
	//Graphics graphics(&bitmap);
	//graphics.DrawImage(cbuttoninfo.currentcontrolimage,0,0,cbuttoninfo.srcx,cbuttoninfo.srcy,cbuttoninfo.srcwidth,cbuttoninfo.srcheight,cbuttoninfo.srcUnit);
	// Graphics g(bt);
	//g.DrawImage(&bitmap,cbuttoninfo.x,cbuttoninfo.y,0,0,cbuttoninfo.srcwidth,cbuttoninfo.srcheight,cbuttoninfo.srcUnit);

	Graphics *graphics=new Graphics(bt);
	graphics->DrawImage(cbuttoninfo.currentcontrolimage,cbuttoninfo.x,cbuttoninfo.y,cbuttoninfo.srcx,cbuttoninfo.srcy,cbuttoninfo.srcwidth,cbuttoninfo.srcheight,cbuttoninfo.srcUnit);
	//ControlClass::ConsoleWrite(ControlClass::IntFormatCString(CString("SetControl£º"),cbuttoninfo.classname));
	//ControlClass::ConsoleWrite(ControlClass::IntFormatCString(CString("SetControl£º"),cbuttoninfo.srcx));
	delete graphics;
}

RECT UIButton::IRECT()
{
	//UIButton *tempbutton=static_cast<UIButton*>(ts);
	//return tempbutton->Gbuttoninfo.rect;
	return this->Gbuttoninfo.rect;
}

CString UIButton::ICLASSTYPE()
{
	return CString("UIButton");
}

CString UIButton::ICLASSNAME()
{
	//UIButton *tempbutton=static_cast<UIButton*>(ts);
	//return tempbutton->Gbuttoninfo.classname;
	return this->Gbuttoninfo.classname;
}

bool UIButton::IMOUSEMOVE(HWND hwnd,IControl *ts,CPoint point)
{
	return false;
}


void UIButton::IPAINT(HDC& dc)
{
	if (!isshow)
	{
		return;
	}

	Drawimage.DrawControl2(Gbuttoninfo.currentcontrolimage,dc,0,0,Gbuttoninfo.srcwidth,Gbuttoninfo.srcheight,Gbuttoninfo.srcx,Gbuttoninfo.srcy);
}

void UIButton::IPAINT2(HDC& dc)
{
	if (!isshow)
	{
		return;
	}

	Drawimage.BitDrawControl(Gbuttoninfo.currentcontrolimage,dc,Gbuttoninfo.x,Gbuttoninfo.y,Gbuttoninfo.srcwidth,Gbuttoninfo.srcheight,Gbuttoninfo.srcx,Gbuttoninfo.srcy);
}

bool UIButton::ILBUTTONDOWN(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,bool & m_bMouseTracking)
{

	UIButton *tempbutton=static_cast<UIButton*>(ts);
	RECT rect;
	//if(tempbutton->pos.currentcontrolimage==tempbutton->binfo.controlimages1)
	//{
	//	tempbutton->pos.currentcontrolimage=tempbutton->binfo.controlimages2;
	//	tempbutton->pos.srcx=tempbutton->pos.srcwidth;
	//	rect=tempbutton->pos.rect;
	//	tempbutton->pos.MouseType=UIEVENT__FIRST;
	//}
	//else{
	//	tempbutton->pos.currentcontrolimage=tempbutton->binfo.controlimages2;
	tempbutton->Gbuttoninfo.srcx=tempbutton->Gbuttoninfo.srcwidth*2;
	rect=tempbutton->Gbuttoninfo.rect;
	tempbutton->Gbuttoninfo.MouseType=UIEVENT_BUTTONDOWN;
	/*}*/
	//::InvalidateRect(hwnd,&rect,1);
	//::UpdateWindow(hwnd);
	/*SendMessage(hwnd,WM_PAINT,NULL,NULL);*/
	return true;
}
bool UIButton::ILBUTTONUP(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList)
{

	UIButton *tempbutton=static_cast<UIButton*>(ts);
	//if (tempbutton->Gbuttoninfo.MouseType!=UIEVENT_BUTTONDOWN)
	//{
	//	RECT rect=tempbutton->Gbuttoninfo.rect;
	//}
	if (tempbutton->Gbuttoninfo.haswm && icontrolevent->SetButtonContorEvent(tempbutton->Gbuttoninfo))
    {
			if(tempbutton->Gbuttoninfo.currentcontrolimage==tempbutton->Gbuttoninfo.controlimages1)
			{
				tempbutton->Gbuttoninfo.currentcontrolimage=tempbutton->Gbuttoninfo.controlimages2;
				/*tempbutton->Gbuttoninfo.srcx=tempbutton->Gbuttoninfo.srcwidth*2;*/
				tempbutton->Gbuttoninfo.srcx=0;
			}
			else
			{
				tempbutton->Gbuttoninfo.currentcontrolimage=tempbutton->Gbuttoninfo.controlimages1;
				//tempbutton->Gbuttoninfo.srcx=tempbutton->Gbuttoninfo.srcwidth;
				tempbutton->Gbuttoninfo.srcx=0;
			}

			RECT rect=tempbutton->Gbuttoninfo.rect;
			tempbutton->Gbuttoninfo.MouseType=UIEVENT_BUTTONUP;
			//::InvalidateRect(hwnd,&rect,1);
			//::UpdateWindow(hwnd);
			//SendMessage(hwnd,WM_PAINT,NULL,NULL);
	//////////////////////////////////////////////////////////////////////////
	}
	return true;
}

bool UIButton::IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int controlid)
{


			/*UIButton *tempbutton=static_cast<UIButton*>(ArrayList->GetAt(controlid));*/
			//if(tempbutton ==ts)
			//{
				this->Gbuttoninfo.srcx=this->Gbuttoninfo.srcwidth;
				RECT rect=this->Gbuttoninfo.rect;
				this->Gbuttoninfo.MouseType=UIEVENT_MOUSEHOVER;
		/*		::InvalidateRect(hwnd,&rect,1);
				::UpdateWindow(hwnd);*/
				/*SendMessage(hwnd,WM_PAINT,NULL,NULL);*/
				return true;
}
bool UIButton::IMOUSELEAVE(HWND hwnd,bool rp)
{
	this->Gbuttoninfo.srcx=0;
	if (rp)
	{
		this->Gbuttoninfo.MouseType=UIEVENT_MOUSELEAVE;
		//::InvalidateRect(hwnd,&this->Gbuttoninfo.rect,1);
		//::UpdateWindow(hwnd);
		return true;
	}
	return false;
}

bool UIButton::ILBUTTONDBCLICK(HWND hwnd,CPoint point)
{
	return false;
}

int UIButton::GetButtonImg()
{
	if (this->Gbuttoninfo.currentcontrolimage==this->Gbuttoninfo.controlimages1)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

int UIButton::IWIDTH()
{
	return Gbuttoninfo.currentcontrolimage->GetWidth()/3;
}
int UIButton::IHIGH()
{
	return Gbuttoninfo.currentcontrolimage->GetHeight();
}

void UIButton::IHIDE()
{
	this->Gbuttoninfo.rect.left=-1;
	this->Gbuttoninfo.rect.top=-1;
	this->Gbuttoninfo.rect.right=-1;
	this->Gbuttoninfo.rect.bottom=-1;
}
void UIButton::ISHOW()
{
	ControlClass *controlclass=new ControlClass();
	this->Gbuttoninfo.rect = controlclass->GetRect(Gbuttoninfo.x,Gbuttoninfo.y,Gbuttoninfo.srcwidth,Gbuttoninfo.srcheight);
	delete controlclass;
}