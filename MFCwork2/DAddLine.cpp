// DAddLine.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCwork2.h"
#include "DAddLine.h"
#include "afxdialogex.h"


// CDAddLine �Ի���

IMPLEMENT_DYNAMIC(CDAddLine, CDialog)

CDAddLine::CDAddLine(CWnd* pParent /*=NULL*/)
	: CDialog(CDAddLine::IDD, pParent)
	, m_node1(0)
	, m_node2(0)
{

}

CDAddLine::~CDAddLine()
{
}

void CDAddLine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NODE1, m_node1);
	DDX_Text(pDX, IDC_NODE2, m_node2);
}


BEGIN_MESSAGE_MAP(CDAddLine, CDialog)
END_MESSAGE_MAP()


// CDAddLine ��Ϣ�������
