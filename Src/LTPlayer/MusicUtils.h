#pragma once
#include "UIInfo.h"
#include "UIInterface.h"
#include  <atltime.h>
class MusicUtils
{
public:
	MusicUtils(void);
	~MusicUtils(void);
	static double GetMusicPositionUsePointX(double sliderlength,double x,QWORD seconds);
	static double SetMusicPositionUseSeconds(double aseconds,double sliderlength,double cseconds);
	static bool IsStrInStrAarry(CString e,CString str);
	static void SpliteCString(CString str,CArray<CString,CString&> &arrays,CString);
	static void ConsoleWrite(CString cs);
	static CString IntFormatCString(CString c,int i);
	static CString IntFormatCString(CString c,CString i);
	static char * WideCharToMultiChar(wchar_t* pwszUnicode);
	template <class T>  static int getArrayLen(T&  array)
	{
		return (sizeof(array) / sizeof(CString));
	}
	static CString GetSubString(CString,int);
	static CString GetMusicName(CString mfullname);
	static CString Seconds2Time(int sec);
	static void WriteConfigXml(LPCTSTR key ,LPCTSTR str,LPCSTR);
	static CString GetConfigXml(LPCTSTR key,LPCTSTR);
	static void LSMusicList(int i,CArray<FileListInfo,FileListInfo&>* carray);
	static void LSRadioList(CArray<FileListInfo,FileListInfo&>* carray);
	static void LSSkinList(int type,CArray<UiSkinInfo,UiSkinInfo&>* carray);
	static UiSkinInfo LSSkinInfo(CString id);
	static bool ArrestKeyDown(MSG *msg);
	static wchar_t* ConverI2W(int i);
	static bool IsUpdateOFVersion();
	static CString GetFileTitleFromFileName(CString FileName);
	static void GetScreenInfo(ScreenInfo * info);
	static int TestStringCx(const wchar_t* szText);
	static void ScanFile(CString Dir,CArray<CString,CString&>&,CString);   
	static char* GetFilePath(char* a);
	static void EmptyDir(CString Dir);
	static HBITMAP GetStretchHBITMAP(CString filename,HDC dc,int cx,int cy);
	static BOOL SaveBitMapToFile(HBITMAP hBitmap, CString lpFileName);
	static char* newGUID();
	static char* CreatePlayerDir(char * sourcepath,char * path);
	static TCHAR* GetModulePathW();
	static char * GetModulePathA();
	static CString GetMusicExt(CString mfullname);
	static bool IsPlayerSupportMusicType(CString mname);
	static int Random(int max);
	static char *  MusicUtils::CreateTimeFileName();
};
