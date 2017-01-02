// DElementInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCEND.h"
#include "DElementInfo.h"
#include "afxdialogex.h"


// CDElementInfo 对话框

IMPLEMENT_DYNAMIC(CDElementInfo, CDialog)

CDElementInfo::CDElementInfo(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DELEMENTINFO, pParent)
	, m_imgh(0)
	, m_imgw(0)
	, m_imgx(0)
	, m_imgy(0)
	, m_imgpath(_T(""))
	, m_title(_T(""))
{

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
}


BEGIN_MESSAGE_MAP(CDElementInfo, CDialog)
END_MESSAGE_MAP()


// CDElementInfo 消息处理程序
