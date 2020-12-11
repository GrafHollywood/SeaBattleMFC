#pragma once


// Диалоговое окно CAcceptDlg

class CAcceptDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAcceptDlg)

public:
	CAcceptDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CAcceptDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACCEPT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};
