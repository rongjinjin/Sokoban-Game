// BoxManDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BoxMan.h"
#include "BoxManDlg.h"

#include <mmsystem.h>
#include "HelpDlg.h"
#include "SelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT g_level = 1;
UINT g_maxlevel = 0;

#define MAP_BACK	   0x30
#define MAP_WHITEWALL  0x31
#define MAP_BLUEWALL   0x32
#define MAP_BALL       0x33
#define MAP_BOX		   0x34
#define MAP_REDBOX     0x35
#define MAP_MAN		   0x36
#define MAP_MANBALL    0x37

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoxManDlg dialog

CBoxManDlg::CBoxManDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBoxManDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBoxManDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	loadMap(g_level);
	passtime = 0;
    m_ptManPosition = getManPosition();
}

void CBoxManDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBoxManDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBoxManDlg, CDialog)
	//{{AFX_MSG_MAP(CBoxManDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDR_EXIT_GAME, OnExitGame)
	ON_COMMAND(IDR_HELP, OnHelp)
	ON_COMMAND(IDR_PLAY_MUSIC, OnPlayMusic)
	ON_COMMAND(IDR_SELECT_LEVEL, OnSelectLevel)
	ON_COMMAND(IDR_START_GAME, OnStartGame)
	ON_COMMAND(IDR_ABOUT, OnAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoxManDlg message handlers

BOOL CBoxManDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			//设置大图标
	SetIcon(m_hIcon, FALSE);		//设置小图标

	//读取配置文件
	g_maxlevel = GetPrivateProfileInt("LEVEL", "MAXLEVEL", 1, ".\\setup.ini");

	InitMenu();						//初始化菜单

	g_level = 1;

	return TRUE;					//初始化成功
}

void CBoxManDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBoxManDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		drawMap(&dc);
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBoxManDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBoxManDlg::OnOK() 
{
	
	CDialog::OnOK();
}

void CBoxManDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CBoxManDlg::OnExitGame() 
{
	CDialog::OnCancel();		//调用基类退出函数	
}

void CBoxManDlg::OnHelp() 
{
	CHelpDlg dlg;

	dlg.DoModal();
	
}

void CBoxManDlg::OnPlayMusic() 
{
	CWnd*   pMain   =   AfxGetMainWnd();   
	CMenu*   pMenu   =   pMain->GetMenu();
	//判断播放音乐菜单当前状态
	BOOL bCheck = (BOOL)pMenu->GetMenuState(IDR_PLAY_MUSIC, MF_CHECKED);
	
	if(bCheck)
	{
		pMenu->CheckMenuItem(IDR_PLAY_MUSIC, 
			MF_BYCOMMAND | MF_UNCHECKED);
	}
	else
	{
		pMenu->CheckMenuItem(IDR_PLAY_MUSIC, 
			MF_BYCOMMAND | MF_CHECKED);
		PlayBackMusic(!bCheck);			//调用播放背景音乐功能函数

	}
}

void CBoxManDlg::OnSelectLevel() 
{
	CSelectDlg dlg;

	dlg.DoModal();
}

void CBoxManDlg::OnStartGame() 
{
	GameStart();
}

void CBoxManDlg::OnAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CBoxManDlg::PlayBackMusic(BOOL bCheck)
{
	//指定文件并播放
	if(bCheck)
	{								//播放指定音乐文件
		sndPlaySound("music.wav",SND_ASYNC); 
	}
	else
	{								//停止播放
		sndPlaySound(NULL,SND_PURGE); 
	}
}

