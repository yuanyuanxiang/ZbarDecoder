
// ZbarDecoderView.h : CZbarDecoderView ��Ľӿ�
//

#pragma once


class CZbarDecoderView : public CScrollView
{
protected: // �������л�����
	CZbarDecoderView();
	DECLARE_DYNCREATE(CZbarDecoderView)

	CSize m_Size;

	CRect m_Rect;

// ����
public:
	CZbarDecoderDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CZbarDecoderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // ZbarDecoderView.cpp �еĵ��԰汾
inline CZbarDecoderDoc* CZbarDecoderView::GetDocument() const
   { return reinterpret_cast<CZbarDecoderDoc*>(m_pDocument); }
#endif
