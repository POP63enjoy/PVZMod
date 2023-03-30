#pragma once
#ifndef _PVZMOD_GAME_OBEJCT_PATCH_H_
#define _PVZMOD_GAME_OBEJCT_PATCH_H_

namespace PVZMod
{
	class InitPatch;

	/// 游戏对象相关补丁
	namespace GameObjectPatch
	{
		/// 【补丁函数】修复 Board 中 ToolTipWidget 的显示坐标。
		///
		/// 修复后，对于 Board 的坐标改变以及其父控件的坐标改变，ToolTipWidget 将以正确的光标坐标显示。
		/// 
		/// 实现 Board 的魔法成员 mvOffset* 后会自动调用此函数。
		/// 
		/// @param patch 补丁对象。
		void FixBoardToolTipPos(InitPatch& patch);

		/// 【补丁函数】修复 Board 中光标样式的判定坐标。
		///
		/// 修复后，对于 Board 的坐标改变以及其父控件的坐标改变，光标样式将以正确的光标坐标判定。
		/// 
		/// 实现 Board 的魔法成员 mvOffset* 后会自动调用此函数。
		/// 
		/// @param patch 补丁对象。
		void FixBoardCursorPos(InitPatch& patch);

		/// 【补丁函数】修复 Board 中对象高亮的判定坐标。
		///
		/// 修复后，对于 Board 的坐标改变以及其父控件的坐标改变，对象高亮将以正确的光标坐标显示。
		/// 
		/// 实现 Board 的魔法成员 mvOffset* 后会自动调用此函数。
		/// 
		/// @param patch 补丁对象。
		void FixBoardHighlightPos(InitPatch& patch);

		/// 【补丁函数】对 Board 中的所有 GameButton 赋值 mParent。
		///
		/// @param patch 补丁对象。
		void FixBoardGameButtonParent(InitPatch& patch);

		/// 【补丁函数】修复 Board 中 CursorObject 的显示坐标。
		///
		/// 修复后，对于 Board 的坐标改变以及其父控件的坐标改变，CursorObject 将以正确的光标坐标显示。
		/// 
		/// 实现 Board 的魔法成员 mvOffset* 后会自动调用此函数。
		/// 
		/// @param patch 补丁对象。
		void FixCursorObjectPos(InitPatch& patch);
		
		/// 【补丁函数】修复 Board 中 CursorPreview 的显示坐标。
		///
		/// 修复后，对于 Board 的坐标改变以及其父控件的坐标改变，CursorPreview 将以正确的光标坐标显示。
		/// 
		/// 实现 Board 的魔法成员 mvOffset* 后会自动调用此函数。
		/// 
		/// @param patch 补丁对象。
		void FixCursorPreviewPos(InitPatch& patch);
	}
}

#endif // !_PVZMOD_GAME_OBEJCT_PATCH_H_
