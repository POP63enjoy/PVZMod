#pragma once
#ifndef _PVZMOD_MTRAND_H_
#define _PVZMOD_MTRAND_H_

#include "SexyCommon.h"

namespace PVZMod
{
	constexpr int MTRAND_N = 624;

	class MTRand
	{
		unsigned long mt[MTRAND_N]; /* the array for the state vector  */
		int mti;

	public:
		MTRand(const std::string& theSerialData);
		MTRand(unsigned long seed);
		MTRand();

		void SRand(const std::string& theSerialData);
		void SRand(unsigned long seed);
		unsigned long NextNoAssert();
		unsigned long Next();
		unsigned long NextNoAssert(unsigned long range);
		unsigned long Next(unsigned long range);
		float NextNoAssert(float range);
		float Next(float range);

		std::string Serialize();

		static void SetRandAllowed(bool allowed);
	};

	struct MTAutoDisallowRand
	{
		MTAutoDisallowRand() { MTRand::SetRandAllowed(false); }
		~MTAutoDisallowRand() { MTRand::SetRandAllowed(true); }
	};
}

#endif // !_PVZMOD_MTRAND_H_
