// SelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BoxMan.h"
#include "SelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectDlg dialog


CSelectDlg::CSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectDlg)
	m_level = 0;
	//}}AFX_DATA_INIT
}


void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectDlg)
	DDX_Text(pDX, IDC_LEVEL, m_level);
	DDV_MinMaxUInt(pDX, m_level, 1, g_maxlevel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectDlg message handlers

BOOL CSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_level = g_level;		//把全局变量的值赋值给等级显示
	
	return TRUE;			//初始化成功
}

void CSelectDlg::OnOK() 
{
	UpdateData(TRUE);
	g_level = m_level;	
	CDialog::OnOK();
}

int CSelectDlg::DoModal() 
{
	m_level = g_level;		//把全局变量的值赋值给等级显示
	
	return CDialog::DoModal();
}
