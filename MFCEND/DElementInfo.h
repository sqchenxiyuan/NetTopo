#pragma once
#include "afxwin.h"


// CDElementInfo �Ի���

class CDElementInfo : public CDialog
{
	DECLARE_DYNAMIC(CDElementInfo)

public:
	CDElementInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDElementInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELEMENTINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_imgh;
	float m_imgw;
	float m_imgx;
	float m_imgy;
	CString m_imgpath;
	CString m_title;
	CComboBox m_ctype;
};
