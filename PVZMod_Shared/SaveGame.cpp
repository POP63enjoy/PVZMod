#include "SaveGame.h"
#include "Trail.h"
#include "Board.h"
#include "LawnApp.h"
#include "EffectSystem.h"

using namespace PVZMod;

int SaveGameContext::ByteLeftToRead()
{
    return (mBuffer.mDataBitSize - mBuffer.mReadBitPos + 7) / 8;
}

void SaveGameContext::SyncBytes(void* theDest, int theReadSize)
{
    int func = 0x485100;
    __asm
    {
        mov esi, theReadSize
        mov eax, theDest
        mov ecx, this
        call func
    }
}

void SaveGameContext::SyncInt(int& theInt)
{
    int func = 0x4851a0;
    __asm
    {
        mov esi, theInt
        mov eax, this
        call func
    }
}

void SaveGameContext::SyncInt(unsigned int& theInt)
{
    SyncInt((int&)theInt);
}

void SaveGameContext::SyncReanimationDef(ReanimatorDefinition*& theDefinition)
{
    int func = 0x4851f0;
    __asm
    {
        mov eax, theDefinition
        mov ecx, this
        call func
    }
}

void SaveGameContext::SyncParticleDef(TodParticleDefinition*& theDefinition)
{
    int func = 0x485290;
    __asm
    {
        mov eax, theDefinition
        mov ecx, this
        call func
    }
}

void SaveGameContext::SyncTrailDef(TrailDefinition*& theDefinition)
{
    int func = 0x485320;
    __asm
    {
        mov eax, theDefinition
        mov ecx, this
        call func
    }
}

void PVZMod::SyncParticleSystem(Board* theBoard, TodParticleSystem* theParticleSystem, SaveGameContext& theContext)
{
    int func = 0x4855b0;
    __asm
    {
        mov ebx, theContext
        mov edi, theParticleSystem
        push theBoard
        call func
        add esp, 0x4
    }
}

void PVZMod::SyncReanimation(Board* theBoard, Reanimation* theReanimation, SaveGameContext& theContext)
{
    int func = 0x485620;
    __asm
    {
        mov eax, theContext
        push theReanimation
        push theBoard
        call func
        add esp, 0x8
    }
}

void PVZMod::SyncTrail(Board* theBoard, Trail* theTrail, SaveGameContext& theContext)
{
    theContext.SyncTrailDef(theTrail->mDefinition);
    if (theContext.mReading)
    {
        theTrail->mTrailHolder = theBoard->mApp->mEffectSystem->mTrailHolder;
    }
}