void CBoxManDlg::updateMap(UINT nChar)
{
	int x1, y1, x2, y2, x3, y3;
	
    x1 = m_ptManPosition.x;
    y1 = m_ptManPosition.y;
	
    switch (nChar)
    {
    case VK_UP:
        x2 = x1;
        y2 = y1 - 1;
        x3 = x1;
        y3 = y1 - 2;
        ReDrawMap(x1, y1, x2, y2, x3, y3);
        break;
    case VK_DOWN:
        x2 = x1;
        y2 = y1 + 1;
        x3 = x1;
        y3 = y1 + 2;
        ReDrawMap(x1, y1, x2, y2, x3, y3);
        break;
    case VK_LEFT:
        x2 = x1 - 1;
        y2 = y1;
        x3 = x1 - 2;
        y3 = y1;
        ReDrawMap(x1, y1, x2, y2, x3, y3);
        break;
    case VK_RIGHT:
        x2 = x1 + 1;
        y2 = y1;
        x3 = x1 + 2;
        y3 = y1;
        ReDrawMap(x1, y1, x2, y2, x3, y3);
        break;
	default:
		break;
    }
}

void CBoxManDlg::ReDrawMap(int x1, int y1, int x2, int y2, int x3, int y3)
{
    switch (m_cMap[y2][x2])
    {
    case MAP_BACK:           //地图有问题
        MessageBox("地图有问题");
        break;
    case MAP_WHITEWALL:          
        break;
    case MAP_BLUEWALL:           
        m_cMap[y2][x2] = MAP_MAN;
        if (m_cMap[y1][x1] == MAP_MAN)
            m_cMap[y1][x1] = MAP_BLUEWALL;
        else if (m_cMap[y1][x1] == MAP_MANBALL)
            m_cMap[y1][x1] = MAP_BALL;
        m_ptManPosition.x = x2;
        m_ptManPosition.y = y2;
		passtime++;
        break;
    case MAP_BALL:            
        m_cMap[y2][x2] = MAP_MANBALL;
        if (m_cMap[y1][x1] == MAP_MAN)
            m_cMap[y1][x1] = MAP_BLUEWALL;
        else if (m_cMap[y1][x1] == MAP_MANBALL)
            m_cMap[y1][x1] = MAP_BALL;        
        m_ptManPosition.x = x2;
        m_ptManPosition.y = y2;
		passtime++;
        break;
    case MAP_BOX:         
        if (m_cMap[y3][x3] == MAP_BALL) 
        {
            m_cMap[y3][x3] = MAP_REDBOX;
            m_cMap[y2][x2] = MAP_MAN;
            if (m_cMap[y1][x1] == MAP_MAN)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;
			passtime++;
        }
        else if (m_cMap[y3][x3] == MAP_BLUEWALL) 
        {
            m_cMap[y3][x3] = MAP_BOX;
            m_cMap[y2][x2] = MAP_MAN;
            if (m_cMap[y1][x1] == MAP_MAN)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;
			passtime++;
        }
        break;
    case MAP_REDBOX:             
        if (m_cMap[y3][x3] == MAP_BALL)
        {
            m_cMap[y3][x3] = MAP_REDBOX;
            m_cMap[y2][x2] = MAP_MANBALL;
            if (m_cMap[y1][x1] == MAP_MAN)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;
			passtime++;
        }
        else if (m_cMap[y3][x3] == MAP_BLUEWALL)
        {
            m_cMap[y3][x3] = MAP_BOX;
            m_cMap[y2][x2] = MAP_MANBALL;
            if (m_cMap[y1][x1] == MAP_MAN)
                m_cMap[y1][x1] = MAP_BLUEWALL;
            else if (m_cMap[y1][x1] == MAP_MANBALL)
                m_cMap[y1][x1] = MAP_BALL;
            m_ptManPosition.x = x2;
            m_ptManPosition.y = y2;
			passtime++;
        }        
        break;
    case MAP_MAN:            //地图有问题
        MessageBox("地图有问题");
        break;
    case MAP_MANBALL:            //地图有问题
        MessageBox("地图有问题");
        break;
    }
}

