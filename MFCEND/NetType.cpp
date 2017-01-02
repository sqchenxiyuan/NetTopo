#include "stdafx.h"
#include "NetType.h"

IMPLEMENT_SERIAL(CNetType, CObject, 0)
CNetType::CNetType()
{
}

CNetType::CNetType(CString name)
{
	m_name = name;
}


CNetType::~CNetType()
{
}


void CNetType::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_id;
		ar << m_name;
	}
	else
	{	// loading code
		ar >> m_id;
		ar >> m_name;
	}
}
