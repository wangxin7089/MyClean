
// CleanDlg.cpp : ʵ���ļ�
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



// CCleanDlg �Ի���



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
	DDX_Control(pDX, IDC_PICTURE, m_picture);   //  ��m_picture �� IDC_PICTURE �Ŀؼ�����
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


// CCleanDlg ��Ϣ�������

BOOL CCleanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	bitmap1.LoadBitmap(IDB_BITMAP1);
	bitmap2.LoadBitmap(IDB_BITMAP2);

	/*CString str[] = {_T("��ɨĿ¼"),_T("��ʾĿ¼"),_T("����Ŀ¼"),_T("ɨ��ɾ��")};*/
	
	CString str[4];
	for(int i=0;i<4;i++)
		str[i].LoadString(IDS_AAA+i);

	m_tabCtrl.InitTabCtrl(4,str);
	m_listctrlPath.SetExtendedStyle(LVS_EX_CHECKBOXES);

	//��ü�����еĺ���
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	m_pThreadPool->CreateThreadPool(1,si.dwNumberOfProcessors*2,10000);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCleanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{

	CDialogEx::OnSysCommand(nID, lParam);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

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
		//  �������� ��С
		this->MoveWindow(&rect);
	}

	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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


		//  �õ�һ���ڵ� �������·���µĶ���
		
		//  ���� strPath ·���µ����ж���
		CFileFind file;
		BOOL nflag = file.FindFile(m_str + _T("\\*.*"));
		while(nflag)
		{
			nflag = file.FindNextFile();
			CString strName = file.GetFileName();

			if(file.IsDots() == TRUE)  //  ȥ�� . �� ..
				continue;


			if(file.IsDirectory() == TRUE)
			{
			//  1.  �� �ļ���
					//  �� �������Ľڵ����·�� �� ����ļ��е����� ƴ�ӱ��һ���µ�·��
					//  �Żص�������
				//m_quFolerPath.push(strPath+'\\'+strName);
				//Ͷ�ݵ��̳߳���
					//  Ͷ�ݵ��̳߳���
			    Itask *p = new CatalogItask(m_str+'\\'+strName);
		    	pthis->m_pThreadPool->PushItask(p);
			}
			else
			{
			//  2.  �� �ļ�
				//  ��ȡ��׺
				CString str = strName;
				int index = strName.ReverseFind('.');
				strName = strName.Right(strName.GetLength()-index);
				//  �� set ������ĺ�׺ƴ��
				if(pthis->m_tabCtrl.m_dlgSet.m_st.count(strName) == 1)
				{
					//  ƥ��ɹ���  �ͷŵ� CMyListCtrlPath �ؼ���
					pthis->m_listctrlPath.InsertItem(pthis->m_listctrlPath.GetItemCount(),m_str+'\\'+str);
				}
			}
		}
	

}

void CCleanDlg::OnBnClickedButton1()
{
	queue<CString> m_quFolerPath;
	//  1.  �� CMyListCtrlShow �ؼ��� �õ�ѡ�е��Ǽ���  �ȷŵ�������
	CMyListCtrlShow* pListCtrl = &(m_tabCtrl.m_dlgShow.m_listCtrlShow);
	for(int i=0;i<pListCtrl->GetItemCount();i++)
	{
		//  ����һ���ǲ��� ѡ�е�
		if(pListCtrl->GetCheck(i) == TRUE)
		{
			//  ��ȡ�ı�
			CString temp = pListCtrl->GetItemText(i,0);
			if(temp.Right(1) == '\\')
				temp = temp.Left(temp.GetLength()-1);
			//  Ͷ�ݵ��̳߳���
			Itask *p = new CatalogItask(temp);
			m_pThreadPool->PushItask(p);
			//m_quFolerPath.push(temp);
		}
	}




}


void CCleanDlg::OnBnClickedButton2()
{
	// ��  m_listctrlPath  ѡ�е��� ɾ��
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

	// TODO: �ڴ˴������Ϣ����������
	if(m_pThreadPool)
	{
		m_pThreadPool->DestroyThreadPool();
		delete m_pThreadPool;
		m_pThreadPool = nullptr;
	}
}
