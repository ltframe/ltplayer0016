// ControlPanelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "shlwapi.h"
#include "ControlPanelDlg.h"
#ifndef PLAYERRUNTIMEVALUE
HSTREAM m_stream=0;
QWORD currentfileseconds;
//double sliderwidth;
#endif

// ControlPanelDlg 对话框
typedef bool (*DROPMYPROC)(HSTREAM,CString*,CString*);
IMPLEMENT_DYNAMIC(ControlPanelDlg, CDialog)
#define  EM(A) affect.AddString(CString(A))
ControlPanelDlg::ControlPanelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ControlPanelDlg::IDD, pParent),m_bMouseTracking(true),CurrentControlClassName(""),InitBitmap(307,595),PrintDCBitmap(0),percontrolnameid(-1),DestPt(0,0),blackBrush(Color(255, 0, 255)),islooplist(false),currentfilename(NULL),currentmusiclistindex(0)
{
	DlgStartEnd=false;
	musicnamelablerollflag=0;
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);      
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	APPPATH=szFilePath;
	//APPINI.AppendFormat(_T("%s%s"),APPPATH,CString("config.ini"));
	wchar_t * skinid =new wchar_t[MAX_PATH+1];
	wcscpy(skinid,MusicUtils::GetConfigXml(CString(L"skin"),L"1"));
	UiSkinInfo skininfo = MusicUtils::LSSkinInfo(skinid);
	
	CString css;
	css.Format(_T("%s\\skin\\%s\\%s"),APPPATH,skinid,skininfo.fname);
	currentfilename= (wchar_t*)malloc(_MAX_PATH+1);
	ZeroMemory(currentfilename,_MAX_PATH+1);

	currentshowfilename = (wchar_t*)malloc(_MAX_FNAME+1);
	ZeroMemory(currentfilename,_MAX_PATH+1);
	//CString css(_T("res\\bg1.png"));

	maskcolor=skininfo.maskcolor;


	delete skinid;

	bgbitmap=new Bitmap(css);


	controlclass=new ControlClass();
	imAtt.SetColorKey(Color(255, 0, 255),Color(255, 0, 255),ColorAdjustTypeDefault);
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 255;
	//Drawimage.LoadResImage(L"res\\nbg1.png",L"BG",image);
	RECT temprect={-1,-1,-1,-1};
	CurrentRect=temprect;

	//从配置文件载入窗口宽和高
	CArray<CString,CString&> wndsizearrays;
	MusicUtils::SpliteCString(MusicUtils::GetConfigXml(L"wndsize",L"1"),wndsizearrays,L",");
	MAINBG_WIDTH=_wtoi(wndsizearrays[0]);
	MAINBG_HEIGHT=_wtoi(wndsizearrays[1]);
	
	int conrolmiddle =ceil((double)(MAINBG_WIDTH/2));

	musiclogo=new UIStatic(L"res\\logo.png");
	musiclogo->Gstaticinfo.x=15;
	musiclogo->Gstaticinfo.y=10;
	musiclogo->Gstaticinfo.width=97;
	musiclogo->Gstaticinfo.high=30;
	musiclogo->Gstaticinfo.rect=controlclass->GetRect(musiclogo->Gstaticinfo.x,musiclogo->Gstaticinfo.y,musiclogo->Gstaticinfo.width,musiclogo->Gstaticinfo.high);
	musiclogo->Gstaticinfo.classname="musiclogo";

	playbutton=new UIButton(L"res\\play.png",L"res\\stop.png");
	playbutton->Gbuttoninfo.srcwidth=38;
	playbutton->Gbuttoninfo.x=conrolmiddle-(playbutton->Gbuttoninfo.srcwidth/2);
	playbutton->Gbuttoninfo.y=180;
	playbutton->Gbuttoninfo.srcx=0;
	playbutton->Gbuttoninfo.srcy=0;
	
	playbutton->Gbuttoninfo.srcheight=38;
	playbutton->Gbuttoninfo.srcUnit=(Unit)2;
	playbutton->Gbuttoninfo.classname="playbutton";
	//playbutton->Gbuttoninfo.controlimages1=;
	//playbutton->Gbuttoninfo.currentcontrolimage="res\\play.png";
	//playbutton->Gbuttoninfo.controlimages2=;
	playbutton->Gbuttoninfo.controltype=CUI_BUTTON;
	playbutton->Gbuttoninfo.MouseType=0;
	playbutton->Gbuttoninfo.haswm=true;
	playbutton->tipstr=L"播放";
	playbutton->Gbuttoninfo.rect=controlclass->GetRect(playbutton->Gbuttoninfo.x,playbutton->Gbuttoninfo.y,playbutton->Gbuttoninfo.srcwidth,playbutton->Gbuttoninfo.srcheight);



	perbutton=new UIButton(L"res\\per.png");
	perbutton->Gbuttoninfo.srcwidth=35;
	perbutton->Gbuttoninfo.x=playbutton->Gbuttoninfo.x-PLAYERCONTROL_BETWEEN_WIDTH-perbutton->Gbuttoninfo.srcwidth;
	perbutton->Gbuttoninfo.y=181;
	perbutton->Gbuttoninfo.srcx=0;
	perbutton->Gbuttoninfo.srcy=0;
	perbutton->Gbuttoninfo.srcheight=36;
	perbutton->Gbuttoninfo.srcUnit=(Unit)2;
	perbutton->Gbuttoninfo.classname="perbutton";
	//perbutton->Gbuttoninfo.controlimages1="res\\per.png";
	//perbutton->Gbuttoninfo.currentcontrolimage="res\\per.png";
	//perbutton->Gbuttoninfo.controlimages2="res\\per.png";
	perbutton->Gbuttoninfo.controltype=CUI_BUTTON;
	perbutton->Gbuttoninfo.MouseType=0;
	perbutton->Gbuttoninfo.haswm=true;
	perbutton->tipstr=L"前一首";
	perbutton->Gbuttoninfo.rect=controlclass->GetRect(perbutton->Gbuttoninfo.x,perbutton->Gbuttoninfo.y,perbutton->Gbuttoninfo.srcwidth,perbutton->Gbuttoninfo.srcheight);


	nextbutton=new UIButton(L"res\\next.png");
	nextbutton->Gbuttoninfo.x=playbutton->Gbuttoninfo.x+ playbutton->Gbuttoninfo.srcwidth+PLAYERCONTROL_BETWEEN_WIDTH;
	nextbutton->Gbuttoninfo.y=181;
	nextbutton->Gbuttoninfo.srcx=0;
	nextbutton->Gbuttoninfo.srcy=0;
	nextbutton->Gbuttoninfo.srcwidth=35;
	nextbutton->Gbuttoninfo.srcheight=36;
	nextbutton->Gbuttoninfo.srcUnit=(Unit)2;
	nextbutton->Gbuttoninfo.classname="nextbutton";
	//nextbutton->Gbuttoninfo.controlimages1="res\\next.png";
	//nextbutton->Gbuttoninfo.currentcontrolimage="res\\next.png";
	//nextbutton->Gbuttoninfo.controlimages2="res\\next.png";
	nextbutton->Gbuttoninfo.controltype=CUI_BUTTON;
	nextbutton->Gbuttoninfo.MouseType=0;
	nextbutton->Gbuttoninfo.haswm=true;
	nextbutton->tipstr=L"下一首";
	nextbutton->Gbuttoninfo.rect=controlclass->GetRect(nextbutton->Gbuttoninfo.x,nextbutton->Gbuttoninfo.y,nextbutton->Gbuttoninfo.srcwidth,nextbutton->Gbuttoninfo.srcheight);



	closebutton=new UIButton(L"res\\close.png");
	closebutton->Gbuttoninfo.srcwidth=33;
	closebutton->Gbuttoninfo.x=MAINBG_WIDTH-closebutton->Gbuttoninfo.srcwidth;
	closebutton->Gbuttoninfo.y=0;
	closebutton->Gbuttoninfo.srcx=0;
	closebutton->Gbuttoninfo.srcy=0;
	
	closebutton->Gbuttoninfo.srcheight=25;
	closebutton->Gbuttoninfo.srcUnit=(Unit)2;
	closebutton->Gbuttoninfo.classname="closebutton";
	//closebutton->Gbuttoninfo.controlimages1="res\\close.png";
	//closebutton->Gbuttoninfo.currentcontrolimage="res\\close.png";
	//closebutton->Gbuttoninfo.controlimages2="res\\close.png";
	closebutton->Gbuttoninfo.controltype=CUI_BUTTON;
	closebutton->Gbuttoninfo.MouseType=0;
	closebutton->Gbuttoninfo.haswm=true;
	closebutton->tipstr=L"关闭";
	closebutton->Gbuttoninfo.rect=controlclass->GetRect(closebutton->Gbuttoninfo.x,closebutton->Gbuttoninfo.y,closebutton->Gbuttoninfo.srcwidth,closebutton->Gbuttoninfo.srcheight);


	minbutton=new UIButton(L"res\\min.png");
	minbutton->Gbuttoninfo.srcheight=25;
	minbutton->Gbuttoninfo.srcwidth=31;
	minbutton->Gbuttoninfo.x=closebutton->Gbuttoninfo.x -minbutton->Gbuttoninfo.srcwidth;
	minbutton->Gbuttoninfo.y=0;
	minbutton->Gbuttoninfo.srcx=0;
	minbutton->Gbuttoninfo.srcy=0;	
	minbutton->Gbuttoninfo.srcUnit=(Unit)2;
	minbutton->Gbuttoninfo.classname="minbutton";
	minbutton->Gbuttoninfo.controltype=CUI_BUTTON;
	minbutton->Gbuttoninfo.MouseType=0;
	minbutton->Gbuttoninfo.haswm=true;
	minbutton->tipstr=L"最小化";
	minbutton->Gbuttoninfo.rect=controlclass->GetRect(minbutton->Gbuttoninfo.x,minbutton->Gbuttoninfo.y,minbutton->Gbuttoninfo.srcwidth,minbutton->Gbuttoninfo.srcheight);
	


	skinbutton=new UIButton(L"res\\skin.png");
	skinbutton->Gbuttoninfo.x=27;
	skinbutton->Gbuttoninfo.y=199;
	skinbutton->Gbuttoninfo.srcx=0;
	skinbutton->Gbuttoninfo.srcy=0;
	skinbutton->Gbuttoninfo.srcwidth=21;
	skinbutton->Gbuttoninfo.srcheight=14;
	skinbutton->Gbuttoninfo.srcUnit=(Unit)2;
	skinbutton->Gbuttoninfo.classname="skinbutton";
	skinbutton->Gbuttoninfo.controltype=CUI_BUTTON;
	skinbutton->Gbuttoninfo.MouseType=0;
	skinbutton->Gbuttoninfo.haswm=true;
	skinbutton->tipstr=L"换肤";
	skinbutton->Gbuttoninfo.rect=controlclass->GetRect(skinbutton->Gbuttoninfo.x,skinbutton->Gbuttoninfo.y,skinbutton->Gbuttoninfo.srcwidth,skinbutton->Gbuttoninfo.srcheight);





	addbutton=new UIButton(L"res\\add.png");
	addbutton->Gbuttoninfo.x=SETTING_X;
	addbutton->Gbuttoninfo.y=MAINBG_HEIGHT-27;
	addbutton->Gbuttoninfo.srcx=0;
	addbutton->Gbuttoninfo.srcy=0;
	addbutton->Gbuttoninfo.srcwidth=23;
	addbutton->Gbuttoninfo.srcheight=23;
	addbutton->Gbuttoninfo.srcUnit=(Unit)2;
	addbutton->Gbuttoninfo.classname="addbutton";
	//addbutton->Gbuttoninfo.controlimages1="res\\add.png";
	//addbutton->Gbuttoninfo.currentcontrolimage="res\\add.png";
	//addbutton->Gbuttoninfo.controlimages2="res\\add.png";
	addbutton->Gbuttoninfo.controltype=CUI_BUTTON;
	addbutton->Gbuttoninfo.MouseType=0;
	addbutton->Gbuttoninfo.haswm=true;
	addbutton->tipstr=L"添加歌曲";
	addbutton->Gbuttoninfo.rect=controlclass->GetRect(addbutton->Gbuttoninfo.x,addbutton->Gbuttoninfo.y,addbutton->Gbuttoninfo.srcwidth,addbutton->Gbuttoninfo.srcheight);


	optionsbutton=new UIButton(L"res\\options.png");
	optionsbutton->Gbuttoninfo.srcwidth=23;
	optionsbutton->Gbuttoninfo.x=MAINBG_WIDTH-72;
	optionsbutton->Gbuttoninfo.y=MAINBG_HEIGHT-27;
	optionsbutton->Gbuttoninfo.srcx=0;
	optionsbutton->Gbuttoninfo.srcy=0;
	
	optionsbutton->Gbuttoninfo.srcheight=23;
	optionsbutton->Gbuttoninfo.srcUnit=(Unit)2;
	optionsbutton->Gbuttoninfo.classname="optionsbutton";
	//addbutton->Gbuttoninfo.controlimages1="res\\add.png";
	//addbutton->Gbuttoninfo.currentcontrolimage="res\\add.png";
	//addbutton->Gbuttoninfo.controlimages2="res\\add.png";
	optionsbutton->Gbuttoninfo.controltype=CUI_BUTTON;
	optionsbutton->Gbuttoninfo.MouseType=0;
	optionsbutton->Gbuttoninfo.haswm=true;
	optionsbutton->tipstr=L"播放器设置";
	optionsbutton->Gbuttoninfo.rect=controlclass->GetRect(optionsbutton->Gbuttoninfo.x,optionsbutton->Gbuttoninfo.y,optionsbutton->Gbuttoninfo.srcwidth,optionsbutton->Gbuttoninfo.srcheight);

	int bottom3ave = ceil((double)((MAINBG_WIDTH-120)/3));
	listxhbutton=new UIButton(L"res\\listxh1.png",L"res\\listxh.png");
	listxhbutton->Gbuttoninfo.x=SETTING_ONELAST_CX+bottom3ave-SETTINGHALF_CX;
	listxhbutton->Gbuttoninfo.y=MAINBG_HEIGHT-27;
	listxhbutton->Gbuttoninfo.srcx=0;
	listxhbutton->Gbuttoninfo.srcy=0;
	listxhbutton->Gbuttoninfo.srcwidth=23;
	listxhbutton->Gbuttoninfo.srcheight=23;
	listxhbutton->Gbuttoninfo.srcUnit=(Unit)2;
	listxhbutton->Gbuttoninfo.classname="listxhbutton";
	//listxhbutton->Gbuttoninfo.controlimages1="res\\listxh1.png";
	//listxhbutton->Gbuttoninfo.currentcontrolimage="res\\listxh1.png";
	//listxhbutton->Gbuttoninfo.controlimages2="res\\listxh.png";
	listxhbutton->Gbuttoninfo.controltype=CUI_BUTTON;
	listxhbutton->Gbuttoninfo.MouseType=0;
	listxhbutton->Gbuttoninfo.haswm=true;
	listxhbutton->tipstr=L"列表循环";
	listxhbutton->Gbuttoninfo.rect=controlclass->GetRect(listxhbutton->Gbuttoninfo.x,listxhbutton->Gbuttoninfo.y,listxhbutton->Gbuttoninfo.srcwidth,listxhbutton->Gbuttoninfo.srcheight);
	if (MusicUtils::GetConfigXml(L"loop",L"1")=="2")
	{
		islooplist=true;
		listxhbutton->Gbuttoninfo.currentcontrolimage=listxhbutton->Gbuttoninfo.controlimages2;
	}
	

	setbutton=new UIButton(L"res\\set.png");
	setbutton->Gbuttoninfo.x=listxhbutton->Gbuttoninfo.x+bottom3ave;
	setbutton->Gbuttoninfo.y=MAINBG_HEIGHT-27;
	setbutton->Gbuttoninfo.srcx=0;
	setbutton->Gbuttoninfo.srcy=0;
	setbutton->Gbuttoninfo.srcwidth=23;
	setbutton->Gbuttoninfo.srcheight=23;
	setbutton->Gbuttoninfo.srcUnit=(Unit)2;
	setbutton->Gbuttoninfo.classname="setbutton";
	//setbutton->Gbuttoninfo.controlimages1="res\\set.png";
	//setbutton->Gbuttoninfo.currentcontrolimage="res\\set.png";
	//setbutton->Gbuttoninfo.controlimages2="res\\set.png";
	setbutton->Gbuttoninfo.controltype=CUI_BUTTON;
	setbutton->Gbuttoninfo.MouseType=0;
	setbutton->Gbuttoninfo.haswm=true;
	setbutton->tipstr=L"清除列表";
	setbutton->Gbuttoninfo.rect=controlclass->GetRect(setbutton->Gbuttoninfo.x,setbutton->Gbuttoninfo.y,setbutton->Gbuttoninfo.srcwidth,setbutton->Gbuttoninfo.srcheight);

