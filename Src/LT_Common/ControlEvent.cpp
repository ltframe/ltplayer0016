#include "StdAfx.h"
#include "ControlEvent.h"

ControlEvent::ControlEvent(HWND hwnd)
{
	BASS_Init(-1,44100,0,NULL,NULL);
}

ControlEvent::~ControlEvent(void)
{
}
 void ControlEvent::MusicPlay()
{
	char filesss[MAX_PATH]="E:\\music\\Nobody-Wonder Girls.mp3";
	HSTREAM str;
	//if (str=BASS_StreamCreateFile(FALSE,file,0,0,0)) {
	//	strc++;
	//	strs=(HSTREAM*)realloc((void*)strs,strc*sizeof(*strs));
	//	strs[strc-1]=str;
	//	STLM(LB_ADDSTRING,0,strrchr(file,'\\')+1);
	//} else
	//	Error("Can't open stream");
	CString musicfile(_T("E:\\music\\Avril Lavigne(°¬Þ±¶ù)-girlfriend.wma"));
	stream =BASS_StreamCreateFile(FALSE,filesss,0,0,0);
	BASS_ChannelPlay(stream,FALSE);
}
 UINT  ControlEvent::MusicPlayLink(LPVOID pParam)
{
ControlEvent t(NULL);
  t.MusicPlay();
  return TRUE;
}