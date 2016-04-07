#pragma once
#include "UIInterface.h"
#include "UIConstValues.h"
#include "ControlClass.h"
#include "DrawImages.h"
#define NPCALINDEX  NeedPaintControlArrayList.GetAt(n) 
class AFX_EXT_CLASS UICanvar
{
private:
	ImageAttributes imAtt;
	CPoint DestPt;
	CSize psize;
	BLENDFUNCTION blendFunc32bpp;
	SolidBrush blackBrush;
	ControlClass  *controlclass;
	HWND GlobalHwnd;
	TRACKMOUSEEVENT tme;
	bool p_paint;
	RECT CurrentContolRect;
	HDC BgHDC;
	HDC FrameHDC;
	HWND hwndTT;
	
	HDC ContorlHDC;
	HDC OutPutHDC;
	
	DrawImages drawimages;
	//int otx;
	//int oty;
public:
	bool m_bMouseTracking;
	CArray<LPIControl,LPIControl&> ControlArrayList;
	CArray<RECT,RECT&> NeedPaintControlArrayList;
	CToolTipCtrl player_tips;
	int MAINBG_WIDTH;
	int MAINBG_HEIGHT;
	int ISDLGALPHA;
	BOOL needpaintall;//是否需要重绘整个界面
	COLORREF BGMASKCOLOR;
	Bitmap *BgSrcImg,*BgFrameImg,*BgPlayShadow,*BgListShadow;
	int BgSourceConstantAlpha;
	HBITMAP hBitmap,_OhBitmap,bbt,_Obbt,tempbmp,_Otempbmp;
public:
	UICanvar(HWND hwnd);
	~UICanvar(void);
	void AddControlToCanvar(LPIControl);
	void Paint(CPaintDC*,RECT);
	void OnInit(CClientDC *dc);
	void MouseMove(CPoint point);
	void MouseHover(CPoint point);
	void LButtonDown(CPoint point);
	void LButtonUp(CPoint point);
	void MouseLeave();
	void LBUTTONDBCLICK(HWND,CPoint);
	void UpdateCanvar(IControl*);
	void Add2PaintQueue(IControl*);
	void TEMP(Bitmap *TempPrintDCBitmap,int n);
	void AddMessageQueue(RECT rect);
	void HideControl(LPIControl);
	void ShowControl(LPIControl);
	void CreateToolTipForRect(HWND hwndParent,LPCTSTR); 
	void ResetCurrentRECT();
	bool IsOperationControl(CPoint);
	void OnSize(CClientDC *dc,int cx,int cy);
};

