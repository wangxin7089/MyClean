// MyTreeCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Clean.h"
#include "MyTreeCtrl.h"


// CMyTreeCtrl

IMPLEMENT_DYNAMIC(CMyTreeCtrl, CTreeCtrl)

CMyTreeCtrl::CMyTreeCtrl()
{

}

CMyTreeCtrl::~CMyTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, &CMyTreeCtrl::OnTvnItemexpanding)
	ON_NOTIFY_REFLECT(NM_CLICK, &CMyTreeCtrl::OnNMClick)
END_MESSAGE_MAP()



// CMyTreeCtrl ��Ϣ�������
void CMyTreeCtrl::InsertOnePage(CString path,HTREEITEM hTreeItemRoot)
{
	if(path == _T("") || hTreeItemRoot == NULL)
		return;

	//  �ļ����ҵĶ���
	CFileFind file;
	path += _T("\\*.*");   //  *.*  ���� �����ļ�
	//  ������ȥ�Ĳ�ʲô����
	BOOL nflag = file.FindFile(path);

	while(nflag)
	{
		//  ������һ���ļ�
		nflag = file.FindNextFile();

		//  ��ǰ�ļ� ��ʲô���͵�
		if(file.IsDots() == TRUE)   //  ���ǲ��� . ���� ..�ļ�
			continue;
		
		//  ��ȡ�ļ���
		CString strFileName = file.GetFileName();
		//  ������ļ��� ���뵽 hTreeItemRoot ������
		this->InsertItem(strFileName,hTreeItemRoot);
	}
}
CString CMyTreeCtrl::GetClickItemPath(HTREEITEM hClickItem)
{
	if(hClickItem == NULL)
		return NULL;
	//  �Ȱѵ������һ�� ���ַ���װ��ȥ
	CString strPath;

	while(hClickItem)
	{
		//  ��ͣ���Ҹ����� �õ�������� �ַ��� ƴ�� 
		CString strParent = this->GetItemText(hClickItem);
		strPath = strParent + '\\' + strPath;
		hClickItem = this->GetParentItem(hClickItem);
	}

	//  ȥ��б��  '\\'
	strPath = strPath.Left(strPath.GetLength()-1);

	return strPath;
}

void CMyTreeCtrl::Delete(HTREEITEM hClickItem)
{
	if(hClickItem == NULL)
		return;

	HTREEITEM hChildItem = this->GetChildItem(hClickItem);
	while(hChildItem)   //  ���� hClickItem  ���е� �ӽڵ�
	{
		//----------------ɾ�� hChildItem ��һ��� ��������-------
		HTREEITEM hChildChildItem = this->GetChildItem(hChildItem);
		while(hChildChildItem)
		{
			HTREEITEM hDelItem = hChildChildItem;
			hChildChildItem = this->GetNextSiblingItem(hChildChildItem);
			this->DeleteItem(hDelItem);
		}
		//-----------------------------------------------------------
		hChildItem = this->GetNextSiblingItem(hChildItem);
	}
}

void CMyTreeCtrl::OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	HTREEITEM hTreeItem = pNMTreeView->itemNew.hItem;
	//  ɾ�� �Ѿ�չ����    hTreeItem �� �������
	this->Delete(hTreeItem);


	//  1.  ��ȡ�������һ��� ����·��
	CString path = this->GetClickItemPath(hTreeItem);

	HTREEITEM hChildItem = this->GetChildItem(hTreeItem);
	//  �ӵ������һ�ʼ���������
	while(hChildItem)   //  ����hTreeItem  ��������
	{
		//  �õ�һ���µ�·��
		CString temp = this->GetItemText(hChildItem);
		temp = path+'\\'+temp;
		//  ȥpath ��·���²���
		this->InsertOnePage(temp,hChildItem);

		hChildItem = this->GetNextSiblingItem(hChildItem);  //  �õ��ֵ���
	}
}


void CMyTreeCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	//HTREEITEM hTreeItem = pNMTreeView->itemNew.hItem;

	POINT point;
	::GetCursorPos(&point);
	this->ScreenToClient(&point);   //  ��Ļת���� �ͻ���������
	//  �� ���� ת���� ��Ӧ��ľ��
	HTREEITEM hItem = this->HitTest(point);
	if(hItem != NULL)
	{
		//  ���� �����һ��� ���
		m_lstClickItem.push_back(hItem);
	}
}
