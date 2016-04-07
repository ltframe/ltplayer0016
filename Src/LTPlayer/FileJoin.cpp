// FileJoin.cpp : 实现文件
//

#include "stdafx.h"
#include "LTPlayer.h"
#include "FileJoin.h"
#include "MusicUtils.h"


// FileJoin 对话框

IMPLEMENT_DYNAMIC(FileJoin, CPropertyPage)
LPBYTE CString_To_LPBYTE(CString str);
void  RegisterFileRelationA(CString strExt, CString strAppName, CString strAppKey, CString strDefaultIcon, CString strDescribe);
FileJoin::FileJoin()
	: CPropertyPage(FileJoin::IDD)
{

}

FileJoin::~FileJoin()
{
}

void FileJoin::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FileJoin, CPropertyPage)
END_MESSAGE_MAP()

void FileJoin::OnOK()
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	wchar_t p[MAX_PATH];
	wcscpy(p,szFilePath);
	 _tcsrchr(p, _T('\\'))[1]=0;
	HKEY hkey;
	CString strMP3("LTplayer.mp3");
	CString strWMA("LTplayer.wma");
	CString strFLAC("LTplayer.flac");
	CString strAPE("LTplayer.ape");
	CString strOGG("LTplayer.ogg");
	//CRegKey myKey(HKEY_CLASSES_ROOT);
	CButton* CMP3 = (CButton*)GetDlgItem(IDC_CHECK1);
	CButton* CWMA = (CButton*)GetDlgItem(IDC_CHECK2);
	CButton* CFLAC = (CButton*)GetDlgItem(IDC_CHECK3);
	CButton* CAPE = (CButton*)GetDlgItem(IDC_CHECK4);
	CButton* COGG = (CButton*)GetDlgItem(IDC_CHECK5);
	CString assfilelist("");
	
	if(CMP3->GetCheck()){
		RegisterFileRelationA(_T(".mp3"),szFilePath,strMP3,CString(p)+L"res\\mp3.ico",_T(""));
		assfilelist.Append(_T("mp3"));
	}
	if(CWMA->GetCheck()){
		RegisterFileRelationA(_T(".wma"),szFilePath,strWMA,CString(p)+L"res\\wma.ico",_T(""));
		if (assfilelist.GetLength()>0)
		{
			assfilelist.Append(_T(",wma"));
		}
		else
		{
			assfilelist.Append(_T("wma"));
		}
	}
	if(CFLAC->GetCheck()){
		RegisterFileRelationA(_T(".flac"),szFilePath,strFLAC,CString(p)+L"res\\flac.ico",_T(""));
		if (assfilelist.GetLength()>0)
		{
			assfilelist.Append(_T(",flac"));
		}
		else
		{
			assfilelist.Append(_T("flac"));
		}
	}
	if(CAPE->GetCheck()){
		RegisterFileRelationA(_T(".ape"),szFilePath,strAPE,CString(p)+L"res\\ape.ico",_T(""));
		if (assfilelist.GetLength()>0)
		{
			assfilelist.Append(_T(",ape"));
		}
		else
		{
			assfilelist.Append(_T("ape"));
		}
	}
	if(COGG->GetCheck()){
		RegisterFileRelationA(_T(".ogg"),szFilePath,strOGG,CString(p)+L"res\\ogg,ico",_T(""));
		if (assfilelist.GetLength()>0)
		{
			assfilelist.Append(_T(",ogg"));
		}
		else
		{
			assfilelist.Append(_T("ogg"));
		}
	}

	SHChangeNotify(SHCNE_ASSOCCHANGED,SHCNF_IDLIST,0,0);
	//MusicUtils::WriteConfigXml(_T("assocfile"),assfilelist,"SetPlayerConfigValue");
	//delete CMP3;
	//delete CWMA;
	//delete CFLAC;
	//delete CAPE;
	//delete COGG;
	//::SendMessage(HWND_BROADCAST, WM_SETTINGCHANGE, 0, 0);
}


