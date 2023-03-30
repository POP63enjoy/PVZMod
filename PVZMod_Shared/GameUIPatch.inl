#pragma once
#ifndef _PVZMOD_GAME_UI_PATCH_INL_
#define _PVZMOD_GAME_UI_PATCH_INL_

#include "PVZMod.h"
#include "GameUIPatch.h"

namespace PVZMod
{
	class LawnApp;
	class GameSelector;
	class TitleScreen;
	class ChallengeScreen;

	enum ChallengePage;

	template<typename T>
	void GameUIPatch::ReplaceGameSelector(InitPatch& patch)
	{
		static_assert(std::is_base_of<GameSelector, T>::value);
		patch.PatchTask("GameUIPatch::ReplaceGameSelector", [&]
			{
				*(int*)0x45275a = sizeof(T);
				patch.mHook.InsertCodeAndJump((void*)0x452780, (void*)0x45278b, [](Hook::Regs* regs)
					{
						LawnApp* theApp = (LawnApp*)regs->edi;
						T* _this = (T*)regs->eax;
						new(_this)T(theApp);
					});
			}, true, true);
	};

	template<typename T>
	void GameUIPatch::ReplaceTitleScreen(InitPatch& patch)
	{
		static_assert(std::is_base_of<TitleScreen, T>::value);
		patch.PatchTask("GameUIPatch::ReplaceTitleScreen", [&]
			{
				*(int*)0x454bb7 = sizeof(T);
				patch.mHook.InsertCodeAndJump((void*)0x454bd3, (void*)0x454bde, [](Hook::Regs* regs)
					{
						LawnApp* theApp = (LawnApp*)regs->ebp;
						T* _this = (T*)regs->eax;
						new(_this)T(theApp);
					});
			}, true, true);
	}

	template<typename T>
	void GameUIPatch::ReplaceChallengeScreen(InitPatch& patch)
	{
		static_assert(std::is_base_of<ChallengeScreen, T>::value);
		patch.PatchTask("GameUIPatch::ReplaceChallengeScreen", [&]
			{
				*(int*)0x441e6f = sizeof(T);
				*(int*)0x452a77 = sizeof(T);
			
				T* (__stdcall * func)(T * _this, LawnApp * theApp, ChallengePage thePage) = [](T* _this, LawnApp* theApp, ChallengePage thePage)
				{
					return new(_this)T(theApp, thePage);
				};

				patch.mHook.HookFunction((void*)0x42F780, func);
			});
	}
}

#endif // !_PVZMOD_GAME_UI_PATCH_INL_
