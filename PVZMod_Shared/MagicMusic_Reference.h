#pragma once

#error 本文件仅用于参考，不要包含

#include "MagicMusic.h"
#include "Music.h"

namespace PVZMod
{
	/// MagicMusic 魔法成员参考。
	///
	/// 本类用于参考 MagicMusic 魔法成员的定义方式和用法，不要直接使用本类。
	class MagicMusic_Reference :public Music
	{
	public:
		/// 构造函数。
		MagicMusic_Reference();

		/// 析构函数。
		~MagicMusic_Reference();

		/// 播放音乐。
		///
		/// @param theMusicTune		音乐编号。
		/// @param theOffset		音乐进度，为 -1 则从头播放。
		/// @param theDrumsOffset	鼓音轨进度。
		/// @param base				原始函数。
		void MF_PlayMusic(MusicTune theMusicTune, int theOffset, int theDrumsOffset, MagicMusic::PlayMusic_t& base);
	};
}