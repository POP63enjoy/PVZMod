#include "Board.h"
#include "Graphics.h"
#include "GameButton.h"
#include "LawnApp.h"
#include "Challenge.h"

using namespace PVZMod;

int* PVZMod::gZombieWaves = (int*)0x6b34a8;

void PVZMod::ZombiePickerInitForWave(ZombiePicker* theZombiePicker)
{
	memset(theZombiePicker, 0, sizeof(ZombiePicker));
}

void PVZMod::ZombiePickerInit(ZombiePicker* theZombiePicker)
{
	ZombiePickerInitForWave(theZombiePicker);
	memset(theZombiePicker->mAllWavesZombieTypeCount, 0, NUM_ZOMBIE_TYPES);
}


Zombie* Board::AddZombie(ZombieType theZombieType, int theFromWave)
{
	return AddZombieInRow(theZombieType, PickRowForNewZombie(theZombieType), theFromWave);
}

Zombie* Board::AddZombieInRow(ZombieType theZombieType, int theRow, int theFromWave)
{
	int func = 0x40f2c0;
	Zombie* result;

	__asm
	{
		mov ebx, theFromWave
		mov eax, this
		push theRow
		push theZombieType
		call func
		mov result, eax
	}

	return result;
}

int Board::PickRowForNewZombie(ZombieType theZombieType)
{
	int func = 0x40f150;
	int result;
	__asm
	{
		push theZombieType
		mov eax, this
		call func
		mov result, eax
	}
	return result;
}

#define ITERATE_GAMEOBJECT(object) \
bool Board::Iterate##object##s(object*& the##object) \
{ \
	while (m##object##s.IterateNext(the##object)) \
		if (!the##object->mDead) \
			return true; \
		return false; \
}

ITERATE_GAMEOBJECT(Zombie);
ITERATE_GAMEOBJECT(Plant);
ITERATE_GAMEOBJECT(Projectile);
ITERATE_GAMEOBJECT(Coin);
ITERATE_GAMEOBJECT(LawnMower);
ITERATE_GAMEOBJECT(GridItem);

#undef ITERATE_GAMEOBJECT

int Board::GetNumWavesPerSurvivalStage()
{
	if (mApp->mGameMode == GAMEMODE_CHALLENGE_LAST_STAND || mApp->IsSurvivalNormal(mApp->mGameMode))
		return 10;
	else if (mApp->IsSurvivalHard(mApp->mGameMode) || mApp->IsSurvivalEndless(mApp->mGameMode))
		return 20;
	assert(false);
	return -1;
}

bool Board::IsFlagWave(int theWaveNumber)
{
	if (mApp->IsFirstTimeAdventureMode() && mLevel == 1)
		return false;

	int aWavesPerFlag = GetNumWavesPerFlag();
	return theWaveNumber % aWavesPerFlag == aWavesPerFlag - 1;
}

int Board::GetNumWavesPerFlag()
{
	return (mApp->IsFirstTimeAdventureMode() && mNumWaves < 10) ? mNumWaves : 10;
}

int Board::GetSurvivalFlagsCompleted()
{
	int aWavesPerFlag = GetNumWavesPerFlag();
	int aFlagsCompleted = mChallenge->mSurvivalStage * GetNumWavesPerSurvivalStage() / aWavesPerFlag;
	int aCurrentWave = mCurrentWave;

	if (IsFlagWave(aCurrentWave - 1) && mBoardFadeOutCounter < 0 && !mNextSurvivalStageCounter)
		aCurrentWave -= 1;

	return aCurrentWave / aWavesPerFlag + aFlagsCompleted;
}

void Board::PutZombieInWave(ZombieType theZombieType, int theWaveNumber, ZombiePicker* theZombiePicker)
{
	assert(theWaveNumber < 100 && theZombiePicker->mZombieCount < 50);
	int func = 0x40a750;
	__asm
	{
		mov ecx, theZombiePicker
		mov eax, theWaveNumber
		mov esi, theZombieType
		mov edi, this
		call func
	}
}

ZombieType Board::GetIntroducedZombieType()
{
	int func = 0x40EBF0;
	ZombieType result;
	__asm
	{
		mov eax, this
		call func
		mov result, eax
	}
	return result;
}

void Board::PutInMissingZombies(int theWaveNumber, ZombiePicker* theZombiePicker)
{
	int func = 0x40a7a0;
	__asm
	{
		push theZombiePicker
		push theWaveNumber
		mov eax, this
		call func
	}
}

ZombieType Board::PickZombieType(int theZombiePoints, int theWaveIndex, ZombiePicker* theZombiePicker)
{
	int func = 0x40eda0;
	ZombieType result;
	__asm
	{
		push theZombiePicker
		push theWaveIndex
		push theZombiePoints
		push this
		call func
		mov result, eax
	}
	return result;
}

int Board::GridToPixelX(int theGridX, int theGridY)
{
	int func = 0x41e010;
	int result;
	__asm
	{
		mov eax, theGridX
		mov esi, theGridY
		mov ecx, this
		call func
		mov result, eax
	}
	return result;
}

int Board::GridToPixelY(int theGridX, int theGridY)
{
	int func = 0x41e0d0;
	int result;
	__asm
	{
		mov ecx, theGridX
		mov eax, theGridY
		mov ebx, this
		call func
		mov result, eax
	}
	return result;
}

Plant* Board::GetFlowerPotAt(int theGridX, int theGridY)
{
	Plant* aPlant = nullptr;
	while (IteratePlants(aPlant))
	{
		if (aPlant->mPlantCol == theGridX && aPlant->mRow == theGridY && !aPlant->NotOnGround() && aPlant->mSeedType == SEED_FLOWERPOT)
		{
			return aPlant;
		}
	}
	return nullptr;
}

bool Board::StageIsNight()
{
	return
		mBackground == BACKGROUND_2_NIGHT ||
		mBackground == BACKGROUND_4_FOG ||
		mBackground == BACKGROUND_6_BOSS ||
		mBackground == BACKGROUND_MUSHROOM_GARDEN ||
		mBackground == BACKGROUND_ZOMBIQUARIUM;
}

bool Board::HasProgressMeter()
{
	int func = 0x418830;
	bool result;

	__asm
	{
		mov edx, this
		call func
		mov result, al
	}

	return result;
}

ZombieID Board::ZombieGetID(Zombie* theZombie)
{
	return (ZombieID)mZombies.DataArrayGetId(theZombie);
}

int Board::MakeRenderOrder(RenderLayer theRenderLayer, int theRow, int theLayerOffset)
{
	return theRow * RENDER_LAYER_ROW_OFFSET + theRenderLayer + theLayerOffset;
}

size_t Board::gExtraZombieSize = 0;
size_t Board::gExtraPlantSize = 0;
