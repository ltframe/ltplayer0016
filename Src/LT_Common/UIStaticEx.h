#pragma once
#include "UIStatic.h"
class AFX_EXT_CLASS UIStaticEx : public UIStatic
{
public:
	UIStaticEx(WCHAR *img1);
	~UIStaticEx(void);
	void IPAINT(HDC&);
	void IPAINT2(HDC&);
};
