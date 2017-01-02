#pragma once
#include "Base.h"
class CNetElement :
	public CBase
{
public:
	int m_type = -1;
	float m_centerx;
	float m_centery;
	float m_imgw=40;
	float m_imgh=30;
	CString m_imgpath = _T("");
	CString m_title = _T("");

	bool m_selected = false;
	bool down(CPoint point, CRect rect);
	bool move(CPoint point, CRect rect);
	bool up(CPoint point, CRect rect);

	CNetElement();
	CNetElement(float cx,float cy);
	CNetElement(int type, CString imgpath=_T(""), CString title = _T(""), float cx=0.5, float cy=0.5 , float w = 40, float h = 30);
	CNetElement(float cx, float cy, int type, CString imgpath, CString title = _T(""), float w = 40, float h = 30);
	virtual ~CNetElement();
	virtual void Draw(CDC * pDC, CRect * rect);
	DECLARE_SERIAL(CNetElement)
	virtual void Serialize(CArchive& ar);
private:
	CPoint m_olddownpoint = CPoint(-1, -1);
	float m_oldcenterx;
	float m_oldcentery;
};

