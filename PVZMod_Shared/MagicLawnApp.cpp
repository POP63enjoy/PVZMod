#include "PVZMod.h"
#define PVZMOD_SEXYAPP_ALL_PUBLIC
#include "LawnApp.h"
#include "MagicLawnApp.h"

#include <cassert>

using namespace PVZMod;

void MagicLawnApp::Binding_MF_Constructor(InitPatch& patch, const std::function<void(LawnApp* _this, Constructor_t& base)>& func)
{
	patch.PatchTask("MagicLawnApp::Binding_MF_Constructor", [&]
		{
			static std::vector<std::function<void(LawnApp* _this, Constructor_t& base)>> func_list;
			patch.PatchTask("MagicLawnApp::Binding_MF_Constructor(Hook)", [&]
				{
					using Raw_t = LawnApp * (__stdcall*)(LawnApp* _this);
					static Raw_t raw;
					Raw_t detour = [](LawnApp* _this)
					{
						Constructor_t base;

						base.mFunction = [&](LawnApp* __this)
						{
							std::swap(_this, __this);
							base();
							_this = __this;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								raw(_this);
							else
							{
								i--;
								func_list[i](_this, base);
								i++;
							}
						};

						func_list.back()(_this, base);
						return _this;
					};
					raw = (Raw_t)patch.mHook.HookFunction((void*)0x451890, detour);
				});
			func_list.push_back(func);
		},false);
}

void MagicLawnApp::Binding_MF_Destructor(InitPatch& patch, const std::function<void(LawnApp* _this, Destructor_t& base)>& func)
{
	patch.PatchTask("MagicLawnApp::Binding_MF_Destructor", [&]
		{
			static std::vector<std::function<void(LawnApp* _this, Destructor_t& base)>> func_list;
			patch.PatchTask("MagicLawnApp::Binding_MF_Destructor(Hook)", [&]
				{
					using Raw_t = void(__fastcall*)(LawnApp* _this);
					static Raw_t raw;
					Raw_t detour = [](LawnApp* _this)
					{
						Destructor_t base;

						base.mFunction = [&](LawnApp* __this)
						{
							std::swap(_this, __this);
							base();
							_this = __this;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								raw(_this);
							else
							{
								i--;
								func_list[i](_this, base);
								i++;
							}
						};

						func_list.back()(_this, base);
					};
					raw = (Raw_t)patch.mHook.HookFunction((void*)0x451bf0, detour);
				});
			func_list.push_back(func);
		}, false);
}

void MagicLawnApp::Binding_MF_Init(InitPatch& patch, const std::function<void(LawnApp* _this, Init_t& base)>& func)
{
	patch.PatchTask("MagicLawnApp::Binding_MF_Init", [&]
		{
			static std::vector<std::function<void(LawnApp* _this, Init_t& base)>> func_list;
			patch.PatchTask("MagicLawnApp::Binding_MF_Init", [&]
				{
					using Raw_t = void(__fastcall*)(LawnApp* _this);
					static Raw_t raw;
					Raw_t detour = [](LawnApp* _this)
					{
						Init_t base;

						base.mFunction = [&](LawnApp* __this)
						{
							std::swap(_this, __this);
							base();
							_this = __this;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								raw(_this);
							else
							{
								i--;
								func_list[i](_this, base);
								i++;
							}
						};

						func_list.back()(_this, base);
					};
					raw = (Raw_t)patch.mHook.HookFunction((void*)0x4547b0, detour);
				});
			func_list.push_back(func);
		}, false);
}

void MagicLawnApp::Binding_MF_LoadingThreadProc(InitPatch& patch, const std::function<void(LawnApp* _this, LoadingThreadProc_t& base)>& func)
{
	patch.PatchTask("MagicLawnApp::Binding_MF_LoadingThreadProc", [&]
		{
			static std::vector<std::function<void(LawnApp* _this, LoadingThreadProc_t& base)>> func_list;
			patch.PatchTask("MagicLawnApp::Binding_MF_LoadingThreadProc(Hook)", [&]
				{
					using Raw_t = void(__fastcall*)(LawnApp* _this);
					static Raw_t raw;
					Raw_t detour = [](LawnApp* _this)
					{
						LoadingThreadProc_t base;

						base.mFunction = [&](LawnApp* __this)
						{
							std::swap(_this, __this);
							base();
							_this = __this;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								raw(_this);
							else
							{
								i--;
								func_list[i](_this, base);
								i++;
							}
						};

						func_list.back()(_this, base);
					};
					raw = (Raw_t)patch.mHook.HookFunction((void*)0x455840, detour);
				});
			func_list.push_back(func);
		}, false);
}

