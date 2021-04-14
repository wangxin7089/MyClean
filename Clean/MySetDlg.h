#pragma once


// CMySetDlg �Ի���
#include "MyTreeCtrl.h"
#include "MyComboBox.h"
#include <set>
using namespace std;


class CMySetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMySetDlg)

public:
	CMySetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMySetDlg();

// �Ի�������
	enum { IDD = IDD_MYSETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMyTreeCtrl m_treeCtrl;  
	CMyComboBox m_comboBox;

	set<CString> m_st;   //  װ �ļ��� ��׺ 
public:
	afx_msg void OnBnClickedBtnFinish();
	afx_msg void OnBnClickedBtnSet();
	virtual BOOL OnInitDialog();
};