//L"res\\progress_thumb.png"64
	positionslider=new UISlider(L"res\\slider_bar.png",L"res\\progress_fill.png",NULL);
	positionslider->Gsliderinfo.classname="positionslider";
	positionslider->Gsliderinfo.moveimmediatelyresponse=false;
	positionslider->Gsliderinfo.i1_x=64;
	positionslider->Gsliderinfo.i1_width=MAINBG_WIDTH-(POSITIONSLIDER_LR_CX*2);

	positionslider->Gsliderinfo.i1_y=163;
	positionslider->Gsliderinfo.i1_srcx=0;
	positionslider->Gsliderinfo.i1_srcy=0;
	positionslider->Gsliderinfo.i1_srcwidth=181;
	positionslider->Gsliderinfo.i1_srcheight=16;
	
	positionslider->Gsliderinfo.i1_height=16;
	positionslider->Gsliderinfo.i1_srcUnit=(Unit)2;

	positionslider->Gsliderinfo.i2_x=0;
	positionslider->Gsliderinfo.i2_y=3;
	positionslider->Gsliderinfo.i2_srcx=0;
	positionslider->Gsliderinfo.i2_srcy=0;
	positionslider->Gsliderinfo.i2_srcwidth=181;
	positionslider->Gsliderinfo.i2_srcheight=10;
	positionslider->Gsliderinfo.i2_width=0;
	positionslider->Gsliderinfo.i2_height=10;
	positionslider->Gsliderinfo.i2_srcUnit=(Unit)2;

	positionslider->Gsliderinfo.i3_x=30;
	positionslider->Gsliderinfo.i3_y=0;
	positionslider->Gsliderinfo.i3_srcx=0;
	positionslider->Gsliderinfo.i3_srcy=0;
	positionslider->Gsliderinfo.i3_srcwidth=16;
	positionslider->Gsliderinfo.i3_srcheight=16;
	positionslider->Gsliderinfo.i3_width=16;
	positionslider->Gsliderinfo.i3_height=16;
	positionslider->Gsliderinfo.i3_srcUnit=(Unit)2;
	positionslider->Gsliderinfo.rect=controlclass->GetRect(positionslider->Gsliderinfo.i1_x,positionslider->Gsliderinfo.i1_y,positionslider->Gsliderinfo.i1_width,positionslider->Gsliderinfo.i1_srcheight);
	
	
	volumeslider=new UISlider(L"res\\vol_slider_bar.png",NULL,L"res\\vol_progress_thumb.png");
	volumeslider->Gsliderinfo.moveimmediatelyresponse=true;
	volumeslider->Gsliderinfo.classname="volumeslider";
	volumeslider->Gsliderinfo.i1_width=41;
	volumeslider->Gsliderinfo.i1_x=MAINBG_WIDTH-VOLUMESLIDER_RIGHT_CX-volumeslider->Gsliderinfo.i1_width;
	volumeslider->Gsliderinfo.i1_y=202;
	volumeslider->Gsliderinfo.i1_srcx=0;
	volumeslider->Gsliderinfo.i1_srcy=0;
	volumeslider->Gsliderinfo.i1_srcwidth=41;
	volumeslider->Gsliderinfo.i1_srcheight=8;
	
	volumeslider->Gsliderinfo.i1_height=8;
	volumeslider->Gsliderinfo.i1_srcUnit=(Unit)2;

	volumeslider->Gsliderinfo.i2_x=0;
	volumeslider->Gsliderinfo.i2_y=0;
	volumeslider->Gsliderinfo.i2_srcx=0;
	volumeslider->Gsliderinfo.i2_srcy=0;
	volumeslider->Gsliderinfo.i2_srcwidth=41;
	volumeslider->Gsliderinfo.i2_srcheight=8;
	volumeslider->Gsliderinfo.i2_width=41;
	volumeslider->Gsliderinfo.i2_height=8;
	volumeslider->Gsliderinfo.i2_srcUnit=(Unit)2;

	volumeslider->Gsliderinfo.i3_x=0;
	volumeslider->Gsliderinfo.i3_y=0;
	volumeslider->Gsliderinfo.i3_srcx=0;
	volumeslider->Gsliderinfo.i3_srcy=0;
	volumeslider->Gsliderinfo.i3_srcwidth=4;
	volumeslider->Gsliderinfo.i3_srcheight=8;
	volumeslider->Gsliderinfo.i3_width=4;
	volumeslider->Gsliderinfo.i3_height=8;
	volumeslider->Gsliderinfo.i3_srcUnit=(Unit)2;
	volumeslider->Gsliderinfo.rect=controlclass->GetRect(volumeslider->Gsliderinfo.i1_x,volumeslider->Gsliderinfo.i1_y,volumeslider->Gsliderinfo.i1_srcwidth,volumeslider->Gsliderinfo.i1_srcheight);	

	volumeico=new UIButton(L"res\\volumeico1.png",L"res\\volumeico2.png");
	volumeico->Gbuttoninfo.srcwidth=15;
	volumeico->Gbuttoninfo.x=volumeslider->Gsliderinfo.i1_x-VOLUMESLIDER_LEFT_CX-volumeico->Gbuttoninfo.srcwidth;
	volumeico->Gbuttoninfo.y=199;
	volumeico->Gbuttoninfo.srcx=0;
	volumeico->Gbuttoninfo.srcy=0;
	
	volumeico->Gbuttoninfo.srcheight=14;
	volumeico->Gbuttoninfo.srcUnit=(Unit)2;
	volumeico->Gbuttoninfo.classname="volumeico";
	volumeico->Gbuttoninfo.controltype=CUI_BUTTON;
	volumeico->Gbuttoninfo.MouseType=0;
	volumeico->Gbuttoninfo.haswm=true;
	volumeico->Gbuttoninfo.rect=controlclass->GetRect(volumeico->Gbuttoninfo.x,volumeico->Gbuttoninfo.y,volumeico->Gbuttoninfo.srcwidth,volumeico->Gbuttoninfo.srcheight);

	
	musiclist=new UIList(L"res\\listbar.png",L"res\\line.png",L"res\\listbar.png");
	musiclist->Glistinfo.classname="musiclist";
	musiclist->Glistinfo.listui_height=MAINBG_HEIGHT-220-34;
	/*musiclist->Glistinfo.listui_height=334;*/
	musiclist->Glistinfo.listui_width=MAINBG_WIDTH;
	musiclist->Glistinfo.listui_x=0;
	musiclist->Glistinfo.listui_y=223;
	musiclist->Glistinfo.listui_offset=0;
	musiclist->Glistinfo.sliderbar_width=9;
	musiclist->Glistinfo.sliderbar_height=75;
	musiclist->Glistinfo.sliderbar_y=0;
	musiclist->Glistinfo.sliderbar_x=MAINBG_WIDTH - musiclist->Glistinfo.sliderbar_width;
	musiclist->Glistinfo.sliderbar_rect=controlclass->GetListBarRect(0,0,0,0);
	musiclist->Glistinfo.file_height=17;
	musiclist->Glistinfo.textcolor = RGB(81,81,81);
	musiclist->Glistinfo.choicebgcolor = RGB(191,191,191);
	musiclist->Glistinfo.choicetextcolor = RGB(255,255,255);
	musiclist->Glistinfo.fontsize = 14;
	musiclist->Glistinfo.listui_rect=controlclass->GetRect(musiclist->Glistinfo.listui_x,musiclist->Glistinfo.listui_y,musiclist->Glistinfo.listui_width,musiclist->Glistinfo.listui_height);
	//AddControlToArray(musiclist);


	//歌曲总时间
	musictimelable=new UILable();
	musictimelable->Glableinfo.classname="musictimelable";
	musictimelable->Glableinfo.str="00:00";
	musictimelable->Glableinfo.fontsize =14;
	musictimelable->Glableinfo.color = RGB(255,255,255);
	musictimelable->Glableinfo.x=positionslider->Gsliderinfo.i1_x+positionslider->Gsliderinfo.i1_width+5;;
	musictimelable->Glableinfo.y=164;
	musictimelable->Glableinfo.width=34;
	musictimelable->Glableinfo.rollstep=0;
	musictimelable->Glableinfo.rect=controlclass->GetRect(musictimelable->Glableinfo.x,musictimelable->Glableinfo.y,musictimelable->Glableinfo.width,15);

    //当前歌曲时间
	musictimeclable=new UILable();
	musictimeclable->Glableinfo.classname="musictimelable";
	musictimeclable->Glableinfo.str="00:00";
	musictimeclable->Glableinfo.x=positionslider->Gsliderinfo.i1_x - 40;;
	musictimeclable->Glableinfo.y=164;
	musictimeclable->Glableinfo.fontsize =14;
	musictimeclable->Glableinfo.color = RGB(255,255,255);
	musictimeclable->Glableinfo.width=34;
	musictimeclable->Glableinfo.rollstep=0;
	musictimeclable->Glableinfo.rect=controlclass->GetRect(musictimeclable->Glableinfo.x,musictimeclable->Glableinfo.y,musictimeclable->Glableinfo.width,15);

	musicnamelable=new UILable();
	musicnamelable->Glableinfo.classname="musicnamelable";
	musicnamelable->Glableinfo.str=L"";
	musicnamelable->Glableinfo.x=19;
	musicnamelable->Glableinfo.y=45;
	musicnamelable->Glableinfo.width=0;
	musicnamelable->Glableinfo.rollstep=0;
	musicnamelable->Glableinfo.fontsize =14;
	musicnamelable->Glableinfo.color = RGB(255,255,255);
	musicnamelable->Glableinfo.rect=controlclass->GetRect(musicnamelable->Glableinfo.x,musicnamelable->Glableinfo.y,musicnamelable->Glableinfo.width,15);
}
ControlPanelDlg::~ControlPanelDlg()
{
	BASS_Free();
	CString cs;
	cs.Format(_T("%d,%d"),MAINBG_WIDTH,MAINBG_HEIGHT);
	if(canvar->ISDLGALPHA){
		cs.Format(_T("%d,%d"),MAINBG_WIDTH-10,MAINBG_HEIGHT-10);
	}

	MusicUtils::WriteConfigXml(_T("wndsize"),cs,"SetPlayerConfigValue");
	MusicUtils::WriteConfigXml(_T("loop"),MusicUtils::ConverI2W(islooplist?2:1),"SetPlayerConfigValue");
	MusicUtils::WriteConfigXml(_T("mute"),MusicUtils::ConverI2W((volumeico->GetButtonImg()==1)?1:2),"SetPlayerConfigValue");
	MusicUtils::WriteConfigXml(_T("volume"),MusicUtils::ConverI2W(volumeslider->Gsliderinfo.i3_x),"SetPlayerConfigValue");
	MusicUtils::WriteConfigXml(_T("lastplayfile"),CString(currentfilename),"SetPlayerConfigValue");

}

void ControlPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ControlPanelDlg, CDialog)
//	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_COPYDATA()
	ON_MESSAGE(WM_MYMUSICPLAY_MESSAGE,OnUserSelfMessageMusicPlay)
	ON_MESSAGE(WM_MYMUSICTIMES_MESSAGE,OnUserSelfMessageMusicTimes)
	ON_MESSAGE(WM_MYMOVE_MESSAGE,OnUserSelfMessage)
	ON_MESSAGE(WM_MYMUSICNAME_MESSAGE,OnUserSelfMessageMusicName)
	ON_MESSAGE(WM_MYMUSICVOL_MESSAGE,OnUserSelfMessageMusicVoL)
	ON_MESSAGE(WM_LAYERPAINT_MESSAGE,OnLayerPaintMessage)
	ON_MESSAGE(WM_MYCLOSEWINDOW_MESSAGE,OnUserSelfMessageNOTIFY)
	ON_COMMAND(IDR_MYSETTING_MESSAGE,OnUserSelfMessageSetting)
	ON_COMMAND(IDR_MYWEBSITE_MESSAGE,OnUserSelfMessageWebSite)
	ON_COMMAND(IDR_MYCLOSE_MESSAGE,OnUserSelfMessageClose)
	ON_MESSAGE(WM_STARTRUNOPENFILE_MESSAGE,OnStartOpenFile)
	ON_MESSAGE(WM_SETMUSIC3D_MESSAGE,SetMusic3D)
	ON_MESSAGE(WM_ACTIVATE_MESSAGE,EnableBgAlpha)
	ON_MESSAGE(WM_ONSETBGIMG_MESSAGE,OnSetBgImg)
	ON_MESSAGE(WM_ONSETBGALPHA_MESSAGE,OnSetBgAlpha)
	ON_WM_DROPFILES()
	ON_WM_NCHITTEST()
	ON_WM_SIZE() 
	ON_WM_MOVE()
	ON_WM_NCLBUTTONDOWN()
//	ON_WM_SIZING()
	ON_WM_GETMINMAXINFO()
//	ON_WM_CREATE()
END_MESSAGE_MAP()


// ControlPanelDlg 消息处理程序

BOOL ControlPanelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	this->SetWindowText(_T("静静聆听播放器"));

	controlevent=new ControlEvent(NULL,m_hWnd);
	controlevent->ShowNotifyIcon(this->m_hWnd);

	playbutton->IEVENTADD(this);
	perbutton->IEVENTADD(this);
	closebutton->IEVENTADD(this);
	minbutton->IEVENTADD(this);
	positionslider->IEVENTADD(this);
	nextbutton->IEVENTADD(this);

	volumeico->IEVENTADD(this);
	addbutton->IEVENTADD(this);
	listxhbutton->IEVENTADD(this);
	setbutton->IEVENTADD(this);
	volumeslider->IEVENTADD(this);
	musiclist->IEVENTADD(this);
	
	optionsbutton->IEVENTADD(this);
	skinbutton->IEVENTADD(this);

	CClientDC *dc=new CClientDC(this);
    canvar=new UICanvar(this->m_hWnd);
	canvar->BGMASKCOLOR=maskcolor;	


	canvar->MAINBG_HEIGHT=MAINBG_HEIGHT;
	canvar->MAINBG_WIDTH=MAINBG_WIDTH;
	int entransparent = _wtoi(MusicUtils::GetConfigXml(L"entransparent",L"1"));
	if(entransparent){
		MAINBG_WIDTH+=10;
		MAINBG_HEIGHT+=10;
		canvar->MAINBG_WIDTH=MAINBG_WIDTH;
		canvar->MAINBG_HEIGHT=MAINBG_HEIGHT;
		currenttransparent = _wtoi(MusicUtils::GetConfigXml(L"transparent",L"1"));
	}

	canvar->ISDLGALPHA=entransparent;
	if (canvar->ISDLGALPHA)
	{
		ModifyStyleEx(0,WS_EX_LAYERED);
	}
	
	canvar->BgSrcImg=bgbitmap;
	canvar->BgSourceConstantAlpha=currenttransparent;
	LoadMusicList();
	if (canvar->ISDLGALPHA)
	{
		ResetControlsXY(0);
		ResetMMCRegion(10);
		ResetPlayRegion(10);
		ResetControlRegion(10);
		ResetMucisNameLable(10);
		ResetSpecificControlRect(10);


	}
	
	canvar->AddControlToCanvar(volumeslider);
    canvar->AddControlToCanvar(positionslider);
	canvar->AddControlToCanvar(closebutton);
	canvar->AddControlToCanvar(addbutton);
	canvar->AddControlToCanvar(listxhbutton);
	canvar->AddControlToCanvar(setbutton);
	canvar->AddControlToCanvar(optionsbutton);
	canvar->AddControlToCanvar(minbutton);
	canvar->AddControlToCanvar(playbutton);
	canvar->AddControlToCanvar(nextbutton);
	canvar->AddControlToCanvar(perbutton);
	
	canvar->AddControlToCanvar(volumeico);
	canvar->AddControlToCanvar(musiclogo);
	canvar->AddControlToCanvar(skinbutton);	
	canvar->AddControlToCanvar(musictimeclable);
	canvar->AddControlToCanvar(musictimelable);
	canvar->AddControlToCanvar(musicnamelable);
	canvar->AddControlToCanvar(musiclist);
	//
	
	

	volumeslider->Gsliderinfo.i3_x=_wtoi(MusicUtils::GetConfigXml(L"volume",L"0"));;
	if (MusicUtils::GetConfigXml(L"mute",L"1")=="2")
	{
		volumeico->Gbuttoninfo.currentcontrolimage=volumeico->Gbuttoninfo.controlimages2;
		controlevent->volumstatus=0;
	}
	
	positionslider->SetSingleControl(dc->m_hDC,3,3);
	volumeslider->SetSingleControl(dc->m_hDC);


	/////////////////音乐播放相关/////////////////////
	BASS_Init(-1,44100,0,this->m_hWnd,NULL);
	BASS_PluginLoad("basswma.dll", 0);
	BASS_PluginLoad("bassflac.dll", 0);
	BASS_PluginLoad("bass_aac.dll",0);
	BASS_PluginLoad("bass_ape.dll",0);
		if (_wtoi(MusicUtils::GetConfigXml(L"autoplay",L"0")))
	{
		AutoPlay();
	}
		canvar->OnInit(dc);
	DlgStartEnd=true;
	::PostMessage(this->m_hWnd,WM_MYCLOSEWINDOW_MESSAGE,NULL,NULL);
	//////////////////////////////////////
	
	//CCommandLineInfo *cmdInfo=new CCommandLineInfo;
	/*MessageBox(AfxGetApp()->m_pCmdInfo->m_strFileName);*/

	return TRUE;  
}

