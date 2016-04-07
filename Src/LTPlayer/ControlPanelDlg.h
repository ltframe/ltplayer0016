#pragma once
#include "ConstValues.h"
#include "ControlPanelDlg.h"
#include "UIInterface.h"
#include "UIButton.h"
#include "UIButtonEx.h"
#include "UISlider.h"
#include "UIList.h"
#include "UILable.h"
#include "UICanvar.h"
#include "UIStatic.h"
#include "ControlClass.h"
#include "ControlEvent.h"
#include "bass.h"
#include "MyPropertySheet.h"
#include "AboutMe.h"
#include "UiSetting.h"
#include "MusicSetting.h"
#include "FileJoin.h"
#include "SoftUpdate.h"
#include "LTPlayer.h"
#include <wchar.h>
// ControlPanelDlg 对话框
#define MUSIC_TIMER 1
#define RADIO_TIMER 2
#define MUSIC_TIMER_NAME_ROLL 3
#define PLAYERCONTROL_BETWEEN_WIDTH 12
#define VOLUMESLIDER_RIGHT_CX 14
#define VOLUMESLIDER_LEFT_CX 5
#define POSITIONSLIDER_LR_CX  61
#define SETTING_ONELAST_CX 60
#define SETTINGHALF_CX 12
#define SETTING_X 48
class ControlPanelDlg : public CDialog,public IControlEventS
{
	DECLARE_DYNAMIC(ControlPanelDlg)
private:	
	void SetWindowTextFunc(CString str);
public:
	int currenttransparent;
	int musicnamelablerollflag;
	int playstatus;
	int volumstatus;
	wchar_t *currentfilename;
	wchar_t * currentshowfilename;
	bool islooplist;
	int currentmusiclistindex;
	AboutMe aboutmedia;
	UiSetting uisettingdia;
	FileJoin filejoindia;
	MusicSetting musicsettingdia;
	SoftUpdate softupdatedia;
	CString APPPATH;
	UICanvar *canvar;
	ControlPanelDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ControlPanelDlg();
	bool DlgStartEnd;
	UIButton *playbutton,*nextbutton,*perbutton,*volumeico,*closebutton,*minbutton,*addbutton,*listxhbutton,*setbutton,*optionsbutton,*skinbutton;
	UISlider *positionslider,*volumeslider;
	UIList *musiclist;
	UIList *networkmusiclist;
	UILable *musicnamelable,*musictimelable,*musictimeclable;
	UIStatic *musiclogo;
	ControlClass  *controlclass;
	bool m_bMouseTracking;
	Image* image;
	DrawImages Drawimage;
	CString CurrentControlClassName;
	ControlEvent *controlevent;
	HDC cdc;
	CBitmap bmp;
	CDC dcMemory;
	Bitmap InitBitmap;
	CPoint   currentpoint;
	Bitmap *PrintDCBitmap;
	int percontrolnameid;
    RECT CurrentRect;
	CPoint DestPt;
	BLENDFUNCTION blendFunc32bpp;
	SolidBrush blackBrush;
	ImageAttributes imAtt;
	CArray<CPoint,CPoint&> *cpointarray;
	HFX musicfx[10];
	int MAINBG_WIDTH;
	int MAINBG_HEIGHT;
	COLORREF maskcolor;
	Bitmap * bgbitmap;
// 对话框数据
	enum { IDD = IDD_CONTROLPANEL };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	void AddControlToArray(LPVOID t);
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	 afx_msg void OnMouseLeave();
	afx_msg void OnPaint();
	afx_msg BOOL OnCopyData(CWnd* pWnd,COPYDATASTRUCT* pCopyDataStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnUserSelfMessageMusicTimes(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserSelfMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	OnUserSelfMessageMusicVoL(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserSelfMessageMusicName(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLayerPaintMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserSelfMessageNOTIFY(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserSelfMessageMusicPlay(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStartOpenFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT SetMusic3D(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT EnableBgAlpha(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetBgImg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetBgAlpha(WPARAM wParam, LPARAM lParam);
	void OnUserSelfMessageSetting();
	void OnUserSelfMessageWebSite();
	void OnUserSelfMessageClose();
    bool SetListContorEvent(UIListInfo,UIFileListInfo);
	bool SetSliderContorEvent(UISliderInfo);
	bool SetButtonContorEvent(UIButtonInfo info);
	void MusicPlay(wchar_t* currentfilename);
	void MusicPlay();
	//static VOID CALLBACK myTimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime);
	void MusicStop();
	void Add2MusicList(CString);
	//static UINT  MusicPlayLink(LPVOID pParam);
	void PlayeTimerStatus(double i,double s);
	void NextMusic();
	void PerMusic();
	//CString GetIniValue(LPCTSTR lpAppName ,LPCTSTR key) const;
	void OpenFileAndPlayer(CString  fname);
	void LoadMusicList();
	void LoadRadioList();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void AutoPlay();

	void UpdateMusicListCanvars();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
//	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	void ResetSpecificControlRect(int);
	int ResetPostitionSlider(int i=0);
	void ResetDoubleTab(int i=0);
	void ResetPlayRegion(int i = 0);
	void ResetControlRegion(int i = 0);
	void ResetLable(INT);
	void ResetMucisNameLable(int offsetint);
	void ResetMMCRegion(int offsetint);
	void ResetControlsXY(int k);
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

