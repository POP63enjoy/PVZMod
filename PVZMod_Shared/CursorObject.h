#pragma once
#ifndef _PVZMOD_CURSOR_OBJECT_H_
#define _PVZMOD_CURSOR_OBJECT_H_

#include "GameObject.h"

namespace PVZMod
{
	enum CursorType
	{
		CURSOR_TYPE_NORMAL,
		CURSOR_TYPE_PLANT_FROM_BANK,
		CURSOR_TYPE_PLANT_FROM_USABLE_COIN,
		CURSOR_TYPE_PLANT_FROM_GLOVE,
		CURSOR_TYPE_PLANT_FROM_DUPLICATOR,
		CURSOR_TYPE_PLANT_FROM_WHEEL_BARROW,
		CURSOR_TYPE_SHOVEL,
		CURSOR_TYPE_HAMMER,
		CURSOR_TYPE_COBCANNON_TARGET,
		CURSOR_TYPE_WATERING_CAN,
		CURSOR_TYPE_FERTILIZER,
		CURSOR_TYPE_BUG_SPRAY,
		CURSOR_TYPE_PHONOGRAPH,
		CURSOR_TYPE_CHOCOLATE,
		CURSOR_TYPE_GLOVE,
		CURSOR_TYPE_MONEY_SIGN,
		CURSOR_TYPE_WHEEELBARROW,
		CURSOR_TYPE_TREE_FOOD,
	};

	enum SeedType;
	enum CoinID;
	enum PlantID;
	enum ReanimationID;

	/// 【游戏类】光标对象。（原 `::%CursorObject`）
	class CursorObject : public GameObject
	{
	public:
		int				mSeedBankIndex;
		SeedType		mType;
		SeedType		mImitaterType;
		CursorType		mCursorType;
		CoinID			mCoinID;
		PlantID			mGlovePlantID;
		PlantID			mDuplicatorPlantID;
		PlantID			mCobCannonPlantID;
		int				mHammerDownCounter;
		ReanimationID	mReanimCursorID;
	};
}

#endif // !_PVZMOD_CURSOR_OBJECT_H_
