#include "StdAfx.h"
#include "UICanvar.h"
#include "UICanvar.h"


UICanvar::UICanvar(HWND hwnd):DestPt(0,0),blackBrush(Color(255, 0, 255)),GlobalHwnd(hwnd),m_bMouseTracking(true),p_paint(true),BgSrcImg(0),BgSourceConstantAlpha(255)
{
	imAtt.SetColorKey(Color(255, 0, 255),Color(255, 0, 255),ColorAdjustTypeDefault);
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 255;

	ResetCurrentRECT();

	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.hwndTrack = GlobalHwnd;
	tme.dwFlags = TME_LEAVE;
	tme.dwHoverTime =1;
	//BgSrcImg=new Bitmap(L"res\\ngb2.png");
	BgFrameImg =new Bitmap(L"res\\nbgframe.png");
	BgPlayShadow =new Bitmap(L"res\\playshadow.png");
	BgListShadow= new Bitmap(L"res\\listshadow.png");
	needpaintall=1;
	BGMASKCOLOR=RGB(0,0,0);
	//otx=0;
	//oty=0;
}


UICanvar::~UICanvar(void)
{
}

void UICanvar::AddControlToCanvar(LPIControl t)
{
	ControlArrayList.Add(t);	
}

void UICanvar::OnInit(CClientDC *dc)
{
	::SelectObject (OutPutHDC,_Otempbmp);
	::DeleteObject(tempbmp);
	::DeleteObject(_Otempbmp);


	::SelectObject (ContorlHDC,_Obbt);
	::DeleteObject(bbt);
	::DeleteObject(_Obbt);


	::SelectObject (BgHDC,_OhBitmap);
	::DeleteObject(hBitmap);
	::DeleteObject(_OhBitmap);

	DeleteDC(BgHDC);
	DeleteDC(FrameHDC);
	DeleteDC(OutPutHDC);
	BgHDC = CreateCompatibleDC(dc->m_hDC);
	void *BglpBits;
	BITMAPINFO Bgbi;
	Bgbi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	Bgbi.bmiHeader.biBitCount = 32;
	if (ISDLGALPHA)
	{
		Bgbi.bmiHeader.biHeight = MAINBG_HEIGHT-10;
		Bgbi.bmiHeader.biWidth = MAINBG_WIDTH-10;
	} 
	else
	{
		Bgbi.bmiHeader.biHeight = MAINBG_HEIGHT;
		Bgbi.bmiHeader.biWidth = MAINBG_WIDTH;
	}

	Bgbi.bmiHeader.biPlanes = 1;
	Bgbi.bmiHeader.biCompression=BI_RGB;
	Bgbi.bmiHeader.biXPelsPerMeter=0;
	Bgbi.bmiHeader.biYPelsPerMeter=0;
	Bgbi.bmiHeader.biClrUsed=0;
	Bgbi.bmiHeader.biClrImportant=0;
	hBitmap = CreateDIBSection(NULL, (BITMAPINFO *)&Bgbi, DIB_RGB_COLORS, (void **)&BglpBits, NULL, (DWORD)0);
	_OhBitmap = (HBITMAP)::SelectObject(BgHDC, hBitmap);


	if (ISDLGALPHA)
	{
		FrameHDC = CreateCompatibleDC(dc->m_hDC);
		void *FramelpBits;
		BITMAPINFO Framebi;
		Framebi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		Framebi.bmiHeader.biBitCount = 32;
		Framebi.bmiHeader.biHeight = MAINBG_HEIGHT;
		Framebi.bmiHeader.biWidth = MAINBG_WIDTH;
		Framebi.bmiHeader.biPlanes = 1;
		Framebi.bmiHeader.biCompression=BI_RGB;
		Framebi.bmiHeader.biXPelsPerMeter=0;
		Framebi.bmiHeader.biYPelsPerMeter=0;
		Framebi.bmiHeader.biClrUsed=0;
		Framebi.bmiHeader.biClrImportant=0;
		HBITMAP FrameHBitmap = CreateDIBSection(NULL, (BITMAPINFO *)&Framebi, DIB_RGB_COLORS, (void **)&FramelpBits, NULL, (DWORD)0);

		HBITMAP _OFrameHBitmap = (HBITMAP)::SelectObject(FrameHDC, FrameHBitmap);
		drawimages.DrawFrameBorder(FrameHDC,BgFrameImg,MAINBG_WIDTH,MAINBG_HEIGHT);
		drawimages.DrawFrameBg(BgHDC,BGMASKCOLOR,MAINBG_WIDTH-10,MAINBG_HEIGHT-10,1,BgSrcImg,BgSourceConstantAlpha);
		drawimages.DrawFrameStatic(BgPlayShadow,BgHDC,0,156,MAINBG_WIDTH,67);
		drawimages.DrawFrameStatic(BgListShadow,BgHDC,0,223,MAINBG_WIDTH,(MAINBG_HEIGHT-220-34-10));
		::DeleteObject(FrameHBitmap);
		::DeleteObject(_OFrameHBitmap);
	}else{
		drawimages.DrawFrameBg(BgHDC,BGMASKCOLOR,MAINBG_WIDTH,MAINBG_HEIGHT,0,BgSrcImg);
		drawimages.DrawFrameStatic(BgPlayShadow,BgHDC,0,156,MAINBG_WIDTH,67);
		drawimages.DrawFrameStatic(BgListShadow,BgHDC,0,223 ,MAINBG_WIDTH,MAINBG_HEIGHT-220-34);
	}

	ContorlHDC=CreateCompatibleDC(dc->m_hDC);
	//if (ISDLGALPHA)
	//{

	//	bbt=CreateCompatibleBitmap(dc->m_hDC,MAINBG_WIDTH-10,MAINBG_HEIGHT-10);
	//	_Obbt = (HBITMAP)SelectObject(ContorlHDC,bbt);

	//} 
	//else
	//{
		bbt=CreateCompatibleBitmap(dc->m_hDC,MAINBG_WIDTH,MAINBG_HEIGHT);
		_Obbt = (HBITMAP)SelectObject(ContorlHDC,bbt);

	//}

	
	for (int i = 0; i < ControlArrayList.GetSize(); i++)
	{
		IControl *t= ControlArrayList.GetAt(i);
		HDC _memdc=CreateCompatibleDC(dc->m_hDC);
		HBITMAP hBitmap= CreateCompatibleBitmap(dc->m_hDC,t->IWIDTH(),t->IHIGH());
		HBITMAP _OhBitmap = (HBITMAP)::SelectObject(_memdc, hBitmap);
		
		if (t->isshow)
		{
			t->IPAINT(_memdc);
			BitBlt(ContorlHDC,t->IRECT().left,t->IRECT().top,t->IWIDTH(),t->IHIGH(),_memdc,0,0,SRCCOPY);
		}
		::SelectObject (_memdc,_OhBitmap);
		::DeleteObject(hBitmap);
		::DeleteObject(_OhBitmap);
		::DeleteDC(_memdc);
	}

	OutPutHDC=CreateCompatibleDC(dc->m_hDC);
	void *OutPutlpBits;
	BITMAPINFO OutPutbi;
	OutPutbi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	OutPutbi.bmiHeader.biBitCount = 32;
	OutPutbi.bmiHeader.biHeight = MAINBG_HEIGHT;
	OutPutbi.bmiHeader.biWidth = MAINBG_WIDTH;
	OutPutbi.bmiHeader.biPlanes = 1;
	OutPutbi.bmiHeader.biCompression=BI_RGB;
	OutPutbi.bmiHeader.biXPelsPerMeter=0;
	OutPutbi.bmiHeader.biYPelsPerMeter=0;
	OutPutbi.bmiHeader.biClrUsed=0;
	OutPutbi.bmiHeader.biClrImportant=0;
	tempbmp = CreateDIBSection(NULL, (BITMAPINFO *)&OutPutbi, DIB_RGB_COLORS, (void **)&OutPutlpBits, NULL, (DWORD)0);
	_Otempbmp = (HBITMAP)::SelectObject(OutPutHDC,tempbmp);

	for (int i=0;i<MAINBG_HEIGHT*MAINBG_WIDTH;i++)
	{
		char * a=(char*)(&((UINT32*)OutPutlpBits)[i]);
		a[3]=255;
	}
/*	CRgn rgn; 
	rgn.CreateRoundRectRgn(0,0,MAINBG_WIDTH,MAINBG_HEIGHT,3,3); 
	SetWindowRgn(GlobalHwnd,rgn,FALSE);*/ 

	if (ISDLGALPHA){
		BitBlt(OutPutHDC,0,0,MAINBG_WIDTH,MAINBG_HEIGHT,FrameHDC,0,0,SRCCOPY);
		BitBlt(OutPutHDC,5,5,MAINBG_WIDTH-10,MAINBG_HEIGHT-10,BgHDC,0,0,SRCCOPY);
		AlphaBlend(OutPutHDC,0,0,MAINBG_WIDTH,MAINBG_HEIGHT,ContorlHDC,0,0,MAINBG_WIDTH,MAINBG_HEIGHT,blendFunc32bpp);
		
		psize.cx=MAINBG_WIDTH;
		psize.cy=MAINBG_HEIGHT;

		::UpdateLayeredWindow(GlobalHwnd,dc->GetSafeHdc(),NULL,&psize,OutPutHDC,&DestPt,0,&blendFunc32bpp,ULW_ALPHA);
	}
	else
	{
		BitBlt(OutPutHDC,0,0,MAINBG_WIDTH,MAINBG_HEIGHT,BgHDC,0,0,SRCCOPY);
		AlphaBlend(OutPutHDC,0,0,MAINBG_WIDTH,MAINBG_HEIGHT,ContorlHDC,0,0,MAINBG_WIDTH,MAINBG_HEIGHT,blendFunc32bpp);
	}

}

