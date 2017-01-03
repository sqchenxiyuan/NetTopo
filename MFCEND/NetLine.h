#pragma once
#include "Base.h"
#include "NetElement.h"
class CNetLine :
	public CBase
{
public:
	int m_e1;
	int m_e2;
	int m_type;

	CNetElement* e1=NULL;
	CNetElement* e2=NULL;

	CNetLine();
	CNetLine(int a,int b,int type=0);
	virtual ~CNetLine();

	virtual void Draw(CDC * pDC, CRect * rect);
	DECLARE_SERIAL(CNetLine)
	virtual void Serialize(CArchive& ar);

	bool m_select = false;
	bool down(CPoint point, CRect rect);
	void reset_select();
	
};

