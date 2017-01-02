
// MFCENDDoc.h : CMFCENDDoc ��Ľӿ�
//


#pragma once
#include "TopoNet.h"
#include "NetElement.h"


class CMFCENDDoc : public CDocument
{
protected: // �������л�����
	CMFCENDDoc();
	DECLARE_DYNCREATE(CMFCENDDoc)

// ����
public:
	CTopoNet m_toponet;
	CTreeCtrl* m_elementTree;
	void InitTreeData();
	map<int, HTREEITEM> m_hash_type;
	map<int, HTREEITEM> m_hash_element;
// ����
public:
	void resetData();
	void mouseDown(CPoint point);
	void mouseMove(CPoint point);
	void mouseUp(CPoint point);
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMFCENDDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnCreatelement();
	afx_msg void OnCrateline();
};
