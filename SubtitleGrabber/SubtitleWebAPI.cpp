#include "StdAfx.h"
#include "SubtitleWebAPI.h"

LPCTSTR CSubtitleWebAPI::pszServerURL= _T("http://zsjoska/");


CSubtitleWebAPI::CSubtitleWebAPI(void)
{
	m_bOnline = FALSE;
	m_strNonce = _T("");
	m_strSessionID = _T("");
}

CSubtitleWebAPI::~CSubtitleWebAPI(void)
{
}

BOOL CSubtitleWebAPI::CheckOnline()
{
	return FALSE;
}

BOOL CSubtitleWebAPI::Authenticate(CString user, CString password)
{
	return FALSE;
}

CString CSubtitleWebAPI::GetAvailableLanguages()
{
	return _T("");
}

CString CSubtitleWebAPI::UploadSubtitle(CString strHash, LPBYTE pFile)
{
	return _T("");
}

BOOL CSubtitleWebAPI::DownloadSubtitle(CString nonce, CString hash, CString langPref, LPBYTE * pBuff)
{
	return FALSE;
}
