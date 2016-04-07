#include "StdAfx.h"
#include "UISheet.h"

UISheet::UISheet(void):blackBrush1(new SolidBrush(Color(1,255,255, 255)))
{
	uilistarray=new CArray<LPIControl,LPIControl&>();
}

UISheet::~UISheet(void)
{
}

RECT UISheet::IRECT()
{
	//UILable *tempbutton=static_cast<UILable*>(ts);
	return this->Gsheetinfo.rect;
}

CString UISheet::ICLASSTYPE()
{
	return CString("UISheet");
}

CString UISheet::ICLASSNAME()
{
	return this->Gsheetinfo.classname;
}

bool UISheet::IMOUSEMOVE(HWND hwnd,IControl *ts,CPoint point)
{
	for (int i=0;i<uilistarray->GetSize();i++)
	{
		IControl *t= uilistarray->GetAt(i);
		if (t->isshow)
		{
			t->IMOUSEMOVE(hwnd,ts,point);
			break;;
		}
	}
	return true;
}

void UISheet::IPAINT(Bitmap *bitmap)
{
	Graphics *gg=new Graphics(bitmap);
	
	RectF layoutRect(0,0,bitmap->GetWidth(),bitmap->GetHeight());
	gg->FillRectangles(blackBrush1, &layoutRect, 1);
	for (int i=0;i<uilistarray->GetSize();i++)
	{
		IControl *t= uilistarray->GetAt(i);
		if (t->isshow)
		{
			Bitmap *tb=new Bitmap(t->IWIDTH(),t->IHIGH());
			t->IPAINT(tb);
			RECT rc=t->IRECT();
			gg->DrawImage(tb,0,0,0,0,tb->GetWidth(),tb->GetHeight(),(Unit)2);
			delete tb;
			break;
		}

	}
	delete gg;
}

bool UISheet::ILBUTTONDOWN(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,bool & m_bMouseTracking)
{
	for (int i=0;i<uilistarray->GetSize();i++)
	{
		IControl *t= uilistarray->GetAt(i);
		if (t->isshow)
		{
			t->ILBUTTONDOWN(hwnd,ts,ArrayList,point,m_bMouseTracking);
			break;;
		}
	}
	return true;
}
bool UISheet::ILBUTTONUP(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList)
{
	for (int i=0;i<uilistarray->GetSize();i++)
	{
		IControl *t= uilistarray->GetAt(i);
		if (t->isshow)
		{
			t->ILBUTTONUP(hwnd,ts,ArrayList);
			break;;
		}
	}
	return true;
}

bool UISheet::IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int controlid)
{
	for (int i=0;i<uilistarray->GetSize();i++)
	{
		IControl *t= uilistarray->GetAt(i);
		if (t->isshow)
		{
			t->IMOUSEHOVER(hwnd,ts,ArrayList,point,controlid);
			break;;
		}
	}
	return true;
}

bool UISheet::IMOUSELEAVE(HWND hwnd,bool rp)
{
	for (int i=0;i<uilistarray->GetSize();i++)
	{
		IControl *t= uilistarray->GetAt(i);
		if (t->isshow)
		{
			t->IMOUSELEAVE(hwnd,rp);
			break;;
		}
	}
	return true;
}

bool UISheet::ILBUTTONDBCLICK(HWND hwnd,CPoint point)
{
	for (int i=0;i<uilistarray->GetSize();i++)
	{
		IControl *t= uilistarray->GetAt(i);
		if (t->isshow)
		{
			t->ILBUTTONDBCLICK(hwnd,point);
			break;;
		}
	}
	return true;
}
int UISheet::IWIDTH()
{
	return this->Gsheetinfo.width;
}
int UISheet::IHIGH()
{
	return this->Gsheetinfo.high;
}
void UISheet::AddPage(LPIControl t)
{
	uilistarray->Add(t);
}
