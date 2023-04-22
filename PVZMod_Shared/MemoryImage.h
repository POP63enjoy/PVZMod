#pragma once
#ifndef _PVZMOD_MEMORY_IMAGE_H_
#define _PVZMOD_MEMORY_IMAGE_H_

#include "Image.h"

namespace PVZMod
{
	const uint32_t MEMORYCHECK_ID = 0x4BEEFADE;

	class NativeDisplay;
	class SexyAppBase;

	/// 【游戏类】内存贴图。（原 `Sexy::MemoryImage`）
	class MemoryImage : public Image
	{
	public:
		uint32_t*				mBits;
		int						mBitsChangedCount;
		void*					mD3DData;
		DWORD					mD3DFlags;	// see D3DInterface.h for possible values

		uint32_t*				mColorTable;
		uint8_t*				mColorIndices;
	
		bool					mForcedMode;
		bool					mHasTrans;
		bool					mHasAlpha;
		bool					mIsVolatile;
		bool					mPurgeBits;
		bool					mWantPal;
	
		uint32_t*				mNativeAlphaData;
		uint8_t*				mRLAlphaData;
		uint8_t*				mRLAdditiveData;

		bool					mBitsChanged;
		SexyAppBase*			mApp;
	
	private:
		void					Init();

	public:
		virtual void*			GetNativeAlphaData(NativeDisplay *theNative);
		virtual uint8_t*		GetRLAlphaData();
		virtual uint8_t*		GetRLAdditiveData(NativeDisplay *theNative);
		virtual void			PurgeBits();
		virtual void			DeleteSWBuffers();
		virtual void			Delete3DBuffers();	
		virtual void			DeleteExtraBuffers();
		virtual void			ReInit();

		virtual void			BitsChanged();
		virtual void			CommitBits();
	
		virtual void			DeleteNativeData();	

		void					NormalBlt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor);
		void					AdditiveBlt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor);

		void					NormalDrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);
		void					AdditiveDrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);

		void					NormalDrawLineAA(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);
		void					AdditiveDrawLineAA(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor);

		void					SlowStretchBlt(Image* theImage, const Rect& theDestRect, const FRect& theSrcRect, const Color& theColor, int theDrawMode);
		void					FastStretchBlt(Image* theImage, const Rect& theDestRect, const FRect& theSrcRect, const Color& theColor, int theDrawMode);
		bool					BltRotatedClipHelper(float &theX, float &theY, const Rect &theSrcRect, const Rect &theClipRect, double theRot, FRect &theDestRect, float theRotCenterX, float theRotCenterY);
		bool					StretchBltClipHelper(const Rect &theSrcRect, const Rect &theClipRect, const Rect &theDestRect, FRect &theSrcRectOut, Rect &theDestRectOut);
		bool					StretchBltMirrorClipHelper(const Rect &theSrcRect, const Rect &theClipRect, const Rect &theDestRect, FRect &theSrcRectOut, Rect &theDestRectOut);
		void					BltMatrixHelper(Image* theImage, float x, float y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, void *theSurface, int theBytePitch, int thePixelFormat, bool blend);
		void					BltTrianglesTexHelper(Image *theTexture, const TriVertex theVertices[][3], int theNumTriangles, const Rect &theClipRect, const Color &theColor, int theDrawMode, void *theSurface, int theBytePitch, int thePixelFormat, float tx, float ty, bool blend);

		void					FillScanLinesWithCoverage(Span* theSpans, int theSpanCount, const Color& theColor, int theDrawMode, const BYTE* theCoverage, int theCoverX, int theCoverY, int theCoverWidth, int theCoverHeight);


	public:
		MemoryImage() = delete;
		MemoryImage(SexyAppBase* theApp) = delete;
		MemoryImage(const MemoryImage& theMemoryImage) = delete;	
		virtual ~MemoryImage();

		virtual void			Clear();
		virtual void			SetBits(uint32_t* theBits, int theWidth, int theHeight, bool commitBits = true);
		virtual void			Create(int theWidth, int theHeight);
		virtual uint32_t*		GetBits();
	
		virtual void			FillRect(const Rect& theRect, const Color& theColor, int theDrawMode);
		virtual void			ClearRect(const Rect& theRect);
		virtual void			DrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode);
		virtual void			DrawLineAA(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode);

		virtual void			Blt(Image* theImage, int theX, int theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode);
		virtual void			BltF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect &theClipRect, const Color& theColor, int theDrawMode);
		virtual void			BltRotated(Image* theImage, float theX, float theY, const Rect &theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY);
		virtual void			StretchBlt(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect& theClipRect, const Color& theColor, int theDrawMode, bool fastStretch);
		virtual void			BltMatrix(Image* theImage, float x, float y, const SexyMatrix3 &theMatrix, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect &theSrcRect, bool blend);
		virtual void			BltTrianglesTex(Image *theTexture, const TriVertex theVertices[][3], int theNumTriangles, const Rect& theClipRect, const Color &theColor, int theDrawMode, float tx, float ty, bool blend);

		virtual void			SetImageMode(bool hasTrans, bool hasAlpha);
		virtual void			SetVolatile(bool isVolatile);	

		virtual bool			Palletize();
	};
}

#endif // !_PVZMOD_MEMORY_IMAGE_H_
