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
	return mSeedType == SeedType::SEED_SUNFLOWER || mSeedType == SeedType::SEED_TWINSUNFLOWER || mSeedType == SeedType::SEED_SUNSHROOM;
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
	if (mSeedType == SeedType::SEED_SQUASH)
	{
		if (mState == PlantState::STATE_SQUASH_RISING || mState == PlantState::STATE_SQUASH_FALLING || mState == PlantState::STATE_SQUASH_DONE_FALLING)
			return true;
	}

	return mSquished || mOnBungeeState == PlantOnBungeeState::PLANT_RISING_WITH_BUNGEE || mDead;
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
		theSeedtype == SeedType::SEED_PUFFSHROOM ||
		theSeedtype == SeedType::SEED_SEASHROOM ||
		theSeedtype == SeedType::SEED_SUNSHROOM ||
		theSeedtype == SeedType::SEED_FUMESHROOM ||
		theSeedtype == SeedType::SEED_HYPNOSHROOM ||
		theSeedtype == SeedType::SEED_DOOMSHROOM ||
		theSeedtype == SeedType::SEED_ICESHROOM ||
		theSeedtype == SeedType::SEED_MAGNETSHROOM ||
		theSeedtype == SeedType::SEED_SCAREDYSHROOM ||
		theSeedtype == SeedType::SEED_GLOOMSHROOM;
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
	assert(theSeedType >= 0 && theSeedType < (int)SeedType::NUM_SEED_TYPES);	// 暂时，直到新增植物

	return aPlantDefs[theSeedType];
}
