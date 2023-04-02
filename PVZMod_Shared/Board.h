#pragma once
#ifndef _PVZMOD_BOARD_H_
#define _PVZMOD_BOARD_H_

#include "Widget.h"
#include "ButtonListener.h"
#include "DataArray.h"
#include "Zombie.h"
#include "Plant.h"
#include "Projectile.h"
#include "Coin.h"
#include "LawnMower.h"
#include "GridItem.h"
#include "TodCommon.h"

namespace PVZMod
{
	enum GridSquareType
	{
		GRIDSQUARE_NONE,
		GRIDSQUARE_GRASS,
		GRIDSQUARE_DIRT,
		GRIDSQUARE_POOL,
		GRIDSQUARE_HIGH_GROUND,
	};

	enum PlantRowType
	{
		PLANTROW_DIRT,
		PLANTROW_NORMAL,
		PLANTROW_POOL,
		PLANTROW_HIGH_GROUND,
	};

	enum BackgroundType
	{
		BACKGROUND_1_DAY,
		BACKGROUND_2_NIGHT,
		BACKGROUND_3_POOL,
		BACKGROUND_4_FOG,
		BACKGROUND_5_ROOF,
		BACKGROUND_6_BOSS,
		BACKGROUND_MUSHROOM_GARDEN,
		BACKGROUND_GREENHOUSE,
		BACKGROUND_ZOMBIQUARIUM,
		BACKGROUND_TREE_OF_WISDOM,
	};

	enum TutorialState
	{
		TUTORIAL_OFF,
		TUTORIAL_LEVEL_1_PICK_UP_PEASHOOTER,
		TUTORIAL_LEVEL_1_PLANT_PEASHOOTER,
		TUTORIAL_LEVEL_1_REFRESH_PEASHOOTER,
		TUTORIAL_LEVEL_1_COMPLETED,
		TUTORIAL_LEVEL_2_PICK_UP_SUNFLOWER,
		TUTORIAL_LEVEL_2_PLANT_SUNFLOWER,
		TUTORIAL_LEVEL_2_REFRESH_SUNFLOWER,
		TUTORIAL_LEVEL_2_COMPLETED,
		TUTORIAL_MORESUN_PICK_UP_SUNFLOWER,
		TUTORIAL_MORESUN_PLANT_SUNFLOWER,
		TUTORIAL_MORESUN_REFRESH_SUNFLOWER,
		TUTORIAL_MORESUN_COMPLETED,
		TUTORIAL_SLOT_MACHINE_PULL,
		TUTORIAL_SLOT_MACHINE_COMPLETED,
		TUTORIAL_SHOVEL_PICKUP,
		TUTORIAL_SHOVEL_DIG,
		TUTORIAL_SHOVEL_KEEP_DIGGING,
		TUTORIAL_SHOVEL_COMPLETED,
		TUTORIAL_ZOMBIQUARIUM_BUY_SNORKEL,
		TUTORIAL_ZOMBIQUARIUM_BOUGHT_SNORKEL,
		TUTORIAL_ZOMBIQUARIUM_CLICK_TROPHY,
		TUTORIAL_ZEN_GARDEN_PICKUP_WATER,
		TUTORIAL_ZEN_GARDEN_WATER_PLANT,
		TUTORIAL_ZEN_GARDEN_KEEP_WATERING,
		TUTORIAL_ZEN_GARDEN_VISIT_STORE,
		TUTORIAL_ZEN_GARDEN_FERTILIZE_PLANTS,
		TUTORIAL_ZEN_GARDEN_COMPLETED,
		TUTORIAL_WHACK_A_ZOMBIE_BEFORE_PICK_SEED,
		TUTORIAL_WHACK_A_ZOMBIE_PICK_SEED,
		TUTORIAL_WHACK_A_ZOMBIE_COMPLETED,
	};

