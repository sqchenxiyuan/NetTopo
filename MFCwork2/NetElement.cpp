#include "stdafx.h"
#include "NetElement.h"

CNetElement::CNetElement(float cx, float cy, CString imgpath, CString type, CString title, float w, float h)
{
	m_centerx=cx;
	m_centery=cy;
	m_imgpath = imgpath;
	m_title = title;
	m_type = type;
	if(w>0)m_imgw = w;
	if(h>0)m_imgh = h;
}


CNetElement::~CNetElement()
{
}

void CNetElement::Draw(CPoint startPoint,float canw,float canh ,CDC* pDC){
	float cx = m_centerx*canw + startPoint.x;
	float cy = m_centery*canh + startPoint.y;

	CRect rect(CPoint(cx - m_imgw / 2, cy - m_imgh / 2), CPoint(cx + m_imgw / 2, cy + m_imgh / 2));
	if (m_selected) {
		pDC->FillSolidRect(rect, RGB(255, 0, 0));
	}
	//drawPNG(m_imgpath, pDC, cx, cy, m_imgw, m_imgh);
	drawPNG(m_imgpath, pDC, rect);

	if (m_title != CString(_T(""))) {
		pDC->DrawText(m_title, CRect(cx - 500, cy + m_imgh / 2, cx + 500, cy + m_imgh / 2 + 20), DT_BOTTOM | DT_CENTER | DT_TOP);
	}
}