void ControlPanelDlg::Add2MusicList(CString name)
{
	FileListInfo fileinfo;

	fileinfo.filepath=name;
	int tpathindex=fileinfo.filepath.ReverseFind('\\');
	CString tcstring=MusicUtils::GetMusicName(MusicUtils::GetSubString(fileinfo.filepath,tpathindex));
	fileinfo.filename=tcstring;
	musiclist->filelistarray->Add(fileinfo);
	musiclist->SetListValue();
	musiclist->GetSliderBarHeight();
	MusicUtils::LSMusicList(0,musiclist->filelistarray);
	musiclist->isshow=true;
	networkmusiclist->isshow=false;
	canvar->UpdateCanvar(musiclist);
	canvar->UpdateCanvar(networkmusiclist);
}

void ControlPanelDlg::OnPaint()
{
	RECT rect;
	GetUpdateRect(&rect,0);
	CPaintDC *dc=new CPaintDC(this);
	//ModifyStyleEx(0,WS_EX_LAYERED);
	canvar->Paint(dc,rect);
	delete dc;

}
void ControlPanelDlg::OnMouseHover(UINT nFlags, CPoint point)
{
	canvar->MouseHover(point);
}

void ControlPanelDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	canvar->MouseMove(point);

}
void ControlPanelDlg::OnMouseLeave()
{
	canvar->MouseLeave();
	
}

void ControlPanelDlg::OnLButtonDown(UINT nFlags, CPoint point)
{

	canvar->LButtonDown(point);
}

void ControlPanelDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{

	canvar->LBUTTONDBCLICK(this->m_hWnd,point);
}

void ControlPanelDlg::OnLButtonUp(UINT nFlags, CPoint point)
{

	canvar->LButtonUp(point);
}

BOOL ControlPanelDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

LRESULT ControlPanelDlg::OnUserSelfMessage(WPARAM wParam, LPARAM lParam)
{

	return 1;
}

LRESULT ControlPanelDlg::OnUserSelfMessageNOTIFY(WPARAM wParam, LPARAM lParam)
{
	if(wParam!=IDR_MAINFRAME)
		return 1;

	
		switch(lParam)
		{
			case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”
				{
					controlevent->ShowCMenu(this);
				}
				break;
			case WM_LBUTTONDBLCLK://双击左键的处理
				{
					controlevent->ShowPlayer(this->m_hWnd,AfxGetMainWnd()->m_hWnd,SW_SHOW);
					minbutton->Gbuttoninfo.srcx=0;
					canvar->UpdateCanvar(minbutton);
					canvar->UpdateCanvar(musiclist);
					canvar->UpdateCanvar(musicnamelable);
				}
				break;
			default:
				break;
		}
	return 1;
}
void ControlPanelDlg::OnTimer(UINT_PTR nIDEvent)
{

	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent==MUSIC_TIMER)
	{

			QWORD  qword = BASS_ChannelGetPosition(m_stream,BASS_POS_BYTE);
			double s = BASS_ChannelBytes2Seconds(m_stream,qword);
			double i= MusicUtils::SetMusicPositionUseSeconds(currentfileseconds,positionslider->Gsliderinfo.i1_width,s);
			//if(i<=19)
			//{
				//i+=19;
			/*}*/
			if (m_stream!=0 && BASS_ChannelIsActive(m_stream)==BASS_ACTIVE_STOPPED)
			{
				playbutton->Gbuttoninfo.srcx=0;
				playbutton->Gbuttoninfo.currentcontrolimage=playbutton->Gbuttoninfo.controlimages1;
				//canvar->Add2PaintQueue(playbutton);
				canvar->UpdateCanvar(playbutton);
				MusicStop();
				if (islooplist)
				{	
					int lastindex=0;
					int musiccount=musiclist->GetListCount();
					if (currentmusiclistindex+1<musiccount)
					{
						lastindex=currentmusiclistindex+1;
					}
					//wchar_t *k = musiclist->filelistarray->GetAt(lastindex).filepath.GetBuffer();
					//char *a = MusicUtils::WideCharToMultiChar(k);
					this->currentfilename=musiclist->filelistarray->GetAt(lastindex).filepath.GetBuffer();
					currentshowfilename=musiclist->filelistarray->GetAt(lastindex).filename.GetBuffer();
					currentmusiclistindex=lastindex;	
					musicnamelable->Glableinfo.str=currentshowfilename;
					canvar->UpdateCanvar(musicnamelable);
					//canvar->Add2PaintQueue(musicnamelable);
					musiclist->SetFileIndex(this->m_hWnd,currentmusiclistindex);
					//canvar->Add2PaintQueue(musiclist);
					canvar->UpdateCanvar(musiclist);
					playbutton->Gbuttoninfo.srcx=0;
					playbutton->Gbuttoninfo.currentcontrolimage=playbutton->Gbuttoninfo.controlimages2;
					//canvar->Add2PaintQueue(playbutton);
					canvar->UpdateCanvar(playbutton);
					MusicPlay();
					
				}
				return;
				//else
				//{
				//	return;
				//}

		}
			if (canvar->m_bMouseTracking && nIDEvent==MUSIC_TIMER)
			{
			PlayeTimerStatus(i,s);
			}

			CDialog::OnTimer(nIDEvent);
	}

	if (nIDEvent==MUSIC_TIMER_NAME_ROLL)
	{
		//musicnamelable->Glableinfo.rollstep=musicnamelable->Glableinfo.rollstep+1;

		if (musicnamelable->Glableinfo.rollstep<=musicnamelable->GetStrWidht()-musicnamelable->IWIDTH() && musicnamelablerollflag==0)
		{
			musicnamelable->Glableinfo.rollstep++;
		}else
		{	
			//MusicUtils::ConsoleWrite(MusicUtils::IntFormatCString(CString("鼠标wowow值"),currentpoint.x));
			musicnamelablerollflag=1;
			musicnamelable->Glableinfo.rollstep--;
			if (musicnamelable->Glableinfo.rollstep==0)
			{
				musicnamelablerollflag=0;
			}
		}
		canvar->UpdateCanvar(musicnamelable);
		CDialog::OnTimer(nIDEvent);
	}
}
////播放器设置按钮事件
void ControlPanelDlg::OnUserSelfMessageSetting()
{
	CMyPropertySheet myps(_T("播放器设置"),this,0);
	myps.m_psh.dwFlags   =   (myps.m_psh.dwFlags)   |   PSH_NOAPPLYNOW   ; 
	myps.m_psh.dwFlags   |=   PSH_HASHELP; 
	myps.AddPage(&aboutmedia);
	myps.AddPage(&uisettingdia);
	myps.AddPage(&filejoindia);
	myps.AddPage(&musicsettingdia);
	myps.AddPage(&softupdatedia);
	INT_PTR a = myps.DoModal();

}
void ControlPanelDlg::OnUserSelfMessageWebSite()
{
	ShellExecute(NULL,L"open",L"http://www.ltplayer.com",NULL,NULL,SW_SHOW);
}

void ControlPanelDlg::OnUserSelfMessageClose()
{
controlevent->ClosePlayer();
}

