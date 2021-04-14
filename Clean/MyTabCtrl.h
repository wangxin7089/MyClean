#pragma once

#include "MyShowDlg.h"
#include "MySetDlg.h"
// CMyTabCtrl

class CMyTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTabCtrl)

public:
	CMyTabCtrl();
	virtual ~CMyTabCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CMyShowDlg m_dlgShow;
	CMySetDlg m_dlgSet;

	BOOL m_bFlagShow;
public:
	void InitTabCtrl(int nCount,CString str[]);
	void ShowDlgIndex(int index);   //  ÇÐ»»¶Ô»°¿ò
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};


