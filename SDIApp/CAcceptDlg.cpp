// CAcceptDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "SDIApp.h"
#include "CAcceptDlg.h"
#include "afxdialogex.h"


// Диалоговое окно CAcceptDlg

IMPLEMENT_DYNAMIC(CAcceptDlg, CDialogEx)

CAcceptDlg::CAcceptDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ACCEPT_DLG, pParent)
{

}

CAcceptDlg::~CAcceptDlg()
{
}

void CAcceptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAcceptDlg, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений CAcceptDlg
