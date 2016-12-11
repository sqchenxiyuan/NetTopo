#pragma once
#include "afx.h"

class CDrawObj :
	public CObject
{
public:
	CDrawObj();
	virtual ~CDrawObj();
	CPoint m_Point;
	CPen   m_SelectedPen;
	CBrush m_SelectedBrush;
	CPen   m_Pen;
	CBrush m_Brush;
	bool   m_IsSelected;
	virtual void Dbclick();
	virtual void Draw(CDC * pDC) = 0;
};

