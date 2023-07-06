#pragma once
#ifndef _PVZMOD_LAWN_APP_H_
#define _PVZMOD_LAWN_APP_H_

#include "SexyApp.h"

namespace PVZMod
{
	class TitleScreen;
	class GameSelector;
	class SeedChooserScreen;
	class AwardScreen;
	class CreditScreen;
	class ChallengeScreen;
	class TodFoley;
	class ButtonWidget;
	class PoolEffect;
	class ZenGarden;
	class ReanimatorCache;
	class ProfileMgr;
	class PlayerInfo;
	class LevelStats;
	class Music;
	class EffectSystem;
	class TypingCheck;
	class Reanimation;
	class Board;
	class ChallengeDefinition;
	enum ReanimationID;
	enum CrazyDaveState;
	enum BoardResult;
	enum ReanimationType;
	enum ChallengePage;
	enum FoleyType;

	enum GameMode
	{
		GAMEMODE_ADVENTURE,
		GAMEMODE_SURVIVAL_NORMAL_STAGE_1,
		GAMEMODE_SURVIVAL_NORMAL_STAGE_2,
		GAMEMODE_SURVIVAL_NORMAL_STAGE_3,
		GAMEMODE_SURVIVAL_NORMAL_STAGE_4,
		GAMEMODE_SURVIVAL_NORMAL_STAGE_5,
		GAMEMODE_SURVIVAL_HARD_STAGE_1,
		GAMEMODE_SURVIVAL_HARD_STAGE_2,
		GAMEMODE_SURVIVAL_HARD_STAGE_3,
		GAMEMODE_SURVIVAL_HARD_STAGE_4,
		GAMEMODE_SURVIVAL_HARD_STAGE_5,
		GAMEMODE_SURVIVAL_ENDLESS_STAGE_1,
		GAMEMODE_SURVIVAL_ENDLESS_STAGE_2,
		GAMEMODE_SURVIVAL_ENDLESS_STAGE_3,
		GAMEMODE_SURVIVAL_ENDLESS_STAGE_4,
		GAMEMODE_SURVIVAL_ENDLESS_STAGE_5,
		GAMEMODE_CHALLENGE_WAR_AND_PEAS,
		GAMEMODE_CHALLENGE_WALLNUT_BOWLING,
		GAMEMODE_CHALLENGE_SLOT_MACHINE,
		GAMEMODE_CHALLENGE_RAINING_SEEDS,
		GAMEMODE_CHALLENGE_BEGHOULED,
		GAMEMODE_CHALLENGE_INVISIGHOUL,
		GAMEMODE_CHALLENGE_SEEING_STARS,
		GAMEMODE_CHALLENGE_ZOMBIQUARIUM,
		GAMEMODE_CHALLENGE_BEGHOULED_TWIST,
		GAMEMODE_CHALLENGE_LITTLE_TROUBLE,
		GAMEMODE_CHALLENGE_PORTAL_COMBAT,
		GAMEMODE_CHALLENGE_COLUMN,
		GAMEMODE_CHALLENGE_BOBSLED_BONANZA,
		GAMEMODE_CHALLENGE_SPEED,
		GAMEMODE_CHALLENGE_WHACK_A_ZOMBIE,
		GAMEMODE_CHALLENGE_LAST_STAND,
		GAMEMODE_CHALLENGE_WAR_AND_PEAS_2,
		GAMEMODE_CHALLENGE_WALLNUT_BOWLING_2,
		GAMEMODE_CHALLENGE_POGO_PARTY,
		GAMEMODE_CHALLENGE_FINAL_BOSS,
		GAMEMODE_CHALLENGE_ART_CHALLENGE_WALLNUT,
		GAMEMODE_CHALLENGE_SUNNY_DAY,
		GAMEMODE_CHALLENGE_RESODDED,
		GAMEMODE_CHALLENGE_BIG_TIME,
		GAMEMODE_CHALLENGE_ART_CHALLENGE_SUNFLOWER,
		GAMEMODE_CHALLENGE_AIR_RAID,
		GAMEMODE_CHALLENGE_ICE,
		GAMEMODE_CHALLENGE_ZEN_GARDEN,
		GAMEMODE_CHALLENGE_HIGH_GRAVITY,
		GAMEMODE_CHALLENGE_GRAVE_DANGER,
		GAMEMODE_CHALLENGE_SHOVEL,
		GAMEMODE_CHALLENGE_STORMY_NIGHT,
		GAMEMODE_CHALLENGE_BUNGEE_BLITZ,
		GAMEMODE_CHALLENGE_SQUIRREL,
		GAMEMODE_TREE_OF_WISDOM,
		GAMEMODE_SCARY_POTTER_1,
		GAMEMODE_SCARY_POTTER_2,
		GAMEMODE_SCARY_POTTER_3,
		GAMEMODE_SCARY_POTTER_4,
		GAMEMODE_SCARY_POTTER_5,
		GAMEMODE_SCARY_POTTER_6,
		GAMEMODE_SCARY_POTTER_7,
		GAMEMODE_SCARY_POTTER_8,
		GAMEMODE_SCARY_POTTER_9,
		GAMEMODE_SCARY_POTTER_ENDLESS,
		GAMEMODE_PUZZLE_I_ZOMBIE_1,
		GAMEMODE_PUZZLE_I_ZOMBIE_2,
		GAMEMODE_PUZZLE_I_ZOMBIE_3,
		GAMEMODE_PUZZLE_I_ZOMBIE_4,
		GAMEMODE_PUZZLE_I_ZOMBIE_5,
		GAMEMODE_PUZZLE_I_ZOMBIE_6,
		GAMEMODE_PUZZLE_I_ZOMBIE_7,
		GAMEMODE_PUZZLE_I_ZOMBIE_8,
		GAMEMODE_PUZZLE_I_ZOMBIE_9,
		GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS,
		GAMEMODE_UPSELL,
		GAMEMODE_INTRO,
		NUM_GAME_MODES,
	};

