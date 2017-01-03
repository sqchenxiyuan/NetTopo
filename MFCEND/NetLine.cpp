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

	CPen * newpen;
	CPen * oldpen;
	if (m_select)
	{
		newpen = new CPen(PS_SOLID, 1, RGB(255, 0, 0));
	} else {
		newpen = new CPen(PS_SOLID, 1, RGB(0, 0, 0));
	}
	
	oldpen = pDC->SelectObject(newpen);

	pDC->MoveTo(sx, sy);
	pDC->LineTo(ex, ey);

	pDC->SelectObject(oldpen);
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

bool CNetLine::down(CPoint point, CRect rect)
{
	float h = rect.Height();
	float w = rect.Width();

	float sx = e1->m_centerx*w;
	float sy = e1->m_centery*h;

	float ex = e2->m_centerx*w;
	float ey = e2->m_centery*h;
	

	if (e1->m_centerx > e2->m_centerx) {
		float x;
		x = sx;
		sx = ex;
		ex = x;

		x = sy;
		sy = ey;
		ey = x;
	}
	
	float maxx = max(sx, ex);
	float minx = min(sx, ex);
	float maxy = max(sy, ey);
	float miny = min(sy, ey);


	m_select = false;
	if (minx-6<point.x&&point.x<maxx+6||
		miny - 6<point.y&&point.y<maxy + 6) {
		if (ex == sx) {
			if (abs(sx - point.x)<6) {
				m_select = true;
				return true;
			}
		}
		else {
			float a = (ey - sy) / (ex - sx);
			float px = (point.y - sy) / a + sx;
			float py = (point.x - sx)*a + sy;
			if (abs(py - point.y)<6&& minx - 6<point.x&&point.x<maxx + 6
				|| abs(px - point.x)<6&& miny - 6<point.y&&point.y<maxy + 6) {
				m_select = true;
				return true;
			}
		}
	}

	return false;
}
