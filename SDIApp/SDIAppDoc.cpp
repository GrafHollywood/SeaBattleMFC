
// SDIAppDoc.cpp : реализация класса CSDIAppDoc
//

#include "stdafx.h"
#include <winsock.h>
#include <thread>
#include <string>
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SDIApp.h"
#endif

#include "SDIAppDoc.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SERVERADDR "127.0.0.1"

// CSDIAppDoc

IMPLEMENT_DYNCREATE(CSDIAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CSDIAppDoc, CDocument)
	//	ON_COMMAND(AFX_ID_PREVIEW_PREV, &CSDIAppDoc::OnAfxIdPreviewPrev)
	ON_COMMAND(ID_BEGIN, &CSDIAppDoc::OnBegin)
	ON_COMMAND(ID_PLACESHIP, &CSDIAppDoc::OnPlaceship)
	ON_COMMAND(ID_SHOT, &CSDIAppDoc::OnShot)
	ON_UPDATE_COMMAND_UI(ID_BEGIN, &CSDIAppDoc::OnUpdateBegin)
	ON_UPDATE_COMMAND_UI(ID_SHOT, &CSDIAppDoc::OnUpdateShot)
	ON_UPDATE_COMMAND_UI(ID_PLACESHIP, &CSDIAppDoc::OnUpdatePlaceship)
END_MESSAGE_MAP()


// создание/уничтожение CSDIAppDoc

CSDIAppDoc::CSDIAppDoc()
{
	// TODO: добавьте код для одноразового вызова конструктора
	//заполним по умолчанию акваторию игрока и противника пустыми клетками (0)
	for (int i = 0; i < 10; i++)
	{
		vector<int> array;
		for (int j = 0; j < 10; j++)
		{
			array.push_back(CELL_EMPTY);
		}
		m_MyAqua.push_back(array);
		m_EnemyAqua.push_back(array);
	}
}

CSDIAppDoc::~CSDIAppDoc()
{
}

BOOL CSDIAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)
	/*for (int i=0; i < 1000; i++)
	{
		pt point;
		point.x = i;
		point.y = i*sin(i) / log(i);
		m_Points.push_back(point);
	}*/

	m_pTree->UpdateTree();

	return TRUE;
}




// сериализация CSDIAppDoc

//void CSDIAppDoc::Serialize(CArchive& ar)
//{
//	/*if (ar.IsStoring())
//	{
//		// TODO: добавьте код сохранения
//		size_t count = m_Points.size();
//		ar << count;
//
//		for (size_t i = 0; i < count; i++)
//		{
//			ar << m_Points[i].x;
//			ar << m_Points[i].y;
//		}
//	}
//	else
//	{
//		// TODO: добавьте код загрузки
//		size_t count;
//		ar >> count;
//
//		m_Points.clear();
//		for (size_t i = 0; i < count; i++)
//		{
//			pt point;
//			ar >> point.x;
//			ar >> point.y;
//			m_Points.push_back(point);
//		}
//	}*/
//}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CSDIAppDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CSDIAppDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задайте содержимое поиска из данных документа. 
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CSDIAppDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// диагностика CSDIAppDoc

#ifdef _DEBUG
void CSDIAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDIAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// команды CSDIAppDoc


bool CSDIAppDoc::ConnectServer(int port)
{
	// TODO: Добавьте сюда код реализации.
	//проверка чтобы не подключиться второй раз
	if (!send(m_Socket, NULL, 0, 0))
	{
		MessageBox(NULL, _T("Вы уже подключены к серверу"), _T("Ошибка"), MB_ICONWARNING);
		return false;
	}

	WSAData wsaData;
	//если ошибка инициализации библиотеки Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		MessageBox(NULL, _T("Ошибка инициализации бибилиотеки"), _T("Ошибка"), MB_ICONWARNING);
		return false;
	}

	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	//если произошла ошибка создания сокета
	if (m_Socket < 0)
	{
		MessageBox(NULL, _T("Ошибка создания сокета"), _T("Ошибка"), MB_ICONWARNING);
		WSACleanup();
		return false;
	}

	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(port);
	if (inet_addr(SERVERADDR) != INADDR_NONE)
		dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
	else
	{
		//некорректный адрес
		MessageBox(NULL, _T("Некорректный адрес"), _T("Ошибка"), MB_ICONERROR);
		closesocket(m_Socket);
		WSACleanup();
		return false;
	}
	// адрес сервера получен – пытаемся установить соединение
	if (connect(m_Socket, (sockaddr*)&dest_addr, sizeof(dest_addr)))
	{
		//неудалось подключится
		MessageBox(NULL, _T("Не удалось подключиться к серверу"), _T("Ошибка"), MB_ICONERROR);
		closesocket(m_Socket);
		WSACleanup();
		return false;
	}
	return true;
}


void CSDIAppDoc::OnBegin()
{
	// TODO: добавьте свой код обработчика команд
	if (!ConnectServer(10000))
		return;

	thread th(WaitEnemyConnect, m_Socket, this);
	th.detach();
}

void CSDIAppDoc::OnPlaceship()
{
	// TODO: добавьте свой код обработчика команд
	if (m_bIsConnect)
	{
		m_dPlaceShipDlg.DoModal();
		thread th(WaitEnemyPlaceShip, m_Socket, this);
		th.detach();
	}
	else
	{
		MessageBox(NULL, _T("Противник еще не найден!"), _T("Ошибка"), MB_ICONWARNING);
	}
}