	enum GameScenes
	{
		SCENE_LOADING,
		SCENE_MENU,
		SCENE_LEVEL_INTRO,
		SCENE_PLAYING,
		SCENE_ZOMBIES_WON,
		SCENE_AWARD,
		SCENE_CREDIT,
		SCENE_CHALLENGE,
	};

	enum Dialogs
	{
		DIALOG_NEW_GAME,
		DIALOG_OPTIONS,
		DIALOG_NEWOPTIONS,
		DIALOG_ALMANAC,
		DIALOG_STORE,
		DIALOG_PREGAME_NAG,
		DIALOG_LOAD_GAME,
		DIALOG_CONFIRM_UPDATE_CHECK,
		DIALOG_CHECKING_UPDATES,
		DIALOG_REGISTER_ERROR,
		DIALOG_COLORDEPTH_EXP,
		DIALOG_OPENURL_WAIT,
		DIALOG_OPENURL_FAIL,
		DIALOG_QUIT,
		DIALOG_HIGH_SCORES,
		DIALOG_NAG,
		DIALOG_INFO,
		DIALOG_GAME_OVER,
		DIALOG_LEVEL_COMPLETE,
		DIALOG_PAUSED,
		DIALOG_NO_MORE_MONEY,
		DIALOG_BONUS,
		DIALOG_CONFIRM_BACK_TO_MAIN,
		DIALOG_CONFIRM_RESTART,
		DIALOG_THANKS_FOR_REGISTERING,
		DIALOG_NOT_ENOUGH_MONEY,
		DIALOG_UPGRADED,
		DIALOG_NO_UPGRADE,
		DIALOG_CHOOSER_WARNING,
		DIALOG_USERDIALOG,
		DIALOG_CREATEUSER,
		DIALOG_CONFIRMDELETEUSER,
		DIALOG_RENAMEUSER,
		DIALOG_CREATEUSERERROR,
		DIALOG_RENAMEUSERERROR,
		DIALOG_CHEAT,
		DIALOG_CHEATERROR,
		DIALOG_CONTINUE,
		DIALOG_GETREADY,
		DIALOG_RESTARTCONFIRM,
		DIALOG_CONFIRMPURCHASE,
		DIALOG_CONFIRMSELL,
		DIALOG_TIMESUP,
		DIALOG_VIRTUALHELP,
		DIALOG_JUMPAHEAD,
		DIALOG_CRAZY_DAVE,
		DIALOG_STORE_PURCHASE,
		DIALOG_ZEN_SELL,
		DIALOG_MESSAGE,
		DIALOG_IMITATER,
		DIALOG_PURCHASE_PACKET_SLOT,
		NUM_DIALOGS,
	};

	enum TrialType
	{
		TRIALTYPE_NONE,
		TRIALTYPE_STAGELOCKED,
	};

	constexpr const int ADVENTURE_AREAS = 5;
	constexpr const int LEVELS_PER_AREA = 10;
	
