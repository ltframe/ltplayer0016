#include "StdAfx.h"
#include "UIList.h"
#include "ControlClass.h"
UIList::UIList(WCHAR *slider,WCHAR *line,WCHAR *bg): filelistarray(new CArray<FileListInfo,FileListInfo&>()),filestartindex(0),fileitemoffset(0),barhieght(0),tandboffset(0),isdowmsilder(false),allowdrag(false),filelistarrayTemp(new CArray<FileListInfo,FileListInfo&>()),showfilecount(16),filecount(0),myFont(L"宋体", 12),listRectTmp(new RECT),m_dwFadeTick(::GetTickCount()),bt(L"res\\ACDSee.png")
{

	Drawimage.LoadResImage(slider,L"AAAAAA",m_pSrcImage1);
	Drawimage.LoadResImage(line,L"AAAAAA",m_pSrcImage2);
	format.SetAlignment(StringAlignmentNear);
	int iccc=11;
	int icccd=0;
	lastsliderbar=NULL;
	blackBrush=new SolidBrush(Color(64, 64, 64));
	blackBrush1=new SolidBrush(Color(10,255,255, 255));
	isshow=true;
	currentselected=-1;
}

UIList::~UIList(void)
{
}
RECT UIList::IRECT()
{

	/*UIList *templist=static_cast<UIList*>(ts);*/
	return this->Glistinfo.listui_rect;
}

CString UIList::ICLASSNAME()
{
	/*UIList *templist=static_cast<UIList*>(ts);*/
	return this->Glistinfo.classname;
}
CString UIList::ICLASSTYPE()
{
	return CString("UIList");
}


