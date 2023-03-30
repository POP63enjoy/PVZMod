#pragma once
#ifndef _PVZMOD_MUSIC_H_
#define _PVZMOD_MUSIC_H_

#include "SexyCommon.h"
#include "bass.h"
#include "PakInterface.h"
#include "BassMusicInterface.h"

namespace PVZMod
{
	class LawnApp;
	class BassMusicInterface;

	enum MusicTune
	{
		MUSIC_TUNE_NONE = 0xFFFFFFFF,
		MUSIC_TUNE_DAY_GRASSWALK = 0x1,
		MUSIC_TUNE_NIGHT_MOONGRAINS = 0x2,
		MUSIC_TUNE_POOL_WATERYGRAVES = 0x3,
		MUSIC_TUNE_FOG_RIGORMORMIST = 0x4,
		MUSIC_TUNE_ROOF_GRAZETHEROOF = 0x5,
		MUSIC_TUNE_CHOOSE_YOUR_SEEDS = 0x6,
		MUSIC_TUNE_TITLE_CRAZY_DAVE_MAIN_THEME = 0x7,
		MUSIC_TUNE_ZEN_GARDEN = 0x8,
		MUSIC_TUNE_PUZZLE_CEREBRAWL = 0x9,
		MUSIC_TUNE_MINIGAME_LOONBOON = 0xA,
		MUSIC_TUNE_CONVEYER = 0xB,
		MUSIC_TUNE_FINAL_BOSS_BRAINIAC_MANIAC = 0xC,
		MUSIC_TUNE_CREDITS_ZOMBIES_ON_YOUR_LAWN = 0xD,
		NUM_MUSIC_TUNES = 0xE,
	};

	enum MusicFile
	{
		MUSIC_FILE_NONE = 0xFFFFFFFF,
		MUSIC_FILE_MAIN_MUSIC = 0x1,
		MUSIC_FILE_DRUMS = 0x2,
		MUSIC_FILE_HIHATS = 0x3,
		MUSIC_FILE_CREDITS_ZOMBIES_ON_YOUR_LAWN = 0x4,
		NUM_MUSIC_FILES = 0x5,
	};

	enum MusicBurstState
	{
		MUSIC_BURST_OFF = 0x0,
		MUSIC_BURST_STARTING = 0x1,
		MUSIC_BURST_ON = 0x2,
		MUSIC_BURST_FINISHING = 0x3,
	};

	enum MusicDrumsState
	{
		MUSIC_DRUMS_OFF = 0x0,
		MUSIC_DRUMS_ON_QUEUED = 0x1,
		MUSIC_DRUMS_ON = 0x2,
		MUSIC_DRUMS_OFF_QUEUED = 0x3,
		MUSIC_DRUMS_FADING = 0x4,
	};

	/// 【游戏类】音乐控制类。（原 ::Music）
	class Music
	{
	public:
		LawnApp* mApp;
		MusicInterface* mMusicInterface;
		MusicTune mCurMusicTune;
		MusicFile mCurMusicFileMain;
		MusicFile mCurMusicFileDrums;
		MusicFile mCurMusicFileHihats;
		int mBurstOverride;
		int mBaseBPM;
		int mBaseModSpeed;
		MusicBurstState mMusicBurstState;
		int mBurstStateCounter;
		MusicDrumsState mMusicDrumsState;
		int mQueuedDrumTrackPackedOrder;
		int mDrumsStateCounter;
		int mPauseOffset;
		int mPauseOffsetDrums;
		bool mPaused;
		bool mMusicDisabled;
		int mFadeOutCounter;
		int mFadeOutDuration;

		Music();

		bool TodLoadMusic(MusicFile theMusicFile, const String& theFileName);
		
		void LoadSong(MusicFile theMusicFile, const String& theFileName);
		HMUSIC GetBassMusicHandle(MusicFile theMusicFile);
		void PlayMusic(MusicTune theMusicTune, int theOffset, int theDrumsOffset);
		void MakeSureMusicIsPlaying(MusicTune theMusicTune);
		void StopAllMusic();
		void PlayFromOffset(MusicFile theMusicFile, int theOffset, double theVolume);
	};

	static_assert(sizeof(Music) == 0x4c);
}

#endif // !_PVZMOD_MUSIC_H_
