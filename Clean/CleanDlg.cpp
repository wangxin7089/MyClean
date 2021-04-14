
// CleanDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Clean.h"
#include "CleanDlg.h"
#include "afxdialogex.h"
#include <queue>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CCleanDlg 对话框



CCleanDlg::CCleanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCleanDlg::IDD, pParent)
{
	m_bFlagWndMove = FALSE;
	m_bFlagBmp = FALSE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pThreadPool = new CMyThreadPool;
}

void CCleanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_picture);   //  将m_picture 和 IDC_PICTURE 的控件关联
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl); 
	DDX_Control(pDX, IDC_LIST1, m_listctrlPath); 
}

BEGIN_MESSAGE_MAP(CCleanDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_PICTURE, &CCleanDlg::OnStnClickedPicture)
	ON_BN_CLICKED(IDC_BUTTON1, &CCleanDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCleanDlg::OnBnClickedButton2)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCleanDlg 消息处理程序

BOOL CCleanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	bitmap1.LoadBitmap(IDB_BITMAP1);
	bitmap2.LoadBitmap(IDB_BITMAP2);

	/*CString str[] = {_T("清扫目录"),_T("显示目录"),_T("设置目录"),_T("扫描删除")};*/
	
	CString str[4];
	for(int i=0;i<4;i++)
		str[i].LoadString(IDS_AAA+i);

	m_tabCtrl.InitTabCtrl(4,str);
	m_listctrlPath.SetExtendedStyle(LVS_EX_CHECKBOXES);

	//获得计算机中的核数
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	m_pThreadPool->CreateThreadPool(1,si.dwNumberOfProcessors*2,10000);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCleanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{

	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCleanDlg::OnPaint()
{
	if(m_bFlagWndMove == FALSE)
	{
		m_bFlagWndMove = TRUE;

		CRect rect;
		this->GetWindowRect(&rect);
		int CY = rect.top;
		rect.top = 0;
		rect.bottom-=CY;
		rect.bottom -= 280;
		//  把主窗口 变小
		this->MoveWindow(&rect);
	}

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCleanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CCleanDlg::OnStnClickedPicture()
{
	m_bFlagBmp = !m_bFlagBmp;

	if(m_bFlagBmp == TRUE)
		m_picture.SetBitmap(bitmap2);
	else
		m_picture.SetBitmap(bitmap1);


	/*HBITMAP hBitmap = ::LoadBitmap(AfxGetInstanceHandle(),LPWSTR(IDB_BITMAP2));*/
	//m_picture.SetBitmap(hBitmap);
}

void CatalogItask::RunItask()
{
	//c:\\---m_str
	CCleanDlg *pthis = (CCleanDlg*)theApp.m_pMainWnd;


		//  拿到一个节点 遍历这个路径下的东西
		
		//  查找 strPath 路径下的所有东西
		CFileFind file;
		BOOL nflag = file.FindFile(m_str + _T("\\*.*"));
		while(nflag)
		{
			nflag = file.FindNextFile();
			CString strName = file.GetFileName();

			if(file.IsDots() == TRUE)  //  去掉 . 和 ..
				continue;


			if(file.IsDirectory() == TRUE)
			{
			//  1.  是 文件夹
					//  用 拿下来的节点里的路径 和 这个文件夹的名字 拼接变成一个新的路径
					//  放回到队列里
				//m_quFolerPath.push(strPath+'\\'+strName);
				//投递到线程池中
					//  投递到线程池中
			    Itask *p = new CatalogItask(m_str+'\\'+strName);
		    	pthis->m_pThreadPool->PushItask(p);
			}
			else
			{
			//  2.  是 文件
				//  截取后缀
				CString str = strName;
				int index = strName.ReverseFind('.');
				strName = strName.Right(strName.GetLength()-index);
				//  和 set 集合里的后缀拼配
				if(pthis->m_tabCtrl.m_dlgSet.m_st.count(strName) == 1)
				{
					//  匹配成功了  就放到 CMyListCtrlPath 控件上
					pthis->m_listctrlPath.InsertItem(pthis->m_listctrlPath.GetItemCount(),m_str+'\\'+str);
				}
			}
		}
	

}

void CCleanDlg::OnBnClickedButton1()
{
	queue<CString> m_quFolerPath;
	//  1.  在 CMyListCtrlShow 控件上 拿到选中的那几项  先放到队列里
	CMyListCtrlShow* pListCtrl = &(m_tabCtrl.m_dlgShow.m_listCtrlShow);
	for(int i=0;i<pListCtrl->GetItemCount();i++)
	{
		//  看这一项是不是 选中的
		if(pListCtrl->GetCheck(i) == TRUE)
		{
			//  获取文本
			CString temp = pListCtrl->GetItemText(i,0);
			if(temp.Right(1) == '\\')
				temp = temp.Left(temp.GetLength()-1);
			//  投递到线程池中
			Itask *p = new CatalogItask(temp);
			m_pThreadPool->PushItask(p);
			//m_quFolerPath.push(temp);
		}
	}




}


void CCleanDlg::OnBnClickedButton2()
{
	// 把  m_listctrlPath  选中的项 删除
	for(int i=m_listctrlPath.GetItemCount()-1;i>=0;i--)
	{
		if(m_listctrlPath.GetCheck(i) == TRUE)
		{
			::DeleteFile(m_listctrlPath.GetItemText(i,0));
			m_listctrlPath.DeleteItem(i);
		}
	}
}


void CCleanDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	if(m_pThreadPool)
	{
		m_pThreadPool->DestroyThreadPool();
		delete m_pThreadPool;
		m_pThreadPool = nullptr;
	}
}