void UIList::IPAINT(HDC& dc)
{
	if (!isshow)
	{
		return;
	}

	HDC listhdc=CreateCompatibleDC(dc);
	void *OutPutlpBits;
	BITMAPINFO OutPutbi;
	OutPutbi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	OutPutbi.bmiHeader.biBitCount = 32;
	OutPutbi.bmiHeader.biHeight = Glistinfo.listui_height;
	OutPutbi.bmiHeader.biWidth = Glistinfo.listui_width;
	OutPutbi.bmiHeader.biPlanes = 1;
	OutPutbi.bmiHeader.biCompression=BI_RGB;
	OutPutbi.bmiHeader.biXPelsPerMeter=0;
	OutPutbi.bmiHeader.biYPelsPerMeter=0;
	OutPutbi.bmiHeader.biClrUsed=0;
	OutPutbi.bmiHeader.biClrImportant=0;
	HBITMAP listbitmap = CreateDIBSection(NULL, (BITMAPINFO *)&OutPutbi, DIB_RGB_COLORS, (void **)&OutPutlpBits, NULL, (DWORD)0);
	HBITMAP hOldBitmap =(HBITMAP)SelectObject(listhdc,listbitmap);
	HFONT hFont = Drawimage.SetTextFont(listhdc, (LPCTSTR)"宋体", 0, Glistinfo.fontsize, 0); //创建字体
	HFONT hOldFont = (HFONT)SelectObject(listhdc, hFont); 

	//HBRUSH bgbrush=CreateSolidBrush(RGB(200,200,200));
	//RECT rectw={0,0,Glistinfo.listui_width,Glistinfo.listui_height};
	//FillRect(listhdc,&rectw,bgbrush);

	int textsize = (Glistinfo.listui_width - Glistinfo.sliderbar_width)/11;
	textsize--;

	SetBkMode(listhdc,TRANSPARENT);

	showfilecount=ceil((float)Glistinfo.listui_height/(float)Glistinfo.file_height+1)+5;
	if (filecount<showfilecount)
	{
		showfilecount=filecount;
	}
	int i=0,y=0;

	filelistarrayTemp->RemoveAll();

	if (filecount!=0)
	{
		for (int id=filestartindex;id<filestartindex+showfilecount;id++)
			//for(int id=0;id<1;id++)
		{	

			FileListInfo temp;
			if(id>=filecount){
			break;
			}
			try
			{
				temp=filelistarray->GetAt(id);
			}
			catch (CException* e)
			{
				break;
			}

			if (i==0)
			{
				y=0;
			}
			else
			{
				y+=this->Glistinfo.file_height+1;
				//y+=this->Glistinfo.file_height;
			}

			int left=0;//左上角的X
			int top=0;//左上角的Y
			int r=Glistinfo.listui_width-30;//右下角的X
			int b=0;//右下角的Y


			if (y==0)
			{
				top=this->Glistinfo.listui_y;
				b=top+(this->Glistinfo.file_height-fileitemoffset);
			}
			else
			{
				top=y+this->Glistinfo.listui_y-fileitemoffset;
				b=top+this->Glistinfo.file_height;
			}

			RECT rectFF={left,top,r,b};



			FileListInfo info;
			info.filepath=filelistarray->GetAt(id).filepath;
			info.rect=rectFF;
			info.allinindex=id;
			info.filename=filelistarray->GetAt(id).filename;
			filelistarrayTemp->Add(info);
			RECT rectw={0,y,Glistinfo.listui_width,y+this->Glistinfo.file_height};
			if (temp.mousedbclick==1 && id==currentselected)
			{
				HBRUSH bgbrush=CreateSolidBrush(Glistinfo.choicebgcolor);
				
				FillRect(listhdc,&rectw,bgbrush);
				SetTextColor(listhdc,Glistinfo.choicetextcolor);
			}
			else
			{
				//HBRUSH bgbrush=CreateSolidBrush(RGB(255,0,255));
				//Brush sobrush;
				SetTextColor(listhdc,Glistinfo.textcolor);
				//RECT rectw={0,y,Glistinfo.listui_width,y+20};
				//FillRect(listhdc,&rectw,bgbrush);
				//BitBlt(listhdc,0,0,Glistinfo.listui_width,Glistinfo.file_height,singleDC,0,0,SRCCOPY);
			}
			//SetBkMode(dcMemorya,TRANSPARENT);

			//TextOut(listhdc,0,y,L"1231111111111111111111111111111111111111",40);

			//选择新字体
			CString ffname = temp.filename.Left(textsize);
			DrawText(listhdc,ffname,ffname.GetLength(),&rectw,NULL);
			//TextOut(listhdc,10,y,ffname,ffname.GetLength());
			i++;
		}
	}
	BLENDFUNCTION blendFunc32bpp;
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 255;


	for (int i=0;i<Glistinfo.listui_height*Glistinfo.listui_width;i++)
	{
		char * a=(char*)(&((UINT32*)OutPutlpBits)[i]);
		if (a[0]==0 && a[1]==0 && a[2]==0)
		{
			continue;
		}
		a[3]=255;
	}






	//????????AlphaBlend(dc,0,0,Glistinfo.listui_width,Glistinfo.listui_height,listhdc,0,0,Glistinfo.listui_width,Glistinfo.listui_height,blendFunc32bpp);
	BitBlt(dc,0,0,Glistinfo.listui_width-this->Glistinfo.sliderbar_width,Glistinfo.listui_height,listhdc,0,0,SRCCOPY);
	BitBlt(dc,Glistinfo.listui_width-this->Glistinfo.sliderbar_width,0,this->Glistinfo.sliderbar_width,barhieght,bargraphics,0,0,SRCCOPY);

	::SelectObject (listhdc,hOldBitmap);
	::DeleteObject(listbitmap);
	::DeleteObject(hOldBitmap);
	::SelectObject (listhdc,hOldFont);
	::DeleteObject(hFont);
	::DeleteObject(hOldFont);
	::DeleteDC(listhdc);
	//AlphaBlend()

/*
		HDC listhdc=CreateCompatibleDC(dc);
		void *OutPutlpBits;
		BITMAPINFO OutPutbi;
		OutPutbi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		OutPutbi.bmiHeader.biBitCount = 32;
		OutPutbi.bmiHeader.biHeight = Glistinfo.listui_height;
		OutPutbi.bmiHeader.biWidth = Glistinfo.listui_width;
		OutPutbi.bmiHeader.biPlanes = 1;
		OutPutbi.bmiHeader.biCompression=BI_RGB;
		OutPutbi.bmiHeader.biXPelsPerMeter=0;
		OutPutbi.bmiHeader.biYPelsPerMeter=0;
		OutPutbi.bmiHeader.biClrUsed=0;
		OutPutbi.bmiHeader.biClrImportant=0;
		HBITMAP listbitmap = CreateDIBSection(NULL, (BITMAPINFO *)&OutPutbi, DIB_RGB_COLORS, (void **)&OutPutlpBits, NULL, (DWORD)0);
		SelectObject(listhdc,listbitmap);



	RECT wocao={0,0,Glistinfo.listui_width,Glistinfo.listui_height};
	HBRUSH bgbrush=CreateSolidBrush(RGB(255,0,255));
	FillRect(listhdc,&wocao,bgbrush);
	for (int i=0;i<Glistinfo.listui_width*Glistinfo.listui_height;i++)
	{
		char * a=(char*)(&((UINT32*)OutPutlpBits)[i]);
		a[3]=255;
	}
	BitBlt(dc,0,0,Glistinfo.listui_width,Glistinfo.listui_height,listhdc,0,0,SRCCOPY);
*/
}

