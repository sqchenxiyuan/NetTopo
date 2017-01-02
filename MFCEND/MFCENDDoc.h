
// MFCENDDoc.h : CMFCENDDoc 类的接口
//


#pragma once
#include "TopoNet.h"
#include "NetElement.h"


class CMFCENDDoc : public CDocument
{
protected: // 仅从序列化创建
	CMFCENDDoc();
	DECLARE_DYNCREATE(CMFCENDDoc)

// 特性
public:
	CTopoNet m_toponet;
	CTreeCtrl* m_elementTree;
	void InitTreeData();
	map<int, HTREEITEM> m_hash_type;
	map<int, HTREEITEM> m_hash_element;
// 操作
public:
	void resetData();
	void mouseDown(CPoint point);
	void mouseMove(CPoint point);
	void mouseUp(CPoint point);
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMFCENDDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnCreatelement();
	afx_msg void OnCrateline();
};
