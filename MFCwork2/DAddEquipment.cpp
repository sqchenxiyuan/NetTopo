// DAddEquipment.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCwork2.h"
#include "DAddEquipment.h"
#include "afxdialogex.h"


// CDAddEquipment 对话框

IMPLEMENT_DYNAMIC(CDAddEquipment, CDialog)
BEGIN_MESSAGE_MAP(CDAddEquipment, CDialog)
END_MESSAGE_MAP()

CDAddEquipment::CDAddEquipment(vector<CString> types,CWnd* pParent /*=NULL*/)
	: CDialog(CDAddEquipment::IDD, pParent)
	, m_imgw(0)
	, m_imgh(0)
	, m_path(_T(""))
	, m_px(0)
	, m_py(0)
	, m_title(_T(""))
	, m_type(_T(""))
{
	m_types = types;
}

CDAddEquipment::~CDAddEquipment()
{
}

void CDAddEquipment::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_IH, m_imgh);
	//  DDX_Text(pDX, IDC_IW, m_imgw);
	//  DDV_MinMaxFloat(pDX, m_imgw, 0, 1);
	DDX_Text(pDX, IDC_IH, m_imgh);
	DDV_MinMaxFloat(pDX, m_imgh, 0, 1000);
	DDX_Text(pDX, IDC_IW, m_imgw);
	DDV_MinMaxFloat(pDX, m_imgw, 0, 1000);
	DDX_Text(pDX, IDC_PATH, m_path);
	DDX_Text(pDX, IDC_PX, m_px);
	DDV_MinMaxFloat(pDX, m_px, 0, 1);
	DDX_Text(pDX, IDC_PY, m_py);
	DDV_MinMaxFloat(pDX, m_py, 0, 1);
	DDX_Text(pDX, IDC_TITLE, m_title);
	DDX_Control(pDX, IDC_COMBO1, c_type);
	DDX_CBString(pDX, IDC_COMBO1, m_type);
}



BOOL CDAddEquipment::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	for (int i = 0; i < m_types.size(); i++) {
		c_type.AddString(m_types.at(i));
	}
	if (m_type == _T("")) {
		c_type.SetCurSel(0);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