void CBoxManDlg::loadMap(int iMissionNum)
{
    CString str;
    str.Format("[%d]", iMissionNum);
	
	FILE *pFile = fopen("map.txt", "rb");
	if (pFile == NULL)
        return;
	
    char cTmp[20];
    fgets(cTmp, 20, pFile);
    while (strncmp(cTmp, str, 3) != 0)
    {
        fgets(cTmp, 20, pFile);
    }
	
    for (int i = 0; i < 14; i++)
        fgets(m_cMap[i], 20, pFile);
	
    fclose(pFile);
}

void CBoxManDlg::drawMap(CDC *pDC)
{
    int i, j, x, y;
    for (i = 0; i < 14; i++)
    {
        for (j = 0; j < 16; j++)
        {
			x = j * 20;
            y = i * 20;
            switch (m_cMap[i][j])
            {
            case MAP_BACK://0
                drawBack(x, y, pDC);
                break;
            case MAP_WHITEWALL://1
                drawWhiteWall(x, y, pDC);
                break;
            case MAP_BLUEWALL://2
                drawBlueWall(x, y, pDC);
                break;
            case MAP_BALL://3
                drawBall(x, y, pDC);
                break;
            case MAP_BOX://4
                drawBox(x, y, pDC);
                break;
            case MAP_REDBOX://5
                drawRedBox(x, y, pDC);
                break;
            case MAP_MAN://6
                drawMan(x, y, pDC);
                break;
            case MAP_MANBALL://7
                drawManBall(x, y, pDC);
                break;
            }
        }
    }

	COLORREF crText = pDC->GetTextColor();
	COLORREF crBack = pDC->GetBkColor();
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->SetBkColor(RGB(255, 255, 255));
	CString str;
	str.Format("当前等级: %02d", g_level);
    pDC->TextOut(330, 50, str);
	str.Format("已走步数: %03d", passtime);
	pDC->TextOut(330, 100, str);
}

void CBoxManDlg::drawBack(int x, int y, CDC *pDC)
{
    COLORREF clr = RGB(0, 0, 0);
    pDC->FillSolidRect(x, y, 20, 20, clr);
}

void CBoxManDlg::drawWhiteWall(int x, int y, CDC *pDC)
{
    COLORREF clr1 = RGB(255, 255, 255);
    COLORREF clr2 = RGB(48, 48, 48);
    COLORREF clr3 = RGB(192, 192, 192);
    pDC->FillSolidRect(x, y, 19, 19, clr1);
    pDC->FillSolidRect(x + 1, y + 1, 19, 19, clr2);
    pDC->FillSolidRect(x + 1, y + 1, 18, 18, clr3);
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y + 10);
    pDC->LineTo(x + 10, y + 20);
}

void CBoxManDlg::drawBlueWall(int x, int y, CDC *pDC)
{
    COLORREF clr = RGB(0, 0, 255);
    pDC->FillSolidRect(x, y, 20, 20, clr);
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y + 10);
    pDC->LineTo(x + 10, y + 20);
}

void CBoxManDlg::drawBall(int x, int y, CDC *pDC)
{
    COLORREF clr = RGB(0, 0, 255);
    pDC->FillSolidRect(x, y, 20, 20, clr);
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y + 10);
    pDC->LineTo(x + 10, y + 20);
    pDC->Ellipse(x, y, x + 20, y + 20);
    pDC->Ellipse(x + 5, y + 5, x + 15, y + 15);
}

void CBoxManDlg::drawBox(int x, int y, CDC *pDC)
{
    COLORREF clr = RGB(255, 255, 0);
    pDC->FillSolidRect(x, y, 20, 20, clr);
    COLORREF clr2 = RGB(255, 192, 0);
    pDC->FillSolidRect(x + 2, y + 2, 16, 16, clr2);
    COLORREF clr3 = RGB(0, 0, 0);
    pDC->SetPixel(x + 3, y + 3, clr3);
    pDC->SetPixel(x + 17, y + 3, clr3);
    pDC->SetPixel(x + 3, y + 17, clr3);
    pDC->SetPixel(x + 17, y + 17, clr3);
}

