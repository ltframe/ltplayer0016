#include "StdAfx.h"
#include "UILable.h"


UILable::UILable(void):origin(0.0f, 0.0f)
{
	isshow=true;
	currentstrwdith=0;
	format=new StringFormat();
	myFont=new Font(L"宋体", 10);
	blackBrush=new SolidBrush(Color(255, 255, 255));
	format->SetAlignment(StringAlignmentNear);
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


void UILable::IPAINT(HDC& dc)
{
	
	if (!isshow)
	{
		return;
	}


	//Graphics *graphics_L=new Graphics(bitmap);
	//
	//RectF boundRect;
	//graphics_L->MeasureString(this->Glableinfo.str, this->Glableinfo.str.GetLength(), myFont, origin, format, &boundRect);
	//delete graphics_L;
	//
	//Bitmap *tempbitmap=new Bitmap(boundRect.Width,15);

	//currentstrwdith=boundRect.Width;
	//SolidBrush *blackBrush1=new SolidBrush(Color(1,255,255, 255));
	//Graphics *graphics_bitmap=new Graphics(tempbitmap);
	//graphics_bitmap->DrawString(this->Glableinfo.str,-1,myFont,boundRect,format,blackBrush);
	//Rect *rect=new Rect(0,0,Glableinfo.width,15);


	//Graphics *graphics_last=new Graphics(bitmap);
	//graphics_last->FillRectangles(blackBrush1, rect,1);
	//graphics_last->DrawImage(tempbitmap,0,0,Glableinfo.rollstep,0,(INT)boundRect.Width,15,(Unit)2);

	//delete graphics_last;
	//delete graphics_bitmap;
	//delete tempbitmap;
	//delete blackBrush1;	
	//delete rect;

	HDC dcMemorya=CreateCompatibleDC(dc);
		void *lpBits;
	BITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biHeight = 15;
	bi.bmiHeader.biWidth = Glableinfo.width;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biCompression=BI_RGB;
	bi.bmiHeader.biXPelsPerMeter=0;
	bi.bmiHeader.biYPelsPerMeter=0;
	bi.bmiHeader.biClrUsed=0;
	bi.bmiHeader.biClrImportant=0;

	HBITMAP THBITMAP = CreateDIBSection(NULL, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&lpBits, NULL, (DWORD)0);
	//for (int i=0;i<307*595;i++)
	//{
	//	char * a=(char*)(&((UINT32*)lpBits)[i]);
	//	a[3]=255;
	//}


	BLENDFUNCTION blendFunc32bpp;
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 255;
	HBITMAP _OTHBITMAP =(HBITMAP)SelectObject(dcMemorya,THBITMAP);
	

	HFONT hFont = Drawimage.SetTextFont(dcMemorya, (LPCTSTR)"宋体", 0, Glableinfo.fontsize, 0); //创建字体
	HFONT _OhFont =(HFONT) SelectObject(dcMemorya, hFont);                         //选择新字体
	
	SetTextColor(dcMemorya,Glableinfo.color);
	SetBkMode(dcMemorya,TRANSPARENT);
	RECT rect={0,0,Glableinfo.width,15};
	DrawText(dcMemorya,Glableinfo.str,wcslen(Glableinfo.str.GetBuffer()),&rect,NULL);
	//TextOut(dcMemorya,0,0,Glableinfo.str,Glableinfo.str.GetLength());

	for (int i=0;i<Glableinfo.width*15;i++)
	{
		char * a=(char*)(&((UINT32*)lpBits)[i]);
		if (a[0]==0 && a[1]==0 && a[2]==0)
		{
			continue;
		}
		a[3]=255;
	}



	AlphaBlend(dc,0,0,Glableinfo.width,15,dcMemorya,Glableinfo.rollstep,0,Glableinfo.width,15,blendFunc32bpp);
	//BitBlt(dc,0,0,Glableinfo.width,15,dcMemorya,Glableinfo.rollstep,0,SRCCOPY);
	::SelectObject (dcMemorya,_OTHBITMAP);
	::DeleteObject(THBITMAP);
	::DeleteObject(_OTHBITMAP);
	::DeleteDC(dcMemorya);

	::SelectObject (dcMemorya,_OhFont);
	::DeleteObject(hFont);
	::DeleteObject(_OhFont);
	/*DrawImages.DrawControl2()*/

}

void UILable::IPAINT2(HDC& dc)
{
	
	if (!isshow)
	{
		return;
	}

	HDC dcMemorya=CreateCompatibleDC(dc);


	void *lpBits;
	BITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biBitCount =32;
	bi.bmiHeader.biHeight = 15;
	bi.bmiHeader.biWidth =  this->Glableinfo.width;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biCompression=BI_RGB;
	bi.bmiHeader.biXPelsPerMeter=0;
	bi.bmiHeader.biYPelsPerMeter=0;
	bi.bmiHeader.biClrUsed=0;
	bi.bmiHeader.biClrImportant=0;

	HBITMAP THBITMAP = CreateDIBSection(NULL, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&lpBits, NULL, (DWORD)0);
	HBITMAP _OTHBITMAP =(HBITMAP)SelectObject(dcMemorya,THBITMAP);


	HFONT hFont = Drawimage.SetTextFont(dcMemorya, (LPCTSTR)"宋体", 0, Glableinfo.fontsize, 0); //创建字体
	HFONT _OhFont =(HFONT) SelectObject(dcMemorya, hFont);                         //选择新字体

	SetTextColor(dcMemorya,Glableinfo.color);
	SetBkMode(dcMemorya,TRANSPARENT);
	RECT rect={0,0,Glableinfo.width,15};
	DrawText(dcMemorya,Glableinfo.str,wcslen(Glableinfo.str.GetBuffer()),&rect,NULL);
	//TextOut(dcMemorya,0,0,Glableinfo.str,Glableinfo.str.GetLength());


	currentstrwdith = this->Glableinfo.width;
	for (int i=0;i<this->Glableinfo.width*15;i++)
	{
		char * a=(char*)(&((UINT32*)lpBits)[i]);
		if (a[0]==0 && a[1]==0 && a[2]==0)
		{
			continue;
		}
		a[3]=255;
	}


	BitBlt(dc,Glableinfo.x,Glableinfo.y,Glableinfo.width,15,dcMemorya,Glableinfo.rollstep,0,SRCCOPY);
	::SelectObject (dcMemorya,_OTHBITMAP);
	::DeleteObject(THBITMAP);
	::DeleteObject(_OTHBITMAP);
	::DeleteDC(dcMemorya);

	::SelectObject (dcMemorya,_OhFont);
	::DeleteObject(hFont);
	::DeleteObject(_OhFont);
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