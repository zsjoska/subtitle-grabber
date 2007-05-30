#include "StdAfx.h"
#include "HTTPTransport.h"
#include "HTTPResponse.h"
#include "HTTPRequest.h"

CHTTPTransport::CHTTPTransport(void)
{
	m_iTransportError = ERROR_SUCCESS;
}

CHTTPTransport::~CHTTPTransport(void)
{
}

CHTTPResponse * CHTTPTransport::DoRequest(CHTTPRequest * pRequest)
{
	CHTTPResponse * pRetResponse = NULL;
	int sendCount, iByteCount;
	BOOL bSentOK = FALSE;

	m_iTransportError = ERROR_SUCCESS;

	LPCSTR preqData = pRequest->PrepareRequest(sendCount);
	if (sendCount > 0 && preqData!= NULL)
	{
		int iByteCount = send(m_Sock, (char*)preqData, sendCount, 0);

		if (iByteCount != SOCKET_ERROR)
		{
			if ( iByteCount == sendCount )
			{
				bSentOK = TRUE;
			} else {
				AfxMessageBox(_T("CHTTPTransport::DoRequest - iSentCount!=sendCount"));
			}
		} else {
			m_iTransportError = WSAGetLastError();
		}

		delete [] preqData;
		preqData = NULL;

	} else {
		// preqData was NULL; string conversion error
		m_iTransportError = GetLastError();
	}

	if (!bSentOK)
	{
		return pRetResponse; // which is NULL;
	}

	#define BUFF_LEN 2048
	// No pending allocation here. would be a good idea to split this function

	LPSTR pRespBuffer = new CHAR[BUFF_LEN + 2];
	pRetResponse = new CHTTPResponse();

	// read the headers first
	pRetResponse->BeginConstruct();

	iByteCount = recv(m_Sock, pRespBuffer, 1, 0);
	BOOL bHeadEnd = FALSE, bNewline = FALSE;

	while (iByteCount > 0)
	{
		pRetResponse->AddBuffer(pRespBuffer, iByteCount);
		if (*pRespBuffer == '\n')
		{
			if (bNewline)	{ bHeadEnd = TRUE; break;}
			else bNewline = TRUE;
		} else {
			if (*pRespBuffer!= '\r')	bNewline = FALSE;
		}
		iByteCount = recv(m_Sock, pRespBuffer, 1, 0);
	}

	if (iByteCount == SOCKET_ERROR)
	{
		m_iTransportError = WSAGetLastError();
		delete [] pRespBuffer; pRespBuffer = NULL;
		delete pRetResponse; pRetResponse = NULL;
		return pRetResponse;
	}

	int nContLength = pRetResponse->EndConstructHeader( bHeadEnd );

	if (bHeadEnd && nContLength > 0)
	{
		// read the headers first
		pRetResponse->BeginConstruct();


		while (iByteCount > 0)
		{
			if (nContLength == 0)
				break;
			iByteCount = recv(m_Sock, pRespBuffer, nContLength > BUFF_LEN ? BUFF_LEN:nContLength, 0);
			if (iByteCount == SOCKET_ERROR)
			{
				break;
			}
			nContLength -= iByteCount;
			pRetResponse->AddBuffer(pRespBuffer, iByteCount);
		}

		if (iByteCount == SOCKET_ERROR)
		{
			m_iTransportError = WSAGetLastError();
			delete [] pRespBuffer; pRespBuffer = NULL;
			delete pRetResponse; pRetResponse = NULL;
			return pRetResponse;
		}

		pRetResponse->EndConstructBody(nContLength == 0);
	}

	delete [] pRespBuffer;

	return pRetResponse;
}

BOOL CHTTPTransport::Close()
{
	m_iTransportError = ERROR_SUCCESS;
	BOOL bRetVal = closesocket( m_Sock ) != SOCKET_ERROR;
	if (!bRetVal)
		m_iTransportError = WSAGetLastError();
	m_Sock = INVALID_SOCKET;
	return bRetVal;
}

BOOL CHTTPTransport::Open(CString strServer)
{
	int iSrvEnd = strServer.Find(':');
	if (iSrvEnd < 0)
	{
		m_strServerName = strServer;
		m_nPort = 80;
	}else {
		m_strServerName = strServer.Left(iSrvEnd);
		strServer.Delete(0, iSrvEnd+1);
		m_nPort = _ttoi(strServer);
	}

	int iRetVal = 0;
	LPCSTR pszHost = ConvertFromWide(CP_ACP, m_strServerName, iRetVal);

	if (pszHost == NULL)
	{
		// no allocation made yet... so safe to return
		m_iTransportError = GetLastError();
		return FALSE;
	}

	iRetVal = ERROR_SUCCESS;

	HOSTENT * pHERemote = NULL;
	pHERemote = gethostbyname( pszHost );

	if (pHERemote != NULL )
	{
		struct sockaddr_in in_Addr;

		memset( &in_Addr, 0, sizeof( in_Addr ) );
		memcpy( &( in_Addr.sin_addr ), pHERemote->h_addr, pHERemote->h_length );
		in_Addr.sin_family = pHERemote->h_addrtype;
		in_Addr.sin_port = htons( m_nPort );

		m_Sock = socket( AF_INET, SOCK_STREAM, 0 );
		if ( m_Sock != INVALID_SOCKET) {

				iRetVal = connect( m_Sock, (struct sockaddr*)&in_Addr, sizeof( in_Addr ) );

				if ( iRetVal != ERROR_SUCCESS ) {

					// the connect failed. We get now the important error code and close the socket later
					m_iTransportError = WSAGetLastError();
					closesocket( m_Sock );
					m_Sock = INVALID_SOCKET;
				}

		} else {
			// the socket creation failed
			m_Sock = iRetVal = INVALID_SOCKET;
			m_iTransportError = WSAGetLastError();
		}

	} else {
		// the gethostbyname failed
		m_Sock = iRetVal = INVALID_SOCKET;
		m_iTransportError = WSAGetLastError();
	}

	if (pszHost != NULL)
	{
		delete [] pszHost;
	}

	return iRetVal == ERROR_SUCCESS;
}

BOOL CHTTPTransport::InitTransport()
{
	WSADATA wsaData;
	WSAStartup(  MAKEWORD( 2, 2 ), &wsaData );
	return TRUE;
}
