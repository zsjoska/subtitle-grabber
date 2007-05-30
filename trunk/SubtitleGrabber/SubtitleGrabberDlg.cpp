// SubtitleGrabberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SubtitleGrabber.h"
#include "SubtitleGrabberDlg.h"
#include "UserPrefs.h"
#include "SubtitleGrabberEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSubtitleGrabberDlg dialog




CSubtitleGrabberDlg::CSubtitleGrabberDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubtitleGrabberDlg::IDD, pParent)
	, m_strPath(_T(""))
	, m_strUser(_T(""))
	, m_strPassword(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSubtitleGrabberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PATH, m_strPath);
	DDX_Text(pDX, IDC_USERNAME, m_strUser);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	DDX_Control(pDX, IDC_LISTAVAIL, m_ListAvail);
	DDX_Control(pDX, IDC_LISTSELECTED, m_ListSelected);
	DDX_Control(pDX, IDC_STATUS, m_StaticStatus);
}

BEGIN_MESSAGE_MAP(CSubtitleGrabberDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_FLDSELECT, &CSubtitleGrabberDlg::OnBnClickedFldselect)
	ON_BN_CLICKED(IDOK, &CSubtitleGrabberDlg::OnBnClickedOk)
	ON_LBN_DBLCLK(IDC_LISTAVAIL, &CSubtitleGrabberDlg::OnLbnDblclkListavail)
	ON_LBN_DBLCLK(IDC_LISTSELECTED, &CSubtitleGrabberDlg::OnLbnDblclkListselected)
	ON_MESSAGE(WM_THREADCOMMAND, OnThreadMessage)
END_MESSAGE_MAP()


// CSubtitleGrabberDlg message handlers

BOOL CSubtitleGrabberDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CUserPrefs * pPrefs = CSubtitleGrabberApp::GetApp()->GetPreferences();
	m_strPath = pPrefs->GetBasePath();
	m_strUser = pPrefs->GetUsername();
	m_strPassword = pPrefs->GetPassword();

	FillListBox(m_ListAvail, _T("EN RO HUN BUL"));
	FillListBox(m_ListSelected, pPrefs->GetLangString());

	UpdateData(FALSE);

	CSubtitleGrabberApp::GetApp()->CreateAndStartEngine(GetSafeHwnd());

	CSubtitleGrabberApp::GetApp()->Engine()->RequestLangList();
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSubtitleGrabberDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSubtitleGrabberDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSubtitleGrabberDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSubtitleGrabberDlg::OnBnClickedFldselect()
{
	CString Result;
	CString strMessage;

	strMessage.LoadString(IDS_SELECT_FOLDER);

	BROWSEINFO BrowseInfo;
	memset(&BrowseInfo, 0, sizeof(BrowseInfo));

	TCHAR szBuffer[MAX_PATH];

	BrowseInfo.hwndOwner      = m_hWnd;
	BrowseInfo.pszDisplayName = szBuffer;
	BrowseInfo.lpszTitle      = strMessage;
	BrowseInfo.ulFlags        = BIF_RETURNONLYFSDIRS;

	// Throw display dialog
	LPITEMIDLIST pList = SHBrowseForFolder(&BrowseInfo);
	ASSERT(_tcslen(szBuffer) < sizeof(szBuffer));

	if (pList != NULL)
	{
		// Convert from MIDLISt to real string path
		SHGetPathFromIDList(pList, szBuffer);
		Result = szBuffer;

		// Global pointer to the shell's IMalloc interface.  
		LPMALLOC pMalloc; 

		// Get the shell's allocator and free the PIDL returned by
		// SHBrowseForFolder.
		if (SUCCEEDED(SHGetMalloc(&pMalloc))) 
			pMalloc->Free(pList);
	}

	m_strPath = Result;
	UpdateData(FALSE);
}

void CSubtitleGrabberDlg::OnBnClickedOk()
{
	UpdateData();
	CUserPrefs * pPrefs = CSubtitleGrabberApp::GetApp()->GetPreferences();
	pPrefs->SetBasePath(m_strPath);
	pPrefs->SetUsername(m_strUser);
	pPrefs->SetPassword(m_strPassword);
	pPrefs->SavePreferences();
	pPrefs->SetLangString(MakeLangString(m_ListSelected));
	OnOK();
}

void CSubtitleGrabberDlg::FillListBox(CListBox & listBox, CString strTokens)
{
	strTokens = strTokens.Trim() + _T(" ");
	int iPos = strTokens.Find(' ');
	while (iPos > 0)
	{
		listBox.AddString(strTokens.Left(iPos));
		strTokens.Delete(0, iPos + 1);
		iPos = strTokens.Find(' ');
	}
}

CString CSubtitleGrabberDlg::MakeLangString(CListBox & listBox)
{
	CString strMade;
	for (int i = 0; i < listBox.GetCount(); i++)
	{
		CString strTemp;
		listBox.GetText(i,strTemp);
		strMade += strTemp + _T(" ");
	}
	return strMade.Trim();
}

void CSubtitleGrabberDlg::OnLbnDblclkListavail()
{
	int iSel = m_ListAvail.GetCurSel();
	if (iSel >= 0 )
	{
		CString strTemp;
		m_ListAvail.GetText(iSel, strTemp);
		if(m_ListSelected.FindStringExact(0, strTemp) < 0)
		{
			m_ListSelected.AddString(strTemp);
		}
	}
}

void CSubtitleGrabberDlg::OnLbnDblclkListselected()
{
	int iSel = m_ListSelected.GetCurSel();
	if (iSel >= 0 )
	{
		m_ListSelected.DeleteString(iSel);
	}
}

LRESULT CSubtitleGrabberDlg::OnThreadMessage(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case TH_COMMAND_DISPLAY_STATUS:
		m_StaticStatus.SetWindowText((LPCTSTR)lParam);
		break;
	default:
	    break;
	}
	return 0;
}
