// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 LT_MUSICTAGS_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// LT_MUSICTAGS_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef LT_MUSICTAGS_EXPORTS
#define LT_MUSICTAGS_API __declspec(dllexport)
#else
#define LT_MUSICTAGS_API __declspec(dllimport)
#endif

// 此类是从 LT_MusicTags.dll 导出的
class LT_MUSICTAGS_API CLT_MusicTags {
public:
	CLT_MusicTags(void);
	// TODO: 在此添加您的方法。
};

extern LT_MUSICTAGS_API int nLT_MusicTags;

LT_MUSICTAGS_API int fnLT_MusicTags(void);

extern "C" LT_MUSICTAGS_API bool GetMusicTilteAndArtist(DWORD,CString*,CString*);