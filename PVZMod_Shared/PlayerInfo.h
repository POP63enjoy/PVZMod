#pragma once
#ifndef _PVZMOD_PLAYER_INFO_H_
#define _PVZMOD_PLAYER_INFO_H_

#include "PVZSTL.h"

namespace PVZMod
{
	enum PottedPlantAge
	{
		PLANTAGE_SPROUT,
		PLANTAGE_SMALL,
		PLANTAGE_MEDIUM,
		PLANTAGE_FULL,
	};

	enum PottedPlantNeed
	{
		PLANTNEED_NONE,
		PLANTNEED_WATER,
		PLANTNEED_FERTILIZER,
		PLANTNEED_BUGSPRAY,
		PLANTNEED_PHONOGRAPH,
	};

	enum SeedType;
	enum GardenType;
	enum DrawVariation;

	class PottedPlant
	{
	public:
		SeedType			mSeedType;
		GardenType			mWhichZenGarden;
		int					mX;
		int					mY;
		int					mFacing;
		__time64_t			mLastWateredTime;
		DrawVariation		mDrawVariation;
		PottedPlantAge		mPlantAge;
		int					mTimesFed;
		int					mFeedingsPerGrow;
		PottedPlantNeed		mPlantNeed;
		__time64_t			mLastNeedFulfilledTime;
		__time64_t			mLastFertilizedTime;
		__time64_t			mLastChocolateTime;
		int					mFutureAttribute[1];
	};

	class DataSync;
	enum GameMode;

	class PlayerInfo
	{
	public:
		String				mName;
		uint32_t			mUseSeq;
		uint32_t			mId;
		int					mLevel;
		int					mCoins;
		int					mFinishedAdventure;
		int					mChallengeRecords[100];
		int					mPurchases[80];
		int					mPlayTimeActivePlayer;
		int					mPlayTimeInactivePlayer;
		int					mHasUsedCheatKeys;
		int					mHasWokenStinky;
		int					mDidntPurchasePacketUpgrade;
		long				mLastStinkyChocolateTime;
		int					mStinkyPosX;
		int					mStinkyPosY;
		int					mHasUnlockedMinigames;
		int					mHasUnlockedPuzzleMode;
		int					mHasNewMiniGame;
		int					mHasNewScaryPotter;
		int					mHasNewIZombie;
		int					mHasNewSurvival;
		int					mHasUnlockedSurvivalMode;
		int					mNeedsMessageOnGameSelector;
		int					mNeedsMagicTacoReward;
		int					mHasSeenStinky;
		int					mHasSeenUpsell;
		int					mPlaceHolderPlayerStats4[1];
		int					mNumPottedPlants;
		PottedPlant			mPottedPlant[200];

	public:
		PlayerInfo();
		~PlayerInfo();

		void				Reset();
		void				AddCoins(int theAmount);
		void				SyncSummary(DataSync& theSync);
		void				SyncDetails(DataSync& theSync);
		void				DeleteUserFiles();
		void				LoadDetails();
		void				SaveDetails();

		int					GetLevel() const { return mLevel; }
		void				SetLevel(int theLevel) { mLevel = theLevel; }
		void				ResetChallengeRecord(GameMode theGameMode);
	};
	static_assert(sizeof(PlayerInfo) == 0x4818);
}

#endif // !_PVZMOD_PLAYER_INFO_H_
