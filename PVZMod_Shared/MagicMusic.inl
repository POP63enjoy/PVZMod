#pragma once
#ifndef _PVZMOD_MAGIC_MUSIC_INL_
#define _PVZMOD_MAGIC_MUSIC_INL_

namespace PVZMod
{
	class Music;

	namespace MagicMusic
	{
		namespace __PRIVATE__
		{
			PVZMOD_CHECK_MAGIC_FUNC(MF_PlayMusic);
		}

		template<typename T>
		void RegisterMain(InitPatch& patch)
		{
			static_assert(std::is_base_of<Music, T>::value);
			patch.PatchTask("MagicMusic::RegisterMain", [&]
				{
					using namespace __PRIVATE__;

					patch.mHook.InsertCode((void*)0x454c3b, [](Hook::Regs* regs)
						{
							*(size_t*)regs->esp = sizeof(T);
						});
					patch.mHook.InsertCodeAndJump((void*)0x454c47, (void*)0x454c50, [](Hook::Regs* regs)
						{
							new((void*)regs->eax) T;
						});
					patch.mHook.InsertCodeAndJump((void*)0x451cc2, (void*)0x451cc8, [](Hook::Regs* regs)
						{
							delete (T*)regs->eax;
						});

					PVZMOD_GENERAL_MAGIC_FUNC(MF_PlayMusic, void(MusicTune theMusicTune, int theOffset, int theDrumsOffset, PlayMusic_t& base), T);
				}, true, true);
		}
	}
}

#endif // !_PVZMOD_MAGIC_MUSIC_INL_