	enum AdviceType
	{
		ADVICE_NONE = -1,
		ADVICE_CLICK_ON_SUN,
		ADVICE_CLICKED_ON_SUN,
		ADVICE_CLICKED_ON_COIN,
		ADVICE_SEED_REFRESH,
		ADVICE_CANT_AFFORD_PLANT,
		ADVICE_PLANT_GRAVEBUSTERS_ON_GRAVES,
		ADVICE_PLANT_LILYPAD_ON_WATER,
		ADVICE_PLANT_TANGLEKELP_ON_WATER,
		ADVICE_PLANT_SEASHROOM_ON_WATER,
		ADVICE_PLANT_POTATOE_MINE_ON_LILY,
		ADVICE_PLANT_WRONG_ART_TYPE,
		ADVICE_PLANT_NEED_POT,
		ADVICE_PLANT_NOT_ON_GRAVE,
		ADVICE_PLANT_NOT_ON_CRATER,
		ADVICE_CANT_PLANT_THERE,
		ADVICE_PLANT_NOT_ON_WATER,
		ADVICE_PLANTING_NEEDS_GROUND,
		ADVICE_BEGHOULED_DRAG_TO_MATCH_3,
		ADVICE_BEGHOULED_MATCH_3,
		ADVICE_BEGHOULED_MATCH_4,
		ADVICE_BEGHOULED_SAVE_SUN,
		ADVICE_BEGHOULED_USE_CRATER_1,
		ADVICE_BEGHOULED_USE_CRATER_2,
		ADVICE_PLANT_NOT_PASSED_LINE,
		ADVICE_PLANT_ONLY_ON_REPEATERS,
		ADVICE_PLANT_ONLY_ON_MELONPULT,
		ADVICE_PLANT_ONLY_ON_SUNFLOWER,
		ADVICE_PLANT_ONLY_ON_SPIKEWEED,
		ADVICE_PLANT_ONLY_ON_KERNELPULT,
		ADVICE_PLANT_ONLY_ON_MAGNETSHROOM,
		ADVICE_PLANT_ONLY_ON_FUMESHROOM,
		ADVICE_PLANT_ONLY_ON_LILYPAD,
		ADVICE_PLANT_NEEDS_REPEATER,
		ADVICE_PLANT_NEEDS_MELONPULT,
		ADVICE_PLANT_NEEDS_SUNFLOWER,
		ADVICE_PLANT_NEEDS_SPIKEWEED,
		ADVICE_PLANT_NEEDS_KERNELPULT,
		ADVICE_PLANT_NEEDS_MAGNETSHROOM,
		ADVICE_PLANT_NEEDS_FUMESHROOM,
		ADVICE_PLANT_NEEDS_LILYPAD,
		ADVICE_SLOT_MACHINE_PULL,
		ADVICE_HUGE_WAVE,
		ADVICE_SHOVEL_REFRESH,
		ADVICE_PORTAL_RELOCATING,
		ADVICE_SLOT_MACHINE_COLLECT_SUN,
		ADVICE_DESTORY_POTS_TO_FINISIH_LEVEL,
		ADVICE_USE_SHOVEL_ON_POTS,
		ADVICE_ALMOST_THERE,
		ADVICE_ZOMBIQUARIUM_CLICK_TROPHY,
		ADVICE_ZOMBIQUARIUM_COLLECT_SUN,
		ADVICE_ZOMBIQUARIUM_CLICK_TO_FEED,
		ADVICE_ZOMBIQUARIUM_BUY_SNORKEL,
		ADVICE_I_ZOMBIE_PLANTS_NOT_REAL,
		ADVICE_I_ZOMBIE_NOT_PASSED_LINE,
		ADVICE_I_ZOMBIE_LEFT_OF_LINE,
		ADVICE_SLOT_MACHINE_SPIN_AGAIN,
		ADVICE_I_ZOMBIE_EAT_ALL_BRAINS,
		ADVICE_PEASHOOTER_DIED,
		ADVICE_STINKY_SLEEPING,
		ADVICE_BEGHOULED_NO_MOVES,
		ADVICE_PLANT_SUNFLOWER5,
		ADVICE_PLANTING_NEED_SLEEPING,
		ADVICE_CLICK_TO_CONTINUE,
		ADVICE_SURVIVE_FLAGS,
		ADVICE_UNLOCKED_MODE,
		NUM_ADVICE_TYPES,
	};

	enum DebugTextMode
	{
		DEBUG_TEXT_NONE,
		DEBUG_TEXT_ZOMBIE_SPAWN,
		DEBUG_TEXT_MUSIC,
		DEBUG_TEXT_MEMORY,
		DEBUG_TEXT_COLLISION,
	};

	enum BoardResult
	{
		BOARDRESULT_NONE,
		BOARDRESULT_WON,
		BOARDRESULT_LOST,
		BOARDRESULT_RESTART,
		BOARDRESULT_QUIT,
		BOARDRESULT_QUIT_APP,
		BOARDRESULT_CHEAT,
	};

	enum PlantPriority
	{
		TOPPLANT_EATING_ORDER,
		TOPPLANT_DIGGING_ORDER,
		TOPPLANT_BUNGEE_ORDER,
		TOPPLANT_CATAPULT_ORDER,
		TOPPLANT_ZEN_TOOL_ORDER,
		TOPPLANT_ANY,
		TOPPLANT_ONLY_NORMAL_POSITION,
		TOPPLANT_ONLY_FLYING,
		TOPPLANT_ONLY_PUMPKIN,
		TOPPLANT_ONLY_UNDER_PLANT
	};