	/// 【游戏类】游戏程序主类。（原 `::%LawnApp`）
	class LawnApp :public SexyApp
	{
	public:
		Board*					mBoard;
		TitleScreen*			mTitleScreen;
		GameSelector*			mGameSelector;
		SeedChooserScreen*		mSeedChooserScreen;
		AwardScreen*			mAwardScreen;
		CreditScreen*			mCreditScreen;
		ChallengeScreen*		mChallengeScreen;
		TodFoley*				mSoundSystem;
		List<ButtonWidget*>		mControlButtonList;
		List<Image*>			mCreatedImageList;
		String					mReferId;
		String					mRegisterLink;
		String					mMod;
		bool					mRegisterResourcesLoaded;
		bool					mTodCheatKeys;
		GameMode				mGameMode;
		GameScenes				mGameScene;
		bool					mLoadingZombiesThreadCompleted;
		bool					mFirstTimeGameSelector;
		int						mGamesPlayed;
		int						mMaxExecutions;
		int						mMaxPlays;
		int						mMaxTime;
		bool					mEasyPlantingCheat;
		PoolEffect*				mPoolEffect;
		ZenGarden*				mZenGarden;
		EffectSystem*			mEffectSystem;
		ReanimatorCache*		mReanimatorCache;
		ProfileMgr*				mProfileMgr;
		PlayerInfo*				mPlayerInfo;
		LevelStats*				mLastLevelStats;
		bool					mCloseRequest;
		int						mAppCounter;
		Music*					mMusic;
		ReanimationID			mCrazyDaveReanimID;
		CrazyDaveState			mCrazyDaveState;
		int						mCrazyDaveBlinkCounter;
		ReanimationID			mCrazyDaveBlinkReanimID;
		int						mCrazyDaveMessageIndex;
		String					mCrazyDaveMessageText;
		int						mAppRandSeed;
		HCURSOR					mBigArrowCursor;
		struct PopDRMComm*		mDRM;
		int						mSessionID;
		int						mPlayTimeActiveSession;
		int						mPlayTimeInactiveSession;
		BoardResult				mBoardResult;
		bool					mKilledYetiAndRestarted;
		TypingCheck*			mKonamiCheck;
		TypingCheck*			mMustacheCheck;
		TypingCheck*			mMoustacheCheck;
		TypingCheck*			mSuperMowerCheck;
		TypingCheck*			mSuperMowerCheck2;
		TypingCheck*			mFutureCheck;
		TypingCheck*			mPinataCheck;
		TypingCheck*			mDaisyCheck;
		TypingCheck*			mSukhbirCheck;
		bool					mMustacheMode;
		bool					mSuperMowerMode;
		bool					mFutureMode;
		bool					mPinataMode;
		bool					mDaisyMode;
		bool					mSukhbirMode;
		TrialType				mTrialType;
		bool					mDebugTrialLocked;
		bool					mMuteSoundsForCutscene;

	public:
		virtual void			LoadingCompleted();
		virtual void			ShowResourceError(bool doExit);

		Reanimation*			ReanimationGet(ReanimationID theReanimID);
		Reanimation*			ReanimationTryToGet(ReanimationID theReanimationID);
		ReanimationID			ReanimationGetID(Reanimation* theReanimation);
		Reanimation*			AddReanimation(float theX, float theY, int aRenderOrder, ReanimationType theReanimationType);
		void					RemoveReanimation(ReanimationID theReanimationID);

		void					ShowGameSelector();
		void					KillGameSelector();
		void					ShowChallengeScreen(ChallengePage thePage);
		int						GetCurrentChallengeIndex();
		ChallengeDefinition&	GetCurrentChallengeDef();
		static SexyString		GetStageString(int theLevel);

		bool					IsAdventureMode();
		bool					IsWhackAZombieLevel();
		bool					IsFirstTimeAdventureMode();
		bool					HasFinishedAdventure();
		bool					IsMiniBossLevel();
		bool					IsSurvivalMode();
		static bool				IsSurvivalNormal(GameMode theGameMode);
		static bool				IsSurvivalHard(GameMode theGameMode);
		static bool				IsSurvivalEndless(GameMode theGameMode);
		bool					IsSquirrelLevel();
		bool					IsStormyNightLevel();
		bool					IsLittleTroubleLevel();
		bool					IsBungeeBlitzLevel();
		bool					IsShovelLevel();
		bool					IsWallnutBowlingLevel();
		bool					IsScaryPotterLevel();
		static bool				IsEndlessScaryPotter(GameMode theGameMode);
		bool					IsIZombieLevel();
		static bool				IsEndlessIZombie(GameMode theGameMode);

		void					PreNewGame(GameMode theGameMode, bool theLookForSavedGame);

		void					PlayFoley(FoleyType theFoleyType);

		void					CenterDialog(Dialog* theDialog, int theWidth, int theHeight);
		int						LawnMessageBox(int theDialogId, const SexyChar* theHeaderName, const SexyChar* theLinesName, const SexyChar* theButton1Name, const SexyChar* theButton2Name, int theButtonMode);

		static SexyString		Pluralize(int theCount, const SexyChar* theSingular, const SexyChar* thePlural);
	};

	static_assert(sizeof(LawnApp) == 0x8c8);

	/// 【游戏变量】全局 LawnApp 指针。
	extern LawnApp*& gLawnApp;
}

#endif // !_PVZMOD_LAWN_APP_H_
