#pragma once
#ifndef _PVZMOD_EFFECT_PATCH_H_
#define _PVZMOD_EFFECT_PATCH_H_

namespace PVZMod
{
	class InitPatch;
	class ReanimationParams;

	/// 特效相关补丁
	namespace EffectPatch
	{
		/// 【补丁函数】替换动画参数数组。
		/// 
		/// 此函数会替换所有动画，而非追加。
		/// 
		/// 建议使用 PVZMod_Tools 中的 ReanimManager 工具，此工具会生成调用这个函数的代码实现新增动画。
		/// 
		/// @param patch		补丁对象。
		/// @param theArray		动画参数数组。
		/// @param theSize		数组大小。
		void SetReanimationParamArray(InitPatch& patch, ReanimationParams* theArray, size_t theSize);
	}
}

#endif // !_PVZMOD_EFFECT_PATCH_H_
