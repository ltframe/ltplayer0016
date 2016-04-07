#pragma once


// FileJoin 对话框

class FileJoin : public CPropertyPage
{
	DECLARE_DYNAMIC(FileJoin)

public:
	FileJoin();
	virtual ~FileJoin();

// 对话框数据
	enum { IDD = IDD_FILEJOIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void OnOK();
	BOOL RegisterFileRelation( const CString& strExtension,  
		const CString& strApplicationName,
		const CString& strRunKey,
		const CString& strDefaultIcon,  
		const CString& strDescription );
	DECLARE_MESSAGE_MAP()
};
