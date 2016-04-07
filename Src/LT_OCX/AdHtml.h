#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CDHtmlDialog。"
#endif 

// AdHtml 对话框

class AdHtml : public CDHtmlDialog
{
	DECLARE_DYNCREATE(AdHtml)

public:
	AdHtml(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AdHtml();
// 重写
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);
	STDMETHOD(ShowContextMenu)(
		DWORD dwID,
		POINT * ppt,
		IUnknown * pcmdtReserved,
		IDispatch * pdispReserved 
		)
	{
		return S_OK;
	}
// 对话框数据
	enum { IDD = IDD_DIALOG1, IDH = IDR_HTML_ADHTML };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
};
