#pragma once

// windows message from thread to window
#define WM_THREADCOMMAND (WM_USER + 100)

#define TH_COMMAND_DISPLAY_STATUS 0

class CSubtitleGrabberEngine
{
public:
	CSubtitleGrabberEngine(HWND hWnd);
	~CSubtitleGrabberEngine(void);
	void Start();
	void Stop();

	void RequestLangList();

private:
	// worker thread functions
	void QueryLangList();

private:
	CWnd * m_pMainWnd;
	CWinThread * m_pThread;

	static UINT ThreadProc(LPVOID pParam);
};

