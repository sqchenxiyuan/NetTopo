#include "stdafx.h"
#include "Base.h"


void CBase::setId(int id)
{
	m_id = id;
}

CBase::CBase()
{
}


CBase::~CBase()
{
}

IMPLEMENT_SERIAL(CBase, CObject, 0)

void CBase::Draw(CDC * pDC,CRect * rect)
{
}


void CBase::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar << m_id;
	}
	else
	{	// loading code
		ar >> m_id;
	}
}
