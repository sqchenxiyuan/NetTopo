// DElementInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCEND.h"
#include "DElementInfo.h"
#include "afxdialogex.h"


// CDElementInfo �Ի���

IMPLEMENT_DYNAMIC(CDElementInfo, CDialog)

CDElementInfo::CDElementInfo(vector<CNetType*> typelist,CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DELEMENTINFO, pParent)
	, m_imgh(40)
	, m_imgw(30)
	, m_imgx(0.5)
	, m_imgy(0.5)
	, m_imgpath(_T("src/Router.png"))
	, m_title(_T("�½��豸"))
	, m_type(_T(""))
{
	m_typelist = typelist;
}

CDElementInfo::~CDElementInfo()
{
}

void CDElementInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, ID_EIMGH, m_imgh);
	DDV_MinMaxFloat(pDX, m_imgh, 0, 1000);
	DDX_Text(pDX, ID_EIMGW, m_imgw);
	DDV_MinMaxFloat(pDX, m_imgw, 0, 1000);
	DDX_Text(pDX, ID_EIMGX, m_imgx);
	DDV_MinMaxFloat(pDX, m_imgx, 0, 1);
	DDX_Text(pDX, ID_EIMGY, m_imgy);
	DDV_MinMaxFloat(pDX, m_imgy, 0, 1);
	DDX_Text(pDX, ID_EIMGPATH, m_imgpath);
	DDX_Text(pDX, ID_ETITLE, m_title);
	DDX_Control(pDX, ID_ETYPE, m_ctype);
	DDX_CBString(pDX, ID_ETYPE, m_type);
}


BEGIN_MESSAGE_MAP(CDElementInfo, CDialog)
END_MESSAGE_MAP()


// CDElementInfo ��Ϣ�������


BOOL CDElementInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	int l = m_typelist.size();
	for (int i = 0; i < l; i++) {
		m_ctype.AddString(m_typelist.at(i)->m_name);
	}
	m_ctype.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
