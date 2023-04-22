#pragma once
#ifndef _PVZMOD_LAWN_MOWER_H_
#define _PVZMOD_LAWN_MOWER_H_

namespace PVZMod
{
	enum LawnMowerState
	{
		MOWER_ROLLING_IN,
		MOWER_READY,
		MOWER_TRIGGERED,
		MOWER_SQUISHED,
	};

	enum LawnMowerType
	{
		LAWNMOWER_LAWN,
		LAWNMOWER_POOL,
		LAWNMOWER_ROOF,
		LAWNMOWER_SUPER_MOWER,
		NUM_MOWER_TYPES,
	};

	enum MowerHeight
	{
		MOWER_HEIGHT_LAND,
		MOWER_HEIGHT_DOWN_TO_POOL,
		MOWER_HEIGHT_IN_POOL,
		MOWER_HEIGHT_UP_TO_LAND,
	};


	class LawnApp;
	enum ReanimationID;
	class Board;

	/// 【游戏类】小推车。（原 `::%LawnMower`）
	class LawnMower
	{
	public:
		LawnApp*			mApp;
		Board*				mBoard;
		float				mPosX;
		float				mPosY;
		int					mRenderOrder;
		int					mRow;
		int					mAnimTicksPerFrame;
		ReanimationID		mReanimID;
		int					mChompCounter;
		int					mRollingInCounter;
		int					mSquishedCounter;
		LawnMowerState		mMowerState;
		bool				mDead;
		bool				mVisible;
		LawnMowerType		mMowerType;
		float				mAltitude;
		MowerHeight			mMowerHeight;
		int					mLastPortalX;
	};
	static_assert(sizeof(LawnMower) == 0x44);
}

#endif // !_PVZMOD_LAWN_MOWER_H_