LRESULT ControlPanelDlg::OnLayerPaintMessage(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT ControlPanelDlg::OnUserSelfMessageMusicName(WPARAM wParam, LPARAM lParam)
{	
	////SetCapture();
	////m_bMouseTracking=false;
	//CPoint point;
	//point.x=44;
	//point.y=50;
	//currentpoint=point;
	//OnPaint();
	////m_bMouseTracking=true;	
	return 1;
}
LRESULT ControlPanelDlg::OnUserSelfMessageMusicTimes(WPARAM wParam, LPARAM lParam)
{


	return 1;
}

LRESULT ControlPanelDlg::OnUserSelfMessageMusicVoL(WPARAM wParam, LPARAM lParam)
{	

	return 1;
}



LRESULT ControlPanelDlg::OnUserSelfMessageMusicPlay(WPARAM wParam, LPARAM lParam)
{	

	return 1;
}

//列表点击事件
bool ControlPanelDlg::SetListContorEvent(UIListInfo in1,UIFileListInfo in2)
{
	//wchar_t *k=in2.filepath.GetBuffer();
	//char *a = MusicUtils::WideCharToMultiChar(k);
	//this->currentfilename=
	wcscpy(this->currentfilename,in2.filepath.GetBuffer());
	//this->currentfilename=L"여자이니까";
	currentmusiclistindex=in2.allinindex;

	wcscpy(this->currentshowfilename,in2.filename.GetBuffer());
	/*currentshowfilename=in2.filename.GetBuffer();*/

	MusicStop();	
	playbutton->Gbuttoninfo.srcx=0;
	playbutton->Gbuttoninfo.currentcontrolimage=playbutton->Gbuttoninfo.controlimages2;
	canvar->UpdateCanvar(playbutton);
	MusicPlay();

	return true;
}

bool ControlPanelDlg::SetSliderContorEvent(UISliderInfo info)
{
		//double x=info.i3_x;
		//double a =MusicUtils::GetMusicPositionUsePointX(sliderwidth,x,currentfileseconds)/1000;
	if (info.classname=="volumeslider")
	{
		//float a=(float)(info.i3_x-info.i1_x)/(float)info.i1_width;
		float a=(float)(info.i3_x)/(float)info.i1_width;
		if (volumeico->GetButtonImg()==1)
		{
				controlevent->SetMusicVolume(a,m_stream);
		}
		
		return true;
	}
	if (info.classname=="positionslider")
	{
		double x=info.i3_x;
		double a =MusicUtils::GetMusicPositionUsePointX(positionslider->Gsliderinfo.i1_width,x,currentfileseconds);
		controlevent->SetMusicPosition(a,m_stream);
		return true;
	}
}

void ControlPanelDlg::NextMusic()
{

	MusicStop();
	int lastindex=0;
	int musiccount=musiclist->GetListCount();
	if(musiccount==0)
	{
		return;
	}
	if (currentmusiclistindex+1<musiccount)
	{
		lastindex=currentmusiclistindex+1;
	}
	FileListInfo _info=musiclist->filelistarray->GetAt(lastindex);
	//wchar_t *k = _info.filepath.GetBuffer();
	//char *a = MusicUtils::WideCharToMultiChar(k);
	this->currentfilename=_info.filepath.GetBuffer();
	currentshowfilename=_info.filename.GetBuffer();
	currentmusiclistindex=lastindex;	
	musiclist->SetFileIndex(this->m_hWnd,currentmusiclistindex);
	canvar->UpdateCanvar(musiclist);
	playbutton->Gbuttoninfo.srcx=0;
	playbutton->Gbuttoninfo.currentcontrolimage=playbutton->Gbuttoninfo.controlimages2;
	canvar->UpdateCanvar(playbutton);
	MusicPlay();
}
void ControlPanelDlg::PerMusic()
{

	MusicStop();
	int lastindex=currentmusiclistindex;
	int musiccount=musiclist->GetListCount();
	if(musiccount==0)
	{
		return;
	}


	if (currentmusiclistindex-1>=0)
	{
		lastindex=currentmusiclistindex-1;
	}
	FileListInfo _info=musiclist->filelistarray->GetAt(lastindex);
	//wchar_t *k = _info.filepath.GetBuffer();
	//char *a = MusicUtils::WideCharToMultiChar(k);
	this->currentfilename=_info.filepath.GetBuffer();
	currentshowfilename=_info.filename.GetBuffer();
	currentmusiclistindex=lastindex;
	musiclist->SetFileIndex(this->m_hWnd,currentmusiclistindex,0);
	canvar->UpdateCanvar(musiclist);
	playbutton->Gbuttoninfo.srcx=0;
	playbutton->Gbuttoninfo.currentcontrolimage=playbutton->Gbuttoninfo.controlimages2;
	canvar->UpdateCanvar(playbutton);
	MusicPlay();
}

bool ControlPanelDlg::SetButtonContorEvent(UIButtonInfo info)
{
	//最小化按钮事件
	if (info.classname=="minbutton")
	{
		//controlevent->ShowPlayer();
		//m_player.put_URL(L"mms://alive.rbc.cn/fm1006");
		::ShowWindow(this->m_hWnd,SW_HIDE);
		
	}
	//最大化按钮事件
	if (info.classname=="maxbutton")
	{
		ScreenInfo screeninfo;
		MusicUtils::GetScreenInfo(&screeninfo);
		CRect rect;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rect,0);
		int cx = 0,cy =0;
		if (rect.bottom <=MAINBG_WIDTH && MAINBG_WIDTH>=screeninfo.cx )
		{cx = 600;cy=600;}
		else{
			cx = screeninfo.cx;
			cy=rect.bottom;}

		MoveWindow(0,0,cx,cy);
		OnSize(1,cx,cy);


	}
	//关闭按钮事件
	if (info.classname=="closebutton")
	{
		controlevent->ClosePlayer();
		
	}

	//上一个按钮事件
	if (info.classname=="perbutton")
	{
		if (musiclist->isshow)
		{
		PerMusic();
		}
	//	return true;
	}	
	//播放按钮事件
	if (info.classname=="playbutton")
	{
		if (this->currentfilename!=NULL && !playstatus)
		{
			musiclist->SetFileIndex(this->m_hWnd,currentmusiclistindex);
			canvar->UpdateCanvar(musiclist);
		}
		MusicPlay();
		//return true;
	}
	//下一个按钮事件
	if (info.classname=="nextbutton")
	{
		if (musiclist->isshow)
		{
			NextMusic();
		}
		
		//return true;
	}
	//声音控制按钮事件
	if (info.classname=="volumeico")
	{
		float a=0.0;
		if (volumeico->GetButtonImg()==1)
		{
			a=0.0;
		}
		else
		{
			a=(float)(volumeslider->Gsliderinfo.i2_srcwidth)/(float)volumeslider->Gsliderinfo.i1_width;
		}


		controlevent->CloseMusicVOL(m_stream,a);
		
		//return false;
	}
	//增加列表按钮事件
	if (info.classname=="addbutton")
	{
		controlevent->AddFilesToList(musiclist);
		/*musiclist->SetFileIndex(m_hWnd,0);*/
		//canvar->Add2PaintQueue(musiclist);
		musiclist->isshow=true;
		networkmusiclist->isshow=false;
		canvar->UpdateCanvar(musiclist);
		canvar->UpdateCanvar(networkmusiclist);
		
	}
	//控制循环按钮事件
	if (info.classname=="listxhbutton")
	{
		if (islooplist)
		{
			islooplist=false;
		}
		else
		{
			islooplist=true;
		}


	}
	//清除列表按钮事件
	if (info.classname=="setbutton")
	{

		musiclist->DeleteList();
		musiclist->GetSliderBarHeight();
		canvar->UpdateCanvar(musiclist);
		MusicStop();
		playbutton->Gbuttoninfo.srcx=0;
		playbutton->Gbuttoninfo.currentcontrolimage=playbutton->Gbuttoninfo.controlimages1;

		canvar->UpdateCanvar(playbutton);
		ZeroMemory(this->currentfilename,MAX_PATH+1);
		MusicUtils::LSMusicList(0,musiclist->filelistarray);
		//return false;
	}
	
	if (info.classname=="optionsbutton")
	{
		CMyPropertySheet myps(_T("播放器设置"),this,0);
		myps.m_psh.dwFlags   =   (myps.m_psh.dwFlags)   |   PSH_NOAPPLYNOW   ; 
		myps.m_psh.dwFlags   |=   PSH_HASHELP; 
		myps.AddPage(&aboutmedia);
		myps.AddPage(&uisettingdia);
		myps.AddPage(&filejoindia);
		myps.AddPage(&musicsettingdia);
		myps.AddPage(&softupdatedia);
		INT_PTR a = myps.DoModal();
	}
	//随机换皮肤
	if(info.classname =="skinbutton")
	{
		if(!skinbutton->Gbuttoninfo.haswm){
			return true;
		}
		skinbutton->Gbuttoninfo.haswm = false;
		CArray<UiSkinInfo,UiSkinInfo&> filearray;
		MusicUtils::LSSkinList(1,&filearray);
		int rand  = MusicUtils::Random(filearray.GetCount()-1);
		UiSkinInfo sinfo = filearray.GetAt(rand);
		OnSetBgImg((WPARAM)&sinfo,currenttransparent);
		skinbutton->Gbuttoninfo.haswm = true;
		
	}
	return true;
}

void ControlPanelDlg::MusicPlay(wchar_t* currentfilename)
{
	//char* filename=(char*)currentfilename;

	m_stream =BASS_StreamCreateFile(FALSE,currentfilename,0,0,BASS_UNICODE);


	musicfx[0]=BASS_ChannelSetFX(m_stream,BASS_FX_DX8_PARAMEQ,0);
	musicfx[1]=BASS_ChannelSetFX(m_stream,BASS_FX_DX8_PARAMEQ,0);
	musicfx[2]=BASS_ChannelSetFX(m_stream,BASS_FX_DX8_PARAMEQ,0);
	musicfx[3]=BASS_ChannelSetFX(m_stream,BASS_FX_DX8_PARAMEQ,0);
	musicfx[4]=BASS_ChannelSetFX(m_stream,BASS_FX_DX8_PARAMEQ,0);
	musicfx[5]=BASS_ChannelSetFX(m_stream,BASS_FX_DX8_PARAMEQ,0);
	musicfx[6]=BASS_ChannelSetFX(m_stream,BASS_FX_DX8_PARAMEQ,0);
	musicfx[7]=BASS_ChannelSetFX(m_stream,BASS_FX_DX8_PARAMEQ,0);
	musicfx[8]=BASS_ChannelSetFX(m_stream,BASS_FX_DX8_PARAMEQ,0);
	musicfx[9]=BASS_ChannelSetFX(m_stream,BASS_FX_DX8_PARAMEQ,0);
	float a=0.0;
	if (volumeslider->Gsliderinfo.i2_srcwidth<=0)
	{
		a=0.0;
	}
	else
	{
		a=(float)(volumeslider->Gsliderinfo.i2_srcwidth)/(float)volumeslider->Gsliderinfo.i1_width;
	}

	if (volumeico->GetButtonImg()==1)
	{

		controlevent->SetMusicVolume(a,m_stream);
	}
	else
	{
		controlevent->SetMusicVolume(0,m_stream);
	}

	BASS_ChannelPlay(m_stream,FALSE);
	currentfileseconds=controlevent->GetMusicSeconds(m_stream);
	//sliderwidth=301-32;

	CClientDC testcclientdc(this);
	musicnamelable->Glableinfo.str=currentshowfilename;
	int strw = MusicUtils::TestStringCx(currentshowfilename);
	if(strw>MAINBG_WIDTH-(canvar->ISDLGALPHA?30:20))
	{
		musicnamelable->Glableinfo.width = MAINBG_WIDTH-(canvar->ISDLGALPHA?30:20);
	}
	else
	{
		musicnamelable->Glableinfo.width = strw;
    }
	musicnamelable->Glableinfo.rect=controlclass->GetRect(musicnamelable->Glableinfo.x,musicnamelable->Glableinfo.y,musicnamelable->Glableinfo.width,15);
	if(canvar->ISDLGALPHA)
	{
	     ResetMucisNameLable(10);
	}else
	{
		ResetMucisNameLable(0);
	}
	SetWindowTextFunc(CString("静静聆听播放器-")+currentshowfilename);
	canvar->UpdateCanvar(musicnamelable);
	playstatus=1;


	if (musicnamelable->GetStrWidht()-musicnamelable->IWIDTH()>0)
	{
		::SetTimer(this->m_hWnd,MUSIC_TIMER_NAME_ROLL,100,NULL); 
	}
	
	::SetTimer(this->m_hWnd,MUSIC_TIMER,1000,NULL);  
	
}

