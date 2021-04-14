
// CleanDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "MyTabCtrl.h"
#include "MyListCtrlPath.h"
#include "MyThreadPool.h"
// CCleanDlg 对话框
class CCleanDlg : public CDialogEx
{
// 构造
public:
	CCleanDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLEAN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picture;
	CBitmap bitmap1;
	CBitmap bitmap2;
	BOOL m_bFlagBmp;   //  切换图片
	BOOL m_bFlagWndMove;  //  窗口是否移动
	CMyTabCtrl m_tabCtrl;

	CMyListCtrlPath m_listctrlPath;  //  显示 查找到的 文件的路径

public:
	afx_msg void OnStnClickedPicture();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	CMyThreadPool *m_pThreadPool;
public:
	afx_msg void OnDestroy();
};

class CatalogItask :public Itask
{
public:
	CatalogItask(CString str):m_str(str)
	{
	}
	~CatalogItask()
	{
	}
	void RunItask();

private:
	CString m_str;
};
