
// MyDrawing.h: MyDrawing 애플리케이션의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CMyDrawingApp:
// 이 클래스의 구현에 대해서는 MyDrawing.cpp을(를) 참조하세요.
//

class CMyDrawingApp : public CWinApp
{
public:
	int m_nShape;
	BOOL m_bFill;
	
	CMyDrawingApp() noexcept;

// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDrStraight();
	afx_msg void OnDrRect();
	afx_msg void OnDrEllipse();
	afx_msg void OnDrFill();
	afx_msg void OnUpdateDrFill(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrEllipse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrRect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrStraight(CCmdUI* pCmdUI);
};

extern CMyDrawingApp theApp;
