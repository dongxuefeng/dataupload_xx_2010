// RmAgentDllTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CRmAgentDllTestApp:
// �йش����ʵ�֣������ RmAgentDllTest.cpp
//

class CRmAgentDllTestApp : public CWinApp
{
public:
	CRmAgentDllTestApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRmAgentDllTestApp theApp;
