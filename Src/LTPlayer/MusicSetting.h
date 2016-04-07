#pragma once
#include "afxwin.h"
#include "bass.h"

// MusicSetting 对话框

class MusicSetting : public CPropertyPage
{
	DECLARE_DYNAMIC(MusicSetting)

public:
	MusicSetting();
	virtual ~MusicSetting();

// 对话框数据
	enum { IDD = IDD_MUSICSETTIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	//CComboBox outdevice;
	CComboBox affect;
	void OnOK();
	bool GetAutoStart();
	void SetAutoStart(int i);
	afx_msg void OnCbnSelchangeCombo1();
};
