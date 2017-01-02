#pragma once


// CDLineInfo 对话框

class CDLineInfo : public CDialog
{
	DECLARE_DYNAMIC(CDLineInfo)

public:
	CDLineInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDLineInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLINEINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_e1;
	int m_e2;
};
