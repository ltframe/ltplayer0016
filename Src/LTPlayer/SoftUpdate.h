#pragma once
#include "afxwin.h"
#include "HyperLink.h"
#include "PictureEx.h"
// SoftUpdate 对话框

class SoftUpdate : public CPropertyPage
{
	DECLARE_DYNAMIC(SoftUpdate)

public:
	SoftUpdate();
	virtual ~SoftUpdate();

// 对话框数据
	enum { IDD = IDD_SOFTUPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CString openurl;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	/*afx_msg void OnStnClickedSoftupdate2();*/
	//CStatic msgtipstatic;

	CPictureEx m_gif;
	CButton checknew;
	afx_msg void OnNMClickSyslink2(NMHDR *pNMHDR, LRESULT *pResult);
	CLinkCtrl m_link;
};
