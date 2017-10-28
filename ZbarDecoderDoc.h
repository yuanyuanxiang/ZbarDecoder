
// ZbarDecoderDoc.h : CZbarDecoderDoc ��Ľӿ�
//


#pragma once
#include "..\3DCode\3DCode\CyImage.h"


class CZbarDecoderDoc : public CDocument
{
protected: // �������л�����
	CZbarDecoderDoc();
	DECLARE_DYNCREATE(CZbarDecoderDoc)

	CyImage *m_pImage;

// ����
public:
	// ��ȡͼ��ָ��
	CyImage* GetImage() { return m_pImage; }
	// ͼ��Ϊ��
	bool ImageIsNull() const
	{
		return NULL == m_pImage || m_pImage->IsNull();
	}
	// ��ȡͼ��ߴ�
	CSize GetImageSize() const
	{
		return  ImageIsNull() ? CSize(100, 100) : CSize(m_pImage->GetWidth(), m_pImage->GetHeight());
	}
	// ���Ƶ�DC
	BOOL DrawTo(CDC *pDC, const CRect &rt)
	{
		return ImageIsNull() ? TRUE : m_pImage->Draw(pDC->GetSafeHdc(), rt);
	}

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CZbarDecoderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnDecode();
	afx_msg void OnUpdateDecode(CCmdUI *pCmdUI);
};
