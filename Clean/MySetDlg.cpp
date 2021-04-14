// MySetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Clean.h"
#include "MySetDlg.h"
#include "CleanDlg.h"
#include "afxdialogex.h"


// CMySetDlg �Ի���

IMPLEMENT_DYNAMIC(CMySetDlg, CDialogEx)

CMySetDlg::CMySetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMySetDlg::IDD, pParent)
{

}

CMySetDlg::~CMySetDlg()
{
}

void CMySetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_TREE1,m_treeCtrl);
	DDX_Control(pDX,IDC_COMBO1,m_comboBox);
}


BEGIN_MESSAGE_MAP(CMySetDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_FINISH, &CMySetDlg::OnBnClickedBtnFinish)
	ON_BN_CLICKED(IDC_BTN_SET, &CMySetDlg::OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CMySetDlg ��Ϣ�������


void CMySetDlg::OnBnClickedBtnFinish()  //  �������
{
	//  ��������   �ҵ�ѡ�е���Щ��
	list<HTREEITEM>::iterator ite = m_treeCtrl.m_lstClickItem.begin();
	while(ite != m_treeCtrl.m_lstClickItem.end())
	{
		//  ����һ���ǲ���ѡ�е�
		if(m_treeCtrl.GetCheck(*ite) == TRUE)
		{
			//  ��ȡ��һ��� �ı�
			CString str = m_treeCtrl.GetItemText(*ite);
			//  ��ȡ��׺
			//  ���� .
			int index = str.ReverseFind('.');
			if(index != -1)
			{
				str = str.Right(str.GetLength()-index);
				//  ���浽 ������   ����ȡ�ظ�
				m_st.insert(str);
			}
		}
		++ite;
	}
	//  �������
	m_treeCtrl.m_lstClickItem.clear();

	if(m_st.size() > 0)
	{
		MessageBox(_T("���óɹ�!"));
		//  ��ת�� ��ɨĿ¼
		((CCleanDlg*)AfxGetMainWnd())->m_tabCtrl.ShowDlgIndex(0);
		((CCleanDlg*)AfxGetMainWnd())->m_tabCtrl.SetCurSel(0);
	}
	else
	{
		MessageBox(_T("����ʧ��!"));
	}
}


void CMySetDlg::OnBnClickedBtnSet()   //  ����  ���ҵ��ļ�����
{
	//  ɾ�� treeCtrl ���� ���ж���
	m_treeCtrl.DeleteAllItems();
	//  ��ȡ �༭���ϵĶ���
	CString path;
	m_comboBox.GetWindowText(path);
	//  �ж� path ·�� ���̷� �����ļ���
	if(path.Right(1) == '\\')
	{
		//  ȥ��'\\'
		path = path.Left(path.GetLength()-1);
	}
	//  �ŵ� tree �ؼ���
	HTREEITEM hTreeItemRoot = m_treeCtrl.InsertItem(path);
	//  ��path·���²���  �ҵ����ж��� ���뵽hTreeItemRoot ������
	m_treeCtrl.InsertOnePage(path,hTreeItemRoot);
}


BOOL CMySetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_comboBox.AddString(_T("Ĭ��Ŀ¼"));
	m_comboBox.AddString(_T("��ѡ��Ŀ¼..."));
	//  ѡ��ĳһ�� �ŵ� ComboBox�ؼ��༭����
	m_comboBox.SelectString(-1,_T("Ĭ��Ŀ¼"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
}
