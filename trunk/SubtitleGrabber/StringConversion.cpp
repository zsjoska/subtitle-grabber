#include "StdAfx.h"

CStringConversion::CStringConversion(void)
{
}

CStringConversion::~CStringConversion(void)
{
}

LPCSTR ConvertFromWide(UINT nCodePage, LPCWSTR strText, int & nCount)
{
	int bufferCount = 0;
	bufferCount = WideCharToMultiByte(nCodePage, 0, strText, -1, NULL, bufferCount, NULL, NULL);
	if( bufferCount != 0 )
	{
		LPSTR pszBytes = new CHAR[bufferCount];
		if(WideCharToMultiByte(nCodePage, 0, strText, -1, pszBytes, bufferCount, NULL, NULL) && bufferCount != 0)
		{
			nCount = bufferCount;
			return pszBytes;
		}
		delete [] pszBytes;
	}
	nCount = 0;
	return NULL;
}

CString ConvertToCString(UINT nCodePage, LPCSTR strText, int nCount)
{
	CString strRetVal = _T("--- Conversion Error ---");
	int bufferCount = 0;
	bufferCount = MultiByteToWideChar(nCodePage, 0, strText, nCount, NULL, bufferCount);
	if( bufferCount != 0 )
	{
		LPWSTR pszBytes = new WCHAR[bufferCount];
		if(MultiByteToWideChar(nCodePage, 0, strText, nCount, pszBytes, bufferCount))
		{
			strRetVal = pszBytes;
		}
		delete [] pszBytes;
	}
	return strRetVal;
}

CString GetStringError(HRESULT hr) 
{ 
	LPTSTR lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL );

	CString strRet = lpMsgBuf;

	LocalFree(lpMsgBuf);

	return strRet;
}
