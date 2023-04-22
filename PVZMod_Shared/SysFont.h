#pragma once
#ifndef _PVZMOD_SYS_FONT_H_
#define _PVZMOD_SYS_FONT_H_

#include "Font.h"

namespace PVZMod
{
	class ImageFont;
	class SexyAppBase;

	/// 【游戏类】系统字体。（原 `Sexy::SysFont`）
	class SysFont : public Font
	{
	public:	
		HFONT					mHFont;
		SexyAppBase*			mApp;
		bool					mDrawShadow;
		bool					mSimulateBold;
	
		void Init(SexyAppBase* theApp, const String& theFace, int thePointSize, int theScript, bool bold, bool italics, bool underline, bool useDevCaps);

	public:
		SysFont(const String& theFace, int thePointSize, bool bold = false, bool italics = false, bool underline = false);
		SysFont(SexyAppBase* theApp, const String& theFace, int thePointSize, int theScript = ANSI_CHARSET, bool bold = false, bool italics = false, bool underline = false);
		SysFont(const SysFont& theSysFont);

		virtual ~SysFont();

		ImageFont*				CreateImageFont();
		virtual int				StringWidth(const SexyString& theString);
		virtual void			DrawString(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect& theClipRect);

		virtual Font*			Duplicate();
	};
}

#endif // !_PVZMOD_SYS_FONT_H_