void UIList::IPAINT2(HDC& dc)
{
	//return;
	if (!isshow)
	{
		return;
	}

	HDC listhdc=CreateCompatibleDC(dc);
	//HBITMAP listbitmap=CreateCompatibleBitmap(listhdc,this->Glistinfo.listui_width,this->Glistinfo.listui_height);
	
    showfilecount=floor((float)Glistinfo.listui_height/(float)(Glistinfo.file_height+1))+5;
	if (filecount<showfilecount)
	{
		showfilecount=filecount;
	}

	void *OutPutlpBits;
	BITMAPINFO OutPutbi;
	OutPutbi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	OutPutbi.bmiHeader.biBitCount = 32;
	OutPutbi.bmiHeader.biHeight = Glistinfo.listui_height*(Glistinfo.file_height+1);
	OutPutbi.bmiHeader.biWidth = Glistinfo.listui_width;
	OutPutbi.bmiHeader.biPlanes = 1;
	OutPutbi.bmiHeader.biCompression=BI_RGB;
	OutPutbi.bmiHeader.biXPelsPerMeter=0;
	OutPutbi.bmiHeader.biYPelsPerMeter=0;
	OutPutbi.bmiHeader.biClrUsed=0;
	OutPutbi.bmiHeader.biClrImportant=0;
	HBITMAP listbitmap = CreateDIBSection(NULL, (BITMAPINFO *)&OutPutbi, DIB_RGB_COLORS, (void **)&OutPutlpBits, NULL, (DWORD)0);

	//if (OutPutlpBits==0)
	//{
	//	return;
	//}

	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(listhdc,listbitmap);
	//Bitmap *bitmap=new Bitmap(this->Glistinfo.listui_width,(this->Glistinfo.file_height+1)*showfilecount);
	
	
	HFONT hFont = Drawimage.SetTextFont(listhdc, (LPCTSTR)"宋体", 0, Glistinfo.fontsize, 0); //创建字体
	HFONT hOldFont = (HFONT)::SelectObject(listhdc, hFont);  
	
	SetBkMode(listhdc,TRANSPARENT);


	int textsize = (Glistinfo.listui_width - Glistinfo.sliderbar_width)/11;

	textsize--;
	

	int i=0,y=0;

	filelistarrayTemp->RemoveAll();

	if (filecount!=0)
	{
		for (int id=filestartindex;id<filestartindex+showfilecount;id++)
		//for(int id=0;id<1;id++)
		{	
			FileListInfo temp;
			if(id>=filecount){
			break;
			}

			try
			{
				temp=filelistarray->GetAt(id);
			}
			catch (CException* e)
			{
				break;
			}

			if (i==0)
			{
				y=0;
			}
			else
			{
				y+=this->Glistinfo.file_height+1;
				//y+=this->Glistinfo.file_height;
			}

			int left=0;//左上角的X
			int top=0;//左上角的Y
			int r=Glistinfo.listui_width-30;//右下角的X
			int b=0;//右下角的Y


			if (y==0)
			{
				top=this->Glistinfo.listui_y;
				b=top+(this->Glistinfo.file_height-fileitemoffset);
			}
			else
			{
				top=y+this->Glistinfo.listui_y-fileitemoffset;
				b=top+this->Glistinfo.file_height;
			}

			RECT rectFF={left,top,r,b};

			

			FileListInfo info;
			info.filepath=filelistarray->GetAt(id).filepath;
			info.rect=rectFF;
			info.allinindex=id;
			info.filename=filelistarray->GetAt(id).filename;
			filelistarrayTemp->Add(info);
			RECT rectw={0,y,Glistinfo.listui_width,y+this->Glistinfo.file_height};
			if (temp.mousedbclick==1 && id==currentselected)
			{
				//blackBrush->SetColor(Color(255,250,250));
				//blackBrush1->SetColor(Color(255,192,224,248));
				HBRUSH bgbrush=CreateSolidBrush(Glistinfo.choicebgcolor);
				
				FillRect(listhdc,&rectw,bgbrush);
				SetTextColor(listhdc,Glistinfo.choicetextcolor);
			}
			else
			{
				//HBRUSH bgbrush=CreateSolidBrush(RGB(255,0,255));
				////Brush sobrush;
				SetTextColor(listhdc,Glistinfo.textcolor);
				//RECT rectw={0,y,Glistinfo.listui_width,y+20};
				//FillRect(listhdc,&rectw,bgbrush);
				//BitBlt(listhdc,0,0,Glistinfo.listui_width,Glistinfo.file_height,singleDC,0,0,SRCCOPY);
			}
			//SetBkMode(dcMemorya,TRANSPARENT);
			
			//TextOut(listhdc,0,y,L"1231111111111111111111111111111111111111",40);

                       //选择新字体
			CString ffname = temp.filename.Left(textsize);
			//TextOut(listhdc,10,y,ffname,ffname.GetLength());
			DrawText(listhdc,ffname,ffname.GetLength(),&rectw,NULL);
			i++;
		}
	}

	//TextOut(listhdc,0,0,L"55555",5);


	for (int i=0;i<Glistinfo.listui_height*(Glistinfo.file_height+1)*Glistinfo.listui_width;i++)
	{
		int att =GetLastError();
		char * a=(char*)(&((UINT32*)OutPutlpBits)[i]);
		if (a[0]==0 && a[1]==0 && a[2]==0)
		{
			continue;
		}
		a[3]=255;
	}


	//
	//	HBRUSH bgbrush=CreateSolidBrush(RGB(255,0,255));
	//FillRect(dc,&Glistinfo.listui_rect,bgbrush);
	BitBlt(dc,Glistinfo.listui_x,Glistinfo.listui_y,Glistinfo.listui_width,Glistinfo.listui_height,listhdc,0,fileitemoffset,SRCCOPY);
	BitBlt(dc,Glistinfo.listui_width-this->Glistinfo.sliderbar_width+this->Glistinfo.listui_x,this->Glistinfo.sliderbar_y+Glistinfo.listui_y,this->Glistinfo.sliderbar_width,barhieght,bargraphics,0,0,SRCCOPY);


	::SelectObject (listhdc,hOldBitmap);
	::DeleteObject(listbitmap);
	::DeleteObject(hOldBitmap);
	::SelectObject (listhdc,hOldFont);
	::DeleteObject(hFont);
	::DeleteObject(hOldFont);
	::DeleteDC(listhdc);

}

