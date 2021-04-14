// MyTabCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "Clean.h"
#include "MyTabCtrl.h"


// CMyTabCtrl

IMPLEMENT_DYNAMIC(CMyTabCtrl, CTabCtrl)

CMyTabCtrl::CMyTabCtrl()
{
	m_bFlagShow = FALSE;
}

CMyTabCtrl::~CMyTabCtrl()
{
}
void CMyTabCtrl::InitTabCtrl(int nCount,CString str[])
{
	if(nCount > 0 && str != NULL)
	{
		//  添加标签项
		for(int i=0;i<nCount;i++)
			this->InsertItem(i,str[i]);
			//  设置高度
		this->SetItemSize(CSize(0,32));

		//   对话框的初始化
		m_dlgShow.Create(IDD_MYSHOWDLG,this);
		m_dlgSet.Create(IDD_MYSETDLG,this);
		//  得到 标签的大小
		CRect rect;
		this->GetClientRect(&rect);
		rect.top+=32;
		rect.bottom+=32;
		//   把对话框 向下移动30
		m_dlgShow.MoveWindow(&rect);
		m_dlgSet.MoveWindow(&rect);
		//  显示哪个对话框
		this->ShowDlgIndex(0);
	}
}
void CMyTabCtrl::ShowDlgIndex(int index)
{
	if(index == 0)
	{
		m_dlgShow.ShowWindow(SW_SHOW);
		m_dlgSet.ShowWindow(SW_HIDE);
	}
	if(index == 1)
	{
		CRect rect;
		AfxGetMainWnd()->GetWindowRect(&rect);
		
		if(m_bFlagShow == FALSE)
			rect.bottom += 280;  //  放大 
		else
			rect.bottom -= 280;//  缩小
	
		AfxGetMainWnd()->MoveWindow(&rect);

		m_bFlagShow = !m_bFlagShow;
	}
	if(index == 2)
	{
		m_dlgShow.ShowWindow(SW_HIDE);
		m_dlgSet.ShowWindow(SW_SHOW);
	}
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CMyTabCtrl::OnNMClick)
END_MESSAGE_MAP()



// CMyTabCtrl 消息处理程序




void CMyTabCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int index = this->GetCurSel();
	this->ShowDlgIndex(index);
}
