#pragma once
#ifndef _PVZMOD_EFFECT_SYSTEM_H_
#define _PVZMOD_EFFECT_SYSTEM_H_

namespace PVZMod
{
	class TodParticleHolder;
	class TrailHolder;
	class ReanimationHolder;
	class AttachmentHolder;

	/// 【游戏类】特效系统。（原 `::%EffectSystem`）
	class EffectSystem
	{
	public:
		TodParticleHolder*	mParticleHolder;
		TrailHolder*		mTrailHolder;
		ReanimationHolder*	mReanimationHolder;
		AttachmentHolder*	mAttachmentHolder;
	};
}

#endif // !_PVZMOD_EFFECT_SYSTEM_H_
