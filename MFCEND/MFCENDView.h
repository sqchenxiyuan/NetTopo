
// MFCENDView.h : CMFCENDView 类的接口
//

#pragma once


class CMFCENDView : public CView
{
protected: // 仅从序列化创建
	CMFCENDView();
	DECLARE_DYNCREATE(CMFCENDView)

// 特性
public:
	CMFCENDDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCENDView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // MFCENDView.cpp 中的调试版本
inline CMFCENDDoc* CMFCENDView::GetDocument() const
   { return reinterpret_cast<CMFCENDDoc*>(m_pDocument); }
#endif

