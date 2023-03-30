#include "D3DInterface.h"

using namespace PVZMod;

void D3DInterface::Flush()
{
	int func = 0x56ee90;
	__asm
	{
		mov esi, this
		call func
	}
}
