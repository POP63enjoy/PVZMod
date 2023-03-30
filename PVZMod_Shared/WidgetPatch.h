#pragma once
#ifndef _PVZMOD_WIDGET_PATCH_H
#define _PVZMOD_WIDGET_PATCH_H

namespace PVZMod
{
	class InitPatch;

	/// 控件相关补丁。
	namespace WidgetPatch
	{
		// 修复 GameButton 的点击坐标，递归取 mParent 坐标，若 mParent 为 Board，则关联 MagicBoard::mvOffsetXPtr、MagicBoard::mvOffsetYPtr。

		/// 【补丁函数】修复 GameButton 点击判定坐标
		///
		/// 原版中，GameButton 只会计算 mParent 的坐标，而不会递归取 mParent 的父控件的坐标，导致点击判定不正确，此补丁会修复这个问题。
		/// 
		/// 实现 Board 的魔法成员 mvOffset* 后会自动调用此函数。
		/// 
		/// @param patch 补丁对象。
		void FixGameButtonClickPos(InitPatch& patch);
	}
}

#endif // !_PVZMOD_WIDGET_PATCH_H
