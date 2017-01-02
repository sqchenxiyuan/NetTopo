// DLineInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCEND.h"
#include "DLineInfo.h"
#include "afxdialogex.h"


// CDLineInfo 对话框

IMPLEMENT_DYNAMIC(CDLineInfo, CDialog)

CDLineInfo::CDLineInfo(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DLINEINFO, pParent)
	, m_e1(0)
	, m_e2(0)
{

}

CDLineInfo::~CDLineInfo()
{
}

void CDLineInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, ID_E1, m_e1);
	DDX_Text(pDX, ID_E2, m_e2);
}


BEGIN_MESSAGE_MAP(CDLineInfo, CDialog)
END_MESSAGE_MAP()


// CDLineInfo 消息处理程序
