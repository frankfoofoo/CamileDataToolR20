
// CamileDataTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCamileDataToolApp: 
// �йش����ʵ�֣������ CamileDataTool.cpp
//

class CCamileDataToolApp : public CWinApp
{
public:
	CCamileDataToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCamileDataToolApp theApp;
