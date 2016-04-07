#include "StdAfx.h"
#include "MusicUtils.h"
#include <conio.h>
#include <direct.h>
#include <Gdipluseffects.h>

typedef void (*MYPROC)(CString,CString);
typedef CString (*GETMYPROC)(CString);
typedef void (*LSMYPROC)(int i,CArray<FileListInfo,FileListInfo&>* carray);
typedef void (*LSRAMYPROC)(CArray<FileListInfo,FileListInfo&>* carray);
typedef void (*LSSKINLISTPROC)(int type,CArray<UiSkinInfo,UiSkinInfo&>* carray);
typedef UiSkinInfo (*LSSKININFO)(CString);
MusicUtils::MusicUtils(void)
{
}

MusicUtils::~MusicUtils(void)
{
}
double MusicUtils::GetMusicPositionUsePointX(double sliderlength,double x,QWORD seconds)
{
	 double t=seconds/sliderlength;
     return t*x;
}

double MusicUtils::SetMusicPositionUseSeconds(double aseconds,double sliderlength,double cseconds)
{
   double a =sliderlength/aseconds;
   return a*cseconds;
}

bool MusicUtils::IsStrInStrAarry(CString e,CString str)
{
   CArray<CString,CString&> arrays;
   SpliteCString(str,arrays,_T(","));
   for (int i=0;i<arrays.GetSize();i++)
   {
	   if (arrays.ElementAt(i)==e)
		   return true;
   }
   return false;
}
void MusicUtils::SpliteCString(CString str,CArray<CString,CString&> &arrays,CString spstr)
{
	int index=0;
	CString resToken=str.Tokenize(spstr,index);
	while (resToken != _T(""))
	{
		arrays.Add(resToken);
		resToken=str.Tokenize(spstr,index);
	}
}
CString MusicUtils::GetSubString(CString str,int index)
{
	str = str.Mid(index+1);
	return str;
}

CString MusicUtils::GetMusicName(CString mfullname)
{
	CArray<CString,CString&> arrays;
	SpliteCString(mfullname,arrays,_T("."));
	CString t=arrays[0];
    return t;
}

void MusicUtils::ConsoleWrite(CString cs)
{
	#ifdef _OPENCONSOLE
		static int si=1;
		_cwprintf_s(_T("%d-%s\n"), si,cs);
		si++;
	#endif
}

CString MusicUtils::IntFormatCString(CString c,int i)
{
  CString cs;
  cs.Format(_T("%s:%d"),c,i);
  return cs;
}

CString MusicUtils::IntFormatCString(CString c,CString i)
{
	CString cs;
	cs.Format(_T("%s:%s"),c,i);
	return cs;
}

char * MusicUtils::WideCharToMultiChar(wchar_t* pwszUnicode)
{
	int iSize; 
	char* pszMultiByte; 

	iSize = WideCharToMultiByte(CP_ACP, 0, pwszUnicode, -1, NULL, 0, NULL, NULL); 
	pszMultiByte = (char*)malloc((iSize+1)/**sizeof(char)*/); 
	WideCharToMultiByte(CP_ACP, 0, pwszUnicode, -1, pszMultiByte, iSize, NULL, NULL); 
	return pszMultiByte;
}

CString MusicUtils::Seconds2Time(int sec)
{
	CString cs;
	int mm=sec/60;
	int se=sec%60;
	CString _pmm("");
	CString _pse("");
	if(mm<10)
	{
		_pmm = "0";
	}else{_pmm="";}
	if(se<10)
	{
		_pse = "0";
	}else{_pse="";}
	cs.Format(_T("%s%d:%s%d"),_pmm,mm,_pse,se);
	return cs;
}

void MusicUtils::WriteConfigXml(LPCTSTR key ,LPCTSTR str,LPCSTR funname)
{
	HINSTANCE hinstLib; 
	MYPROC ProcAdd; 
	hinstLib = LoadLibrary(TEXT("LT_XMLCtrl.dll")); 
	ProcAdd = (MYPROC)GetProcAddress(hinstLib, funname); 
	(ProcAdd)(key,str);
	FreeLibrary(hinstLib);
}

CString MusicUtils::GetConfigXml(LPCTSTR key,LPCTSTR defalutvalue)
{
	HINSTANCE hinstLib; 
	GETMYPROC ProcAdd; 
	hinstLib = LoadLibrary(TEXT("LT_XMLCtrl.dll")); 
	int a=GetLastError();
	ProcAdd = (GETMYPROC) GetProcAddress(hinstLib, "GetPlayerConfigValue"); 
	CString T = (ProcAdd)(key);
	if (T=="")
	{
		T= defalutvalue;
	}
	FreeLibrary(hinstLib);
	return T;
	/*return CString("1");*/
}

