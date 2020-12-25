
// SDIAppView.cpp : реализация класса CSDIAppView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SDIApp.h"
#endif

#include "SDIAppDoc.h"
#include "SDIAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDIAppView

IMPLEMENT_DYNCREATE(CSDIAppView, CView)

BEGIN_MESSAGE_MAP(CSDIAppView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// создание/уничтожение CSDIAppView

CSDIAppView::CSDIAppView()
{
	// TODO: добавьте код создания
}

CSDIAppView::~CSDIAppView()
{
}

BOOL CSDIAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

// рисование CSDIAppView

void CSDIAppView::OnDraw(CDC* pDC)
{
	CSDIAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	int pictSize = 48;
	int paddingHeight, paddingWidth;
	GetClientRect(rect);

	paddingHeight = (rect.Height() - pictSize * 10) / 2;
	paddingWidth = (rect.Width() - pictSize * 10) / 2;

	//вывод текста
	CFont font;
	font.CreateFontW(pictSize, 0, 0, 0, true, false, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
	CString str;
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->SelectObject(font);
	pDC->SetTextAlign(TA_RIGHT);
	for (int i = 1; i <= 10; i++)
	{
		//цифры
		str.Empty();
		str.AppendFormat(_T("%i"), i);
		pDC->TextOutW(paddingWidth, paddingHeight + (pictSize + 1) * (i - 1), str);

		//вывод букв
		str.Empty();
		switch (i)
		{
		case 1:
			str = "A";
			break;
		case 2:
			str = "B";
			break;
		case 3:
			str = "C";
			break;
		case 4:
			str = "D";
			break;
		case 5:
			str = "E";
			break;
		case 6:
			str = "F";
			break;
		case 7:
			str = "G";
			break;
		case 8:
			str = "H";
			break;
		case 9:
			str = "I";
			break;
		case 10:
			str = "J";
			break;
		}
		pDC->TextOutW(paddingWidth + 40 + (pictSize + 1) * (i - 1), paddingHeight - pictSize, str);
	}

	//вывод изображений
	if (m_bShipsDraw == IS_DRAW_SHIP)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				CBitmap bitmap;
				if (pDoc->m_MyAqua[i][j] == CELL_SHIP)
					bitmap.LoadBitmap(IDB_BITMAP_SHIP);
				else if (pDoc->m_MyAqua[i][j] == CELL_EMPTY)
					bitmap.LoadBitmap(IDB_BITMAP_SEA);
				else if (pDoc->m_MyAqua[i][j] == CELL_MISS)
					bitmap.LoadBitmap(IDB_BITMAP_MISS);
				else if (pDoc->m_MyAqua[i][j] == CELL_SHOT)
					bitmap.LoadBitmap(IDB_BITMAP_BANG);

				CDC memdc;
				memdc.CreateCompatibleDC(pDC);
				CBitmap* oldbmp = memdc.SelectObject(&bitmap);

				BITMAP BitMap;
				bitmap.GetBitmap(&BitMap);
				pDC->BitBlt(paddingWidth + j * (BitMap.bmWidth + 1), paddingHeight + i * (BitMap.bmHeight + 1), BitMap.bmWidth, BitMap.bmHeight, &memdc, 0, 0, SRCCOPY);

				pDC->SelectObject(oldbmp);
			}
		}
	}
	else if (m_bShipsDraw == IS_DRAW_ENEMY)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				CBitmap bitmap;
				if (pDoc->m_EnemyAqua[i][j] == CELL_EMPTY)
					bitmap.LoadBitmap(IDB_BITMAP_SEA);
				else if (pDoc->m_EnemyAqua[i][j] == CELL_MISS)
					bitmap.LoadBitmap(IDB_BITMAP_MISS);
				else if (pDoc->m_EnemyAqua[i][j] == CELL_SHOT)
					bitmap.LoadBitmap(IDB_BITMAP_BANG);
				else if (pDoc->m_EnemyAqua[i][j] == CELL_SELECTED)
					bitmap.LoadBitmap(IDB_BITMAP_SELECTED);

				CDC memdc;
				memdc.CreateCompatibleDC(pDC);
				CBitmap* oldbmp = memdc.SelectObject(&bitmap);

				BITMAP BitMap;
				bitmap.GetBitmap(&BitMap);
				pDC->BitBlt(paddingWidth + j * (BitMap.bmWidth + 1), paddingHeight + i * (BitMap.bmHeight + 1), BitMap.bmWidth, BitMap.bmHeight, &memdc, 0, 0, SRCCOPY);
				pDC->SelectObject(oldbmp);
			}
		}

	}
}

// диагностика CSDIAppView

#ifdef _DEBUG
void CSDIAppView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIAppDoc* CSDIAppView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIAppDoc)));
	return (CSDIAppDoc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CSDIAppView


void CSDIAppView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CSDIAppDoc* pDoc = GetDocument();
	//проверка что игрок подключен и готов играть
	if (!pDoc->m_bIsConnect || !pDoc->m_bIsShipPlace || !pDoc->m_bIsYouMove)
		return;

	if (m_bShipsDraw == IS_DRAW_SHIP)
	{
		MessageBox(L"В СВОЁ ПОЛЕ НЕЛЬЗЯ СТРЕЛЯТЬ!!!");
		return;
	}

	//получим размер клеток, чтобы узнать в какую клетку нажал рользователь
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP_SHIP);
	BITMAP BitMap;
	bitmap.GetBitmap(&BitMap);

	int cellSize = BitMap.bmWidth; //размер клетки в пикселях
	int aquaSize = BitMap.bmWidth * 10 + 9; //размер поля акватории в пикселях (+ отступы)
	CRect rect;
	GetClientRect(rect);

	int paddingHeight = (rect.Height() - cellSize * 10) / 2; //отступы по вертикали
	int paddingWidth = (rect.Width() - cellSize * 10) / 2; //отступы по горизонтали

	//проверка, что пользователь кликнул не в поле
	if ((point.x - paddingWidth) < 0 || (point.x - paddingWidth) > aquaSize || (point.y - paddingHeight) < 0 || (point.y - paddingHeight) > aquaSize)
		return;

	//определение клетки, на которую пользователь кликнул
	int letter = (point.x - paddingWidth) / (cellSize + 1);
	int num = (point.y - paddingHeight) / (cellSize + 1);

	//если уже была выбрана клетка, то убираем старую выбранную клетку
	if (pDoc->m_bIsReadyShot)
	{
		if (pDoc->m_EnemyAqua[num][letter] == CELL_EMPTY)
		{
			pDoc->m_EnemyAqua[pDoc->m_iSelectY][pDoc->m_iSelectX] = CELL_EMPTY;
			pDoc->m_iSelectY = num;
			pDoc->m_iSelectX = letter;
			pDoc->m_EnemyAqua[pDoc->m_iSelectY][pDoc->m_iSelectX] = CELL_SELECTED;
		}
	}
	else if (pDoc->m_EnemyAqua[num][letter] == CELL_EMPTY)
	{
		pDoc->m_EnemyAqua[num][letter] = CELL_SELECTED;
		pDoc->m_iSelectY = num;
		pDoc->m_iSelectX = letter;
	}
	else
		return;



	Invalidate(FALSE);
	pDoc->m_bIsReadyShot = true;
	CView::OnLButtonDblClk(nFlags, point);
}
