#pragma once
#include "afxwin.h"


// CDAddEquipment �Ի���

class CDAddEquipment : public CDialog
{
	DECLARE_DYNAMIC(CDAddEquipment)

public:
	CDAddEquipment(vector<CString> types,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDAddEquipment();

// �Ի�������
	enum { IDD = IDD_DADDEQUIPMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
