#pragma once
#include "afx.h"
class CBase :
	public CObject
{
public:
	int m_id=-1;

	void setId(int id);
	CBase();
	~CBase();
	virtual void Draw(CDC * pDC, CRect * rect);
	virtual void Serialize(CArchive& ar);
	DECLARE_SERIAL(CBase);
};

