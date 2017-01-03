
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
	ON_COMMAND(ID_DELELEMENT, &CMFCENDDoc::OnDelelement)
	ON_COMMAND(ID_DELLINE, &CMFCENDDoc::OnDelline)
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

	m_hash_line.clear();
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

		m_hash_line[pobj->m_id] = item;
	}

}

void CMFCENDDoc::OnCreatelement()
{
	// TODO: 在此添加命令处理程序代码
	CDElementInfo dialog(m_toponet.getTypeList());
	if (IDOK == dialog.DoModal())
	{
		int id_type = m_toponet.getTypeIdByName(dialog.m_type);

		CNetElement * newelement = new CNetElement(
			id_type,
			dialog.m_imgpath,
			dialog.m_title,
			dialog.m_imgx,
			dialog.m_imgy,
			dialog.m_imgw,
			dialog.m_imgh);
		m_toponet.AddElement(newelement);

		InitTreeData();
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

bool CMFCENDDoc::mouseDown(CPoint point)
{
	if (m_toponet.down(point)) {

		POSITION pos;
		pos = m_toponet.m_elementList.GetHeadPosition();
		while (pos)
		{
			CNetElement * element = (CNetElement *)m_toponet.m_elementList.GetNext(pos);
			if (element->m_selected) {
				showElementP(element);
				return true;
			}
		}

		pos = m_toponet.m_lineList.GetHeadPosition();
		while (pos)
		{
			CNetLine * line = (CNetLine *)m_toponet.m_lineList.GetNext(pos);
			if (line->m_select) {
				showLineP(line);
				return true;
			}
		}
	}
	return false;
}

void CMFCENDDoc::mouseMove(CPoint point)
{
	m_toponet.move(point);
}

void CMFCENDDoc::mouseUp(CPoint point)
{
	m_toponet.up(point);
}

void CMFCENDDoc::mouseOut()
{
	m_toponet.out();
}

void CMFCENDDoc::showElementP(CNetElement * element)
{
	((CMainFrame *)AfxGetMainWnd())->showPData((DWORD)element);
}

void CMFCENDDoc::showLineP(CNetLine * line)
{
	((CMainFrame *)AfxGetMainWnd())->showPData((DWORD)line);
}


void CMFCENDDoc::OnDelelement()
{
	CNetElement * element = m_toponet.RemoveElement();
	if (element != NULL) {
		HTREEITEM item=m_hash_element.find(element->m_id)->second;
		m_elementTree->DeleteItem(item);

		CNetLine * line = NULL;
		while (line = m_toponet.RemoveLine(element)) {
			m_elementTree->DeleteItem(m_hash_line.find(line->m_id)->second);
			delete line;
		}
		delete element;
	}
	else {
		AfxGetMainWnd()->MessageBox(_T("请选中要删除的设备"));
	}
	// TODO: 在此添加命令处理程序代码
}


void CMFCENDDoc::OnDelline()
{
	CNetLine * line = m_toponet.RemoveLine();
	if (line != NULL) {
		HTREEITEM item = m_hash_line.find(line->m_id)->second;
		m_elementTree->DeleteItem(item);
		delete line;
	}
	else {
		AfxGetMainWnd()->MessageBox(_T("请选中要删除的连接"));
	}
	// TODO: 在此添加命令处理程序代码
}


void CMFCENDDoc::changeData(DWORD data, CString dataname, CString datavalue)
{
	CObject* obj = (CObject*)data;
	if (obj->IsKindOf(RUNTIME_CLASS(CNetElement))) {
		if (dataname == "标题") {
			((CNetElement*)obj)->m_title = datavalue;
		}
		else if (dataname == "图片路径") {
			((CNetElement*)obj)->m_imgpath = datavalue;
		}
		else if (dataname == "设备类型") {
			((CNetElement*)obj)->m_type = m_toponet.getTypeIdByName(datavalue);
		}
	}
	else if (obj->IsKindOf(RUNTIME_CLASS(CNetLine))) {
		if (dataname == "节点一") {
			int id = _ttoi(datavalue);
			CNetElement* element = m_toponet.GetElementById(id);
			if (element !=NULL) {
				((CNetLine*)obj)->m_e1 = id;
				((CNetLine*)obj)->e1 = element;
			}
			else {
				AfxGetMainWnd()->MessageBox(_T("错误的ID号!"));
			}
		}
		else if (dataname == "节点二") {
			int id = _ttoi(datavalue);
			CNetElement* element = m_toponet.GetElementById(id);
			if (element != NULL) {
				((CNetLine*)obj)->m_e2 = id;
				((CNetLine*)obj)->e2 = element;
			}
			else {
				AfxGetMainWnd()->MessageBox(_T("错误的ID号!"));
			}
		}
	}
	else if (obj->IsKindOf(RUNTIME_CLASS(CNetType))) {
		if (dataname == "类型名") {
			((CNetType*)obj)->m_name = datavalue;
		}
	}

	InitTreeData();
}