
// NI-USB6009-Test.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNIUSB6009TestApp: 
// �йش����ʵ�֣������ NI-USB6009-Test.cpp
//

class CNIUSB6009TestApp : public CWinApp
{
public:
	CNIUSB6009TestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNIUSB6009TestApp theApp;