#include "StdAfx.h"
#include "ControlEvent.h"
#include "ConstValues.h"

typedef bool (*GETMYPROC)(HSTREAM,CString*,CString*);
ControlEvent::ControlEvent(CArray<LPVOID,LPVOID&> *ArrayList,HWND hwnd) :volumstatus(0),CurrentVOLPostion(0)
{
	//currentfilename=NULL;
	//TArrayList=ArrayList;
	parenthwnd=hwnd;
	////per_parenthwnd=::GetWindow(hwnd,GW_HWNDPREV);
	per_parenthwnd=AfxGetMainWnd()->m_hWnd;
	//BASS_Init(-1,44100,0,hwnd,NULL);
	//PostMessage(hwnd,WM_MYCLOSEWINDOW_MESSAGE,NULL,NULL);
	
}

ControlEvent::~ControlEvent(void)
{
	/*BASS_Free();  */
}





void ControlEvent::MusicPause()
{
	//BASS_ChannelPause(m_stream);
}

void ControlEvent::SetContorEvent(CString eventname,LPVOID tcontrol,...)
{
	
	//CString controlclassarray[8] ={CString("playbutton"),CString("positionslider"),CString("closebutton"),
	//CString("minbutton"),CString("volumeico"),CString("addbutton"),CString("volumeslider"),CString("musiclist")};
	//int indexof=-1;
	//for (int i=0;i<MusicUtils::getArrayLen(controlclassarray);i++)
	//{
	//	if (controlclassarray[i]==eventname)
	//	{
	//		indexof=i;
	//	}
	//}
	//switch(indexof)
	//{
		/*case  MU_PALY:*/

	//		if (this->currentfilename!=NULL)
	//		{
	//		
	//			if (!playstatus){
	//				playstatus=1;
	//				UISlider *tempslider1=static_cast<UISlider*>(TArrayList->GetAt(10));
	//				tempslider1->Gsliderinfo.i3_x=tempslider1->Gsliderinfo.i1_x+(tempslider1->Gsliderinfo.i1_width/3);
	//				tempslider1->Gsliderinfo.i2_srcwidth=(tempslider1->Gsliderinfo.i1_width/3);
	//				//PostMessage(parenthwnd,WM_MYMUSICVOL_MESSAGE,NULL,NULL);
	//				//this->currentfilename="E:\\music\\3.mp3";
	//				AfxBeginThread(&ControlEvent::MusicPlayLink,this);
	//				UILable *tempslider=static_cast<UILable*>(TArrayList->GetAt(14));
	//				USES_CONVERSION;
	//				CString a=A2W(this->currentfilename);
	//				int tpathindex=a.ReverseFind('\\');
	//				CString tcstring=MusicUtils::GetMusicName(MusicUtils::GetSubString(a,tpathindex));
	//				tempslider->Glableinfo.str=tcstring;
	//				SetMusicVolume(0.3);
	//				//PostMessage(parenthwnd,WM_MYMUSICNAME_MESSAGE,NULL,NULL);
	//			}
	//				///*ControlEvent::MusicPlayLink(this);*/}
	//			else{
	//				MusicStop(true);
	//				/*SendMessage(parenthwnd,WM_MYMOVE_MESSAGE,NULL,MAKELPARAM(19,64));*/
	//				//SetMusicPosition();
	//				volumstatus=1;

	//				//AfxEndThread(0);
	//				playstatus=0;}
	//		}
	//		break;
	//	case  MU_SETPOSITION:
	//		{
	//		UISlider *tempslider=static_cast<UISlider*>(tcontrol);
	//		double x=tempslider->Gsliderinfo.i3_x;
	//		double a =MusicUtils::GetMusicPositionUsePointX(sliderwidth,x,currentfileseconds);
	//		SetMusicPosition(a);
	//		}
	//		break;;
	//	case MU_CLOSE:
	//		{
	//			ClosePlayer();
	//		}
	//		break;
	//	case MU_MIN:
	//		{
	//			ShowPlayer(parenthwnd,per_parenthwnd,SW_HIDE);
	//		}
	//		break;
	//	case MU_VOLUME:
	//		{
	//			UISlider *tempslider=static_cast<UISlider*>(TArrayList->GetAt(10));
	//			double x=tempslider->Gsliderinfo.i3_x;
	//			//double a =MusicUtils::GetMusicPositionUsePointX(sliderwidth,x,currentfileseconds)/1000;
	//			float a=(float)(tempslider->Gsliderinfo.i3_x-tempslider->Gsliderinfo.i1_x)/(float)tempslider->Gsliderinfo.i1_width;

	//			if (volumstatus)
	//			{
	//				SetMusicVolume(a);
	//				volumstatus=0;
	//			} 
	//			else
	//			{

	//				SetMusicVolume(0);
	//				volumstatus=1;
	//			}
	//			
	//		}
	//		break;
	//	case MU_ADD:
	//		{
			   /* UIList *templist=static_cast<UIList*>(TArrayList->GetAt(13));*/
				//AddFilesToList(templist);
				///*SendMessage(parenthwnd,WM_PAINT,NULL,NULL);*/
				///* ::InvalidateRect(parenthwnd,&templist->Glistinfo.listui_rect,1);*/
				//PostMessage(parenthwnd,WM_MYREFERENCE_MESSAGE,NULL,NULL);
	//			
	//			
	//		}
	//		break;
	//	case MU_SETVOLPOSITION:
	//		{
	//			UISlider *tempslider=static_cast<UISlider*>(tcontrol);
	//			double x=tempslider->Gsliderinfo.i3_x;
	//			//double a =MusicUtils::GetMusicPositionUsePointX(sliderwidth,x,currentfileseconds)/1000;
	//		   float a=(float)(tempslider->Gsliderinfo.i3_x-tempslider->Gsliderinfo.i1_x)/(float)tempslider->Gsliderinfo.i1_width;
	//			SetMusicVolume(a);

	//		}
	//		break;
	//	case MU_MUSICLIST:
	//		{
	//			va_list argptr;
	//			va_start(argptr, tcontrol);
	//			CString mname = va_arg(argptr,CString);
	//			playstatus=1;

	//	/*		char * name = (char*)malloc(mname.GetLength()*2);
	//				wcstombs(name,mname,mname.GetLength()*2);*/
	//			int num=mname.GetLength();
	//			//char a*=new char[MAX_PATH];
	//			//strcpy(a,(LPSTR)(LPCTSTR)mname);
	//			wchar_t *k=mname.GetBuffer();
	//			char *a = MusicUtils::WideCharToMultiChar(k);
	//	/*		strcpy(this->currentfilename,a);*/
	//			//delete a;
	//			this->currentfilename=a;
	//			MusicStop(false);
	//			//CPoint point;
	//			//point.x=157;
	//			//point.y=151;
	//			playstatus=0;
	//			//SendMessage(parenthwnd,WM_LBUTTONDOWN,NULL,MAKELPARAM(156,124));
	//			//SendMessage(parenthwnd,WM_LBUTTONUP,NULL,MAKELPARAM(156,124));
	//			PostMessage(parenthwnd,WM_MYMUSICPLAY_MESSAGE,NULL,MAKELPARAM(156,124));
	//		}
	//		break;
	//	default:
	//		break;;
	//}
	
}




