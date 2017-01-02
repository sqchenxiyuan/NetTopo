
// MFCENDView.h : CMFCENDView ��Ľӿ�
//

#pragma once


class CMFCENDView : public CView
{
protected: // �������л�����
	CMFCENDView();
	DECLARE_DYNCREATE(CMFCENDView)

// ����
public:
	CMFCENDDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMFCENDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
protected:
//	afx_msg LRESULT resetTree(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT resetTreeData(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnNcMouseLeave();
};

#ifndef _DEBUG  // MFCENDView.cpp �еĵ��԰汾
inline CMFCENDDoc* CMFCENDView::GetDocument() const
   { return reinterpret_cast<CMFCENDDoc*>(m_pDocument); }
#endif

