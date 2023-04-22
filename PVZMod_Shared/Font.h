#pragma once
#ifndef _PVZMOD_FONT_H_
#define _PVZMOD_FONT_H_

#include "SexyCommon.h"
#include "Rect.h"
#include "Color.h"

namespace PVZMod
{
	class Graphics;

	/// 【游戏类】字体基本接口。（原 `Sexy::Font`）
	class Font
	{
	public:
		int						mAscent;
		int						mAscentPadding; // How much space is above the avg uppercase char
		int						mHeight;
		int						mLineSpacingOffset; // This plus height should get added between lines

	public:
		Font();
		Font(const Font& theFont);
		virtual ~Font();

		virtual int				GetAscent();
		virtual int				GetAscentPadding();
		virtual int				GetDescent();
		virtual int				GetHeight();
		virtual int				GetLineSpacingOffset();
		virtual int				GetLineSpacing();
		virtual int				StringWidth(const SexyString& theString);
		virtual int				CharWidth(SexyChar theChar);
		virtual int				CharWidthKern(SexyChar theChar, SexyChar thePrevChar);

		virtual void			DrawString(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect& theClipRect);

		virtual Font*			Duplicate() = 0;
	};
}

#endif // !_PVZMOD_FONT_H_