//UINT  ControlPanelDlg::MusicPlayLink(LPVOID pParam)
//{
//	ControlPanelDlg *t=static_cast<ControlPanelDlg*>(pParam);
//	t->MusicPlay(t->currentfilename);
//	return TRUE;
//}

void ControlPanelDlg::MusicPlay()
{

	if(!playstatus){

		if (this->currentfilename!=NULL)
		{
			//AfxBeginThread(&ControlPanelDlg::MusicPlayLink,this);

			//if (strstr(this->currentfilename,"mms://"))
			//{
			//	RadioPlayer(this->currentfilename);
			//}
			//else{
				MusicPlay(this->currentfilename);
			//}
		}
	}
	else
	{
		musiclist->SetFileIndex(this->m_hWnd,-1);
		canvar->UpdateCanvar(musiclist);
		MusicStop();
		/*volumstatus=1;*/
		
	}
}

void ControlPanelDlg::PlayeTimerStatus(double i,double s)
{
	if (canvar->m_bMouseTracking)
	{
	CClientDC *dc =new CClientDC(this);
    positionslider->Gsliderinfo.i2_width=(int)i;
	
	//positionslider->Gsliderinfo.i3_x=(int)i;
	canvar->UpdateCanvar(positionslider);
	CString cs;
	cs.Format(_T("%s"),MusicUtils::Seconds2Time(currentfileseconds));
	musictimelable->Glableinfo.str=cs;
	
	canvar->UpdateCanvar(musictimelable);

	musictimeclable->Glableinfo.str = MusicUtils::Seconds2Time(s);
	canvar->UpdateCanvar(musictimeclable);

	}
}
void ControlPanelDlg::MusicStop()
{
	::KillTimer(this->m_hWnd, MUSIC_TIMER); 
	::KillTimer(this->m_hWnd, MUSIC_TIMER_NAME_ROLL); 
	BASS_ChannelStop(m_stream);
	BASS_StreamFree(m_stream);
	positionslider->Gsliderinfo.i2_width=0;
	canvar->UpdateCanvar(positionslider);
	musictimelable->Glableinfo.str = "00:00";
	canvar->UpdateCanvar(musictimelable);

	musictimeclable->Glableinfo.str = "00:00";
	canvar->UpdateCanvar(musictimeclable);
	musicnamelable->EmptyString();
	canvar->UpdateCanvar(musicnamelable);

	playstatus=0;
	musicnamelable->Glableinfo.rollstep=0;
	musicnamelablerollflag=0;
	SetWindowTextFunc(_T("静静聆听播放器"));


	return;
}

//CString ControlPanelDlg::GetIniValue(LPCTSTR lpAppName ,LPCTSTR key) const
//{
//	TCHAR  inBuf[MAX_PATH]; 
//	GetPrivateProfileString(lpAppName, key, _T(""), inBuf, MAX_PATH, APPINI);
//	return inBuf;
//}

LRESULT ControlPanelDlg::OnStartOpenFile(WPARAM wParam, LPARAM lParam)
{

	//AfxMessageBox(*(CString*)lParam);
	Add2MusicList(CString(*(LPCTSTR)lParam));
	return 1;
}

//void ControlPanelDlg::SetIniValue(LPCTSTR lpAppName ,LPCTSTR key ,LPCTSTR str)
//{
//	::WritePrivateProfileString(lpAppName,key,str,APPINI);
//}

BOOL ControlPanelDlg::OnCopyData(CWnd* pWnd,COPYDATASTRUCT* pCopyDataStruct)
{
   OpenFileAndPlayer(CString((LPCTSTR)pCopyDataStruct->lpData));
   return 1;
}

void ControlPanelDlg::OpenFileAndPlayer(CString  fname)
{
	if (!IsWindowVisible())
	{
		controlevent->ShowPlayer(this->m_hWnd,AfxGetMainWnd()->m_hWnd,SW_SHOW);
	}
	
	minbutton->Gbuttoninfo.srcx=0;
	canvar->UpdateCanvar(minbutton);
	SwitchToThisWindow(this->m_hWnd,FALSE);
	SwitchToThisWindow(AfxGetMainWnd()->m_hWnd,FALSE);
	Add2MusicList(fname);
	playbutton->Gbuttoninfo.srcx=0;
	playbutton->Gbuttoninfo.currentcontrolimage=playbutton->Gbuttoninfo.controlimages1;
	canvar->UpdateCanvar(playbutton);
	MusicStop();
	INT lastindex=musiclist->GetListCount()-1;
	//wchar_t *k = 
	//char *a = MusicUtils::WideCharToMultiChar(k);
	this->currentfilename=musiclist->filelistarray->GetAt(lastindex).filepath.GetBuffer();
	currentshowfilename=musiclist->filelistarray->GetAt(lastindex).filename.GetBuffer();
	currentmusiclistindex=lastindex;	
	musicnamelable->Glableinfo.str=currentshowfilename;
	canvar->UpdateCanvar(musicnamelable);
	musiclist->SetFileIndex(this->m_hWnd,currentmusiclistindex);
	canvar->UpdateCanvar(musiclist);
	playbutton->Gbuttoninfo.srcx=0;
	playbutton->Gbuttoninfo.currentcontrolimage=playbutton->Gbuttoninfo.controlimages2;
	canvar->UpdateCanvar(playbutton);
	MusicPlay();
	
}

LRESULT ControlPanelDlg::SetMusic3D(WPARAM wParam, LPARAM lParam)
{

	int musicfxvaluey[5][10]={{3,1,0,-2,-4,-4,-2,0,1,2},{-2,0,2,4,-2,-2,0,0,4,4},{-6,0,0,0,0,0,4,0,4,0},
					{-2,3,4,1,-2,-2,0,0,4,4},{-6,1,4,-2,-2,-4,0,0,6,6}};
	int musicfxCenter[]={31,62,125,250,500,1000,2000,4000,8000,16000};

	if (wParam!=NULL)
	{
		for (int i=0;i<10;i++)
		{
			MUSIC_EQ(0,musicfxCenter[i]);
			BASS_FXSetParameters(musicfx[i],&p);
		}
	    return 1;
	}

	//BASS_DX8_PARAMEQ p;
	//p.fBandwidth=12;
	for (int i=0;i<10;i++)
	{
		MUSIC_EQ(musicfxvaluey[lParam][i],musicfxCenter[i]);
		BASS_FXSetParameters(musicfx[i],&p);
	}

	return 1;
}
void ControlPanelDlg::LoadRadioList()
{
	
	MusicUtils::LSRadioList(networkmusiclist->filelistarray);
	if (networkmusiclist->filelistarray->GetSize()>0)
	{
		networkmusiclist->SetListValue();
		//networkmusiclist->GetSliderBarHeight();
	}
}
void ControlPanelDlg::LoadMusicList()
{

	MusicUtils::LSMusicList(1,musiclist->filelistarray);
	if (musiclist->filelistarray->GetSize()>0)
	{
		musiclist->SetListValue();
		musiclist->GetSliderBarHeight();
		canvar->UpdateCanvar(musiclist);
	}
}

BOOL ControlPanelDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	return MusicUtils::ArrestKeyDown(pMsg);
}
void ControlPanelDlg::AutoPlay()
{
	CString path=MusicUtils::GetConfigXml(L"lastplayfile",L"");
	if (path!="")
	{
		for (int i=0;i<musiclist->GetListCount();i++)
		{
			FileListInfo info=musiclist->filelistarray->GetAt(i);
			if (path==info.filepath)
			{
				USES_CONVERSION;
				this->currentfilename=path.GetBuffer();;

				currentshowfilename=info.filename.GetBuffer();

				MusicPlay(currentfilename);			
				musiclist->SetFileIndex(this->m_hWnd,i);
				canvar->UpdateCanvar(musiclist);			
				playbutton->Gbuttoninfo.srcx=0;
				playbutton->Gbuttoninfo.currentcontrolimage=playbutton->Gbuttoninfo.controlimages2;
				canvar->UpdateCanvar(playbutton);
				break;
			}
		}
	}
}


void ControlPanelDlg::UpdateMusicListCanvars()
{
	canvar->UpdateCanvar(musiclist);
}

void ControlPanelDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	this->EnableWindow(FALSE);
	UINT count;
	wchar_t filePath[200];
	count = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	USES_CONVERSION;
	HINSTANCE hinstLib; 
	DROPMYPROC ProcAdd; 
	hinstLib = LoadLibrary(TEXT("LT_MusicTags.dll")); 

	for(UINT i=0; i<count; i++)
	{
		int pathLen = DragQueryFile(hDropInfo, i, filePath, sizeof(filePath));

		if(PathIsDirectory(filePath) || !MusicUtils::IsPlayerSupportMusicType(filePath))
		{
			continue;
		}

		FileListInfo fileinfo;
		fileinfo.filepath=filePath;
		HSTREAM m_stream_t =BASS_StreamCreateFile(FALSE,W2A(fileinfo.filepath),0,0,0);	
		if (m_stream_t!=NULL)
		{
			ProcAdd = (DROPMYPROC) GetProcAddress(hinstLib, "GetMusicTilteAndArtist"); 
			CString *a=new CString();
			CString *b=new CString();
			if (!ProcAdd(m_stream_t,a,b))
			{
				int tpathindex=fileinfo.filepath.ReverseFind('\\');
				CString tcstring=MusicUtils::GetMusicName(MusicUtils::GetSubString(fileinfo.filepath,tpathindex));
				fileinfo.filename=tcstring;
			}else{
				CString tempnamestr;
				tempnamestr.Format(_T("%s - %s"),*a,*b);
				fileinfo.filename=tempnamestr;
				delete a;
				delete b;
			}
		}
		else
		{
			int tpathindex=fileinfo.filepath.ReverseFind('\\');
			CString tcstring=MusicUtils::GetMusicName(MusicUtils::GetSubString(fileinfo.filepath,tpathindex));
			fileinfo.filename=tcstring;
		}

		musiclist->filelistarray->Add(fileinfo);
	}

	musiclist->SetListValue();
	musiclist->GetSliderBarHeight();
	MusicUtils::LSMusicList(0,musiclist->filelistarray);
	FreeLibrary(hinstLib);
	DragFinish(hDropInfo);
	UpdateMusicListCanvars();
	this->EnableWindow(TRUE);
	CDialog::OnDropFiles(hDropInfo);
}


