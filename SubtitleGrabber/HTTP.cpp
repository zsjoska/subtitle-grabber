#include "StdAfx.h"
#include "HTTP.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "HTTPTransport.h"

const TCHAR CHTTP::CRLF[3]=_T("\r\n");


CHTTP::CHTTP(void)
{
	m_bUseProxy = FALSE;
	m_strLastServer = _T("");
	m_bKeepAlive = FALSE;
	m_pTransport = new CHTTPTransport;
}

CHTTP::~CHTTP(void)
{
	if (m_pTransport != NULL)
	{
		if (m_bKeepAlive)
		{
			m_bKeepAlive = FALSE;
			m_pTransport->Close();
		}
		delete m_pTransport;
		m_pTransport = NULL;
	}
}

CHTTPResponse * CHTTP::ExecuteRequest(CHTTPRequest * pRequest)
{
	BOOL bCanUseKeepalive = pRequest->CanPersist();

	if (m_bKeepAlive && !bCanUseKeepalive)
	{
		m_bKeepAlive = FALSE;
		m_pTransport->Close();
	}

	if (m_bKeepAlive && pRequest->GetServer() != m_strLastServer)
	{
		m_bKeepAlive = FALSE;
		m_pTransport->Close();
	}

	BOOL bConnected = FALSE;

	if (!m_bKeepAlive)
	{
		m_strLastServer = pRequest->GetServer();
		bConnected = m_pTransport->Open(m_strLastServer);
	}

	if (!bConnected)
	{
		return NULL;
	}

	CHTTPResponse * pResponse = m_pTransport->DoRequest(pRequest);

	if (pResponse == NULL)
	{
		m_bKeepAlive = FALSE;

	} else {

		if (bCanUseKeepalive && pResponse->CanPersist())
		{
			m_bKeepAlive = TRUE;
		} else {
			m_bKeepAlive = FALSE;
		}
	}

	if (!m_bKeepAlive)
	{
		m_pTransport->Close();
	}
	
	return pResponse;
}
