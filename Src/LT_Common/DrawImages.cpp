#include "StdAfx.h"
#include "DrawImages.h"
#include <Gdipluseffects.h>
DrawImages::DrawImages(void)
{
}

DrawImages::~DrawImages(void)
{
}

void DrawImages::DrawMainBg(HDC &hdc,long width,long height,Bitmap* image)
{
	Graphics graphics(hdc);
	graphics.DrawImage(image,0,0,0,0,width,height,(Unit)2);

}

void DrawImages::DrawMainBg(HWND m_hWnd,long width,long height,Bitmap* image,BYTE p)
{
	HDC hDC=::GetDC(m_hWnd);
	HDC hMemDC=::CreateCompatibleDC(hDC);
	BITMAPINFO *bitmapinfo=new BITMAPINFO();
	bitmapinfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfo->bmiHeader.biBitCount = 32;
	bitmapinfo->bmiHeader.biHeight = height;
	bitmapinfo->bmiHeader.biWidth = width;
	bitmapinfo->bmiHeader.biPlanes = 1;
	bitmapinfo->bmiHeader.biCompression=BI_RGB;
	bitmapinfo->bmiHeader.biXPelsPerMeter=0;
	bitmapinfo->bmiHeader.biYPelsPerMeter=0;
	bitmapinfo->bmiHeader.biClrUsed=0;
	bitmapinfo->bmiHeader.biClrImportant=0;
	bitmapinfo->bmiHeader.biSizeImage = bitmapinfo->bmiHeader.biWidth * bitmapinfo->bmiHeader.biHeight * bitmapinfo->bmiHeader.biBitCount / 8;
	HBITMAP hBitmap=::CreateDIBSection (hMemDC,bitmapinfo, 0,NULL, 0, 0);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject (hMemDC,hBitmap);
	Graphics *graphics=new Graphics(hMemDC);
	graphics->DrawImage(image,0,0,0,0,width,height,(Unit)2);
	CPoint *DestPt=new CPoint(0,0);
	CSize *psize=new CSize(width,height);
	BLENDFUNCTION *blendFunc32bpp=new BLENDFUNCTION;
	blendFunc32bpp->AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp->BlendFlags = 0;
	blendFunc32bpp->BlendOp = AC_SRC_OVER;
	blendFunc32bpp->SourceConstantAlpha = p;

	::UpdateLayeredWindow(m_hWnd,hDC,NULL,psize,hMemDC,DestPt,0,blendFunc32bpp,ULW_ALPHA);	
	::SelectObject (hMemDC,hOldBitmap);
	::DeleteObject(hBitmap);
	::DeleteObject(hOldBitmap);
	delete bitmapinfo;
	delete graphics;
	delete DestPt;
	delete psize;
	delete blendFunc32bpp;
	::DeleteDC(hMemDC);
	::ReleaseDC(m_hWnd,hDC);

}

void DrawImages::DrawFrameBg2(HDC& memdc,Bitmap * bt,int bcx,int bcy)
{
	COLORREF m_clrCustomBK = RGB(255,0,255);
	RECT rect={0,0,bcx,bcy};
	HBRUSH brush=CreateSolidBrush(m_clrCustomBK);
	void *lpBits;
	HDC Tdc=CreateCompatibleDC(memdc);
	BITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biHeight = bcy;
	bi.bmiHeader.biWidth = bcx;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biCompression=BI_RGB;
	bi.bmiHeader.biXPelsPerMeter=0;
	bi.bmiHeader.biYPelsPerMeter=0;
	bi.bmiHeader.biClrUsed=0;
	bi.bmiHeader.biClrImportant=0;

	HBITMAP THBITMAP = CreateDIBSection(NULL, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&lpBits, NULL, (DWORD)0);
	SelectObject(Tdc, THBITMAP);
	FillRect(Tdc,&rect,brush);
	for (int i=0;i<bcx*bcy;i++)
	{
		char * a=(char*)(&((UINT32*)lpBits)[i]);
		a[3]=255;
	}


	BLENDFUNCTION blendFunc32bpp;
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 100;
	AlphaBlend(memdc,0,0,bcx,bcy,Tdc,0,0,bcx,bcy,blendFunc32bpp);

}

