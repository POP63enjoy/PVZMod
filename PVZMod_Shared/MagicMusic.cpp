#include "PVZMod.h"
#include "MagicMusic.h"
#include "Music.h"
#include <cassert>

using namespace PVZMod;

// ≤•∑≈“Ù¿÷ - MF_PlayMusic

void MagicMusic::Binding_MF_PlayMusic(InitPatch& patch, const std::function<void(Music* _this, MusicTune theMusicTune, int theOffset, int theDrumsOffset, PlayMusic_t& base)>& func)
{
	patch.PatchTask("MagicMusic::Binding_MF_PlayMusic", [&]
		{
			static auto _func = func;

			memset((void*)0x45dc7b, 0x90, 7);
			*(char*)0x45e2a6 = '\xeb';

			patch.mHook.InsertCodeAndJump((void*)0x45e438, (void*)0x45e6d0, [](Hook::Regs* regs)
				{
					PlayMusic_t base;

					base.mFunction = [](Music* _this, MusicTune theMusicTune, int theOffset, int theDrumsOffset)
					{
						switch (theMusicTune)
						{
						case MUSIC_TUNE_DAY_GRASSWALK:
							_this->mCurMusicFileMain = MUSIC_FILE_MAIN_MUSIC;
							_this->mCurMusicFileDrums = MUSIC_FILE_DRUMS;
							_this->mCurMusicFileHihats = MUSIC_FILE_HIHATS;
							if (theOffset == -1)
								theOffset = 0;
							_this->PlayFromOffset(_this->mCurMusicFileMain, theOffset, 1.0);
							_this->PlayFromOffset(_this->mCurMusicFileDrums, theOffset, 0.0);
							_this->PlayFromOffset(_this->mCurMusicFileHihats, theOffset, 0.0);
							break;

						case MUSIC_TUNE_NIGHT_MOONGRAINS:
							_this->mCurMusicFileMain = MUSIC_FILE_MAIN_MUSIC;
							_this->mCurMusicFileDrums = MUSIC_FILE_DRUMS;
							if (theOffset == -1)
							{
								theOffset = 0x80000030;
								theDrumsOffset = 0x8000005C;
							}
							_this->PlayFromOffset(_this->mCurMusicFileMain, theOffset, 1.0);
							_this->PlayFromOffset(_this->mCurMusicFileDrums, theDrumsOffset, 0.0);
							break;

						case MUSIC_TUNE_POOL_WATERYGRAVES:
							_this->mCurMusicFileMain = MUSIC_FILE_MAIN_MUSIC;
							_this->mCurMusicFileDrums = MUSIC_FILE_DRUMS;
							_this->mCurMusicFileHihats = MUSIC_FILE_HIHATS;
							if (theOffset == -1)
								theOffset = 0x8000005E;
							_this->PlayFromOffset(_this->mCurMusicFileMain, theOffset, 1.0);
							_this->PlayFromOffset(_this->mCurMusicFileDrums, theOffset, 0.0);
							_this->PlayFromOffset(_this->mCurMusicFileHihats, theOffset, 0.0);
							break;

						case MUSIC_TUNE_FOG_RIGORMORMIST:
							_this->mCurMusicFileMain = MUSIC_FILE_MAIN_MUSIC;
							_this->mCurMusicFileDrums = MUSIC_FILE_DRUMS;
							_this->mCurMusicFileHihats = MUSIC_FILE_HIHATS;
							if (theOffset == -1)
								theOffset = 0x8000007D;
							_this->PlayFromOffset(_this->mCurMusicFileMain, theOffset, 1.0);
							_this->PlayFromOffset(_this->mCurMusicFileDrums, theOffset, 0.0);
							_this->PlayFromOffset(_this->mCurMusicFileHihats, theOffset, 0.0);
							break;

						case MUSIC_TUNE_ROOF_GRAZETHEROOF:
							_this->mCurMusicFileMain = MUSIC_FILE_MAIN_MUSIC;
							_this->mCurMusicFileDrums = MUSIC_FILE_DRUMS;
							_this->mCurMusicFileHihats = MUSIC_FILE_HIHATS;
							if (theOffset == -1)
								theOffset = 0x8000008B;
							_this->PlayFromOffset(_this->mCurMusicFileMain, theOffset, 1.0);
							_this->PlayFromOffset(_this->mCurMusicFileDrums, theOffset, 0.0);
							_this->PlayFromOffset(_this->mCurMusicFileHihats, theOffset, 0.0);
							break;

						case MUSIC_TUNE_CHOOSE_YOUR_SEEDS:
							_this->mCurMusicFileMain = MUSIC_FILE_MAIN_MUSIC;
							if (theOffset == -1)
								theOffset = 0x8000007A;
							_this->PlayFromOffset(_this->mCurMusicFileMain, theOffset, 1.0);
							break;

						case MUSIC_TUNE_TITLE_CRAZY_DAVE_MAIN_THEME:
							_this->mCurMusicFileMain = MUSIC_FILE_MAIN_MUSIC;
							if (theOffset == -1)
								theOffset = 0x80000098;
							_this->PlayFromOffset(_this->mCurMusicFileMain, theOffset, 1.0);
							break;

						case MUSIC_TUNE_ZEN_GARDEN:
							_this->mCurMusicFileMain = MUSIC_FILE_MAIN_MUSIC;
							if (theOffset == -1)
								theOffset = 0xDD;
							_this->PlayFromOffset(_this->mCurMusicFileMain, theOffset, 1.0);
							break;

						case MUSIC_TUNE_PUZZLE_CEREBRAWL:
							_this->mCurMusicFileMain = MUSIC_FILE_MAIN_MUSIC;
							if (theOffset == -1)
								theOffset = 0xB1;
							_this->PlayFromOffset(_this->mCurMusicFileMain, theOffset, 1.0);
							break;

						case MUSIC_TUNE_MINIGAME_LOONBOON:
							_this->mCurMusicFileMain = MUSIC_FILE_MAIN_MUSIC;
							if (theOffset == -1)
								theOffset = 0xA6;
							_this->PlayFromOffset(_this->mCurMusicFileMain, theOffset, 1.0);
							break;

						case MUSIC_TUNE_CONVEYER:
							_this->mCurMusicFileMain = MUSIC_FILE_MAIN_MUSIC;
							if (theOffset == -1)
								theOffset = 0xD4;
							_this->PlayFromOffset(_this->mCurMusicFileMain, theOffset, 1.0);
							break;

						case MUSIC_TUNE_FINAL_BOSS_BRAINIAC_MANIAC:
							_this->mCurMusicFileMain = MUSIC_FILE_MAIN_MUSIC;
							if (theOffset == -1)
								theOffset = 0x9E;
							_this->PlayFromOffset(_this->mCurMusicFileMain, theOffset, 1.0);
							break;

						case MUSIC_TUNE_CREDITS_ZOMBIES_ON_YOUR_LAWN:
							_this->mCurMusicFileMain = MUSIC_FILE_CREDITS_ZOMBIES_ON_YOUR_LAWN;
							if (theOffset == -1)
								theOffset = 0;
							_this->PlayFromOffset(_this->mCurMusicFileMain, theOffset, 1.0);
							break;

						default:
							assert(false);
							break;
						}
					};
					base.mDefaultFunction = [&] { return base((Music*)regs->esi, (MusicTune)regs->ecx, regs->edi, regs->ebx); };

					_func((Music*)regs->esi, (MusicTune)regs->ecx, regs->edi, regs->ebx, base);
				});
		}, true, true);
}
