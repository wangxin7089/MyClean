// MyComboBox.cpp : 实现文件
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



// CMyComboBox 消息处理程序




void CMyComboBox::OnCbnCloseup()
{
	//  判断 选择了下拉列表框的哪一项
	if(this->GetCurSel() == (this->GetCount()-1))
	{
		TCHAR strFolderName[MAX_PATH] = {0};   //  TCHAR 宽字符集
		TCHAR strFolderPath[MAX_PATH] = {0};   //  保存文件夹路径的空间

		BROWSEINFO info;
		info.hwndOwner = this->m_hWnd;  //  谁拥有这个对话框 
		info.pidlRoot = NULL;       //  以哪个文件夹 为根目录
		info.pszDisplayName = strFolderName;   //  接收文件夹 名字的空间
		info.lpszTitle = _T("~O(∩_∩)O~");     //  标题 提示信息
		info.ulFlags = BIF_EDITBOX;                  // 对话框上的空间
		info.lpfn = NULL;  //  处理函数
		info.lParam = NULL;  //  附加信息
		info.iImage = NULL;  // 图片

		//  显示  浏览文件夹对话框
		LPITEMIDLIST path = ::SHBrowseForFolder(&info);
		// 获取这个文件夹 所在的路径
		::SHGetPathFromIDList(path,strFolderPath);

		if(wcscmp(strFolderPath,_T("")))
		{
			//  把 strFolderPath 放到 ComboBox 的编辑控件上
			this->InsertString(0,strFolderPath);
			this->SelectString(-1,strFolderPath);
		}
	}

	this->SetCurSel(0);
}
