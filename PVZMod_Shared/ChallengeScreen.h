#pragma once
#ifndef _PVZMOD_CHALLENGE_SCREEN_H_
#define _PVZMOD_CHALLENGE_SCREEN_H_

#include "Widget.h"
#include "ButtonListener.h"
#include "LawnApp.h"

namespace PVZMod
{
	constexpr int NUM_CHALLENGE_MODES = (NUM_GAME_MODES - 1);

	enum ChallengePage
	{
		CHALLENGE_PAGE_SURVIVAL,
		CHALLENGE_PAGE_CHALLENGE,
		CHALLENGE_PAGE_LIMBO,
		CHALLENGE_PAGE_PUZZLE,
		MAX_CHALLANGE_PAGES,
	};

	enum UnlockingState
	{
		UNLOCK_OFF,
		UNLOCK_SHAKING,
		UNLOCK_FADING,
	};

	class LawnApp;
	class ToolTipWidget;
	class NewLawnButton;
	class ButtonWidget;

	/// 【游戏类】选关界面。（原 `::%ChallengeScreen`）
	class ChallengeScreen : public Widget, public ButtonListener
	{
	private:
		enum
		{
			BTN_BACK = 100,
			BTN_MODE = 200,
			BTN_PAGE = 300
		};

	public:
		NewLawnButton*		mBackButton;							
		ButtonWidget*		mPageButton[MAX_CHALLANGE_PAGES];		
		ButtonWidget*		mChallengeButtons[NUM_CHALLENGE_MODES];	
		LawnApp*			mApp;									
		ToolTipWidget*		mToolTip;								
		ChallengePage		mPageIndex;								
		bool				mCheatEnableChallenges;					
		UnlockingState		mUnlockState;							
		int					mUnlockStateCounter;					
		int					mUnlockChallengeIndex;					
		float				mLockShakeX;							
		float				mLockShakeY;							

	public:
		ChallengeScreen(LawnApp* theApp, ChallengePage thePage);
		virtual ~ChallengeScreen();

		void						SetUnlockChallengeIndex(ChallengePage thePage, bool theIsIZombie = false);
		int							MoreTrophiesNeeded(int theChallengeIndex);
		bool						ShowPageButtons();
		void						UpdateButtons();
		int							AccomplishmentsNeeded(int theChallengeIndex);
		void						DrawButton(Graphics* g, int theChallengeIndex);
		virtual void				Draw(Graphics* g);
		virtual void				Update();
		virtual void				AddedToManager(WidgetManager* theWidgetManager);
		virtual void				RemovedFromManager(WidgetManager* theWidgetManager);
		virtual void				ButtonPress(int theId);
		virtual void				ButtonDepress(int theId);
		void						UpdateToolTip();
		virtual void				KeyChar(SexyChar theChar) { ; }

		bool						IsScaryPotterLevel(GameMode theGameMode);
		bool						IsIZombieLevel(GameMode theGameMode);
	};

	/// 【游戏类】关卡定义信息（原 `::%ChallengeDefinition`）
	class ChallengeDefinition
	{
	public:
		GameMode				mChallengeMode;
		int						mChallengeIconIndex;
		ChallengePage			mPage;
		int						mRow;
		int						mCol;
		const SexyChar*			mChallengeName;
	};

	extern ChallengeDefinition* gChallengeDefs;

	ChallengeDefinition& GetChallengeDefinition(int theChallengeMode);
}

#endif // !_PVZMOD_CHALLENGE_SCREEN_H_
