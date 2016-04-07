// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 LT_XMLCTRL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// LT_XMLCTRL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。

typedef struct tagFileListInfo
{
	CString filename;
	CString filepath;
	int filewidth;
	int fileheight;
	RECT rect;
	int allinindex;
	int mousehovered;
	int mousedbclick;
}FileListInfo,UIFileListInfo;

typedef struct tagUiBgSkinInfo
{
	CString id;
	INT maskcolor;
	CString fname;
}UiSkinInfo ;

#ifdef LT_XMLCTRL_EXPORTS
#define LT_XMLCTRL_API __declspec(dllexport)
#else
#define LT_XMLCTRL_API __declspec(dllimport)
#endif

// 此类是从 LT_XMLCtrl.dll 导出的
class LT_XMLCTRL_API CLT_XMLCtrl {
public:
	CLT_XMLCtrl(void);
	// TODO: 在此添加您的方法。
};

extern LT_XMLCTRL_API int nLT_XMLCtrl;

LT_XMLCTRL_API int fnLT_XMLCtrl(void);
extern "C" LT_XMLCTRL_API void PlayList(int i,CArray<FileListInfo,FileListInfo&>*);
void LoadPlayList(CArray<FileListInfo,FileListInfo&>*);
void SavePlayList(CArray<FileListInfo,FileListInfo&>*);
void LoadSkinList(CArray<UiSkinInfo,UiSkinInfo&> *sklist);
void SaveSkinList(CArray<UiSkinInfo,UiSkinInfo&> *sklist);
void CreateFile(CString filename);
CString GetMusicName(CString mfullname);
CString GetSubString(CString str,int index);
void SpliteCString(CString str,CArray<CString,CString&> &arrays,CString spstr);
extern "C" LT_XMLCTRL_API CString GetPlayerConfigValue(CString);
extern "C" LT_XMLCTRL_API void SetPlayerConfigValue(CString,CString);
extern "C" LT_XMLCTRL_API void RadioList(CArray<FileListInfo,FileListInfo&>*);
extern "C" LT_XMLCTRL_API void SkinList(int type,CArray<UiSkinInfo,UiSkinInfo&>*);
extern "C" LT_XMLCTRL_API void SaveNewSkin(CString,char*);
extern "C" LT_XMLCTRL_API UiSkinInfo GetSkinInfo(CString);
char *cctryWideCharToAnsi(wchar_t *pWideChar);
wchar_t * AnsiToWideChar(char* aaa);
