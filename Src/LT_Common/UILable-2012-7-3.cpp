#include "StdAfx.h"
#include "UILable.h"


UILable::UILable(void)
{
	isshow=true;
	currentstrwdith=0;
}


UILable::~UILable(void)
{
}

void UILable::SetControl(HWND hwnd,UILableInfo cbuttoninfo,Bitmap *bt)
{

}

RECT UILable::IRECT()
{
	//UILable *tempbutton=static_cast<UILable*>(ts);
	return this->Glableinfo.rect;
}

CString UILable::ICLASSTYPE()
{
	return CString("UILable");
}

CString UILable::ICLASSNAME()
{
	/*UILable *tempbutton=static_cast<UILable*>(ts);*/
	return this->Glableinfo.classname;
}

bool UILable::IMOUSEMOVE(HWND hwnd,IControl *ts,CPoint point)
{
	return false;
}

void UILable::IPAINT(Bitmap *bitmap)
{
	
	if (!isshow)
	{
		return;
	}

	//StringFormat format;
	//Font myFont(L"ËÎÌו", 10);
	//SolidBrush blackBrush(Color(255, 255, 255));
	//format.SetAlignment(StringAlignmentNear);
	//Graphics *graphics=new Graphics(bitmap);
	//PointF origin(0.0f, 0.0f);
	//RectF boundRect;
	//graphics->MeasureString(this->Glableinfo.str, this->Glableinfo.str.GetLength(), &myFont, origin, &format, &boundRect);

	//if (boundRect.Width>Glableinfo.width)
	//{
	//	boundRect.Width=Glableinfo.width;
	//}
	//RECT rect={0,0,boundRect.Width,15};
	//SolidBrush *blackBrush1=new SolidBrush(Color(1,255,255, 255));
	//graphics->FillRectangles(blackBrush1, &boundRect,1);
	//graphics->DrawString(this->Glableinfo.str,-1,&myFont,boundRect,&format,&blackBrush);
	//delete graphics;
	//delete blackBrush1;	

////////////////////////////////////////////////////////////////////////
	StringFormat format;
	Font myFont(L"ËÎÌו", 10);
	SolidBrush blackBrush(Color(255, 255, 255));
	format.SetAlignment(StringAlignmentNear);
	PointF origin(0.0f, 0.0f);

	Graphics *graphics_L=new Graphics(bitmap);
	
	RectF boundRect;
	graphics_L->MeasureString(this->Glableinfo.str, this->Glableinfo.str.GetLength(), &myFont, origin, &format, &boundRect);
	delete graphics_L;
	
	Bitmap *tempbitmap=new Bitmap(boundRect.Width,15);
	/*
	if (boundRect.Width>Glableinfo.width)
	{
		boundRect.Width=Glableinfo.width;
	}*/
	currentstrwdith=boundRect.Width;
	SolidBrush *blackBrush1=new SolidBrush(Color(1,255,255, 255));
	Graphics *graphics_bitmap=new Graphics(tempbitmap);
	//graphics_bitmap->FillRectangles(blackBrush1, &boundRect,1);
	graphics_bitmap->DrawString(this->Glableinfo.str,-1,&myFont,boundRect,&format,&blackBrush);
	Rect *rect=new Rect(0,0,Glableinfo.width,15);
	Graphics *graphics_last=new Graphics(bitmap);
	graphics_last->FillRectangles(blackBrush1, rect,1);
	graphics_last->DrawImage(tempbitmap,0,0,Glableinfo.rollstep,0,(INT)boundRect.Width,15,(Unit)2);

	delete graphics_last;
	delete graphics_bitmap;
	delete tempbitmap;
	delete blackBrush1;	
	delete rect;
}

bool UILable::ILBUTTONDOWN(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,bool & m_bMouseTracking)
{
	return false;
}
bool UILable::ILBUTTONUP(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList)
{
return false;
}

bool UILable::IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int controlid)
{
	return false;
}

bool UILable::IMOUSELEAVE(HWND hwnd,bool rp)
{
	return false;

}

bool UILable::ILBUTTONDBCLICK(HWND hwnd,CPoint point)
{
	return false;
}
int UILable::IWIDTH()
{
	return this->Glableinfo.width;
}
int UILable::IHIGH()
{
	return 15;
}

void UILable::IHIDE()
{
	this->Glableinfo.rect.left=-1;
	this->Glableinfo.rect.top=-1;
	this->Glableinfo.rect.right=-1;
	this->Glableinfo.rect.bottom=-1;
}
void UILable::ISHOW()
{
	ControlClass *controlclass=new ControlClass();
	this->Glableinfo.rect = controlclass->GetRect(Glableinfo.x,Glableinfo.y,this->Glableinfo.str.GetLength()*12,15);
	delete controlclass;
}

void UILable::EmptyString()
{
	this->Glableinfo.str=L"                                                                                                   ";
}

int UILable::GetStrWidht()
{
	return currentstrwdith;
}