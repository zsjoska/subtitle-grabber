#pragma once

LPCSTR ConvertFromWide(UINT nCodePage, LPCWSTR strText, int & nCount);
CString ConvertToCString(UINT nCodePage, LPCSTR strText, int nCount);
CString GetStringError(HRESULT hr);


class CStringConversion
{
public:
	CStringConversion(void);
public:
	~CStringConversion(void);
};
