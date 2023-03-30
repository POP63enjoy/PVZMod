#include "Coin.h"

using namespace PVZMod;

void Coin::MouseDown(int x, int y, int theClickCount)
{
	int func = 0x4348f0;
	__asm
	{
		push theClickCount
		mov ecx, this
		call func
	}
}
