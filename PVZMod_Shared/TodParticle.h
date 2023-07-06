#pragma once
#ifndef _PVZMOD_TOD_PARTICLE_H_
#define _PVZMOD_TOD_PARTICLE_H_
#include "TodList.h"

namespace PVZMod
{
	constexpr size_t MAX_PARTICLE_FIELDS = 4;

	enum ParticleEffect
	{
		PARTICLE_NONE = -1,
		PARTICLE_MELONSPLASH,
		PARTICLE_WINTERMELON,
		PARTICLE_FUMECLOUD,
		PARTICLE_POPCORNSPLASH,
		PARTICLE_POWIE,
		PARTICLE_JACKEXPLODE,
		PARTICLE_ZOMBIE_HEAD,
		PARTICLE_ZOMBIE_ARM,
		PARTICLE_ZOMBIE_TRAFFIC_CONE,
		PARTICLE_ZOMBIE_PAIL,
		PARTICLE_ZOMBIE_HELMET,
		PARTICLE_ZOMBIE_FLAG,
		PARTICLE_ZOMBIE_DOOR,
		PARTICLE_ZOMBIE_NEWSPAPER,
		PARTICLE_ZOMBIE_HEADLIGHT,
		PARTICLE_POW,
		PARTICLE_ZOMBIE_POGO,
		PARTICLE_ZOMBIE_NEWSPAPER_HEAD,
		PARTICLE_ZOMBIE_BALLOON_HEAD,
		PARTICLE_SOD_ROLL,
		PARTICLE_GRAVE_STONE_RISE,
		PARTICLE_PLANTING,
		PARTICLE_PLANTING_POOL,
		PARTICLE_ZOMBIE_RISE,
		PARTICLE_GRAVE_BUSTER,
		PARTICLE_GRAVE_BUSTER_DIE,
		PARTICLE_POOL_SPLASH,
		PARTICLE_ICE_SPARKLE,
		PARTICLE_SEED_PACKET,
		PARTICLE_TALL_NUT_BLOCK,
		PARTICLE_DOOM,
		PARTICLE_DIGGER_RISE,
		PARTICLE_DIGGER_TUNNEL,
		PARTICLE_DANCER_RISE,
		PARTICLE_POOL_SPARKLY,
		PARTICLE_WALLNUT_EAT_SMALL,
		PARTICLE_WALLNUT_EAT_LARGE,
		PARTICLE_PEA_SPLAT,
		PARTICLE_BUTTER_SPLAT,
		PARTICLE_CABBAGE_SPLAT,
		PARTICLE_PUFF_SPLAT,
		PARTICLE_STAR_SPLAT,
		PARTICLE_ICE_TRAP,
		PARTICLE_SNOWPEA_SPLAT,
		PARTICLE_SNOWPEA_PUFF,
		PARTICLE_SNOWPEA_TRAIL,
		PARTICLE_LANTERN_SHINE,
		PARTICLE_SEED_PACKET_PICKUP,
		PARTICLE_POTATO_MINE,
		PARTICLE_POTATO_MINE_RISE,
		PARTICLE_PUFFSHROOM_TRAIL,
		PARTICLE_PUFFSHROOM_MUZZLE,
		PARTICLE_SEED_PACKET_FLASH,
		PARTICLE_WHACK_A_ZOMBIE_RISE,
		PARTICLE_ZOMBIE_LADDER,
		PARTICLE_UMBRELLA_REFLECT,
		PARTICLE_SEED_PACKET_PICK,
		PARTICLE_ICE_TRAP_ZOMBIE,
		PARTICLE_ICE_TRAP_RELEASE,
		PARTICLE_ZAMBONI_SMOKE,
		PARTICLE_GLOOMCLOUD,
		PARTICLE_ZOMBIE_POGO_HEAD,
		PARTICLE_ZAMBONI_TIRE,
		PARTICLE_ZAMBONI_EXPLOSION,
		PARTICLE_ZAMBONI_EXPLOSION2,
		PARTICLE_CATAPULT_EXPLOSION,
		PARTICLE_MOWER_CLOUD,
		PARTICLE_BOSS_ICE_BALL,
		PARTICLE_BLASTMARK,
		PARTICLE_COIN_PICKUP_ARROW,
		PARTICLE_PRESENT_PICKUP,
		PARTICLE_IMITATER_MORPH,
		PARTICLE_MOWERED_ZOMBIE_HEAD,
		PARTICLE_MOWERED_ZOMBIE_ARM,
		PARTICLE_ZOMBIE_HEAD_POOL,
		PARTICLE_ZOMBIE_BOSS_FIREBALL,
		PARTICLE_FIREBALL_DEATH,
		PARTICLE_ICEBALL_DEATH,
		PARTICLE_ICEBALL_TRAIL,
		PARTICLE_FIREBALL_TRAIL,
		PARTICLE_BOSS_EXPLOSION,
		PARTICLE_SCREEN_FLASH,
		PARTICLE_TROPHY_SPARKLE,
		PARTICLE_PORTAL_CIRCLE,
		PARTICLE_PORTAL_SQUARE,
		PARTICLE_POTTED_PLANT_GLOW,
		PARTICLE_POTTED_WATER_PLANT_GLOW,
		PARTICLE_POTTED_ZEN_GLOW,
		PARTICLE_MIND_CONTROL,
		PARTICLE_VASE_SHATTER,
		PARTICLE_VASE_SHATTER_LEAF,
		PARTICLE_VASE_SHATTER_ZOMBIE,
		PARTICLE_AWARD_PICKUP_ARROW,
		PARTICLE_ZOMBIE_SEAWEED,
		PARTICLE_ZOMBIE_MUSTACHE,
		PARTICLE_ZOMBIE_SUNGLASS,
		PARTICLE_ZOMBIE_PINATA,
		PARTICLE_DUST_SQUASH,
		PARTICLE_DUST_FOOT,
		PARTICLE_ZOMBIE_DAISIES,
		PARTICLE_CREDIT_STROBE,
		PARTICLE_CREDITS_RAYSWIPE,
		PARTICLE_CREDITS_ZOMBIEHEADWIPE,
		PARTICLE_STARBURST,
		PARTICLE_CREDITS_FOG,
		PARTICLE_PERSENT_PICK_UP_ARROW,
		NUM_PARTICLES
	};

