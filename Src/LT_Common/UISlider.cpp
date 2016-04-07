#include "StdAfx.h"
#include "UISlider.h"

UISlider::UISlider(WCHAR *img1,WCHAR *img2,WCHAR *img3):m_pSrcImage2(NULL), m_pSrcImage3(NULL)
{
	Drawimage.LoadResImage(img1,L"AAAAAA",m_pSrcImage1);
	if (img2!=NULL)
	{
		Drawimage.LoadResImage(img2,L"AAAAAA",m_pSrcImage2);
	}
	if (img3!=NULL)
	{
		Drawimage.LoadResImage(img3,L"AAAAAA",m_pSrcImage3);
	}
	
	isshow=true;
}

UISlider::~UISlider(void)
{
}

void UISlider:: SetControl(Bitmap *bt,int x,int y,int srcx,int srcy,int srcwidth,int srcheight,Unit srcUnit,int imgid)
{
	Bitmap *temp=NULL;
	switch(imgid)
	{
	case 1:
		temp=m_pSrcImage1;
		break;
	case 2:
		temp=m_pSrcImage2;
		break;
	default:
		temp=m_pSrcImage3;
		break;;
	}
	Graphics *g=new Graphics(bt);
	g->DrawImage(temp,x,y,srcx,srcy,srcwidth,srcheight,srcUnit);
	delete g;
	delete temp;

}

void UISlider::SetSingleControl(HDC memdc,int top1cx,int top2cx)
{
	

	//BLENDFUNCTION blendFunc32bpp;
	//blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	//blendFunc32bpp.BlendFlags = 0;
	//blendFunc32bpp.BlendOp = AC_SRC_OVER;
	//blendFunc32bpp.SourceConstantAlpha = 255;


//////////////////////////////////////////////////
	int dlgcx = this->Gsliderinfo.i1_width;
	HDC dcMemorya1=CreateCompatibleDC(memdc);
	HBITMAP hBitmap1;
	m_pSrcImage1->GetHBITMAP(NULL,&hBitmap1);
	HBITMAP hOldBitmap1 = (HBITMAP)::SelectObject(dcMemorya1, hBitmap1);

	int m1_h = m_pSrcImage1->GetHeight();
	int m1_w =m_pSrcImage1->GetWidth();
	SingleControl1 = CreateCompatibleDC(memdc);
	HBITMAP lasthbitmap1 = CreateCompatibleBitmap(memdc,dlgcx,m1_h);
	HBITMAP Oldlasthbitmap1 = (HBITMAP)::SelectObject(SingleControl1,lasthbitmap1);
	BitBlt(SingleControl1,0,0,top1cx,m1_h,dcMemorya1,0,0,SRCCOPY);
	StretchBlt(SingleControl1,top1cx,0,dlgcx-(top1cx*2),m1_h,dcMemorya1,top1cx,0,m1_w-(top1cx*2),m1_h,SRCCOPY);
	BitBlt(SingleControl1,dlgcx-top1cx,0,top1cx,m1_h,dcMemorya1,m1_w-top1cx,0,SRCCOPY);
	//////////////////////////////////////////////////////////////////////

	HDC dcMemorya2=CreateCompatibleDC(memdc);
	HBITMAP hBitmap2;
	m_pSrcImage2->GetHBITMAP(NULL,&hBitmap2);
	HBITMAP hOldBitmap2 = (HBITMAP)::SelectObject(dcMemorya2, hBitmap2);

	int m2_h = m_pSrcImage2->GetHeight();
	int m2_w =m_pSrcImage2->GetWidth();
	SingleControl2 = CreateCompatibleDC(memdc);
	HBITMAP lasthbitmap2 = CreateCompatibleBitmap(memdc,dlgcx,m2_h);
	HBITMAP Oldlasthbitmap2 = (HBITMAP)::SelectObject(SingleControl2,lasthbitmap2);


	BitBlt(SingleControl2,0,0,top2cx,m2_h,dcMemorya2,0,0,SRCCOPY);
	StretchBlt(SingleControl2,top2cx,0,dlgcx-(top2cx*2),m2_h,dcMemorya2,top2cx,0,m2_w-(top2cx*2),m2_h,SRCCOPY);
	BitBlt(SingleControl2,dlgcx-top2cx,0,top2cx,m2_h,dcMemorya2,m2_w-top2cx,0,SRCCOPY);
}

