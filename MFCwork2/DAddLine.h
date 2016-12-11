#pragma once


// CDAddLine 对话框

class CDAddLine : public CDialog
{
	DECLARE_DYNAMIC(CDAddLine)

public:
	CDAddLine(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDAddLine();

// 对话框数据
	enum { IDD = IDD_DADDLINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_node1;
	int m_node2;
};
