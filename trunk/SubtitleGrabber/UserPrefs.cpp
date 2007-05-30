#include "StdAfx.h"
#include "UserPrefs.h"

LPCTSTR CUserPrefs::pszSection = _T("UserPref");
LPCTSTR CUserPrefs::pszUser = _T("username");
LPCTSTR CUserPrefs::pszPass = _T("password");
LPCTSTR CUserPrefs::pszPath = _T("path");
LPCTSTR CUserPrefs::pszLang = _T("languages");

CUserPrefs::CUserPrefs(void)
{
}

CUserPrefs::~CUserPrefs(void)
{
}

BOOL CUserPrefs::ReadPreferences()
{
	CWinApp * pApp = AfxGetApp();
	m_strUser = pApp->GetProfileString(pszSection, pszUser, _T(""));
	m_strPassword = pApp->GetProfileString(pszSection, pszPass, _T(""));
	m_strBasedir = pApp->GetProfileString(pszSection, pszPath, _T(""));
	m_strLang = pApp->GetProfileString(pszSection, pszLang, _T(""));
	return TRUE;
}

BOOL CUserPrefs::SavePreferences()
{
	CWinApp * pApp = AfxGetApp();
	pApp->WriteProfileString(pszSection, pszUser, m_strUser);
	pApp->WriteProfileString(pszSection, pszPass, m_strPassword);
	pApp->WriteProfileString(pszSection, pszPath, m_strBasedir);
	pApp->WriteProfileString(pszSection, pszLang, m_strLang);
	return TRUE;
}

CString CUserPrefs::GetUsername()
{
	return m_strUser;
}

CString CUserPrefs::GetPassword()
{
	return m_strPassword;
}

CString CUserPrefs::GetBasePath()
{
	return m_strBasedir;
}

CString CUserPrefs::GetLangString()
{
	return m_strLang;
}

void CUserPrefs::SetUsername(CString user)
{
	m_strUser = user;
}

void CUserPrefs::SetPassword(CString pass)
{
	m_strPassword = pass;
}

void CUserPrefs::SetBasePath(CString path)
{
	m_strBasedir = path;
}

void CUserPrefs::SetLangString(CString langstr)
{
	m_strLang = langstr;
}
