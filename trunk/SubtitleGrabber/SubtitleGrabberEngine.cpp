#include "StdAfx.h"
#include "SubtitleGrabberEngine.h"

#define THREADMSG_REQ_LANGLIST WM_USER +1

CSubtitleGrabberEngine::CSubtitleGrabberEngine(HWND hWnd)
{
	m_pMainWnd = CWnd::FromHandle(hWnd);
}

CSubtitleGrabberEngine::~CSubtitleGrabberEngine(void)
{
}

void CSubtitleGrabberEngine::Start()
{
	m_pThread = AfxBeginThread((AFX_THREADPROC)(ThreadProc),(LPVOID)this);
}


void CSubtitleGrabberEngine::Stop()
{
	m_pThread->PostThreadMessage(WM_QUIT, 0, 0);
	WaitForSingleObject(m_pThread->m_hThread, INFINITE);
}

UINT CSubtitleGrabberEngine::ThreadProc(LPVOID pParam)
{
	MSG msg;
	CSubtitleGrabberEngine * pEngine = (CSubtitleGrabberEngine *)pParam;
	while (GetMessage( &msg , NULL, 0, 0))
	{

		switch(msg.message)
		{
		case THREADMSG_REQ_LANGLIST:
			pEngine->QueryLangList();
			break;
		}
	}
	return 0;
}

void CSubtitleGrabberEngine::RequestLangList()
{
	m_pThread->PostThreadMessage(THREADMSG_REQ_LANGLIST, 0, NULL);
}

void CSubtitleGrabberEngine::QueryLangList()
{
	m_pMainWnd->SendMessage(WM_THREADCOMMAND, TH_COMMAND_DISPLAY_STATUS, (LPARAM)_T("Reading language list..."));
}
