#pragma once

class CVC2019RedistDlg : public CDialogEx
{
public:
	CVC2019RedistDlg(CWnd* pParent = nullptr);	// standard constructor

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VC2019_REDIST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

private:
	void InitLib();
	void UnZiPfile(CString strCurrentPath);
	BOOL GetReourceFiles(CString strFileName, CString strResourceID, UINT nID);
	BOOL SetUnZipFolder(CString strCurrentPath, CString strFilePath = L"");

	rediSetup Setupobj;
	BOOL bTimer;
};