bool UIList::ILBUTTONDBCLICK(HWND hwnd,CPoint point)
{
	if (::GetTickCount()-m_dwFadeTick<500UL)
	{
		return false;
	}
	for (int i=0;i<filelistarrayTemp->GetSize();i++)
	{
		if(::PtInRect(&filelistarrayTemp->GetAt(i).rect,point))
		{
			/*CString cs;
			cs.Format(_T("%s"),filelistarrayTemp->GetAt(i).filename);
			CString mname=filelistarrayTemp->GetAt(i).filepath;
			UIFileListInfo info;
			info.filename=mname;
			info.filepath=cs;*/
			UIFileListInfo info=filelistarrayTemp->GetAt(i);
			GetColorIndex(info.allinindex);
			/* UIList *templist=static_cast<UIList*>(ArrayList->GetAt(13));*/
			
			icontrolevent->SetListContorEvent(this->Glistinfo,info);
			m_dwFadeTick=::GetTickCount();
			return true;
			break; 
		}
	}
}

void UIList::GetColorIndex(int index)
{
	currentselected=index;
	for (int i=0;i<filelistarrayTemp->GetCount();i++)
	{
		FileListInfo info=filelistarrayTemp->GetAt(i);
		if(info.allinindex==index)
		{
			filelistarray->GetAt(info.allinindex).mousedbclick=1;
		}
		else
		{
			filelistarray->GetAt(info.allinindex).mousedbclick=0;
		}
	}
}


