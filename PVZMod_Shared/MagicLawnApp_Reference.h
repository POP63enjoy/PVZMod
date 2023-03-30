#pragma once

#error 本文件仅用于参考，不要包含

#include "LawnApp.h"
#include "MagicLawnApp.h"

namespace PVZMod
{
	/// MagicLawnApp 魔法成员参考。
	///
	/// 本类用于参考 MagicLawnApp 魔法成员的定义方式和用法，不要直接使用本类。
	class MagicLawnApp_Reference :public LawnApp
	{
	public:
		/// 构造函数。
		/// 
		/// @param base		原始函数。
		void MF_Constructor(MagicLawnApp::Constructor_t& base);

		/// 析构函数。
		///
		/// @param base		原始函数。
		void MF_Destructor(MagicLawnApp::Destructor_t& base);

		/// 初始化函数。
		/// 
		/// 在此函数中进行基本的初始化。
		/// 
		/// 注意：需要消耗一定时间的加载操作建议在 MF_LoadingThreadProc 中进行。
		/// 
		/// @param base 原始函数。
		void MF_Init(MagicLawnApp::Init_t& base);

		/// 加载线程函数。
		/// 
		/// 在此函数中进行耗时的加载操作，如加载贴图，加载时 TitleScreen 会显示进度条。
		/// 
		/// @param base 原始函数。
		void MF_LoadingThreadProc(MagicLawnApp::LoadingThreadProc_t& base);

		/// 加载完毕函数。
		/// 
		/// 点击 TitleScreen 中开始游戏按钮时会执行本函数。
		/// 
		/// @param base 原始函数。
		void MF_LoadingCompleted(MagicLawnApp::LoadingCompleted_t& base);

		/// 在关闭游戏时释放资源。
		/// 
		/// @param base 原始函数。
		void MF_Shutdown(MagicLawnApp::Shutdown_t& base);

		/// 对游戏窗口的消息进行处理。
		/// 
		/// 本函数可以为静态，不为静态时 this 指针可能为 nullptr。
		/// 
		/// @param hwnd		窗口句柄。
		/// @param uMsg		消息类型。
		/// @param wParam	消息的第一个参数。
		/// @param lParam	消息的第二个参数。
		/// @param base		原始函数。
		/// @return			消息处理结果。
		/// 
		/// @see			<https://learn.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-wndproc>
		LRESULT MF_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, MagicLawnApp::WindowProc_t& base);


		/// 全局对话框数量。
		static const int MC_NUM_DIALOGS;

		/// 处理全局对话框的按钮点击。
		/// 
		/// @param theId	对话框 id。
		/// @param isYes	为 true 则点击“确定”或“是”按钮，为 false 则点击“取消”或“否”按钮。
		/// @param base		原始函数。
		void MF_DialogButtonDepress(int theId, bool isYes, MagicLawnApp::DialogButtonDepress_t& base);

		/// 是否使用独占全屏。
		/// 
		/// 为 true 时使用独占全屏，为 false 时使用无边框窗口全屏。（默认为 true）
		static bool mvExclusiveFullscreen;

		/// 自动修复画面比例。
		///
		/// 为 true 时，重建窗口将自动修复画面比例。（默认为 false）
		static bool mvAutoFixAspectRatio;

		/// 窗口是否可以缩放。
		///
		/// 为 true 时窗口可以缩放，改变此值需要重建窗口后生效。（默认为 false）
		static bool mvWindowCanResize;
	};
}
