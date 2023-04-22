#pragma once
#ifndef _PVZMOD_SCROLLBAR_WIDGET_H_
#define _PVZMOD_SCROLLBAR_WIDGET_H_

#include "Widget.h"
#include "ButtonListener.h"

namespace PVZMod
{
	class ScrollListener;
	class ScrollbuttonWidget;

	/// ����Ϸ�ࡿ�������ؼ�����ԭ `Sexy::ScrollbarWidget`��
	class ScrollbarWidget : public Widget, public ButtonListener
	{
	public:

		enum
		{
			UPDATE_MODE_IDLE = 0,
			UPDATE_MODE_PGUP,
			UPDATE_MODE_PGDN
		};

	public:

		ScrollbuttonWidget* mUpButton;
		ScrollbuttonWidget* mDownButton;

		bool					mInvisIfNoScroll;

	public:

		int						mId;

		double					mValue;
		double					mMaxValue;
		double					mPageSize;
		bool					mHorizontal;

		bool					mPressedOnThumb;
		int						mMouseDownThumbPos;
		int						mMouseDownX;
		int						mMouseDownY;

		int						mUpdateMode;
		int						mUpdateAcc;
		int						mButtonAcc;
		int						mLastMouseX;
		int						mLastMouseY;
		ScrollListener* mScrollListener;

	public:
		ScrollbarWidget(int theId, ScrollListener* theScrollListener);
		virtual ~ScrollbarWidget();

		virtual void			SetInvisIfNoScroll(bool invisIfNoScroll);
		virtual void			SetMaxValue(double theNewMaxValue);
		virtual void			SetPageSize(double theNewPageSize);
		virtual void			SetValue(double theNewValue);
		virtual void			SetHorizontal(bool isHorizontal);

		virtual void			ResizeScrollbar(int theX, int theY, int theWidth, int theHeight);
		virtual bool			AtBottom();
		virtual void			GoToBottom();
		virtual void			DrawThumb(Graphics* g, int theX, int theY, int theWidth, int theHeight);
		virtual int				GetTrackSize();
		virtual int				GetThumbSize();
		virtual int				GetThumbPosition();
		virtual void			Draw(Graphics* g);
		virtual void			ClampValue();
		virtual void			SetThumbPosition(int thePosition);
		virtual void			ButtonPress(int theId);
		virtual void			ButtonDepress(int theId);
		virtual void			ButtonDownTick(int theId);
		virtual void			Update();
		virtual int				ThumbCompare(int x, int y);
		virtual void			MouseDown(int x, int y, int theClickCount) { Widget::MouseDown(x, y, theClickCount); }
		virtual void			MouseDown(int x, int y, int theBtnNum, int theClickCount);
		virtual void			MouseUp(int x, int y) { Widget::MouseUp(x, y); }
		virtual void			MouseUp(int x, int y, int theBtnNum, int theClickCount);
		virtual void			MouseDrag(int x, int y);
	};
}

#endif // !_PVZMOD_SCROLLBAR_WIDGET_H_