LRESULT ControlPanelDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetWindowRect(&rect);
	CRect rect1 = rect;
	rect1.DeflateRect(10, 10, -10, -10);
	rect1.NormalizeRect();
	if (point.x <= rect.left+3)
		return HTLEFT;
	else if (point.x >= rect.right-3)
		return HTRIGHT;
	else if (point.y <= rect.top+3)
		return HTTOP;
	else if (point.y >= rect.bottom-3)
		return HTBOTTOM;
	else if (point.x <= rect.left+10 && point.y <= rect.top+10)
		return HTTOPLEFT;
	else if (point.x >= rect.right-10 && point.y <= rect.top+10)
		return HTTOPRIGHT;
	else if (point.x <= rect.left+10 && point.y >= rect.bottom-10)
		return HTBOTTOMLEFT;
	else if (point.x >= rect.right-10 && point.y >= rect.bottom-10)
		return HTBOTTOMRIGHT;
	else if (!rect.IsRectEmpty())
	{
		if (canvar->IsOperationControl(point))
		{
			return CWnd::OnNcHitTest(point);
		}
		else
		{
			LRESULT uRet = CWnd::OnNcHitTest(point);
			uRet = (uRet == HTCLIENT) ? HTCAPTION : uRet;
			return uRet;
		}
	}
	else
	{
		return CWnd::OnNcHitTest(point);
	}
	return 0;

}

void ControlPanelDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{


	CPoint cupoint;
	GetCursorPos(&cupoint);
	CRect rect;
	GetWindowRect(&rect);
	switch(nHitTest)
	{
	case HTTOP:
		SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y));
		return;
	case HTBOTTOM:
		SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
		return;
	case HTLEFT:
		SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y));
		return;
	case HTRIGHT:
		SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
		return;
	case HTTOPLEFT:
		SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
		return;
	case HTTOPRIGHT:
		SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
		return;
	case HTBOTTOMLEFT:
		SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
		return;
	case HTBOTTOMRIGHT:
		SendMessage( WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
		return;
	default:
		CDialog::OnNcLButtonDown( nHitTest, point );
	}
}
void ControlPanelDlg::OnSize(UINT nType, int cx, int cy)
{
	if (DlgStartEnd)
	{
		CClientDC *dc=new CClientDC(this);
		if (canvar->ISDLGALPHA)
		{
			canvar->MAINBG_WIDTH=cx;
			canvar->MAINBG_HEIGHT=cy;
			MAINBG_WIDTH=cx;
			MAINBG_HEIGHT=cy;
			int offsetint = 10;
			ResetMMCRegion(offsetint);
			ResetPlayRegion(offsetint);
			ResetControlRegion(offsetint);
			ResetMucisNameLable(offsetint);
			//ResetPostitionSlider();
			//
			//ResetDoubleTab();
			//ResetButton(34);
			//ResetLable();
			ResetSpecificControlRect(offsetint);
			
			//positionslider->SetSingleControl(dc->m_hDC,(MAINBG_WIDTH-offsetint)-19-19);
			canvar->OnInit(dc);
		}else
		{
			canvar->MAINBG_WIDTH=cx;
			canvar->MAINBG_HEIGHT=cy;
			MAINBG_WIDTH=cx;
			MAINBG_HEIGHT=cy;
			//closebutton->Gbuttoninfo.x=MAINBG_WIDTH-closebutton->Gbuttoninfo.srcwidth;
			//closebutton->Gbuttoninfo.rect=controlclass->GetRect(closebutton->Gbuttoninfo.x,closebutton->Gbuttoninfo.y,closebutton->Gbuttoninfo.srcwidth,closebutton->Gbuttoninfo.srcheight);
			//
			//
			//maxbutton->Gbuttoninfo.x=MAINBG_WIDTH-maxbutton->Gbuttoninfo.srcwidth-closebutton->Gbuttoninfo.srcwidth;
			//maxbutton->Gbuttoninfo.rect=controlclass->GetRect(maxbutton->Gbuttoninfo.x,maxbutton->Gbuttoninfo.y,maxbutton->Gbuttoninfo.srcwidth,maxbutton->Gbuttoninfo.srcheight);

			//minbutton->Gbuttoninfo.x=MAINBG_WIDTH-minbutton->Gbuttoninfo.srcwidth-closebutton->Gbuttoninfo.srcwidth-maxbutton->Gbuttoninfo.srcwidth;
			//minbutton->Gbuttoninfo.rect=controlclass->GetRect(minbutton->Gbuttoninfo.x,minbutton->Gbuttoninfo.y,minbutton->Gbuttoninfo.srcwidth,minbutton->Gbuttoninfo.srcheight);

			ResetMMCRegion(0);
			ResetPlayRegion(0);
			ResetControlRegion(0);
			ResetMucisNameLable(0);
			//ResetPostitionSlider();
			//
			//ResetDoubleTab();
			//ResetButton(34);
			//ResetLable();
			ResetSpecificControlRect(0);
			//positionslider->SetSingleControl(dc->m_hDC,MAINBG_WIDTH-19-19);
			canvar->OnInit(dc);
			canvar->needpaintall=1;
			RECT rect={-1,-1,-1,-1};
			GetWindowRect(&rect);
			canvar->Paint((CPaintDC*)dc,rect);
		}
	}
}



void ControlPanelDlg::OnMove(int x, int y)
{
	if (DlgStartEnd)
	{
		RECT rect;
		GetWindowRect(&rect);
		MoveWindow(x,y,rect.right-rect.left,rect.bottom-rect.top);
		return CWnd::OnMove(x,y);
	}
	else{

		MoveWindow(x,y,MAINBG_WIDTH,MAINBG_HEIGHT);
		return CWnd::OnMove(x,y);
	}
}

LRESULT ControlPanelDlg::EnableBgAlpha(WPARAM wParam, LPARAM lParam)
{
	CClientDC *dc=new CClientDC(this);

	RECT rect={-1,-1,-1,-1};
	if (wParam)
	{
		
		GetWindowRect(&rect);
		ModifyStyleEx(0,WS_EX_LAYERED);
		canvar->ISDLGALPHA=1;	
		MAINBG_WIDTH+=10;
		MAINBG_HEIGHT+=10;
		canvar->MAINBG_WIDTH =MAINBG_WIDTH;
		canvar->MAINBG_HEIGHT =MAINBG_HEIGHT;

		
		MoveWindow(rect.left-5,rect.top-5,MAINBG_WIDTH,MAINBG_HEIGHT);	
		ResetControlsXY(0);
		int offsetint = 10;
		ResetMMCRegion(offsetint);
		ResetPlayRegion(offsetint);
		ResetControlRegion(offsetint);
		ResetMucisNameLable(offsetint);
		ResetSpecificControlRect(offsetint);
		canvar->OnInit(dc);
	
	}
	else{
		
		MAINBG_WIDTH-=10;
		MAINBG_HEIGHT-=10;
		canvar->MAINBG_WIDTH=MAINBG_WIDTH;
		canvar->MAINBG_HEIGHT=MAINBG_HEIGHT;
		ModifyStyleEx(WS_EX_LAYERED,0);
		GetWindowRect(&rect);
		MoveWindow(rect.left+5,rect.top+5,MAINBG_WIDTH,MAINBG_HEIGHT);	
		canvar->needpaintall=1;
		canvar->ISDLGALPHA=0;
		ResetControlsXY(1);
		ResetMMCRegion(0);
		ResetPlayRegion(0);
		ResetControlRegion(0);
		ResetMucisNameLable(0);
		ResetSpecificControlRect(0);
		canvar->OnInit(dc);
		RECT rect={-1,-1,-1,-1};

		canvar->Paint((CPaintDC*)dc,rect);
	}

	MusicUtils::WriteConfigXml(_T("entransparent"),MusicUtils::ConverI2W(wParam),"SetPlayerConfigValue");

	return 1;
}

void ControlPanelDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	ScreenInfo screeninfo;
	MusicUtils::GetScreenInfo(&screeninfo);
	lpMMI->ptMinTrackSize.x = theApp.DlgWidth;   //x宽度  
	lpMMI->ptMinTrackSize.y = theApp.DlgHigh;   //y高度  
	lpMMI->ptMaxTrackSize.x = screeninfo.cx;
	lpMMI->ptMaxTrackSize.y= screeninfo.cy;
}

void ControlPanelDlg::ResetSpecificControlRect(int offsetint)
{
	musiclist->Glistinfo.listui_x=offsetint/2;
	musiclist->Glistinfo.listui_height=(MAINBG_HEIGHT-offsetint)-220-34;
	musiclist->Glistinfo.listui_width=(MAINBG_WIDTH-offsetint);
	musiclist->Glistinfo.listui_rect=controlclass->GetRect(musiclist->Glistinfo.listui_x,musiclist->Glistinfo.listui_y,musiclist->Glistinfo.listui_width,musiclist->Glistinfo.listui_height);
	//musiclist->Glistinfo.sliderbar_x = MAINBG_WIDTH - musiclist->Glistinfo.sliderbar_width;
	CPoint cupoint;
	//GetCursorPos(&cupoint);
	//::ScreenToClient(m_hWnd,&cupoint);
	//musiclist->ResetSliderBarPos(cupoint);
	musiclist->SetListValue();
	musiclist->GetSliderBarHeight();
	musiclist->SetStepInt();
	



}


int ControlPanelDlg::ResetPostitionSlider(int offsetint)
{
	positionslider->Gsliderinfo.i1_width =(MAINBG_WIDTH-offsetint)-64-59;
	//positionslider->Gsliderinfo.i2_width =(MAINBG_WIDTH-offsetint)-64-59;
	positionslider->Gsliderinfo.rect=controlclass->GetRect(positionslider->Gsliderinfo.i1_x,positionslider->Gsliderinfo.i1_y,positionslider->Gsliderinfo.i1_width,positionslider->Gsliderinfo.i3_height);
	return (MAINBG_WIDTH-offsetint)-64-59;
}

void ControlPanelDlg::ResetDoubleTab(int offsetint)
{

}
void ControlPanelDlg::ResetMMCRegion(int offsetint)
{
	closebutton->Gbuttoninfo.x=MAINBG_WIDTH-closebutton->Gbuttoninfo.srcwidth-(offsetint/2);
	closebutton->Gbuttoninfo.rect=controlclass->GetRect(closebutton->Gbuttoninfo.x,closebutton->Gbuttoninfo.y,closebutton->Gbuttoninfo.srcwidth,closebutton->Gbuttoninfo.srcheight);


	minbutton->Gbuttoninfo.x=closebutton->Gbuttoninfo.x -minbutton->Gbuttoninfo.srcwidth;
	minbutton->Gbuttoninfo.rect=controlclass->GetRect(minbutton->Gbuttoninfo.x,minbutton->Gbuttoninfo.y,minbutton->Gbuttoninfo.srcwidth,minbutton->Gbuttoninfo.srcheight);

}

