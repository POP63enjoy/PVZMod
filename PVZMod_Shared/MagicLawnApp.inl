#pragma once
#ifndef _PVZMOD_MAGIC_LAWN_APP_INL_
#define _PVZMOD_MAGIC_LAWN_APP_INL_

namespace PVZMod
{
	namespace MagicLawnApp
	{
		namespace __PRIVATE__
		{
			PVZMOD_CHECK_MAGIC_FUNC(MF_Constructor);
			PVZMOD_CHECK_MAGIC_FUNC(MF_Destructor);

			PVZMOD_CHECK_MAGIC_FUNC(MF_Init);
			PVZMOD_CHECK_MAGIC_FUNC(MF_LoadingThreadProc);
			PVZMOD_CHECK_MAGIC_FUNC(MF_LoadingCompleted);
			PVZMOD_CHECK_MAGIC_FUNC(MF_Shutdown);
			PVZMOD_CHECK_MAGIC_FUNC(MF_WindowProc);

			PVZMOD_CHECK_MAGIC_VAR(MC_NUM_DIALOGS);
			PVZMOD_CHECK_MAGIC_FUNC(MF_DialogButtonDepress);

			PVZMOD_CHECK_MAGIC_VAR(mvExclusiveFullscreen);
			PVZMOD_CHECK_MAGIC_VAR(mvAutoFixAspectRatio);
			PVZMOD_CHECK_MAGIC_VAR(mvWindowCanResize);
		}
		
		template <typename T>
		void RegisterMain(InitPatch& patch)
		{
			static_assert(std::is_base_of<LawnApp, T>::value);
			patch.PatchTask("MagicLawnApp::RegisterMain", [&]
				{
					using namespace __PRIVATE__;

					*(int*)0x4516ef = sizeof(T);

					PVZMOD_MAGIC_FUNC(MF_Constructor, void(Constructor_t & base), T,
						{
							Binding_MF_Constructor(patch, [](LawnApp* _this, Constructor_t& base)
								{
									((T*)_this)->MF_Constructor(base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_Destructor, void(Destructor_t & base), T,
						{
							Binding_MF_Destructor(patch, [](LawnApp* _this, Destructor_t& base)
								{
									((T*)_this)->MF_Destructor(base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_Init, void(Init_t & base), T,
						{
							Binding_MF_Init(patch, [](LawnApp* _this, Init_t& base)
								{
									((T*)_this)->MF_Init(base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_LoadingThreadProc, void(LoadingThreadProc_t & base), T,
						{
							Binding_MF_LoadingThreadProc(patch, [](LawnApp* _this, LoadingThreadProc_t& base)
								{
									((T*)_this)->MF_LoadingThreadProc(base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_LoadingCompleted, void(LoadingCompleted_t & base), T,
						{
							Binding_MF_LoadingCompleted(patch, [](LawnApp* _this, LoadingCompleted_t& base)
								{
									((T*)_this)->MF_LoadingCompleted(base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_Shutdown, void(Shutdown_t & base), T,
						{
							Binding_MF_Shutdown(patch, [](LawnApp* _this, Shutdown_t& base)
								{
									((T*)_this)->MF_Shutdown(base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_WindowProc, LRESULT(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, WindowProc_t & base), T,
						{
							Binding_MF_WindowProc(patch, [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, WindowProc_t& base)
								{
									return ((T*)gLawnApp)->MF_WindowProc(hwnd, uMsg, wParam, lParam, base);
								});
						});

					PVZMOD_MAGIC_SVAR(MC_NUM_DIALOGS, const int, T,
						{
							static_assert(T::MC_NUM_DIALOGS >= NUM_DIALOGS && T::MC_NUM_DIALOGS < 1000);
							Binding_MC_NUM_DIALOGS(patch, T::MC_NUM_DIALOGS, "The range of MC_NUM_DIALOGS must be [NUM_DIALOGS,1000).");
						});

					PVZMOD_MAGIC_FUNC(MF_DialogButtonDepress, void(int theId, bool isYes, DialogButtonDepress_t & base), T,
						{
							Binding_MF_DialogButtonDepress(patch, [](LawnApp* _this, int theId, bool isYes, DialogButtonDepress_t& base)
								{
									return ((T*)_this)->MF_DialogButtonDepress(theId, isYes, base);
								});
						});

					PVZMOD_MAGIC_SVAR(mvExclusiveFullscreen, bool, T,
						{
							Binding_mvExclusiveFullscreen(patch, T::mvExclusiveFullscreen);
						});

					PVZMOD_MAGIC_SVAR(mvAutoFixAspectRatio, bool, T,
						{
							Binding_mvAutoFixAspectRatio(patch, T::mvAutoFixAspectRatio);
						});

					PVZMOD_MAGIC_SVAR(mvWindowCanResize, bool, T,
						{
							Binding_mvWindowCanResize(patch, T::mvWindowCanResize);
						});
				}, true, true);
		}
	}
}

#endif	// !_PVZMOD_MAGIC_LAWN_APP_INL_