void UISlider::SetSingleControl(HDC memdc)
{
	HDC dcMemorya1=CreateCompatibleDC(memdc);
	HBITMAP hBitmap1;
	m_pSrcImage1->GetHBITMAP(NULL,&hBitmap1);
	HBITMAP hOldBitmap1 = (HBITMAP)::SelectObject(dcMemorya1, hBitmap1);

	int m1_h = m_pSrcImage1->GetHeight();
	int m1_w =m_pSrcImage1->GetWidth();
	SingleControl1 = CreateCompatibleDC(memdc);
	HBITMAP lasthbitmap1 = CreateCompatibleBitmap(memdc,m1_w,m1_h);
	HBITMAP Oldlasthbitmap1 = (HBITMAP)::SelectObject(SingleControl1,lasthbitmap1);
	BitBlt(SingleControl1,0,0,m1_w,m1_h,dcMemorya1,0,0,SRCCOPY);

	//////////////////////////////////////////////////////////////////////

	if (m_pSrcImage2!=NULL)
	{
		HDC dcMemorya2=CreateCompatibleDC(memdc);
		HBITMAP hBitmap2;
		m_pSrcImage2->GetHBITMAP(NULL,&hBitmap2);
		HBITMAP hOldBitmap2 = (HBITMAP)::SelectObject(dcMemorya2, hBitmap2);

		int m2_h = m_pSrcImage2->GetHeight();
		int m2_w =m_pSrcImage2->GetWidth();
		SingleControl2 = CreateCompatibleDC(memdc);
		HBITMAP lasthbitmap2 = CreateCompatibleBitmap(memdc,m2_w,m2_h);
		HBITMAP Oldlasthbitmap2 = (HBITMAP)::SelectObject(SingleControl2,lasthbitmap2);
		BitBlt(SingleControl2,0,0,m2_w,m2_h,dcMemorya2,0,0,SRCCOPY);
	}
}

bool UISlider:: IMOUSEMOVE(HWND hwnd,IControl *ts,CPoint point)
{
	
	UISlider *tempslider=static_cast<UISlider*>(ts);
	tempslider->Gsliderinfo.i2_width=point.x-tempslider->Gsliderinfo.i1_x;
	//::InvalidateRect(hwnd,&tempslider->sinfo.rect,1);
	//long tempa=point.x;
	//if (point.x<tempslider->Gsliderinfo.i1_x+tempslider->Gsliderinfo.i3_srcwidth)
	//{
	//	tempa=tempslider->Gsliderinfo.i1_x;
	//}

	//if(point.x>tempslider->Gsliderinfo.i1_x+tempslider->Gsliderinfo.i1_srcwidth-tempslider->Gsliderinfo.i3_srcwidth)
	//{
	//	tempa=tempslider->Gsliderinfo.i1_x+tempslider->Gsliderinfo.i1_srcwidth-tempslider->Gsliderinfo.i3_srcwidth;
	//}


	tempslider->Gsliderinfo.i3_x=tempslider->Gsliderinfo.i2_width;
	if (tempslider->Gsliderinfo.moveimmediatelyresponse)
	{
		icontrolevent->SetSliderContorEvent(tempslider->Gsliderinfo);
	}
	/*::InvalidateRect(hwnd,&tempslider->Gsliderinfo.rect,1);*/
	//::UpdateWindow(hwnd);
	//CString *cs=&tempslider->Gsliderinfo.classname;
	//PostMessage(hwnd,WM_LAYERPAINT_MESSAGE,cs,NULL);
	return true;

}

RECT UISlider::IRECT()
{
	return this->Gsliderinfo.rect;

}

