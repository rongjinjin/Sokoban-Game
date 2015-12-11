// BoxManDlg.h : header file
//

#if !defined(AFX_BOXMANDLG_H__F762E96B_1D50_450F_A4CB_7AA00BC1C0F2__INCLUDED_)
#define AFX_BOXMANDLG_H__F762E96B_1D50_450F_A4CB_7AA00BC1C0F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBoxManDlg dialog

class CBoxManDlg : public CDialog
{
// Construction
public:
	void InitMenu();
	CPoint getManPosition();
	void GameStart();
	BOOL isFinish();
	void drawManBall(int x, int y, CDC* pDC);
	void drawMan(int x, int y, CDC* pDC);
	void drawRedBox(int x, int y, CDC* pDC);
	void drawBox(int x, int y, CDC* pDC);
	void drawBall(int x, int y, CDC* pDC);
	void drawBlueWall(int x, int y, CDC* pDC);
	void drawWhiteWall(int x, int y, CDC* pDC);
	void drawBack(int x, int y, CDC* pDC);
	void drawMap(CDC* pDC);
	void loadMap(int iMissionNum);
	void ReDrawMap(int x1, int y1, int x2, int y2, int x3, int y3);
	void updateMap(UINT nChar);
	void PlayBackMusic(BOOL bCheck);
	CBoxManDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBoxManDlg)
	enum { IDD = IDD_BOXMAN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoxManDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	UINT passtime;

protected:
    char m_cMap[20][20];
    CPoint m_ptManPosition;

	// Generated message map functions
	//{{AFX_MSG(CBoxManDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnExitGame();
	afx_msg void OnHelp();
	afx_msg void OnPlayMusic();
	afx_msg void OnSelectLevel();
	afx_msg void OnStartGame();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOXMANDLG_H__F762E96B_1D50_450F_A4CB_7AA00BC1C0F2__INCLUDED_)
