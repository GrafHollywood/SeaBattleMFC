#pragma once
#include <vector>

class CSDIAppDoc;
// Диалоговое окно CPlaceShipDlg

struct Cell
{
	int Letter;
	int Num;
};

class CPlaceShipDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPlaceShipDlg)

public:
	CPlaceShipDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CPlaceShipDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLACESHIP_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CSDIAppDoc* m_pDoc;
	afx_msg void OnBnClickedButtonPlace();
	// тип корабля
	CString m_sType;
	// координата цифра
	int m_iNum;
	// координата буква
	bool m_bIsHorizontal = true;
	afx_msg void OnBnClickedRadioHorizontal();
	afx_msg void OnBnClickedRadioVertical();
	CString m_sLetter;
	CString m_sOut;
	int LetterToCoord(char letter);
	char CoordToLetter(int coord);
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
};
