
// MFCENDView.cpp : CMFCENDView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CMFCENDView ����/����

CMFCENDView::CMFCENDView()
{
	// TODO: �ڴ˴���ӹ������

}

CMFCENDView::~CMFCENDView()
{
}

BOOL CMFCENDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCENDView ����

void CMFCENDView::OnDraw(CDC* /*pDC*/)
{
	CMFCENDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMFCENDView ��ӡ


void CMFCENDView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCENDView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCENDView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCENDView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CMFCENDView ���

#ifdef _DEBUG
void CMFCENDView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCENDView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCENDDoc* CMFCENDView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCENDDoc)));
	return (CMFCENDDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCENDView ��Ϣ�������


void CMFCENDView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMainFrame * pf = (CMainFrame*)AfxGetMainWnd();
	POSITION pos;
	switch (nIDEvent)//nIDEvent�ǵ�ǰtimer����˭����
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
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	GetDocument()->mouseDown(point);
	CView::OnLButtonDown(nFlags, point);
}

void CMFCENDView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	GetDocument()->mouseMove(point);
	CView::OnMouseMove(nFlags, point);
}


void CMFCENDView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	GetDocument()->mouseUp(point);
	CView::OnLButtonUp(nFlags, point);
}