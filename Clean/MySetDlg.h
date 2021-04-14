#pragma once


// CMySetDlg 对话框
#include "MyTreeCtrl.h"
#include "MyComboBox.h"
#include <set>
using namespace std;


class CMySetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMySetDlg)

public:
	CMySetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMySetDlg();

// 对话框数据
	enum { IDD = IDD_MYSETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyTreeCtrl m_treeCtrl;  
	CMyComboBox m_comboBox;

	set<CString> m_st;   //  装 文件的 后缀 
public:
	afx_msg void OnBnClickedBtnFinish();
	afx_msg void OnBnClickedBtnSet();
	virtual BOOL OnInitDialog();
};
