#pragma once
#ifndef _PVZMOD_MAGIC_MUSIC_H_
#define _PVZMOD_MAGIC_MUSIC_H_

#include "Magic.h"

namespace PVZMod
{
	enum MusicTune;
	class Music;
	class InitPatch;

	/// Music 魔法成员扩展。
	/// 
	/// @see MagicMusic_Reference
	namespace MagicMusic
	{
		/// 【补丁函数】为 MagicMusic 扩展魔法成员。
		///
		/// @tparam T		一个继承于 MagicMusic 的类，不允许定义虚函数，可以定义构造函数和析构函数。
		/// @param patch	补丁对象。
		template <typename T>
		void Extend(InitPatch& patch);

		using PlayMusic_t = Magic::BaseFunction<void(Music* _this, MusicTune theMusicTune, int theOffset, int theDrumsOffset)>;
		void Binding_MF_PlayMusic(InitPatch& patch, const std::function<void(Music* _this, MusicTune theMusicTune, int theOffset, int theDrumsOffset, PlayMusic_t& base)>& func);
	}
}

#include "MagicMusic.inl"

#endif // !_PVZMOD_MAGIC_MUSIC_H_