void  RegisterFileRelationA(CString strExt, CString strAppName, CString strAppKey, CString strDefaultIcon, CString strDescribe)
{

	CString strTemp;
	HKEY hKey;  
	USES_CONVERSION;
	RegCreateKey(HKEY_CLASSES_ROOT,strExt,&hKey);  
	RegSetValue(hKey,_T(""),REG_SZ,strAppKey,strAppKey.GetLength()+1);  
	RegCloseKey(hKey);  

	//RegCreateKey(HKEY_CLASSES_ROOT,strAppKey,&hKey);  
	//RegSetValue(hKey,_T(""),REG_SZ,strDescribe,strDescribe.GetLength()+1);  
	//RegCloseKey(hKey);  

	strTemp.Format(_T("%s\\DefaultIcon"),strAppKey); 
	RegCreateKey(HKEY_CLASSES_ROOT,strTemp,&hKey);  
	RegSetValue(hKey,_T(""),REG_SZ,strDefaultIcon,strDefaultIcon.GetLength()+1);  
	RegCloseKey(hKey);  

	strTemp.Format(_T("%s\\Shell"),strAppKey);  
	RegCreateKey(HKEY_CLASSES_ROOT,strTemp,&hKey);  
	RegSetValue(hKey,_T(""),REG_SZ,_T("Open"),CString("Open").GetLength()+1);  
	RegCloseKey(hKey);  

	strTemp.Format(_T("%s\\Shell\\Open\\Command"),strAppKey);
	RegCreateKey(HKEY_CLASSES_ROOT,strTemp,&hKey);  
  
	strTemp.Format(_T("%s \"%%1\""),strAppName);
	RegSetValue(hKey,_T(""),REG_SZ,strTemp,strTemp.GetLength()+1);  
	RegCloseKey(hKey);  


	HKEY hKeyW; 
	strTemp.Format(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\%s"),strExt);
	RegCreateKey(HKEY_CURRENT_USER,strTemp,&hKeyW);////创建键"testfile\\shell\\open\\command",键值为本程序指针
	RegSetValueExW(hKeyW,_T("Progid"),0,REG_SZ,(LPBYTE)strAppKey.GetBuffer(),(strAppKey.GetLength()+1)*sizeof(CString));
	RegCloseKey(hKeyW);  
	//SHChangeNotify(SHCNE_ASSOCCHANGED,   SHCNF_IDLIST,   0,   0);

	
	/*
	CRegKey myKey;
	
	myKey.Create(HKEY_CLASSES_ROOT,strExt);
	myKey.SetValue(strAppKey);myKey.Close();
	
	CString strTemp;
	strTemp.Format(_T("%s\\DefaultIcon"),strAppKey); 
	
	
	myKey.Create(HKEY_CLASSES_ROOT,strAppKey);
	myKey.Create(HKEY_CLASSES_ROOT,strTemp);
	myKey.SetValue(strDefaultIcon);
	strTemp.Format(_T("%s\\Shell"),strAppKey);  
	myKey.Create(HKEY_CLASSES_ROOT,strTemp);
	myKey.SetValue(_T("open"));
	strTemp.Format(_T("%s\\Shell\\open\\Command"),strAppKey);
	myKey.Create(HKEY_CLASSES_ROOT,strTemp);
	strTemp.Format(_T("%s \"%%1\""),strAppName);
	myKey.SetValue(strTemp);
	myKey.Close();
	//SHChangeNotify(SHCNE_ASSOCCHANGED,   SHCNF_FLUSHNOWAIT,   0,   0);
	*/
	
	SHChangeNotify(SHCNE_ASSOCCHANGED,SHCNF_FLUSHNOWAIT,0,0);
	//SendMessage(HWND_BROADCAST, WM_SETTINGCHANGE, 0, 0);
}

LPBYTE CString_To_LPBYTE(CString str)
{
	LPBYTE lpb=new BYTE[str.GetLength()+1];
	for(int i=0;i<str.GetLength();i++)
		lpb[i]=str[i];


	lpb[str.GetLength()]=0;
	return lpb;
}

BOOL FileJoin::RegisterFileRelation( const CString& strExtension,  
	const CString& strApplicationName,
	const CString& strRunKey,
	const CString& strDefaultIcon,  
	const CString& strDescription )
{

	HKEY hRegeditKey ;

	if ( RegOpenKey( HKEY_CLASSES_ROOT, strExtension, &hRegeditKey ) != ERROR_SUCCESS )
	{
		if ( RegCreateKey( HKEY_CLASSES_ROOT, strExtension, &hRegeditKey ) != ERROR_SUCCESS )
		{
			AfxMessageBox(_T("errors11!"));
			return FALSE ;
		}
	}

	RegSetValue( hRegeditKey, _T(""), REG_SZ, strRunKey, strRunKey.GetLength()+1 ) ;
	RegCloseKey( hRegeditKey ) ;

	if ( RegOpenKey( HKEY_CLASSES_ROOT, strRunKey, &hRegeditKey ) != ERROR_SUCCESS )
	{
		if ( RegCreateKey( HKEY_CLASSES_ROOT, strRunKey, &hRegeditKey ) != ERROR_SUCCESS )
		{
			AfxMessageBox(_T("errors22!"));
			return FALSE ;
		}
	}

	RegSetValue( hRegeditKey, _T(""), REG_SZ, strDescription, strDescription.GetLength()+1 ) ;
	RegCloseKey( hRegeditKey ) ;

	if ( RegOpenKey( HKEY_CLASSES_ROOT, strRunKey, &hRegeditKey ) != ERROR_SUCCESS )
	{
		if ( RegCreateKey( HKEY_CLASSES_ROOT, strRunKey, &hRegeditKey ) != ERROR_SUCCESS )
		{
			AfxMessageBox(_T("errors33!"));
			return FALSE ;
		}
	}

	CString strRegedit ;

	strRegedit.Format( _T("%s\\DefaultIcon"), strRunKey ) ;

	if ( RegOpenKey( HKEY_CLASSES_ROOT, strRegedit, &hRegeditKey ) != ERROR_SUCCESS )
	{
		if ( RegCreateKey( HKEY_CLASSES_ROOT, strRegedit, &hRegeditKey ) != ERROR_SUCCESS )
		{
			AfxMessageBox(_T("errors44!"));
			return FALSE ;
		}
	}

	if ( strDefaultIcon.IsEmpty() )
	{
		strRegedit.Format( _T("\"%s\",3"), strApplicationName ) ;
	}
	else
	{
		strRegedit = strDefaultIcon ;
	}

	RegSetValue( hRegeditKey, _T(""), REG_SZ, strRegedit, strRegedit.GetLength()+1 ) ;
	RegCloseKey( hRegeditKey ) ;

	strRegedit.Format( _T("%s\\Shell"), strRunKey ) ;

	if ( RegOpenKey( HKEY_CLASSES_ROOT, strRegedit, &hRegeditKey ) != ERROR_SUCCESS )
	{
		if ( RegCreateKey( HKEY_CLASSES_ROOT, strRegedit, &hRegeditKey ) != ERROR_SUCCESS )
		{
			AfxMessageBox(_T("errors55!"));
			return FALSE ;
		}
	}

	strRegedit = _T("Open") ;

	RegSetValue( hRegeditKey, _T(""), REG_SZ, strRegedit, strRegedit.GetLength()+1 ) ;
	RegCloseKey( hRegeditKey ) ;

	strRegedit.Format( _T("%s\\Shell\\Open\\Command"), strRunKey ) ;

	if ( RegOpenKey( HKEY_CLASSES_ROOT, strRegedit, &hRegeditKey ) != ERROR_SUCCESS )
	{
		if ( RegCreateKey( HKEY_CLASSES_ROOT, strRegedit, &hRegeditKey ) != ERROR_SUCCESS )
		{
			AfxMessageBox(_T("errors66!"));
			return FALSE ;
		}
	}

	strRegedit.Format( _T("\"%s\" \"%%1\""), strApplicationName ) ;

	RegSetValue( hRegeditKey, _T(""), REG_SZ, strRegedit, strRegedit.GetLength()+1 ) ;
	RegCloseKey( hRegeditKey ) ;
	//AfxMessageBox(_T("errors777!"));
	return TRUE ;
}