void DrawImages::DrawFrameBorder(HDC& memdc,Bitmap * bt,int dlgcx,int dlgcy)
{
	HDC dcMemorya=CreateCompatibleDC(memdc);
	HBITMAP hBitmap;
	bt->GetHBITMAP(NULL,&hBitmap);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(dcMemorya, hBitmap);
	SelectObject(dcMemorya,hBitmap);
	//int WlessFive=dlgcx-5;
	//int HlessFive=dlgcy-5;
	//int WlessTen=dlgcx-(2*5);
	//int HlessTen=dlgcy-(2*5);
	int picwidth = bt->GetWidth();
	int picheight =bt->GetHeight();

	int _W = dlgcx-(2*5);//上下部分的宽度
	int _H = dlgcy-(2*5);//左右部分的高度

	int _WMultiple = _W/297 ;//上下部分与原图的倍数
	int _HMultiple = _H/585;//左右部分与原图的倍数
	int _WRemainder = _W%297 ;//上下部分与原图的余数
	int _HRemainder = _H%585;//左右部分与原图的余数


	BitBlt(memdc,0,0,5,5,dcMemorya,0,0,SRCCOPY);//左上角的拐角部分
	///////////画出上半部分中间的长条///////////////////////////
	//for (int i=0;i<_WMultiple;i++)
	//{
	//	BitBlt(memdc,i*297+5,0,297,5,dcMemorya,5,0,SRCCOPY);
	//}
	//BitBlt(memdc,(_WMultiple*297)+5,0,_WRemainder,5,dcMemorya,5,0,SRCCOPY);
	StretchBlt(memdc,5,0,_W,5,dcMemorya,5,0,picwidth-10,5,SRCCOPY);
	/////////////////////////////////////////////////////////////////
	BitBlt(memdc,dlgcx-5,0,5,5,dcMemorya,picwidth-5,0,SRCCOPY);//右上角的拐角部分


	BitBlt(memdc,0,dlgcy-5,5,5,dcMemorya,0,picheight-5,SRCCOPY);//左下角的拐角部分
	/////////////画出下半部分中间的长条///////////////////////////
	//for (int i=0;i<_WMultiple;i++)
	//{
	//	BitBlt(memdc,i*297+5,dlgcy-5,297,5,dcMemorya,5,595-5,SRCCOPY);
	//}
	//BitBlt(memdc,(_WMultiple*297)+5,dlgcy-5,_WRemainder,5,dcMemorya,5,0,SRCCOPY);
	StretchBlt(memdc,5,dlgcy-5,_W,5,dcMemorya,5,picheight-5,bt->GetWidth()-10,5,SRCCOPY);
	///////////////////////////////////////////////////////////////////
	BitBlt(memdc,dlgcx-5,dlgcy-5,5,5,dcMemorya,picwidth-5,picheight-5,SRCCOPY);//右下角的拐角部分


	///////////////////////////////左边部分的长条//////////////////////////////
	//for (int i=0;i<_HMultiple;i++)
	//{
	//	BitBlt(memdc,0,i*585+5,5,585,dcMemorya,0,5,SRCCOPY);
	//}
	//BitBlt(memdc,0,(_HMultiple*585)+5,5,_HRemainder,dcMemorya,0,5,SRCCOPY);

	StretchBlt(memdc,0,5,5,_H,dcMemorya,0,5,5,picheight-10,SRCCOPY);
	//////////////////////////////////////////////////////////////////////////


	///////////////////////////////右边部分的长条//////////////////////////////
	//for (int i=0;i<_HMultiple;i++)
	//{
	//	BitBlt(memdc,dlgcx-5,i*585+5,5,585,dcMemorya,307-5,5,SRCCOPY);
	//}
	//BitBlt(memdc,dlgcx-5,(_HMultiple*585)+5,5,_HRemainder,dcMemorya,307-5,5,SRCCOPY);

	StretchBlt(memdc,dlgcx-5,5,5,_H,dcMemorya,picwidth-5,5,5,picheight-10,SRCCOPY);
	//////////////////////////////////////////////////////////////////////////


}


