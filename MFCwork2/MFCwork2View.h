
// MFCwork2View.h : CMFCwork2View ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "DAddEquipment.h"
#include "DAddLine.h"


class CMFCwork2View : public CFormView
{
protected: // �������л�����
	CMFCwork2View();
	DECLARE_DYNCREATE(CMFCwork2View)

public:
	enum{ IDD = IDD_MFCWORK2_FORM };

// ����
public:
	CMFCwork2Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CMFCwork2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // MFCwork2View.cpp �еĵ��԰汾
inline CMFCwork2Doc* CMFCwork2View::GetDocument() const
   { return reinterpret_cast<CMFCwork2Doc*>(m_pDocument); }
#endif

