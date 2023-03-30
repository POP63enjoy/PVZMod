#pragma once
#ifndef _PVZMOD_DDINTERFACE_H_
#define _PVZMOD_DDINTERFACE_H_

#include "NativeDisplay.h"
#include <ddraw.h>
#include "CritSect.h"
#include "Ratio.h"
#include "Rect.h"
#include "SexyCommon.h"

namespace PVZMod
{
	class SexyAppBase;
	class D3DInterface;
	class D3DTester;
	class DDImage;
	class Image;
	class MemoryImage;

	typedef Set<DDImage*> DDImageSet;

	/// 【游戏类】DirectDraw 接口。（原 Sexy::DDInterface）
	class DDInterface : public NativeDisplay
	{
	public:
		enum
		{
			RESULT_OK = 0,
			RESULT_FAIL = 1,
			RESULT_DD_CREATE_FAIL = 2,
			RESULT_SURFACE_FAIL = 3,
			RESULT_EXCLUSIVE_FAIL = 4,
			RESULT_DISPCHANGE_FAIL = 5,
			RESULT_INVALID_COLORDEPTH = 6,
			RESULT_3D_FAIL = 7
		};

		SexyAppBase* mApp;
		D3DInterface* mD3DInterface;
		D3DTester* mD3DTester;
		bool					mIs3D;

		CritSect				mCritSect;
		bool					mInRedraw;
		LPDIRECTDRAW			mDD;
		LPDIRECTDRAW7			mDD7;
		LPDIRECTDRAWSURFACE		mPrimarySurface;
		LPDIRECTDRAWSURFACE		mSecondarySurface;
		LPDIRECTDRAWSURFACE		mDrawSurface;
		LPDIRECTDRAWSURFACE		mWindowScaleBuffers[4];
		int						mWidth;
		int						mHeight;
		Ratio					mAspect;
		int						mDesktopWidth;
		int						mDesktopHeight;
		Ratio					mDesktopAspect;
		bool					mIsWidescreen;
		int						mDisplayWidth;
		int						mDisplayHeight;
		Ratio					mDisplayAspect;

		Rect					mPresentationRect;
		int						mFullscreenBits;
		DWORD					mRefreshRate;
		DWORD					mMillisecondsPerFrame;
		int						mScanLineFailCount;

		int* mRedAddTable;
		int* mGreenAddTable;
		int* mBlueAddTable;

		uint32_t				mRedConvTable[256];
		uint32_t				mGreenConvTable[256];
		uint32_t				mBlueConvTable[256];

		bool					mInitialized;
		HWND					mHWnd;
		bool					mIsWindowed;
		DDImage*				mScreenImage;
		DDImage*				mSecondarySurfaceImage;
		DDImageSet				mDDImageSet;
		bool					mVideoOnlyDraw;
		uint32_t				mInitCount;

		int						mCursorWidth;
		int						mCursorHeight;
		int						mNextCursorX;
		int						mNextCursorY;
		int						mCursorX;
		int						mCursorY;
		Image* mCursorImage;
		bool					mHasOldCursorArea;
		LPDIRECTDRAWSURFACE		mOldCursorArea;
		LPDIRECTDRAWSURFACE		mNewCursorArea;
		DDImage* mOldCursorAreaImage;
		DDImage* mNewCursorAreaImage;

		String				mErrorString;

	public:
		bool					CopyBitmap(LPDIRECTDRAWSURFACE theSurface, HBITMAP TheBitmap, int theX, int theY, int theWidth, int theHeight);
		uint32_t				GetColorRef(uint32_t theRGB);
		void					AddDDImage(DDImage* theDDImage);
		void					RemoveDDImage(DDImage* theDDImage);
		void					Remove3DData(MemoryImage* theImage); // for 3d texture cleanup

		void					Cleanup();
		bool					GotDXError(HRESULT theResult, const char* theContext = "");

		void					RestoreOldCursorAreaFrom(LPDIRECTDRAWSURFACE theSurface, bool adjust);
		void					DrawCursorTo(LPDIRECTDRAWSURFACE theSurface, bool adjust);
		void					MoveCursorTo(LPDIRECTDRAWSURFACE theSurface, bool adjust, int theNewCursorX, int theNewCursorY);

		HRESULT					CreateSurface(DDSURFACEDESC2* theDesc, LPDIRECTDRAWSURFACE* theSurface, void*);
		void					ClearSurface(LPDIRECTDRAWSURFACE theSurface);
		bool					Do3DTest(HWND theHWND);

	public:
		DDInterface(SexyAppBase* theApp);
		virtual ~DDInterface();

		static String		ResultToString(int theResult);

		DDImage* GetScreenImage();
		int						Init(HWND theWindow, bool IsWindowed);
		bool					Redraw(Rect* theClipRect = NULL);
		void					SetVideoOnlyDraw(bool videoOnly);
		void					RemapMouse(int& theX, int& theY);

		bool					SetCursorImage(Image* theImage);
		void					SetCursorPos(int theCursorX, int theCursorY);
	};
	static_assert(sizeof(DDInterface) == 0xD50);
}

#endif // !_PVZMOD_DDINTERFACE_H_
