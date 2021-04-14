// MyTabCtrl.cpp : ʵ���ļ�
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
		//  ��ӱ�ǩ��
		for(int i=0;i<nCount;i++)
			this->InsertItem(i,str[i]);
			//  ���ø߶�
		this->SetItemSize(CSize(0,32));

		//   �Ի���ĳ�ʼ��
		m_dlgShow.Create(IDD_MYSHOWDLG,this);
		m_dlgSet.Create(IDD_MYSETDLG,this);
		//  �õ� ��ǩ�Ĵ�С
		CRect rect;
		this->GetClientRect(&rect);
		rect.top+=32;
		rect.bottom+=32;
		//   �ѶԻ��� �����ƶ�30
		m_dlgShow.MoveWindow(&rect);
		m_dlgSet.MoveWindow(&rect);
		//  ��ʾ�ĸ��Ի���
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
			rect.bottom += 280;  //  �Ŵ� 
		else
			rect.bottom -= 280;//  ��С
	
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



// CMyTabCtrl ��Ϣ�������




void CMyTabCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	int index = this->GetCurSel();
	this->ShowDlgIndex(index);
}