bool UIList::IMOUSELEAVE(HWND hwnd,bool rp)
{
	allowdrag=false;
	//::InvalidateRect(hwnd,&this->Glistinfo.listui_rect,1);
	//::UpdateWindow(hwnd);
	return true;

}
bool UIList::ILBUTTONDOWN(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,bool & m_bMouseTracking)
{
	if (listRectTmp->left<0)
	{
		listRectTmp->left=this->Glistinfo.listui_x;
		listRectTmp->top=this->Glistinfo.listui_y;
		listRectTmp->right=this->Glistinfo.listui_x+273-this->Glistinfo.sliderbar_width;
		listRectTmp->bottom=this->Glistinfo.listui_y+this->Glistinfo.listui_height;
	}
	///*RECT listRectTmp;

	/*allowdrag=false;*/
	if (!::PtInRect(listRectTmp,point))
	{
		allowdrag=true;
		tandboffset=point.y-this->Glistinfo.sliderbar_y;
	}
	else
	{
		for (int i=0;i<filelistarrayTemp->GetSize();i++)
		{
			FileListInfo info=filelistarrayTemp->GetAt(i);
			if(::PtInRect(&info.rect,point))
				filelistarray->GetAt(info.allinindex).mousehovered=1;
			else
				filelistarray->GetAt(info.allinindex).mousehovered=0;
		}	
		//::InvalidateRect(hwnd,&this->Glistinfo.listui_rect,1);
		//::UpdateWindow(hwnd);
	}
	return true;
}
bool UIList::ILBUTTONUP(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList)
{
	//isdowmsilder=false;
	allowdrag=false;
	//::InvalidateRect(hwnd,&this->Glistinfo.listui_rect,1);
	//::UpdateWindow(hwnd);

	return true;
}

