#pragma once
#ifndef _PVZMOD_WIDGET_CONTAINER_H_
#define _PVZMOD_WIDGET_CONTAINER_H_

#include "SexyCommon.h"
#include "Rect.h"
#include "Flags.h"

namespace PVZMod
{
	class Graphics;
	class Widget;
	class WidgetManager;

	typedef List<Widget*> WidgetList;

	/// 【游戏类】控件容器。（原 `Sexy::WidgetContainer`）
	class WidgetContainer
	{
	public:
		WidgetList				mWidgets;
		WidgetManager*			mWidgetManager;
		WidgetContainer*		mParent;

		bool					mUpdateIteratorModified;
		Iterator<WidgetList>	mUpdateIterator;
		uint32_t				mLastWMUpdateCount;
		int						mUpdateCnt;
		bool					mDirty;
		int						mX;
		int						mY;
		int						mWidth;
		int						mHeight;
		bool					mHasAlpha;
		bool					mClip;
		FlagsMod				mWidgetFlagsMod;
		int						mPriority;
		int						mZOrder;

	public:
		Widget*					GetWidgetAtHelper(int x, int y, int theFlags, bool* found, int* theWidgetX, int* theWidgetY);
		bool					IsBelowHelper(Widget* theWidget1, Widget* theWidget2, bool* found);
		void					InsertWidgetHelper(const WidgetList::iterator& where, Widget* theWidget);

	public:
		WidgetContainer();
		virtual ~WidgetContainer();

		virtual Rect			GetRect();
		virtual bool			Intersects(WidgetContainer* theWidget);

		virtual void			AddWidget(Widget* theWidget);
		virtual void			RemoveWidget(Widget* theWidget);
		virtual bool			HasWidget(Widget* theWidget);
		virtual void			DisableWidget(Widget* theWidget);
		virtual void			RemoveAllWidgets(bool doDelete = false, bool recursive = false);

		virtual void			SetFocus(Widget* theWidget);
		virtual bool			IsBelow(Widget* theWidget1, Widget* theWidget2);
		virtual void			MarkAllDirty();
		virtual void			BringToFront(Widget* theWidget);
		virtual void			BringToBack(Widget* theWidget);
		virtual void			PutBehind(Widget* theWidget, Widget* theRefWidget);
		virtual void			PutInfront(Widget* theWidget, Widget* theRefWidget);
		virtual Point			GetAbsPos(); // relative to top level

		virtual void			MarkDirty();
		virtual void			MarkDirtyFull();
		virtual void			MarkDirtyFull(WidgetContainer* theWidget);
		virtual void			MarkDirty(WidgetContainer* theWidget);

		virtual void			AddedToManager(WidgetManager* theWidgetManager);
		virtual void			RemovedFromManager(WidgetManager* theWidgetManager);

		virtual void			Update();
		virtual void			UpdateAll(ModalFlags* theFlags);
		virtual void			UpdateF(float theFrac);
		virtual void			UpdateFAll(ModalFlags* theFlags, float theFrac);
		virtual void			Draw(Graphics* g);
		virtual void			DrawAll(ModalFlags* theFlags, Graphics* g);
		virtual void			SysColorChangedAll();
		virtual void			SysColorChanged();
	};
	static_assert(sizeof(WidgetContainer) == 0x54);
}

#endif // !_PVZMOD_WIDGET_CONTAINER_H_
