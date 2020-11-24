
// SDIAppDoc.h : интерфейс класса CSDIAppDoc
//
#include <vector>
#include "MyView.h"
#include "SDIAppView.h"
#include "CPlaceShipDlg.h"

#pragma once

#define CELL_EMPTY 0
#define CELL_SHIP_LIVE 1
#define CELL_SHIP_SHOT 2
#define CELL_EMPTY_SHOT 3

using namespace std;

class CSDIAppDoc : public CDocument
{
protected: // создать только из сериализации
	CSDIAppDoc();
	DECLARE_DYNCREATE(CSDIAppDoc)
// Атрибуты
public:
	//bool m_b;
	CMyView *m_pTree;
	CSDIAppView *m_pView;
	CPlaceShipDlg m_dPlaceShipDlg;

	SOCKET m_Socket; //сокет для отправки и получение запросов сервера

	vector<vector<int>> m_MyAqua;
	vector<vector<int>> m_EnemyAqua;
// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
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
};