CString UISlider::ICLASSTYPE()
{
	return CString("UISlider");
}

CString UISlider::ICLASSNAME()
{
	/*UISlider *tempslider=static_cast<UISlider*>(ts);*/
	return this->Gsliderinfo.classname;
}


void UISlider::IPAINT(HDC& dc)
{
	//Bitmap *bt=new Bitmap(Gsliderinfo.i1_srcwidth,Gsliderinfo.i1_srcheight);

	//UISlider *tempslider=static_cast<UISlider*>(ts);
	if (!isshow)
	{
		return;
	}
	if (this->Gsliderinfo.i2_width>this->Gsliderinfo.i1_width)
	{
		this->Gsliderinfo.i2_width=this->Gsliderinfo.i1_width;
	}

	if(this->Gsliderinfo.i3_x>=Gsliderinfo.i2_width-Gsliderinfo.i3_srcwidth)
	{
		this->Gsliderinfo.i3_x=Gsliderinfo.i2_width-Gsliderinfo.i3_srcwidth;
	}

	if (this->Gsliderinfo.i3_x<=0)
	{
		this->Gsliderinfo.i3_x=0;
	}


	HDC dcMemorya=CreateCompatibleDC(dc);
	HDC SliderTempHDC=CreateCompatibleDC(dc);
	void *lpBitss;
	BITMAPINFO bbi;
	bbi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bbi.bmiHeader.biBitCount = 32;
	bbi.bmiHeader.biHeight = Gsliderinfo.i1_height;
	bbi.bmiHeader.biWidth = Gsliderinfo.i1_width;
	bbi.bmiHeader.biPlanes = 1;
	bbi.bmiHeader.biCompression=BI_RGB;
	bbi.bmiHeader.biXPelsPerMeter=0;
	bbi.bmiHeader.biYPelsPerMeter=0;
	bbi.bmiHeader.biClrUsed=0;
	bbi.bmiHeader.biClrImportant=0;
	HBITMAP SliderTempBitMap = CreateDIBSection(NULL, (BITMAPINFO *)&bbi, DIB_RGB_COLORS, (void **)&lpBitss, NULL, (DWORD)0);
	HBITMAP hOldBitmap  = (HBITMAP)::SelectObject(SliderTempHDC,SliderTempBitMap);

	Drawimage.AlphaDrawControl2(SingleControl1,SliderTempHDC,0,0,Gsliderinfo.i1_width,Gsliderinfo.i1_srcheight,0,0);
	if (SingleControl2!=NULL)
	{	
		Drawimage.AlphaDrawControl2(SingleControl2,SliderTempHDC,Gsliderinfo.i2_x,Gsliderinfo.i2_y,Gsliderinfo.i2_width,Gsliderinfo.i2_srcheight,0,0);
	}
	if (m_pSrcImage3!=NULL)
	{
		Drawimage.DrawControl2(m_pSrcImage3,SliderTempHDC,Gsliderinfo.i3_x,Gsliderinfo.i3_y,Gsliderinfo.i3_srcwidth,Gsliderinfo.i3_srcheight,Gsliderinfo.i3_srcx,Gsliderinfo.i3_srcy);
	}
	
	BitBlt(dc,0,0,Gsliderinfo.i1_width,Gsliderinfo.i1_height,SliderTempHDC,0,0,SRCCOPY);

	
	::SelectObject (SliderTempHDC,hOldBitmap);
	::DeleteObject(SliderTempBitMap);
	::DeleteObject(hOldBitmap);
	::DeleteDC(SliderTempHDC);


}

