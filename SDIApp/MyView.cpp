// MyView.cpp: файл реализации
//

#include "stdafx.h"
#include "SDIApp.h"
#include "MyView.h"
#include "SDIAppDoc.h"


// CMyView

IMPLEMENT_DYNCREATE(CMyView, CTreeView)

CMyView::CMyView()
{

}

CMyView::~CMyView()
{
}

BEGIN_MESSAGE_MAP(CMyView, CTreeView)
	ON_WM_CREATE()
//	ON_WM_LBUTTONDOWN()
ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CMyView::OnTvnSelchanged)
END_MESSAGE_MAP()


// диагностика CMyView

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// обработчики сообщений CMyView

void CMyView::UpdateTree()
{
	CTreeCtrl &tree = GetTreeCtrl();

	tree.DeleteAllItems();

	m_hViews = tree.InsertItem(L"Виды", -1, -1, NULL, TVI_FIRST);

	m_hShip = tree.InsertItem(L"Расстановка", -1, -1, m_hViews, TVI_LAST);
	m_hEnemy = tree.InsertItem(L"Стрелялка", -1, -1, m_hViews, TVI_LAST);

	tree.Expand(m_hViews, TVE_EXPAND);

	tree.SetItemData(m_hShip, IS_DRAW_SHIP);
	tree.SetItemData(m_hEnemy, IS_DRAW_ENEMY);
}


int CMyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_SHOWSELALWAYS;

	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания


	return 0;
}



void CMyView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений
	CTreeCtrl& tree = GetTreeCtrl();
	HTREEITEM sel = tree.GetSelectedItem();
	int i = tree.GetItemData(sel);

	if (tree.GetItemData(sel) == IS_DRAW_SHIP)
	{
		pDoc->m_pView->m_bShipsDraw = IS_DRAW_SHIP;
	}
	else if (tree.GetItemData(sel) == IS_DRAW_ENEMY)
	{
		pDoc->m_pView->m_bShipsDraw = IS_DRAW_ENEMY;
	}
	
	pDoc->m_pView->Invalidate(FALSE);
	*pResult = 0;
}
