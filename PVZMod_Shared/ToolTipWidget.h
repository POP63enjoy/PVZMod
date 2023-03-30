#pragma once
#ifndef _PVZMOD_TOOL_TIP_WIDGET_H_
#define _PVZMOD_TOOL_TIP_WIDGET_H_

#include "SexyCommon.h"

namespace PVZMod
{
	/// 【游戏类】工具提示。（原 ::ToolTipWidget）
	class ToolTipWidget
	{
	public:
		SexyString		mTitle;
		SexyString		mLabel;
		SexyString		mWarningText;
		int				mX;
		int				mY;
		int				mWidth;
		int				mHeight;
		bool			mVisible;
		bool			mCenter;
		int				mMinLeft;
		int				mMaxBottom;
		int				mGetsLinesWidth;
		int				mWarningFlashCounter;

	public:
		ToolTipWidget();
	};
}

#endif // !_PVZMOD_TOOL_TIP_WIDGET_H_
