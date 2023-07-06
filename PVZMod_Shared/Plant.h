#pragma once
#ifndef _PVZMOD_PLANT_H_
#define _PVZMOD_PLANT_H_

#include "GameObject.h"
#include "Rect.h"
#include "SexyCommon.h"

namespace PVZMod
{
	enum SeedType
	{
		SEED_PEASHOOTER,
		SEED_SUNFLOWER,
		SEED_CHERRYBOMB,
		SEED_WALLNUT,
		SEED_POTATOMINE,
		SEED_SNOWPEA,
		SEED_CHOMPER,
		SEED_REPEATER,
		SEED_PUFFSHROOM,
		SEED_SUNSHROOM,
		SEED_FUMESHROOM,
		SEED_GRAVEBUSTER,
		SEED_HYPNOSHROOM,
		SEED_SCAREDYSHROOM,
		SEED_ICESHROOM,
		SEED_DOOMSHROOM,
		SEED_LILYPAD,
		SEED_SQUASH,
		SEED_THREEPEATER,
		SEED_TANGLEKELP,
		SEED_JALAPENO,
		SEED_SPIKEWEED,
		SEED_TORCHWOOD,
		SEED_TALLNUT,
		SEED_SEASHROOM,
		SEED_PLANTERN,
		SEED_CACTUS,
		SEED_BLOVER,
		SEED_SPLITPEA,
		SEED_STARFRUIT,
		SEED_PUMPKINSHELL,
		SEED_MAGNETSHROOM,
		SEED_CABBAGEPULT,
		SEED_FLOWERPOT,
		SEED_KERNELPULT,
		SEED_INSTANT_COFFEE,
		SEED_GARLIC,
		SEED_UMBRELLA,
		SEED_MARIGOLD,
		SEED_MELONPULT,
		SEED_GATLINGPEA,
		SEED_TWINSUNFLOWER,
		SEED_GLOOMSHROOM,
		SEED_CATTAIL,
		SEED_WINTERMELON,
		SEED_GOLD_MAGNET,
		SEED_SPIKEROCK,
		SEED_COBCANNON,
		SEED_IMITATER,
		SEED_EXPLODE_O_NUT,
		SEED_GIANT_WALLNUT,
		SEED_SPROUT,
		SEED_LEFTPEATER,
		NUM_SEED_TYPES,
		SEED_BEGHOULED_BUTTON_SHUFFLE,
		SEED_BEGHOULED_BUTTON_CRATER,
		SEED_SLOT_MACHINE_SUN,
		SEED_SLOT_MACHINE_DIAMOND,
		SEED_ZOMBIQUARIUM_SNORKEL,
		SEED_ZOMBIQUARIUM_TROPHY,
		SEED_ZOMBIE_NORMAL,
		SEED_ZOMBIE_TRAFFIC_CONE,
		SEED_ZOMBIE_POLEVAULTER,
		SEED_ZOMBIE_PAIL,
		SEED_ZOMBIE_LADDER,
		SEED_ZOMBIE_DIGGER,
		SEED_ZOMBIE_BUNGEE,
		SEED_ZOMBIE_FOOTBALL,
		SEED_ZOMBIE_BALLOON,
		SEED_ZOMBIE_SCREEN_DOOR,
		SEED_ZOMBONI,
		SEED_ZOMBIE_POGO,
		SEED_ZOMBIE_DANCER,
		SEED_ZOMBIE_GARGANTUAR,
		SEED_ZOMBIE_IMP,

		NUM_SEEDS_IN_CHOOSER = SEED_IMITATER + 1,
		SEED_NONE = -1,
	};

	enum PlantState
	{
		STATE_NOTREADY,
		STATE_READY,
		STATE_DOINGSPECIAL,
		STATE_SQUASH_LOOK,
		STATE_SQUASH_PRE_LAUNCH,
		STATE_SQUASH_RISING,
		STATE_SQUASH_FALLING,
		STATE_SQUASH_DONE_FALLING,
		STATE_GRAVEBUSTER_LANDING,
		STATE_GRAVEBUSTER_EATING,
		STATE_CHOMPER_BITING,
		STATE_CHOMPER_BITING_GOT_ONE,
		STATE_CHOMPER_BITING_MISSED,
		STATE_CHOMPER_DIGESTING,
		STATE_CHOMPER_SWALLOWING,
		STATE_POTATO_RISING,
		STATE_POTATO_ARMED,
		STATE_POTATO_MASHED,
		STATE_SPIKEWEED_ATTACKING,
		STATE_SPIKEWEED_ATTACKING_2,
		STATE_SCAREDYSHROOM_LOWERING,
		STATE_SCAREDYSHROOM_SCARED,
		STATE_SCAREDYSHROOM_RAISING,
		STATE_SUNSHROOM_SMALL,
		STATE_SUNSHROOM_GROWING,
		STATE_SUNSHROOM_BIG,
		STATE_MAGNETSHROOM_SUCKING,
		STATE_MAGNETSHROOM_CHARGING,
		STATE_BOWLING_UP,
		STATE_BOWLING_DOWN,
		STATE_CACTUS_LOW,
		STATE_CACTUS_RISING,
		STATE_CACTUS_HIGH,
		STATE_CACTUS_LOWERING,
		STATE_TANGLEKELP_GRABBING,
		STATE_COBCANNON_ARMING,
		STATE_COBCANNON_LOADING,
		STATE_COBCANNON_READY,
		STATE_COBCANNON_FIRING,
		STATE_KERNELPULT_BUTTER,
		STATE_UMBRELLA_TRIGGERED,
		STATE_UMBRELLA_REFLECTING,
		STATE_IMITATER_MORPHING,
		STATE_ZEN_GARDEN_WATERED,
		STATE_ZEN_GARDEN_NEEDY,
		STATE_ZEN_GARDEN_HAPPY,
		STATE_MARIGOLD_ENDING,
		STATE_FLOWERPOT_INVULNERABLE,
		STATE_LILYPAD_INVULNERABLE,
	};

