#pragma once


// CDAddLine �Ի���

class CDAddLine : public CDialog
{
	DECLARE_DYNAMIC(CDAddLine)

public:
	CDAddLine(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDAddLine();

// �Ի�������
	enum { IDD = IDD_DADDLINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_node1;
	int m_node2;
};
