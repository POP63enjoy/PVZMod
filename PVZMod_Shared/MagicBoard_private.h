#pragma once

namespace PVZMod::__MAGIC_BOARD_PRIVATE__
{
	extern int* mvOffsetXPtr, * mvOffsetYPtr;
	
	extern bool* mvUseDynLevelNamePtr;
	extern SexyString* mvDynLevelNamePtr;

	void LevelNamePatch(InitPatch& patch);
}