#include "EffectPatch.h"
#include "PVZMod.h"
#include "Reanimator.h"

using namespace PVZMod;

void EffectPatch::SetReanimationParamArray(InitPatch& patch, ReanimationParams* theArray, size_t theSize)
{
	patch.PatchTask("EffectPatch::SetReanimationParamArray", [&]
		{
			*(size_t*)0x47731e = theSize;
			*(ReanimationParams**)0x477345 = theArray;
			*(const char***)0x477395 = &theArray[0].mReanimFileName;
			*(size_t*)0x485223 = theSize - 1;
			*(size_t*)0x48526c = theSize;
		}, true, true);
}