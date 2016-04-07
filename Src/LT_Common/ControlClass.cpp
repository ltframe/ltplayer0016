#include "StdAfx.h"
#include "ControlClass.h"
#include "UIButton.h"

ControlClass::ControlClass(void)
{
}

ControlClass::~ControlClass(void)
{
}
RECT ControlClass::GetRect(int x,int y,int srcwidth,int srcheight)
{
	RECT rect={x,y,x+srcwidth,y+srcheight};
	return  rect;
}
IControl* ControlClass::FindControl(POINT point,CArray<LPIControl,LPIControl&> *ArrayList,int *it)
{
	for (int i = 0; i < ArrayList->GetSize(); i++)
	{

		IControl * temp=ArrayList->ElementAt(i);
		bool b=::PtInRect(&temp->IRECT(),point);
		if(::PtInRect(&temp->IRECT(),point)){
			if (it!=NULL)
			{
				*it=i;
			}
			return temp;
			break;;
		}
	}
	return NULL;
}

IControl* ControlClass::FindControl(CString cname,CArray<LPIControl,LPIControl&> *ArrayList)
{
	for (int i = 0; i < ArrayList->GetSize(); i++)
	{

		IControl * temp=ArrayList->ElementAt(i);
		if(temp->ICLASSNAME()==cname){
			return temp;
			break;;
		}
	}
	return NULL;
}

IControl* ControlClass::FindControl(RECT rect,CArray<LPIControl,LPIControl&> *ArrayList)
{
	for (int i = 0; i < ArrayList->GetSize(); i++)
	{
		IControl * temp=ArrayList->ElementAt(i);
		RECT  lprcDst;
		if(IntersectRect(&lprcDst,&temp->IRECT(),&rect)){
			return temp;
			break;;
		}
	}
	return NULL;
}

IControl* ControlClass::FindControlIntersectRect(RECT rect,CArray<LPIControl,LPIControl&> *ArrayList)
{
	for (int i = 0; i < ArrayList->GetSize(); i++)
	{
		IControl * temp=ArrayList->ElementAt(i);
		RECT  lprcDst;
		if(IntersectRect(&lprcDst,&temp->IRECT(),&rect)){
			return temp;
			break;;
		}
	}
	return NULL;
}

void ControlClass::ResetAllBtControl(HWND hwnd,CArray<LPVOID,LPVOID&> *ArrayList,int percontrolnameid,CPoint &point)
{
	/*for (int i = 0; i < ArrayList->GetSize(); i++)
	{
		IControl * temp=static_cast<IControl*>(ArrayList->ElementAt(i));*/
		/*if (temp->ICLASSTYPE()=="UIButton" && temp->ICLASSNAME(temp)==percontrolname)
		{*/
			UIButton *tempbutton=static_cast<UIButton*>(ArrayList->GetAt(percontrolnameid));
			if(tempbutton->ICLASSTYPE()=="UIButton"){
			RECT rect=tempbutton->Gbuttoninfo.rect;
			tempbutton->Gbuttoninfo.srcx=0;
			tempbutton->Gbuttoninfo.MouseType=UIEVENT_MOUSELEAVE;
			point.x=tempbutton->Gbuttoninfo.x+1;
			point.y=tempbutton->Gbuttoninfo.y+1;			
			//::InvalidateRect(hwnd,&rect,1);
			
			SendMessage(hwnd,WM_PAINT,NULL,NULL);
			}
			//break;
			
	/*	}
	}   */
}

Rect ControlClass::RECT2Rect(RECT rect)
{
	int x=rect.left;
	int y=rect.top;
	int w=rect.right-x;
	int h=rect.bottom-y;
	return Rect(x,y,w,h);
}

void ControlClass::ConsoleWrite(CString cs)
{
#ifdef _OPENCONSOLE
	static int si=1;
	_cwprintf_s(_T("%d-%s\n"), si,cs);
	si++;
#endif
}

CString ControlClass::IntFormatCString(CString c,int i)
{
	CString cs;
	cs.Format(_T("%s:%d"),c,i);
	return cs;
}

CString ControlClass::IntFormatCString(CString c,CString i)
{
	CString cs;
	cs.Format(_T("%s:%s"),c,i);
	return cs;
}
bool ControlClass::IsStrInStrAarry(CString e,CString str)
{
	CArray<CString,CString&> arrays;
	SpliteCString(str,arrays,_T(","));
	for (int i=0;i<arrays.GetSize();i++)
	{
		if (arrays.ElementAt(i)==e)
			return true;
	}
	return false;
}
void ControlClass::SpliteCString(CString str,CArray<CString,CString&> &arrays,CString spstr)
{
	int index=0;
	CString resToken=str.Tokenize(spstr,index);
	while (resToken != _T(""))
	{
		arrays.Add(resToken);
		resToken=str.Tokenize(spstr,index);
	}
}

RECT ControlClass::GetListBarRect(int left,int top,int rig,int bottom)
{
	RECT rect={left,top,rig,bottom};
	return rect;
}

