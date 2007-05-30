#pragma once
#include "httpcontent.h"

class CHTTPRequest :
	public CHTTPContent
{
public:
	CHTTPRequest(void);
	~CHTTPRequest(void);

	void SetRequestURL( CString strURL);
	void SetMethod(CString strMethod);
	void SetHTTPVersion(CString strHttp);

	inline CString GetServer(){ return m_strServer; }
	LPCSTR PrepareRequest(int & iSendCount);
	BOOL CanPersist();
private:
	CString m_strMethod;
	CString m_strUri;
	CString m_strServer;
	CString m_strHTTPVer;
	void FormatCommand();

};
