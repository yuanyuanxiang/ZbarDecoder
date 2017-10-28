#pragma once

// Image
#include "../3DCode/3DCode/CyImage.h"

// ZBar
#include "ZBar/include/zbar.h"
#pragma comment(lib, "ZBar/lib/libzbar-0.lib")
using namespace zbar;

/**
* @class ZbarCaller
* @brief Zbar调用者
*/
class ZbarCaller
{
private:
	std::string result;
	bool Decode(BYTE *pSrc, int width, int height, int rowlen, bool bFlip);
public:
	ZbarCaller(void);
	~ZbarCaller(void);
	// 解析二维码图像
	std::string DecodeHard(const CyImage *pImage);
};