void CBoxManDlg::drawRedBox(int x, int y, CDC *pDC)
{
    COLORREF clr = RGB(255, 255, 0);
    pDC->FillSolidRect(x, y, 20, 20, clr);
    COLORREF clr2 = RGB(255, 0, 0);
    pDC->FillSolidRect(x + 2, y + 2, 16, 16, clr2);
    COLORREF clr3 = RGB(0, 0, 0);
    pDC->SetPixel(x + 3, y + 3, clr3);
    pDC->SetPixel(x + 17, y + 3, clr3);
    pDC->SetPixel(x + 3, y + 17, clr3);
    pDC->SetPixel(x + 17, y + 17, clr3);
}

void CBoxManDlg::drawMan(int x, int y, CDC *pDC)
{
    COLORREF clr = RGB(0, 0, 255);                   //蓝色墙
    pDC->FillSolidRect(x, y, 20, 20, clr);
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y + 10);
    pDC->LineTo(x + 10, y + 20);
	
    pDC->Ellipse(x + 6, y + 2, x + 14, y + 10);      //人头
	
    pDC->MoveTo(x + 2, y + 11);                      //人手
    pDC->LineTo(x + 18, y + 11);
	
    pDC->MoveTo(x + 10, y + 10);                     //人身体
    pDC->LineTo(x + 10, y + 12);
	
    pDC->MoveTo(x + 2, y + 20);                      //人脚
    pDC->LineTo(x + 10, y + 12);
    pDC->LineTo(x + 18, y +20);
}

void CBoxManDlg::drawManBall(int x, int y, CDC *pDC)
{
    COLORREF clr = RGB(0, 0, 255);                   //球
    pDC->FillSolidRect(x, y, 20, 20, clr);
    pDC->MoveTo(x, y + 10);
    pDC->LineTo(x + 20, y + 10);
    pDC->MoveTo(x + 10, y + 10);
    pDC->LineTo(x + 10, y + 20);
    pDC->Ellipse(x, y, x + 20, y + 20);
    pDC->Ellipse(x + 5, y + 5, x + 15, y + 15);
	
    pDC->Ellipse(x + 6, y + 2, x + 14, y + 10);      //人头
	
    pDC->MoveTo(x + 2, y + 11);                      //人手
    pDC->LineTo(x + 18, y + 11);
	
    pDC->MoveTo(x + 10, y + 10);                     //人身体
    pDC->LineTo(x + 10, y + 12);
	
    pDC->MoveTo(x + 2, y + 20);                      //人脚
    pDC->LineTo(x + 10, y + 12);
    pDC->LineTo(x + 18, y +20);
}

BOOL CBoxManDlg::isFinish()
{
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (m_cMap[i][j] == MAP_BALL || m_cMap[i][j] == MAP_MANBALL)
			{
                return FALSE;
			}
        }
    }
    return TRUE;
}

void CBoxManDlg::GameStart()
{
	loadMap(g_level);
	m_ptManPosition = getManPosition();
	passtime = 0;

	Invalidate();
}

void CBoxManDlg::InitMenu()
{
	CWnd*   pMain   =   AfxGetMainWnd();   
	CMenu*   pMenu   =   pMain->GetMenu();
	pMenu->CheckMenuItem(IDR_PLAY_MUSIC, 
		MF_BYCOMMAND | MF_UNCHECKED);
}

CPoint CBoxManDlg::getManPosition()
{
    CPoint manPosition(0, 0);
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (m_cMap[i][j] == MAP_MAN || m_cMap[i][j] == MAP_MANBALL)
            {
                manPosition.x = j;
                manPosition.y = i;
            }
        }
    }
    return manPosition;
}



BOOL CBoxManDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN) 
	{ 
		updateMap(pMsg->wParam);
		Invalidate(false);
		if (isFinish())
		{
			AfxMessageBox("您获得胜利,将进入下一关!");
			g_level = g_level +1;
			if (g_level > g_maxlevel)
				g_level = 1;
			GameStart();

		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}



