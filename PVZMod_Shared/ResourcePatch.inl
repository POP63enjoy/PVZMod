#pragma once
#ifndef _PVZMOD_RESOURCE_PATCH_INL_
#define _PVZMOD_RESOURCE_PATCH_INL_

#include "PakInterface.h"
#include "PVZMod.h"
#include "Magic.h"

namespace PVZMod
{
	/*template<typename T>
	bool ResourcePatch::ImageLoader::TryImageExt(const std::string& thePath, const std::string& theName, const std::string& theExt, const std::string& theTargetExt, T func)
	{
		std::string fullFileName;
		if (theExt.empty())
			fullFileName = thePath + theName + theTargetExt;
		else if (_stricmp(theExt.c_str(), theTargetExt.c_str()))
			return false;
		else
			fullFileName = thePath + theName + theExt;

		PFILE* file = p_fopen(fullFileName.c_str(), "rb");
		if (file == nullptr) return false;
		bool result = func(file);
		p_fclose(file);
		return result;
	}*/

	PVZMOD_CHECK_MAGIC_FUNC(MF_LoadPak);

	template <typename T>
	void ResourcePatch::ReplacePakInterface(InitPatch& patch)
	{
		patch.PatchTask("ResourcePatch::ReplacePakInterface", [&]
			{
				gPakInterface = nullptr;

				void (*pakInterfaceInitFunc)() = []
				{
					gPakInterfaceBase = new T;
					void(*pvz_atexit)(void(__cdecl*)(void)) = (decltype(pvz_atexit))0x625F3D;
					pvz_atexit([] { delete (T*)gPakInterfaceBase; });
				};

				patch.mHook.HookFunction((void*)0x65b6a0, pakInterfaceInitFunc);

				const DWORD addressList[] = { 0x6B9FD0,0x6B9FE8,0x6BA038,0x6BA050,0x6BA090,0x6BA108,0x6BA120,0x6BA134 };

				for (auto address : addressList)
				{
					DWORD* ptr = (DWORD*)address;
					ptr[0] = 1;
					ptr[1] = (DWORD)&gPakInterfaceBase;
				}

				patch.mHook.InsertCodeAndJump((void*)0x55a17a, (void*)0x55a1a2, [](Hook::Regs* regs)
					{
						PVZMOD_IF_MAGIC_FUNC_EXIST(MF_LoadPak, void(), T,
							{
								((T*)gPakInterfaceBase)->MF_LoadPak();
							});
					});
			}, true, true);
	}
}

#endif // !_PVZMOD_RESOURCE_PATCH_INL_
