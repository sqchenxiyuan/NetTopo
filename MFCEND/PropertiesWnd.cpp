
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

	

	



	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("���"));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("��ά���"), (_variant_t) false, _T("ָ�����ڵ����岻ʹ�ô��壬���ҿؼ���ʹ����ά�߿�")));

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("�߿�"), _T("�Ի������"), _T("����֮һ: ���ޡ�����ϸ�������ɵ�����С���򡰶Ի������"));
	pProp->AddOption(_T("��"));
	pProp->AddOption(_T("ϸ"));
	pProp->AddOption(_T("�ɵ�����С"));
	pProp->AddOption(_T("�Ի������"));
	pProp->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("����"), (_variant_t) _T("����"), _T("ָ�����ڱ���������ʾ���ı�")));

	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("���ڴ�С"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("�߶�"), (_variant_t) 250l, _T("ָ�����ڵĸ߶�"));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("���"), (_variant_t) 150l, _T("ָ�����ڵĿ��"));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("����"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	_tcscpy_s(lf.lfFaceName, _T("����, Arial"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("����"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("ָ�����ڵ�Ĭ������")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("ʹ��ϵͳ����"), (_variant_t) true, _T("ָ������ʹ�á�MS Shell Dlg������")));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("����"));
	pProp = new CMFCPropertyGridProperty(_T("(����)"), _T("Ӧ�ó���"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("������ɫ"), RGB(210, 192, 254), NULL, _T("ָ��Ĭ�ϵĴ�����ɫ"));
	pColorProp->EnableOtherButton(_T("����..."));
	pColorProp->EnableAutomaticButton(_T("Ĭ��"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	static const TCHAR szFilter[] = _T("ͼ���ļ�(*.ico)|*.ico|�����ļ�(*.*)|*.*||");
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("ͼ��"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("ָ������ͼ��")));

	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("�ļ���"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("��νṹ"));

	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("��һ���Ӽ�"));
	pGroup4->AddSubItem(pGroup41);

	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("�ڶ����Ӽ�"));
	pGroup41->AddSubItem(pGroup411);

	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�� 1"), (_variant_t) _T("ֵ 1"), _T("��Ϊ˵��")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�� 2"), (_variant_t) _T("ֵ 2"), _T("��Ϊ˵��")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�� 3"), (_variant_t) _T("ֵ 3"), _T("��Ϊ˵��")));

	pGroup4->Expand(FALSE);
	m_wndPropList.AddProperty(pGroup4);


	
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
	p_name->SetData((DWORD)&(type->m_name));
}

void CPropertiesWnd::ShowElementP(CNetElement* element)
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
	p_title->SetData((DWORD)&(element->m_title));
	m_wndPropList.AddProperty(p_title);

	//����
	CString type;
	type.Format(_T("%d"), element->m_type);
	CMFCPropertyGridProperty* p_type = new CMFCPropertyGridProperty(_T("�豸����"), type, _T("���豸��ID"));
	p_id->AllowEdit(false);
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
	imgpath->SetData((DWORD)&(element->m_imgpath));
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
	m_wndPropList.AddProperty(new CMFCPropertyGridProperty(_T("�ڵ�һ"), (_variant_t)line->m_e1, _T("���豸��ID")));

	//�ڵ��
	m_wndPropList.AddProperty(new CMFCPropertyGridProperty(_T("�ڵ��"), (_variant_t)line->m_e2, _T("���豸��ID")));

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
		CString * str=(CString *)pProp->GetData();
		str->SetString((CString)pProp->GetValue());
		//((CMainFrame *)AfxGetMainWnd())->reset();
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
