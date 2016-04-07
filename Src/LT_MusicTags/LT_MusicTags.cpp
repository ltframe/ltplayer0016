// LT_MusicTags.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "LT_MusicTags.h"
#include "tags.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;
const char* const g_fmt = "%IFV2(%ITRM(%TITL),%ITRM(%TITL),no-Atitle)|%IFV2(%ITRM(%ARTI),%ITRM(%ARTI),no-Aartist)";
using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// 初始化 MFC 并在失败时显示错误
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: MFC 初始化失败\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: 在此处为应用程序的行为编写代码。
	}

	return nRetCode;
}
extern "C" LT_MUSICTAGS_API bool GetMusicTilteAndArtist(DWORD handle,CString* title,CString* artist)
{
	if(!handle)
	{
		return true;
	}
	char* str =(char*) TAGS_Read(handle, g_fmt);
	if(*str)
	{
		int index=0;
		CArray<CString,CString&> arrays;
		CString tag=CString(str);
		CString resToken=tag.Tokenize(_T("|"),index);
		while (resToken != _T(""))
		{
			arrays.Add(resToken);
			resToken=tag.Tokenize(_T("|"),index);
		}
		*title=arrays.GetAt(0);
		*artist=arrays.GetAt(1);
		if (*title==_T("no-Atitle"))
		{
			return false;
		}
		else
		{
			if (*artist==_T("no-Aartist"))
			{
				*artist=_T("");
			}
		}
	}else
	{
		//delete str;
		return false;
	}
	//delete str;
	return true;
}
