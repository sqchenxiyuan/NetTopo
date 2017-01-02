#include "stdafx.h"
#include "TopoNet.h"

IMPLEMENT_SERIAL(CTopoNet, CObject, 0)
CTopoNet::CTopoNet()
{
}


CTopoNet::~CTopoNet()
{
	
	CBase* element;
	POSITION pos = m_elementList.GetHeadPosition();
	while (pos)
	{
		element = (CNetElement *)m_elementList.GetNext(pos);//获得m_SpiritList中的对象
		delete element;
	}

	KillTimer(m_pView->m_hWnd, 1);
}

void CTopoNet::buildnewnet()
{
	CNetType* t1 = new CNetType(_T("网络设备"));
	CNetType* t2 = new CNetType(_T("家用设备"));
	t1->m_id = 0;
	t2->m_id = 1;

	this->AddType(t1);
	this->AddType(t2);

	CNetElement* e1 = new CNetElement(0.1, 0.5,0, _T("src/cloud.png"), _T("因特网"));
	CNetElement* e2 = new CNetElement(0.5, 0.5,0, _T("src/Router.png"), _T("无线路由"));
	CNetElement* e3 = new CNetElement(0.5, 0.1,0, _T("src/computer.png"), _T("192.168.0.100"));
	CNetElement* e4 = new CNetElement(0.7, 0.5,0, _T("src/mobile_phone.png"));
	CNetElement* e5 = new CNetElement(0.6, 0.7,0, _T("src/computer.png"), _T("192.168.0.200"));
	CNetElement* e6 = new CNetElement(0.8, 0.8,1, _T("src/computer.png"));
	CNetElement* e7 = new CNetElement(0.2, 0.75,1, _T("src/mobile_phone.png"));
	this->AddElement(e1);
	this->AddElement(e2);
	this->AddElement(e3);
	this->AddElement(e4);
	this->AddElement(e5);
	this->AddElement(e6);
	this->AddElement(e7);
	e1->setId(1);
	e2->setId(2);
	e3->setId(3);
	e4->setId(4);
	e5->setId(5);
	e6->setId(6);
	e7->setId(7);
	CNetLine *line;
	line = new CNetLine(e2->m_id, e1->m_id);
	line->setId(8);
	this->AddLine(line);
	line = new CNetLine(e2->m_id, e3->m_id);
	line->setId(9);
	this->AddLine(line);
	line = new CNetLine(e2->m_id, e4->m_id);
	line->setId(10);
	this->AddLine(line);
	line = new CNetLine(e2->m_id, e5->m_id);
	line->setId(11);
	this->AddLine(line);
	line = new CNetLine(e2->m_id, e7->m_id);
	line->setId(12);
	this->AddLine(line);
	line = new CNetLine(e5->m_id, e6->m_id);
	line->setId(13);
	this->AddLine(line);
}

void CTopoNet::loadnet()
{

	CNetLine * line;
	POSITION pos = m_lineList.GetHeadPosition();
	while (pos)
	{
		line = (CNetLine *)m_lineList.GetNext(pos);//获得m_SpiritList中的对象
		CNetElement* element;
		POSITION pos2 = m_elementList.GetHeadPosition();
		while (pos2)
		{
			element = (CNetElement *)m_elementList.GetNext(pos2);//获得m_SpiritList中的对象
			if (element->m_id == line->m_e1) {
				line->e1 = element;
			}
			if (element->m_id == line->m_e2) {
				line->e2 = element;
			}
		}
	}

}

void CTopoNet::Draw()
{
	CDC * pDC = m_pView->GetDC();//获得视图类的CDC
	CRect rect;
	m_pView->GetWindowRect(&rect);

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap MemBitmap;
	MemBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	//按原来背景填充客户区，不然会是黑色
	MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(0,0,rect.Width(),rect.Height(), pDC->GetBkColor());
	//////////////////////////////////////////////////////

	CNetLine * line;
	POSITION pos = m_lineList.GetHeadPosition();
	while (pos)
	{
		line = (CNetLine *)m_lineList.GetNext(pos);//获得m_SpiritList中的对象
		line->Draw(&MemDC, &rect);//将兼容DC传给对象，是对象的DC操作在兼容DC上进行，可以防止闪屏
	}

	CNetElement* element;
	pos = m_elementList.GetHeadPosition();
	while (pos)
	{
		element = (CNetElement *)m_elementList.GetNext(pos);//获得m_SpiritList中的对象
		element->Draw(&MemDC,&rect);//将兼容DC传给对象，是对象的DC操作在兼容DC上进行，可以防止闪屏
	}

	//////////////////////////////////////////////////////
	pDC->SetBkMode(false);//透明
						  //pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);

	MemDC.DeleteDC();     //删除DC
	MemBitmap.DeleteObject(); //删除位图

}

void CTopoNet::AddElement(CBase * Sp)
{
	if (Sp->m_id>m_maxelementid) {
		m_maxelementid = Sp->m_id;
	}
	else if (Sp->m_id == -1) {
		Sp->m_id = ++m_maxelementid;
	}
	m_elementList.AddHead(Sp);
}

void CTopoNet::AddLine(CBase * Sp)
{
	CNetElement* element;
	POSITION pos = m_elementList.GetHeadPosition();
	while (pos)
	{
		element = (CNetElement *)m_elementList.GetNext(pos);//获得m_SpiritList中的对象
		if (element->m_id == ((CNetLine*)Sp)->m_e1) {
			((CNetLine*)Sp)->e1 = element;
		}
		if (element->m_id == ((CNetLine*)Sp)->m_e2) {
			((CNetLine*)Sp)->e2 = element;
		}
	}

	if (Sp->m_id>m_maxlineid) {
		m_maxlineid = Sp->m_id;
	}
	else if (Sp->m_id == -1) {
		Sp->m_id = ++m_maxlineid;
	}

	m_lineList.AddHead(Sp);
}

void CTopoNet::AddType(CNetType * Sp)
{
	if (Sp->m_id>m_maxtypeid) {
		m_maxtypeid= Sp->m_id;
	}
	else if(Sp->m_id==-1){
		Sp->m_id = ++m_maxtypeid;
	}

	m_typeList.AddHead(Sp);
}

void CTopoNet::InitTopoNet(CView * pview, CDC * pDc)
{
	m_pView = pview;

	SetTimer(m_pView->m_hWnd, 1, 30, NULL);
}


void CTopoNet::Serialize(CArchive& ar)
{
	m_typeList.Serialize(ar);
	m_elementList.Serialize(ar);
	m_lineList.Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar << m_maxtypeid;
		ar << m_maxelementid;
		ar << m_maxlineid;
	}
	else
	{	// loading code
		ar >> m_maxtypeid;
		ar >> m_maxelementid;
		ar >> m_maxlineid;
		loadnet();
	}
}
