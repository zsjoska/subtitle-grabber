#pragma once

class CUserPrefs
{
public:
	CUserPrefs(void);
	~CUserPrefs(void);

	BOOL ReadPreferences();
	BOOL SavePreferences();

	CString GetUsername();
	CString GetPassword();

	CString GetBasePath();
	CString GetLangString();

	void SetUsername(CString user);
	void SetPassword(CString pass);

	void SetBasePath(CString path);
	void SetLangString(CString langstr);

private:
	CString m_strUser;
	CString m_strPassword;
	CString m_strBasedir;
	CString m_strLang;

	static LPCTSTR pszSection;
	static LPCTSTR pszUser;
	static LPCTSTR pszPass;
	static LPCTSTR pszPath;
	static LPCTSTR pszLang; 
};

