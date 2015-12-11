// BoxMan.h : main header file for the BOXMAN application
//

#if !defined(AFX_BOXMAN_H__54A1A49E_727A_43FD_B0AC_7736E87A2FD7__INCLUDED_)
#define AFX_BOXMAN_H__54A1A49E_727A_43FD_B0AC_7736E87A2FD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBoxManApp:
// See BoxMan.cpp for the implementation of this class
//

class CBoxManApp : public CWinApp
{
public:
	CBoxManApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoxManApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBoxManApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOXMAN_H__54A1A49E_727A_43FD_B0AC_7736E87A2FD7__INCLUDED_)
