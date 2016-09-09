#pragma once


// CLogDlg dialog

class CLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogDlg)

public:
	CLogDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLogDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOG_DIALOG };
#endif
	enum { WM_TEXT = WM_USER + 1};

protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	void OnOK() override {}
	void OnCancel() override {}

	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnText(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnSizing(UINT nSide, LPRECT lpRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	CString m_csLog;
	CEdit m_ctrlLog;
};
