// UiSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "LTPlayer.h"
#include "UiSetting.h"
#include "MusicUtils.h"
#include <direct.h> 
#include "DrawImages.h"
// UiSetting 对话框

IMPLEMENT_DYNAMIC(UiSetting, CPropertyPage)

UiSetting::UiSetting()
	: CPropertyPage(UiSetting::IDD),skinlist(new CImageList())
{
	skinlist->Create(32, 32, ILC_COLOR16, 4, 4);
	currentusebgimage = MusicUtils::GetConfigXml(L"skin",L"");
}

UiSetting::~UiSetting()
{
	int sssssssss= 0 ;
}

void UiSetting::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, alphipos);
	DDX_Control(pDX, IDC_LIST1, Image_bgList);
	DDX_Control(pDX, IDC_CHECK1, enablealpha);
}


BEGIN_MESSAGE_MAP(UiSetting, CPropertyPage)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK1, &UiSetting::OnBnClickedCheck1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &UiSetting::OnNMClickList1)
//	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &UiSetting::OnNMDblclkList1)
ON_NOTIFY(NM_RCLICK, IDC_LIST1, &UiSetting::OnNMRClickList1)
ON_BN_CLICKED(IDC_BUTTON1, &UiSetting::OnBnClickedButton1)
END_MESSAGE_MAP()


void UiSetting::OnOK()
{
	int a= alphipos.GetPos();
	wchar_t *st;
	st= (wchar_t*)malloc(_MAX_PATH);
	ZeroMemory(st,wcslen(st));
	_itow(abs(a-255)==0?1:abs(a-255),st,10);
	MusicUtils::WriteConfigXml(L"transparent",st,"SetPlayerConfigValue");
	free(st);
}

// UiSetting 消息处理程序

void UiSetting::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int a= alphipos.GetPos();
	if (a==255)
	{
		a=254;
	}
	::PostMessage(AfxGetMainWnd()->m_hWnd,WM_ONSETBGALPHA_MESSAGE,NULL,abs(a-255));
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL UiSetting::OnInitDialog()
{
 	CDialog::OnInitDialog();

	strcpy(modulepath,MusicUtils::GetModulePathA());
    int entransparent = _wtoi(MusicUtils::GetConfigXml(L"entransparent",L"255"));
	if (entransparent)
	{
		alphipos.EnableWindow(TRUE);
		enablealpha.SetCheck(BST_CHECKED);

	}

	alphipos.SetRangeMin(0);
	alphipos.SetRangeMax(255);

	Image_bgList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	Image_bgList.SetIconSpacing(CSize(45, 40));     //set pictures spacing
	Image_bgList.SetBkColor(GetSysColor(0));

	//MusicUtils::ScanFile(_T("skin\\"),filearray,CString("bmp"));
	//CArray<UiSkinInfo,UiSkinInfo&> *carray;
	if (filearray.GetCount()==0)
	{
		MusicUtils::LSSkinList(1,&filearray);
	}
	
	

	

	
	for (int i = 0;i<filearray.GetCount();i++)
	{
		CArray<CString,CString&> carray;
		UiSkinInfo info = filearray.GetAt(i);
		MusicUtils::SpliteCString(info.fname,carray,_T("."));
		CString sname =CString("skin\\") + info.id + CString("\\") + carray.ElementAt(0) + CString("_s.bmp");
		HBITMAP   hBitmap   =   (HBITMAP)LoadImage(NULL,sname,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE); 
		CBitmap * hcbitmpa =CBitmap::FromHandle(hBitmap);
		skinlist->Add(hcbitmpa,RGB(0,0,0));
		Image_bgList.SetImageList(skinlist,LVSIL_NORMAL);
		Image_bgList.InsertItem(i, NULL,i); 
		DeleteObject(hBitmap);
	}



	//HBITMAP   _hBitmap   =   (HBITMAP)LoadImage(NULL,CString("skin\\system\\addskin_s.bmp"),IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE); 
	//CBitmap * _hcbitmpa =CBitmap::FromHandle(_hBitmap);
	//skinlist->Add(_hcbitmpa,RGB(0,0,0));
	//Image_bgList.InsertItem(skinlist->GetImageCount()-1, NULL,skinlist->GetImageCount()-1); 



	alphipos.SetPos(abs(_wtoi(MusicUtils::GetConfigXml(L"transparent",L"255"))-255));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
	
}

void UiSetting::OnStnClickedbg1()
{

	int a= alphipos.GetPos();
	::PostMessage(AfxGetMainWnd()->m_hWnd,WM_ONSETBGIMG_MESSAGE,1,abs(a-255));
	//SetSkin(1);
	// TODO: 在此添加控件通知处理程序代码
}

