
// MFCwork2.h : MFCwork2 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFCwork2App:
// �йش����ʵ�֣������ MFCwork2.cpp
//

class CMFCwork2App : public CWinApp
{
public:
	CMFCwork2App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCwork2App theApp;
