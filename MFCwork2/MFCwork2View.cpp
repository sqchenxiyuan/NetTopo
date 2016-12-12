
// MFCwork2View.cpp : CMFCwork2View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCwork2.h"
#endif

#include "MFCwork2Doc.h"
#include "MFCwork2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCwork2View

IMPLEMENT_DYNCREATE(CMFCwork2View, CFormView)

BEGIN_MESSAGE_MAP(CMFCwork2View, CFormView)
//	ON_WM_PAINT()
//	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCwork2View::OnAddEquipment)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &CMFCwork2View::OnNMDblclkTree1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCwork2View::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCwork2View::OnBnClickedButton3)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMFCwork2View::OnTvnSelchangedTree1)
END_MESSAGE_MAP()

// CMFCwork2View 构造/析构

CMFCwork2View::CMFCwork2View()
	: CFormView(CMFCwork2View::IDD)
{
	// TODO:  在此处添加构造代码
	vector<CNetElement*> nodes;
	CNetElement* e1 = new CNetElement(0.1, 0.5, _T("res/cloud.png"),_T("网络设备"), _T("因特网"));
	CNetElement* e2 = new CNetElement(0.5, 0.5, _T("res/Router.png"), _T("网络设备"), _T("无线路由"));
	CNetElement* e3 = new CNetElement(0.5, 0.1, _T("res/computer.png"), _T("网络设备"), _T("192.168.0.100"));
	CNetElement* e4 = new CNetElement(0.7, 0.5, _T("res/mobile_phone.png"), _T("网络设备"));
	CNetElement* e5 = new CNetElement(0.6, 0.7, _T("res/computer.png"), _T("网络设备"), _T("192.168.0.200"));
	CNetElement* e6 = new CNetElement(0.8, 0.8, _T("res/computer.png"), _T("家用设备"));
	CNetElement* e7 = new CNetElement(0.2, 0.75, _T("res/mobile_phone.png"), _T("家用设备"));
	vector<CNetLine*> links;
	links.push_back(new CNetLine(e2, e1));
	links.push_back(new CNetLine(e2, e3));
	links.push_back(new CNetLine(e2, e4));
	links.push_back(new CNetLine(e2, e5));
	links.push_back(new CNetLine(e2, e7));
	links.push_back(new CNetLine(e5, e6));
	nodes.push_back(e1);
	nodes.push_back(e2);
	nodes.push_back(e3);
	nodes.push_back(e4);
	nodes.push_back(e5);
	nodes.push_back(e6);
	nodes.push_back(e7);
	m_NetTopo=new CNetTopo(CPoint(5, 5), CPoint(425, 325));
	//CNetTopo* topo = new CNetTopo(CPoint(0, 0), CPoint(400, 300));
	m_NetTopo->setData(nodes, links);
}

CMFCwork2View::~CMFCwork2View()
{
}

void CMFCwork2View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}

