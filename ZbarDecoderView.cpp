
// ZbarDecoderView.cpp : CZbarDecoderView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ZbarDecoder.h"
#endif

#include "ZbarDecoderDoc.h"
#include "ZbarDecoderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CZbarDecoderView

IMPLEMENT_DYNCREATE(CZbarDecoderView, CScrollView)

BEGIN_MESSAGE_MAP(CZbarDecoderView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CZbarDecoderView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CZbarDecoderView 构造/析构

CZbarDecoderView::CZbarDecoderView()
{
	// TODO: 在此处添加构造代码

}

CZbarDecoderView::~CZbarDecoderView()
{
}

BOOL CZbarDecoderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CZbarDecoderView 绘制

void CZbarDecoderView::OnDraw(CDC* pDC)
{
	CZbarDecoderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	pDoc->DrawTo(pDC, m_Rect);
}

void CZbarDecoderView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CZbarDecoderDoc *pDoc = GetDocument();
	m_Size = pDoc->GetImageSize();
	m_Rect = CRect(0, 0, m_Size.cx, m_Size.cy);
	SetScrollSizes(MM_TEXT, m_Size);
}


// CZbarDecoderView 打印


void CZbarDecoderView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CZbarDecoderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CZbarDecoderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CZbarDecoderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CZbarDecoderView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CZbarDecoderView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CZbarDecoderView 诊断

#ifdef _DEBUG
void CZbarDecoderView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CZbarDecoderView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CZbarDecoderDoc* CZbarDecoderView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CZbarDecoderDoc)));
	return (CZbarDecoderDoc*)m_pDocument;
}
#endif //_DEBUG


// CZbarDecoderView 消息处理程序


BOOL CZbarDecoderView::OnEraseBkgnd(CDC* pDC)
{
	CZbarDecoderDoc* pDoc = GetDocument();
	if (!pDoc->ImageIsNull())
	{
		// 1	2	3
		// 4	5	6
		// 7	8	9
		// 其中5代表绘图区域
		CRect rect;
		GetClientRect(&rect);
		CyImage *pImage = pDoc->GetImage();
		pDC->PatBlt(0, 0, m_Rect.left, rect.bottom, PATCOPY);	// 1 4 7
		pDC->PatBlt(0, 0, rect.right, m_Rect.top, PATCOPY);		// 1 2 3
		pDC->PatBlt(m_Rect.right, 0, rect.right - m_Rect.right, rect.bottom, PATCOPY);	// 3 6 9	
		pDC->PatBlt(0, m_Rect.bottom, rect.right, rect.bottom - m_Rect.bottom, PATCOPY);// 7 8 9
		return TRUE;
	}
	return CScrollView::OnEraseBkgnd(pDC);
}
