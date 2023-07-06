#pragma once
#ifndef _PVZMOD_TITLE_SCREEN_
#define _PVZMOD_TITLE_SCREEN_

#include "Widget.h"
#include "ButtonListener.h"

#include <cassert>

namespace PVZMod
{
	class HyperlinkWidget;
	class LawnApp;

	enum TitleState
	{
		TITLESTATE_WAITING_FOR_FIRST_DRAW,
		TITLESTATE_POPCAP_LOGO,
		TITLESTATE_PARTNER_LOGO,
		TITLESTATE_SCREEN
	};

	/// 【游戏类】标题界面。（原 `::%TitleScreen`）
	class TitleScreen :public Widget, public ButtonListener
	{
	public:
		HyperlinkWidget*	mStartButton;
		float				mCurBarWidth;
		float				mTotalBarWidth;
		float				mBarVel;
		float				mBarStartProgress;
		bool				mRegisterClicked;
		bool				mLoadingThreadComplete;
		int					mTitleAge;
		KeyCode				mQuickLoadKey;
		bool				mNeedRegister;
		bool				mNeedShowRegisterBox;
		bool				mDrawnYet;
		bool				mNeedToInit;
		float				mPrevLoadingPercent;
		TitleState			mTitleState;
		int					mTitleStateCounter;
		int					mTitleStateDuration;
		bool				mDisplayPartnerLogo;
		bool				mLoaderScreenIsLoaded;
		LawnApp*			mApp;

	public:
		TitleScreen(LawnApp* theApp);
		virtual ~TitleScreen();

		virtual void			AddedToManager(WidgetManager* theWidgetManager);
		virtual void			RemovedFromManager(WidgetManager* theWidgetManager);
		virtual void			ButtonPress(int theId);
		virtual void			ButtonDepress(int theId);
		virtual void			MouseDown(int x, int y, int theClickCount);
		virtual void			KeyDown(KeyCode theKey);
		virtual void			Draw(Graphics* g);
		virtual void			Update();
	};

	static_assert(sizeof(TitleScreen) == 0xc8);
}

#endif // !_PVZMOD_TITLE_SCREEN_
