
// ZbarDecoderDoc.h : CZbarDecoderDoc 类的接口
//


#pragma once
#include "..\3DCode\3DCode\CyImage.h"


class CZbarDecoderDoc : public CDocument
{
protected: // 仅从序列化创建
	CZbarDecoderDoc();
	DECLARE_DYNCREATE(CZbarDecoderDoc)

	CyImage *m_pImage;

// 特性
public:
	// 获取图像指针
	CyImage* GetImage() { return m_pImage; }
	// 图像为空
	bool ImageIsNull() const
	{
		return NULL == m_pImage || m_pImage->IsNull();
	}
	// 获取图像尺寸
	CSize GetImageSize() const
	{
		return  ImageIsNull() ? CSize(100, 100) : CSize(m_pImage->GetWidth(), m_pImage->GetHeight());
	}
	// 绘制到DC
	BOOL DrawTo(CDC *pDC, const CRect &rt)
	{
		return ImageIsNull() ? TRUE : m_pImage->Draw(pDC->GetSafeHdc(), rt);
	}

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CZbarDecoderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnDecode();
	afx_msg void OnUpdateDecode(CCmdUI *pCmdUI);
};
