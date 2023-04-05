#pragma once
#ifndef _PVZMOD_ZOMBIE_H_
#define _PVZMOD_ZOMBIE_H_

#include "GameObject.h"
#include "Rect.h"
#include "SexyCommon.h"

namespace PVZMod
{
	enum ZombieType
	{
		ZOMBIE_INVALID = -1,
		ZOMBIE_NORMAL,
		ZOMBIE_FLAG,
		ZOMBIE_TRAFFIC_CONE,
		ZOMBIE_POLEVAULTER,
		ZOMBIE_PAIL,
		ZOMBIE_NEWSPAPER,
		ZOMBIE_DOOR,
		ZOMBIE_FOOTBALL,
		ZOMBIE_DANCER,
		ZOMBIE_BACKUP_DANCER,
		ZOMBIE_DUCKY_TUBE,
		ZOMBIE_SNORKEL,
		ZOMBIE_ZAMBONI,
		ZOMBIE_BOBSLED,
		ZOMBIE_DOLPHIN_RIDER,
		ZOMBIE_JACK_IN_THE_BOX,
		ZOMBIE_BALLOON,
		ZOMBIE_DIGGER,
		ZOMBIE_POGO,
		ZOMBIE_YETI,
		ZOMBIE_BUNGEE,
		ZOMBIE_LADDER,
		ZOMBIE_CATAPULT,
		ZOMBIE_GARGANTUAR,
		ZOMBIE_IMP,
		ZOMBIE_BOSS,
		ZOMBIE_PEA_HEAD,
		ZOMBIE_WALLNUT_HEAD,
		ZOMBIE_JALAPENO_HEAD,
		ZOMBIE_GATLING_HEAD,
		ZOMBIE_SQUASH_HEAD,
		ZOMBIE_TALLNUT_HEAD,
		ZOMBIE_REDEYE_GARGANTUAR,
		NUM_ZOMBIE_TYPES,
	};

