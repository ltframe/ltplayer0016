#include "StdAfx.h"
#include "UIStaticEx.h"

UIStaticEx::UIStaticEx(WCHAR *img1) : UIStatic(img1)
{
}

UIStaticEx::~UIStaticEx(void)
{
}

void UIStaticEx::IPAINT(HDC& dc)
{
	if (!isshow)
	{
		return;
	}

	Drawimage.BitDrawStretchControl(m_pSrcImage1,dc,0,0,Gstaticinfo.width,Gstaticinfo.high,1);
}

void UIStaticEx::IPAINT2(HDC& dc)
{
	if (!isshow)
	{
		return;
	}
	Drawimage.BitDrawStretchControl(m_pSrcImage1,dc,0,0,Gstaticinfo.width,Gstaticinfo.high,2);
}