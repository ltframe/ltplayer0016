#pragma once

class AFX_EXT_CLASS DrawImages
{
public:
	DrawImages(void);
	~DrawImages(void);
	void DrawMainBg(HWND m_hWnd,long width,long height,Bitmap* image,BYTE p=255);
	void DrawStaticImage(HWND m_hWnd,int x,int y,int cx,int cy,long width,long height,Bitmap* image,BYTE p=255);
	void LoadResImage(WCHAR* filename,WCHAR * streamname,Bitmap * &pImage);
	void DrawMainBg(HDC &hdc,long width,long height,Bitmap* image);
	void ClearColor(HDC & cdc,Bitmap bt);
	int  gaussBlur(int *data, int width ,int height ,double sigma ,int radius);   
	void BitDrawControl(Bitmap* bt,HDC & memdc,int x,int y,int cx,int cy,int sx,int sy);
	void DrawControl2(Bitmap* bt,HDC & memdc,int x,int y,int cx,int cy,int sx,int sy);
	void AlphaDrawControl2(HDC bt,HDC & memdc,int x,int y,int cx,int cy,int sx,int sy);
	void DrawFrameBg(HDC& memdc,int maskcolor,int bcx,int bcy,int a,Bitmap*,int DrawFrameBg=255);
	void DrawFrameBg2(HDC& memdc,Bitmap * bt,int bcx,int bcy);
	HFONT SetTextFont(HDC hdc, LPCTSTR face, int width, int height, int angle);
	void DrawFrameBorder(HDC& memdc,Bitmap * bt,int dlgcx,int dlgcy);
	int GetEncoderClsid(const WCHAR *format, CLSID *pClsid);
	COLORREF MakeFrameBgImage(Bitmap * bt,char* guid,CString name,char* mpath);
	void DrawFrameBgImage(HDC&memdc,Bitmap* bt);
	void BitDrawStretchButton(Bitmap* bt,HDC & memdc,int x,int y,int leftw,int rightw,int width,int cx,int cy,int srcx,int srcy,int textx,int texty,WCHAR * buttonstr,COLORREF textcolor,int pint =1);
	void BitDrawStretch(Bitmap * bt,HDC & memdc,int x,int y,int width,int height,int sx,int sy,int scx,int scy);
	void BitDrawStretchControl(Bitmap* bt,HDC & memdc,int x,int y,int cx,int cy,int drawtype);
	void DrawFrameStatic(Bitmap * bt,HDC& memdc,int x,int y,int cx,int cy);
};
