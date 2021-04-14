// MyShowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Clean.h"
#include "MyShowDlg.h"
#include "afxdialogex.h"


// CMyShowDlg 对话框

IMPLEMENT_DYNAMIC(CMyShowDlg, CDialogEx)

CMyShowDlg::CMyShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyShowDlg::IDD, pParent)
{

}

CMyShowDlg::~CMyShowDlg()
{
}

void CMyShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST1,m_listCtrlShow);
}


BEGIN_MESSAGE_MAP(CMyShowDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyShowDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyShowDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyShowDlg::OnBnClickedButton2)
	ON_COMMAND(ID_AAA_32771, &CMyShowDlg::OnAaa32771)
END_MESSAGE_MAP()


// CMyShowDlg 消息处理程序


void CMyShowDlg::OnBnClickedButton1()
{
	TCHAR strFolderName[MAX_PATH] = {0};   //  TCHAR 宽字符集
	TCHAR strFolderPath[MAX_PATH] = {0};   //  保存文件夹路径的空间

	BROWSEINFO info;
	info.hwndOwner = this->m_hWnd;  //  谁拥有这个对话框 
	info.pidlRoot = NULL;       //  以哪个文件夹 为根目录
	info.pszDisplayName = strFolderName;   //  接收文件夹 名字的空间
	info.lpszTitle = _T("~O(∩_∩)O~");     //  标题 提示信息
	info.ulFlags = BIF_EDITBOX;                  // 对话框上的空间
	info.lpfn = NULL;  //  处理函数
	info.lParam = NULL;  //  附加信息
	info.iImage = NULL;  // 图片

	//  显示  浏览文件夹对话框
	LPITEMIDLIST path = ::SHBrowseForFolder(&info);
	// 获取这个文件夹 所在的路径
	::SHGetPathFromIDList(path,strFolderPath);
	//  把 strFolderPath 放到 ListCtrl上

	m_listCtrlShow.InsertItem(m_listCtrlShow.GetItemCount(),strFolderPath);

}


BOOL CMyShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//  设置 listctrl 样式
	m_listCtrlShow.SetExtendedStyle(LVS_EX_CHECKBOXES/*|LVS_EX_GRIDLINES*/);
	//  加载菜单
	m_TrackPopMenu.LoadMenu(IDR_MENU1);

	return TRUE;  // return TRUE unless you set the focus to a control

}


void CMyShowDlg::OnBnClickedButton3()
{
	//  删除选中的项
	for(int i=m_listCtrlShow.GetItemCount()-1;i>=0;i--)
	{
		if(m_listCtrlShow.GetCheck(i) == TRUE)
		{
			m_listCtrlShow.DeleteItem(i);
		}
	}
}


void CMyShowDlg::OnBnClickedButton2()
{
	m_listCtrlShow.DeleteAllItems();
}


void CMyShowDlg::OnAaa32771()
{
	TCHAR strFolderName[MAX_PATH] = {0};   //  TCHAR 宽字符集
	TCHAR strFolderPath[MAX_PATH] = {0};   //  保存文件夹路径的空间

	BROWSEINFO info;
	info.hwndOwner = this->m_hWnd;  //  谁拥有这个对话框 
	info.pidlRoot = NULL;       //  以哪个文件夹 为根目录
	info.pszDisplayName = strFolderName;   //  接收文件夹 名字的空间
	info.lpszTitle = _T("~O(∩_∩)O~");     //  标题 提示信息
	info.ulFlags = BIF_EDITBOX;                  // 对话框上的空间
	info.lpfn = NULL;  //  处理函数
	info.lParam = NULL;  //  附加信息
	info.iImage = NULL;  // 图片

	//  显示  浏览文件夹对话框
	LPITEMIDLIST path = ::SHBrowseForFolder(&info);
	// 获取这个文件夹 所在的路径
	::SHGetPathFromIDList(path,strFolderPath);
	//  把 strFolderPath 放到 ListCtrl上

	m_listCtrlShow.InsertItem(m_listCtrlShow.GetItemCount(),strFolderPath);
}
