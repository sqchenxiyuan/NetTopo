#include "stdafx.h"
#include "NetElement.h"

IMPLEMENT_SERIAL(CNetElement,CBase, 0)



CNetElement::CNetElement()
{
}

CNetElement::CNetElement(float cx, float cy) {
	m_centerx = cx;
	m_centery = cy;
}

CNetElement::CNetElement(int type, CString imgpath, CString title, float cx, float cy, float w, float h)
{
	m_type = type;
	m_centerx = cx;
	m_centery = cy;
	if (w>0)m_imgw = w;
	if (h>0)m_imgh = h;
	m_imgpath = imgpath;
	m_title = title;
}

CNetElement::CNetElement(float cx, float cy, int type, CString imgpath, CString title, float w, float h)
{
	m_type = type;
	m_centerx = cx;
	m_centery = cy;
	if (w>0)m_imgw = w;
	if (h>0)m_imgh = h;
	m_imgpath = imgpath;
	m_title = title;
}


CNetElement::~CNetElement()
{
}

void CNetElement::Draw(CDC * pDC, CRect * rect)
{
	float h = rect->Height();
	float w = rect->Width();

	float cx = m_centerx*w;
	float cy = m_centery*h;

	float sx = cx - m_imgw / 2;
	float sy = cy - m_imgh / 2;

	float ex = cx + m_imgw / 2;
	float ey = cy + m_imgh / 2;
	

	CRect imgrect(CPoint(sx, sy), CPoint(ex,ey));
	if (m_selected) {
		CBrush newb(RGB(255, 0, 0));
		CBrush* oldb= pDC->SelectObject(&newb);
		pDC->FillRect(imgrect,&newb);
		pDC->SelectObject(&oldb);
	}
	//drawPNG(m_imgpath, pDC, cx, cy, m_imgw, m_imgh);
	drawPNG(m_imgpath, pDC, imgrect);

	if (m_title != CString(_T(""))) {
		pDC->DrawText(m_title, CRect(cx - 500, cy + m_imgh / 2, cx + 500, cy + m_imgh / 2 + 20), DT_BOTTOM | DT_CENTER | DT_TOP);
	}


}



void CNetElement::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	CBase::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar << m_type;
		ar << m_centerx;
		ar << m_centery;
		ar << m_imgw;
		ar << m_imgh;
		ar << m_imgpath;
		ar << m_title;
	}
	else
	{	// loading code
		ar >> m_type;
		ar >> m_centerx;
		ar >> m_centery;
		ar >> m_imgw;
		ar >> m_imgh;
		ar >> m_imgpath;
		ar >> m_title;
	}
}

bool CNetElement::down(CPoint point,CRect rect)
{
	float h = rect.Height();
	float w = rect.Width();

	float cx = m_centerx*w;
	float cy = m_centery*h;

	float sx = cx - m_imgw / 2;
	float sy = cy - m_imgh / 2;

	float ex = cx + m_imgw / 2;
	float ey = cy + m_imgh / 2;


	CRect imgrect(CPoint(sx, sy), CPoint(ex, ey));

	if (point.x >= imgrect.left&&
		point.x <= imgrect.right&&
		point.y >= imgrect.top&&
		point.y <= imgrect.bottom
		) {
		m_selected = true;
		m_olddownpoint = point;
		m_oldcenterx = m_centerx;
		m_oldcentery = m_centery;
		return true;
	}
	else {
		m_selected = false;
		return false;
	}
}

bool CNetElement::move(CPoint point, CRect rect)
{
	if (m_olddownpoint!=CPoint(-1,-1)){

		float h = rect.Height();
		float w = rect.Width();

		float cx = m_oldcenterx*w;
		float cy = m_oldcentery*h;

		int movex = point.x - m_olddownpoint.x;
		int movey = point.y - m_olddownpoint.y;

		cx = cx + movex;
		cy = cy + movey;
		m_centerx = cx / w;
		m_centery = cy / h;

		return true;
	}
	else {

		return false;
	}
}

bool CNetElement::up(CPoint point, CRect rect)
{
	if (m_olddownpoint != CPoint(-1, -1)) {
		m_olddownpoint = CPoint(-1, -1);
		return true;
	}
	else {
		return false;
	}
}