void MusicUtils::LSMusicList(int i,CArray<FileListInfo,FileListInfo&>* carray)
{
	HINSTANCE hinstLib; 
	LSMYPROC ProcAdd; 
	hinstLib = LoadLibrary(TEXT("LT_XMLCtrl.dll")); 
	ProcAdd = (LSMYPROC) GetProcAddress(hinstLib, "PlayList"); 
	ProcAdd(i,carray);
	FreeLibrary(hinstLib);
}

void MusicUtils::LSSkinList(int type,CArray<UiSkinInfo,UiSkinInfo&>* carray)
{
	HINSTANCE hinstLib; 
	LSSKINLISTPROC ProcAdd; 
	hinstLib = LoadLibrary(TEXT("LT_XMLCtrl.dll")); 
	ProcAdd = (LSSKINLISTPROC) GetProcAddress(hinstLib, "SkinList"); 
	ProcAdd(type,carray);
	FreeLibrary(hinstLib);
}



UiSkinInfo MusicUtils::LSSkinInfo(CString id)
{
	HINSTANCE hinstLib; 
	LSSKININFO ProcAdd; 
	hinstLib = LoadLibrary(TEXT("LT_XMLCtrl.dll")); 
	ProcAdd = (LSSKININFO) GetProcAddress(hinstLib, "GetSkinInfo"); 
	UiSkinInfo info = ProcAdd(id);
	FreeLibrary(hinstLib);
	return info;
}


void MusicUtils::LSRadioList(CArray<FileListInfo,FileListInfo&>* carray)
{
	HINSTANCE hinstLib; 
	LSRAMYPROC ProcAdd; 
	hinstLib = LoadLibrary(TEXT("LT_XMLCtrl.dll")); 
	ProcAdd = (LSRAMYPROC) GetProcAddress(hinstLib, "RadioList"); 
	ProcAdd(carray);
	FreeLibrary(hinstLib);
}

bool MusicUtils::ArrestKeyDown(MSG *pMsg)
{
	if( pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE || pMsg->wParam==VK_RETURN ))
	{
		return TRUE;
	}
	return FALSE;
}
wchar_t* MusicUtils::ConverI2W(int i)
{
	wchar_t *st;
	st= (wchar_t*)malloc(_MAX_PATH);
	ZeroMemory(st,wcslen(st));
	_itow(i,st,10);
	return st;
}

CString MusicUtils::GetFileTitleFromFileName(CString FileName) //获取文件名和扩展名
{
	int Where=FileName.ReverseFind('\\');
	if(Where==-1)
	{
		Where=FileName.ReverseFind('/');
	}
	CString FileTitle=FileName.Right(FileName.GetLength()-1-Where);
	int Which=FileTitle.ReverseFind('.');
	return FileTitle.Right(FileTitle.GetLength()-Which-1);

}
bool MusicUtils::IsUpdateOFVersion()
{
	//CInternetSession mysession;
	//CHttpConnection *myconn=mysession.GetHttpConnection(L"www.ltplayer.com");
	//CHttpFile *myfile=myconn->OpenRequest(L"GET",L"/getversion.php");
	//myfile->SendRequest();
	//CString mystr;
	//char tmp[1024];
	//while(myfile->ReadString((wchar_t*)tmp,1024))
	//{
	//	mystr+=tmp;
	//}
	//myfile->Close();
	//myconn->Close();
	//mysession.Close();
	//delete myfile;
	//delete myconn;
	//myfile=0;
	//myconn=0;

	//USES_CONVERSION;
	//CString mystr=_T("0.0.1.4");
	//int index=0;
	//mystr.Remove(_T('.'));
	//int versiontotal=atoi(W2A(mystr));
	//if(versiontotal>USERVERSION)
	//{
	//  return true;
	//}
	return false;
}

void MusicUtils::GetScreenInfo(ScreenInfo * info)
{
    info->cx  = GetSystemMetrics(SM_CXSCREEN); //屏幕宽度 
	info->cy = GetSystemMetrics(SM_CYSCREEN); //屏幕高度 
}

int MusicUtils::TestStringCx(const wchar_t *szText)
{
	//CDC tdc;
	//tdc.CreateCompatibleDC(CDC::FromHandle(::GetDC(0)));
	//HBITMAP hbitmap = CreateCompatibleBitmap(tdc.m_hDC,600,15);
	//tdc.SelectObject(hbitmap);
	//return tdc.GetOutputTextExtent(szText).cx;
	GraphicsPath path;
	FontFamily fontfamily;
	Font font(L"宋体",14);
	font.GetFamily(&fontfamily);
	StringFormat strFormat;
	strFormat.SetAlignment(StringAlignmentNear);
	path.AddString(szText,-1,&fontfamily,font.GetStyle(),font.GetSize(),PointF(0,0),&strFormat);
	RectF rcBound;
	path.GetBounds(&rcBound);
	return rcBound.Width;
}

