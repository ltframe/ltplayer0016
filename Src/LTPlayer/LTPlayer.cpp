// LTPlayer.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "LTPlayer.h"
#include "LTPlayerDlg.h"
#include "ControlPanelDlg.h"
#include "CWMPPlayer4.h"
#include "CWMPSettings.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ULONG_PTR m_gdiplusToken;
// CLTPlayerApp

BEGIN_MESSAGE_MAP(CLTPlayerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CLTPlayerApp 构造

CLTPlayerApp::CLTPlayerApp():DlgHigh(526),DlgWidth(303)
{
	//AfxMessageBox(_T("aaaaaaaaa"));// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CLTPlayerApp 对象

CLTPlayerApp theApp;


// CLTPlayerApp 初始化

BOOL CLTPlayerApp::InitInstance()
{	
	
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	startfilename = cmdInfo.m_strFileName;

	OSVERSIONINFO osvi;
	BOOL bIsWindowsXPorLater;

	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&osvi);
	if (osvi.dwMajorVersion<5)
	{
		MessageBox(NULL,_T("您所使用操作系统版本过低"),_T("提示"),MB_OK);
		return FALSE;	
	}
	myglobalhandle=::CreateMutex(NULL,FALSE,_T(ISSTARTAPP));
	{
		if(GetLastError()==ERROR_ALREADY_EXISTS)	
		{
			//SendMessage(WM_STARTRUNOPENFILE_MESSAGE)
			HWND   hWnd  = FindWindow(NULL,_T("静静聆听播放器")); 
			if (GetProp(hWnd,CString(ISSTARTAPP))==(HANDLE)1)
			{
				COPYDATASTRUCT cpd;                     // 给COPYDATASTRUCT布局赋值
				cpd.dwData = 0;
				cpd.cbData = (startfilename.GetLength()+1)*sizeof(CString);
				cpd.lpData =(void*)startfilename.GetBuffer(cpd.cbData);
				SendMessage(hWnd,WM_COPYDATA,NULL,(LPARAM)&cpd);
			}
			return FALSE;	
		}
	}

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));



	ControlPanelDlg dlg;
	m_pMainWnd = &dlg;

#ifdef _OPENCONSOLE
	if (!AllocConsole())
	{}
#endif


	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

int CLTPlayerApp::ExitInstance() 
{
	//	deallocate console
#ifdef _OPENCONSOLE
	if (!FreeConsole())
	{}
#endif
	CloseHandle(myglobalhandle);

	return CWinApp::ExitInstance();
}
