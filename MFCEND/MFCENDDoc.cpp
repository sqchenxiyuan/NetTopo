
// MFCENDDoc.cpp : CMFCENDDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCEND.h"
#endif

#include "MFCENDDoc.h"
#include "MainFrm.h"
#include "DElementInfo.h"
#include "DLineInfo.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCENDDoc

IMPLEMENT_DYNCREATE(CMFCENDDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCENDDoc, CDocument)
	ON_COMMAND(ID_CREATELEMENT, &CMFCENDDoc::OnCreatelement)
	ON_COMMAND(ID_CRATELINE, &CMFCENDDoc::OnCrateline)
END_MESSAGE_MAP()


// CMFCENDDoc 构造/析构

CMFCENDDoc::CMFCENDDoc()
{
	// TODO: 在此添加一次性构造代码

}



CMFCENDDoc::~CMFCENDDoc()
{
}

void CMFCENDDoc::resetData()
{
	InitTreeData();
}

BOOL CMFCENDDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	m_toponet.buildnewnet();

	CMainFrame * pframe = (CMainFrame *)AfxGetMainWnd();
	m_elementTree = pframe->getElementTree();
	InitTreeData();

	return TRUE;
}




// CMFCENDDoc 序列化

void CMFCENDDoc::Serialize(CArchive& ar)
{
	m_toponet.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMFCENDDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMFCENDDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMFCENDDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCENDDoc 诊断

#ifdef _DEBUG
void CMFCENDDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCENDDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCENDDoc 命令


BOOL CMFCENDDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  在此添加您专用的创建代码
	CMainFrame * pframe = (CMainFrame *)AfxGetMainWnd();
	m_elementTree = pframe->getElementTree();
	InitTreeData();
	return TRUE;
}


BOOL CMFCENDDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDocument::OnSaveDocument(lpszPathName);
}

void CMFCENDDoc::InitTreeData()
{
	m_elementTree->DeleteAllItems();
	POSITION pos;

	m_hash_type.clear();
	pos = m_toponet.m_typeList.GetHeadPosition();
	while (pos)
	{
		CNetType * pobj = (CNetType *)m_toponet.m_typeList.GetNext(pos);
		HTREEITEM item;
		item=m_elementTree->InsertItem(pobj->m_name,0,0);
		m_elementTree->SetItemData(item, (DWORD)pobj);

		m_hash_type[pobj->m_id] = item;
	}

	m_hash_element.clear();
	pos = m_toponet.m_elementList.GetHeadPosition();
	while (pos)
	{
		CNetElement * pobj = (CNetElement *)m_toponet.m_elementList.GetNext(pos);
		CString id;
		id.Format(_T("%d"), pobj->m_id);
		HTREEITEM item;
		item = m_elementTree->InsertItem(id+_T(" ")+pobj->m_title,0,0, m_hash_type.find(pobj->m_type)->second);
		m_elementTree->SetItemData(item, (DWORD)pobj);

		m_hash_element[pobj->m_id] = item;
	}

	pos = m_toponet.m_lineList.GetHeadPosition();
	while (pos)
	{
		CNetLine * pobj = (CNetLine *)m_toponet.m_lineList.GetNext(pos);
		CString id;
		HTREEITEM item;


		id.Format(_T("%d"), pobj->m_e2);
		item = m_elementTree->InsertItem(id, 0, 0, m_hash_element.find(pobj->m_e1)->second);
		m_elementTree->SetItemData(item, (DWORD)pobj);

		id.Format(_T("%d"), pobj->m_e1);
		item = m_elementTree->InsertItem(id, 0, 0, m_hash_element.find(pobj->m_e2)->second);
		m_elementTree->SetItemData(item, (DWORD)pobj);
	}

}

void CMFCENDDoc::OnCreatelement()
{
	// TODO: 在此添加命令处理程序代码
	CDElementInfo dialog;
	if (IDOK == dialog.DoModal())
	{
		CNetElement * newelement = new CNetElement(
			0,
			dialog.m_imgpath,
			dialog.m_title,
			dialog.m_imgx,
			dialog.m_imgy,
			dialog.m_imgw,
			dialog.m_imgh);
		m_toponet.AddElement(newelement);

		CString id;
		id.Format(_T("%d"), newelement->m_id);
		HTREEITEM item;
		item = m_elementTree->InsertItem(id + _T(" ") + newelement->m_title, 0, 0, m_hash_type.find(newelement->m_type)->second);
		m_elementTree->SetItemData(item, (DWORD)newelement);

		m_hash_element[newelement->m_id] = item;
	}
}


void CMFCENDDoc::OnCrateline()
{
	// TODO: 在此添加命令处理程序代码
	CDLineInfo dialog;
	if (IDOK == dialog.DoModal())
	{
		CNetLine * newline = new CNetLine(
			dialog.m_e1,
			dialog.m_e2);
		m_toponet.AddLine(newline);



		CString id;
		HTREEITEM item;
		id.Format(_T("%d"), newline->m_e2);
		item = m_elementTree->InsertItem(id, 0, 0, m_hash_element.find(newline->m_e1)->second);
		m_elementTree->SetItemData(item, (DWORD)newline);

		id.Format(_T("%d"), newline->m_e1);
		item = m_elementTree->InsertItem(id, 0, 0, m_hash_element.find(newline->m_e2)->second);
		m_elementTree->SetItemData(item, (DWORD)newline);
	}
}

void CMFCENDDoc::mouseDown(CPoint point)
{
	m_toponet.down(point);
}

void CMFCENDDoc::mouseMove(CPoint point)
{
	m_toponet.move(point);
}

void CMFCENDDoc::mouseUp(CPoint point)
{
	m_toponet.up(point);
}