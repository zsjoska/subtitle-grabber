// SubtitleGrabber.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SubtitleGrabber.h"
#include "SubtitleGrabberDlg.h"
#include "HTTPRequest.h"
#include "HTTP.h"
#include "HTTPResponse.h"
#include "HTTPTransport.h"
#include "UserPrefs.h"
#include "SubtitleGrabberEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSubtitleGrabberApp

BEGIN_MESSAGE_MAP(CSubtitleGrabberApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSubtitleGrabberApp construction

CSubtitleGrabberApp::CSubtitleGrabberApp()
{
	m_pPrefs = NULL;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CSubtitleGrabberApp object

CSubtitleGrabberApp theApp;


// CSubtitleGrabberApp initialization

BOOL CSubtitleGrabberApp::InitInstance()
{

	/*
	CHTTPTransport::InitTransport();
	CHTTP http;

	CHTTPRequest  * req = new CHTTPRequest();
	req->SetRequestURL(_T("http://zsjoska"));
	CHTTPResponse * pRsp = http.ExecuteRequest(req);
	if (pRsp != NULL)
	{
		AfxMessageBox( pRsp->GetHeaderString() + _T("\n") + pRsp->GetContent() );
		delete pRsp;
	}else {
		AfxMessageBox( GetStringError(http.GetTransportError()) );
	}
	delete req;

	req = new CHTTPRequest();
	req->SetRequestURL(_T("http://zsjoska"));
	pRsp = http.ExecuteRequest(req);
	if (pRsp != NULL)
	{
		AfxMessageBox( pRsp->GetHeaderString() + _T("\n") + pRsp->GetContent() );
		delete pRsp;
	} else {
		AfxMessageBox( GetStringError(http.GetTransportError()) );
	}
	delete req;
	/**/

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	SetRegistryKey(_T("SubtitleGrabber"));

	CSubtitleGrabberDlg dlg;
	m_pMainWnd = &dlg;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	m_pEngine->Stop();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

CUserPrefs * CSubtitleGrabberApp::GetPreferences()
{
	if (m_pPrefs == NULL)
	{
		m_pPrefs = new CUserPrefs;
		m_pPrefs->ReadPreferences();
	}
	return m_pPrefs;
}

void CSubtitleGrabberApp::CreateAndStartEngine(HWND hWnd)
{
	m_pEngine = new CSubtitleGrabberEngine(hWnd);
	m_pEngine->Start();
}
