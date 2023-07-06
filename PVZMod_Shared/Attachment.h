#pragma once
#ifndef _PVZMOD_ATTACHMENT_H_
#define _PVZMOD_ATTACHMENT_H_

#include "SexyMatrix.h"

namespace PVZMod
{
	class Reanimation;

	enum AttachmentID
	{
		ATTACHMENTID_NULL,
	};

	enum EffectType
	{
		EFFECT_PARTICLE,
		EFFECT_TRAIL,
		EFFECT_REANIM,
		EFFECT_ATTACHMENT,
		EFFECT_OTHER,
	};

	class AttachEffect
	{
	public:
		size_t				mEffectID;
		EffectType			mEffectType;
		SexyTransform2D		mOffset;
		bool				mDontDrawIfParentHidden;
		bool				mDontPropogateColor;
	};

	AttachEffect* AttachReanim(AttachmentID* theAttachmentID, Reanimation* theReanimation, float theOffsetX, float theOffsetY);
}

#endif // !_PVZMOD_ATTACHMENT_H_