bool UIList::IMOUSEHOVER(HWND hwnd,IControl *ts,CArray<LPVOID,LPVOID&> *ArrayList,CPoint point,int controlid)
{
	//RECT *listRectTmp=new RECT;
	//listRectTmp->left=this->Glistinfo.listui_x;
	//listRectTmp->top=this->Glistinfo.listui_y;
	//listRectTmp->right=this->Glistinfo.listui_x+this->Glistinfo.listui_width-this->Glistinfo.sliderbar_width;
	//listRectTmp->bottom=this->Glistinfo.listui_y+this->Glistinfo.listui_height;

	/*
	if (listRectTmp->left<0)
	{
		listRectTmp->left=this->Glistinfo.listui_x;
		listRectTmp->top=this->Glistinfo.listui_y;
		listRectTmp->right=this->Glistinfo.listui_x+this->Glistinfo.listui_width-this->Glistinfo.sliderbar_width;
		listRectTmp->bottom=this->Glistinfo.listui_y+this->Glistinfo.listui_height;
	}
	if (::PtInRect(listRectTmp,point))
	{
		for (int i=0;i<filelistarrayTemp->GetSize();i++)
		{
			FileListInfo info=filelistarrayTemp->GetAt(i);
			if(::PtInRect(&info.rect,point))
				filelistarray->GetAt(info.allinindex).mousehovered=1;
			else
				filelistarray->GetAt(info.allinindex).mousehovered=0;
		}	
		
	}*/
	//::InvalidateRect(hwnd,&this->Glistinfo.listui_rect,1);
	//::UpdateWindow(hwnd);
	//delete listRectTmp;
	//::InvalidateRect(hwnd,&this->Glistinfo.listui_rect,1);
	//::UpdateWindow(hwnd);
	return true;

}
bool UIList::IMOUSEMOVE(HWND hwnd,IControl *ts,CPoint point)
{


		if (allowdrag)
		{


			/*UIList *templist=static_cast<UIList*>(ts);*/
			/*UIListInfo sinfo=this->Glistinfo;*/
			///*FileListInfo finfo=templist->Gfileinfo;*/

		ResetSliderBarPos(point);



	
		}	
		return true;
		//::InvalidateRect(hwnd,&this->Glistinfo.listui_rect,1);
		//	::UpdateWindow(hwnd);
}

void UIList::ResetSliderBarPos(CPoint point)
{
	this->Glistinfo.sliderbar_y=((point.y)-tandboffset);//
	if (this->Glistinfo.sliderbar_y<=0)
	{
		this->Glistinfo.sliderbar_y=0;
		//::InvalidateRect(hwnd,&this->Glistinfo.listui_rect,1);
		//::UpdateWindow(hwnd);
		/*return;*/
	}
	if (this->Glistinfo.sliderbar_y+barhieght>=this->Glistinfo.listui_height)
	{
		this->Glistinfo.sliderbar_y=this->Glistinfo.listui_height-barhieght;
		//::InvalidateRect(hwnd,&this->Glistinfo.listui_rect,1);
		//::UpdateWindow(hwnd);
		/*return;*/
	}


	int realfileheight=this->Glistinfo.file_height+1;//this->Glistinfo.setpint;
	int ty=(this->Glistinfo.sliderbar_y-this->Glistinfo.listui_offset)*this->Glistinfo.setpint;//从sliderbar头到listUI头的距离
	//fileitemoffset = ty%sinfo.file_height*this->Glistinfo.setpint;//滑动ty距离会跳走多少个文件
	fileitemoffset = ty%realfileheight;//是否会产生一个偏离量5
	if(ty<realfileheight)//如果滑动距离不足一个文件高度
	{
		filestartindex=0;
	}
	else
	{
		float a=(float)ty/(float)realfileheight;
		filestartindex=ceil(a);

		if(fileitemoffset!=0){
			if(filestartindex>1)
				filestartindex--;
		}
	}
	CString cs;
	cs.Format(_T("height:%d,ty:%d,startindex:%d"),this->Glistinfo.listui_height,ty,filestartindex);

	ControlClass::ConsoleWrite(ControlClass::IntFormatCString(CString("值"),cs));
}

