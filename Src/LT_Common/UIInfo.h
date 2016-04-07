#pragma once
#include "stdafx.h"
typedef struct tagUIButtonInfo 
{
	INT x;
	INT y;
	INT srcx;
	INT srcy;
	INT srcwidth;
	INT srcheight;
	Unit srcUnit;
	CString classname;
	RECT rect;
	int MouseType;
	BOOL allowmove;
	BOOL haswm;
	INT controltype;
	Bitmap * currentcontrolimage;
	Bitmap * controlimages1;
	Bitmap * controlimages2;
	CString currentcontrolname;
}UIButtonInfo;

typedef struct tagUISliderInfo
{

	CString classname;
	INT controltype;
	RECT rect;
	int MouseType;
	BOOL allowmove;
	BOOL haswm;
	BOOL moveimmediatelyresponse;

	CString image_i1;
	INT i1_x;
	INT i1_y;
	INT i1_srcx;
	INT i1_srcy;
	INT i1_srcwidth;
	INT i1_srcheight;
	INT i1_width;
	INT i1_height;
	Unit i1_srcUnit;

	CString image_i2;
	INT i2_x;
	INT i2_y;
	INT i2_srcx;
	INT i2_srcy;
	INT i2_srcwidth;
	INT i2_srcheight;
	INT i2_width;
	INT i2_height;
	Unit i2_srcUnit;

	CString image_i3;
	INT i3_x;
	INT i3_y;
	INT i3_srcx;
	INT i3_srcy;
	INT i3_srcwidth;
	INT i3_srcheight;
	INT i3_width;
	INT i3_height;
	Unit i3_srcUnit;

}UISliderInfo;


typedef struct tagUIListInfo
{
	CString classname;
	int listui_width;
	int listui_height;
	RECT listui_rect;
	int listui_x;
	int listui_y;
	int listui_offset;
	int MouseType;

	INT slideritem_width;
	INT slideritem_height;


	CString silderbar_image;
	CString sliderbar_gb;
	INT sliderbar_x;
	INT sliderbar_y;
	INT sliderbar_srcx;
	INT sliderbar_srcy;
	INT sliderbar_srcwidth;
	INT sliderbar_srcheight;
	INT sliderbar_width;
	INT sliderbar_height;
	RECT sliderbar_rect;

	CString slidertop_image;
	RECT slidertop_rect;
	CString sliderbelow_image;
	RECT sliderbelow_rect;
	float setpint;

	int file_height;
	RECT itemlistrect;

	Unit srcUnit;

	int textcolor;
	int choicetextcolor;
	int choicebgcolor;
	int fontsize;
}UIListInfo;

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


typedef struct tagUILableInfo 
{
	INT x;
	INT y;
	RECT rect;
	CString classname;
	int fontsize;
	COLORREF color;
	CString str;
	//int strwidth;
	INT width;
	int rollstep;
}UILableInfo;


typedef struct tagUIStatic
{
	INT x;
	INT y;
	RECT rect;
	CString classname;
	int width;
	int high;
}UIStaticInfo;


typedef struct tagScreenInfo
{
  int cx;
  int cy;
}ScreenInfo;