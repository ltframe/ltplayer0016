// SoftUpdate.cpp : 实现文件
//

#include "stdafx.h"
#include "LTPlayer.h"
#include "SoftUpdate.h"
#include "afxinet.h"
#include <Sensapi.h>
#include "MusicUtils.h"
// SoftUpdate 对话框
#define USERVERSION 15
IMPLEMENT_DYNAMIC(SoftUpdate, CPropertyPage)
CString GetJsonValue(CString,CString);
SoftUpdate::SoftUpdate()
	: CPropertyPage(SoftUpdate::IDD),openurl("")
{

}

SoftUpdate::~SoftUpdate()
{
}

void SoftUpdate::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//DDX_Control(pDX, IDD_SOFTUPDATE2, msgtipstatic);
	//DDX_Control(pDX, IDD_SOFTUPDATE3, msgtiperror);
	DDX_Control(pDX, IDC_GIF, m_gif);
	DDX_Control(pDX, IDC_BUTTON1, checknew);
	DDX_Control(pDX, IDC_SYSLINK2, m_link);
}


BEGIN_MESSAGE_MAP(SoftUpdate, CPropertyPage)

	ON_BN_CLICKED(IDC_BUTTON1, &SoftUpdate::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	/*ON_STN_CLICKED(IDD_SOFTUPDATE2, &SoftUpdate::OnStnClickedSoftupdate2)*/
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK2, &SoftUpdate::OnNMClickSyslink2)
END_MESSAGE_MAP()


// SoftUpdate 消息处理程序


BOOL SoftUpdate::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void SoftUpdate::OnBnClickedButton1()
{



	m_link.ShowWindow(SW_HIDE);
	m_gif.ShowWindow(SW_SHOW);
	m_gif.Load(_T("res\\checknew.gif"));
	m_gif.Draw();
	checknew.EnableWindow(FALSE);

	DWORD dw;
	if(!IsNetworkAlive(&dw))
	{
		m_gif.ShowWindow(SW_HIDE);
		m_link.ShowWindow(SW_SHOW);
		m_link.SetWindowText(_T("<a href=\"http://www.ltplayer.com/faq.html\">网络连接断开,请检查网络设置</a>"));
		checknew.EnableWindow(TRUE);
		return;
	}


	CInternetSession mysession;
	CHttpConnection *myconn=0;
	CHttpFile *myfile=0;
	mysession.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5); //重试之间的等待延时 
	mysession.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1); //重试次数 
	try
	{

		myconn=mysession.GetHttpConnection(L"127.0.0.1");
		myfile=myconn->OpenRequest(L"GET",L"/index.asp");
		if(myfile->SendRequest()==0)
		{
			m_gif.ShowWindow(SW_HIDE);
			m_link.ShowWindow(SW_SHOW);
			m_link.SetWindowText(_T("<a href=\"http://www.ltplayer.com/faq.html\">网络连接断开,请检查网络设置</a>"));
			myfile->Close();
			myconn->Close();
			mysession.Close();
			delete myfile;
			delete myconn;
			myfile=0;
			myconn=0;
			checknew.EnableWindow(TRUE);
			return;
		}

		
	}
	catch (CMemoryException* e)
	{
		myfile->Close();
		myconn->Close();
		mysession.Close();
		delete myfile;
		delete myconn;
		myfile=0;
		myconn=0;
		return;
	}
	CString mystr;
	char tmp[1024];
	while(myfile->ReadString((wchar_t*)tmp,1024))
	{
		mystr+=tmp;
	}
	myfile->Close();
	myconn->Close();
	mysession.Close();
	delete myfile;
	delete myconn;
	myfile=0;
	myconn=0;

	mystr=_T("{ptm:2012-7-16,ver:0.0.1.6}");
	CString OFVERSION =GetJsonValue(mystr,_T("ver"));
	CString OFPUBLISH =GetJsonValue(mystr,_T("ptm"));
	if(OFVERSION=="" || OFPUBLISH=="")
	{
		m_gif.ShowWindow(SW_HIDE);
		m_link.ShowWindow(SW_SHOW);
		m_link.SetWindowText(_T("<a href=\"http://www.ltplayer.com/faq.html\">网络连接断开,请检查网络设置</a>"));
		checknew.EnableWindow(TRUE);
		return;
	}
	USES_CONVERSION;
	//CString mystr=_T("0.0.1.7");
	CString newversion=OFVERSION;
	int index=0;
	OFVERSION.Remove(_T('.'));
	int versiontotal=atoi(W2A(OFVERSION));
	if(versiontotal>USERVERSION)
	{
		CString cs;
		cs.Format(_T("<a href=\"http://www.ltplayer.com/download.html\">发现最新版本%s(%s),请点击更新</a>"),newversion,OFPUBLISH);
		m_gif.ShowWindow(SW_HIDE);
		m_link.ShowWindow(SW_SHOW);
		m_link.SetWindowText(cs);
		checknew.EnableWindow(TRUE);
	}
	else
	{
		m_gif.ShowWindow(SW_HIDE);
		m_link.ShowWindow(SW_SHOW);
		m_link.SetWindowText(_T("您使用的是最新版本,无需升级"));
		checknew.EnableWindow(TRUE);

	}
}


HBRUSH SoftUpdate::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDD_SOFTUPDATE2)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
	}
	return hbr;
}

CString GetJsonValue(CString str,CString key)
{
	str.Remove('{');
	str.Remove('}');
	int index=0;
	CString resToken=str.Tokenize(_T(","),index);
	while (resToken != _T(""))
	{
		int index1=0;
		CString resToken1=resToken.Tokenize(_T(":"),index1);
		int flag=0;
		while(resToken1!=_T(""))
		{
			if (flag)
			{
				return resToken1;
			}
			if (resToken1==key)
			{
				flag=1; 
			}
			resToken1=resToken.Tokenize(_T(":"),index1);
		}
		resToken=str.Tokenize(_T(","),index);
	}
	return _T("");
}


void SoftUpdate::OnNMClickSyslink2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	PNMLINK pNMLink = (PNMLINK) pNMHDR;   
	if (wcscmp(pNMLink->item.szUrl,L"http://www.ltplayer.com/download.html"))
	{
			ShellExecute(NULL,L"open",L"http://www.ltplayer.com/download.html",NULL,NULL,SW_SHOW);
	}
	if (wcscmp(pNMLink->item.szUrl,L"http://www.ltplayer.com/faq.html"))
	{
		ShellExecute(NULL,L"open",L"http://www.ltplayer.com/faq.html",NULL,NULL,SW_SHOW);
	}
	*pResult = 0;
}