BOOL CMFCwork2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CMFCwork2View::OnInitialUpdate()
{
	
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CMFCwork2View 诊断

#ifdef _DEBUG
void CMFCwork2View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCwork2View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCwork2Doc* CMFCwork2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCwork2Doc)));
	return (CMFCwork2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCwork2View 消息处理程序



void CMFCwork2View::OnDraw(CDC* /*pDC*/)
{
	// TODO:  在此添加专用代码和/或调用基类
	CDC* pDC = GetDC();
	CMFCwork2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	

	////双缓冲
	//CRect rect;
	//GetClientRect(&rect);
	//CDC MemDC;
	//MemDC.CreateCompatibleDC(pDC);
	//CBitmap MemBitmap;
	//MemBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	////按原来背景填充客户区，不然会是黑色
	//MemDC.SelectObject(&MemBitmap);
	//MemDC.FillSolidRect(rect, pDC->GetBkColor());

	/////

	//m_NetTopo->Draw(&MemDC);


	/////
	//pDC->SetBkMode(false);//透明
	////pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
	//pDC->BitBlt(20, 20, 430, 330, &MemDC, 0, 0, SRCCOPY);

	//MemDC.DeleteDC();     //删除DC
	//MemBitmap.DeleteObject(); //删除位图
	drawNet();
	if (!m_init){
		m_init = true;
		setTree();
	}
	
}

void CMFCwork2View::drawNet() {

	CDC* pDC = GetDC();

	//双缓冲
	CRect rect;
	GetClientRect(&rect);
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap MemBitmap;
	MemBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	//按原来背景填充客户区，不然会是黑色
	MemDC.SelectObject(&MemBitmap);
	MemDC.FillSolidRect(rect, pDC->GetBkColor());

	///

	m_NetTopo->Draw(&MemDC);


	///
	pDC->SetBkMode(false);//透明
						  //pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
	pDC->BitBlt(20, 20, 430, 330, &MemDC, 0, 0, SRCCOPY);

	MemDC.DeleteDC();     //删除DC
	MemBitmap.DeleteObject(); //删除位图

}


void CMFCwork2View::OnAddEquipment()
{
	// TODO:  在此添加控件通知处理程序代码
	CDAddEquipment dadd(m_NetTopo->getTypes());
	if (IDOK == dadd.DoModal())
	{
		int id=m_NetTopo->addEquipment(dadd.m_type,dadd.m_title, dadd.m_path, dadd.m_px, dadd.m_py, dadd.m_imgw, dadd.m_imgh);
		setTree();
		drawNet();
	}
}

void CMFCwork2View::OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hCurTree = m_tree.GetSelectedItem();
	int id = m_tree.GetItemData(hCurTree);
	if (id == -1)return;

	CDAddEquipment d(m_NetTopo->getTypes());
	CNetElement* element = m_NetTopo->getElemnetById(id);
	d.m_type = element->m_type;
	d.m_title = element->m_title;
	d.m_path = element->m_imgpath;
	d.m_px = element->m_centerx;
	d.m_py = element->m_centery;
	d.m_imgw = element->m_imgw;
	d.m_imgh = element->m_imgh;

	if (IDOK == d.DoModal())
	{
		element->m_title = d.m_title;
		element->m_type = d.m_type;
		element->m_imgpath = d.m_path;
		element->m_centerx = d.m_px;
		element->m_centery = d.m_py;
		element->m_imgw = element->m_imgw;
		element->m_imgh = d.m_imgw;
		m_NetTopo->checkNewType(d.m_type);
		setTree();
		drawNet();
	}

	*pResult = 0;
}


void CMFCwork2View::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	HTREEITEM hCurTree = m_tree.GetSelectedItem();
	int id = m_tree.GetItemData(hCurTree);
	if (m_NetTopo->delElemnetById(id)){
		setTree();
	}
}

void CMFCwork2View::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	CDAddLine dadd;

	if (IDOK == dadd.DoModal())
	{
		int id = m_NetTopo->addLineById(dadd.m_node1, dadd.m_node2);
		setTree();
		Invalidate();
	}
}

void CMFCwork2View::setTree(){
	m_tree.DeleteAllItems();

	vector<CString> types = m_NetTopo->getTypes();
	map<CString, HTREEITEM> hash_type;
	for (int i = 0; i < types.size(); i++) {
		HTREEITEM typenode = m_tree.InsertItem(types.at(i), 0, 0);
		m_tree.SetItemData(typenode, -1);
		hash_type[types.at(i)] = typenode;
	}

	
	map<int, HTREEITEM> hash_node;
	vector<CNetElement*> nodes=m_NetTopo->getNodes();
	for (int i = 0; i < nodes.size(); i++){
		HTREEITEM newelement;
		CString a;
		a.Format(_T("%d"), nodes.at(i)->m_id);
		HTREEITEM zzz = hash_type.find(nodes.at(i)->m_type)->second;

		newelement = m_tree.InsertItem(a + _T(" ") + nodes.at(i)->m_title, 0, 0, zzz);
		m_tree.SetItemData(newelement, nodes.at(i)->m_id);
		
		hash_node[nodes.at(i)->m_id] = newelement;
	}

	vector<CNetLine*> links = m_NetTopo->getLinks();
	for (int i = 0; i < links.size(); i++) {
		int ida = links.at(i)->m_a->m_id;
		int idb = links.at(i)->m_b->m_id;

		CString a;
		a.Format(_T("%d"), ida);
		CString b;
		b.Format(_T("%d"), idb);

		HTREEITEM newa = m_tree.InsertItem(b, 0, 0, hash_node.find(ida)->second);
		m_tree.SetItemData(newa, idb);
		HTREEITEM newb = m_tree.InsertItem(a, 0, 0, hash_node.find(idb)->second);
		m_tree.SetItemData(newb, ida);
	}

}




void CMFCwork2View::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hCurTree = m_tree.GetSelectedItem();
	m_NetTopo->selcNodeById(m_tree.GetItemData(hCurTree));
	drawNet();
	*pResult = 0;
}


