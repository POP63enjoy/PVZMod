#include "Zombie.h"

using namespace PVZMod;

void Zombie::ReanimShowPrefix(const char* theTrackPrefix, int theRenderGroup)
{
	int func = 0x537630;
	__asm
	{
		mov eax,this
		push theRenderGroup
		push theTrackPrefix
		call func
	}
}

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
