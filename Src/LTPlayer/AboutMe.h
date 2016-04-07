#pragma once

// AboutMe 对话框

class AboutMe : public CPropertyPage
{
	DECLARE_DYNAMIC(AboutMe)

public:
	AboutMe();   // 标准构造函数
	virtual ~AboutMe();
// 对话框数据
	enum { IDD = IDD_ABOUTSOFT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnNMClickSyslink2(NMHDR *pNMHDR, LRESULT *pResult);
};
