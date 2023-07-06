#pragma once
#ifndef _PVZMOD_SEED_PACKET_H_
#define _PVZMOD_SEED_PACKET_H_

#include "GameObject.h"

namespace PVZMod
{
	/// °æ”Œœ∑¿‡°øø®∆¨°££®‘≠ `::%SeedPacket`£©
	class SeedPacket : public GameObject
	{
	public:
		int				mRefreshCounter;
		int				mRefreshTime;
		int				mIndex;
		int				mOffsetX;
		SeedType		mPacketType;
		SeedType		mImitaterType;
		int				mSlotMachineCountDown;
		SeedType		mSlotMachiningNextSeed;
		float			mSlotMachiningPosition;
		bool			mActive;
		bool			mRefreshing;
		int				mTimesUsed;
	};
	static_assert(sizeof(SeedPacket) == 0x50);

	constexpr size_t SEEDBANK_MAX = 10;

	class SeedBank : public GameObject
	{
	public:
		int				    mNumPackets;
		SeedPacket		    mSeedPackets[SEEDBANK_MAX];
		int				    mCutSceneDarken;
		int				    mConveyorBeltCounter;
	};
}

#endif // !_PVZMOD_SEED_PACKET_H_
