#pragma once


// CMyComboBox

class CMyComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CMyComboBox)

public:
	CMyComboBox();
	virtual ~CMyComboBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnCloseup();
};


