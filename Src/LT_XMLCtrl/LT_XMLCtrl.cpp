// LT_XMLCtrl.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "LT_XMLCtrl.h"
#include "tinystr.h"
#include "tinyxml.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			_tprintf(_T("错误: MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: 在此处为应用程序的行为编写代码。
		}
	}
	else
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
extern "C" LT_XMLCTRL_API void PlayList(int i,CArray<FileListInfo,FileListInfo&> *l)
{
	if (i)
		LoadPlayList(l);
	else
		SavePlayList(l);
}
extern "C" LT_XMLCTRL_API void SaveNewSkin(CString filename,char * maskcolor)
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);      
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	USES_CONVERSION;
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );	
	doc.LinkEndChild( decl );
		TiXmlElement * element = new TiXmlElement( "SKIN" );
		element->SetAttribute("maskcolor",maskcolor);
	CString cs;
	cs.Format(_T("%s\%s.xml"),szFilePath,CString(filename));
	doc.SaveFile(W2A(cs));
}

extern "C" LT_XMLCTRL_API void RadioList(CArray<FileListInfo,FileListInfo&> *mulist)
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);      
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	CString cs;
	cs.Format(_T("%s\%s"),szFilePath,CString("radiolist.xml"));
	USES_CONVERSION;
	TiXmlDocument *doc=new TiXmlDocument();
	doc->LoadFile(W2A(cs));
	TiXmlElement* mu = doc->RootElement();
	while(mu)
	{
		TiXmlAttribute* attributeOfmu = mu->FirstAttribute(); 
		FileListInfo fileinfo;
		while(attributeOfmu)
		{
			const char * ss=attributeOfmu->Name();
			USES_CONVERSION;
			LPWSTR x = A2W(attributeOfmu->Value());
			
			if (!strcmp(attributeOfmu->Name(),"name"))
			{
				fileinfo.filename=x;
			}

			if (!strcmp(attributeOfmu->Name(),"value"))
			{
				fileinfo.filepath=x;
			}

			//int tpathindex=fileinfo.filepath.ReverseFind('\\');
			//CString tcstring=GetMusicName(GetSubString(fileinfo.filepath,tpathindex));
			
			attributeOfmu = attributeOfmu->Next();
		}
		mulist->Add(fileinfo);
		mu = mu->NextSiblingElement();
	}
}

extern "C" LT_XMLCTRL_API void SetPlayerConfigValue(CString nodename,CString nodevale)
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);      
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	CString cs;
	cs.Format(_T("%s\%s"),szFilePath,CString("config.xml"));
	USES_CONVERSION;

	TiXmlDocument *docw=new TiXmlDocument();
	docw->LoadFile(W2A(cs));
	TiXmlElement* muw = docw->RootElement();
	while(muw)
	{

		if(A2W(muw->Value())==nodename)
		{
			TiXmlAttribute* attributeOfmuw = muw->FirstAttribute(); 
			while(attributeOfmuw)
			{ 
				LPWSTR Aname = A2W(attributeOfmuw->Name());
				if(Aname==CString("value")){
					char * n = cctryWideCharToAnsi(nodevale.GetBuffer());
					
					attributeOfmuw->SetValue(n); 
					docw->SaveFile(W2A(cs));  
					return; 
				}
				attributeOfmuw = attributeOfmuw->Next();
			}
		}		
		muw = muw->NextSiblingElement();
	}
		
}

void SaveSkinList(CArray<UiSkinInfo,UiSkinInfo&> *sklist)
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);      
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	USES_CONVERSION;
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );	
	doc.LinkEndChild( decl );

	for (int i=0;i<sklist->GetSize();i++)
	{	
		/*CString www=sklist->GetAt(i).filepath;*/
		TiXmlElement * element = new TiXmlElement( "SKIN" );
		UiSkinInfo info =sklist->GetAt(i);
		element->SetAttribute("id",W2A(info.id));
		element->SetAttribute("fname",W2A(info.fname));

		char *st;
		st= (char*)malloc(_MAX_PATH);
		ZeroMemory(st,strlen(st));
		_itoa(info.maskcolor,st,10);

		element->SetAttribute("maskcolor",st);
		doc.LinkEndChild( element );
	}
	CString cs;
	cs.Format(_T("%s\%s"),szFilePath,CString("skinlist.xml"));
	doc.SaveFile(W2A(cs));
}

