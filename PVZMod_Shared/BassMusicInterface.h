#pragma once
#ifndef _PVZMOD_BASS_MUSIC_INTERFACE_H_
#define _PVZMOD_BASS_MUSIC_INTERFACE_H_

#include "MusicInterface.h"
#include "bass.h"

namespace PVZMod
{
	/// 【游戏类】bass.dll 音乐信息。（原 Sexy::BassMusicInfo）
	class BassMusicInfo
	{
	public:
		HMUSIC					mHMusic;
		HSTREAM					mHStream;
		double					mVolume;
		double					mVolumeAdd;
		double					mVolumeCap;
		bool					mStopOnFade;

	public:
		BassMusicInfo();

		DWORD GetHandle() { return mHMusic ? mHMusic : mHStream; }
	};

	typedef Map<int, BassMusicInfo> BassMusicMap;

	/// 【游戏类】bass.dll 音乐接口。（原 Sexy::BassMusicInterface）
	class BassMusicInterface : public MusicInterface
	{
	public:
		BassMusicMap			mMusicMap;
		int						mMaxMusicVolume;
		int						mMusicLoadFlags;

	public:
		BassMusicInterface(HWND theHWnd);
		virtual ~BassMusicInterface();

		virtual bool			LoadMusic(int theSongId, const std::string& theFileName);
		virtual void			PlayMusic(int theSongId, int theOffset = 0, bool noLoop = false);
		virtual void			StopMusic(int theSongId);
		virtual void			StopAllMusic();
		virtual void			UnloadMusic(int theSongId);
		virtual void			UnloadAllMusic();
		virtual void			PauseAllMusic();
		virtual void			ResumeAllMusic();
		virtual void			PauseMusic(int theSongId);
		virtual void			ResumeMusic(int theSongId);
		virtual void			FadeIn(int theSongId, int theOffset = -1, double theSpeed = 0.002, bool noLoop = false);
		virtual void			FadeOut(int theSongId, bool stopSong = true, double theSpeed = 0.004);
		virtual void			FadeOutAll(bool stopSong = true, double theSpeed = 0.004);
		virtual void			SetSongVolume(int theSongId, double theVolume);
		virtual void			SetSongMaxVolume(int theSongId, double theMaxVolume);
		virtual bool			IsPlaying(int theSongId);

		virtual void			SetVolume(double theVolume);
		virtual void			SetMusicAmplify(int theSongId, double theAmp); // default is 0.50
		virtual void			Update();

		// functions for dealing with MODs
		int						GetMusicOrder(int theSongId);
	};

	static_assert(sizeof(BassMusicInterface) == 0x18);
}

#endif // !_PVZMOD_BASS_MUSIC_INTERFACE_H_
