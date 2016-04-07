// MusicSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "LTPlayer.h"
#include "MusicSetting.h"
#include "AtlBase.h"
#include "AtlConv.h"
#include "ConstValues.h"
#include "MusicUtils.h"
// MusicSetting 对话框
#define  EM(A) affect.AddString(CString(A))
IMPLEMENT_DYNAMIC(MusicSetting, CPropertyPage)

MusicSetting::MusicSetting()
	: CPropertyPage(MusicSetting::IDD)
{

}

MusicSetting::~MusicSetting()
{
}

void MusicSetting::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO2, outdevice);
	DDX_Control(pDX, IDC_COMBO1, affect);
}


BEGIN_MESSAGE_MAP(MusicSetting, CPropertyPage)

	ON_CBN_SELCHANGE(IDC_COMBO1, &MusicSetting::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

void MusicSetting::OnOK()
{
	int a=affect.GetCurSel();
	wchar_t *st;
	st= (wchar_t*)malloc(_MAX_PATH);
	ZeroMemory(st,wcslen(st));
	_itow(a-1,st,10);
	free(st);

	////////////////////
	CButton* autostart = (CButton*)GetDlgItem(IDC_CHECK2);
	CButton* autoplay = (CButton*)GetDlgItem(IDC_CHECK1);
	if(autostart->GetCheck())
	{	
		/*MusicUtils::WriteConfigXml(_T("autostart"),MusicUtils::ConverI2W(1),"SetPlayerConfigValue");*/
		SetAutoStart(1);
	}else{
		/*	MusicUtils::WriteConfigXml(_T("autostart"),MusicUtils::ConverI2W(0),"SetPlayerConfigValue");*/
		SetAutoStart(0);
	}
	if(autoplay->GetCheck())
	{	
		MusicUtils::WriteConfigXml(_T("autoplay"),MusicUtils::ConverI2W(1),"SetPlayerConfigValue");
	}else{
		MusicUtils::WriteConfigXml(_T("autoplay"),MusicUtils::ConverI2W(0),"SetPlayerConfigValue");
	}
}

BOOL MusicSetting::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	CWnd *T1 = (CWnd*)GetDlgItem(IDC_STATIC);
	T1->ShowWindow(SW_HIDE);
	EM("原音");
	EM("流行音乐");
	EM("摇滚");
	EM("金属乐");
	EM("舞曲");
	EM("电子乐");
	affect.SetCurSel(0);

	CButton* autostart = (CButton*)GetDlgItem(IDC_CHECK2);
	CButton* autoplay = (CButton*)GetDlgItem(IDC_CHECK1);
	autostart->SetCheck(BST_CHECKED);
	autoplay->SetCheck(BST_CHECKED);

	DWORD BufferSize = 8192;
	char  szPath[_MAX_PATH];  
	HKEY hKey; 
	long lRet=RegOpenKeyEx( HKEY_LOCAL_MACHINE,TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run\\"), 0, KEY_ENUMERATE_SUB_KEYS|KEY_QUERY_VALUE|KEY_SET_VALUE, &hKey );
	if( lRet == ERROR_SUCCESS){
		if(RegQueryValueEx(hKey,TEXT("LTplayer"),NULL,NULL,(LPBYTE) szPath,&BufferSize)!=0)
		{
			autostart->SetCheck(BST_UNCHECKED);
		}
	}
	RegCloseKey(hKey); 

	if (_wtoi(MusicUtils::GetConfigXml(L"autoplay",L"0"))==0)
	{
		autoplay->SetCheck(BST_UNCHECKED);
	}
	return TRUE; 
}

// MusicSetting 消息处理程序


void MusicSetting::OnCbnSelchangeCombo1()
{
	int a=affect.GetCurSel();
	HWND   hWnd  = ::FindWindow(NULL,_T("静静聆听播放器")); 
	if (a==0 && GetProp(hWnd,CString(ISSTARTAPP))==(HANDLE)1)
	{
		::SendMessage(hWnd,WM_SETMUSIC3D_MESSAGE,1,a-1);
		return;
	}

	if (GetProp(hWnd,CString(ISSTARTAPP))==(HANDLE)1)
	{
		::SendMessage(hWnd,WM_SETMUSIC3D_MESSAGE,NULL,a-1);
	}
	
}


bool MusicSetting::GetAutoStart()
{
	return true;
}
void MusicSetting::SetAutoStart(int i)
{
	HKEY hKey;  
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	wchar_t p[MAX_PATH];
	wcscpy(p,szFilePath);
	_tcsrchr(p, _T('\\'))[1]=0;
	CString appname(szFilePath);
	CString strTemp=_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	if (!i)
	{
		long lRet=RegOpenKeyEx( HKEY_LOCAL_MACHINE,TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run\\"), 0, KEY_ENUMERATE_SUB_KEYS|KEY_QUERY_VALUE|KEY_SET_VALUE, &hKey );
		if( lRet == ERROR_SUCCESS){
		RegDeleteValue(hKey, _T("LTplayer"));
		}
		RegCloseKey(hKey);
		return;
	}


	RegCreateKey(HKEY_LOCAL_MACHINE,strTemp,&hKey);  
	RegSetValueExW(hKey,_T("LTplayer"),0,REG_SZ,(LPBYTE)appname.GetBuffer(),(appname.GetLength()+1)*sizeof(CString));
	RegCloseKey(hKey);  
}
