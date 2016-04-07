#pragma once
#include "afxcmn.h"
#include "ConstValues.h"
#include "afxwin.h"
#include "UIInterface.h"

// UiSetting 对话框

class UiSetting : public CPropertyPage
{
	DECLARE_DYNAMIC(UiSetting)

public:
	UiSetting();   // 标准构造函数
	virtual ~UiSetting();

// 对话框数据
	enum { IDD = IDD_UISETTING };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void OnOK();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl alphipos;
	CArray<UiSkinInfo,UiSkinInfo&> filearray;
	virtual BOOL OnInitDialog();
	CImageList *skinlist;
	afx_msg void OnStnClickedbg1();
	afx_msg void OnStnClickedbg2();
	afx_msg void OnStnClickedbg3();
	afx_msg void OnStnClickedbg4();
	void SetSkin(CString i);
	afx_msg void OnBnClickedCheck1();
	CListCtrl Image_bgList;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	CButton enablealpha;
//	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	void MakeSkin(CString filename,char* sourcepath);
private:
	char  modulepath[MAX_PATH];
	CString currentusebgimage;
public:
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton1();
};