void CSDIAppDoc::OnShot()
{
	// TODO: добавьте свой код обработчика команд
	if (!m_bIsConnect)
	{
		MessageBox(NULL, _T("Противник еще не найден!"), _T("Ошибка"), MB_ICONWARNING);
		return;
	}
	if (!m_bIsShipPlace)
	{
		MessageBox(NULL, _T("Вы или Ваш противник не расставил свои корабли"), _T("Ошибка"), MB_ICONWARNING);
		return;
	}
	if (!m_bIsYouMove)
	{
		MessageBox(NULL, _T("Ход противника"), _T("Ошибка"), MB_ICONWARNING);
		return;
	}
	if (!m_bIsReadyShot)
	{
		MessageBox(NULL, _T("Вы не готовы стрелять! Выберите куда хотите выстрелить"), _T("Ошибка"), MB_ICONWARNING);
		return;
	}

	//отправка запроса
	char str[32];
	sprintf(str, "%c%i",
		m_dPlaceShipDlg.CoordToLetter(m_iSelectX),
		m_iSelectY + 1);
	string request = str;
	send(m_Socket, request.c_str(), request.size() + 1, 0);

	//получение ответа
	char buff[1024];
	recv(m_Socket, &buff[0], sizeof(buff), 0);
	string response = buff;

	if (response == "Попадание!")
	{
		m_EnemyAqua[m_iSelectY][m_iSelectX] = CELL_SHOT;
	}
	else if (response == "Мимо(")
	{
		m_EnemyAqua[m_iSelectY][m_iSelectX] = CELL_MISS;
		m_bIsYouMove = false;
	}
	else if (response == "Корабль потоплен!")
	{
		m_EnemyAqua[m_iSelectY][m_iSelectX] = CELL_SHOT;
		if (CheckEndGame())
		{
			send(m_Socket, "OK", 2, 0);
			m_bIsEndGame = true;
		}
	}

	thread th(ChechMove, m_Socket, this);
	th.detach();

	m_iSelectY = m_iSelectX = NULL;
	m_pView->Invalidate(FALSE);
	m_bIsReadyShot = false;
}

void CSDIAppDoc::WaitEnemyConnect(SOCKET mSocket, CSDIAppDoc* pDoc)
{
	// TODO: Добавьте сюда код реализации.
	//ожидание ответа от сервера, что соперник найден и нужно расставлять корабли
	char buf[1024];
	CString string;
	while (recv((SOCKET)mSocket, buf, sizeof(buf), 0))
	{
		string = buf;
		if ((string == "Расставляйте корабли!"))
		{
			if (pDoc->m_dAcceprDlg.DoModal() == IDOK)
			{
				pDoc->m_bIsConnect = true;
			}
			break;
		}
	}
	return;
}

void CSDIAppDoc::WaitEnemyPlaceShip(SOCKET mSocket, CSDIAppDoc* pDoc)
{
	// TODO: Добавьте сюда код реализации.
	if (pDoc->CheckEndGame())
	{
		pDoc->m_bIsEndGame = true;
		return;
	}
	char buf[1024];
	CString string;
	while (recv(mSocket, buf, sizeof(buf), 0))
	{
		string = buf;
		if ((string == "Ваш ход!"))
		{
			MessageBox(NULL, _T("Выберите место куда будете стрелять и нажмите на кнопку, чтобы выстрелить"), _T("Противник расставил корабли"), MB_OK);
			pDoc->m_bIsShipPlace = true;
			pDoc->m_bIsYouMove = true;
			break;
		}
	}
}


// проверяет ответы от сервера на завершение игры (true - завершение игры)
bool CSDIAppDoc::CheckEndGame()
{
	// TODO: Добавьте сюда код реализации.
	if (m_bIsEndGame)
		return true;

	char buf[1024];
	CString string;
	recv(m_Socket, buf, sizeof(buf), MSG_PEEK);
	string = buf;
	if ((string == "Вы выиграли"))
	{
		MessageBox(NULL, _T("ВЫ ВЫИГРАЛИ!!!"), _T("ПОБЕДА!!"), MB_OK);
		return true;
	}
	if ((string == "Вы проиграли("))
	{
		MessageBox(NULL, _T("ВЫ ПРОИГРАЛИ((("), _T("ПОРАЖЕНИЕ"), MB_OK);
		return true;
	}

	if ((string == "Ваш ход!"))
	{
		m_bIsYouMove = true;
		return false;
	}
	return false;

}


void CSDIAppDoc::ChechMove(SOCKET mSocket, CSDIAppDoc* pDoc)
{
	// TODO: Добавьте сюда код реализации.
	if (pDoc->CheckEndGame())
	{
		pDoc->m_bIsEndGame = true;
		return;
	}
	char buf[1024];
	CString string;
	while (recv(mSocket, buf, sizeof(buf), 0))
	{
		string = buf;
		if ((string == "Ваш ход!"))
		{
			MessageBox(NULL, _T("Выберите место куда будете стрелять и нажмите на кнопку, чтобы выстрелить"), _T("Ваш ход"), MB_OK);
			pDoc->m_bIsYouMove = true;
			break;
		}
	}
}


void CSDIAppDoc::OnUpdateBegin(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	if (m_bIsEndGame)
	{
		pCmdUI->Enable(false);
	}
}


void CSDIAppDoc::OnUpdateShot(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	if (m_bIsEndGame)
	{
		pCmdUI->Enable(false);
	}
}


void CSDIAppDoc::OnUpdatePlaceship(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	if (m_bIsEndGame)
	{
		pCmdUI->Enable(false);
	}
}