	enum PlantingReason
	{
		PLANTING_OK,
		PLANTING_NOT_HERE,
		PLANTING_ONLY_ON_GRAVES,
		PLANTING_ONLY_IN_POOL,
		PLANTING_ONLY_ON_GROUND,
		PLANTING_NEEDS_POT,
		PLANTING_NOT_ON_ART,
		PLANTING_NOT_PASSED_LINE,
		PLANTING_NEEDS_UPGRADE,
		PLANTING_NOT_ON_GRAVE,
		PLANTING_NOT_ON_CRATER,
		PLANTING_NOT_ON_WATER,
		PLANTING_NEEDS_GROUND,
		PLANTING_NEEDS_SLEEPING
	};

	struct TodSmoothArray
	{
		int mItem;
		float mWeight;
		float mLastPicked;
		float mSecondLastPicked;
	};

	class LawnApp;
	class CursorObject;
	class CursorPreview;
	class MessageWidget;
	class SeedBank;
	class GameButton;
	class ToolTipWidget;
	class CutScene;
	class Challenge;
	class InitPatch;
	enum ParticleSystemID;
	enum ZombieType;
	enum ReanimationID;

	namespace MagicZombie
	{
		void Binding_ExtendBase(InitPatch& patch, size_t theZombieSize, size_t theDataArraySize);
	}

	namespace MagicPlant
	{
		void Binding_ExtendBase(InitPatch& patch, size_t thePlantSize, size_t theDataArraySize);
	}

	constexpr int MAX_GRID_SIZE_X = 9, MAX_GRID_SIZE_Y = 6;
	constexpr int MAX_ZOMBIE_WAVES = 100, MAX_ZOMBIES_IN_WAVE = 50;

	/// 【游戏类】出怪计算信息。（原 ::ZombiePicker）
	class ZombiePicker
	{
	public:
		int								mZombieCount;
		int								mZombiePoints;
		int								mZombieTypeCount[NUM_ZOMBIE_TYPES];
		int								mAllWavesZombieTypeCount[NUM_ZOMBIE_TYPES];
	};

	void						ZombiePickerInitForWave(ZombiePicker* theZombiePicker);
	void						ZombiePickerInit(ZombiePicker* theZombiePicker);

	struct PlantsOnLawn
	{
		Plant*							mUnderPlant;
		Plant*							mPumpkinPlant;
		Plant*							mFlyingPlant;
		Plant*							mNormalPlant;
	};

	struct BungeeDropGrid
	{
		TodWeightedGridArray			mGridArray[MAX_GRID_SIZE_X * MAX_GRID_SIZE_Y];
		int								mGridArrayCount;
	};

	class HitResult
	{
	public:
		void* mObject;
		GameObjectType					mObjectType;
	};

	/// 【游戏类】关卡界面。（原 ::Board）
	class Board :public Widget, public ButtonListener
	{
	private:
		static size_t gExtraZombieSize;
		static size_t gExtraPlantSize;

