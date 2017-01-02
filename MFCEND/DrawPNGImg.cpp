#include "stdafx.h"
#include "DrawPNGImg.h"

vector<PNGsave> PNGImgs;
CImage* getPNGImg(CString path);
void std::drawPNG(CString path, CDC* pDC, float cx, float cy, float w, float h) {
	CImage* Image = getPNGImg(path);
	float drawprop = w / h;

	float imgw = Image->GetWidth();
	float imgh = Image->GetHeight();
	float imgprop = imgw / imgh;

	//调正变形
	if (drawprop > imgprop) {
		w = w / drawprop*imgprop;
	}
	else if (drawprop < imgprop) {
		h = h / imgprop*drawprop;
	}
	Image->Draw(pDC->m_hDC, cx - w / 2, cy - h / 2, w, h, 0, 0, imgw, imgh);
}

void std::drawPNG(CString path, CDC* pDC, CRect rect) {
	float cx, cy, w, h;
	w = rect.Width();
	h = rect.Height();

	CImage* Image = getPNGImg(path);
	if (!Image)return;
	float drawprop = w / h;

	float imgw = Image->GetWidth();
	float imgh = Image->GetHeight();
	float imgprop = imgw / imgh;

	//调正变形
	if (drawprop > imgprop) {
		w = w / drawprop*imgprop;
	}
	else if (drawprop < imgprop) {
		h = h / imgprop*drawprop;
	}
	Image->Draw(pDC->m_hDC, rect.left, rect.top, w, h, 0, 0, imgw, imgh);
}

CImage* getPNGImg(CString path) {
	CImage* Image = NULL;
	for (int i = 0; i < PNGImgs.size(); i++) {
		if (PNGImgs.at(i).path == path) {
			Image = PNGImgs.at(i).PNG;
			break;
		}
	}
	if (Image == NULL) {
		Image = new CImage();
		Image->Load(path);
		if (Image->IsNull())
		{
			return NULL;
		}
		if (Image->GetBPP() == 32) //确认该图像包含Alpha通道
		{
			int i;
			int j;
			for (i = 0; i < Image->GetWidth(); i++)
			{
				for (j = 0; j < Image->GetHeight(); j++)
				{
					byte *pByte = (byte *)Image->GetPixelAddress(i, j);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
		PNGsave ps;
		ps.path = path;
		ps.PNG = Image;
		PNGImgs.push_back(ps);
	}
	return Image;
}