#pragma once


// CMyListCtrlShow

class CMyListCtrlShow : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrlShow)

public:
	CMyListCtrlShow();
	virtual ~CMyListCtrlShow();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
};


