#pragma once
#ifndef _PVZMOD_MUSIC_INTERFACE_H_
#define _PVZMOD_MUSIC_INTERFACE_H_

#include "SexyCommon.h"

namespace PVZMod
{
	/// 【游戏类】基本音乐接口。（原 Sexy::MusicInterface）
	class MusicInterface
	{
	public:

	public:
		MusicInterface();
		virtual ~MusicInterface();

		virtual bool			LoadMusic(int theSongId, const String& theFileName);
		virtual void			PlayMusic(int theSongId, int theOffset = 0, bool noLoop = false);
		virtual void			StopMusic(int theSongId);
		virtual void			PauseMusic(int theSongId);
		virtual void			ResumeMusic(int theSongId);
		virtual void			StopAllMusic();

		virtual void			UnloadMusic(int theSongId);
		virtual void			UnloadAllMusic();
		virtual void			PauseAllMusic();
		virtual void			ResumeAllMusic();

		virtual void			FadeIn(int theSongId, int theOffset = -1, double theSpeed = 0.002, bool noLoop = false);
		virtual void			FadeOut(int theSongId, bool stopSong = true, double theSpeed = 0.004);
		virtual void			FadeOutAll(bool stopSong = true, double theSpeed = 0.004);
		virtual void			SetSongVolume(int theSongId, double theVolume);
		virtual void			SetSongMaxVolume(int theSongId, double theMaxVolume);
		virtual bool			IsPlaying(int theSongId);

		virtual void			SetVolume(double theVolume);
		virtual void			SetMusicAmplify(int theSongId, double theAmp);
		virtual void			Update();
	};
}

#endif // !_PVZMOD_MUSIC_INTERFACE_H_
