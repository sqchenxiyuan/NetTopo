
#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "MFCEND.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	m_nComboHeight = 0;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar ��Ϣ�������

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() -(m_nComboHeight+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// �������: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("δ�ܴ���������� \n");
		return -1;      // δ�ܴ���
	}

	m_wndObjectCombo.AddString(_T("Ӧ�ó���"));
	m_wndObjectCombo.AddString(_T("���Դ���"));
	m_wndObjectCombo.SetCurSel(0);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect (&rectCombo);

	m_nComboHeight = rectCombo.Height();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("δ�ܴ�����������\n");
		return -1;      // δ�ܴ���
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* ������*/);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* ����*/);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��: 
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: �ڴ˴���������������
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: �ڴ˴����������� UI ����������
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: �ڴ˴���������������
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: �ڴ˴����������� UI ����������
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
}

void CPropertiesWnd::ShowTypeP(CNetType * type)
{
	m_wndPropList.RemoveAll();

	//ID
	CString id;
	id.Format(_T("%d"), type->m_id);
	CMFCPropertyGridProperty* p_id = new CMFCPropertyGridProperty(_T("ID"), id, _T("���豸��ID"));
	p_id->AllowEdit(false);
	m_wndPropList.AddProperty(p_id);

	//������
	CMFCPropertyGridProperty* p_name = new CMFCPropertyGridProperty(_T("������"), type->m_name, _T("���豸��ID"));
	m_wndPropList.AddProperty(p_name);
	p_name->SetData((DWORD)type);
}

void CPropertiesWnd::ShowElementP(CNetElement* element, vector<CNetType*> typelist)
{
	m_wndPropList.RemoveAll();
	//ID
	CString id;
	id.Format(_T("%d"), element->m_id);
	CMFCPropertyGridProperty* p_id = new CMFCPropertyGridProperty(_T("ID"), id, _T("���豸��ID"));
	p_id->AllowEdit(false);
	m_wndPropList.AddProperty(p_id);

	//����
	CMFCPropertyGridProperty* p_title = new CMFCPropertyGridProperty(_T("����"), element->m_title, _T("���豸��ID"));
	p_title->SetData((DWORD)element);
	m_wndPropList.AddProperty(p_title);


	//����
	CString type;
	int l = typelist.size();
	for (int i = 0; i < l; i++) {
		if (typelist.at(i)->m_id == element->m_type) {
			type = typelist.at(i)->m_name;
			break;
		}
	}

	CMFCPropertyGridProperty* p_type = new CMFCPropertyGridProperty(_T("�豸����"), type, _T("���豸��ID"));
	for (int i = 0; i < l; i++) {
		p_type->AddOption(typelist.at(i)->m_name);
	}
	p_type->SetData((DWORD)element);
	m_wndPropList.AddProperty(p_type);


	//============================Format(_T("%d"), element->m_type);====
	//ͼƬ·��
	//================================

	CMFCPropertyGridProperty* imgpath = new CMFCPropertyGridProperty(_T("ͼƬ·��"), element->m_imgpath, _T("����֮һ: ���ޡ�����ϸ�������ɵ�����С���򡰶Ի������"));
	imgpath->AddOption(_T("src/cloud.png"));
	imgpath->AddOption(_T("src/Router.png"));
	imgpath->AddOption(_T("src/computer.png"));
	imgpath->AddOption(_T("src/mobile_phone.png"));
	imgpath->AllowEdit(FALSE);
	imgpath->SetData((DWORD)element);
	m_wndPropList.AddProperty(imgpath);


	CString f;
	
	//================================
	//ͼƬλ��
	//================================

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("ͼƬλ��"), 0, TRUE); 
	pSize->AllowEdit(FALSE);
	CString a = (_variant_t)(element->m_centerx);

	f.Format(_T("%.3f"), element->m_centerx);
	CMFCPropertyGridProperty*  pProp = new CMFCPropertyGridProperty(_T("X����"), f, _T("ָ������ĸ߶�"), 3);
	pSize->AddSubItem(pProp);

	f.Format(_T("%.3f"), element->m_centery);
	pProp = new CMFCPropertyGridProperty(_T("Y����"), f, _T("ָ������Ŀ��"), 4);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	//================================
	//ͼƬ��С
	//================================

	f.Format(_T("%.0f"), element->m_imgw);
	pSize = new CMFCPropertyGridProperty(_T("ͼƬ��С"), 0, TRUE);
	pSize->AllowEdit(FALSE);
	pProp = new CMFCPropertyGridProperty(_T("ͼƬ���"), f, _T("ָ������ĸ߶�"), 3);
	pSize->AddSubItem(pProp);

	f.Format(_T("%.0f"), element->m_imgh);
	pProp = new CMFCPropertyGridProperty(_T("ͼƬ�߶�"), f, _T("ָ������Ŀ��"), 4);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);
}

void CPropertiesWnd::ShowLineP(CNetLine * line)
{
	m_wndPropList.RemoveAll();

	//ID
	CString id;
	id.Format(_T("%d"), line->m_id);
	CMFCPropertyGridProperty* p_id = new CMFCPropertyGridProperty(_T("ID"), id, _T("���豸��ID"));
	p_id->AllowEdit(false);
	m_wndPropList.AddProperty(p_id);

	//�ڵ�һ
	CMFCPropertyGridProperty* point1 = new CMFCPropertyGridProperty(_T("�ڵ�һ"), (_variant_t)line->m_e1, _T("���豸��ID"));
	point1->SetData((DWORD)line);
	m_wndPropList.AddProperty(point1);

	//�ڵ��
	CMFCPropertyGridProperty* point2 = new CMFCPropertyGridProperty(_T("�ڵ��"), (_variant_t)line->m_e2, _T("���豸��ID"));
	point1->SetData((DWORD)line);
	m_wndPropList.AddProperty(point2);

	//����
	m_wndPropList.AddProperty(new CMFCPropertyGridProperty(_T("����"), (_variant_t)line->m_type, _T("���豸��ID")));
}






void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	int x = 1;

	SetPropListFont();
}

LRESULT CPropertiesWnd::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	CMFCPropertyGridProperty* pProp = reinterpret_cast<CMFCPropertyGridProperty*>(lParam);
	
	if (pProp->GetData()) {
		CString name = pProp->GetName();
		CString value = pProp->GetValue();
		((CMFCENDDoc *)((CMainFrame *)AfxGetMainWnd())->GetActiveView()->GetDocument())
			->changeData(pProp->GetData(), name,value);
	}

	//�Զ���Ĳ���

	return 0;
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}
