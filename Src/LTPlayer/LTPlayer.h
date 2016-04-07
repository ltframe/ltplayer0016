// LTPlayer.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#define ISSTARTAPP "BA77185C-A5D5-406c-86FC-0974C8BA9337"
#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CLTPlayerApp:
// 有关此类的实现，请参阅 LTPlayer.cpp
//

class CLTPlayerApp : public CWinApp
{
public:
	CLTPlayerApp();
	HANDLE  myglobalhandle;
		CString startfilename;
// 重写
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
// 实现
	INT DlgWidth;	
	INT DlgHigh;
	DECLARE_MESSAGE_MAP()
};

extern CLTPlayerApp theApp;