void UICanvar::TEMP(Bitmap *TempPrintDCBitmap,int n)
{
	//IControl *_control=0;
	//*_control=*(controlclass->FindControl(NeedPaintControlArrayList.GetAt(n),&ControlArrayList));
	//_control->IPAINT(GlobalHwnd,NULL,PrintDCBitmap);
}

void UICanvar::Paint(CPaintDC *dc,RECT rect)
{

		

		if (ISDLGALPHA)
		{
			psize.cx=MAINBG_WIDTH;
			psize.cy=MAINBG_HEIGHT;
			IControl * control=controlclass->FindControl(rect,&ControlArrayList);
			ControlClass::ConsoleWrite(control->ICLASSNAME());
			if (!control)
			{
				return;
			}
			control->IPAINT2(ContorlHDC);
			BitBlt(OutPutHDC,control->IRECT().left,control->IRECT().top,control->IWIDTH(),control->IHIGH(),BgHDC,control->IRECT().left-5,control->IRECT().top-5,SRCCOPY);		
			AlphaBlend(OutPutHDC,control->IRECT().left,control->IRECT().top,control->IWIDTH(),control->IHIGH(),ContorlHDC,control->IRECT().left,control->IRECT().top,control->IWIDTH(),control->IHIGH(),blendFunc32bpp);		
			::UpdateLayeredWindow(GlobalHwnd,dc->GetSafeHdc(),NULL,&psize,OutPutHDC,&DestPt,0,&blendFunc32bpp,ULW_ALPHA);	

		}
		else
		{		
			if (needpaintall)
			{
				BitBlt(dc->GetSafeHdc(),0,0,MAINBG_WIDTH,MAINBG_HEIGHT,OutPutHDC,0,0,SRCCOPY);
				needpaintall=0;
				return;
			}

			int x=rect.left;
			int y=rect.top;
			int cx=rect.right-rect.left;
			int cy=rect.bottom-rect.top;
			for (int i = 0; i < ControlArrayList.GetSize(); i++)
			{
				IControl *t= ControlArrayList.GetAt(i);
				t->IPAINT2(ContorlHDC);
			}
			BitBlt(OutPutHDC,x,y,cx,cy,BgHDC,x,y,SRCCOPY);		
			AlphaBlend(OutPutHDC,x,y,cx,cy,ContorlHDC,x,y,cx,cy,blendFunc32bpp);
			BitBlt(dc->m_hDC,x,y,cx,cy,OutPutHDC,x,y,SRCCOPY);
		}	
}

