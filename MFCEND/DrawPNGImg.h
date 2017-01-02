#pragma once
struct PNGsave
{
	CImage * PNG;
	CString path;
};

namespace std {

	void drawPNG(CString path, CDC* pDC, float x, float y, float w, float h);
	void drawPNG(CString path, CDC* pDC, CRect rect);
}