//获取文件路径
char * MusicUtils::GetFilePath(char* a)
{
	char x[MAX_PATH];
	strcpy(x,a);
	char * p = strrchr(x,'\\');
	*p='\0';
	return x;
}


void MusicUtils::ScanFile(CString Dir,CArray<CString,CString&>& filearray,CString filetype)    
{

	CFileFind finder;
	CString Add=L"\\*";
	CString DirSpec=Dir+Add;                        //补全要遍历的文件夹的目录
	BOOL bWorking = finder.FindFile(DirSpec);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if(!finder.IsDots())              //扫描到的不是节点
		{
			if(finder.IsDirectory())           //扫描到的是文件夹
			{
				CString strDirectory = finder.GetFilePath();
				ScanFile(strDirectory,filearray,filetype);           //递归调用ScanFile（）
			}
			else                               //扫描到的是文件
			{
				CString strFile = finder.GetFilePath();    // 得到文件的全路径
				CString ext = GetFileTitleFromFileName(strFile).MakeLower();
				if (ext==CString("bmp"))
				{
					filearray.Add(strFile);
				}
				//进行一系列自定义操作
				
			}
		}
	}
	finder.Close();
}

void MusicUtils::EmptyDir(CString Dir)
{
	CFileFind finder;
	CFile cfile;
	CString Add=L"\\*";
	CString DirSpec=Dir+Add;                        //????????????
	BOOL bWorking = finder.FindFile(DirSpec);


	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		if(!finder.IsDots())              //????????
		{
			if(finder.IsDirectory())           //????????
			{
				CString strDirectory = finder.GetFilePath();
				if(_rmdir((const char*)(LPSTR)(LPCTSTR)strDirectory)==-1)
				{
					EmptyDir(strDirectory); 
				}
				bWorking = finder.FindFile(DirSpec);
			}
			else                               //???????
			{
				cfile.Remove(finder.GetFilePath());
			}
		}
	}
	finder.Close();

}


HBITMAP MusicUtils::GetStretchHBITMAP(CString filename,HDC dc,int cx,int cy)
{


	HDC hMemDC=::CreateCompatibleDC(dc);
	BITMAPINFO *bitmapinfo=new BITMAPINFO();
	bitmapinfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfo->bmiHeader.biBitCount = 32;
	bitmapinfo->bmiHeader.biHeight = cy;
	bitmapinfo->bmiHeader.biWidth = cx;
	bitmapinfo->bmiHeader.biPlanes = 1;
	bitmapinfo->bmiHeader.biCompression=BI_RGB;
	bitmapinfo->bmiHeader.biXPelsPerMeter=0;
	bitmapinfo->bmiHeader.biYPelsPerMeter=0;
	bitmapinfo->bmiHeader.biClrUsed=0;
	bitmapinfo->bmiHeader.biClrImportant=0;
	                       
	HBITMAP desthbitmap=::CreateDIBSection(hMemDC, bitmapinfo, DIB_RGB_COLORS, 0, NULL, (DWORD)0);
	HDC destdc =::CreateCompatibleDC(dc);
	::SelectObject(destdc,desthbitmap);
	::SetStretchBltMode(destdc, COLORONCOLOR);
	Bitmap bt(filename);
	HBITMAP temphBitmap;
	bt.GetHBITMAP(NULL,&temphBitmap);

	HDC tempdc =::CreateCompatibleDC(dc);
	::SelectObject(tempdc,temphBitmap);
	StretchBlt(destdc,0,0,cx,cy,tempdc,0,0,bt.GetWidth(),bt.GetHeight(),SRCCOPY);
	return desthbitmap;
}

