// MyListCtrlShow.cpp : ʵ���ļ�
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



// CMyListCtrlShow ��Ϣ�������




void CMyListCtrlShow::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// ���� �����˵�
	CMenu* pMenu = &(((CCleanDlg*)AfxGetMainWnd())->m_tabCtrl.m_dlgShow.m_TrackPopMenu);
	//  ��ȡ����λ��
	POINT point;
	::GetCursorPos(&point);
	//  ���������˵�
	pMenu->GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,point.x,point.y,&(((CCleanDlg*)AfxGetMainWnd())->m_tabCtrl.m_dlgShow));

	*pResult = 0;
}
