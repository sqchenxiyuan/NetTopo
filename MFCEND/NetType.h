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
	DECLARE_SERIAL(CNetType) //��������Ϊ�˴��л����󣬱��ڴ洢
	virtual void Serialize(CArchive& ar);
};