void UICanvar::LButtonDown(CPoint point)
{
	//if (!p_paint)
	//{
	//	return;
	//}
	::SetCapture(GlobalHwnd);
	IControl * control=controlclass->FindControl(point,&ControlArrayList);
	if(control!=NULL){
		//NeedPaintControlArrayList.RemoveAll();
		bool a=true;
		m_bMouseTracking=false;
		
		CurrentContolRect=control->IRECT();
		if(control->ILBUTTONDOWN(GlobalHwnd,control,NULL,point,a))
		{
			AddMessageQueue(control->IRECT());
			::InvalidateRect(GlobalHwnd,&control->IRECT(),false);
			::UpdateWindow(GlobalHwnd);
		};		
		
	}

}

void UICanvar::LBUTTONDBCLICK(HWND hwnd,CPoint point)
{
	//if (!p_paint)
	//{
	//	return;
	//}
	IControl * control=controlclass->FindControl(point,&ControlArrayList);
	if(control!=NULL){
		//NeedPaintControlArrayList.RemoveAll();
		
		if(control->ILBUTTONDBCLICK(GlobalHwnd,point)){
			ControlClass::ConsoleWrite(control->ICLASSNAME());

			AddMessageQueue(control->IRECT());
			::InvalidateRect(GlobalHwnd,&control->IRECT(),false);
			::UpdateWindow(GlobalHwnd);
		};		
		
	}
}