	enum EmitterType
	{
		EMITTER_CIRCLE,
		EMITTER_BOX,
		EMITTER_BOX_PATH,
		EMITTER_CIRCLE_PATH,
		EMITTER_CIRCLE_EVEN_SPACING
	};

	enum ParticleFieldType
	{
		FIELD_INVALID,
		FIELD_FRICTION,                     ///< 摩擦力场：该场内粒子的速度按一定比例不断衰减
		FIELD_ACCELERATION,                 ///< 加速度场：该场内粒子以一定加速度做加速运动
		FIELD_ATTRACTOR,                    ///< 弹性力场：该场内粒子加速度的大小和方向均受到粒子与发射器之间距离大小的影响
		FIELD_MAX_VELOCITY,                 ///< 限速场：该场内粒子速度的大小不能超过一定的上限值
		FIELD_VELOCITY,                     ///< 匀速场：该场内粒子速度的大小总是为一给定值
		FIELD_POSITION,                     ///< 定位场：该场内粒子的位置总是为一给定值
		FIELD_SYSTEM_POSITION,              ///< 系统定位场：仅发射器可用，该场内发射器的位置总是为一给定值
		FIELD_GROUND_CONSTRAINT,            ///< 地面限制：粒子的纵向位置不能低于地面，且接触地面时会触发弹起效果
		FIELD_SHAKE,                        ///< 震动：粒子的坐标会有随机 -1.0 到 +1.0 的偏移，每帧独立计算
		FIELD_CIRCLE,                       ///< 引力场：该场内粒子围绕发射器中心做圆周运动（考虑误差，实为螺线运动）
		FIELD_AWAY,                         ///< 斥力场：该场内粒子沿径向不断远离发射器中心
		PARTICLE_FIELD_COUNT
	};

	enum ParticleTracks
	{
		TRACK_PARTICLE_RED,
		TRACK_PARTICLE_GREEN,
		TRACK_PARTICLE_BLUE,
		TRACK_PARTICLE_ALPHA,
		TRACK_PARTICLE_BRIGHTNESS,
		TRACK_PARTICLE_SPIN_SPEED,
		TRACK_PARTICLE_SPIN_ANGLE,
		TRACK_PARTICLE_SCALE,
		TRACK_PARTICLE_STRETCH,
		TRACK_PARTICLE_COLLISION_REFLECT,
		TRACK_PARTICLE_COLLISION_SPIN,
		TRACK_PARTICLE_CLIP_TOP,
		TRACK_PARTICLE_CLIP_BOTTOM,
		TRACK_PARTICLE_CLIP_LEFT,
		TRACK_PARTICLE_CLIP_RIGHT,
		TRACK_PARTICLE_ANIMATION_RATE,
		NUM_PARTICLE_TRACKS
	};

	enum ParticleID { PARTICLEID_NULL };
	enum ParticleEmitterID { PARTICLEEMITTERID_NULL };
	enum ParticleSystemID { PARTICLESYSTEMID_NULL };

