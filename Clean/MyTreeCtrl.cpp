// MyTreeCtrl.cpp : 实现文件
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



// CMyTreeCtrl 消息处理程序
void CMyTreeCtrl::InsertOnePage(CString path,HTREEITEM hTreeItemRoot)
{
	if(path == _T("") || hTreeItemRoot == NULL)
		return;

	//  文件查找的对象
	CFileFind file;
	path += _T("\\*.*");   //  *.*  查找 所有文件
	//  告诉它去哪查什么东西
	BOOL nflag = file.FindFile(path);

	while(nflag)
	{
		//  查找下一个文件
		nflag = file.FindNextFile();

		//  当前文件 是什么类型的
		if(file.IsDots() == TRUE)   //  看是不是 . 或者 ..文件
			continue;
		
		//  获取文件名
		CString strFileName = file.GetFileName();
		//  把这个文件名 插入到 hTreeItemRoot 的下面
		this->InsertItem(strFileName,hTreeItemRoot);
	}
}
CString CMyTreeCtrl::GetClickItemPath(HTREEITEM hClickItem)
{
	if(hClickItem == NULL)
		return NULL;
	//  先把点击的这一项 的字符串装进去
	CString strPath;

	while(hClickItem)
	{
		//  不停的找父亲项 拿到父亲项的 字符串 拼接 
		CString strParent = this->GetItemText(hClickItem);
		strPath = strParent + '\\' + strPath;
		hClickItem = this->GetParentItem(hClickItem);
	}

	//  去掉斜杠  '\\'
	strPath = strPath.Left(strPath.GetLength()-1);

	return strPath;
}

void CMyTreeCtrl::Delete(HTREEITEM hClickItem)
{
	if(hClickItem == NULL)
		return;

	HTREEITEM hChildItem = this->GetChildItem(hClickItem);
	while(hChildItem)   //  遍历 hClickItem  所有的 子节点
	{
		//----------------删除 hChildItem 这一项的 所有子项-------
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
	//  删除 已经展开的    hTreeItem 的 第三层的
	this->Delete(hTreeItem);


	//  1.  获取点击的这一项的 完整路径
	CString path = this->GetClickItemPath(hTreeItem);

	HTREEITEM hChildItem = this->GetChildItem(hTreeItem);
	//  从点击的这一项开始插入第三层
	while(hChildItem)   //  遍历hTreeItem  所有子项
	{
		//  得到一个新的路径
		CString temp = this->GetItemText(hChildItem);
		temp = path+'\\'+temp;
		//  去path 个路径下查找
		this->InsertOnePage(temp,hChildItem);

		hChildItem = this->GetNextSiblingItem(hChildItem);  //  得到兄弟项
	}
}


void CMyTreeCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	//HTREEITEM hTreeItem = pNMTreeView->itemNew.hItem;

	POINT point;
	::GetCursorPos(&point);
	this->ScreenToClient(&point);   //  屏幕转换成 客户器的坐标
	//  把 坐标 转换成 对应项的句柄
	HTREEITEM hItem = this->HitTest(point);
	if(hItem != NULL)
	{
		//  保存 点击这一项的 句柄
		m_lstClickItem.push_back(hItem);
	}
}
