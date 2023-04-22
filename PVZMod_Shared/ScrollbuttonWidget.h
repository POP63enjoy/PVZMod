#pragma once
#ifndef _PVZMOD_SCROLLBUTTON_WIDGET_H_
#define _PVZMOD_SCROLLBUTTON_WIDGET_H_

#include "ButtonWidget.h"

namespace PVZMod
{
	class ButtonListener;

	/// ����Ϸ�ࡿ��������ť�ؼ�����ԭ `Sexy::ScrollbuttonWidget`��
	class ScrollbuttonWidget : public ButtonWidget
	{
	public:
		bool				mHorizontal;

		// mType is a new way of doing things (1 = up, 2 = down, 3 = left, 4 = right).  
		// This overrides mHorizontal and mId.
		int					mType;

	public:
		ScrollbuttonWidget(int theId, ButtonListener* theButtonListener, int theType = 0);
		virtual ~ScrollbuttonWidget();

		void				Draw(Graphics* g);
	};
}

#endif // !_PVZMOD_SCROLLBUTTON_WIDGET_H_