	class ParticleField
	{
	public:
		ParticleFieldType			mFieldType;                     ///< 场的类型，决定了场对粒子运动的影响方式
		FloatParameterTrack			mX;                             ///< 场在水平方向（横向）上对粒子的影响
		FloatParameterTrack			mY;                             ///< 场在竖直方向（纵向）上对粒子的影响
	};

	class TodEmitterDefinition
	{
	public:
		Image*						mImage;
		int							mImageCol;
		int							mImageRow;
		int							mImageFrames;
		int							mAnimated;
		int							mParticleFlags;
		EmitterType					mEmitterType;
		const char*					mName;
		const char*					mOnDuration;
		FloatParameterTrack			mSystemDuration;
		FloatParameterTrack			mCrossFadeDuration;
		FloatParameterTrack			mSpawnRate;
		FloatParameterTrack			mSpawnMinActive;
		FloatParameterTrack			mSpawnMaxActive;
		FloatParameterTrack			mSpawnMaxLaunched;
		FloatParameterTrack			mEmitterRadius;
		FloatParameterTrack			mEmitterOffsetX;
		FloatParameterTrack			mEmitterOffsetY;
		FloatParameterTrack			mEmitterBoxX;
		FloatParameterTrack			mEmitterBoxY;
		FloatParameterTrack			mEmitterSkewX;
		FloatParameterTrack			mEmitterSkewY;
		FloatParameterTrack			mEmitterPath;
		FloatParameterTrack			mParticleDuration;
		FloatParameterTrack			mLaunchSpeed;
		FloatParameterTrack			mLaunchAngle;
		FloatParameterTrack			mSystemRed;
		FloatParameterTrack			mSystemGreen;
		FloatParameterTrack			mSystemBlue;
		FloatParameterTrack			mSystemAlpha;
		FloatParameterTrack			mSystemBrightness;
		ParticleField*				mParticleFields;
		int							mParticleFieldCount;
		ParticleField*				mSystemFields;
		int							mSystemFieldCount;
		FloatParameterTrack			mParticleRed;
		FloatParameterTrack			mParticleGreen;
		FloatParameterTrack			mParticleBlue;
		FloatParameterTrack			mParticleAlpha;
		FloatParameterTrack			mParticleBrightness;
		FloatParameterTrack			mParticleSpinAngle;
		FloatParameterTrack			mParticleSpinSpeed;
		FloatParameterTrack			mParticleScale;
		FloatParameterTrack			mParticleStretch;
		FloatParameterTrack			mCollisionReflect;
		FloatParameterTrack			mCollisionSpin;
		FloatParameterTrack			mClipTop;
		FloatParameterTrack			mClipBottom;
		FloatParameterTrack			mClipLeft;
		FloatParameterTrack			mClipRight;
		FloatParameterTrack			mAnimationRate;
	};

	class TodParticleDefinition
	{
	public:
		TodEmitterDefinition*		mEmitterDefs;
		int							mEmitterDefCount;
	};

	class TodParticleSystem;
	class TodParticleEmitter;
	class TodParticle;

	class TodParticleHolder
	{
	public:
		DataArray<TodParticleSystem>	mParticleSystems;
		DataArray<TodParticleEmitter>	mEmitters;
		DataArray<TodParticle>			mParticles;
		TodAllocator					mParticleListNodeAllocator;
		TodAllocator					mEmitterListNodeAllocator;
	};

	class TodParticleSystem
	{
	public:
		ParticleEffect					mEffectType;
		TodParticleDefinition*			mParticleDef;
		TodParticleHolder*				mParticleHolder;
		TodList<ParticleEmitterID>		mEmitterList;
		bool							mDead;
		bool							mIsAttachment;
		int								mRenderOrder;
		bool							mDontUpdate;
	};

	class TodParticle
	{
	public:
		TodParticleEmitter*				mParticleEmitter;
		int								mParticleDuration;
		int								mParticleAge;
		float							mParticleTimeValue;
		float							mParticleLastTimeValue;
		float							mAnimationTimeValue;
		SexyVector2						mVelocity;
		SexyVector2						mPosition;
		int								mImageFrame;
		float							mSpinPosition;
		float							mSpinVelocity;
		ParticleID						mCrossFadeParticleID;
		int								mCrossFadeDuration;
		float							mParticleInterp[NUM_PARTICLE_TRACKS];
		float							mParticleFieldInterp[MAX_PARTICLE_FIELDS][2];
	};
}
#endif // !_PVZMOD_TOD_PARTICLE_H_
