
// SDIAppDoc.h : интерфейс класса CSDIAppDoc
//
#include <vector>
#include "MyView.h"
#include "SDIAppView.h"
#include "CPlaceShipDlg.h"
#include "CAcceptDlg.h"

#pragma once

#define CELL_EMPTY 0
#define CELL_SHIP 1
#define CELL_SHOT 2
#define CELL_MISS 3

using namespace std;

class CSDIAppDoc : public CDocument
{
protected: // создать только из сериализации
	CSDIAppDoc();
	DECLARE_DYNCREATE(CSDIAppDoc)
// Атрибуты
public:
	//bool m_b;
	CMyView *m_pTree; //дерево
	CSDIAppView *m_pView; //игровое поле
	CPlaceShipDlg m_dPlaceShipDlg; //диалог расстановки кораблей
	CAcceptDlg m_dAcceprDlg; //диалог принятия игры

	SOCKET m_Socket; //сокет для отправки и получение запросов сервера

	vector<vector<int>> m_MyAqua; //сетка акватории игрока
	vector<vector<int>> m_EnemyAqua; //сетка акватории противника

	int m_iShip4 = 0, m_iShip3 = 0, m_iShip2 = 0, m_iShip1 = 0; //кол-во кораблей на поле
	bool m_bIsConnect = false;
// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
//	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CSDIAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	bool ConnectServer(int port);
	afx_msg void OnBegin();
	static void WaitEnemyConnect(SOCKET mSocket, CSDIAppDoc* pDoc);
};
