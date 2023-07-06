#pragma once
#ifndef _PVZMOD_MAGIC_MUSIC_H_
#define _PVZMOD_MAGIC_MUSIC_H_

#include "Magic.h"

namespace PVZMod
{
	enum MusicTune;
	class Music;
	class InitPatch;

	/// `Music` ħ����Ա��չ��
	namespace MagicMusic
	{
		/// ������������Ϊ MagicMusic ��չħ����Ա��
		///
		/// @tparam T		һ���̳��� MagicMusic ���࣬���������麯�������Զ��幹�캯��������������
		/// @param patch	��������
		template <typename T>
		void RegisterMain(InitPatch& patch);

		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////

		// �������� - MF_PlayMusic

		using PlayMusic_t = Magic::BaseFunction<void(Music* _this, MusicTune theMusicTune, int theOffset, int theDrumsOffset)>;
		void Binding_MF_PlayMusic(InitPatch& patch, const std::function<void(Music* _this, MusicTune theMusicTune, int theOffset, int theDrumsOffset, PlayMusic_t& base)>& func);
	}
}

#include "MagicMusic.inl"

#endif // !_PVZMOD_MAGIC_MUSIC_H_
