#pragma once

class CHTTPContent;
class CHTTPResponse;
class CHTTPRequest;

#include "HTTPTransport.h"

class CHTTP
{
public:

	static const TCHAR CRLF[3];


	CHTTP(void);
	~CHTTP(void);

	CHTTPResponse * ExecuteRequest(CHTTPRequest * request);
	inline int GetTransportError(){ return (m_pTransport == NULL ? ERROR_NOT_READY:m_pTransport->GetTransportError()); }

private:
	BOOL m_bUseProxy;
	CString m_strLastServer;
	BOOL m_bKeepAlive;
	CHTTPTransport * m_pTransport;
};