void UISlider::IPAINT2(HDC& dc)
{
	//Bitmap *bt=new Bitmap(Gsliderinfo.i1_srcwidth,Gsliderinfo.i1_srcheight);

	//UISlider *tempslider=static_cast<UISlider*>(ts);
	if (!isshow)
	{
		return;
	}
   if (this->Gsliderinfo.i2_width>this->Gsliderinfo.i1_width)
	{
		this->Gsliderinfo.i2_width=this->Gsliderinfo.i1_width;
	}

	if(this->Gsliderinfo.i3_x>=Gsliderinfo.i2_width-Gsliderinfo.i3_srcwidth)
	{
		this->Gsliderinfo.i3_x=Gsliderinfo.i2_width-Gsliderinfo.i3_srcwidth;
	}

	if (this->Gsliderinfo.i3_x<=0)
	{
		this->Gsliderinfo.i3_x=0;
	}
	//UISliderInfo sinfo=Gsliderinfo;
	HDC SliderTempHDC=CreateCompatibleDC(dc);
	void *lpBitss;
	BITMAPINFO bbi;
	bbi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bbi.bmiHeader.biBitCount = 32;
	bbi.bmiHeader.biHeight = Gsliderinfo.i1_height;
	bbi.bmiHeader.biWidth = Gsliderinfo.i1_width;
	bbi.bmiHeader.biPlanes = 1;
	bbi.bmiHeader.biCompression=BI_RGB;
	bbi.bmiHeader.biXPelsPerMeter=0;
	bbi.bmiHeader.biYPelsPerMeter=0;
	bbi.bmiHeader.biClrUsed=0;
	bbi.bmiHeader.biClrImportant=0;
	HBITMAP SliderTempBitMap = CreateDIBSection(NULL, (BITMAPINFO *)&bbi, DIB_RGB_COLORS, (void **)&lpBitss, NULL, (DWORD)0);
	HBITMAP hOldBitmap  = (HBITMAP)::SelectObject(SliderTempHDC,SliderTempBitMap);

	//BitBlt(dc,Gsliderinfo.i1_x,Gsliderinfo.i1_y,Gsliderinfo.i1_width,Gsliderinfo.i1_height,SingleControl1,0,0,SRCCOPY);
	//BitBlt(dc,Gsliderinfo.i2_x,Gsliderinfo.i2_y,Gsliderinfo.i2_width,Gsliderinfo.i2_height,SingleControl2,0,0,SRCCOPY);
	//BitBlt(dc,Gsliderinfo.i1_x,Gsliderinfo.i1_y,Gsliderinfo.i1_width,Gsliderinfo.i1_height,SliderTempHDC,0,0,SRCCOPY);

	Drawimage.AlphaDrawControl2(SingleControl1,SliderTempHDC,0,0,Gsliderinfo.i1_width,Gsliderinfo.i1_srcheight,0,0);
	if (SingleControl2!=NULL)
	{
		Drawimage.AlphaDrawControl2(SingleControl2,SliderTempHDC,Gsliderinfo.i2_x,Gsliderinfo.i2_y,Gsliderinfo.i2_width-3,Gsliderinfo.i2_srcheight,0,0);
		if(Gsliderinfo.i2_width>3){
			Drawimage.AlphaDrawControl2(SingleControl2,SliderTempHDC,Gsliderinfo.i2_width-3,Gsliderinfo.i2_y,3,Gsliderinfo.i2_srcheight,this->Gsliderinfo.i1_width-3,0);
		}
	}
	if (m_pSrcImage3!=NULL)
	{	
		Drawimage.DrawControl2(m_pSrcImage3,SliderTempHDC,Gsliderinfo.i3_x,Gsliderinfo.i3_y,Gsliderinfo.i3_srcwidth,Gsliderinfo.i3_srcheight,Gsliderinfo.i3_srcx,Gsliderinfo.i3_srcy);
	}

	BitBlt(dc,Gsliderinfo.i1_x,Gsliderinfo.i1_y,Gsliderinfo.i1_width,Gsliderinfo.i1_height,SliderTempHDC,0,0,SRCCOPY);

	//Drawimage.DrawControl2(m_pSrcImage1,dc,Gsliderinfo.i1_x,Gsliderinfo.i1_y,Gsliderinfo.i1_srcwidth,Gsliderinfo.i1_srcheight,Gsliderinfo.i1_srcx,Gsliderinfo.i1_srcy);
	//Drawimage.DrawControl2(m_pSrcImage2,dc,Gsliderinfo.i1_x+Gsliderinfo.i2_x,Gsliderinfo.i1_y+Gsliderinfo.i2_y,Gsliderinfo.i2_srcwidth,Gsliderinfo.i2_srcheight,Gsliderinfo.i2_srcx,Gsliderinfo.i2_srcy);
	//Drawimage.DrawControl2(m_pSrcImage3,dc,Gsliderinfo.i1_x+Gsliderinfo.i3_x,Gsliderinfo.i1_y+Gsliderinfo.i3_y,Gsliderinfo.i3_srcwidth,Gsliderinfo.i3_srcheight,Gsliderinfo.i3_srcx,Gsliderinfo.i3_srcy);
	::SelectObject (SliderTempHDC,hOldBitmap);
	::DeleteObject(SliderTempBitMap);
	::DeleteObject(hOldBitmap);
	::DeleteDC(SliderTempHDC);

	

}

