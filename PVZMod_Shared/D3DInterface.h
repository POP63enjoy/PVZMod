#pragma once
#ifndef _PVZMOD_D3DINTERFACE_H_
#define _PVZMOD_D3DINTERFACE_H_

#include "SexyCommon.h"
#include "MemoryImage.h"
#include "SexyMatrix.h"
#include <d3d.h>

namespace PVZMod
{
	class DDInterface;

	enum PixelFormat
	{
		PixelFormat_Unknown		= 0x0000,
		PixelFormat_A8R8G8B8	= 0x0001,
		PixelFormat_A4R4G4B4	= 0x0002,
		PixelFormat_R5G6B5		= 0x0004,
		PixelFormat_Palette8	= 0x0008,
	};

	/// 【游戏类】Direct3D 接口。（原 Sexy::D3DInterface）
	class D3DInterface
	{
	public:
		HWND					mHWnd;
		int						mWidth;
		int						mHeight;

		LPDIRECTDRAW7			mDD;
		LPDIRECTDRAWSURFACE7	mDDSDrawSurface;
		LPDIRECTDRAWSURFACE7	mZBuffer;
		LPDIRECT3D7				mD3D;
		LPDIRECT3DDEVICE7		mD3DDevice;
		D3DVIEWPORT7			mD3DViewport;

		bool					mSceneBegun;
		bool					mIsWindowed;

		typedef Set<MemoryImage*> ImageSet;
		ImageSet mImageSet;

		typedef List<SexyMatrix3> TransformStack;
		TransformStack mTransformStack;

		//static std::string mErrorString;

	protected:
		void					UpdateViewport();
		bool					InitD3D();
		void					SetupDrawMode(int theDrawMode, const Color& theColor, Image* theImage);
		static HRESULT CALLBACK PixelFormatsCallback(LPDDPIXELFORMAT theFormat, LPVOID lpContext);

	public:
		D3DInterface();
		virtual ~D3DInterface();

		void					Cleanup();
		void					PushTransform(const SexyMatrix3& theTransform, bool concatenate = true);
		void					PopTransform();

		bool					PreDraw();
		void					Flush();
		void					RemoveMemoryImage(MemoryImage* theImage);

		bool					CreateImageTexture(MemoryImage* theImage);
		bool					RecoverBits(MemoryImage* theImage);
		void					SetCurTexture(MemoryImage* theImage);
		void					Blt(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode, bool linearFilter = false);
		void					BltClipF(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Rect* theClipRect, const Color& theColor, int theDrawMode);
		void					BltMirror(Image* theImage, float theX, float theY, const Rect& theSrcRect, const Color& theColor, int theDrawMode, bool linearFilter = false);
		void					StretchBlt(Image* theImage, const Rect& theDestRect, const Rect& theSrcRect, const Rect* theClipRect, const Color& theColor, int theDrawMode, bool fastStretch, bool mirror = false);
		void					BltRotated(Image* theImage, float theX, float theY, const Rect* theClipRect, const Color& theColor, int theDrawMode, double theRot, float theRotCenterX, float theRotCenterY, const Rect& theSrcRect);
		void					BltTransformed(Image* theImage, const Rect* theClipRect, const Color& theColor, int theDrawMode, const Rect& theSrcRect, const SexyMatrix3& theTransform, bool linearFilter, float theX = 0, float theY = 0, bool center = false);
		void					DrawLine(double theStartX, double theStartY, double theEndX, double theEndY, const Color& theColor, int theDrawMode);
		void					FillRect(const Rect& theRect, const Color& theColor, int theDrawMode);
		void					DrawTriangle(const TriVertex& p1, const TriVertex& p2, const TriVertex& p3, const Color& theColor, int theDrawMode);
		void					DrawTriangleTex(const TriVertex& p1, const TriVertex& p2, const TriVertex& p3, const Color& theColor, int theDrawMode, Image* theTexture, bool blend = true);
		void					DrawTrianglesTex(const TriVertex theVertices[][3], int theNumTriangles, const Color& theColor, int theDrawMode, Image* theTexture, float tx = 0, float ty = 0, bool blend = true);
		void					DrawTrianglesTexStrip(const TriVertex theVertices[], int theNumTriangles, const Color& theColor, int theDrawMode, Image* theTexture, float tx = 0, float ty = 0, bool blend = true);
		void					FillPoly(const Point theVertices[], int theNumVertices, const Rect* theClipRect, const Color& theColor, int theDrawMode, int tx, int ty);

		bool					InitFromDDInterface(DDInterface* theInterface);

		static void				MakeDDPixelFormat(PixelFormat theFormatType, DDPIXELFORMAT* theFormat);
		static PixelFormat		GetDDPixelFormat(LPDDPIXELFORMAT theFormat);
		static bool				CheckDXError(HRESULT theError, const char* theMsg = "");
	};
}

#endif // !_PVZMOD_D3DINTERFACE_H_
