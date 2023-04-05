#include "Zombie.h"
#include <cassert>
#include "LawnApp.h"
#include "Reanimator.h"
#include "TodParticle.h"

using namespace PVZMod;

bool Zombie::IsOnBoard()
{
	int func = 0x52F2B0;
	bool result;
	__asm
	{
		mov eax, this
		call func
		mov result, al
	}
	return result;
}

float Zombie::GetPosYBasedOnRow(int theRow)
{
	int func = 0x535CF0;
	float result;
	__asm
	{
		push theRow
		mov eax, this
		call func
		fstp result
	}
	return result;
}

Reanimation* Zombie::LoadReanim(ReanimationType theReanimationType)
{
	int func = 0x5288E0;
	Reanimation* result;
	__asm
	{
		push theReanimationType
		mov eax, this
		call func
		mov result, eax
	}
	return result;
}

void Zombie::LoadPlainZombieReanim()
{
	int func = 0x5287E0;
	__asm
	{
		mov edi, this
		call func
	}
}

void Zombie::PlayZombieReanim(const char* theTrackName, ReanimLoopType theLoopType, int theBlendTime, float theAnimRate)
{
	int func = 0x52CF70;
	__asm
	{
		push theAnimRate
		push theBlendTime
		push theLoopType
		push theTrackName
		mov edi, this
		call func
	}
}

void Zombie::ReanimShowPrefix(const char* theTrackPrefix, int theRenderGroup)
{
	int func = 0x537630;
	__asm
	{
		mov eax, this
		push theRenderGroup
		push theTrackPrefix
		call func
	}
}

void Zombie::StartWalkAnim(int theBlendTime)
{
	int func = 0x533750;
	__asm
	{
		mov eax, this
		mov esi, theBlendTime
		call func
	}
}

void Zombie::SetupWaterTrack(const char* theTrackName)
{
	int func = 0x53B310;
	__asm
	{
		push theTrackName
		mov eax, this
		call func
	}
}

void Zombie::SetAnimRate(float theAnimRate)
{
	int func = 0x533440;
	__asm
	{
		push theAnimRate
		mov eax, this
		call func
	}
}

void Zombie::BossSetupReanim()
{
	int func = 0x53AC60;
	__asm
	{
		mov eax, this
		call func
	}
}

void Zombie::UpdateAnimSpeed()
{
	int func = 0x5334C0;
	__asm
	{
		mov esi, this
		call func
	}
}

void Zombie::UpdateReanim()
{
	int func = 0x530780;
	__asm
	{
		mov eax, this
		call func
	}
}

void Zombie::AttachShield()
{
	int func = 0x537470;
	__asm
	{
		mov eax, this
		call func
	}
}

void Zombie::PickBungeeZombieTarget(int theColumn)
{
	int func = 0x528B10;
	__asm
	{
		push theColumn
		push this
		call func
	}
}

TodParticleSystem* Zombie::AddAttachedParticle(int thePosX, int thePosY, ParticleEffect theEffect)
{
	int func = 0x536660;
	TodParticleSystem* result;
	__asm
	{
		push theEffect
		push thePosY
		push thePosX
		mov eax, this
		call func
		mov result, eax
	}
}

void Zombie::PickRandomSpeed()
{
	int func = 0x528EE0;
	__asm
	{
		mov eax, this
		call func
	}
}

void Zombie::PlayZombieAppearSound()
{
	int func = 0x534AB0;
	__asm
	{
		mov ecx, this
		call func
	}
}

void Zombie::StartZombieSound()
{
	int func = 0x534BE0;
	__asm
	{
		mov esi, this
		call func
	}
}

ZombieDefinition& PVZMod::GetZombieDefinition(ZombieType theZombieType)
{
	auto aZombieDefs = (ZombieDefinition*)0x6ADA38;

	assert(aZombieDefs[theZombieType].mZombieType == theZombieType);
	assert(theZombieType >= 0 && theZombieType < (int)ZombieType::NUM_ZOMBIE_TYPES);	// 暂时，直到新增僵尸

	return aZombieDefs[theZombieType];
}
