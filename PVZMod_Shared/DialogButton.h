#pragma once
#ifndef _PVZMOD_DIALOG_BUTTON_H_
#define _PVZMOD_DIALOG_BUTTON_H_

#include "ButtonWidget.h"

namespace PVZMod
{
	class Image;
	class Graphics;
	class ButtonListener;

	/// 【游戏类】对话框按钮控件。（原 `Sexy::DialogButton`）
	class DialogButton : public ButtonWidget
	{
	public:
		Image*					mComponentImage;
		int						mTranslateX, mTranslateY;
		int						mTextOffsetX, mTextOffsetY;

	public:
		DialogButton(Image* theComponentImage, int theId, ButtonListener* theListener);

		virtual void			Draw(Graphics* g);
	};
}

#endif // !_PVZMOD_DIALOG_BUTTON_H_
