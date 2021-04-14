
// CleanDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "MyTabCtrl.h"
#include "MyListCtrlPath.h"
#include "MyThreadPool.h"
// CCleanDlg �Ի���
class CCleanDlg : public CDialogEx
{
// ����
public:
	CCleanDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLEAN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picture;
	CBitmap bitmap1;
	CBitmap bitmap2;
	BOOL m_bFlagBmp;   //  �л�ͼƬ
	BOOL m_bFlagWndMove;  //  �����Ƿ��ƶ�
	CMyTabCtrl m_tabCtrl;

	CMyListCtrlPath m_listctrlPath;  //  ��ʾ ���ҵ��� �ļ���·��

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
