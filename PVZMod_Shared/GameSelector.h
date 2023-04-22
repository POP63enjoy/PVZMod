#pragma once
#ifndef _PVZMOD_GAME_SELECTOR_H_
#define _PVZMOD_GAME_SELECTOR_H_

#include "Widget.h"
#include "ButtonListener.h"

namespace PVZMod
{
	class LawnApp;
	class NewLawnButton;
	class DialogButton;
	class ToolTipWidget;
	enum ParticleSystemID;
	enum ReanimationID;

	enum SelectorAnimState
	{
		SELECTOR_OPEN,
		SELECTOR_NEW_USER,
		SELECTOR_SHOW_SIGN,
		SELECTOR_IDLE,
	};
	

	/// 【游戏类】主菜单界面。（原 `::%GameSelector`）
	class GameSelector :public Widget, public ButtonListener
	{
	public:
		LawnApp*				mApp;
		NewLawnButton*			mAdventureButton;
		NewLawnButton*			mMinigameButton;
		NewLawnButton*			mPuzzleButton;
		NewLawnButton*			mOptionsButton;
		NewLawnButton*			mQuitButton;
		NewLawnButton*			mHelpButton;
		NewLawnButton*			mStoreButton;
		NewLawnButton*			mAlmanacButton;
		NewLawnButton*			mZenGardenButton;
		NewLawnButton*			mSurvivalButton;
		NewLawnButton*			mChangeUserButton;
		Widget*					mOverlayWidget;
		bool					mStartingGame;
		int						mStartingGameCounter;
		bool					mMinigamesLocked;
		bool					mPuzzleLocked;
		bool					mSurvivalLocked;
		bool					mShowStartButton;
		ParticleSystemID		mTrophyParticleID;
		ReanimationID			mSelectorReanimID;
		ReanimationID			mCloudReanimID[6];
		int						mCloudCounter[6];
		ReanimationID			mFlowerReanimID[3];
		ReanimationID			mLeafReanimID;
		ReanimationID			mHandReanimID;
		int						mLeafCounter;
		SelectorAnimState		mSelectorState;
		int						mLevel;
		bool					mLoading;
		ToolTipWidget*			mToolTip;
		bool					mHasTrophy;
		bool					mUnlockSelectorCheat;

		enum
		{
			Btn_Adventure = 100,
			Btn_Minigame,
			Btn_Puzzle,
			Btn_Options,
			Btn_Help,
			Btn_Quit,
			Btn_ChangeUser,
			Btn_Store,
			Btn_Almanac,
			Btn_ZenGarden,
			Btn_Survival,
		};

	public:
		GameSelector(LawnApp* theApp);
		virtual ~GameSelector();

		void					SyncProfile(bool theShowLoading);

		virtual void			AddedToManager(WidgetManager* theWidgetManager);
		virtual void			RemovedFromManager(WidgetManager* theWidgetManager);
		virtual void			OrderInManagerChanged();
		virtual void			KeyDown(KeyCode theKey);
		virtual void			KeyChar(SexyChar theChar);
		virtual void			ButtonMouseEnter(int theId);
		virtual void			ButtonPress(int theId, int theClickCount);
		virtual void			ButtonDepress(int theId);
		virtual void			MouseDown(int x, int y, int theClickCount);
		virtual void			Update();
		virtual void			Draw(Graphics* g);
		virtual void			DrawOverlay(Graphics* g);
		void					TrackButton(DialogButton* theButton, const char* theTrackName, float theOffsetX, float theOffsetY);
	};

	static_assert(sizeof(GameSelector) == 0x130);

	class GameSelectorOverlay : public Widget
	{
	public:
		GameSelector* mParent;					//+0x88

	public:
		GameSelectorOverlay(GameSelector* theGameSelector);
		virtual ~GameSelectorOverlay() { }

		virtual void Draw(Graphics* g);
	};
}

#endif // !_PVZMOD_GAME_SELECTOR_H_