void UiSetting::OnStnClickedbg2()
{
	int a= alphipos.GetPos();
	::PostMessage(AfxGetMainWnd()->m_hWnd,WM_ONSETBGIMG_MESSAGE,2,abs(a-255));
	//SetSkin(2);
	// TODO: 在此添加控件通知处理程序代码
}

void UiSetting::OnStnClickedbg3()
{
	int a= alphipos.GetPos();
	::PostMessage(AfxGetMainWnd()->m_hWnd,WM_ONSETBGIMG_MESSAGE,3,abs(a-255));
	//SetSkin(3);
	// TODO: 在此添加控件通知处理程序代码
}

void UiSetting::OnStnClickedbg4()
{
	int a= alphipos.GetPos();
	::PostMessage(AfxGetMainWnd()->m_hWnd,WM_ONSETBGIMG_MESSAGE,4,abs(a-255));
	//SetSkin(4);
	// TODO: 在此添加控件通知处理程序代码
}


void UiSetting::SetSkin(CString i)
{
	//wchar_t *st;
	//st= (wchar_t*)malloc(_MAX_PATH);
	//ZeroMemory(st,wcslen(st));
	//_itow(i,st,10);
	USES_CONVERSION;
	MusicUtils::WriteConfigXml(L"skin",i,"SetPlayerConfigValue");
	//free(st);
}

void UiSetting::OnBnClickedCheck1()
{
	CButton* opena = (CButton*)GetDlgItem(IDC_CHECK1);
	opena->EnableWindow(FALSE);
	int type = 0;
	if (opena->GetCheck())
	{
		alphipos.EnableWindow(TRUE);
		type = ::PostMessage(AfxGetMainWnd()->m_hWnd,WM_ACTIVATE_MESSAGE,1,0);
	}
	else{
		alphipos.EnableWindow(FALSE);
		type = ::PostMessage(AfxGetMainWnd()->m_hWnd,WM_ACTIVATE_MESSAGE,0,0);
	}
	if (type)
	{
		opena->EnableWindow(TRUE);
	}
	/*	OnOK();*/
}

void UiSetting::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{

	NM_LISTVIEW *info=(NM_LISTVIEW*)pNMHDR;
	if (info->iItem==-1)
	{
		return;
	}

	//int D = Image_bgList.GetItemCount();
	//if (Image_bgList.GetItemCount()-1 == info->iItem)
	//{
	//	
	//	TCHAR szFilters[]= _T("图片文件格式 (*.jpg;*.png;*.bmp)|*.jpg;*.png;*.bmp||");
	//	CFileDialog fileDlg(TRUE, _T("bmp"), _T("*.bmp"),OFN_FILEMUSTEXIST, szFilters);
	//	//const int MIN_FILE_NUMBER = 200;                                                           //至少允许选择10个文件
	//	//fileDlg.m_ofn.lpstrFile = new TCHAR[MAX_PATH * MIN_FILE_NUMBER]; //重新定义缓冲区大小          
	//	//memset(fileDlg.m_ofn.lpstrFile, 0, _MAX_PATH * MIN_FILE_NUMBER);  //初始化定义的缓冲区
	//	//if(fileDlg.DoModal() == IDOK)
	//	//{
	//	//	CString pathName = fileDlg.GetPathName();
	//	//	//fileDlg.GetFolderPath();

	//	//	char  sourcepath[MAX_PATH] ={0}; 
	//	//	strcat(sourcepath,modulepath);
	//	//	strcat(sourcepath,"\skin");
	//	//	MakeSkin(pathName,sourcepath);


	//	//}


	//}else
	//{
	
		UiSkinInfo *sinfo = &(filearray.GetAt(info->iItem));
		//CString name = sinfo.fname;
		//CString id = sinfo.id;
		//int maskcolor = sinfo.maskcolor; 

		int a= alphipos.GetPos();

		Image_bgList.EnableWindow(FALSE);
		/*CString *wpcstring = new CString(CString(id) + L"|" + name);*/
		SetSkin(sinfo->id);
		if(::PostMessage(AfxGetMainWnd()->m_hWnd,WM_ONSETBGIMG_MESSAGE,(WPARAM)sinfo,abs(a-255)))
		{
			currentusebgimage = sinfo->id;
			Image_bgList.EnableWindow(TRUE);

		}

	//}

	*pResult = 0; 
}

//void UiSetting::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}

