#pragma once
#include "afxwin.h"


// CDAddEquipment 对话框

class CDAddEquipment : public CDialog
{
	DECLARE_DYNAMIC(CDAddEquipment)

public:
	CDAddEquipment(vector<CString> types,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDAddEquipment();

// 对话框数据
	enum { IDD = IDD_DADDEQUIPMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
	float m_imgh;
	float m_imgw;
	CString m_path;
	float m_px;
	float m_py;
	CString m_title;
	CString m_type=_T("");
	vector<CString> m_types;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	CComboBox c_type;
	
};