	public:
		LawnApp*								mApp;
		DataArray<Zombie, &gExtraZombieSize>	mZombies;
		DataArray<Plant, &gExtraPlantSize>		mPlants;
		DataArray<Projectile>					mProjectiles;
		DataArray<Coin>							mCoins;
		DataArray<LawnMower>					mLawnMowers;
		DataArray<GridItem>						mGridItems;
		CursorObject*							mCursorObject;
		CursorPreview*							mCursorPreview;
		MessageWidget*							mAdvice;
		SeedBank*								mSeedBank;
		GameButton*								mMenuButton;
		GameButton*								mStoreButton;
		bool									mIgnoreMouseUp;
		ToolTipWidget*							mToolTip;
		Font*									mDebugFont;
		CutScene*								mCutScene;
		Challenge*								mChallenge;
		bool									mPaused;
		GridSquareType							mGridSquareType[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y];
		int										mGridCelLook[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y];
		int										mGridCelOffset[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y][2];
		int										mGridCelFog[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y + 1];
		bool									mEnableGraveStones;
		int										mSpecialGraveStoneX;
		int										mSpecialGraveStoneY;
		float									mFogOffset;
		int										mFogBlownCountDown;
		PlantRowType							mPlantRow[MAX_GRID_SIZE_Y];
		int										mWaveRowGotLawnMowered[MAX_GRID_SIZE_Y];
		int										mBonusLawnMowersRemaining;
		int										mIceMinX[MAX_GRID_SIZE_Y];
		int										mIceTimer[MAX_GRID_SIZE_Y];
		ParticleSystemID						mIceParticleID[MAX_GRID_SIZE_Y];
		TodSmoothArray							mRowPickingArray[MAX_GRID_SIZE_Y];
		ZombieType								mZombiesInWave[MAX_ZOMBIE_WAVES][MAX_ZOMBIES_IN_WAVE];
		bool									mZombieAllowed[100];
		int										mSunCountDown;
		int										mNumSunsFallen;
		int										mShakeCounter;
		int										mShakeAmountX;
		int										mShakeAmountY;
		BackgroundType							mBackground;
		int										mLevel;
		int										mSodPosition;
		int										mPrevMouseX;
		int										mPrevMouseY;
		int										mSunMoney;
		int										mNumWaves;
		int										mMainCounter;
		int										mEffectCounter;
		int										mDrawCount;
		int										mRiseFromGraveCounter;
		int										mOutOfMoneyCounter;
		int										mCurrentWave;
		int										mTotalSpawnedWaves;
		TutorialState							mTutorialState;
		ParticleSystemID						mTutorialParticleID;
		int										mTutorialTimer;
		int										mLastBungeeWave;
		int										mZombieHealthToNextWave;
		int										mZombieHealthWaveStart;
		int										mZombieCountDown;
		int										mZombieCountDownStart;
		int										mHugeWaveCountDown;
		bool									mHelpDisplayed[NUM_ADVICE_TYPES];
		AdviceType								mHelpIndex;
		bool									mFinalBossKilled;
		bool									mShowShovel;
		int										mCoinBankFadeCount;
		DebugTextMode							mDebugTextMode;
		bool									mLevelComplete;
		int										mBoardFadeOutCounter;
		int										mNextSurvivalStageCounter;
		int										mScoreNextMowerCounter;
		bool									mLevelAwardSpawned;
		int										mProgressMeterWidth;
		int										mFlagRaiseCounter;
		int										mIceTrapCounter;
		int										mBoardRandSeed;
		ParticleSystemID						mPoolSparklyParticleID;
		ReanimationID							mFwooshID[MAX_GRID_SIZE_Y][12];
		int										mFwooshCountDown;
		int										mTimeStopCounter;
		bool									mDroppedFirstCoin;
		int										mFinalWaveSoundCounter;
		int										mCobCannonCursorDelayCounter;
		int										mCobCannonMouseX;
		int										mCobCannonMouseY;
		bool									mKilledYeti;
		bool									mMustacheMode;
		bool									mSuperMowerMode;
		bool									mFutureMode;
		bool									mPinataMode;
		bool									mDaisyMode;
		bool									mSukhbirMode;
		BoardResult								mPrevBoardResult;
		int										mTriggeredLawnMowers;
		int										mPlayTimeActiveLevel;
		int										mPlayTimeInactiveLevel;
		int										mMaxSunPlants;
		int										mStartDrawTime;
		int										mIntervalDrawTime;
		int										mIntervalDrawCountStart;
		float									mMinFPS;
		int										mPreloadTime;
		int										mGameID;
		int										mGravesCleared;
		int										mPlantsEaten;
		int										mPlantsShoveled;
		int										mCoinsCollected;
		int										mDiamondsCollected;
		int										mPottedPlantsCollected;
		int										mChocolateCollected;

	public:
		// -------- 僵尸 --------

		// 生成
		Zombie*							AddZombie(ZombieType theZombieType, int theFromWave);
		Zombie*							AddZombieInRow(ZombieType theZombieType, int theRow, int theFromWave);
		void							SpawnZombiesFromGraves();
		void							SpawnZombiesFromPool();
		void							SpawnZombiesFromSky();
		void							BungeeDropZombie(BungeeDropGrid* theBungeeDropGrid, ZombieType theZombieType);

		// 移除
		void							RemoveAllZombies();
		void							RemoveCutsceneZombies();
		void							RemoveZombiesForRepick();

		// 获取
		bool							IterateZombies(Zombie*& theZombie);
		ZombieID						ZombieGetID(Zombie* theZombie);
		Zombie*							ZombieGet(ZombieID theZombieID);
		Zombie*							ZombieTryToGet(ZombieID theZombieID);
		Zombie*							ZombieHitTest(int theMouseX, int theMouseY);
		Zombie*							GetBossZombie();
		Zombie*							GetWinningZombie();