COLORREF DrawImages::MakeFrameBgImage(Bitmap * bt,char* guid,CString name,char* mpath)
{
	int w=bt->GetWidth();
	int h=bt->GetHeight();


	HDC dcMemorya=CreateCompatibleDC(GetDC(0));
	HBITMAP hBitmap;
	bt->GetHBITMAP(NULL,&hBitmap);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(dcMemorya, hBitmap);


	long r = 0, g = 0, b = 0;
	for(int i = 0; i < w; i++)                   
	{
		for(int j = 0; j < h; j++)
		{
			COLORREF pixelColor=GetPixel(dcMemorya,i,j);
			r += BYTE(GetRValue(pixelColor));
			g += BYTE(GetGValue(pixelColor));
			b += BYTE(GetBValue(pixelColor));
		}
	}
	int n = w  * h;
	INT MAKSW=50;
	COLORREF m_clrCustomBK = RGB(r / n, g / n, b / n);
	int alpha = 255;
	for (UINT row = w-MAKSW; row<=w; row++)
	{
		alpha  = alpha - 5;
		if(alpha<0)
		{
			alpha = 0;
		}
		for (UINT col = 0; col < h; col+=1)
		{
			COLORREF pixelColor=GetPixel(dcMemorya,row,col);
			r = BYTE(GetRValue(pixelColor));
			g = BYTE(GetGValue(pixelColor));
			b = BYTE(GetBValue(pixelColor));
			bt->SetPixel(row, col, Color(alpha, r, g, b));
		}
	}

	alpha = 255;
	for (UINT col = h-MAKSW; col<=h; col++)
	{
		alpha  = alpha - 5;
		if(alpha<0)
		{
			alpha = 0;
		}
		for (UINT row = 0; row <= w-MAKSW; row++)
		{
			COLORREF pixelColor=GetPixel(dcMemorya,row,col);
			r = BYTE(GetRValue(pixelColor));
			g = BYTE(GetGValue(pixelColor));
			b = BYTE(GetBValue(pixelColor));
			bt->SetPixel(row, col, Color(alpha, r, g, b));
		}
	}



	Color newcolor;
	newcolor.SetFromCOLORREF(m_clrCustomBK);
	int R=newcolor.GetR();
	int G=newcolor.GetG();
	int B=newcolor.GetB();
	LinearGradientBrush *linGrBrushH=new LinearGradientBrush(Rect(0,0,MAKSW,h),Color(0,R, G, B),Color(255,R, G, B),LinearGradientModeHorizontal);//右边的遮罩
	LinearGradientBrush *linGrBrushW=new LinearGradientBrush(Rect(0,0,w,MAKSW),Color(0,R, G, B),Color(255,R, G, B),LinearGradientModeVertical);//下边的遮罩


	Bitmap *tempbitmap_w=new Bitmap(w,MAKSW);//下边的遮罩
	Bitmap *tempbitmap_h=new Bitmap(MAKSW,h);//右边的遮罩



	Graphics *graphicsW=new Graphics(tempbitmap_w);
	graphicsW->FillRectangle(linGrBrushW, Rect(0, 0, w, MAKSW));
	delete graphicsW;
	Graphics *graphicsH=new Graphics(tempbitmap_h);
	graphicsH->FillRectangle(linGrBrushH, Rect(0, 0, MAKSW, h));
	delete graphicsH;
	delete linGrBrushH;
	delete linGrBrushW;


	SolidBrush *argbBrush=new SolidBrush(newcolor);
	Bitmap * nbt=new Bitmap(w,h);
	Graphics *graphics=new Graphics(nbt);
	graphics->FillRectangle(argbBrush, Rect(0, 0, nbt->GetWidth(), nbt->GetHeight()));
	graphics->DrawImage(bt,0,0,0,0,w,h,(Unit)2);

	graphics->DrawImage(bt, 0,0,0,0,w,h,(Unit)2);
	graphics->DrawImage(tempbitmap_h, Rect(w-MAKSW,0,MAKSW,h));
	graphics->DrawImage(tempbitmap_w, Rect(0,h-MAKSW,w,MAKSW));





	CString filename;
	CLSID  encoderClsid;
	//SYSTEMTIME timeDest;
	//GetLocalTime(&timeDest);
	
	GetEncoderClsid(L"image/bmp", &encoderClsid);
	CString P(guid);
	CString M(mpath);
	filename.Format(L"%s\\skin\\%s\\%s.bmp",M,P,name);
	int x = nbt->Save(filename,&encoderClsid,NULL);

	//delete graphicsBT;
	delete graphics;
	delete argbBrush;
	delete tempbitmap_h;
	delete tempbitmap_w;
	return m_clrCustomBK;

}