void UICanvar::LButtonUp(CPoint point)
{
	//if (!p_paint)
	//{
	//	return;
	//}
	//controlclass->ConsoleWrite(controlclass->IntFormatCString(CString("LButtonUp"),CString("")));
	ReleaseCapture();
	IControl * control=controlclass->FindControl(point,&ControlArrayList);
	if(control!=NULL){
		//NeedPaintControlArrayList.RemoveAll();
		m_bMouseTracking=true;
		//controlclass->ConsoleWrite(controlclass->IntFormatCString(CString("LButtonUp"),control->ICLASSNAME()));
		
		if(control->ILBUTTONUP(GlobalHwnd,control,NULL))
			AddMessageQueue(control->IRECT());
			::InvalidateRect(GlobalHwnd,&control->IRECT(),false);
			::UpdateWindow(GlobalHwnd);
		}
	
}

void UICanvar::MouseHover(CPoint point)
{
	//if (!p_paint)
	//{
	//	return;
	//}
	 //IControl * control=controlclass->FindControl(point,&ControlArrayList);
	if(!::PtInRect(&CurrentContolRect,point)){

			IControl * pcontrol=controlclass->FindControl(CurrentContolRect,&ControlArrayList);
			if (pcontrol!=NULL)
			{	
				if (pcontrol->IMOUSELEAVE(GlobalHwnd,true)){
				DestroyWindow(hwndTT);
				::InvalidateRect(GlobalHwnd,&pcontrol->IRECT(),false);
				::UpdateWindow(GlobalHwnd);
				}
			}

			IControl * control=controlclass->FindControl(point,&ControlArrayList);
			if (control!=NULL)
			{
				CurrentContolRect=control->IRECT();
				//controlclass->ConsoleWrite(controlclass->IntFormatCString(CString("MouseHover-2"),control->ICLASSNAME()));

				if (control->IMOUSEHOVER(GlobalHwnd,control,NULL,point))
				{
					////////////////////////
					DestroyWindow(hwndTT);
					CreateToolTipForRect(GlobalHwnd,control->tipstr);
					///////////////////////
					AddMessageQueue(CurrentContolRect);
					::InvalidateRect(GlobalHwnd,&control->IRECT(),false);
					::UpdateWindow(GlobalHwnd);
				}

			}
			else
			{
				ResetCurrentRECT();
			}
	}



	// if(!::PtInRect(&CurrentContolRect,point)){
	//	IControl * control=controlclass->FindControl(point,&ControlArrayList);
	//	if(control!=NULL){

	//		//NeedPaintControlArrayList.RemoveAll();
	//		IControl * pcontrol=controlclass->FindControl(CurrentContolRect,&ControlArrayList);
	//		if (pcontrol!=NULL)
	//		{			
	//			/*PrevContorlRect=pcontrol->IRECT();*/
	//			//controlclass->ConsoleWrite(controlclass->IntFormatCString(CString("MouseHover-1"),pcontrol->ICLASSNAME()));
	//			
	//			if (pcontrol->IMOUSELEAVE(GlobalHwnd,true))
	//			{
	//				DestroyWindow(hwndTT);
	//				CreateToolTipForRect(GlobalHwnd,pcontrol->tipstr);
	//				AddMessageQueue(CurrentContolRect);
	//				::InvalidateRect(GlobalHwnd,&pcontrol->IRECT(),false);
	//				::UpdateWindow(GlobalHwnd);
	//			}
	//			
	//			//MouseLeave();
	//			
	//		}
	//		CurrentContolRect=control->IRECT();
	//		controlclass->ConsoleWrite(controlclass->IntFormatCString(CString("MouseHover-2"),control->ICLASSNAME()));
	//		
	//		if (control->IMOUSEHOVER(GlobalHwnd,control,NULL,point))
	//		{
	//			////////////////////////
	//			DestroyWindow(hwndTT);
	//			CreateToolTipForRect(GlobalHwnd,control->tipstr);
	//			///////////////////////
	//			AddMessageQueue(CurrentContolRect);
	//			::InvalidateRect(GlobalHwnd,&control->IRECT(),false);
	//			::UpdateWindow(GlobalHwnd);
	//		}
	//	}	
	//
	//}
}
void UICanvar::MouseMove(CPoint point)
{
	if(m_bMouseTracking){
		_TrackMouseEvent(&tme);
		MouseHover(point);
	}
	else
	{
		
		//SetCapture(GlobalHwnd);
		//NeedPaintControlArrayList.RemoveAll();
		//if (!p_paint)
		//{
		//	return;
		//}	
		//CString cs;
		//cs.Format(_T("%d"),point.y);
		//controlclass->ConsoleWrite(controlclass->IntFormatCString(CString("操他妈的UISlider,UIButton"),cs));
		IControl * control=controlclass->FindControl(CurrentContolRect,&ControlArrayList);
		if (control!=NULL && controlclass->IsStrInStrAarry(control->ICLASSTYPE(),CString("UIList,UISlider")))
		{

			//controlclass->ConsoleWrite(controlclass->IntFormatCString(CString("MouseMove"),CString("")));
			//if (NeedPaintControlArrayList.GetSize()<1)
			//{
			//	
			//}
			
			if(control->IMOUSEMOVE(GlobalHwnd,control,point))
			{
				AddMessageQueue(control->IRECT());
				::InvalidateRect(GlobalHwnd,&control->IRECT(),false);::UpdateWindow(GlobalHwnd);
			}
			
		}
	}
}

