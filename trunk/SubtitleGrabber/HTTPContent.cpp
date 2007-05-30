#include "StdAfx.h"
#include "HTTPContent.h"
#include "HTTPHeaderSet.h"

CHTTPContent::CHTTPContent(void)
{
}

CHTTPContent::~CHTTPContent(void)
{
}

int CHTTPContent::GetNumericHeaderField(CString str)
{
	CString strVal = m_HeaderSet.GetHeaderField(str);
	int iRetVal = -1;
	if (strVal != _T(""))
	{
		 iRetVal = _ttoi(strVal);
		 if (errno == ERANGE)
		 {
			 iRetVal = 0;
		 }
	}
	return iRetVal;
}
