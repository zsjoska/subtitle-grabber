#pragma once
#include "httpcontent.h"
#include <vector>

class CHTTPResponse :
	public CHTTPContent
{
public:
	CHTTPResponse(void);
	virtual ~CHTTPResponse(void);

	void BeginConstruct();
	void AddBuffer(LPCSTR pBuffer, int nSize);
	int EndConstructHeader(BOOL bTransportFinish);
	void EndConstructBody(BOOL bTransportFinish);


	BOOL CanPersist();

private:
	void ParseAndFillHeaders();
	std::vector<CHAR> m_readBuffer;

	CString m_strHTTPVer;
	UINT m_nHTTPStatus;
	CString m_strServerMessage;

};
