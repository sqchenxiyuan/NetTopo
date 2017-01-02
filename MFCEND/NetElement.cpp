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

		CRect imgrect1(CPoint(sx-3, sy-3), CPoint(sx + 3, sy + 3));
		pDC->Rectangle(imgrect1);

		CRect imgrect2(CPoint(sx - 3, ey - 3), CPoint(sx + 3, ey + 3));
		pDC->Rectangle(imgrect2);

		CRect imgrect3(CPoint(ex - 3, sy - 3), CPoint(ex + 3, sy + 3));
		pDC->Rectangle(imgrect3);

		CRect imgrect4(CPoint(ex - 3, ey - 3), CPoint(ex + 3, ey + 3));
		pDC->Rectangle(imgrect4);
	}
	//drawPNG(m_imgpath, pDC, cx, cy, m_imgw, m_imgh);
	drawPNG(m_imgpath, pDC, imgrect);

	if (m_title != CString(_T(""))) {
		pDC->SetTextAlign(TA_CENTER| TA_BASELINE);//设置文本对齐方式 
		pDC->TextOut(cx, ey+15, m_title);
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


	m_resize = 0;
	if (m_selected) {
		m_oldimgw=m_imgw;
		m_oldimgh=m_imgh;
		if (abs(point.x - sx) < 4 && abs(point.y - sy) < 4) {
			m_resize = 1;
		}
		if (abs(point.x - ex) < 4 && abs(point.y - sy) < 4) {
			m_resize = 2;
		}
		if (abs(point.x - ex) < 4 && abs(point.y - ey) < 4) {
			m_resize = 3;
		}
		if (abs(point.x - sx) < 4 && abs(point.y - ey) < 4) {
			m_resize = 4;
		}
	}

	if (point.x >= imgrect.left&&
		point.x <= imgrect.right&&
		point.y >= imgrect.top&&
		point.y <= imgrect.bottom||
		m_resize != 0
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

		if (m_resize == 0) {
			cx = cx + movex;
			cy = cy + movey;
			m_centerx = cx / w;
			m_centery = cy / h;

			if (m_centerx < 0)m_centerx = 0;
			if (m_centery < 0)m_centery = 0;
			if (m_centerx > 1)m_centerx = 1;
			if (m_centery > 1)m_centery = 1;
		}
		else {
			switch (m_resize)
			{
			case 1:	m_imgw = m_oldimgw - movex;
					m_imgh = m_oldimgh - movey;
					break;
			case 2:	m_imgw = m_oldimgw + movex;
					m_imgh = m_oldimgh - movey;
					break;
			case 3:	m_imgw = m_oldimgw + movex;
					m_imgh = m_oldimgh + movey;
					break;
			case 4:	m_imgw = m_oldimgw - movex;
					m_imgh = m_oldimgh + movey;
					break;
			}
			if (m_imgw < 10)m_imgw = 10;
			if (m_imgh < 10)m_imgh = 10;
		}

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

void CNetElement::out()
{
	m_olddownpoint = CPoint(-1, -1);
}
