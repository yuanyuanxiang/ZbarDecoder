
// ZbarDecoderView.cpp : CZbarDecoderView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CZbarDecoderView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CZbarDecoderView ����/����

CZbarDecoderView::CZbarDecoderView()
{
	// TODO: �ڴ˴���ӹ������

}

CZbarDecoderView::~CZbarDecoderView()
{
}

BOOL CZbarDecoderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CZbarDecoderView ����

void CZbarDecoderView::OnDraw(CDC* pDC)
{
	CZbarDecoderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CZbarDecoderView ��ӡ


void CZbarDecoderView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CZbarDecoderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CZbarDecoderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CZbarDecoderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CZbarDecoderView ���

#ifdef _DEBUG
void CZbarDecoderView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CZbarDecoderView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CZbarDecoderDoc* CZbarDecoderView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CZbarDecoderDoc)));
	return (CZbarDecoderDoc*)m_pDocument;
}
#endif //_DEBUG


// CZbarDecoderView ��Ϣ�������


BOOL CZbarDecoderView::OnEraseBkgnd(CDC* pDC)
{
	CZbarDecoderDoc* pDoc = GetDocument();
	if (!pDoc->ImageIsNull())
	{
		// 1	2	3
		// 4	5	6
		// 7	8	9
		// ����5�����ͼ����
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
