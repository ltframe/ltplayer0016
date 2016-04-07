// LTPlayerDlg.h : 头文件
//

#pragma once
#include "DrawImages.h"
#include "ConstValues.h"
#include "ControlPanelDlg.h"
#include "FrameShadowDlg.h"

// CLTPlayerDlg 对话框
class CLTPlayerDlg : public CDialog
{
// 构造
public:
	CLTPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CLTPlayerDlg();
// 对话框数据
	enum { IDD = IDD_LTPLAYER_DIALOG };
	/*ControlPanelDlg *m_ControlPanelDlg;*/
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	ControlPanelDlg *m_ControlPanelDlg;
	FrameShadowDlg *m_FrameShadowDlg;
	DrawImages Drawimage;
	Bitmap*bgimgsrc;
	Bitmap*setbgsrc;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMove(int x, int y);
	void SetIniValue(LPCTSTR key ,LPCTSTR str);
	void SetIniValue(LPCTSTR key ,LPCTSTR str,LPCSTR funname);
	afx_msg LRESULT OnSetBgAlpha(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetBgImg(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDropFiles(HDROP hDropInfo);
};