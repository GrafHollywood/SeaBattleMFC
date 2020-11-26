// CPlaceShipDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "SDIApp.h"
#include "CPlaceShipDlg.h"
#include "SDIAppDoc.h"
#include "afxdialogex.h"
#include <string>

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
	CheckRadioButton(IDC_RADIO_HORIZONTAL, IDC_RADIO_HORIZONTAL, IDC_RADIO_HORIZONTAL);
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
	UpdateData(TRUE);
	if (m_sLetter == L"" || m_sType == L"")
	{
		m_sOut = "Вы не выбрали один из параметров";
		UpdateData(FALSE);
		return;
	}

	int size;


	if (m_sType.Find('4') != -1)
	{
		size = 4;
		if (n4size <=0)
		{
			m_sOut = "Все 4-хпалублые корабли расставлены";
			UpdateData(FALSE);
			return;
		}
	}
	else if (m_sType.Find('3') != -1)
	{
		size = 3;
		if (n3size <= 0)
		{
			m_sOut = "Все 3-хпалублые корабли расставлены";
			UpdateData(FALSE);
			return;
		}
	}
	else if (m_sType.Find('2') != -1)
	{
		size = 2;
		if (n2size <= 0)
		{
			m_sOut = "Все 2-хпалублые корабли расставлены";
			UpdateData(FALSE);
			return;
		}
	}
	else if (m_sType.Find('1') != -1)
	{
		size = 1;
		if (n1size <= 0)
		{
			m_sOut = "Все 1-палублые корабли расставлены";
			UpdateData(FALSE);
			return;
		}
	}

	/*char buf[1024];
	sprintf(buf, "%S", responce);*/

	vector<Cell> shipCells;
	Cell cell;
	cell.Letter = LetterToCoord(m_sLetter[0]);
	cell.Num = m_iNum;
	shipCells.push_back(cell);

	for (int i = 1; i < size; i++)
	{
		if (m_bIsHorizontal)
		{
			cell.Letter++;
			if (cell.Letter > 9)
			{
				m_sOut = "Корабль поставлен неверно";
				UpdateData(FALSE);
				return;
			}
			shipCells.push_back(cell);
		}
		else
		{
			cell.Num++;
			if (cell.Num > 9)
			{
				m_sOut = "Корабль поставлен неверно";
				UpdateData(FALSE);
				return;
			}
			shipCells.push_back(cell);
		}
	}

	string request;

	if (size == 4)
	{
		char str[32];
		sprintf(str, "%i(%c%i,%c%i,%c%i,%c%i)",
			size,
			CoordToLetter(shipCells[0].Letter), shipCells[0].Num + 1,
			CoordToLetter(shipCells[1].Letter), shipCells[1].Num + 1,
			CoordToLetter(shipCells[2].Letter), shipCells[2].Num + 1,
			CoordToLetter(shipCells[3].Letter), shipCells[3].Num + 1
		);
		request = str;
	}
	else if (size == 3)
	{
		char str[32];
		sprintf(str, "%i(%c%i,%c%i,%c%i)",
			size,
			CoordToLetter(shipCells[0].Letter), shipCells[0].Num + 1,
			CoordToLetter(shipCells[1].Letter), shipCells[1].Num + 1,
			CoordToLetter(shipCells[2].Letter), shipCells[2].Num + 1
		);
		request = str;
	}
	else if (size == 2)
	{
		char str[32];
		sprintf(str, "%i(%c%i,%c%i)",
			size,
			CoordToLetter(shipCells[0].Letter), shipCells[0].Num + 1,
			CoordToLetter(shipCells[1].Letter), shipCells[1].Num + 1
		);
		request = str;
	}
	else
	{
		char str[32];
		sprintf(str, "%i(%c%i)",
			size,
			CoordToLetter(shipCells[0].Letter), shipCells[0].Num + 1
		);
		request = str;
	}

	//отправляем серверу местоположение корабля
	send(m_pDoc->m_Socket, request.c_str(), request.size() + 1, 0);

	//получаем ответ от сервера о корректности расположения корабля
	char buff[1024];
	recv(m_pDoc->m_Socket, &buff[0], sizeof(buff), 0);

	string response = buff;

	if (response == "OK")
	{
		m_sOut = "Корабль поставлен";
		UpdateData(FALSE);

		for (int i = 0; i < shipCells.size(); i++)
		{
			m_pDoc->m_MyAqua[shipCells[i].Num][shipCells[i].Letter] = CELL_SHIP;
		}

		m_pDoc->m_pView->Invalidate();

		switch (size)
		{
		case 1:
			n1size--;
			break;
		case 2:
			n2size--;
			break;
		case 3:
			n3size--;
			break;
		case 4:
			n4size--;
			break;
		}
	}
	else
	{
		m_sOut = "Корабль поставлен неверно";
		UpdateData(FALSE);
	}

	recv(m_pDoc->m_Socket, &buff[0], sizeof(buff), 0);
	response = buff;
	if (response == "Ваши корабли готовы!")
	{
		MessageBox(_T("Вы расставили все корабли!"), _T("Расстановка завершена"));
		OnCancel();
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


int CPlaceShipDlg::LetterToCoord(char letter)
{
	// TODO: Добавьте сюда код реализации.
	switch (letter)
	{
	case 'A':
		return LETTER_A;
	case 'B':
		return LETTER_B;
	case 'C':
		return LETTER_C;
	case 'D':
		return LETTER_D;
	case 'E':
		return LETTER_E;
	case 'F':
		return LETTER_F;
	case 'G':
		return LETTER_G;
	case 'H':
		return LETTER_H;
	case 'I':
		return LETTER_I;
	case 'J':
		return LETTER_J;
	}

	return -1;
}


char CPlaceShipDlg::CoordToLetter(int coord)
{
	// TODO: Добавьте сюда код реализации.
	switch (coord)
	{
	case LETTER_A:
		return 'A';
	case LETTER_B:
		return 'B';
	case LETTER_C:
		return 'C';
	case LETTER_D:
		return 'D';
	case LETTER_E:
		return 'E';
	case LETTER_F:
		return 'F';
	case LETTER_G:
		return 'G';
	case LETTER_H:
		return 'H';
	case LETTER_I:
		return 'I';
	case LETTER_J:
		return 'J';
	}
	return -1;
}


void CPlaceShipDlg::OnCancel()
{
	// TODO: добавьте специализированный код или вызов базового класса

	CDialogEx::OnCancel();
}
