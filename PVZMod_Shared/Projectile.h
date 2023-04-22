#pragma once
#ifndef _PVZMOD_PROJECTILE_H_
#define _PVZMOD_PROJECTILE_H_

#include "GameObject.h"

namespace PVZMod
{
	enum ProjectileMotion
	{
		MOTION_STRAIGHT,
		MOTION_LOBBED,
		MOTION_THREEPEATER,
		MOTION_BEE,
		MOTION_BEE_BACKWARDS,
		MOTION_PUFF,
		MOTION_BACKWARDS,
		MOTION_STAR,
		MOTION_FLOAT_OVER,
		MOTION_HOMING,
	};

	enum ProjectileType
	{
		PROJECTILE_PEA,
		PROJECTILE_SNOWPEA,
		PROJECTILE_CABBAGE,
		PROJECTILE_MELON,
		PROJECTILE_PUFF,
		PROJECTILE_WINTERMELON,
		PROJECTILE_FIREBALL,
		PROJECTILE_STAR,
		PROJECTILE_SPIKE,
		PROJECTILE_BASKETBALL,
		PROJECTILE_KERNEL,
		PROJECTILE_COBBIG,
		PROJECTILE_BUTTER,
		PROJECTILE_ZOMBIE_PEA,
		NUM_PROJECTILES,
	};

	enum AttachmentID;
	enum ZombieID;

	/// 【游戏类】子弹。（原 `::%Projectile`）
	class Projectile : public GameObject
	{
	public:
		int						mFrame;
		int						mNumFrames;
		int						mAnimCounter;
		float					mPosX;
		float					mPosY;
		float					mPosZ;
		float					mVelX;
		float					mVelY;
		float					mVelZ;
		float					mAccZ;
		float					mShadowY;
		bool					mDead;
		int						mAnimTicksPerFrame;
		ProjectileMotion		mMotionType;
		ProjectileType			mProjectileType;
		int						mProjectileAge;
		int						mClickBackoffCounter;
		float					mRotation;
		float					mRotationSpeed;
		bool					mOnHighGround;
		int						mDamageRangeFlags;
		int						mHitTorchwoodGridX;
		AttachmentID			mAttachmentID;
		float					mCobTargetX;
		int						mCobTargetRow;
		ZombieID				mTargetZombieID;
		int						mLastPortalX;
	};
	static_assert(sizeof(Projectile) == 0x90);
}

#endif // !_PVZMOD_PROJECTILE_H_
