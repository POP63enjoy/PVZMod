#pragma once
#ifndef _PVZMOD_GAME_UI_PATCH_H_
#define _PVZMOD_GAME_UI_PATCH_H_

namespace PVZMod
{
	class InitPatch;

	/// 游戏界面相关补丁。
	namespace GameUIPatch
	{
		/// 【补丁函数】替换主菜单。
		/// 
		/// @tparam T		一个继承于 GameSelector 的类，可以定义构造函数和析构函数，可以重写虚函数。
		/// @param patch	补丁对象。
		template<typename T>
		void ReplaceGameSelector(InitPatch& patch);

		/// 【补丁函数】替换标题界面。
		/// 
		/// @tparam T		一个继承于 TitleScreen 的类，可以定义构造函数和析构函数，可以重写虚函数。
		/// @param patch	补丁对象。
		template<typename T>
		void ReplaceTitleScreen(InitPatch& patch);

		/// 【补丁函数】替换选关界面。
		/// 
		/// @tparam T		一个继承于 ChallengeScreen 的类，可以定义构造函数和析构函数，可以重写虚函数。
		/// @param patch	补丁对象。
		template<typename T>
		void ReplaceChallengeScreen(InitPatch& patch);
	}
}

#include "GameUIPatch.inl"

#endif // !_PVZMOD_GAME_UI_PATCH_H_