void ControlEvent::SetMusicVolume(float volume,HSTREAM m_stream)
{
	//BASS_SetVolume(volume);

	BASS_ChannelSetAttribute(m_stream,BASS_ATTRIB_VOL,volume);
}

void ControlEvent::SetMusicPosition(double seconds,HSTREAM m_stream)
{
	QWORD  p = BASS_ChannelSeconds2Bytes(m_stream,seconds);
 	BASS_ChannelSetPosition(m_stream,p,BASS_POS_BYTE);
}

double ControlEvent::GetMusicSeconds(QWORD len,HSTREAM m_stream)
{
	double time=BASS_ChannelBytes2Seconds(m_stream, len); // the length in seconds
	return time;
}

QWORD ControlEvent::GetMusicLength(HSTREAM m_stream)
{
	QWORD len=BASS_ChannelGetLength(m_stream, BASS_POS_BYTE); // the length in bytes
	return len;
}


double ControlEvent::GetMusicSeconds(HSTREAM m_stream)
{
	double time=BASS_ChannelBytes2Seconds(m_stream, GetMusicLength(m_stream)); // the length in seconds
	return time;
}

void ControlEvent::ShowNotifyIcon(HWND hwnd)
{
	NOTIFYICONDATA nid;
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd=parenthwnd;
	nid.uID=IDR_MAINFRAME;
	nid.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP ;
	nid.uCallbackMessage=WM_MYCLOSEWINDOW_MESSAGE;//自定义的消息名称
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy(nid.szTip,_T("静静聆听播放器"));//信息提示条为“计划任务提醒”
	Shell_NotifyIcon(NIM_ADD,&nid);//在托盘区添加图标
}

