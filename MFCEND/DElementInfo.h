#pragma once
#include "afxwin.h"
#include "NetType.h"


// CDElementInfo 对话框

class CDElementInfo : public CDialog
{
	DECLARE_DYNAMIC(CDElementInfo)

public:
	CDElementInfo(vector<CNetType*> typelist,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDElementInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELEMENTINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_imgh=30;
	float m_imgw=40;
	float m_imgx=0.5;
	float m_imgy=0.5;
	CString m_imgpath= _T("src/Router.png");
	CString m_title= _T("新建设备");
	CComboBox m_ctype;

	vector<CNetType*> m_typelist;
	virtual BOOL OnInitDialog();
	CString m_type;
};
