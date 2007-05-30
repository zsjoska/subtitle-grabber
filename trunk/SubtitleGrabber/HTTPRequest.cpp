#include "StdAfx.h"
#include "HTTPRequest.h"
#include "HTTP.h"

CHTTPRequest::CHTTPRequest(void)
{
	m_strMethod = _T("GET");
	m_strUri = _T("");
	m_strServer = _T("");
	m_strHTTPVer = _T("HTTP/1.1");
}

CHTTPRequest::~CHTTPRequest(void)
{
}

void CHTTPRequest::SetRequestURL( CString strURL)
{
	if (strURL.Find(_T("http://"))==0)
	{
		strURL.Delete(0, 7);
	}
	int srvEnd = strURL.Find('/');
	if (srvEnd < 0 )
	{
		m_strUri = _T("/");
		m_strServer = strURL;
	} else {
		m_strServer = strURL.Left(srvEnd);
		m_strUri = strURL.Mid(srvEnd);
	}
	FormatCommand();
}

void CHTTPRequest::SetMethod(CString strMethod)
{
	m_strMethod = strMethod;
	FormatCommand();
}

void CHTTPRequest::SetHTTPVersion(CString strHttp)
{
	m_strHTTPVer = strHttp;
	FormatCommand();
}

void CHTTPRequest::FormatCommand()
{
	CString strCommand = m_strMethod + _T(" ") + m_strUri + _T(" ") + m_strHTTPVer;
	SetTitle(strCommand);
}

BOOL CHTTPRequest::CanPersist()
{
	return m_strHTTPVer == _T("HTTP/1.1") && GetHeaderField(_T("Connection"))!= _T("close");
}

LPCSTR CHTTPRequest::PrepareRequest(int & iSendCount)
{
	int bodyLen = 0;

	LPCSTR pszBody = ConvertFromWide(CP_UTF8, GetContent(), bodyLen);
	delete [] pszBody;

	TCHAR szBuff[12];
	_itot_s(bodyLen-1, szBuff, 11, 10); 
	// bodyLen-1 since the trailing \0 must not be counted
	// 11 bytes buffer, base 10

	// the mandatory HTTP fields
	SetHeaderString(_T("Content-Length"), szBuff );
	SetHeaderString(_T("Host"), GetServer());

	CString request = GetTitle() + CHTTP::CRLF + GetHeaderString() + CHTTP::CRLF + GetContent();

	LPCSTR pszReq = ConvertFromWide(CP_UTF8, request, iSendCount);

	// the iSendCount now contains a +1=\n we have to decrement it here since this must not be sent to the server
	iSendCount--;

	return pszReq;
}
