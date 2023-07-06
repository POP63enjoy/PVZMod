#include "PVZMod.h"
#include <cassert>
#include "Res.h"
#include <intrin.h>
#include "MagicBoard_private.h"

using namespace PVZMod;

Hook* InitPatch::gHook = nullptr;

InitPatch::InitPatch()
	:mHook(*gHook)
{
	DWORD old;
	VirtualProtect((void*)0x401000, 0x25C000, PAGE_EXECUTE_READWRITE, &old);
	VirtualProtect((void*)0x65D000, 0x4C000, PAGE_READWRITE, &old);
}

InitPatch::~InitPatch()
{
	DWORD old;
	VirtualProtect((void*)0x401000, 0x25C000, PAGE_EXECUTE_READ, &old);
	VirtualProtect((void*)0x65D000, 0x4C000, PAGE_READONLY, &old);
}

void InitPatch::PatchTask(const std::string &name, const std::function<void()>& func, bool once, bool throwOnTwice)
{
	if (!once)
		goto patch;

	if (!mPatchMap[name])
	{
		mPatchMap[name] = true;
	patch:
		mPatchList.push_back(name);
		try
		{
			func();
		}
		catch (const std::exception& e)
		{
			std::string exstring;
			exstring += "Exception: ";
			exstring += e.what();
			exstring += "\n\n";
			exstring += "At:";
			while (!mPatchList.empty())
			{
				exstring += "\n" + mPatchList.front();
				mPatchList.pop_front();
			}
			MessageBoxA(nullptr, exstring.c_str(), "InitPatch Exception", MB_ICONERROR);
			abort();
		}
		mPatchList.pop_back();
	}
	else if (throwOnTwice)
	{
		throw std::exception((name + " can only be called once.").c_str());
	}
}

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,
	DWORD fdwReason,
	LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	{
		InitPatch::gHook = new Hook();
		InitPatch* patch = new InitPatch();
		patch->PatchTask("Start Patching", [&]
			{
				patch->PatchTask("Patch Alloc", [&]
					{
						patch->mHook.HookFunction((void*)0x629611, &malloc);	// malloc
						patch->mHook.HookFunction((void*)0x627D9C, &free);		// free
						patch->mHook.HookFunction((void*)0x62895d, &realloc);	// realloc
						patch->mHook.HookFunction((void*)0x6369D0, &_msize);	// _msize
						patch->mHook.HookFunction((void*)0x629465, &calloc);	// _calloc_impl
					});
				patch->PatchTask("Patch Resource File", [&]
					{
						ExtractGameResourcesByName = (decltype(ExtractGameResourcesByName))patch->mHook.HookFunction((void*)0x478320, &ExtractAllResourcesByName);
					});

				__MAGIC_BOARD_PRIVATE__::LevelNamePatch(*patch);

				Main(*patch);
			});
		delete patch;
		break;
	}
	case DLL_PROCESS_DETACH:
		delete InitPatch::gHook;
		break;
	}
	return TRUE;
}