void LoadSkinList(CArray<UiSkinInfo,UiSkinInfo&> *sklist)
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);      
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	CString cs;
	cs.Format(_T("%s\%s"),szFilePath,CString("skinlist.xml"));
	USES_CONVERSION;
	TiXmlDocument *doc=new TiXmlDocument();
	doc->LoadFile(W2A(cs));
	TiXmlElement* mu = doc->RootElement();
	while(mu)
	{
		TiXmlAttribute* attributeOfmu = mu->FirstAttribute(); 
		UiSkinInfo skininfo;
		while(attributeOfmu)
		{
			const char * ss=attributeOfmu->Name();
			USES_CONVERSION;
			LPWSTR x = A2W(attributeOfmu->Value());

			if (!strcmp(attributeOfmu->Name(),"id"))
			{
				skininfo.id=x;
			}

			if (!strcmp(attributeOfmu->Name(),"fname"))
			{
				skininfo.fname=x;
			}

			if (!strcmp(attributeOfmu->Name(),"maskcolor"))
			{
				skininfo.maskcolor=_wtoi(x);
			}

			//int tpathindex=fileinfo.filepath.ReverseFind('\\');
			//CString tcstring=GetMusicName(GetSubString(fileinfo.filepath,tpathindex));

			attributeOfmu = attributeOfmu->Next();
		}
		sklist->Add(skininfo);
		mu = mu->NextSiblingElement();
	}

}


extern "C" LT_XMLCTRL_API void SkinList(int type,CArray<UiSkinInfo,UiSkinInfo&> *sklist)
{
	if (type)
	{
		LoadSkinList(sklist);
	}else
	{
		SaveSkinList(sklist);
	}
}
extern "C" LT_XMLCTRL_API UiSkinInfo GetSkinInfo(CString id)
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);      
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	CString cs;
	cs.Format(_T("%s\%s"),szFilePath,CString("skinlist.xml"));
	USES_CONVERSION;
	TiXmlDocument *doc=new TiXmlDocument();
	doc->LoadFile(W2A(cs));
	TiXmlElement* mu = doc->RootElement();
	UiSkinInfo skininfo={0,0,L""};
	while(mu)
	{
		if(skininfo.maskcolor!=0 && skininfo.id!=CString("") && skininfo.fname!=CString(""))
		{
			return skininfo;
		}

		TiXmlAttribute* attributeOfmu = mu->FirstAttribute(); 

		while(attributeOfmu)
		{
			const char * ss=attributeOfmu->Name();
			USES_CONVERSION;
			LPWSTR x = A2W(attributeOfmu->Value());

			if(!strcmp(attributeOfmu->Name(),"id") && id!=x)
			{
				mu = mu->NextSiblingElement();
				break;
			}


			if (!strcmp(attributeOfmu->Name(),"id"))
			{
 				skininfo.id = id;
				//attributeOfmu = attributeOfmu->Next();
				//continue;
			}
			if (!strcmp(attributeOfmu->Name(),"fname"))
			{
				skininfo.fname=x;
			}

			if (!strcmp(attributeOfmu->Name(),"maskcolor"))
			{
				skininfo.maskcolor=atoi(attributeOfmu->Value());
			}
			attributeOfmu = attributeOfmu->Next();
		}
		//delete attributeOfmu;
		//mu = mu->NextSiblingElement();
	}
}


