#pragma once
#include "UIInterface.h"
#include "DrawImages.h"
#include "UIInfo.h"
#include "ControlClass.h"
class AFX_EXT_CLASS UIList : public IControl
{
public:
	UIList(WCHAR *img1,WCHAR *img2,WCHAR *img3);
	~UIList(void);
	int barhieght,showfilecount,filecount;
	bool allowdrag;
	int sliderbar_offset;//滚动条的偏移量
	int tandboffset;
	int sliderbarstart;//鼠标按下的时候当前SLIDERBAR的Y值
	bool isdowmsilder;
	Font myFont;
	DWORD m_dwFadeTick;
	int currentselected;
	StringFormat format;
	SolidBrush *blackBrush,*blackBrush1;
	CArray<FileListInfo,FileListInfo&> *filelistarray;
	CArray<FileListInfo,FileListInfo&> *filelistarrayTemp;
	UIListInfo Glistinfo;
	FileListInfo Gfileinfo;
	Bitmap * m_pSrcImage1;
	Bitmap * m_pSrcImage2;
	Bitmap * m_pSrcImage3;
	Bitmap * lastsliderbar;
    HDC bargraphics;
	int filestartindex;
	int fileitemoffset;
	RECT *listRectTmp;
	DrawImages Drawimage;
	void SetControl(Bitmap *bt,int);
	bool IMOUSEMOVE(HWND hwnd,IControl *ts,CPoint point);
	RECT IRECT();
	CString ICLASSNAME();
	CString ICLASSTYPE();
	void IPAINT(HDC&);
	void IPAINT2(HDC&);
	int IWIDTH();
	int IHIGH();
	void IHIDE();
	void ISHOW();
	Bitmap bt;
	bool IMOUSELEAVE(HWND,bool rp=true);
	bool ILBUTTONDOWN(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,bool&);
	bool ILBUTTONUP(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList);
	bool IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int i=0);
	bool ILBUTTONDBCLICK(HWND hwnd,CPoint point);
	void GetSliderBarHeight();
	bool DeleteList();
	int GetListCount();
	void SetFileIndex(HWND,int,int i=1);
	inline void SetListValue();
	void GetColorIndex(int index);
	void SetStepInt();
	void ResetSliderBarPos(CPoint);
};
