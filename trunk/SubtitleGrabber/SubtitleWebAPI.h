#pragma once

class CSubtitleWebAPI
{
public:
	CSubtitleWebAPI(void);
	~CSubtitleWebAPI(void);

	BOOL CheckOnline();
	BOOL Authenticate(CString user, CString password);
	
	CString GetAvailableLanguages();

	CString UploadSubtitle(CString strHash, LPBYTE pFile);

	BOOL DownloadSubtitle(CString nonce, CString hash, CString langPref, LPBYTE * pBuff);
private:
	static LPCTSTR pszServerURL;

	BOOL	m_bOnline;
	CString m_strSessionID;
	CString m_strNonce;
};
