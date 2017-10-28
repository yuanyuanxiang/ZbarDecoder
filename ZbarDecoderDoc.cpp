
// ZbarDecoderDoc.cpp : CZbarDecoderDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CZbarDecoderDoc ����/����

CZbarDecoderDoc::CZbarDecoderDoc()
{
	// TODO: �ڴ����һ���Թ������
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

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CZbarDecoderDoc ���л�

void CZbarDecoderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CZbarDecoderDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CZbarDecoderDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CZbarDecoderDoc ���

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


// CZbarDecoderDoc ����


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