	enum MagnetItemType
	{
		MAGNET_ITEM_NONE,
		MAGNET_ITEM_PAIL_1,
		MAGNET_ITEM_PAIL_2,
		MAGNET_ITEM_PAIL_3,
		MAGNET_ITEM_FOOTBALL_HELMET_1,
		MAGNET_ITEM_FOOTBALL_HELMET_2,
		MAGNET_ITEM_FOOTBALL_HELMET_3,
		MAGNET_ITEM_DOOR_1,
		MAGNET_ITEM_DOOR_2,
		MAGNET_ITEM_DOOR_3,
		MAGNET_ITEM_POGO_1,
		MAGNET_ITEM_POGO_2,
		MAGNET_ITEM_POGO_3,
		MAGNET_ITEM_JACK_IN_THE_BOX,
		MAGNET_ITEM_LADDER_1,
		MAGNET_ITEM_LADDER_2,
		MAGNET_ITEM_LADDER_3,
		MAGNET_ITEM_LADDER_PLACED,
		MAGNET_ITEM_SILVER_COIN,
		MAGNET_ITEM_GOLD_COIN,
		MAGNET_ITEM_DIAMOND,
		MAGNET_ITEM_PICK_AXE,
	};

	enum PlantOnBungeeState
	{
		PLANT_NOT_ON_BUNGEE,
		PLANT_GETTING_GRABBED_BY_BUNGEE,
		PLANT_RISING_WITH_BUNGEE,
	};

	enum PlantSubClass
	{
		SUBCLASS_NORMAL,
		SUBCLASS_SHOOTER,
	};

	enum PlantID
	{
		PLANTID_NULL
	};

	struct MagnetItem
	{
		float			mPosX;
		float			mPosY;
		float			mDestOffsetX;
		float			mDestOffsetY;
		MagnetItemType	mItemType;
	};

	class Image;
	class TodParticleSystem;

	enum ParticleSystemID;
	enum ReanimationID;
	enum ZombieID;
	enum ReanimationType;
	enum ParticleEffect;

	/// 【游戏类】植物。（原 `::%Plant`）
	class Plant : public GameObject
	{
	public:
		SeedType				mSeedType;
		int						mPlantCol;
		int						mAnimCounter;
		int						mFrame;
		int						mFrameLength;
		int						mNumFrames;
		PlantState				mState;
		int						mPlantHealth;
		int						mPlantMaxHealth;
		int						mSubclass;
		int						mDisappearCountdown;
		int						mDoSpecialCountdown;
		int						mStateCountdown;
		int						mLaunchCounter;
		int						mLaunchRate;
		Rect					mPlantRect;
		Rect					mPlantAttackRect;
		int						mTargetX;
		int						mTargetY;
		int						mStartRow;
		ParticleSystemID		mParticleID;
		int						mShootingCounter;
		ReanimationID			mBodyReanimID;
		ReanimationID			mHeadReanimID;
		ReanimationID			mHeadReanimID2;
		ReanimationID			mHeadReanimID3;
		ReanimationID			mBlinkReanimID;
		ReanimationID			mLightReanimID;
		ReanimationID			mSleepingReanimID;
		int						mBlinkCountdown;
		int						mRecentlyEatenCountdown;
		int						mEatenFlashCountdown;
		int						mBeghouledFlashCountdown;
		float					mShakeOffsetX;
		float					mShakeOffsetY;
		MagnetItem				mMagnetItems[5];
		ZombieID				mTargetZombieID;
		int						mWakeUpCounter;
		PlantOnBungeeState		mOnBungeeState;
		SeedType				mImitaterType;
		int						mPottedPlantIndex;
		bool					mAnimPing;
		bool					mDead;
		bool					mSquished;
		bool					mIsAsleep;
		bool					mIsOnBoard;
		bool					mHighlighted;

	public:
		int						CalcRenderOrder();
		void					SetSleeping(bool theIsAsleep);
		bool					IsOnBoard();

		TodParticleSystem*		AddAttachedParticle(int thePosX, int thePosY, int theRenderPosition, ParticleEffect theEffect);

		bool					MakesSun();
		bool					IsInPlay();
		bool					NotOnGround();
		static bool				IsNocturnal(SeedType theSeedtype);

	};

	static_assert(sizeof(Plant) == 0x148);

	float					   PlantDrawHeightOffset(Board* theBoard, Plant* thePlant, SeedType theSeedType, int theCol, int theRow);

	/// 【游戏类】植物定义信息。（原 `::%PlantDefinition`）
	class PlantDefinition
	{
	public:
		SeedType			mSeedType;
		Image**				mPlantImage;
		ReanimationType		mReanimationType;   
		int					mPacketIndex;
		int					mSeedCost;
		int					mRefreshTime;
		PlantSubClass		mSubClass;
		int					mLaunchRate;
		const SexyChar*		mPlantName;
	};

	PlantDefinition& GetPlantDefinition(SeedType theSeedType);
}

#endif // !_PVZMOD_PLANT_H_
