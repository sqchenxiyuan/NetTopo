
// MFCwork2View.h : CMFCwork2View 类的接口
//

#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "DAddEquipment.h"
#include "DAddLine.h"


class CMFCwork2View : public CFormView
{
protected: // 仅从序列化创建
	CMFCwork2View();
	DECLARE_DYNCREATE(CMFCwork2View)

public:
	enum{ IDD = IDD_MFCWORK2_FORM };

// 特性
public:
	CMFCwork2Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CMFCwork2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	bool m_init = false;
	CNetTopo* m_NetTopo;
	CTreeCtrl m_tree;


	afx_msg void OnAddEquipment();
	afx_msg void OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	virtual void OnDraw(CDC* /*pDC*/);

	void drawNet();
	void setTree();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // MFCwork2View.cpp 中的调试版本
inline CMFCwork2Doc* CMFCwork2View::GetDocument() const
   { return reinterpret_cast<CMFCwork2Doc*>(m_pDocument); }
#endif

