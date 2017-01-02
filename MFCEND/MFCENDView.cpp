
// MFCENDView.cpp : CMFCENDView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCEND.h"
#endif

#include "MFCENDDoc.h"
#include "MFCENDView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCENDView

IMPLEMENT_DYNCREATE(CMFCENDView, CView)

BEGIN_MESSAGE_MAP(CMFCENDView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCENDView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_MESSAGE(MSG_RESET_DATA, &CMFCENDView::resetTreeData)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMFCENDView 构造/析构

CMFCENDView::CMFCENDView()
{
	// TODO: 在此处添加构造代码

}

CMFCENDView::~CMFCENDView()
{
}

BOOL CMFCENDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCENDView 绘制

void CMFCENDView::OnDraw(CDC* /*pDC*/)
{
	CMFCENDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCENDView 打印


void CMFCENDView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCENDView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCENDView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCENDView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMFCENDView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCENDView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCENDView 诊断

#ifdef _DEBUG
void CMFCENDView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCENDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCENDDoc* CMFCENDView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCENDDoc)));
	return (CMFCENDDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCENDView 消息处理程序


void CMFCENDView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMainFrame * pf = (CMainFrame*)AfxGetMainWnd();
	POSITION pos;
	switch (nIDEvent)//nIDEvent是当前timer是由谁发出
	{
	case 1:
		this->GetDocument()->m_toponet.Draw();

		break;
	}

	CView::OnTimer(nIDEvent);
}


void CMFCENDView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	GetDocument()->m_toponet.InitTopoNet(this, this->GetDC());
	// TODO: 在此添加专用代码和/或调用基类
}


//afx_msg LRESULT CMFCENDView::resetTree(WPARAM wParam, LPARAM lParam)
//{
//
//	return 0;
//}


afx_msg LRESULT CMFCENDView::resetTreeData(WPARAM wParam, LPARAM lParam)
{
	GetDocument()->InitTreeData();
	return 0;
}


void CMFCENDView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GetDocument()->mouseDown(point);
	CView::OnLButtonDown(nFlags, point);
}

void CMFCENDView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GetDocument()->mouseMove(point);
	CView::OnMouseMove(nFlags, point);
}


void CMFCENDView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GetDocument()->mouseUp(point);
	CView::OnLButtonUp(nFlags, point);
}