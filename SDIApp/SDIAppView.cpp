
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
	if (m_bShipsDraw)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				CBitmap bitmap;
				if (i % 2 == 0 && j % 2 == 0)
					bitmap.LoadBitmap(IDB_BITMAP_SHIP2);
				else
					bitmap.LoadBitmap(IDB_BITMAP_SEA2);

				CDC memdc;
				memdc.CreateCompatibleDC(pDC);
				CBitmap* oldbmp = memdc.SelectObject(&bitmap);

				BITMAP BitMap;
				bitmap.GetBitmap(&BitMap);
				pDC->BitBlt(paddingWidth + i * (BitMap.bmWidth + 1), paddingHeight + j * (BitMap.bmHeight + 1), BitMap.bmWidth, BitMap.bmHeight, &memdc, 0, 0, SRCCOPY);

				pDC->SelectObject(oldbmp);
			}
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				CBitmap bitmap;
				if (i % 2 == 0 && j % 2 == 0)
					bitmap.LoadBitmap(IDB_BITMAP_BANG2);
				else
					bitmap.LoadBitmap(IDB_BITMAP_SEA2);

				CDC memdc;
				memdc.CreateCompatibleDC(pDC);
				CBitmap* oldbmp = memdc.SelectObject(&bitmap);

				BITMAP BitMap;
				bitmap.GetBitmap(&BitMap);
				pDC->BitBlt(paddingWidth + i * BitMap.bmWidth, paddingHeight + j * BitMap.bmHeight, BitMap.bmWidth, BitMap.bmHeight, &memdc, 0, 0, SRCCOPY);

				pDC->SelectObject(oldbmp);
			}
		}

	}

	//pDC->TextOutW(paddingWidth, paddingHeight, _T("A"));
}


// печать CSDIAppView

BOOL CSDIAppView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CSDIAppView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CSDIAppView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
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
