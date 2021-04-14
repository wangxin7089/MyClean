// MyComboBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Clean.h"
#include "MyComboBox.h"


// CMyComboBox

IMPLEMENT_DYNAMIC(CMyComboBox, CComboBox)

CMyComboBox::CMyComboBox()
{

}

CMyComboBox::~CMyComboBox()
{
}


BEGIN_MESSAGE_MAP(CMyComboBox, CComboBox)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, &CMyComboBox::OnCbnCloseup)
END_MESSAGE_MAP()



// CMyComboBox ��Ϣ�������




void CMyComboBox::OnCbnCloseup()
{
	//  �ж� ѡ���������б�����һ��
	if(this->GetCurSel() == (this->GetCount()-1))
	{
		TCHAR strFolderName[MAX_PATH] = {0};   //  TCHAR ���ַ���
		TCHAR strFolderPath[MAX_PATH] = {0};   //  �����ļ���·���Ŀռ�

		BROWSEINFO info;
		info.hwndOwner = this->m_hWnd;  //  ˭ӵ������Ի��� 
		info.pidlRoot = NULL;       //  ���ĸ��ļ��� Ϊ��Ŀ¼
		info.pszDisplayName = strFolderName;   //  �����ļ��� ���ֵĿռ�
		info.lpszTitle = _T("~O(��_��)O~");     //  ���� ��ʾ��Ϣ
		info.ulFlags = BIF_EDITBOX;                  // �Ի����ϵĿռ�
		info.lpfn = NULL;  //  ������
		info.lParam = NULL;  //  ������Ϣ
		info.iImage = NULL;  // ͼƬ

		//  ��ʾ  ����ļ��жԻ���
		LPITEMIDLIST path = ::SHBrowseForFolder(&info);
		// ��ȡ����ļ��� ���ڵ�·��
		::SHGetPathFromIDList(path,strFolderPath);

		if(wcscmp(strFolderPath,_T("")))
		{
			//  �� strFolderPath �ŵ� ComboBox �ı༭�ؼ���
			this->InsertString(0,strFolderPath);
			this->SelectString(-1,strFolderPath);
		}
	}

	this->SetCurSel(0);
}