void UICanvar::MouseLeave()
{
	//if (!p_paint)
	//{
	//	return;
	//}
	DestroyWindow(hwndTT);
	IControl * pcontrol=controlclass->FindControl(CurrentContolRect,&ControlArrayList);
	if (pcontrol!=NULL)
	{			
		//NeedPaintControlArrayList.RemoveAll();
		CurrentContolRect=pcontrol->IRECT();
		
		//controlclass->ConsoleWrite(controlclass->IntFormatCString(CString("进入：MouseLeave"),pcontrol->ICLASSNAME()));
		if(pcontrol->IMOUSELEAVE(GlobalHwnd))
		{
			AddMessageQueue(CurrentContolRect);
			::InvalidateRect(GlobalHwnd,&pcontrol->IRECT(),false);
			::UpdateWindow(GlobalHwnd);
			//::UpdateWindow(GlobalHwnd);
		}
		
	}
	/*RECT temprect={-1,-1,-1,-1};
	CurrentContolRect=temprect;
	*/ResetCurrentRECT();
	m_bMouseTracking=true;
}

void UICanvar::UpdateCanvar(IControl * pcontrol)
{
	::InvalidateRect(GlobalHwnd,&pcontrol->IRECT(),false);
	::UpdateWindow(GlobalHwnd);
}

