#pragma once
#ifndef _PVZMOD_COLOR_H_
#define _PVZMOD_COLOR_H_

#include <cstdint>

namespace PVZMod
{
#pragma pack(push,1)
	struct SexyRGBA { unsigned char b, g, r, a; };
#pragma pack(pop)

	/// 【游戏类】颜色。（原 `Sexy::Color`）
	class Color
	{
	public:
		int mRed;
		int mGreen;
		int mBlue;
		int mAlpha;

		static Color Black;
		static Color White;

	public:
		Color();
		Color(int theColor);
		Color(int theColor, int theAlpha);
		Color(int theRed, int theGreen, int theBlue);
		Color(int theRed, int theGreen, int theBlue, int theAlpha);
		Color(const SexyRGBA& theColor);
		Color(const uint8_t* theElements);
		Color(const int* theElements);

		int						GetRed() const;
		int						GetGreen() const;
		int						GetBlue() const;
		int						GetAlpha() const;
		uint32_t				ToInt() const;
		SexyRGBA				ToRGBA() const;

		int&					operator[](int theIdx);
		int						operator[](int theIdx) const;
	};

	bool operator==(const Color& theColor1, const Color& theColor2);
	bool operator!=(const Color& theColor1, const Color& theColor2);
}

#endif // !_PVZMOD_COLOR_H_