void ControlPanelDlg::ResetPlayRegion(int offsetint)
{

	int conrolmiddle =ceil((double)((MAINBG_WIDTH-offsetint)/2));
	playbutton->Gbuttoninfo.x=conrolmiddle-(playbutton->Gbuttoninfo.srcwidth/2);
	perbutton->Gbuttoninfo.x=playbutton->Gbuttoninfo.x-PLAYERCONTROL_BETWEEN_WIDTH-perbutton->Gbuttoninfo.srcwidth;
	nextbutton->Gbuttoninfo.x=playbutton->Gbuttoninfo.x+ playbutton->Gbuttoninfo.srcwidth+PLAYERCONTROL_BETWEEN_WIDTH;
	playbutton->Gbuttoninfo.rect=controlclass->GetRect(playbutton->Gbuttoninfo.x,playbutton->Gbuttoninfo.y,playbutton->Gbuttoninfo.srcwidth,playbutton->Gbuttoninfo.srcheight);
	perbutton->Gbuttoninfo.rect=controlclass->GetRect(perbutton->Gbuttoninfo.x,perbutton->Gbuttoninfo.y,perbutton->Gbuttoninfo.srcwidth,perbutton->Gbuttoninfo.srcheight);
	nextbutton->Gbuttoninfo.rect=controlclass->GetRect(nextbutton->Gbuttoninfo.x,nextbutton->Gbuttoninfo.y,nextbutton->Gbuttoninfo.srcwidth,nextbutton->Gbuttoninfo.srcheight);

	
	volumeslider->Gsliderinfo.i1_x=(MAINBG_WIDTH-offsetint)-VOLUMESLIDER_RIGHT_CX-volumeslider->Gsliderinfo.i1_width;
	volumeslider->Gsliderinfo.rect=controlclass->GetRect(volumeslider->Gsliderinfo.i1_x,volumeslider->Gsliderinfo.i1_y,volumeslider->Gsliderinfo.i1_srcwidth,volumeslider->Gsliderinfo.i1_srcheight);	

	volumeico->Gbuttoninfo.x=volumeslider->Gsliderinfo.i1_x-VOLUMESLIDER_LEFT_CX-volumeico->Gbuttoninfo.srcwidth;
	volumeico->Gbuttoninfo.rect=controlclass->GetRect(volumeico->Gbuttoninfo.x,volumeico->Gbuttoninfo.y,volumeico->Gbuttoninfo.srcwidth,volumeico->Gbuttoninfo.srcheight);

	CClientDC *dc =new CClientDC(this);
	positionslider->Gsliderinfo.i1_width=(MAINBG_WIDTH-offsetint)-(POSITIONSLIDER_LR_CX*2);
	positionslider->SetSingleControl(dc->m_hDC,3,3);
	positionslider->Gsliderinfo.rect=controlclass->GetRect(positionslider->Gsliderinfo.i1_x,positionslider->Gsliderinfo.i1_y,positionslider->Gsliderinfo.i1_width,positionslider->Gsliderinfo.i1_srcheight);
	delete dc;

	musictimelable->Glableinfo.x=positionslider->Gsliderinfo.i1_x+positionslider->Gsliderinfo.i1_width+5;;
	musictimelable->Glableinfo.rect=controlclass->GetRect(musictimelable->Glableinfo.x,musictimelable->Glableinfo.y,musictimelable->Glableinfo.width,15);

}


void ControlPanelDlg::ResetControlRegion(int offsetint)
{
	
	int bottom3ave = ceil((double)(((MAINBG_WIDTH-offsetint)-120)/3));

	addbutton->Gbuttoninfo.y=(MAINBG_HEIGHT-(offsetint/2))-27;

	optionsbutton->Gbuttoninfo.x=(MAINBG_WIDTH-offsetint)-72;
	optionsbutton->Gbuttoninfo.y =(MAINBG_HEIGHT-(offsetint/2))-27;

	listxhbutton->Gbuttoninfo.x=SETTING_ONELAST_CX+bottom3ave-SETTINGHALF_CX;
	listxhbutton->Gbuttoninfo.y =(MAINBG_HEIGHT-(offsetint/2))-27;

	setbutton->Gbuttoninfo.x=listxhbutton->Gbuttoninfo.x+bottom3ave;
	setbutton->Gbuttoninfo.y =(MAINBG_HEIGHT-(offsetint/2))-27;

	listxhbutton->Gbuttoninfo.rect=controlclass->GetRect(listxhbutton->Gbuttoninfo.x,listxhbutton->Gbuttoninfo.y,listxhbutton->Gbuttoninfo.srcwidth,listxhbutton->Gbuttoninfo.srcheight);
	setbutton->Gbuttoninfo.rect=controlclass->GetRect(setbutton->Gbuttoninfo.x,setbutton->Gbuttoninfo.y,setbutton->Gbuttoninfo.srcwidth,setbutton->Gbuttoninfo.srcheight);
	optionsbutton->Gbuttoninfo.rect=controlclass->GetRect(optionsbutton->Gbuttoninfo.x,optionsbutton->Gbuttoninfo.y,optionsbutton->Gbuttoninfo.srcwidth,optionsbutton->Gbuttoninfo.srcheight);
	addbutton->Gbuttoninfo.rect=controlclass->GetRect(addbutton->Gbuttoninfo.x,addbutton->Gbuttoninfo.y,addbutton->Gbuttoninfo.srcwidth,addbutton->Gbuttoninfo.srcheight);

}

void ControlPanelDlg::ResetLable(int offsetint)
{
	//musictimelable->Glableinfo.x=(MAINBG_WIDTH-offsetint) - 80;;
	//musictimelable->Glableinfo.rect=controlclass->GetRect(musictimelable->Glableinfo.x,musictimelable->Glableinfo.y,musictimelable->Glableinfo.width,15);

}


void ControlPanelDlg::ResetMucisNameLable(int offsetint)
{
	int strw = MusicUtils::TestStringCx(currentshowfilename);
	CClientDC testcclientdc(this);
	int conrolmiddle =ceil((double)((MAINBG_WIDTH-offsetint)/2));
	int strwidthmiddle = ceil((double)(strw/2));
	musicnamelable->Glableinfo.x=conrolmiddle - strwidthmiddle;
	
	if(strw>MAINBG_WIDTH-(canvar->ISDLGALPHA?30:20))
	{
		musicnamelable->Glableinfo.width = MAINBG_WIDTH-(canvar->ISDLGALPHA?30:20);
	}
	else
	{
		musicnamelable->Glableinfo.width = strw;
    }
	musicnamelable->Glableinfo.rect=controlclass->GetRect(musicnamelable->Glableinfo.x,musicnamelable->Glableinfo.y,musicnamelable->Glableinfo.width,15);

}
//设置界面上在透明与不透明时候固定控件坐标值
void ControlPanelDlg::ResetControlsXY(int k)
{
   if (canvar->ISDLGALPHA && !k)
   {
	   musiclogo->Gstaticinfo.x +=5;
	   musiclogo->Gstaticinfo.y +=5;
	   musiclist->Glistinfo.listui_y +=5;
	   closebutton->Gbuttoninfo.y +=5;
	   minbutton->Gbuttoninfo.y +=5;
	   playbutton->Gbuttoninfo.y +=5;
	   perbutton->Gbuttoninfo.y +=5;
	   nextbutton->Gbuttoninfo.y +=5;
	   volumeslider->Gsliderinfo.i1_y +=5;
	   volumeico->Gbuttoninfo.y+=5;
	   positionslider->Gsliderinfo.i1_y +=5;
	   musictimelable->Glableinfo.y +=5;
	   musictimeclable->Glableinfo.y +=5;
	   skinbutton->Gbuttoninfo.y +=5;
	   musicnamelable->Glableinfo.y+=5;


   }
   else 
   {
	   if (k){	
			musiclogo->Gstaticinfo.x -=5;
			musiclogo->Gstaticinfo.y -=5;
			musiclist->Glistinfo.listui_y -=5;
			closebutton->Gbuttoninfo.y -=5;
			minbutton->Gbuttoninfo.y -=5;
			playbutton->Gbuttoninfo.y -=5;
			perbutton->Gbuttoninfo.y -=5;
			nextbutton->Gbuttoninfo.y -=5;
			volumeslider->Gsliderinfo.i1_y -=5;
			volumeico->Gbuttoninfo.y-=5;
			positionslider->Gsliderinfo.i1_y -=5;
			musictimelable->Glableinfo.y -=5;
			musictimeclable->Glableinfo.y -=5;
			skinbutton->Gbuttoninfo.y -=5;
			musicnamelable->Glableinfo.y-=5;
	   }
   } 
	musictimeclable->Glableinfo.rect=controlclass->GetRect(musictimeclable->Glableinfo.x,musictimeclable->Glableinfo.y,musictimeclable->Glableinfo.width,15);
	skinbutton->Gbuttoninfo.rect=controlclass->GetRect(skinbutton->Gbuttoninfo.x,skinbutton->Gbuttoninfo.y,skinbutton->Gbuttoninfo.srcwidth,skinbutton->Gbuttoninfo.srcheight);

}

void ControlPanelDlg::SetWindowTextFunc(CString str)
{
	this->SetWindowText(str);
}


LRESULT ControlPanelDlg::OnSetBgImg(WPARAM wParam, LPARAM lParam)
{
	if (bgbitmap!=NULL)
	{
		delete bgbitmap;
	}
	UiSkinInfo usi = *((UiSkinInfo*)wParam);
	CString cs(L"skin\\"+usi.id+L"\\"+usi.fname);
    bgbitmap =new Bitmap(APPPATH+CString(cs));
	canvar->BgSrcImg  = bgbitmap;
	canvar->BGMASKCOLOR=usi.maskcolor;

	int i=1;
	CClientDC * client =new CClientDC(this);
	RECT rect={-1,-1,-1,-1};
	GetWindowRect(&rect);
	if (!canvar->ISDLGALPHA)
	{
		canvar->OnInit(client);
		
		canvar->needpaintall = 1;
		canvar->Paint((CPaintDC*)client,rect);
	}
	else
	{
		while (i<=15 && i*17<=lParam)
		{
			Sleep(50);
			canvar->BgSourceConstantAlpha = i*17;
			canvar->OnInit(client);
			if (!canvar->ISDLGALPHA)
			{
				canvar->needpaintall = 1;
				canvar->Paint((CPaintDC*)client,rect);
			}

			i++;
		}
	}

	delete client;
	return 1;
}

LRESULT ControlPanelDlg::OnSetBgAlpha(WPARAM wParam, LPARAM lParam)
{	
	if (canvar->ISDLGALPHA)
	{
		CClientDC * client =new CClientDC(this);
		canvar->BgSourceConstantAlpha = lParam;
		canvar->OnInit(client);
		delete client;
	}
	return 1;
}

//int ControlPanelDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//
//	return 0;
//}
