#pragma once
#include "DrawObj.h"
class CNetElement
{
public:
	CNetElement(float cx,float cy,CString imgpath, CString type, CString title = _T(""),float w=40,float h=30);
	virtual ~CNetElement();

	bool m_selected = false;
	int m_id = -1;
	float m_centerx;
	float m_centery;
	float m_imgw=40;
	float m_imgh=30;
	CString m_imgpath;
	CString m_type;
	CString m_title = _T("");
	vector<CNetElement*> m_linklist;

	void Draw(CPoint startPoint, float w, float h, CDC* pDC);
};

