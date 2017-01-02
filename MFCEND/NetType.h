#pragma once
#include "afx.h"
class CNetType :
	public CObject
{
public:
	int m_id=-1;
	CString m_name;

	CNetType();
	CNetType(CString name);
	~CNetType();
	DECLARE_SERIAL(CNetType) //宏声明，为了串行化对象，便于存储
	virtual void Serialize(CArchive& ar);
};

