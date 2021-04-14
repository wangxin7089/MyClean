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
	void Delete(HTREEITEM hClickItem);       //  ɾ��  �����һ��� �������
	void InsertOnePage(CString path,HTREEITEM hTreeItemRoot);
	CString GetClickItemPath(HTREEITEM hClickItem);   //  ��ȡ�����һ��� ����·��
public:
	afx_msg void OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};