int DrawImages::GetEncoderClsid(const WCHAR *format, CLSID *pClsid)
{
	UINT num   =   0;// number   of   image   encoders
	UINT size   =   0;// size   of   the   image   encoder   array   in   bytes
	ImageCodecInfo *pImageCodecInfo = NULL;
	GetImageEncodersSize(&num,&size);
	if(size == 0)
		return -1;// Failure
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;// Failure
	GetImageEncoders(num,size,pImageCodecInfo);
	for(UINT j = 0; j < num; ++j)
	{
		if(wcscmp(pImageCodecInfo[j].MimeType,format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;// Success
		}
	}
	free(pImageCodecInfo);
	return -1;// Failure
}

void DrawImages::DrawFrameBgImage(HDC&memdc,Bitmap* bt)
{

}

void DrawImages::DrawFrameStatic(Bitmap * bt,HDC& memdc,int x,int y,int cx,int cy)
{
	HDC dcMemorya=CreateCompatibleDC(memdc);


	BLENDFUNCTION blendFunc32bpp;
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 255;

	HBITMAP hBitmap;
	bt->GetHBITMAP(NULL,&hBitmap);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(dcMemorya, hBitmap);


	void *lpBits;
	HDC stretchdc = CreateCompatibleDC(memdc);
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

	HBITMAP THBITMAP = CreateDIBSection(NULL, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&lpBits, NULL, (DWORD)0);
	HBITMAP OldTHBITMAP = (HBITMAP)::SelectObject(stretchdc, THBITMAP);

	StretchBlt(stretchdc,0,0,cx,cy,dcMemorya,0,0,bt->GetWidth(),bt->GetHeight(),SRCCOPY);

	AlphaBlend(memdc,x,y,cx,cy,stretchdc,0,0,cx,cy,blendFunc32bpp);
	//BitBlt(memdc,x,y,cx,cy,dcMemorya,0,0,SRCCOPY);


	::SelectObject (stretchdc,OldTHBITMAP);
	::DeleteObject(THBITMAP);
	::DeleteObject(OldTHBITMAP);
	::DeleteDC(stretchdc);

	::SelectObject (dcMemorya,hOldBitmap);
	::DeleteObject(hBitmap);
	::DeleteObject(hOldBitmap);
	::DeleteDC(dcMemorya);
}

void DrawImages::DrawFrameBg(HDC& memdc,int maskcolor,int bcx,int bcy,int a,Bitmap * bt,int BgSourceConstantAlpha)
{
	int w=bt->GetWidth();
	int h=bt->GetHeight();


	//HDC dcMemorya=CreateCompatibleDC(memdc);
	//HBITMAP hBitmap;
	//bt->GetHBITMAP(NULL,&hBitmap);
	//HBITMAP hOldBitmap = (HBITMAP)::SelectObject(dcMemorya, hBitmap);


	//long r = 0, g = 0, b = 0;
	//for(int i = 0; i < w; i++)                   
	//{
	//	for(int j = 0; j < h; j++)
	//	{
	//		COLORREF pixelColor=GetPixel(dcMemorya,i,j);
	//		r += BYTE(GetRValue(pixelColor));
	//		g += BYTE(GetGValue(pixelColor));
	//		b += BYTE(GetBValue(pixelColor));
	//	}
	//}
	//int n = w  * h;
	//COLORREF m_clrCustomBK = RGB(r / n, g / n, b / n);


	COLORREF m_clrCustomBK =maskcolor;
	RECT rect={0,0,bcx,bcy};
	HBRUSH brush=CreateSolidBrush(m_clrCustomBK);



	void *lpBits;
	HDC Tdc=CreateCompatibleDC(memdc);
	BITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biHeight = bcy;
	bi.bmiHeader.biWidth = bcx;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biCompression=BI_RGB;
	bi.bmiHeader.biXPelsPerMeter=0;
	bi.bmiHeader.biYPelsPerMeter=0;
	bi.bmiHeader.biClrUsed=0;
	bi.bmiHeader.biClrImportant=0;
	HBITMAP THBITMAP = CreateDIBSection(NULL, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&lpBits, NULL, (DWORD)0);
	HBITMAP _OTHBITMAP = (HBITMAP)SelectObject(Tdc, THBITMAP);
	
	//void *bglpBits;
	HBITMAP hBitmap;
	bt->GetHBITMAP(NULL,&hBitmap);
	HDC bgimagehdc=CreateCompatibleDC(memdc);
	//BITMAPINFO bgbi;
	//bgbi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//bgbi.bmiHeader.biBitCount = 32;
	//bgbi.bmiHeader.biHeight = bcy;
	//bgbi.bmiHeader.biWidth = bcx;
	//bgbi.bmiHeader.biPlanes = 1;
	//bgbi.bmiHeader.biCompression=BI_RGB;
	//bgbi.bmiHeader.biXPelsPerMeter=0;
	//bgbi.bmiHeader.biYPelsPerMeter=0;
	//bgbi.bmiHeader.biClrUsed=0;
	//bgbi.bmiHeader.biClrImportant=0;
	//HBITMAP BGIMAGEBITMAP = CreateDIBSection(NULL, (BITMAPINFO *)&bgbi, DIB_RGB_COLORS, (void **)&bglpBits, NULL, (DWORD)0);
	HBITMAP _0hBitmap = (HBITMAP)SelectObject(bgimagehdc, hBitmap);

	
	FillRect(Tdc,&rect,brush);


	
	for (int i=0;i<bcx*bcy;i++)
	{
		char * a=(char*)(&((UINT32*)lpBits)[i]);
		a[3]=255;
	}
	BitBlt(Tdc,0,0,w,h,bgimagehdc,0,0,SRCCOPY);
	if (a)
	{	
		BLENDFUNCTION blendFunc32bpp;
		blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
		blendFunc32bpp.BlendFlags = 0;
		blendFunc32bpp.BlendOp = AC_SRC_OVER;
		blendFunc32bpp.SourceConstantAlpha = BgSourceConstantAlpha;
		AlphaBlend(memdc,0,0,bcx,bcy,Tdc,0,0,bcx,bcy,blendFunc32bpp);
	}else{
		BitBlt(memdc,0,0,bcx,bcy,Tdc,0,0,SRCCOPY);
	}

	SelectObject(Tdc,_OTHBITMAP);
	DeleteObject(_OTHBITMAP);
	DeleteObject(THBITMAP);
	DeleteDC(Tdc);

	SelectObject(bgimagehdc,_0hBitmap);
	DeleteObject(_0hBitmap);
	DeleteObject(hBitmap);
	DeleteDC(bgimagehdc);

}


HFONT DrawImages::SetTextFont(HDC hdc, LPCTSTR face, int width, int height, int angle)
{
	HFONT hFont;
	hFont = CreateFont(
		height,      //字体的逻辑高度
		width,       //逻辑平均字符宽度
		angle,       //与水平线的角度
		0,           //基线方位角度
		FW_REGULAR,  //字形：常规
		FALSE,       //字形：斜体
		FALSE,       //字形：下划线
		FALSE,       //字形：粗体
		GB2312_CHARSET,          //字符集
		OUT_DEFAULT_PRECIS,      //输出精度
		CLIP_DEFAULT_PRECIS,     //剪截精度
		NONANTIALIASED_QUALITY,           //输出品质
		FIXED_PITCH | FF_MODERN, //倾斜度
		face                     //字体
		); 
	return hFont;
}

void DrawImages::DrawStaticImage(HWND m_hWnd,int x,int y,int cx,int cy,long width,long height,Bitmap* image,BYTE p)
{
	HDC hDC=::GetDC(m_hWnd);
	HDC hMemDC=::CreateCompatibleDC(hDC);
	BITMAPINFO bitmapinfo;
	bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfo.bmiHeader.biBitCount = 32;
	bitmapinfo.bmiHeader.biHeight = height;
	bitmapinfo.bmiHeader.biWidth = width;
	bitmapinfo.bmiHeader.biPlanes = 1;
	bitmapinfo.bmiHeader.biCompression=BI_RGB;
	bitmapinfo.bmiHeader.biXPelsPerMeter=0;
	bitmapinfo.bmiHeader.biYPelsPerMeter=0;
	bitmapinfo.bmiHeader.biClrUsed=0;
	bitmapinfo.bmiHeader.biClrImportant=0;
	bitmapinfo.bmiHeader.biSizeImage = bitmapinfo.bmiHeader.biWidth * bitmapinfo.bmiHeader.biHeight * bitmapinfo.bmiHeader.biBitCount / 8;
	HBITMAP hBitmap=::CreateDIBSection (hMemDC,&bitmapinfo, 0,NULL, 0, 0);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject (hMemDC,hBitmap);
	Graphics graphics(hMemDC);
	/*Image image(filename);
	//RectF destRect(0, 0, width, height);

	BlurParams myBlurParams;
	myBlurParams.expandEdge = TRUE;
	myBlurParams.radius = 3;

	Blur myBlur;
	myBlur.SetParameters(&myBlurParams);
*/

	graphics.DrawImage(image,x,y,cx,cy,width,height,(Unit)2);
	CPoint DestPt(0,0);
	CSize psize(width,height);
	BLENDFUNCTION blendFunc32bpp;
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = p;
	::UpdateLayeredWindow(m_hWnd,hDC,NULL,&psize,hMemDC,&DestPt,0,&blendFunc32bpp,ULW_ALPHA);	

}

//void DrawImages::DrawFourCorner(Bitmap* bt,HDC& memdc)
//{
	//HDC dcMemorya=CreateCompatibleDC(memdc);
	//void *lpBits;
	//BITMAPINFO bi;
	//bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//bi.bmiHeader.biBitCount = 32;
	//bi.bmiHeader.biHeight = 595;
	//bi.bmiHeader.biWidth = 307;
	//bi.bmiHeader.biPlanes = 1;
	//bi.bmiHeader.biCompression=BI_RGB;
	//bi.bmiHeader.biXPelsPerMeter=0;
	//bi.bmiHeader.biYPelsPerMeter=0;
	//bi.bmiHeader.biClrUsed=0;
	//bi.bmiHeader.biClrImportant=0;
	//HBITMAP hBitmap = CreateDIBSection(NULL, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&lpBits, NULL, (DWORD)0);
	//SelectObject(dcMemorya, hBitmap);

	//BitBlt(memdc,0,0)



//}

void DrawImages::DrawControl2(Bitmap* bt,HDC & memdc,int x,int y,int cx,int cy,int sx,int sy)
{
	HDC dcMemorya=CreateCompatibleDC(memdc);

	//BITMAPINFO bi;
	//bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//bi.bmiHeader.biBitCount = 32;
	//bi.bmiHeader.biHeight = 595;
	//bi.bmiHeader.biWidth = 307;
	//bi.bmiHeader.biPlanes = 1;
	//bi.bmiHeader.biCompression=BI_RGB;
	//bi.bmiHeader.biXPelsPerMeter=0;
	//bi.bmiHeader.biYPelsPerMeter=0;
	//bi.bmiHeader.biClrUsed=0;
	//bi.bmiHeader.biClrImportant=0;

	BLENDFUNCTION blendFunc32bpp;
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 255;

	HBITMAP hBitmap;
	bt->GetHBITMAP(NULL,&hBitmap);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(dcMemorya, hBitmap);

	AlphaBlend(memdc,x,y,cx,cy,dcMemorya,sx,sy,cx,cy,blendFunc32bpp);
	//BitBlt(memdc,x,y,cx,cy,dcMemorya,0,0,SRCCOPY);


	::SelectObject (dcMemorya,hOldBitmap);
	::DeleteObject(hBitmap);
	::DeleteObject(hOldBitmap);
	::DeleteDC(dcMemorya);
}

void DrawImages::AlphaDrawControl2(HDC bt,HDC & memdc,int x,int y,int cx,int cy,int sx,int sy)
{
	HDC dcMemorya=CreateCompatibleDC(memdc);

	//BITMAPINFO bi;
	//bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//bi.bmiHeader.biBitCount = 32;
	//bi.bmiHeader.biHeight = 595;
	//bi.bmiHeader.biWidth = 307;
	//bi.bmiHeader.biPlanes = 1;
	//bi.bmiHeader.biCompression=BI_RGB;
	//bi.bmiHeader.biXPelsPerMeter=0;
	//bi.bmiHeader.biYPelsPerMeter=0;
	//bi.bmiHeader.biClrUsed=0;
	//bi.bmiHeader.biClrImportant=0;

	BLENDFUNCTION blendFunc32bpp;
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 255;

	//HBITMAP hBitmap;
	//bt->GetHBITMAP(NULL,&hBitmap);
	//HBITMAP hOldBitmap = (HBITMAP)::SelectObject(dcMemorya, hBitmap);

	AlphaBlend(memdc,x,y,cx,cy,bt,sx,sy,cx,cy,blendFunc32bpp);
	//BitBlt(memdc,x,y,cx,cy,dcMemorya,0,0,SRCCOPY);


	//::SelectObject (dcMemorya,hOldBitmap);
	//::DeleteObject(hBitmap);
	//::DeleteObject(hOldBitmap);
	::DeleteDC(dcMemorya);
}

void DrawImages::BitDrawStretch(Bitmap * bt,HDC & memdc,int x,int y,int width,int height,int sx,int sy,int scx,int scy)
{
	HDC dcMemorya=CreateCompatibleDC(memdc);


	HBITMAP hBitmap;
	bt->GetHBITMAP(NULL,&hBitmap);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(dcMemorya, hBitmap);
	HDC TempControl = CreateCompatibleDC(memdc);
	void *OutPutlpBits;
	BITMAPINFO OutPutbi;
	OutPutbi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	OutPutbi.bmiHeader.biBitCount = 32;
	OutPutbi.bmiHeader.biHeight = height;
	OutPutbi.bmiHeader.biWidth = width;
	OutPutbi.bmiHeader.biPlanes = 1;
	OutPutbi.bmiHeader.biCompression=BI_RGB;
	OutPutbi.bmiHeader.biXPelsPerMeter=0;
	OutPutbi.bmiHeader.biYPelsPerMeter=0;
	OutPutbi.bmiHeader.biClrUsed=0;
	OutPutbi.bmiHeader.biClrImportant=0;


	HBITMAP TempBitmap = CreateDIBSection(NULL, (BITMAPINFO *)&OutPutbi, DIB_RGB_COLORS, (void **)&OutPutlpBits, NULL, (DWORD)0);
	HBITMAP OldTempBitmap = (HBITMAP)::SelectObject(TempControl,TempBitmap);
	StretchBlt(memdc,x,y,width,height,dcMemorya,sx,sy,scx,scy,SRCCOPY);;

	::SelectObject (dcMemorya,hOldBitmap);
	::DeleteObject(hBitmap);
	::DeleteObject(hOldBitmap);
	::DeleteDC(dcMemorya);

	::SelectObject(TempControl,OldTempBitmap);
	::DeleteObject(TempBitmap);
	::DeleteObject(OldTempBitmap);
	::DeleteDC(TempControl);
}


void DrawImages::BitDrawStretchControl(Bitmap* bt,HDC & memdc,int x,int y,int cx,int cy,int drawtype)
{
   HDC dcMemorya=CreateCompatibleDC(memdc);
   HBITMAP hBitmap;
   bt->GetHBITMAP(NULL,&hBitmap);
   HBITMAP hOldBitmap = (HBITMAP)::SelectObject(dcMemorya, hBitmap);


   HDC TempControl = CreateCompatibleDC(memdc);
   void *OutPutlpBits;
   BITMAPINFO OutPutbi;
   OutPutbi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   OutPutbi.bmiHeader.biBitCount = 32;
   OutPutbi.bmiHeader.biHeight = cy;
   OutPutbi.bmiHeader.biWidth = cx;
   OutPutbi.bmiHeader.biPlanes = 1;
   OutPutbi.bmiHeader.biCompression=BI_RGB;
   OutPutbi.bmiHeader.biXPelsPerMeter=0;
   OutPutbi.bmiHeader.biYPelsPerMeter=0;
   OutPutbi.bmiHeader.biClrUsed=0;
   OutPutbi.bmiHeader.biClrImportant=0;


   HBITMAP TempBitmap = CreateDIBSection(NULL, (BITMAPINFO *)&OutPutbi, DIB_RGB_COLORS, (void **)&OutPutlpBits, NULL, (DWORD)0);
   HBITMAP OldTempBitmap = (HBITMAP)::SelectObject(TempControl,TempBitmap);

   StretchBlt(TempControl,0,0,cx,cy,dcMemorya,0,0,bt->GetWidth(),bt->GetHeight(),SRCCOPY);


   if (drawtype==1)
   {
	   BLENDFUNCTION blendFunc32bpp;
	   blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	   blendFunc32bpp.BlendFlags = 0;
	   blendFunc32bpp.BlendOp = AC_SRC_OVER;
	   blendFunc32bpp.SourceConstantAlpha = 255;

	   AlphaBlend(memdc,x,y,cx,cy,TempControl,0,0,cx,cy,blendFunc32bpp);
   }
   else{

	   BitBlt(memdc,x,y,cx,cy,TempControl,0,0,SRCCOPY);
   }
   ::SelectObject (dcMemorya,hOldBitmap);
   ::DeleteObject(hBitmap);
   ::DeleteObject(hOldBitmap);
   ::DeleteDC(dcMemorya);



   ::SelectObject(TempControl,OldTempBitmap);
   ::DeleteObject(TempBitmap);
   ::DeleteObject(OldTempBitmap);
   ::DeleteDC(TempControl);

}
void DrawImages::BitDrawStretchButton(Bitmap* bt,HDC & memdc,int x,int y,int leftw,int rightw,int width,int cx,int cy,int srcx,int srcy,int textx,int texty,WCHAR * buttonstr,COLORREF textcolor,int pint)
{
	HDC dcMemorya=CreateCompatibleDC(memdc);


	HBITMAP hBitmap;
	bt->GetHBITMAP(NULL,&hBitmap);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(dcMemorya, hBitmap);



	
	HDC TempControl = CreateCompatibleDC(memdc);
	void *OutPutlpBits;
	BITMAPINFO OutPutbi;
	OutPutbi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	OutPutbi.bmiHeader.biBitCount = 32;
	OutPutbi.bmiHeader.biHeight = cy;
	OutPutbi.bmiHeader.biWidth = width;
	OutPutbi.bmiHeader.biPlanes = 1;
	OutPutbi.bmiHeader.biCompression=BI_RGB;
	OutPutbi.bmiHeader.biXPelsPerMeter=0;
	OutPutbi.bmiHeader.biYPelsPerMeter=0;
	OutPutbi.bmiHeader.biClrUsed=0;
	OutPutbi.bmiHeader.biClrImportant=0;


	HBITMAP TempBitmap = CreateDIBSection(NULL, (BITMAPINFO *)&OutPutbi, DIB_RGB_COLORS, (void **)&OutPutlpBits, NULL, (DWORD)0);
	HBITMAP OldTempBitmap = (HBITMAP)::SelectObject(TempControl,TempBitmap);

	//中间部分的宽度
	int _width = width -leftw-rightw;
	//左部分
	BitBlt(TempControl,0,0,leftw,cy,dcMemorya,srcx,srcy,SRCCOPY);
	//拉伸中间部分
	StretchBlt(TempControl,leftw,0,_width,cy,dcMemorya,srcx+leftw,srcy,cx-leftw-rightw,cy,SRCCOPY);
	//右部分
	BitBlt(TempControl,_width+leftw,0,rightw,cy,dcMemorya,srcx+cx-rightw,srcy,SRCCOPY);

	HFONT hFont = SetTextFont(TempControl, (LPCTSTR)"宋体", 0, 12, 0); //创建字体
	HFONT _OhFont =(HFONT) SelectObject(TempControl, hFont);                         //选择新字体
	SetTextColor(TempControl,textcolor);
	SetBkMode(TempControl,TRANSPARENT);
	TextOut(TempControl,textx,texty,buttonstr,wcslen(buttonstr));

	for (int i=0;i<cy*width;i++)
	{
		char * a=(char*)(&((UINT32*)OutPutlpBits)[i]);
		if ((a[0]!=0 && a[1]!=0 && a[2]!=1) || (a[0]==0 && a[1]==0 && a[2]==0))
		{
			continue;
		}
		a[3]=255;
	}

	if (pint==1)
	{
		BLENDFUNCTION blendFunc32bpp;
		blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
		blendFunc32bpp.BlendFlags = 0;
		blendFunc32bpp.BlendOp = AC_SRC_OVER;
		blendFunc32bpp.SourceConstantAlpha = 255;

		AlphaBlend(memdc,x,y,width,cy,TempControl,0,0,width,cy,blendFunc32bpp);
	}
	else{
		
		BitBlt(memdc,x,y,width,cy,TempControl,0,0,SRCCOPY);
	}


	::SelectObject (dcMemorya,hOldBitmap);
	::DeleteObject(hBitmap);
	::DeleteObject(hOldBitmap);
	::DeleteDC(dcMemorya);



	::SelectObject(TempControl,OldTempBitmap);
	::DeleteObject(TempBitmap);
	::DeleteObject(OldTempBitmap);
	::DeleteDC(TempControl);

	::DeleteObject(hFont);
	::DeleteObject(_OhFont);
}


void DrawImages::BitDrawControl(Bitmap* bt,HDC & memdc,int x,int y,int cx,int cy,int sx,int sy)
{
	HDC dcMemorya=CreateCompatibleDC(memdc);
	
	//BITMAPINFO bi;
	//bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//bi.bmiHeader.biBitCount = 32;
	//bi.bmiHeader.biHeight = 595;
	//bi.bmiHeader.biWidth = 307;
	//bi.bmiHeader.biPlanes = 1;
	//bi.bmiHeader.biCompression=BI_RGB;
	//bi.bmiHeader.biXPelsPerMeter=0;
	//bi.bmiHeader.biYPelsPerMeter=0;
	//bi.bmiHeader.biClrUsed=0;
	//bi.bmiHeader.biClrImportant=0;
	
	BLENDFUNCTION blendFunc32bpp;
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 255;

	HBITMAP hBitmap;
	bt->GetHBITMAP(NULL,&hBitmap);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(dcMemorya, hBitmap);

	/*AlphaBlend(memdc,x,y,cx,cy,dcMemorya,0,0,cx,cy,blendFunc32bpp);*/
	


	//HFONT hFont = SetTextFont(dcMemorya, (LPCTSTR)"宋体", 0, 12, 0); //创建字体
	//HFONT _OhFont =(HFONT) SelectObject(dcMemorya, hFont);                         //选择新字体
	//SetTextColor(dcMemorya,RGB(0,0,0));
	//SetBkMode(dcMemorya,TRANSPARENT);
	//TextOut(dcMemorya,5,5,_T("测试"),2);
		BitBlt(memdc,x,y,cx,cy,dcMemorya,sx,sy,SRCCOPY);

	::SelectObject (dcMemorya,hOldBitmap);
	::DeleteObject(hBitmap);
	::DeleteObject(hOldBitmap);
	::DeleteDC(dcMemorya);
}

void DrawImages::LoadResImage(WCHAR* filename,WCHAR * streamname,Bitmap * &pImage)
{
	
	IStream* pIStream = NULL;
	HRESULT hr;
	CFile tempfile;
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	wchar_t p[MAX_PATH];
	wcscpy(p,szFilePath);
	_tcsrchr(p, _T('\\'))[1]=0;
	CString cs;
	cs.Format(_T("%s%s"),p,filename);

	tempfile.Open(cs,CFile::modeRead | CFile::shareDenyNone);
	//MessageBox(NULL,cs,NULL,NULL);
	DWORD filesize=tempfile.GetLength();
	
	HGLOBAL hMem = ::GlobalAlloc(GMEM_FIXED,filesize);
	
	LPVOID lpBuf = ::GlobalLock(hMem);   //锁定内存
		
	tempfile.Read(lpBuf,filesize);   //读取图片到全局内存当中

	tempfile.Close();
	hr = CreateStreamOnHGlobal(hMem,TRUE,&pIStream); 
	pImage=Bitmap::FromStream(pIStream);
	//pIStorage->Release();
	::GlobalUnlock(hMem);   //解锁内存
	pIStream->Release();
}
void DrawImages::ClearColor(HDC & cdc,Bitmap bt)
{
	Graphics *g=Graphics::FromHDC(cdc);
	g->DrawImage(&bt,0,0,0,0,307,596,(Unit)2);
}

int  DrawImages::gaussBlur(int *data, int width ,int height ,double sigma ,int radius)   
{   
	double *gaussMatrix, gaussSum = 0.0, _2sigma2 = 2 * sigma * sigma;   
	int x, y, xx, yy, xxx, yyy;   
	double *pdbl, a, r, g, b, d;   
	unsigned char *bbb, *pout, *poutb;   
	poutb =(unsigned char*)malloc(width*height*4);   
	pout = poutb;
	if (!pout) return 0;   
	gaussMatrix = (double *)malloc( (radius * 2 + 1) * (radius * 2 + 1) * sizeof(double));   
	pdbl = gaussMatrix;
	if (!gaussMatrix) {   
		free(pout);   
		return 0;   
	}   
	for (y = -radius; y <= radius; y++) {   
		for (x = -radius; x <= radius; x++) {   
			a = exp(-(double)(x * x + y * y) / _2sigma2);   
			*pdbl++ = a;   
			gaussSum += a;   
		}   
	}   
	pdbl = gaussMatrix;   
	for (y = -radius; y <= radius; y++) {   
		for (x = -radius; x <= radius; x++) {   
			*pdbl++ /= gaussSum;   
		}   
	}   
	for (y = 0; y < height; y++) {   
		for (x = 0; x < width; x++) {   
			a = r = g = b = 0.0;   
			pdbl = gaussMatrix;   
			for (yy = -radius; yy <= radius; yy++) {   
				yyy = y + yy;   
				if (yyy >= 0 && yyy < height) {   
					for (xx = -radius; xx <= radius; xx++) {   
						xxx = x + xx;   
						if (xxx >= 0 && xxx < width) {   
							bbb = (unsigned char *)&data[xxx + yyy * width];   
							d = *pdbl;   
							b += d * bbb[0];   
							g += d * bbb[1];   
							r += d * bbb[2];   
							a += d * bbb[3];   
						}   
						pdbl++;   
					}   
				} else {   
					pdbl += (radius * 2 + 1);   
				}   
			}   
			*pout++ = (unsigned char)b;   
			*pout++ = (unsigned char)g;   
			*pout++ = (unsigned char)r;   
			*pout++ = (unsigned char)a;   
		}   
	}   
	memcpy(data, poutb, width * height * 4);   
	free(gaussMatrix);   
	free(poutb);   
	return 1;   
}  
