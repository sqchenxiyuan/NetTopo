#pragma once
#include "afxwin.h"
#include "NetType.h"


// CDElementInfo �Ի���

class CDElementInfo : public CDialog
{
	DECLARE_DYNAMIC(CDElementInfo)

public:
	CDElementInfo(vector<CNetType*> typelist,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDElementInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELEMENTINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_imgh=30;
	float m_imgw=40;
	float m_imgx=0.5;
	float m_imgy=0.5;
	CString m_imgpath= _T("src/Router.png");
	CString m_title= _T("�½��豸");
	CComboBox m_ctype;

	vector<CNetType*> m_typelist;
	virtual BOOL OnInitDialog();
	CString m_type;
};