void MagicLawnApp::Binding_MF_LoadingCompleted(InitPatch& patch, const std::function<void(LawnApp* _this, LoadingCompleted_t& base)>& func)
{
	patch.PatchTask("MagicLawnApp::Binding_MF_LoadingCompleted", [&]
		{
			static std::vector<std::function<void(LawnApp* _this, LoadingCompleted_t& base)>> func_list;
			patch.PatchTask("MagicLawnApp::Binding_MF_LoadingCompleted(Hook)", [&]
				{
					using Raw_t = void(__fastcall*)(LawnApp* _this);
					static Raw_t raw;
					Raw_t detour = [](LawnApp* _this)
					{
						LoadingCompleted_t base;

						base.mFunction = [&](LawnApp* __this)
						{
							std::swap(_this, __this);
							base();
							_this = __this;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								raw(_this);
							else
							{
								i--;
								func_list[i](_this, base);
								i++;
							}
						};

						func_list.back()(_this, base);
					};
					raw = (Raw_t)patch.mHook.HookFunction((void*)0x455cb0, detour);
				});
			func_list.push_back(func);
		}, false);
}

void MagicLawnApp::Binding_MF_Shutdown(InitPatch& patch, const std::function<void(LawnApp* _this, Shutdown_t& base)>& func)
{
	patch.PatchTask("MagicLawnApp::Binding_MF_Shutdown", [&]
		{
			static std::vector<std::function<void(LawnApp* _this, Shutdown_t& base)>> func_list;
			patch.PatchTask("MagicLawnApp::Binding_MF_Shutdown(Hook)", [&]
				{
					using Raw_t = void(__fastcall*)(LawnApp* _this);
					static Raw_t raw;
					Raw_t detour = [](LawnApp* _this)
					{
						Shutdown_t base;

						base.mFunction = [&](LawnApp* __this)
						{
							std::swap(_this, __this);
							base();
							_this = __this;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								raw(_this);
							else
							{
								i--;
								func_list[i](_this, base);
								i++;
							}
						};

						func_list.back()(_this, base);
					};
					raw = (Raw_t)patch.mHook.HookFunction((void*)0x452000, detour);
				});
			func_list.push_back(func);
		}, false);
}

