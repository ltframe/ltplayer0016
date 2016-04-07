#pragma once
#include "UIButton.h"
#include "UIList.h"
#include "bass.h"
#include "IControlEvent.h"
#include "MusicUtils.h"
#include "resource.h"



class  ControlEvent : public IControlEventS
{



public:
		int volumstatus;
		char *currentfilename;
		UINT_PTR timer1;
		
	float CurrentVOLPostion;
	HWND parenthwnd;
	HWND per_parenthwnd;
	ControlEvent(CArray<LPVOID,LPVOID&> *ArrayList,HWND hwnd=NULL);
	CArray<LPVOID,LPVOID&> * TArrayList;
	~ControlEvent(void);
	void MusicPlay(char * filename);
	void MusicPlay();
	void MusicStop(bool post);
	void MusicPause();
	void SetContorEvent(CString eventname,LPVOID,...);
	void SetMusicVolume(float volume,HSTREAM);
	void SetMusicPosition(double seconds,HSTREAM);
	double GetMusicSeconds(QWORD len,HSTREAM);
	double GetMusicSeconds(HSTREAM m_stream);
	QWORD GetMusicLength(HSTREAM);
	static void PostUserMessage(HWND hwnd);
	static VOID CALLBACK myTimerProc(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime);
    void ShowNotifyIcon(HWND hwnd);	
	void DeleteNotifyIcon(HWND hwnd);
	void ShowPlayer(HWND parenthwnd,HWND per_parenthwnd,int type);
	void ShowPlayer();
	void ShowCMenu(CWnd *);
	void ClosePlayer();
	void CloseMusicVOL(HSTREAM,float);
	void AddFilesToList(UIList *ulist);
	void DbClickMusicPlay(CString);
};
