
// SDIAppView.cpp : реализаци€ класса CSDIAppView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позвол€ет совместно использовать код документа в данным проекте.
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
	// —тандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// создание/уничтожение CSDIAppView

CSDIAppView::CSDIAppView()
{
	// TODO: добавьте код создани€

}

CSDIAppView::~CSDIAppView()
{
}

BOOL CSDIAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменени€
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

	if (m_bShipsDraw)
	{

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				CBitmap bitmap;
				//bitmap.LoadBitmap(IDB_BITMAP1);
				
				if (i % 2 == 0 && j % 2 == 0)
					bitmap.LoadBitmap(IDB_BITMAP_SHIP2);
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
	else
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				CBitmap bitmap;
				if (i % 2 == 0 && j % 2 == 0)
					bitmap.LoadBitmap(IDB_BITMAP_BANG);
				else
					bitmap.LoadBitmap(IDB_BITMAP_SEA);

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

CSDIAppDoc* CSDIAppView::GetDocument() const // встроена неотлаженна€ верси€
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIAppDoc)));
	return (CSDIAppDoc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CSDIAppView
