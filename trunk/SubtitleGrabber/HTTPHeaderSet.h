#pragma once

class CHTTPHeaderSet
{
public:
	CHTTPHeaderSet(void);
	// CHTTPHeaderSet(CHTTPHeaderSet & obj);
	~CHTTPHeaderSet(void);

	BOOL			ImportFromString(CString strHeaders);
	CString			GetHeaderString();

	inline CString	GetHeaderField(CString str){ CString strVal; m_headerMap.Lookup(str.MakeLower(), strVal); return strVal;}

	inline void		SetHeaderString(CString name, CString value){ m_headerMap[name.MakeLower()]=value.MakeLower(); }

private:
	CMapStringToString m_headerMap;


};
