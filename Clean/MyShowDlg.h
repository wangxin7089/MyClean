#pragma once

#include "MyListCtrlShow.h"

// CMyShowDlg �Ի���

class CMyShowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyShowDlg)

public:
	CMyShowDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyShowDlg();

// �Ի�������
	enum { IDD = IDD_MYSHOWDLG };
public:
	CMyListCtrlShow m_listCtrlShow;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
