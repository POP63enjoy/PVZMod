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
		MUSIC_TUNE_NONE = -1,
		MUSIC_TUNE_DAY_GRASSWALK,
		MUSIC_TUNE_NIGHT_MOONGRAINS,
		MUSIC_TUNE_POOL_WATERYGRAVES,
		MUSIC_TUNE_FOG_RIGORMORMIST,
		MUSIC_TUNE_ROOF_GRAZETHEROOF,
		MUSIC_TUNE_CHOOSE_YOUR_SEEDS,
		MUSIC_TUNE_TITLE_CRAZY_DAVE_MAIN_THEME,
		MUSIC_TUNE_ZEN_GARDEN,
		MUSIC_TUNE_PUZZLE_CEREBRAWL,
		MUSIC_TUNE_MINIGAME_LOONBOON,
		MUSIC_TUNE_CONVEYER,
		MUSIC_TUNE_FINAL_BOSS_BRAINIAC_MANIAC,
		MUSIC_TUNE_CREDITS_ZOMBIES_ON_YOUR_LAWN,
		NUM_MUSIC_TUNES,
	};

	enum MusicFile
	{
		MUSIC_FILE_NONE = -1,
		MUSIC_FILE_MAIN_MUSIC,
		MUSIC_FILE_DRUMS,
		MUSIC_FILE_HIHATS,
		MUSIC_FILE_CREDITS_ZOMBIES_ON_YOUR_LAWN,
		NUM_MUSIC_FILES,
	};

	enum MusicBurstState
	{
		MUSIC_BURST_OFF,
		MUSIC_BURST_STARTING,
		MUSIC_BURST_ON,
		MUSIC_BURST_FINISHING,
	};

	enum MusicDrumsState
	{
		MUSIC_DRUMS_OFF,
		MUSIC_DRUMS_ON_QUEUED,
		MUSIC_DRUMS_ON,
		MUSIC_DRUMS_OFF_QUEUED,
		MUSIC_DRUMS_FADING,
	};

	/// ����Ϸ�ࡿ���ֿ����ࡣ��ԭ `::%Music`��
	class Music
	{
	public:
		LawnApp*			mApp;
		MusicInterface*		mMusicInterface;
		MusicTune			mCurMusicTune;
		MusicFile			mCurMusicFileMain;
		MusicFile			mCurMusicFileDrums;
		MusicFile			mCurMusicFileHihats;
		int					mBurstOverride;
		int					mBaseBPM;
		int					mBaseModSpeed;
		MusicBurstState		mMusicBurstState;
		int					mBurstStateCounter;
		MusicDrumsState		mMusicDrumsState;
		int					mQueuedDrumTrackPackedOrder;
		int					mDrumsStateCounter;
		int					mPauseOffset;
		int					mPauseOffsetDrums;
		bool				mPaused;
		bool				mMusicDisabled;
		int					mFadeOutCounter;
		int					mFadeOutDuration;

	public:
		Music();

		bool		TodLoadMusic(MusicFile theMusicFile, const String& theFileName);
		void		LoadSong(MusicFile theMusicFile, const String& theFileName);
		HMUSIC		GetBassMusicHandle(MusicFile theMusicFile);
		void		PlayMusic(MusicTune theMusicTune, int theOffset, int theDrumsOffset);
		void		MakeSureMusicIsPlaying(MusicTune theMusicTune);
		void		StopAllMusic();
		void		PlayFromOffset(MusicFile theMusicFile, int theOffset, double theVolume);
	};

	static_assert(sizeof(Music) == 0x4c);
}

#endif // !_PVZMOD_MUSIC_H_
