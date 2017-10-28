
// ZbarDecoderDoc.cpp : CZbarDecoderDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ZbarDecoder.h"
#endif

#include "ZbarDecoderDoc.h"
#include <propkey.h>
#include "ZbarCaller.h"
#include "..\3DCode\3DCode\CodeTransform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CZbarDecoderDoc

IMPLEMENT_DYNCREATE(CZbarDecoderDoc, CDocument)

BEGIN_MESSAGE_MAP(CZbarDecoderDoc, CDocument)
	ON_COMMAND(ID_DECODE, &CZbarDecoderDoc::OnDecode)
	ON_UPDATE_COMMAND_UI(ID_DECODE, &CZbarDecoderDoc::OnUpdateDecode)
END_MESSAGE_MAP()


// CZbarDecoderDoc 构造/析构

CZbarDecoderDoc::CZbarDecoderDoc()
{
	// TODO: 在此添加一次性构造代码
	m_pImage = NULL;
}

CZbarDecoderDoc::~CZbarDecoderDoc()
{
	SAFE_DELETE(m_pImage);
}

BOOL CZbarDecoderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CZbarDecoderDoc 序列化

void CZbarDecoderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CZbarDecoderDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CZbarDecoderDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CZbarDecoderDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CZbarDecoderDoc 诊断

#ifdef _DEBUG
void CZbarDecoderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CZbarDecoderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CZbarDecoderDoc 命令


BOOL CZbarDecoderDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	SAFE_DELETE(m_pImage);
	m_pImage = new CyImage();
	BOOL bRet = S_OK == m_pImage->Load(lpszPathName);
	return bRet;
}


BOOL CZbarDecoderDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	BOOL bRet = S_OK == m_pImage->Save(lpszPathName);

	return bRet;
}


void CZbarDecoderDoc::OnDecode()
{
	ZbarCaller caller;
	BeginWaitCursor();
	std::string result = caller.DecodeHard(m_pImage);
	EndWaitCursor();
	if (!result.empty())
	{
		AfxMessageBox(CString(result.c_str()), MB_OK | MB_ICONINFORMATION);
	}
}


void CZbarDecoderDoc::OnUpdateDecode(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!ImageIsNull());
}