BOOL MusicUtils::SaveBitMapToFile(HBITMAP hBitmap, CString lpFileName)
{
	HDC		hDC;		//?????       
	int		iBits;		//?????????????????   
	WORD	wBitCount;	//????????????   
	DWORD	dwPaletteSize=0,//???????,?????????,??????,???????
		dwBmBitsSize,
		dwDIBSize,
		dwWritten;
	BITMAP	Bitmap;      
	BITMAPFILEHEADER	bmfHdr;	//??????
	BITMAPINFOHEADER	bi;		//???????                
	LPBITMAPINFOHEADER	lpbi;	//???????           
	HANDLE	fh,   hDib,   hPal,hOldPal=NULL;//?????????,????,??????,?????
	//???????????????   
	hDC = CreateDC(_T("DISPLAY"),NULL,NULL,NULL);   
	iBits = GetDeviceCaps(hDC,BITSPIXEL)*GetDeviceCaps(hDC,PLANES);   
	DeleteDC(hDC);
	if(iBits<=1)   
		wBitCount = 1;   
	else if(iBits<=4)   
		wBitCount = 4;   
	else if(iBits<=8)   
		wBitCount = 8;
	else if(iBits<=24)   
		wBitCount = 24;
	else
		wBitCount = 32;
	//???????   
	if(wBitCount<=8)   
		dwPaletteSize = (1<<wBitCount)*sizeof(RGBQUAD);   

	//?????????
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);   
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;   
	bi.biHeight = Bitmap.bmHeight;   
	bi.biPlanes = 1;   
	bi.biBitCount = wBitCount;   
	bi.biCompression = BI_RGB;   
	bi.biSizeImage = 0;   
	bi.biXPelsPerMeter = 0;   
	bi.biYPelsPerMeter = 0;   
	bi.biClrUsed = 0;   
	bi.biClrImportant = 0;   

	dwBmBitsSize = ((Bitmap.bmWidth*wBitCount+31)/32)*4*Bitmap.bmHeight;   

	//?????????   
	hDib = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));   
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);   
	*lpbi = bi;   

	//   ?????         
	hPal = GetStockObject(DEFAULT_PALETTE);   
	if(hPal)
	{   
		hDC = ::GetDC(NULL);   
		hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);   
		RealizePalette(hDC);  
	}   

	//   ????????????   
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight,
		(LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwPaletteSize,
		(LPBITMAPINFO)lpbi,DIB_RGB_COLORS);   

	//?????         
	if(hOldPal)
	{
		SelectPalette(hDC,(HPALETTE)hOldPal,TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}   

	//??????           
	fh = CreateFile(lpFileName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,NULL);

	if(fh==INVALID_HANDLE_VALUE)
		return   FALSE;

	//   ???????   
	bmfHdr.bfType = 0x4D42;//   "BM"   
	dwDIBSize = sizeof(BITMAPFILEHEADER)+
		sizeof(BITMAPINFOHEADER)+
		dwPaletteSize+dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+
		(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;

	//   ???????
	WriteFile(fh,(LPSTR)&bmfHdr,sizeof(BITMAPFILEHEADER),&dwWritten,NULL);
	//   ??????????
	WriteFile(fh,(LPSTR)lpbi,dwDIBSize,&dwWritten,NULL);

	//??????
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return   TRUE;
}


char* MusicUtils::CreatePlayerDir(char * sourcepath,char * path)
{
	char createpath[MAX_PATH]={0};
	strcat(createpath,sourcepath);
	strcat(createpath,"\\");
	strcat(createpath,path);
	USES_CONVERSION;
	if(!::CreateDirectory(A2W(createpath),NULL))
	{
		int x = GetLastError();
		::MessageBox(NULL,_T("aaaaaaaaaaaa"),NULL,NULL);
		return NULL;
	}

	return createpath;
}
char* MusicUtils::newGUID()
{
	static char buf[64] = {0};
	GUID guid;
	CoInitialize(NULL);
	if (S_OK == ::CoCreateGuid(&guid))
	{
		_snprintf(buf, sizeof(buf),
			"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
			guid.Data1,
			guid.Data2,
			guid.Data3,
			guid.Data4[0], guid.Data4[1],
			guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
	}
	CoUninitialize();
	return (char*)buf;
}


TCHAR* MusicUtils::GetModulePathW()
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);      
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	return szFilePath;
}

char * MusicUtils::GetModulePathA()
{
	USES_CONVERSION;
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);      
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;

    return W2A(szFilePath);
}


bool MusicUtils::IsPlayerSupportMusicType(CString mname)
{
	CString ext = GetMusicExt(mname);
	return IsStrInStrAarry(ext,L"mp1,mp2,mp3,wma,flac,aac,ogg,ape");
}

CString MusicUtils::GetMusicExt(CString mfullname)
{
	CArray<CString,CString&> arrays;
	SpliteCString(mfullname,arrays,_T("."));
	CString t=arrays[1];
	return t;
}

int MusicUtils::Random(int max)
{
	srand((int)time(0));
	int x = rand()%max;
	return x;
}


char *  MusicUtils::CreateTimeFileName()
{
	char name[MAX_PATH+1];
	ZeroMemory(name,MAX_PATH);
	SYSTEMTIME timeDest;
	GetLocalTime(&timeDest);
	sprintf(name,"%4d%02d%02d%02d%02d%02d%02d",timeDest.wYear,timeDest.wMonth,timeDest.wDay,timeDest.wHour,timeDest.wMinute,timeDest.wSecond,timeDest.wMilliseconds);
	return name;
}