	enum ZombiePhase
	{
		PHASE_ZOMBIE_NORMAL,
		PHASE_ZOMBIE_DYING,
		PHASE_ZOMBIE_BURNED,
		PHASE_ZOMBIE_MOWERED,
		PHASE_BUNGEE_DIVING,
		PHASE_BUNGEE_DIVING_SCREAMING,
		PHASE_BUNGEE_AT_BOTTOM,
		PHASE_BUNGEE_GRABBING,
		PHASE_BUNGEE_RISING,
		PHASE_BUNGEE_HIT_OUCHY,
		PHASE_BUNGEE_CUTSCENE,
		PHASE_POLEVAULTER_PRE_VAULT,
		PHASE_POLEVAULTER_IN_VAULT,
		PHASE_POLEVAULTER_POST_VAULT,
		PHASE_RISING_FROM_GRAVE,
		PHASE_JACK_IN_THE_BOX_RUNNING,
		PHASE_JACK_IN_THE_BOX_POPPING,
		PHASE_BOBSLED_SLIDING,
		PHASE_BOBSLED_BOARDING,
		PHASE_BOBSLED_CRASHING,
		PHASE_POGO_BOUNCING,
		PHASE_POGO_HIGH_BOUNCE_1,
		PHASE_POGO_HIGH_BOUNCE_2,
		PHASE_POGO_HIGH_BOUNCE_3,
		PHASE_POGO_HIGH_BOUNCE_4,
		PHASE_POGO_HIGH_BOUNCE_5,
		PHASE_POGO_HIGH_BOUNCE_6,
		PHASE_POGO_FORWARD_BOUNCE_2,
		PHASE_POGO_FORWARD_BOUNCE_7,
		PHASE_NEWSPAPER_READING,
		PHASE_NEWSPAPER_MADDENING,
		PHASE_NEWSPAPER_MAD,
		PHASE_DIGGER_TUNNELING,
		PHASE_DIGGER_RISING,
		PHASE_DIGGER_TUNNELING_PAUSE_WITHOUT_AXE,
		PHASE_DIGGER_RISE_WITHOUT_AXE,
		PHASE_DIGGER_STUNNED,
		PHASE_DIGGER_WALKING,
		PHASE_DIGGER_WALKING_WITHOUT_AXE,
		PHASE_DIGGER_CUTSCENE,
		PHASE_DANCER_DANCING_IN,
		PHASE_DANCER_SNAPPING_FINGERS,
		PHASE_DANCER_SNAPPING_FINGERS_WITH_LIGHT,
		PHASE_DANCER_SNAPPING_FINGERS_HOLD,
		PHASE_DANCER_DANCING_LEFT,
		PHASE_DANCER_WALK_TO_RAISE,
		PHASE_DANCER_RAISE_LEFT_1,
		PHASE_DANCER_RAISE_RIGHT_1,
		PHASE_DANCER_RAISE_LEFT_2,
		PHASE_DANCER_RAISE_RIGHT_2,
		PHASE_DANCER_RISING,
		PHASE_DOLPHIN_WALKING,
		PHASE_DOLPHIN_INTO_POOL,
		PHASE_DOLPHIN_RIDING,
		PHASE_DOLPHIN_IN_JUMP,
		PHASE_DOLPHIN_WALKING_IN_POOL,
		PHASE_DOLPHIN_WALKING_WITHOUT_DOLPHIN,
		PHASE_SNORKEL_WALKING,
		PHASE_SNORKEL_INTO_POOL,
		PHASE_SNORKEL_WALKING_IN_POOL,
		PHASE_SNORKEL_UP_TO_EAT,
		PHASE_SNORKEL_EATING_IN_POOL,
		PHASE_SNORKEL_DOWN_FROM_EAT,
		PHASE_ZOMBIQUARIUM_ACCEL,
		PHASE_ZOMBIQUARIUM_DRIFT,
		PHASE_ZOMBIQUARIUM_BACK_AND_FORTH,
		PHASE_ZOMBIQUARIUM_BITE,
		PHASE_CATAPULT_LAUNCHING,
		PHASE_CATAPULT_RELOADING,
		PHASE_GARGANTUAR_THROWING,
		PHASE_GARGANTUAR_SMASHING,
		PHASE_IMP_GETTING_THROWN,
		PHASE_IMP_LANDING,
		PHASE_BALLOON_FLYING,
		PHASE_BALLOON_POPPING,
		PHASE_BALLOON_WALKING,
		PHASE_LADDER_CARRYING,
		PHASE_LADDER_PLACING,
		PHASE_BOSS_ENTER,
		PHASE_BOSS_IDLE,
		PHASE_BOSS_SPAWNING,
		PHASE_BOSS_STOMPING,
		PHASE_BOSS_BUNGEES_ENTER,
		PHASE_BOSS_BUNGEES_DROP,
		PHASE_BOSS_BUNGEES_LEAVE,
		PHASE_BOSS_DROP_RV,
		PHASE_BOSS_HEAD_ENTER,
		PHASE_BOSS_HEAD_IDLE_BEFORE_SPIT,
		PHASE_BOSS_HEAD_IDLE_AFTER_SPIT,
		PHASE_BOSS_HEAD_SPIT,
		PHASE_BOSS_HEAD_LEAVE,
		PHASE_YETI_RUNNING,
		PHASE_SQUASH_PRE_LAUNCH,
		PHASE_SQUASH_RISING,
		PHASE_SQUASH_FALLING,
		PHASE_SQUASH_DONE_FALLING,
	};

	enum ZombieHeight
	{
		HEIGHT_ZOMBIE_NORMAL,
		HEIGHT_IN_TO_POOL,
		HEIGHT_OUT_OF_POOL,
		HEIGHT_DRAGGED_UNDER,
		HEIGHT_UP_TO_HIGH_GROUND,
		HEIGHT_DOWN_OFF_HIGH_GROUND,
		HEIGHT_UP_LADDER,
		HEIGHT_FALLING,
		HEIGHT_IN_TO_CHIMNEY,
		HEIGHT_GETTING_BUNGEE_DROPPED,
		HEIGHT_ZOMBIQUARIUM,
	};

	enum HelmType
	{
		HELMTYPE_NONE,
		HELMTYPE_TRAFFIC_CONE,
		HELMTYPE_PAIL,
		HELMTYPE_FOOTBALL,
		HELMTYPE_DIGGER,
		HELMTYPE_REDEYES,
		HELMTYPE_HEADBAND,
		HELMTYPE_BOBSLED,
		HELMTYPE_WALLNUT,
		HELMTYPE_TALLNUT,
	};

	enum ShieldType
	{
		SHIELDTYPE_NONE,
		SHIELDTYPE_DOOR,
		SHIELDTYPE_NEWSPAPER,
		SHIELDTYPE_LADDER,
	};

	enum ZombieID
	{
		ZOMBIEID_NULL,
	};

	enum
	{
		ZOMBIE_WAVE_DEBUG = -1,
		ZOMBIE_WAVE_CUTSCENE = -2,
		ZOMBIE_WAVE_UI = -3,
		ZOMBIE_WAVE_WINNER = -4
	};