void UICanvar::AddMessageQueue(RECT rect)
{
	//bool isaddtoarray=true;
	//for (int i = 0; i < NeedPaintControlArrayList.GetSize(); i++)
	//{
	//	RECT T = NeedPaintControlArrayList.ElementAt(i);
	//	if(EqualRect(&T,&rect)){
	//		isaddtoarray=false;
	//		break;
	//	}
	//}
	//if (isaddtoarray)
	//{
	//	NeedPaintControlArrayList.Add(rect);
	//}
}

void UICanvar::Add2PaintQueue(IControl * pcontrol)
{
	//AddMessageQueue(pcontrol->IRECT());
}

void UICanvar::HideControl(LPIControl t)
{
	t->isshow=false;	
	UpdateCanvar(t);
	t->IHIDE();
}
void UICanvar::ShowControl(LPIControl t)
{
	t->isshow=true;	
	t->ISHOW();
	UpdateCanvar(t);
}


void UICanvar::CreateToolTipForRect(HWND hwndParent,LPCTSTR str) 
{ 
	if (str==L"")
	{
		return;
	}
		hwndTT = CreateWindowEx(WS_EX_TOPMOST, 
		TOOLTIPS_CLASS, 
		L"CAOAOAOAOAAOAOAOA", 
		WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		hwndParent, 
		NULL, 
		AfxGetInstanceHandle(), 
		NULL); 

	SetWindowPos(hwndTT, 
		HWND_TOPMOST, 
		0, 0, 0, 0, 
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE); 

	TOOLINFO ti = {0}; 
	ti.cbSize = sizeof(TOOLINFO); 
	ti.uFlags = TTF_SUBCLASS; 
	ti.hwnd = hwndParent; 
	ti.hinst = AfxGetInstanceHandle(); 
	ti.lpszText = (LPWSTR)str; 

	GetClientRect(hwndParent, &ti.rect); 

	SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO)&ti); 
} 


void UICanvar::ResetCurrentRECT()
{
	CurrentContolRect.left=-1;
	CurrentContolRect.top=-1;
	CurrentContolRect.right=-1;
	CurrentContolRect.bottom=-1;
}

bool UICanvar::IsOperationControl(CPoint point)
{
	POINT cp={point.x,point.y};
	ScreenToClient(GlobalHwnd,&cp);
	point.x=cp.x;
	point.y=cp.y;
	IControl * control=controlclass->FindControl(point,&ControlArrayList);
	if (control!=NULL)
	{
		return true;
	}
	return false;
}

