#pragma once

class CHTTPResponse;
class CHTTPRequest;

class CHTTPTransport
{
public:
	CHTTPTransport(void);
	~CHTTPTransport(void);
	BOOL Close();
	BOOL Open(CString strServer);
	CHTTPResponse * DoRequest(CHTTPRequest * pRequest);
	inline int GetTransportError(){return m_iTransportError;}

	static BOOL InitTransport();

private:
	CString m_strServerName;
	int m_nPort;
	SOCKET m_Sock;
	int m_iTransportError;
};
