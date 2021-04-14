// MySetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Clean.h"
#include "MySetDlg.h"
#include "CleanDlg.h"
#include "afxdialogex.h"


// CMySetDlg 对话框

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


// CMySetDlg 消息处理程序


void CMySetDlg::OnBnClickedBtnFinish()  //  完成设置
{
	//  遍历链表   找到选中的那些项
	list<HTREEITEM>::iterator ite = m_treeCtrl.m_lstClickItem.begin();
	while(ite != m_treeCtrl.m_lstClickItem.end())
	{
		//  看这一项是不是选中的
		if(m_treeCtrl.GetCheck(*ite) == TRUE)
		{
			//  获取这一项的 文本
			CString str = m_treeCtrl.GetItemText(*ite);
			//  截取后缀
			//  查找 .
			int index = str.ReverseFind('.');
			if(index != -1)
			{
				str = str.Right(str.GetLength()-index);
				//  保存到 集合里   用来取重复
				m_st.insert(str);
			}
		}
		++ite;
	}
	//  清空链表
	m_treeCtrl.m_lstClickItem.clear();

	if(m_st.size() > 0)
	{
		MessageBox(_T("设置成功!"));
		//  跳转到 清扫目录
		((CCleanDlg*)AfxGetMainWnd())->m_tabCtrl.ShowDlgIndex(0);
		((CCleanDlg*)AfxGetMainWnd())->m_tabCtrl.SetCurSel(0);
	}
	else
	{
		MessageBox(_T("设置失败!"));
	}
}


void CMySetDlg::OnBnClickedBtnSet()   //  设置  查找的文件类型
{
	//  删除 treeCtrl 上面 所有东西
	m_treeCtrl.DeleteAllItems();
	//  获取 编辑框上的东西
	CString path;
	m_comboBox.GetWindowText(path);
	//  判断 path 路径 是盘符 函数文件夹
	if(path.Right(1) == '\\')
	{
		//  去掉'\\'
		path = path.Left(path.GetLength()-1);
	}
	//  放到 tree 控件上
	HTREEITEM hTreeItemRoot = m_treeCtrl.InsertItem(path);
	//  在path路径下查找  找到所有东西 插入到hTreeItemRoot 的下面
	m_treeCtrl.InsertOnePage(path,hTreeItemRoot);
}


BOOL CMySetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_comboBox.AddString(_T("默认目录"));
	m_comboBox.AddString(_T("请选择目录..."));
	//  选中某一项 放到 ComboBox控件编辑框里
	m_comboBox.SelectString(-1,_T("默认目录"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
}
