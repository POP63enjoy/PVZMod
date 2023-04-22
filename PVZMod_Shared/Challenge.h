#pragma once
#ifndef _PVZMOD_CHALLENGE_H_
#define _PVZMOD_CHALLENGE_H_

namespace PVZMod
{
	enum ChallengeState
	{
		STATECHALLENGE_NORMAL,
		STATECHALLENGE_BEGHOULED_MOVING,
		STATECHALLENGE_BEGHOULED_FALLING,
		STATECHALLENGE_BEGHOULED_NO_MATCHES,
		STATECHALLENGE_SLOT_MACHINE_ROLLING,
		STATECHALLENGE_STORM_FLASH_1,
		STATECHALLENGE_STORM_FLASH_2,
		STATECHALLENGE_STORM_FLASH_3,
		STATECHALLENGE_ZEN_FADING,
		STATECHALLENGE_SCARY_POTTER_MALLETING,
		STATECHALLENGE_LAST_STAND_ONSLAUGHT,
		STATECHALLENGE_TREE_JUST_GREW,
		STATECHALLENGE_TREE_GIVE_WISDOM,
		STATECHALLENGE_TREE_WAITING_TO_BABBLE,
		STATECHALLENGE_TREE_BABBLING
	};

	class LawnApp;
	class Board;
	enum SeedType;
	enum ReanimationID;

	/// 【游戏类】关卡特性。（原 `::%Challenge`）
	class Challenge
	{
	public:
		LawnApp*			mApp;
		Board*				mBoard;
		bool				mBeghouledMouseCapture;
		int					mBeghouledMouseDownX;
		int					mBeghouledMouseDownY;
		bool				mBeghouledEated[9][6];
		bool				mBeghouledPurcasedUpgrade[3];
		int					mBeghouledMatchesThisMove;
		ChallengeState		mChallengeState;
		int					mChallengeStateCounter;
		int					mConveyorBeltCounter;
		int					mChallengeScore;
		bool				mShowBowlingLine;
		SeedType			mLastConveyorSeedType;
		int					mSurvivalStage;
		int					mSlotMachineRollCount;
		ReanimationID		mReanimChallenge;
		ReanimationID		mReanimClouds[6];
		int					mCloudsCounter[6];
		int					mChallengeGridX;
		int					mChallengeGridY;
		int					mScaryPotterPots;
		int					mRainCounter;
		int					mTreeOfWisdomTalkIndex;
	};
}

#endif // !_PVZMOD_CHALLENGE_H_
