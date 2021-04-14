// MyListCtrlShow.cpp : 实现文件
//

#include "stdafx.h"
#include "Clean.h"
#include "MyListCtrlShow.h"
#include "CleanDlg.h"

// CMyListCtrlShow

IMPLEMENT_DYNAMIC(CMyListCtrlShow, CListCtrl)

CMyListCtrlShow::CMyListCtrlShow()
{

}

CMyListCtrlShow::~CMyListCtrlShow()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrlShow, CListCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CMyListCtrlShow::OnNMRClick)
END_MESSAGE_MAP()



// CMyListCtrlShow 消息处理程序




void CMyListCtrlShow::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// 弹出 浮动菜单
	CMenu* pMenu = &(((CCleanDlg*)AfxGetMainWnd())->m_tabCtrl.m_dlgShow.m_TrackPopMenu);
	//  获取光标的位置
	POINT point;
	::GetCursorPos(&point);
	//  弹出浮动菜单
	pMenu->GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,&(((CCleanDlg*)AfxGetMainWnd())->m_tabCtrl.m_dlgShow));

	*pResult = 0;
}
