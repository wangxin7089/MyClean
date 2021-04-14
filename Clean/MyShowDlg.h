#pragma once

#include "MyListCtrlShow.h"

// CMyShowDlg 对话框

class CMyShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyShowDlg)

public:
	CMyShowDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyShowDlg();

// 对话框数据
	enum { IDD = IDD_MYSHOWDLG };
public:
	CMyListCtrlShow m_listCtrlShow;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMenu m_TrackPopMenu;
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnAaa32771();

};