		// 查询
		int								PickRowForNewZombie(ZombieType theZombieType);
		bool							AreEnemyZombiesOnScreen();
		bool							RowCanHaveZombies(int theRow);
		bool							RowCanHaveZombieType(int theRow, ZombieType theZombieType);
		int								NumberZombiesInWave(int theWaveIndex);
		int								TotalZombiesHealthInWave(int theWaveIndex);
		static bool						CanZombieSpawnOnLevel(ZombieType theZombieType, int theLevel);
		bool							IsZombieWaveDistributionOk();
		static bool						IsZombieTypePoolOnly(ZombieType theZombieType);
		ZombieType						GetIntroducedZombieType();
		int								CountZombiesOnScreen();
		bool							StageHasZombieWalkInFromRight();
		int								CountZombieByType(ZombieType theZombieType);
		static bool						IsZombieTypeSpawnedOnly(ZombieType theZombieType);

		// 操作
		void							KillAllZombiesInRadius(int theRow, int theX, int theY, int theRadius, int theRowRange, bool theBurn, int theDamageRangeFlags);

		// -------- 植物 --------

		// 生成
		Plant*							AddPlant(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType = SeedType::SEED_NONE);
		Plant*							NewPlant(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType = SeedType::SEED_NONE);
		void							DoPlantingEffects(int theGridX, int theGridY, Plant* thePlant);
		
		// 移除
		void							KillAllPlantsInRadius(int theX, int theY, int theRadius);

		// 获取
		bool							IteratePlants(Plant*& thePlant);
		Plant*							GetTopPlantAt(int theGridX, int theGridY, PlantPriority thePriority);
		void							GetPlantsOnLawn(int theGridX, int theGridY, PlantsOnLawn* thePlantOnLawn);
		Plant*							GetPumpkinAt(int theGridX, int theGridY);
		Plant*							GetFlowerPotAt(int theGridX, int theGridY);
		Plant*							FindUmbrellaPlant(int theGridX, int theGridY);
		Plant*							SpecialPlantHitTest(int x, int y);
		Plant*							ToolHitTestHelper(HitResult* theHitResult);
		Plant*							ToolHitTest(int theX, int theY);

		// 查询
		PlantingReason					CanPlantAt(int theGridX, int theGridY, SeedType theSeedType);
		int								PlantingPixelToGridX(int theX, int theY, SeedType theSeedType);
		int								PlantingPixelToGridY(int theX, int theY, SeedType theSeedType);
		int								CountPlantByType(SeedType theSeedType);
		bool							PlantingRequirementsMet(SeedType theSeedType);
		bool							HasValidCobCannonSpot();
		bool							IsValidCobCannonSpot(int theGridX, int theGridY);
		bool							IsValidCobCannonSpotHelper(int theGridX, int theGridY);
		bool							IsPlantInCursor();
		bool							IsPlantInGoldWateringCanRange(int theMouseX, int theMouseY, Plant* thePlant);
		int								GetCurrentPlantCost(SeedType theSeedType, SeedType theImitaterType);
		bool							PlantUsesAcceleratedPricing(SeedType theSeedType);
		void							OffsetYForPlanting(int& theY, SeedType theSeedType);
		bool							MouseHitTestPlant(int x, int y, HitResult* theHitResult);

		// 操作
		void							HighlightPlantsForMouse(int theMouseX, int theMouseY);
		void							ClearFogAroundPlant(Plant* thePlant, int theSize);


		// -------- 暂未分类 ---------

		bool							IterateProjectiles(Projectile*& theProjectile);
		bool							IterateCoins(Coin*& theCoin);
		bool							IterateLawnMowers(LawnMower*& theLawnMower);
		bool							IterateGridItems(GridItem*& theGridItem);

		int								GetNumWavesPerSurvivalStage();
		bool							IsFlagWave(int theWaveNumber);
		int								GetNumWavesPerFlag();
		void							PutZombieInWave(ZombieType theZombieType, int theWaveNumber, ZombiePicker* theZombiePicker);
		void							PutInMissingZombies(int theWaveNumber, ZombiePicker* theZombiePicker);
		ZombieType						PickZombieType(int theZombiePoints, int theWaveIndex, ZombiePicker* theZombiePicker);

		int								GridToPixelX(int theGridX, int theGridY);
		int								GridToPixelY(int theGridX, int theGridY);

		bool							StageIsNight();

		static int						MakeRenderOrder(RenderLayer theRenderLayer, int theRow, int theLayerOffset);

		friend void MagicZombie::Binding_ExtendBase(InitPatch& patch, size_t theZombieSize, size_t theDataArraySize);
		friend void MagicPlant::Binding_ExtendBase(InitPatch& patch, size_t thePlantSize, size_t theDataArraySize);
	};
	static_assert(sizeof(Board) == 0x57b0);

	extern int* gZombieWaves;
}

#endif // !_PVZMOD_BOARD_H_