void MagicLawnApp::Binding_MF_WindowProc(InitPatch& patch, const std::function<LRESULT(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, WindowProc_t& base)>& func)
{
	patch.PatchTask("MagicLawnApp::Binding_MF_WindowProc", [&]
		{
			static std::vector<std::function<LRESULT(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, WindowProc_t& base)>> func_list;
			patch.PatchTask("MagicLawnApp::Binding_MF_WindowProc(Hook)", [&]
				{
					static WNDPROC raw;
					WNDPROC detour = [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
					{
						WindowProc_t base;

						base.mFunction = [&](HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
						{
							std::swap(hwnd, _hwnd);
							std::swap(uMsg, _uMsg);
							std::swap(wParam, _wParam);
							std::swap(lParam, _lParam);
							auto result = base();
							hwnd = _hwnd;
							uMsg = _uMsg;
							wParam = _wParam;
							lParam = _lParam;
							return result;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							LRESULT result;
							if (i == 0)
							{
								result = raw(hwnd, uMsg, wParam, lParam);
								if (gSexyAppBase)
									gSexyAppBase->ProcessDeferredMessages(false);
							}
							else
							{
								i--;
								result = func_list[i](hwnd, uMsg, wParam, lParam, base);
								i++;
							}
							return result;
						};

						return func_list.back()( hwnd, uMsg, wParam, lParam, base);
					};
					raw = (WNDPROC)patch.mHook.HookFunction((void*)0x554090, detour);
				});
			func_list.push_back(func);
		});
}

void MagicLawnApp::Binding_MC_NUM_DIALOGS(InitPatch& patch, int theNumDialogs)
{
	assert(theNumDialogs >= NUM_DIALOGS && theNumDialogs < 1000);
	patch.PatchTask("MagicLawnApp::Binding_MC_NUM_DIALOGS", [&]
		{
			static int _theNumDialogs = theNumDialogs;
			patch.mHook.InsertCode((void*)0x452043, [](Hook::Regs* regs)
				{
					regs->efl = Hook::cmp(regs->esi, _theNumDialogs);
				}, 3);
		}, true, true);
}

void MagicLawnApp::Binding_MF_DialogButtonDepress(InitPatch& patch, const std::function<void(LawnApp* _this, int theId, bool isYes, DialogButtonDepress_t& base)>& func)
{
	patch.PatchTask("MagicLawnApp::Binding_MF_DialogButtonDepress", [&]
		{
			static std::vector<std::function<void(LawnApp* _this, int theId, bool isYes, DialogButtonDepress_t& base)>> func_list;
			patch.PatchTask("MagicLawnApp::Binding_MF_DialogButtonDepress(Hook)", [&]
				{
					using Raw_t = void(__fastcall*)(LawnApp* _this, int, int theId);
					static Raw_t raw;
					Raw_t detour = [](LawnApp* _this, int, int theId)
					{
						DialogButtonDepress_t base;

						base.mFunction = [&](LawnApp* __this, int _theId, bool _isYes)
						{
							int id = _isYes ? _theId + 2000 : _theId + 3000;
							std::swap(_this, __this);
							std::swap(theId, id);
							base();
							_this = __this;
							theId = id;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{ 
							if (i == 0)
								raw(_this, 0, theId);
							else
							{
								i--;
								int id = theId % 10000;
								if (id >= 2000 && id < 3000)
									func_list[i](_this, id - 2000, true, base);
								else if (id >= 3000 && id < 4000)
									func_list[i](_this, id - 3000, true, base);
								i++;
							}
						};

						int id = theId % 10000;

						if (id >= 2000 && id < 3000)
							func_list.back()(_this, id - 2000, true, base);
						else if (id >= 3000 && id < 4000)
							func_list.back()(_this, id - 3000, true, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicLawnApp::Binding_mvExclusiveFullscreen(InitPatch& patch, bool& exclusiveFullscreen)
{
	patch.PatchTask("MagicLawnApp::Binding_mvExclusiveFullscreen", [&]
		{
			static bool& _exclusiveFullscreen = exclusiveFullscreen;

			patch.mHook.InsertCode((void*)0x567740, [](Hook::Regs* regs)
				{
					if (_exclusiveFullscreen == false)
						*(bool*)(regs->esp + 0x8) = true;
				});

			patch.mHook.InsertCode((void*)0x556c4f, [](Hook::Regs* regs)
				{
					if (_exclusiveFullscreen == false)
					{
						*(int*)(regs->esp) = 0;
						*(int*)(regs->esp + 0x18) = GetSystemMetrics(SM_CXSCREEN);
						*(int*)(regs->esp + 0x1c) = GetSystemMetrics(SM_CYSCREEN);
					}
				});
		}, true, true);
}

void MagicLawnApp::Binding_mvAutoFixAspectRatio(InitPatch& patch, bool& autoFixAspectRatio)
{
	patch.PatchTask("MagicLawnApp::Binding_mvAutoFixAspectRatio", [&]
		{
			static bool& _autoFixAspectRatio = autoFixAspectRatio;
			patch.mHook.InsertCode((void*)0x558468, [](Hook::Regs* regs)
				{
					if (_autoFixAspectRatio)
					{
						SexyAppBase* app = (SexyAppBase*)regs->esi;
						RECT rect;
						GetClientRect(app->mHWnd, &rect);
						app->KeepAspectRatioFullClient(rect.right, rect.bottom);
					}
				});
		}, true, true);
}

void MagicLawnApp::Binding_mvWindowCanResize(InitPatch& patch, bool& windowCanResize)
{
	patch.PatchTask("MagicLawnApp::Binding_mvWindowCanResize", [&]
		{
			static bool& _windowCanResize = windowCanResize;
			patch.mHook.InsertCode((void*)0x556c85, [](Hook::Regs* regs)
				{
					if (_windowCanResize)
					{
						regs->ebx |= WS_THICKFRAME;
						*(DWORD*)(regs->esp + 0x24) = regs->ebx;
					}
				});
		});
}