void UiSetting::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW *info=(NM_LISTVIEW*)pNMHDR;
	if (info->iItem==-1)
	{
		return;
	}

	UiSkinInfo sinfo = filearray.GetAt(info->iItem);
	CString name = sinfo.fname;
	CString id = sinfo.id;
	if (MusicUtils::IsStrInStrAarry(MusicUtils::ConverI2W(info->iItem),L"0,1,2,3") || !currentusebgimage.Compare(id))
	{
		return;
	}

	if (MessageBox(_T("确定要删除这个背景吗？删除是不可恢复的"),_T("标题"), MB_ICONWARNING |MB_OKCANCEL )==IDOK)
	{
		Image_bgList.DeleteItem(info->iItem);
		MusicUtils::EmptyDir(CString(modulepath) + CString("skin\\")+id);
		//USES_CONVERSION;
		int x = _wrmdir(CString(modulepath) + CString("skin\\")+id);
		filearray.RemoveAt(info->iItem);
		MusicUtils::LSSkinList(0,&filearray);
	}
}


void UiSetting::MakeSkin(CString filename,char* sourcepath)
{
	USES_CONVERSION;
	int tpathindex=filename.ReverseFind('\\');
	CString name=MusicUtils::GetSubString(filename,tpathindex);
	char ppppp[MAX_PATH]={0};
	ZeroMemory(ppppp,MAX_PATH);
	char *  guid = MusicUtils::newGUID();
	strcpy(ppppp,MusicUtils::CreatePlayerDir(sourcepath,guid));
	
	CString tttttt= A2W(ppppp);
	CString namepath = tttttt+CString("\\")+CString(name);

	//CArray<CString,CString&> arrays;
	//MusicUtils::SpliteCString(name,arrays,_T("."));

	char abc[20];
	strcpy(abc,MusicUtils::CreateTimeFileName());
	CString filetimename = CString(abc);

	CString smallname = filetimename+CString("_s")+CString(".bmp");
	//CopyFile(filename,namepath,TRUE);


     int skinlistcount = skinlist->GetImageCount();
	//skinlist->Remove(skinlist->GetImageCount()-1);

	skinlistcount = skinlist->GetImageCount();

	HBITMAP hbitmapA = MusicUtils::GetStretchHBITMAP(filename,::GetDC(m_hWnd),32,32);
	MusicUtils::SaveBitMapToFile(hbitmapA,tttttt + CString("\\") +  smallname);
	HBITMAP   hBitmap   =   (HBITMAP)LoadImage(NULL,tttttt + CString("\\")+ smallname,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE); 
	CBitmap * hcbitmpa =CBitmap::FromHandle(hBitmap);
	skinlist->Add(hcbitmpa,RGB(0,0,0));
	
    skinlistcount = skinlist->GetImageCount();




	DrawImages drawimages;
	Bitmap *bt =new Bitmap(filename);

	COLORREF maskcolor = drawimages.MakeFrameBgImage(bt,guid,filetimename,modulepath);


	skinlistcount = skinlist->GetImageCount();

	int x = skinlist->GetImageCount()-1;
	//Image_bgList.DeleteItem(x);
	Image_bgList.InsertItem(x, NULL,x); 



	//HBITMAP   syshbitmap   =   (HBITMAP)LoadImage(NULL,CString("skin\\system\\addskin_s.bmp"),IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_DEFAULTSIZE|LR_LOADFROMFILE); 
	//CBitmap *sysbitmap=CBitmap::FromHandle(syshbitmap);
	//skinlist->Add(sysbitmap,RGB(0,0,0));
	//x = Image_bgList.GetItemCount();
	//Image_bgList.InsertItem(x, NULL,x); 


	UiSkinInfo info={A2W(guid),maskcolor,filetimename+CString(".bmp")};
	filearray.Add(info);


	MusicUtils::LSSkinList(0,&filearray);
}


void UiSetting::OnBnClickedButton1()
{
		TCHAR szFilters[]= _T("图片文件格式 (*.jpg;*.png;*.bmp)|*.jpg;*.png;*.bmp||");
		CFileDialog fileDlg(TRUE, _T("bmp"), _T("*.bmp"),OFN_FILEMUSTEXIST, szFilters);
		const int MIN_FILE_NUMBER = 200;                                                           //至少允许选择10个文件
		fileDlg.m_ofn.lpstrFile = new TCHAR[MAX_PATH * MIN_FILE_NUMBER]; //重新定义缓冲区大小          
		memset(fileDlg.m_ofn.lpstrFile, 0, _MAX_PATH * MIN_FILE_NUMBER);  //初始化定义的缓冲区
		if(fileDlg.DoModal() == IDOK)
		{
			CString pathName = fileDlg.GetPathName();
			//fileDlg.GetFolderPath();

			char  sourcepath[MAX_PATH] ={0}; 
			strcat(sourcepath,modulepath);
			strcat(sourcepath,"\skin");
			MakeSkin(pathName,sourcepath);
		}
}