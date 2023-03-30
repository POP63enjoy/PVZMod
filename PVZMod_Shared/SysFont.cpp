#include "SysFont.h"
#include "DDImage.h"
#include "SexyAppBase.h"
#include "Graphics.h"
//#include "ImageFont.h"
#include "MemoryImage.h"
#include "DDInterface.h"
#include "D3DInterface.h"
#include "WidgetManager.h"
#include <stdlib.h>

using namespace PVZMod;

SysFont::SysFont(const String& theFace, int thePointSize, bool bold, bool italics, bool underline)
{
	Init(gSexyAppBase, theFace, thePointSize, ANSI_CHARSET, bold, italics, underline, false);
}

SysFont::SysFont(SexyAppBase* theApp, const String& theFace, int thePointSize, int theScript, bool bold, bool italics, bool underline)
{
	Init(theApp, theFace, thePointSize, theScript, bold, italics, underline, true);
}

void SysFont::Init(SexyAppBase* theApp, const String& theFace, int thePointSize, int theScript, bool bold, bool italics, bool underline, bool useDevCaps)
{
	mApp = theApp;

	HDC aDC = ::GetDC(mApp->mHWnd);

	int aHeight = -MulDiv(thePointSize, useDevCaps ? GetDeviceCaps(aDC, LOGPIXELSY) : 96, 72);

	mHFont = CreateFontA(aHeight, 0, 0, 0, bold ? FW_BOLD : FW_NORMAL, italics, underline,
		false, theScript, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, theFace.c_str());

	TEXTMETRIC aTextMetric;
	HFONT anOldFont = (HFONT)SelectObject(aDC, mHFont);
	GetTextMetrics(aDC, &aTextMetric);
	SelectObject(aDC, anOldFont);
	ReleaseDC(mApp->mHWnd, aDC);

	mHeight = aTextMetric.tmHeight;
	mAscent = aTextMetric.tmAscent;

	mDrawShadow = false;
	mSimulateBold = false;
}

SysFont::SysFont(const SysFont& theSysFont)
{
	LOGFONT aLogFont;

	GetObject(theSysFont.mHFont, sizeof(LOGFONT), &aLogFont);
	mHFont = CreateFontIndirect(&aLogFont);
	mApp = theSysFont.mApp;
	mHeight = theSysFont.mHeight;
	mAscent = theSysFont.mAscent;

	mDrawShadow = false;
	mSimulateBold = false;
}

SysFont::~SysFont()
{
	DeleteObject(mHFont);
}

/*ImageFont* SysFont::CreateImageFont()
{
	int i;
	MemoryImage* anImage;
	int anImageCharWidth, anImageXOff, anImageYOff;

	////////////////////////////////////////////////////
	// Step 1: Create image 
	anImageCharWidth = CharWidth('W') * 2;
	anImageXOff = anImageCharWidth / 4;
	anImageYOff = mHeight / 2;
	int aWidth = 257 * anImageCharWidth;
	int aHeight = mHeight * 2;

	BITMAPINFO aBitmapInfo;
	memset(&aBitmapInfo, 0, sizeof(aBitmapInfo));
	BITMAPINFOHEADER& aHeader = aBitmapInfo.bmiHeader;
	aHeader.biSize = sizeof(aHeader);
	aHeader.biWidth = aWidth;
	aHeader.biHeight = -aHeight;
	aHeader.biPlanes = 1;
	aHeader.biBitCount = 32;
	aHeader.biCompression = BI_RGB;

	HDC aDC = CreateCompatibleDC(NULL);

	DWORD* aBits = NULL;
	HBITMAP aBitmap = CreateDIBSection(aDC, &aBitmapInfo, DIB_RGB_COLORS, (void**)&aBits, NULL, 0);

	HBITMAP anOldBitmap = (HBITMAP)SelectObject(aDC, aBitmap);
	HFONT anOldFont = (HFONT)SelectObject(aDC, mHFont);

	HBRUSH anOldBrush = (HBRUSH)SelectObject(aDC, GetStockObject(BLACK_BRUSH));
	Rectangle(aDC, 0, 0, aWidth, aHeight);

	SetBkMode(aDC, TRANSPARENT);
	SetTextColor(aDC, RGB(255, 255, 255));

	int xpos = anImageXOff;
	int ypos = anImageYOff;
	for (i = 0; i < 256; i++)
	{
		char aChar = i;
		TextOutA(aDC, xpos, ypos, &aChar, 1);
		xpos += anImageCharWidth;
	}
	GdiFlush();


	SelectObject(aDC, anOldBrush);
	SelectObject(aDC, anOldBitmap);
	SelectObject(aDC, anOldFont);

	int aSize = aWidth * aHeight;
	anImage = new MemoryImage(mApp);
	anImage->Create(aWidth, aHeight);
	DWORD* src = aBits;
	DWORD* dst = anImage->GetBits();
	for (i = 0; i < aSize; i++)
	{
		DWORD anAlpha = ((*src++) & 0xff) << 24;
		*dst++ = anAlpha | 0xFFFFFF;
	}
	anImage->BitsChanged();
	DeleteObject(aBitmap);


	////////////////////////////////////////////////////
	// Step 2: Create image font

	ImageFont* aFont = new ImageFont(anImage);
	FontLayer* aFontLayer = &aFont->mFontData->mFontLayerList.back();

	aFontLayer->mAscent = mAscent;
	aFontLayer->mHeight = mHeight;

	for (i = 0; i < 256; i++)
	{
		char aChar = i;

		aFontLayer->mCharData[(uchar)aChar].mImageRect = Rect(aChar * anImageCharWidth, 0, anImageCharWidth, anImage->mHeight);
		aFontLayer->mCharData[(uchar)aChar].mWidth = CharWidth(aChar);
		aFontLayer->mCharData[(uchar)aChar].mOffset = Point(-anImageXOff, -anImageYOff);
	}

	aFont->GenerateActiveFontLayers();
	aFont->mActiveListValid = true;

	return aFont;
}*/

int	SysFont::StringWidth(const SexyString& theString)
{
	int result;
	int func = 0x59ff80;
	__asm
	{
		push theString
		mov ecx, this
		call func
		mov result, eax
	}
	return result;
}

void SysFont::DrawString(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect& theClipRect)
{
	int func = 0x5a0040;
	__asm
	{
		push theClipRect
		push theColor
		push theString
		push theY
		push theX
		push g
		mov ecx, this
		call func
	}
}

Font* SysFont::Duplicate()
{
	return new SysFont(*this);
}