void ControlEvent::DeleteNotifyIcon(HWND hwnd)
{
	NOTIFYICONDATA nid;
	nid.hWnd=parenthwnd;
	nid.uID=IDR_MAINFRAME;
	Shell_NotifyIcon(NIM_DELETE,&nid);//在托盘区添加图标
}

void ControlEvent::ShowPlayer(HWND parenthwnd,HWND per_parenthwnd,int type)
{
	::ShowWindow(parenthwnd,type);
	::ShowWindow(per_parenthwnd,type);
	::ShowWindow(::GetParent(parenthwnd),type);
}

void ControlEvent::ShowPlayer()
{
	ShowPlayer(parenthwnd,per_parenthwnd,SW_HIDE);
}

void ControlEvent::ShowCMenu(CWnd *pcwnd)
{
	LPPOINT lpoint=new tagPOINT;
	::GetCursorPos(lpoint);//得到鼠标位置
	CMenu menu;
	menu.CreatePopupMenu();//声明一个弹出式菜单
	//增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已
	//隐藏），将程序结束。
	menu.AppendMenu(MF_STRING,IDR_MYSETTING_MESSAGE,CString("软件设置"));
	menu.AppendMenu(MF_STRING,IDR_MYWEBSITE_MESSAGE,CString("官方网站"));
	menu.AppendMenu(MF_STRING,IDR_MYCLOSE_MESSAGE,CString("关闭退出"));
	//确定弹出式菜单的位置
	menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,pcwnd);
	//资源回收
	HMENU hmenu=menu.Detach();
	menu.DestroyMenu();
	delete lpoint;
}

void ControlEvent::ClosePlayer()
{
	DeleteNotifyIcon(parenthwnd);
	::EndDialog(parenthwnd,NULL);
	::EndDialog(per_parenthwnd,NULL);
	PostQuitMessage(0);
}

void ControlEvent::CloseMusicVOL(HSTREAM m_stream,float a)
{
	//if (!volumstatus)
	//{
	//	SetMusicVolume(a,m_stream);
	//	volumstatus=1;
	//} 
	//else
	//{

		SetMusicVolume(a,m_stream);
	/*	volumstatus=0;
	}*/
}
void ControlEvent::AddFilesToList(UIList * ulist)
{
	TCHAR szFilters[]= _T("音乐文件格式 (*.mp1;*.mp2;*.mp3;*.wma;*.flac;*.aac;*.ogg;*.ape)|*.mp1;*.mp2;*.mp3;*.wma;*.flac;*.aac;*.ogg;*.ape||");
	CFileDialog fileDlg(TRUE, _T("MP3"), _T("*.mp3"),OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST, szFilters);


	//char string[15]; 
	//char *ptr, c = 'r'; 

	//strcpy(string, "This is a string"); 
	//ptr = strrchr(string, c); 

	const int MIN_FILE_NUMBER = 200;                                                           //至少允许选择10个文件
	fileDlg.m_ofn.lpstrFile = new TCHAR[_MAX_PATH * MIN_FILE_NUMBER]; //重新定义缓冲区大小          
	memset(fileDlg.m_ofn.lpstrFile, 0, _MAX_PATH * MIN_FILE_NUMBER);  //初始化定义的缓冲区
	fileDlg.m_ofn.nMaxFile = _MAX_PATH * MIN_FILE_NUMBER;
	if(fileDlg.DoModal() == IDOK)
	{ 
		//CArray<FileListInfo> templist;
		int i=0;
		POSITION pos = fileDlg.GetStartPosition();
	/*	ulist->filelistarray->SetSize(2);*/
		USES_CONVERSION;


	
		HINSTANCE hinstLib; 
		GETMYPROC ProcAdd; 
		hinstLib = LoadLibrary(TEXT("LT_MusicTags.dll")); 




		while (pos)
		{
			FileListInfo fileinfo;
			
			fileinfo.filepath=fileDlg.GetNextPathName(pos);
			
			HSTREAM m_stream_t =BASS_StreamCreateFile(FALSE,W2A(fileinfo.filepath),0,0,0);	
			if (m_stream_t!=NULL)
			{
				ProcAdd = (GETMYPROC) GetProcAddress(hinstLib, "GetMusicTilteAndArtist"); 
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
			ulist->filelistarray->Add(fileinfo);
			//i++;
		}
		ulist->SetListValue();
		ulist->GetSliderBarHeight();
		MusicUtils::LSMusicList(0,ulist->filelistarray);
		FreeLibrary(hinstLib);
	}
	else
	{
	 return;
	}
}

