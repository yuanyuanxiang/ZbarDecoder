#include "stdafx.h"
#include "ZbarCaller.h"
#include "..\3DCode\3DCode\Transform.h"


ZbarCaller::ZbarCaller(void)
{
}


ZbarCaller::~ZbarCaller(void)
{
}


bool ZbarCaller::Decode(BYTE *pSrc, int width, int height, int rowlen, bool bFlip)
{
	if (bFlip)
		ImageFlipV(pSrc, width, height, rowlen);
	Image imageZbar(width, height, "Y800", pSrc, rowlen * height);
	ImageScanner scanner;
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
	scanner.scan(imageZbar); // 扫描条码
	Image::SymbolIterator symbol = imageZbar.symbol_begin();
	bool ret = false;
	for( ; symbol != imageZbar.symbol_end(); ++symbol)
	{
		ret = true;
		char szResult[2048];
		result = symbol->get_data();
		std::string type = symbol->get_type_name();
		sprintf_s(szResult, "条码：%s\n类型：%s \n", result.c_str(), type.c_str());
		OutputDebugStringA(szResult);
	}
	return ret;
}

std::string ZbarCaller::DecodeHard(const CyImage *pImage)
{
	CyImage *pCopy = pImage->MakeCopy();
	pCopy->ToGray();
	int width = pCopy->GetWidth();
	int height = pCopy->GetHeight();
	int rowlen = pCopy->GetRowlen();
	BYTE *pSrc = pCopy->GetHeadAddress();
	result.clear();
	if (!Decode(pSrc, width, height, rowlen, true))
		Decode(pSrc, width, height, rowlen, false);
	SAFE_DELETE(pCopy);
	return result;
}
