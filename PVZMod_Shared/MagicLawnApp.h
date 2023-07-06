#pragma once
#ifndef _PVZMOD_MAGIC_LAWN_APP_H_
#define _PVZMOD_MAGIC_LAWN_APP_H_

#ifndef _PVZMOD_LAWN_APP_H_
#error 必须在 #include <MagicLawnApp.h> 之前 #include <LawnApp.h> 。
#endif // !_PVZMOD_LAWN_APP_H_


#include "Magic.h"

namespace PVZMod
{
	class LawnApp;
	class InitPatch;

	/// `LawnApp` 魔法成员扩展。
	namespace MagicLawnApp
	{
		/// 【补丁函数】为 LawnApp 扩展魔法成员。
		///
		/// @tparam T		一个继承于 LawnApp 的类，不允许定义构造函数、析构函数、虚函数。
		/// @param patch	补丁对象。
		template <typename T>
		void RegisterMain(InitPatch& patch);

		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////

		// 构造函数和析构函数 - MF_Constructor、MF_Destructor

		using Constructor_t = Magic::BaseFunction<void(LawnApp* _this)>;
		void Binding_MF_Constructor(InitPatch& patch, const std::function<void(LawnApp* _this, Constructor_t& base)>& func);

		using Destructor_t = Magic::BaseFunction<void(LawnApp* _this)>;
		void Binding_MF_Destructor(InitPatch& patch, const std::function<void(LawnApp* _this, Destructor_t& base)>& func);

		// 初始化与释放 - MF_Init、MF_LoadingThreadProc、MF_LoadingCompleted、MF_Shutdown

		using Init_t = Magic::BaseFunction<void(LawnApp* _this)>;
		void Binding_MF_Init(InitPatch& patch, const std::function<void(LawnApp* _this, Init_t& base)>& func);

		using LoadingThreadProc_t = Magic::BaseFunction<void(LawnApp* _this)>;
		void Binding_MF_LoadingThreadProc(InitPatch& patch, const std::function<void(LawnApp* _this, LoadingThreadProc_t& base)>& func);

		using LoadingCompleted_t = Magic::BaseFunction<void(LawnApp* _this)>;
		void Binding_MF_LoadingCompleted(InitPatch& patch, const std::function<void(LawnApp* _this, LoadingCompleted_t& base)>& func);

		using Shutdown_t = Magic::BaseFunction<void(LawnApp* _this)>;
		void Binding_MF_Shutdown(InitPatch& patch, const std::function<void(LawnApp* _this, Shutdown_t& base)>& func);

		// 游戏窗口消息处理 - MF_WindowProc

		using WindowProc_t = Magic::BaseFunction<LRESULT(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)>;
		void Binding_MF_WindowProc(InitPatch& patch, const std::function<LRESULT(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, WindowProc_t& base)>& func);

		// 全局对话框 - MC_NUM_DIALOGS、MF_DialogButtonDepress

		void Binding_MC_NUM_DIALOGS(InitPatch& patch, int theNumDialogs);

		using DialogButtonDepress_t = Magic::BaseFunction<void(LawnApp* _this, int theId, bool isYes)>;
		void Binding_MF_DialogButtonDepress(InitPatch& patch, const std::function<void(LawnApp* _this, int theId, bool isYes, DialogButtonDepress_t& base)>& func);

		// 关卡名称

		using GetLevelName_t = Magic::BaseFunction<SexyString(LawnApp* _this, GameMode theLevelId)>;
		void Binding_MF_GetLevelName(InitPatch& patch, const std::function<SexyString(LawnApp* _this, GameMode theLevelId, GetLevelName_t& base)>& func);

		// 各种补丁

		void Binding_mvExclusiveFullscreen(InitPatch& patch, bool& exclusiveFullscreen);
		void Binding_mvAutoFixAspectRatio(InitPatch& patch, bool& autoFixAspectRatio);
		void Binding_mvWindowCanResize(InitPatch& patch, bool& windowCanResize);
	}
}

#include "MagicLawnApp.inl"

#endif	// !_PVZMOD_MAGIC_LAWN_APP_H_
