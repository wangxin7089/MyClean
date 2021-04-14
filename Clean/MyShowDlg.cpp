// MyShowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Clean.h"
#include "MyShowDlg.h"
#include "afxdialogex.h"


// CMyShowDlg �Ի���

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


// CMyShowDlg ��Ϣ�������


void CMyShowDlg::OnBnClickedButton1()
{
	TCHAR strFolderName[MAX_PATH] = {0};   //  TCHAR ���ַ���
	TCHAR strFolderPath[MAX_PATH] = {0};   //  �����ļ���·���Ŀռ�

	BROWSEINFO info;
	info.hwndOwner = this->m_hWnd;  //  ˭ӵ������Ի��� 
	info.pidlRoot = NULL;       //  ���ĸ��ļ��� Ϊ��Ŀ¼
	info.pszDisplayName = strFolderName;   //  �����ļ��� ���ֵĿռ�
	info.lpszTitle = _T("~O(��_��)O~");     //  ���� ��ʾ��Ϣ
	info.ulFlags = BIF_EDITBOX;                  // �Ի����ϵĿռ�
	info.lpfn = NULL;  //  ������
	info.lParam = NULL;  //  ������Ϣ
	info.iImage = NULL;  // ͼƬ

	//  ��ʾ  ����ļ��жԻ���
	LPITEMIDLIST path = ::SHBrowseForFolder(&info);
	// ��ȡ����ļ��� ���ڵ�·��
	::SHGetPathFromIDList(path,strFolderPath);
	//  �� strFolderPath �ŵ� ListCtrl��

	m_listCtrlShow.InsertItem(m_listCtrlShow.GetItemCount(),strFolderPath);

}


BOOL CMyShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//  ���� listctrl ��ʽ
	m_listCtrlShow.SetExtendedStyle(LVS_EX_CHECKBOXES/*|LVS_EX_GRIDLINES*/);
	//  ���ز˵�
	m_TrackPopMenu.LoadMenu(IDR_MENU1);

	return TRUE;  // return TRUE unless you set the focus to a control

}


void CMyShowDlg::OnBnClickedButton3()
{
	//  ɾ��ѡ�е���
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
	TCHAR strFolderName[MAX_PATH] = {0};   //  TCHAR ���ַ���
	TCHAR strFolderPath[MAX_PATH] = {0};   //  �����ļ���·���Ŀռ�

	BROWSEINFO info;
	info.hwndOwner = this->m_hWnd;  //  ˭ӵ������Ի��� 
	info.pidlRoot = NULL;       //  ���ĸ��ļ��� Ϊ��Ŀ¼
	info.pszDisplayName = strFolderName;   //  �����ļ��� ���ֵĿռ�
	info.lpszTitle = _T("~O(��_��)O~");     //  ���� ��ʾ��Ϣ
	info.ulFlags = BIF_EDITBOX;                  // �Ի����ϵĿռ�
	info.lpfn = NULL;  //  ������
	info.lParam = NULL;  //  ������Ϣ
	info.iImage = NULL;  // ͼƬ

	//  ��ʾ  ����ļ��жԻ���
	LPITEMIDLIST path = ::SHBrowseForFolder(&info);
	// ��ȡ����ļ��� ���ڵ�·��
	::SHGetPathFromIDList(path,strFolderPath);
	//  �� strFolderPath �ŵ� ListCtrl��

	m_listCtrlShow.InsertItem(m_listCtrlShow.GetItemCount(),strFolderPath);
}
