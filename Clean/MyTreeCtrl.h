#pragma once

#include <list>
using namespace std;
// CMyTreeCtrl

class CMyTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CMyTreeCtrl)

public:
	CMyTreeCtrl();
	virtual ~CMyTreeCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	list<HTREEITEM> m_lstClickItem;
public:
	void Delete(HTREEITEM hClickItem);       //  删除  点击这一项的 第三层的
	void InsertOnePage(CString path,HTREEITEM hTreeItemRoot);
	CString GetClickItemPath(HTREEITEM hClickItem);   //  获取点击这一项的 完整路径
public:
	afx_msg void OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};


