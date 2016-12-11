#include "stdafx.h"
#include "NetTopo.h"

CNetTopo::CNetTopo(CPoint s, CPoint e)
{
	m_startPoint = CPoint(min(s.x,e.x),min(s.y,e.y));
	m_endPoint = CPoint(max(s.x, e.x), max(s.y, e.y));
	m_w = m_endPoint.x - m_startPoint.x;
	m_h = m_endPoint.y - m_startPoint.y;
}


CNetTopo::~CNetTopo()
{
}

void CNetTopo::Draw(CDC * pDC){
	int l = m_links.size();

	CPen* oldpen = pDC->SelectObject(new CPen(PS_DASH, 1, RGB(0, 0, 0)));
	for (int i = 0; i < l; i++) {
		CNetLine* line = m_links.at(i);
		pDC->MoveTo(line->m_a->m_centerx*m_w + m_startPoint.x, line->m_a->m_centery*m_h + m_startPoint.y);
		pDC->LineTo(line->m_b->m_centerx*m_w + m_startPoint.x, line->m_b->m_centery*m_h + m_startPoint.y);
	}
	pDC->SelectObject(oldpen);


	l = m_linklist.size();
	pDC->SetBkMode(false);//透明
	for (int i = 0; i < l; i++){
		m_linklist.at(i)->Draw(m_startPoint, m_w, m_h, pDC);
		/*float cx = nete->m_centerx*m_w + m_startPoint.x;
		float cy = nete->m_centery*m_h + m_startPoint.y;
		float w = nete->m_imgw;
		float h = nete->m_imgh;

		drawPNG(nete->m_imgpath, pDC, cx, cy, w,h);
		CString title = nete->m_title;
		if (title != CString(_T(""))){
			pDC->DrawText(nete->m_title, CRect(cx - 500, cy + h / 2, cx +500, cy + h / 2 + 20), DT_BOTTOM | DT_CENTER | DT_TOP);
		}*/
	}

	pDC->MoveTo(m_startPoint.x, m_startPoint.y);
	pDC->LineTo(m_startPoint.x, m_endPoint.y);
	pDC->LineTo(m_endPoint.x, m_endPoint.y);
	pDC->LineTo(m_endPoint.x, m_startPoint.y);
	pDC->LineTo(m_startPoint.x, m_startPoint.y);

}

void CNetTopo::Dbclick(){

}

void CNetTopo::setData(vector<CNetElement*> nodes, vector<CNetLine*> links){
	m_linklist = nodes;
	m_links = links;
	for (int i = 0; i < m_linklist.size(); i++){
		m_linklist.at(i)->m_id = ++id;
		checkNewType(m_linklist.at(i)->m_type);
	}
}

vector<CNetElement*> CNetTopo::getNodes(){
	return m_linklist;
}

vector<CNetLine*> CNetTopo::getLinks() {
	return m_links;
}

int CNetTopo::addEquipment(CString type,CString title, CString path, float px, float py, float w, float h){
	CNetElement* newElement = new CNetElement(px, py, path, type, title, w, h);
	checkNewType(type);
	m_linklist.push_back(newElement);
	newElement->m_id = ++id;
	return newElement->m_id;
}

CNetElement* CNetTopo::getElemnetById(int id){
	for (int i = 0; i < m_linklist.size(); i++){
		if (m_linklist.at(i)->m_id == id){
			CString x = m_linklist.at(i)->m_title;
			return m_linklist.at(i);
		}
	}
	return NULL;
}

bool CNetTopo::delElemnetById(int id){

	vector<CNetElement*>::iterator it;

	for (it = m_linklist.begin(); it != m_linklist.end();)
	{
		if ((*it)->m_id == id) {

			vector<CNetLine*>::iterator jt;
			for (jt = m_links.begin(); jt != m_links.end();)
			{
				if ((*jt)->m_a == (*it) || (*jt)->m_b == (*it)) {
					jt = m_links.erase(jt);
				}
				else {
					++jt;
				}
			}
			it = m_linklist.erase(it);    //删除元素，返回值指向已删除元素的下一个位置
			return true;
		}
		else {
			++it;    //指向下一个位置
		}
    }
	return false;
}

bool CNetTopo::addLineById(int id1, int id2,int type){
	CNetElement* a = NULL;
	CNetElement* b=NULL;
	for (int i = 0; i < m_links.size(); i++){
		if (m_links.at(i)->m_a->m_id == id1&&m_links.at(i)->m_b->m_id == id2 ||
			m_links.at(i)->m_a->m_id == id2&&m_links.at(i)->m_b->m_id == id1) {
			return false;
		}
	}
	for (int i = 0; i < m_linklist.size()&&!(a&&b); i++) {
		if (m_linklist.at(i)->m_id == id1) {
			a = m_linklist.at(i);
		}
		if(m_linklist.at(i)->m_id == id2) {
			b = m_linklist.at(i);
		}
	}
	if (a&&b) {
		m_links.push_back(new CNetLine(a, b));
		return true;
	}
	else {
		return false;
	}
}

void CNetTopo::selcNodeById(int id) {
	for (int i = 0; i < m_linklist.size(); i++) {
		if (m_linklist.at(i)->m_id == id) {
			m_linklist.at(i)->m_selected = true;
		}
		else {
			m_linklist.at(i)->m_selected = false;
		}
	}
}


void CNetTopo::checkNewType(CString newtype) {
	for (int i = 0; i < m_types.size(); i++) {
		if (m_types.at(i) == newtype)return;
	}
	m_types.push_back(newtype);
}

vector<CString> CNetTopo::getTypes() {
	return m_types;
}