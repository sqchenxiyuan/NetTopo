#pragma once
#include "DrawObj.h"
class CNetTopo :
	public CDrawObj
{
public:
	CNetTopo(CPoint startPoint, CPoint endPoint);
	virtual ~CNetTopo();

	virtual void Draw(CDC * pDC);
	virtual void Dbclick();

	void setData(vector<CNetElement*> nodes,vector<CNetLine*> links);
	vector<CNetElement*> getNodes();
	vector<CNetLine*> getLinks();
	vector<CString> getTypes();
	CNetElement* getElemnetById(int id);
	
	int addEquipment(CString, CString,CString, float, float, float,float);
	bool addLineById(int id1,int id2,int type=0);
	bool delElemnetById(int id);
	void selcNodeById(int id);
	void checkNewType(CString newtype);
private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	int id=0;
	float m_w;
	float m_h;

	vector<CNetElement*> m_linklist;
	vector<CNetLine*> m_links;
	vector<CString> m_types;
};