void UICanvar::OnSize(CClientDC *dc,int cx,int cy)
{

	DeleteDC(BgHDC);
	BgHDC = CreateCompatibleDC(dc->m_hDC);
	void *lpBits;
	BITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biHeight = cy;
	bi.bmiHeader.biWidth = cx;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biCompression=BI_RGB;
	bi.bmiHeader.biXPelsPerMeter=0;
	bi.bmiHeader.biYPelsPerMeter=0;
	bi.bmiHeader.biClrUsed=0;
	bi.bmiHeader.biClrImportant=0;
	HBITMAP hBitmap = CreateDIBSection(NULL, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&lpBits, NULL, (DWORD)0);
	SelectObject(BgHDC, hBitmap);
	/*DrawImages drawimages;
	drawimages.DrawFrameBg2(BgHDC,BgSrcImg,cx,cy);*/
	if (ISDLGALPHA)
	{	
		RECT rect={0,0,cx-10,cy-10};
		HBRUSH brush=CreateSolidBrush(RGB(255,155,155));
		FillRect(BgHDC,&rect,brush);

		for (int i=0;i<cx*cy;i++)
		{
			char * a=(char*)(&((UINT32*)lpBits)[i]);
			a[3]=255;
		}
	} 
	else
	{
		RECT rect={0,0,cx,cy};
		HBRUSH brush=CreateSolidBrush(RGB(255,155,155));
		FillRect(BgHDC,&rect,brush);

	}


	//DeleteDC(OutPutHDC);

	OutPutHDC=CreateCompatibleDC(dc->m_hDC);
	void *lpBitss;
	BITMAPINFO bbi;
	bbi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bbi.bmiHeader.biBitCount = 32;
	bbi.bmiHeader.biHeight = cy;
	bbi.bmiHeader.biWidth = cx;
	bbi.bmiHeader.biPlanes = 1;
	bbi.bmiHeader.biCompression=BI_RGB;
	bbi.bmiHeader.biXPelsPerMeter=0;
	bbi.bmiHeader.biYPelsPerMeter=0;
	bbi.bmiHeader.biClrUsed=0;
	bbi.bmiHeader.biClrImportant=0;
	HBITMAP tempbmp = CreateDIBSection(NULL, (BITMAPINFO *)&bbi, DIB_RGB_COLORS, (void **)&lpBitss, NULL, (DWORD)0);
	SelectObject(OutPutHDC,tempbmp);

	ContorlHDC=CreateCompatibleDC(dc->m_hDC);
	if (ISDLGALPHA)
	{
	}
	HBITMAP bbt=CreateCompatibleBitmap(dc->m_hDC,MAINBG_WIDTH-10,MAINBG_HEIGHT-10);
	SelectObject(ContorlHDC,bbt);


	for (int i = 0; i < ControlArrayList.GetSize(); i++)
	{
		IControl *t= ControlArrayList.GetAt(i);
		HDC _memdc=CreateCompatibleDC(dc->m_hDC);
		HBITMAP hBitmap= CreateCompatibleBitmap(dc->m_hDC,t->IWIDTH(),t->IHIGH());
		SelectObject(_memdc, hBitmap);
		t->IPAINT(_memdc);
		BitBlt(ContorlHDC,t->IRECT().left,t->IRECT().top,t->IWIDTH(),t->IHIGH(),_memdc,0,0,SRCCOPY);
	}


	if (ISDLGALPHA)
	{
		FrameHDC = CreateCompatibleDC(dc->m_hDC);
		void *FramelpBits;
		BITMAPINFO Framebi;
		Framebi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		Framebi.bmiHeader.biBitCount = 32;
		Framebi.bmiHeader.biHeight = cy;
		Framebi.bmiHeader.biWidth = cx;
		Framebi.bmiHeader.biPlanes = 1;
		Framebi.bmiHeader.biCompression=BI_RGB;
		Framebi.bmiHeader.biXPelsPerMeter=0;
		Framebi.bmiHeader.biYPelsPerMeter=0;
		Framebi.bmiHeader.biClrUsed=0;
		Framebi.bmiHeader.biClrImportant=0;
		HBITMAP FrameHBitmap = CreateDIBSection(NULL, (BITMAPINFO *)&Framebi, DIB_RGB_COLORS, (void **)&FramelpBits, NULL, (DWORD)0);
		SelectObject(FrameHDC, FrameHBitmap);
		drawimages.DrawFrameBorder(FrameHDC,BgFrameImg,cx,cy);

		BitBlt(OutPutHDC,0,0,cx,cy,FrameHDC,0,0,SRCCOPY);
		BitBlt(OutPutHDC,5,5,cx-10,cy-10,BgHDC,0,0,SRCCOPY);
		AlphaBlend(OutPutHDC,5,5,cx-10,cy-10,ContorlHDC,0,0,cx-10,cy-10,blendFunc32bpp);
		psize.cx=cx;
		psize.cy=cy;
		::UpdateLayeredWindow(GlobalHwnd,dc->GetSafeHdc(),NULL,&psize,OutPutHDC,&DestPt,0,&blendFunc32bpp,ULW_ALPHA);	
	}
	else
	{
		BitBlt(OutPutHDC,0,0,cx,cy,BgHDC,0,0,SRCCOPY);
		AlphaBlend(OutPutHDC,0,0,cx,cy,ContorlHDC,0,0,cx,cy,blendFunc32bpp);
		BitBlt(dc->GetSafeHdc(),0,0,cx,cy,OutPutHDC,0,0,SRCCOPY);
	}

	

}