void UIList::GetSliderBarHeight()
{
	/*this->Glistinfo.sliderbar_height=16;*/
	/*int filecount=filelistarray->GetSize();*/


	barhieght  = 0;
	int allfilehight=filecount*(this->Glistinfo.file_height+1);
	int middlehight=0;
	int tandbhight=8;//滑动条的头部和下部分
	//if (allfilehight>this->Glistinfo.listui_height)
	//{
		if (allfilehight>=this->Glistinfo.listui_height*2)
		{
			barhieght=tandbhight*2;
			/*this->Glistinfo.setpint=((allfilehight-barhieght)/(this->Glistinfo.listui_height-40));*/
		}
		else
		{
			if (allfilehight>this->Glistinfo.listui_height)
			{
				barhieght=this->Glistinfo.listui_height-(allfilehight-this->Glistinfo.listui_height);
		/*		this->Glistinfo.setpint=1;
				this->Glistinfo.setpint=*/
				middlehight=barhieght-(tandbhight*2);
			}
			
		}
	//}
	this->Glistinfo.setpint=(float)((allfilehight-this->Glistinfo.listui_height)/(float)(this->Glistinfo.listui_height-barhieght));
	int startint=this->Glistinfo.sliderbar_height;
	

	bargraphics=CreateCompatibleDC(GetDC(0));
	void *OutPutlpBits;
	BITMAPINFO OutPutbi;
	OutPutbi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	OutPutbi.bmiHeader.biBitCount = 32;
	OutPutbi.bmiHeader.biHeight = barhieght;
	OutPutbi.bmiHeader.biWidth = this->Glistinfo.sliderbar_width;
	OutPutbi.bmiHeader.biPlanes = 1;
	OutPutbi.bmiHeader.biCompression=BI_RGB;
	OutPutbi.bmiHeader.biXPelsPerMeter=0;
	OutPutbi.bmiHeader.biYPelsPerMeter=0;
	OutPutbi.bmiHeader.biClrUsed=0;
	OutPutbi.bmiHeader.biClrImportant=0;
	HBITMAP listbitmap = CreateDIBSection(NULL, (BITMAPINFO *)&OutPutbi, DIB_RGB_COLORS, (void **)&OutPutlpBits, NULL, (DWORD)0);
	SelectObject(bargraphics,listbitmap);

	//上面圆头部分
	Drawimage.BitDrawControl(m_pSrcImage1,bargraphics,0,0,this->Glistinfo.sliderbar_width,tandbhight,0,0);
	if (middlehight!=0)
	{
		//Drawimage.BitDrawControl(m_pSrcImage1,bargraphics,0,tandbhight,this->Glistinfo.sliderbar_width,middlehight,0,tandbhight);
		Drawimage.BitDrawStretch(m_pSrcImage1,bargraphics,0,tandbhight,this->Glistinfo.sliderbar_width,middlehight,0,tandbhight,this->Glistinfo.sliderbar_width,Glistinfo.sliderbar_height-(tandbhight*2));

		Drawimage.BitDrawControl(m_pSrcImage1,bargraphics,0,middlehight+tandbhight,this->Glistinfo.sliderbar_width,tandbhight,0,this->Glistinfo.sliderbar_height-tandbhight);
	} 
	else
	{
//bargraphics->DrawImage(m_pSrcImage1,0,20,0,this->Glistinfo.sliderbar_height-20,this->Glistinfo.sliderbar_width,20,(Unit)2);
		Drawimage.BitDrawControl(m_pSrcImage1,bargraphics,0,tandbhight,this->Glistinfo.sliderbar_width,tandbhight,0,this->Glistinfo.sliderbar_height-(tandbhight));
	}


	/*
	//lastsliderbar=new Bitmap(this->Glistinfo.sliderbar_width,barhieght);
	//bargraphics=new Graphics(lastsliderbar);
	//bargraphics->DrawImage(m_pSrcImage1,0,0,0,0,this->Glistinfo.sliderbar_width,tandbhight,(Unit)2);
	if (middlehight!=0)
	{
		//中间平头部分
		bargraphics->DrawImage(m_pSrcImage1,0,tandbhight,0,tandbhight,this->Glistinfo.sliderbar_width,middlehight,(Unit)2);
		//下面的部分
		bargraphics->DrawImage(m_pSrcImage1,0,middlehight+tandbhight,0,this->Glistinfo.sliderbar_height-tandbhight,this->Glistinfo.sliderbar_width,tandbhight,(Unit)2);


		////////////////////////////////////
		Drawimage.BitDrawControl(m_pSrcImage1,)
	}
	else{
		bargraphics->DrawImage(m_pSrcImage1,0,20,0,this->Glistinfo.sliderbar_height-20,this->Glistinfo.sliderbar_width,20,(Unit)2);
	}
	delete bargraphics;
	*/
	
} 