	class TodParticleSystem;
	class Reanimation;

	enum AttachmentID;
	enum ReanimationID;
	enum PlantID;
	enum ReanimationType;
	enum ReanimLoopType;
	enum ParticleEffect;

	/// 【游戏类】僵尸。（原 ::Zombie）
	class Zombie : public GameObject
	{
	public:
		ZombieType			mZombieType;
		ZombiePhase			mZombiePhase;
		float				mPosX;
		float				mPosY;
		float				mVelX;
		int					mAnimCounter;
		int					mGroanCounter;
		int					mAnimTicksPerFrame;
		int					mAnimFrames;
		int					mFrame;
		int					mPrevFrame;
		bool				mVariant;
		bool				mIsEating;
		int					mJustGotShotCounter;
		int					mShieldJustGotShotCounter;
		int					mShieldRecoilCounter;
		int					mZombieAge;
		ZombieHeight		mZombieHeight;
		int					mPhaseCounter;
		int					mFromWave;
		bool				mDroppedLoot;
		int					mZombieFade;
		bool				mFlatTires;
		int					mUseLadderCol;
		int					mTargetCol;
		float				mAltitude;
		bool				mHitUmbrella;
		Rect				mZombieRect;
		Rect				mZombieAttackRect;
		int					mChilledCounter;
		int					mButteredCounter;
		int					mIceTrapCounter;
		bool				mMindControlled;
		bool				mBlowingAway;
		bool				mHasHead;
		bool				mHasArm;
		bool				mHasObject;
		bool				mInPool;
		bool				mOnHighGround;
		bool				mYuckyFace;
		int					mYuckyFaceCounter;
		HelmType			mHelmType;
		int					mBodyHealth;
		int					mBodyMaxHealth;
		int					mHelmHealth;
		int					mHelmMaxHealth;
		ShieldType			mShieldType;
		int					mShieldHealth;
		int					mShieldMaxHealth;
		int					mFlyingHealth;
		int					mFlyingMaxHealth;
		bool				mDead;
		ZombieID			mRelatedZombieID;
		ZombieID			mFollowerZombieID[4];
		bool				mPlayingSong;
		int					mParticleOffsetX;
		int					mParticleOffsetY;
		AttachmentID		mAttachmentID;
		int					mSummonCounter;
		ReanimationID		mBodyReanimID;
		float				mScaleZombie;
		float				mVelZ;
		float				mOrginalAnimRate;
		PlantID				mTargetPlantID;
		int					mBossMode;
		int					mTargetRow;
		int					mBossBungeeCounter;
		int					mBossStompCounter;
		int					mBossHeadCounter;
		ReanimationID		mBossFireBallReanimID;
		ReanimationID		mSpecialHeadReanimID;
		int					mFireballRow;
		bool				mIsFireBall;
		ReanimationID		mMoweredReanimID;
		int					mLastPortalX;

	public:
		bool				IsOnBoard();

		float				GetPosYBasedOnRow(int theRow);

		Reanimation*		LoadReanim(ReanimationType theReanimationType);
		void				LoadPlainZombieReanim();
		void                PlayZombieReanim(const char* theTrackName, ReanimLoopType theLoopType, int theBlendTime, float theAnimRate);
		void				ReanimShowPrefix(const char* theTrackPrefix, int theRenderGroup);
		void				StartWalkAnim(int theBlendTime);
		void                SetupWaterTrack(const char* theTrackName);
		void                SetAnimRate(float theAnimRate);
		void                BossSetupReanim();
		void				UpdateAnimSpeed();
		void				UpdateReanim();

		void				AttachShield();
		void                PickBungeeZombieTarget(int theColumn);
		TodParticleSystem*	AddAttachedParticle(int thePosX, int thePosY, ParticleEffect theEffect);
		void                PickRandomSpeed();

		void				PlayZombieAppearSound();
		void				StartZombieSound();
	};

	static_assert(sizeof(Zombie) == 0x158);
	
	/// 【游戏类】僵尸定义信息。（原 ::ZombieDefinition）
	class ZombieDefinition
	{
	public:
		ZombieType           mZombieType;
		ReanimationType      mReanimationType;
		int                  mZombieValue;
		int                  mStartingLevel;
		int                  mFirstAllowedWave;
		int                  mPickWeight;
		const SexyChar*		 mZombieName;
	};

	ZombieDefinition& GetZombieDefinition(ZombieType theZombieType);
}

#endif // !_PVZMOD_ZOMBIE_H_
