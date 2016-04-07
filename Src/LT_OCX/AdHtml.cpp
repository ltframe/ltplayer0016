// AdHtml.cpp : 实现文件
//

#include "stdafx.h"
#include "LT_OCX.h"
#include "AdHtml.h"


// AdHtml 对话框

IMPLEMENT_DYNCREATE(AdHtml, CDHtmlDialog)

AdHtml::AdHtml(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(AdHtml::IDD, AdHtml::IDH, pParent)
{

}

AdHtml::~AdHtml()
{
	DestroyWindow();
}

void AdHtml::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL AdHtml::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	//ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
	SetWindowLong(this-> GetSafeHwnd(),GWL_EXSTYLE, WS_EX_TOOLWINDOW|WS_EX_STATICEDGE); 
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(AdHtml, CDHtmlDialog)

	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(AdHtml)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)

END_DHTML_EVENT_MAP()



// AdHtml 消息处理程序

HRESULT AdHtml::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT AdHtml::OnButtonCancel(IHTMLElement* /*pElement*/)
{

		OnCancel();
	return S_OK;
}

void AdHtml::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	//DestroyWindow();
	//PostThreadMessage()

	//CDHtmlDialog::PostNcDestroy();

}

int AdHtml::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDHtmlDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

void AdHtml::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDHtmlDialog::OnClose();
}
