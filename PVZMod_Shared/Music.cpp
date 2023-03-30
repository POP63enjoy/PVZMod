#include "Music.h"
#include "BassLoader.h"
#include "LawnApp.h"

using namespace PVZMod;

Music::Music()
{
	mApp = gLawnApp;
	mMusicInterface = mApp->mMusicInterface;
	mCurMusicTune = MUSIC_TUNE_NONE;
	mCurMusicFileMain = MUSIC_FILE_NONE;
	mCurMusicFileDrums = MUSIC_FILE_NONE;
	mCurMusicFileHihats = MUSIC_FILE_NONE;
	mBurstOverride = -1;
	mMusicDrumsState = MUSIC_DRUMS_OFF;
	mQueuedDrumTrackPackedOrder = -1;
	mBaseBPM = 155;
	mBaseModSpeed = 3;
	mMusicBurstState = MUSIC_BURST_OFF;
	mPauseOffset = 0;
	mPauseOffsetDrums = 0;
	mPaused = false;
	mMusicDisabled = false;
	mFadeOutCounter = 0;
	mFadeOutDuration = 0;
}

bool Music::TodLoadMusic(MusicFile theMusicFile, const String& theFileName)
{
	int func = 0x45d910;
	bool result;
	__asm
	{
		push theFileName
		push theMusicFile
		push this
		call func
		mov result, al
	}
	return result;
};

void Music::LoadSong(MusicFile theMusicFile, const String& theFileName)
{
	if (TodLoadMusic(theMusicFile, theFileName))
	{
		gBass->BASS_MusicSetAttribute(GetBassMusicHandle(theMusicFile), 2, 4);
	}
	else
	{
		mMusicDisabled = true;
	}
}

HMUSIC Music::GetBassMusicHandle(MusicFile theMusicFile)
{
	int func = 0x45E270;
	HMUSIC result;
	__asm
	{
		mov eax,theMusicFile
		mov ecx,this
		call func
		mov result, eax
	}
	return result;
}

void Music::PlayMusic(MusicTune theMusicTune, int theOffset, int theDrumsOffset)
{
	int func = 0x45E400;
	__asm
	{
		mov esi, this
		mov ecx, theMusicTune
		mov eax, theDrumsOffset
		mov edx, theOffset
		call func
	}
}

void Music::MakeSureMusicIsPlaying(MusicTune theMusicTune)
{
	if (mCurMusicTune != theMusicTune)
	{
		StopAllMusic();
		PlayMusic(theMusicTune, -1, -1);
	}
}

void Music::StopAllMusic()
{
	int func = 0x45E200;
	__asm
	{
		mov esi, this
		call func
	}
}

void Music::PlayFromOffset(MusicFile theMusicFile, int theOffset, double theVolume)
{
	int func = 0x45e2c0;
	__asm
	{
		sub esp, 0x8
		fld qword ptr ds:theVolume
		fstp qword ptr ds:[esp]
		push theOffset
		push theMusicFile
		push this
		call func
	};
}