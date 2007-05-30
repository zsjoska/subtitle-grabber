#include "StdAfx.h"
#include "HTTPHeaderSet.h"
#include "HTTP.h"

CHTTPHeaderSet::CHTTPHeaderSet(void)
{
}

/**
CHTTPHeaderSet::CHTTPHeaderSet(CHTTPHeaderSet & obj)
{
	// m_headerMap = obj.m_headerMap.
}
/**/

CHTTPHeaderSet::~CHTTPHeaderSet(void)
{
	m_headerMap.RemoveAll();
}

CString	CHTTPHeaderSet::GetHeaderString()
{
	CString strHeaders;

	if (m_headerMap.GetSize() == 0)
	{
		return strHeaders;
	}
	
	CMapStringToString::CPair* pCurVal;
	pCurVal= m_headerMap.PGetFirstAssoc( );
	while (pCurVal != NULL)
	{

		strHeaders += pCurVal->key;
		strHeaders += _T(": ");
		strHeaders += pCurVal->value;
		strHeaders += CHTTP::CRLF;

		pCurVal= m_headerMap.PGetNextAssoc(pCurVal);
	}
	
	return strHeaders;
}
