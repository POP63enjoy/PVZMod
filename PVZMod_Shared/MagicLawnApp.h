#pragma once
#ifndef _PVZMOD_MAGIC_LAWN_APP_H_
#define _PVZMOD_MAGIC_LAWN_APP_H_

#ifndef _PVZMOD_LAWN_APP_H_
#error ������ #include <MagicLawnApp.h> ֮ǰ #include <LawnApp.h> ��
#endif // !_PVZMOD_LAWN_APP_H_


#include "Magic.h"

namespace PVZMod
{
	class LawnApp;
	class InitPatch;

	/// LawnApp ħ����Ա��չ��
	/// 
	/// @see MagicLawnApp_Reference
	namespace MagicLawnApp
	{
		/// ������������Ϊ LawnApp ��չħ����Ա��
		///
		/// @tparam T		һ���̳��� LawnApp ���࣬���������幹�캯���������������麯����
		/// @param patch	��������
		template <typename T>
		void Extend(InitPatch& patch);

		using Constructor_t = Magic::BaseFunction<void(LawnApp* _this)>;
		void Binding_MF_Constructor(InitPatch& patch, const std::function<void(LawnApp* _this, Constructor_t& base)>& func);

		using Destructor_t = Magic::BaseFunction<void(LawnApp* _this)>;
		void Binding_MF_Destructor(InitPatch& patch, const std::function<void(LawnApp* _this, Destructor_t& base)>& func);

		using Init_t = Magic::BaseFunction<void(LawnApp* _this)>;
		void Binding_MF_Init(InitPatch& patch, const std::function<void(LawnApp* _this, Init_t& base)>& func);

		using LoadingThreadProc_t = Magic::BaseFunction<void(LawnApp* _this)>;
		void Binding_MF_LoadingThreadProc(InitPatch& patch, const std::function<void(LawnApp* _this, LoadingThreadProc_t& base)>& func);

		using LoadingCompleted_t = Magic::BaseFunction<void(LawnApp* _this)>;
		void Binding_MF_LoadingCompleted(InitPatch& patch, const std::function<void(LawnApp* _this, LoadingCompleted_t& base)>& func);

		using Shutdown_t = Magic::BaseFunction<void(LawnApp* _this)>;
		void Binding_MF_Shutdown(InitPatch& patch, const std::function<void(LawnApp* _this, Shutdown_t& base)>& func);

		using WindowProc_t = Magic::BaseFunction<LRESULT(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)>;
		void Binding_MF_WindowProc(InitPatch& patch, const std::function<LRESULT(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, WindowProc_t& base)>& func);

		void Binding_MC_NUM_DIALOGS(InitPatch& patch, int theNumDialogs);

		using DialogButtonDepress_t = Magic::BaseFunction<void(LawnApp* _this, int theId, bool isYes)>;
		void Binding_MF_DialogButtonDepress(InitPatch& patch, const std::function<void(LawnApp* _this, int theId, bool isYes, DialogButtonDepress_t& base)>& func);

		void Binding_mvExclusiveFullscreen(InitPatch& patch, bool& exclusiveFullscreen);
		void Binding_mvAutoFixAspectRatio(InitPatch& patch, bool& autoFixAspectRatio);
		void Binding_mvWindowCanResize(InitPatch& patch, bool& windowCanResize);
	}
}

#include "MagicLawnApp.inl"

#endif	// !_PVZMOD_MAGIC_LAWN_APP_H_