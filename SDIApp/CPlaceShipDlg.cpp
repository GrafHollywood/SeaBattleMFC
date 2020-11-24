// CPlaceShipDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "SDIApp.h"
#include "CPlaceShipDlg.h"
#include "SDIAppDoc.h"
#include "afxdialogex.h"

#define LETTER_A 0
#define LETTER_B 1
#define LETTER_C 2
#define LETTER_D 3
#define LETTER_E 4
#define LETTER_F 5
#define LETTER_G 6
#define LETTER_H 7
#define LETTER_I 8
#define LETTER_J 9


// Диалоговое окно CPlaceShipDlg

IMPLEMENT_DYNAMIC(CPlaceShipDlg, CDialogEx)

CPlaceShipDlg::CPlaceShipDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLACESHIP_DLG, pParent)
	, m_sType(_T(""))
	, m_iNum(0)
	, m_sLetter(_T(""))
	, m_sOut(_T(""))
{

}

CPlaceShipDlg::~CPlaceShipDlg()
{
}

void CPlaceShipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	CFrameWnd* pFrame = (CFrameWnd*)AfxGetApp()->m_pMainWnd;
	m_pDoc = (CSDIAppDoc*)pFrame->GetActiveDocument();
	DDX_CBString(pDX, IDC_COMBO_TYPE, m_sType);
	DDX_CBIndex(pDX, IDC_COMBO_NUM, m_iNum);
	DDX_CBString(pDX, IDC_COMBO_LETTER, m_sLetter);
	DDX_Text(pDX, IDC_STATIC_OUT, m_sOut);
}


BEGIN_MESSAGE_MAP(CPlaceShipDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PLACE, &CPlaceShipDlg::OnBnClickedButtonPlace)
	ON_BN_CLICKED(IDC_RADIO_HORIZONTAL, &CPlaceShipDlg::OnBnClickedRadioHorizontal)
	ON_BN_CLICKED(IDC_RADIO_VERTICAL, &CPlaceShipDlg::OnBnClickedRadioVertical)
END_MESSAGE_MAP()


// Обработчики сообщений CPlaceShipDlg


void CPlaceShipDlg::OnBnClickedButtonPlace()
{
	// TODO: добавьте свой код обработчика уведомлений
	int count = 0; //кол-во расставленных кораблей
	UpdateData(TRUE);
	if (m_iNum == 0 || m_sLetter == L"" || m_sType == L"")
	{
		m_sOut = "Вы не выбрали один из параметров";
		UpdateData(FALSE);
		return;
	}

	int xCoord, yCoord;
	int size;
	CString responce;
	responce = _T("qwqeqwrqw[]");
	switch (m_sLetter[0])
	{
	case 'A':
		xCoord = LETTER_A;
		break;
	case 'B':
		xCoord = LETTER_B;
		break;
	case 'C':
		xCoord = LETTER_C;
		break;
	case 'D':
		xCoord = LETTER_D;
		break;
	case 'E':
		xCoord = LETTER_E;
		break;
	case 'F':
		xCoord = LETTER_F;
		break;
	case 'G':
		xCoord = LETTER_G;
		break;
	case 'H':
		xCoord = LETTER_H;
		break;
	case 'I':
		xCoord = LETTER_I;
		break;
	case 'J':
		xCoord = LETTER_J;
		break;
	}
	yCoord = m_iNum - 1;

	if (m_sType.Find('4') != -1)
		size = 4;
	else if (m_sType.Find('3') != -1)
		size = 3;
	else if (m_sType.Find('2') != -1)
		size = 2;
	else if (m_sType.Find('1') != -1)
		size = 1;
	/*char buf[1024];
	sprintf(buf, "%S", responce);*/
	
	for (int i = 0; i < size; i++)
	{

	}
}


void CPlaceShipDlg::OnBnClickedRadioHorizontal()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_bIsHorizontal = true;
}


void CPlaceShipDlg::OnBnClickedRadioVertical()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_bIsHorizontal = false;
}