bool UIList::DeleteList()
{
	filelistarray->RemoveAll();
	filelistarrayTemp->RemoveAll();
	filecount=0;
	barhieght=0;
	filestartindex=0;
	/*showfilecount=0;*/
	Glistinfo.sliderbar_y=0;
	return true;
}

int UIList::GetListCount()
{

	return this->filelistarray->GetSize();
}
void UIList::SetListValue()
{
	filecount=filelistarray->GetCount();
	showfilecount=17;
	if (filecount<showfilecount)
	{
		showfilecount=filecount;
	}
	/*filelistarrayTemp->RemoveAll();
	filelistarrayTemp->SetSize(showfilecount);*/
}

void UIList::SetFileIndex(HWND hwnd,int index,int pn)
{

	//for (int i=0;i<filelistarrayTemp->GetSize();i++)
	//{

	//	if (filelistarrayTemp->GetAt(i).allinindex==index)
	//	{
	//		GetColorIndex(index);
	//		fileitemoffset=0;
	//		return;
	//	}
	//}
	///////////////////////////////////////////
	int realfileheight=this->Glistinfo.file_height+1;//取得一条记录实际的高度，文件高度+分割线（1）
	int realuioutputcount= 0;
	int newfileitemoffset = this->Glistinfo.listui_height%realfileheight;
	//计算当前列表高度里可以显示几条记录
	realuioutputcount = ceil((float)(this->Glistinfo.listui_height/realfileheight));




	////////////////////////////////////////////
	if (pn)
	{
		filestartindex=index-(realuioutputcount);
	}
	else{
		filestartindex=index;
	}
	if (filestartindex<0)
	{
		filestartindex=0;
	}
	UIListInfo sinfo=this->Glistinfo;
	int t=filestartindex*(sinfo.file_height+1);
	this->Glistinfo.sliderbar_y=ceil((float)t/(float)this->Glistinfo.setpint)+sinfo.listui_offset;
	/*::InvalidateRect(hwnd,&sinfo.listui_rect,1);*/
	filelistarrayTemp->RemoveAll();
	for (int id=filestartindex;id<filestartindex+showfilecount;id++)
	{	
		FileListInfo info;
		info.allinindex=id;
		filelistarrayTemp->Add(info);
	}
	fileitemoffset=(realfileheight-newfileitemoffset);
	GetColorIndex(index);
	//filelistarray->GetAt(index).mousehovered=1;
	
	//::UpdateWindow(hwnd);
}

int UIList::IWIDTH()
{
	return this->Glistinfo.listui_width;
}
int UIList::IHIGH()
{
	//return (this->Glistinfo.file_height+1)*showfilecount;
	return this->Glistinfo.listui_height;
}

void UIList::IHIDE()
{
	this->Glistinfo.listui_rect.left=-1;
	this->Glistinfo.listui_rect.top=-1;
	this->Glistinfo.listui_rect.right=-1;
	this->Glistinfo.listui_rect.bottom=-1;
}
void UIList::ISHOW()
{
	ControlClass *controlclass=new ControlClass();
	this->Glistinfo.listui_rect = controlclass->GetRect(Glistinfo.listui_x,Glistinfo.listui_y,Glistinfo.listui_width,Glistinfo.listui_height);
	delete controlclass;
}

void UIList::SetStepInt()
{
	int allfilehight=filecount*(this->Glistinfo.file_height+1);
	this->Glistinfo.setpint=(float)((allfilehight-this->Glistinfo.listui_height)/(float)(this->Glistinfo.listui_height-barhieght));
}