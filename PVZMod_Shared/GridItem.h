#pragma once
#ifndef _PVZMOD_GRID_ITEM_H_
#define _PVZMOD_GRID_ITEM_H_

namespace PVZMod
{
	enum GridItemType
	{
		GRIDITEM_NONE,
		GRIDITEM_GRAVESTONE,
		GRIDITEM_CRATER,
		GRIDITEM_LADDER,
		GRIDITEM_PORTAL_CIRCLE,
		GRIDITEM_PORTAL_SQUARE,
		GRIDITEM_BRAIN,
		GRIDITEM_SCARY_POT,
		GRIDITEM_SQUIRREL,
		GRIDITEM_ZEN_TOOL,
		GRIDITEM_STINKY,
		GRIDITEM_RAKE,
		GRIDITEM_IZOMBIE_BRAIN,
	};

	enum GridItemState
	{
		GRIDITEM_STATE_NORMAL,
		GRIDITEM_STATE_GRAVESTONE_SPECIAL,
		GRIDITEM_STATE_PORTAL_CLOSED,
		GRIDITEM_STATE_SCARY_POT_QUESTION,
		GRIDITEM_STATE_SCARY_POT_LEAF,
		GRIDITEM_STATE_SCARY_POT_ZOMBIE,
		GRIDITEM_STATE_SQUIRREL_WAITING,
		GRIDITEM_STATE_SQUIRREL_PEEKING,
		GRIDITEM_STATE_SQUIRREL_RUNNING_UP,
		GRIDITEM_STATE_SQUIRREL_RUNNING_DOWN,
		GRIDITEM_STATE_SQUIRREL_RUNNING_LEFT,
		GRIDITEM_STATE_SQUIRREL_RUNNING_RIGHT,
		GRIDITEM_STATE_SQUIRREL_CAUGHT,
		GRIDITEM_STATE_SQUIRREL_ZOMBIE,
		GRIDITEM_STATE_ZEN_TOOL_WATERING_CAN,
		GRIDITEM_STATE_ZEN_TOOL_FERTILIZER,
		GRIDITEM_STATE_ZEN_TOOL_BUG_SPRAY,
		GRIDITEM_STATE_ZEN_TOOL_PHONOGRAPH,
		GRIDITEM_STATE_ZEN_TOOL_GOLD_WATERING_CAN,
		GRIDITEM_STINKY_WALKING_LEFT,
		GRIDITEM_STINKY_TURNING_LEFT,
		GRIDITEM_STINKY_WALKING_RIGHT,
		GRIDITEM_STINKY_TURNING_RIGHT,
		GRIDITEM_STINKY_SLEEPING,
		GRIDITEM_STINKY_FALLING_ASLEEP,
		GRIDITEM_STINKY_WAKING_UP,
		GRIDITEM_STATE_RAKE_ATTRACTING,
		GRIDITEM_STATE_RAKE_WAITING,
		GRIDITEM_STATE_RAKE_TRIGGERED,
		GRIDITEM_STATE_BRAIN_SQUISHED,
	};

	enum ScaryPotType
	{
		SCARYPOT_NONE,
		SCARYPOT_SEED,
		SCARYPOT_ZOMBIE,
		SCARYPOT_SUN,
	};

	struct MotionTrailFrame
	{
		float mPosX;
		float mPosY;
		float mAnimTime;
	};

	class LawnApp;
	class Board;
	enum ReanimationID;
	enum ParticleSystemID;
	enum ZombieType;
	enum SeedType;

	/// 【游戏类】格内物品。（原 ::GridItem）
	class GridItem
	{
	public:
		LawnApp*				mApp;
		Board*					mBoard;
		GridItemType			mGridItemType;
		GridItemState			mGridItemState;
		int						mGridX;
		int						mGridY;
		int						mGridItemCounter;
		int						mRenderOrder;
		bool					mDead;
		float					mPosX;
		float					mPosY;
		float					mGoalX;
		float					mGoalY;
		ReanimationID			mGridItemReanimID;
		ParticleSystemID		mGridItemParticleID;
		ZombieType				mZombieType;
		SeedType				mSeedType;
		ScaryPotType			mScaryPotType;
		bool					mHighlighted;
		int						mTransparentCounter;
		int						mSunCount;
		MotionTrailFrame		mMotionTrailFrames[12];
		int						mMotionTrailCount;
	};

	static_assert(sizeof(GridItem) == 0xE8);
}

#endif // !_PVZMOD_GRID_ITEM_H_
