#pragma once


// CDLineInfo �Ի���

class CDLineInfo : public CDialog
{
	DECLARE_DYNAMIC(CDLineInfo)

public:
	CDLineInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLineInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLINEINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_e1;
	int m_e2;
};
