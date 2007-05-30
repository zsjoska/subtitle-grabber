#include "StdAfx.h"
#include "HTTPResponse.h"
#include "StringConversion.h"
#include "HTTP.h"

CHTTPResponse::CHTTPResponse(void)
{
}

CHTTPResponse::~CHTTPResponse(void)
{
}

BOOL CHTTPResponse::CanPersist()
{
	return m_strHTTPVer == _T("HTTP/1.1") && GetHeaderField(_T("Connection")) != _T("close");
}

void CHTTPResponse::BeginConstruct()
{
	m_readBuffer.clear();
}

void CHTTPResponse::AddBuffer(LPCSTR pBuffer, int nSize)
{
	for (int i = 0; i < nSize; i++)
	{
		m_readBuffer.push_back(*pBuffer++);
	}
}

int CHTTPResponse::EndConstructHeader(BOOL bTransportFinish)
{
	// the byte sequence now is as-is. for the string conversion function we have to append a \0
	m_readBuffer.push_back(0);

	CString strRspHeders = ConvertToCString(CP_ACP,&m_readBuffer[0], (int)m_readBuffer.size());

	m_readBuffer.clear();

	int iPos = strRspHeders.Find(CHTTP::CRLF);

	if (iPos <= 0)
	{
		// the server response is unrecognizable
		return 0;
	}

	SetTitle(strRspHeders.Left(iPos));
	ParseAndFillHeaders();

	while (iPos > 0)
	{
		strRspHeders.Delete(0, iPos + 2);
		iPos = strRspHeders.Find(CHTTP::CRLF);
		if (iPos > 0)
		{
			CString strTemp = strRspHeders.Left(iPos);
			int iColPos = strTemp.Find(':');
			if (iColPos > 0)
			{
				SetHeaderString(strTemp.Left(iColPos).Trim(), strTemp.Mid(iColPos + 2).Trim());
			}
		}
	}

	return GetNumericHeaderField(_T("Content-Length"));	
}

void CHTTPResponse::EndConstructBody(BOOL bTransportFinish)
{
	// the byte sequence now is as-is. for the string conversion function we have to append a \0
	m_readBuffer.push_back(0);

	// TODO: get the charset heder and cuse the correct codepage
	SetContent(ConvertToCString(CP_ACP,&m_readBuffer[0], (int)m_readBuffer.size()));
}

void CHTTPResponse::ParseAndFillHeaders()
{
	CString strHTTPStatus = _T("");
	CString strTitle = GetTitle().Trim(_T(" \r\n"));
	int iPos = strTitle.Find(' ');
	if (iPos > 0)
	{
		m_strHTTPVer = strTitle.Left(iPos);
		strTitle.Delete(0,iPos);
		strTitle = strTitle.Trim();
		int iPos = strTitle.Find(' ');
		if (iPos > 0)
		{
			strHTTPStatus = strTitle.Left(iPos);
			strTitle.Delete(0,iPos);
			strTitle = strTitle.Trim();
			if (iPos > 0)
			{
				m_strServerMessage = strTitle;
			}
		}

	}

	m_nHTTPStatus = 0;
	if (strHTTPStatus != _T(""))
	{
		m_nHTTPStatus =_ttoi(strHTTPStatus);
	}

}
