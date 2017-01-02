#pragma once
#include "afx.h"
#include "Base.h"
#include "NetElement.h"
#include "NetLine.h"
#include "NetType.h"
#include <map>

class CTopoNet :
	public CObject
{
public:
	//存放列表
	int m_maxtypeid=0;
	int m_maxelementid=0;
	int m_maxlineid=0;
	CObList m_typeList;
	CObList m_elementList;
	CObList m_lineList;

	CView * m_pView;
	

	CTopoNet();
	virtual ~CTopoNet();

	void buildnewnet();
	void loadnet();

	void Draw();
	void AddElement(CBase * Sp);
	void AddLine(CBase * Sp);
	void AddType(CNetType * Sp);

	void down(CPoint point);
	void move(CPoint point);
	void up(CPoint point);
	void out();


	void InitTopoNet(CView * pview, CDC *pDc);
	DECLARE_SERIAL(CTopoNet) //宏声明，为了串行化对象，便于存储
	virtual void Serialize(CArchive& ar);
};

