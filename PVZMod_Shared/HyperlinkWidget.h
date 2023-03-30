#pragma once
#ifndef _PVZMOD_HYPERLINK_WIDGET_H_
#define _PVZMOD_HYPERLINK_WIDGET_H_

#include "ButtonWidget.h"

namespace PVZMod
{
	/// 【游戏类】超链接控件。（原 Sexy::HyperlinkWidget）
	class HyperlinkWidget : public ButtonWidget
	{
	public:
		Color					mColor;
		Color					mOverColor;
		int						mUnderlineSize;
		int						mUnderlineOffset;

	public:
		HyperlinkWidget(int theId, ButtonListener* theButtonListener);

		void					Draw(Graphics* g);
		void					MouseEnter();
		void					MouseLeave();
	};
}

#endif // !_PVZMOD_HYPERLINK_WIDGET_H_
