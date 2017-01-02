
// MFCENDDoc.cpp : CMFCENDDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CMFCENDDoc ����/����

CMFCENDDoc::CMFCENDDoc()
{
	// TODO: �ڴ����һ���Թ������

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

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	m_toponet.buildnewnet();

	CMainFrame * pframe = (CMainFrame *)AfxGetMainWnd();
	m_elementTree = pframe->getElementTree();
	InitTreeData();

	return TRUE;
}




// CMFCENDDoc ���л�

void CMFCENDDoc::Serialize(CArchive& ar)
{
	m_toponet.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMFCENDDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CMFCENDDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CMFCENDDoc ���

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


// CMFCENDDoc ����


BOOL CMFCENDDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  �ڴ������ר�õĴ�������
	CMainFrame * pframe = (CMainFrame *)AfxGetMainWnd();
	m_elementTree = pframe->getElementTree();
	InitTreeData();
	return TRUE;
}


BOOL CMFCENDDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: �ڴ����ר�ô����/����û���

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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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