bool UISlider::IMOUSELEAVE(HWND hwnd,bool rp)
{
	return false;
}
bool UISlider::ILBUTTONDOWN(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,bool & m_bMouseTracking)
{
	UISlider *tempslider=static_cast<UISlider*>(ts);
	tempslider->Gsliderinfo.i2_width=point.x-tempslider->Gsliderinfo.i1_x;;

	//long tempa=point.x;
	//if (point.x<tempslider->Gsliderinfo.i1_x+tempslider->Gsliderinfo.i3_srcwidth)
	//{
	//	tempa=tempslider->Gsliderinfo.i1_x;
	//}

	//if(point.x>tempslider->Gsliderinfo.i1_x+tempslider->Gsliderinfo.i1_srcwidth-tempslider->Gsliderinfo.i3_srcwidth)
	//{
	//	tempa=tempslider->Gsliderinfo.i1_x+tempslider->Gsliderinfo.i1_srcwidth-tempslider->Gsliderinfo.i3_srcwidth;
	//}


	tempslider->Gsliderinfo.i3_x=tempslider->Gsliderinfo.i2_width;
	tempslider->Gsliderinfo.MouseType=UIEVENT_BUTTONDOWN;
	//::InvalidateRect(hwnd,&tempslider->Gsliderinfo.rect,1);
	//::UpdateWindow(hwnd);
	return true;
	//icontrolevent->SetSliderContorEvent(tempslider->Gsliderinfo);
	
}
bool UISlider::ILBUTTONUP(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList)
{
	UISlider *tempslider=static_cast<UISlider*>(ts);
	tempslider->Gsliderinfo.MouseType=UIEVENT_BUTTONUP;
	icontrolevent->SetSliderContorEvent(tempslider->Gsliderinfo);
	//::InvalidateRect(hwnd,&tempslider->Gsliderinfo.rect,1);
	//::UpdateWindow(hwnd);
	return true;
}

bool UISlider::IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int controlid)
{
	//testslider *tempslider=static_cast<testslider*>(ts);
	//tempslider->sinfo.i3_srcx=32;
	//::InvalidateRect(hwnd,&tempslider->sinfo.rect,1);
	return false;
}
bool UISlider::ILBUTTONDBCLICK(HWND hwnd,CPoint point)
{
	return false;
}
int UISlider::IWIDTH()
{
	return Gsliderinfo.i1_width;
}
int UISlider::IHIGH()
{
	return Gsliderinfo.i1_srcheight;
}

void UISlider::IHIDE()
{
	this->Gsliderinfo.rect.left=-1;
	this->Gsliderinfo.rect.top=-1;
	this->Gsliderinfo.rect.right=-1;
	this->Gsliderinfo.rect.bottom=-1;
}
void UISlider::ISHOW()
{
	ControlClass *controlclass=new ControlClass();
	this->Gsliderinfo.rect = controlclass->GetRect(this->Gsliderinfo.i1_x,this->Gsliderinfo.i1_y,this->Gsliderinfo.i1_srcwidth,this->Gsliderinfo.i1_srcheight);
	delete controlclass;
}