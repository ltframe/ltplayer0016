// LT_OCX.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "LT_OCX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CLT_OCXApp

BEGIN_MESSAGE_MAP(CLT_OCXApp, CWinApp)
END_MESSAGE_MAP()


// CLT_OCXApp 构造

CLT_OCXApp::CLT_OCXApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

CLT_OCXApp::~CLT_OCXApp()
{
	int i=0;
}
// 唯一的一个 CLT_OCXApp 对象

CLT_OCXApp theApp;


// CLT_OCXApp 初始化

BOOL CLT_OCXApp::InitInstance()
{
	CWinApp::InitInstance();
	
	CoInitialize(0);

	return TRUE;
}

void CLT_OCXApp::ShowAd()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CoInitialize(0);
	AdHtml *ad=new AdHtml;
	ad->Create(IDD_DIALOG1);
	int   cx=GetSystemMetrics(SM_CXSCREEN); 
	int   cy=GetSystemMetrics(SM_CYSCREEN); 
	RECT trect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &trect, 0);
	CRect   rectWindow; 
	ad->GetWindowRect(&rectWindow); 
	int   w=rectWindow.Width(); 
	int   h=rectWindow.Height(); 
    rectWindow.left=cx-w; 
	rectWindow.top=cy-h; 
	rectWindow.right=cx; 
	rectWindow.bottom=trect.bottom; 
	ad->MoveWindow(rectWindow,TRUE);
	ad->ShowWindow(SW_SHOW);

	MSG msg; 
	BOOL bRet=TRUE;

	while(GetMessage( &msg, NULL, 0, 0 ))
	{ 
		if (!ad->IsWindowVisible())
		{
			ad->DestroyWindow();
			delete ad;
			break;
		}
		else
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
	}
}