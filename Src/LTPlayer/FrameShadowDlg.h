#pragma once

#include "DrawImages.h"
#include "ConstValues.h"
// FrameShadowDlg 对话框

class FrameShadowDlg : public CDialog
{
	DECLARE_DYNAMIC(FrameShadowDlg)

public:
	FrameShadowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FrameShadowDlg();

// 对话框数据
	enum { IDD = IDD_FRAMESHADOWDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DrawImages Drawimage;
	Bitmap*bgimgsrc;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMove(int x, int y);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
