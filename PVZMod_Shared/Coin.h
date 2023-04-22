#pragma once
#ifndef _PVZMOD_COIN_H_
#define _PVZMOD_COIN_H_

#include "GameObject.h"
#include "PlayerInfo.h"

namespace PVZMod
{
	enum CoinType
	{
		COIN_NONE,
		COIN_SILVER,
		COIN_GOLD,
		COIN_DIAMOND,
		COIN_SUN,
		COIN_SMALLSUN,
		COIN_LARGESUN,
		COIN_FINAL_SEED_PACKET,
		COIN_TROPHY,
		COIN_SHOVEL,
		COIN_ALMANAC,
		COIN_CARKEYS,
		COIN_VASE,
		COIN_WATERING_CAN,
		COIN_TACO,
		COIN_NOTE,
		COIN_USABLE_SEED_PACKET,
		COIN_PRESENT_PLANT,
		COIN_AWARD_MONEY_BAG,
		COIN_AWARD_PRESENT,
		COIN_AWARD_BAG_DIAMOND,
		COIN_AWARD_SILVER_SUNFLOWER,
		COIN_AWARD_GOLD_SUNFLOWER,
		COIN_CHOCOLATE,
		COIN_AWARD_CHOCOLATE,
		COIN_PRESENT_MINIGAMES,
		COIN_PRESENT_PUZZLE_MODE,
	};

	enum CoinMotion
	{
		COIN_MOTION_FROM_SKY,
		COIN_MOTION_FROM_SKY_SLOW,
		COIN_MOTION_FROM_PLANT,
		COIN_MOTION_COIN,
		COIN_MOTION_LAWNMOWER_COIN,
		COIN_MOTION_FROM_PRESENT,
		COIN_MOTION_FROM_BOSS,
	};

	enum AttachmentID;
	enum SeedType;

	/// 【游戏类】掉落物。（原 `::%Coin`）
	class Coin : public GameObject
	{
	public:
		float			mPosX;
		float			mPosY;
		float			mVelX;
		float			mVelY;
		float			mScale;
		bool			mDead;
		int				mFadeCount;
		float			mCollectX;
		float			mCollectY;
		int				mGroundY;
		int				mCoinAge;
		bool			mIsBeingCollected;
		int				mDisappearCounter;
		CoinType		mType;
		CoinMotion		mCoinMotion;
		AttachmentID	mAttachmentID;
		float			mCollectionDistance;
		SeedType		mUsableSeedType;
		PottedPlant		mPottedPlantSpec;
		bool			mNeedsBouncyArrow;
		bool			mHasBouncyArrow;
		bool			mHitGround;
		int				mTimesDropped;

	public:
		void			MouseDown(int x, int y, int theClickCount);
	};

	static_assert(sizeof(Coin) == 0xD0);
}

#endif // !_PVZMOD_COIN_H_
