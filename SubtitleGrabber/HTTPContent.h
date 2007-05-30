#pragma once

#include "HTTPHeaderSet.h"

class CHTTPContent
{
public:
	CHTTPContent(void);
	virtual ~CHTTPContent(void);

	inline CString	GetTitle(){ return m_strTitle; }
	inline CString	GetContent(){ return m_strContent; }
	inline void 	SetContent(CString str){m_strContent = str;}
	inline CString	GetHeaderField(CString str){ return m_HeaderSet.GetHeaderField(str);}
	inline CString	GetHeaderString(){ return m_HeaderSet.GetHeaderString();}
	inline void		SetHeaderString(CString name, CString value){ m_HeaderSet.SetHeaderString(name, value); }

protected:
	inline void		SetTitle(CString strTitle){ m_strTitle = strTitle;}

	int GetNumericHeaderField(CString str);
private:
	CString			m_strTitle;
	CHTTPHeaderSet  m_HeaderSet;
	CString			m_strContent;
};