extern "C" LT_XMLCTRL_API CString GetPlayerConfigValue(CString name)
{

	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);      
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	CString cs;
	cs.Format(_T("%s\%s"),szFilePath,CString("config.xml"));
	USES_CONVERSION;

	TiXmlDocument *docw=new TiXmlDocument();
	docw->LoadFile(W2A(cs));
	TiXmlElement* muw = docw->RootElement();
	
	while(muw)
	{

	    if(A2W(muw->Value())==name)
		{
			TiXmlAttribute* attributeOfmuw = muw->FirstAttribute(); 
			while(attributeOfmuw)
			{ 
				LPWSTR Aname = A2W(attributeOfmuw->Name());
				if(Aname==CString("value")){
				/*LPWSTR Avalue = A2W(attributeOfmuw->Value());*/
					wchar_t *abcccc =new wchar_t[MAX_PATH+1];
					ZeroMemory(abcccc,0);
					wcscpy(abcccc,AnsiToWideChar((char*)attributeOfmuw->Value()));
					//wchar_t * abcccc=;
				return abcccc;
				}
				attributeOfmuw = attributeOfmuw->Next();
			}
		}		
		muw = muw->NextSiblingElement();
	}
	return CString(L"");
}
// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 LT_XML.h
void LoadPlayList(CArray<FileListInfo,FileListInfo&>* mulist)
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);      
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	CString cs;
	cs.Format(_T("%s\%s"),szFilePath,CString("playlist.xml"));
	USES_CONVERSION;


	TiXmlDocument *doc=new TiXmlDocument();
	doc->LoadFile(W2A(cs));
	TiXmlElement* mu = doc->RootElement();
	while(mu)
	{
		

		TiXmlAttribute* attributeOfmu = mu->FirstAttribute(); 		
		FileListInfo fileinfo;
		while(attributeOfmu)
		{
			const char * ss=attributeOfmu->Name();
			//LPWSTR x = A2W();
			char * aaaaaa = (char*)attributeOfmu->Value();
			wchar_t *x = new wchar_t[MAX_PATH+1];
			memset(x,0,MAX_PATH+1);
			wcscpy(x,AnsiToWideChar((char*)attributeOfmu->Value()));
				
			if (!strcmp(attributeOfmu->Name(),"name"))
			{
				fileinfo.filename=x;
			}		
			if (!strcmp(attributeOfmu->Name(),"value"))
			{
				fileinfo.filepath=x;

			}
			attributeOfmu = attributeOfmu->Next();
		}
		mulist->Add(fileinfo);
		 mu = mu->NextSiblingElement();
	}
}
void SavePlayList(CArray<FileListInfo,FileListInfo&> *musiclist)
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);      
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	USES_CONVERSION;
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );	
	doc.LinkEndChild( decl );
	
	for (int i=0;i<musiclist->GetSize();i++)
	{	
		CString www=musiclist->GetAt(i).filepath;
		TiXmlElement * element = new TiXmlElement( "MU" );
		element->SetAttribute("value",cctryWideCharToAnsi(musiclist->GetAt(i).filepath.GetBuffer()));
		element->SetAttribute("name",cctryWideCharToAnsi(musiclist->GetAt(i).filename.GetBuffer()));
		doc.LinkEndChild( element );
	}
	CString cs;
	cs.Format(_T("%s\%s"),szFilePath,CString("playlist.xml"));
	doc.SaveFile(W2A(cs));
}

CString GetMusicName(CString mfullname)
{
	CArray<CString,CString&> arrays;
	SpliteCString(mfullname,arrays,_T("."));
	CString t=arrays[0];
	return t;
}

CString GetSubString(CString str,int index)
{
	str = str.Mid(index+1);
	return str;
}

void SpliteCString(CString str,CArray<CString,CString&> &arrays,CString spstr)
{
	int index=0;
	CString resToken=str.Tokenize(spstr,index);
	while (resToken != _T(""))
	{
		arrays.Add(resToken);
		resToken=str.Tokenize(spstr,index);
	}
}

char *cctryWideCharToAnsi(wchar_t *pWideChar)
{
	if (!pWideChar) return NULL;
	char *pszBuf = NULL;
	int needBytes = WideCharToMultiByte(CP_UTF8, 0, pWideChar, -1, NULL, 0, NULL, NULL);
	if (needBytes > 0){
	pszBuf = new char[needBytes+1];
	ZeroMemory(pszBuf, (needBytes+1)*sizeof(char));
	WideCharToMultiByte(CP_UTF8, 0, pWideChar, -1, pszBuf, needBytes, NULL, NULL);
	}
	return pszBuf;
}

wchar_t * AnsiToWideChar(char* aaa)
{
	WCHAR abc[MAX_PATH+1];
	int nSize = MultiByteToWideChar(CP_UTF8 ,0,aaa,-1,NULL,0);
	MultiByteToWideChar(CP_UTF8 ,0,aaa,-1,abc,nSize);
	return abc;
}
