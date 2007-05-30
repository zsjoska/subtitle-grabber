// SubtitleGrabber.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSubtitleGrabberApp:
// See SubtitleGrabber.cpp for the implementation of this class
//

class CUserPrefs;
class CSubtitleGrabberEngine;

class CSubtitleGrabberApp : public CWinApp
{
public:
	static inline CSubtitleGrabberApp * GetApp(){ return (CSubtitleGrabberApp *)AfxGetApp(); }

public:
	CSubtitleGrabberApp();

// Overrides
	public:
	virtual BOOL InitInstance();

	CUserPrefs * GetPreferences();

	void CreateAndStartEngine(HWND hWnd);

	inline CSubtitleGrabberEngine * Engine(){return m_pEngine;}
// Implementation

	DECLARE_MESSAGE_MAP()
private:
	CUserPrefs * m_pPrefs;
	CSubtitleGrabberEngine * m_pEngine;
};

extern CSubtitleGrabberApp theApp;