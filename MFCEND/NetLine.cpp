#include "stdafx.h"
#include "NetLine.h"

IMPLEMENT_SERIAL(CNetLine, CBase, 0)

CNetLine::CNetLine()
{
}

CNetLine::CNetLine(int a, int b, int type)
{
	m_e1 = a;
	m_e2 = b;
	m_type = type;
}


CNetLine::~CNetLine()
{
}

void CNetLine::Draw(CDC * pDC, CRect * rect)
{
	float h = rect->Height();
	float w = rect->Width();

	float sx = e1->m_centerx*w;
	float sy = e1->m_centery*h;

	float ex = e2->m_centerx*w;
	float ey = e2->m_centery*h;

	pDC->MoveTo(sx, sy);
	pDC->LineTo(ex, ey);
}

void CNetLine::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);
	CBase::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar << m_e1;
		ar << m_e2;
		ar << m_type;
	}
	else
	{	// loading code
		ar >> m_e1;
		ar >> m_e2;
		ar >> m_type;
	}
}
