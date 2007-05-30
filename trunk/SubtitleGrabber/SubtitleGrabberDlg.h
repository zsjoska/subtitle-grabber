// SubtitleGrabberDlg.h : header file
//

#pragma once
#include "afxwin.h"



// CSubtitleGrabberDlg dialog
class CSubtitleGrabberDlg : public CDialog
{
// Construction
public:
	CSubtitleGrabberDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SUBTITLEGRABBER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedFldselect();
	afx_msg void OnBnClickedOk();
public:
	// the path selected by the user
	CString m_strPath;
	CString m_strUser;
	CString m_strPassword;
	CListBox m_ListAvail;
	CListBox m_ListSelected;

	void FillListBox(CListBox & listBox, CString strTokens);
	CString MakeLangString(CListBox & listBox);
public:
	afx_msg void OnLbnDblclkListavail();
public:
	afx_msg void OnLbnDblclkListselected();

	afx_msg LRESULT OnThreadMessage(WPARAM wParam, LPARAM lParam);
public:
	CStatic m_StaticStatus;
};
