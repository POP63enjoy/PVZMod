#include "Plant.h"
#include <cassert>
#include "LawnApp.h"

using namespace PVZMod;

int Plant::CalcRenderOrder()
{
	int func = 0x461f90;
	int result;
	__asm
	{
		mov esi, this
		call func
		mov result, eax
	}
	return result;
}

void Plant::SetSleeping(bool theIsAsleep)
{
	int func = 0x462030;
	int _theIsAsleep = theIsAsleep;
	__asm
	{
		push _theIsAsleep
		mov eax, this
		call func
	}
}

bool Plant::MakesSun()
{
	return mSeedType == SEED_SUNFLOWER || mSeedType == SEED_TWINSUNFLOWER || mSeedType == SEED_SUNSHROOM;
}

bool Plant::IsOnBoard()
{
	if (!mIsOnBoard)
		return false;

	assert(mBoard);
	return true;
}

bool Plant::IsInPlay()
{
	return IsOnBoard() && mApp->mGameMode != GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN && mApp->mGameMode != GameMode::GAMEMODE_TREE_OF_WISDOM;
}

bool Plant::NotOnGround()
{
	if (mSeedType == SEED_SQUASH)
	{
		if (mState == STATE_SQUASH_RISING || mState == STATE_SQUASH_FALLING || mState == STATE_SQUASH_DONE_FALLING)
			return true;
	}

	return mSquished || mOnBungeeState == PLANT_RISING_WITH_BUNGEE || mDead;
}

TodParticleSystem* Plant::AddAttachedParticle(int thePosX, int thePosY, int theRenderPosition, ParticleEffect theEffect)
{
	int func = 0x462670;
	TodParticleSystem* result;
	__asm
	{
		push theEffect
		push theRenderPosition
		push thePosY
		push thePosX
		mov edi, this
		call func
		mov result, eax
	}
	return result;
}

bool Plant::IsNocturnal(SeedType theSeedtype)
{
	return
		theSeedtype == SEED_PUFFSHROOM ||
		theSeedtype == SEED_SEASHROOM ||
		theSeedtype == SEED_SUNSHROOM ||
		theSeedtype == SEED_FUMESHROOM ||
		theSeedtype == SEED_HYPNOSHROOM ||
		theSeedtype == SEED_DOOMSHROOM ||
		theSeedtype == SEED_ICESHROOM ||
		theSeedtype == SEED_MAGNETSHROOM ||
		theSeedtype == SEED_SCAREDYSHROOM ||
		theSeedtype == SEED_GLOOMSHROOM;
}

float PVZMod::PlantDrawHeightOffset(Board* theBoard, Plant* thePlant, SeedType theSeedType, int theCol, int theRow)
{
	int func = 0x468890;
	float result;
	__asm
	{
		push theRow
		push theCol
		mov esi, theSeedType
		mov eax, thePlant
		mov edi, theBoard
		call func
		add esp, 0x8
		fstp result
	}
	return result;
}

PlantDefinition& PVZMod::GetPlantDefinition(SeedType theSeedType)
{
	auto aPlantDefs = (PlantDefinition*)0x6AF238;

	assert(aPlantDefs[theSeedType].mSeedType == theSeedType);
	assert(theSeedType >= 0 && theSeedType < NUM_SEED_TYPES);	// ��ʱ��ֱ������ֲ��

	return aPlantDefs[theSeedType];
}
