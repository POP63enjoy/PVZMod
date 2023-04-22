#pragma once
#ifndef _PVZMOD_REANIMATOR_H_
#define _PVZMOD_REANIMATOR_H_

#include "SexyMatrix.h"
#include "Color.h"
#include "DataArray.h"
#include "Rect.h"

namespace PVZMod
{
	enum ReanimLoopType
	{
		REANIM_LOOP,
		REANIM_LOOP_FULL_LAST_FRAME,
		REANIM_PLAY_ONCE,
		REANIM_PLAY_ONCE_AND_HOLD,
		REANIM_PLAY_ONCE_FULL_LAST_FRAME,
		REANIM_PLAY_ONCE_FULL_LAST_FRAME_AND_HOLD,
	};

	enum FilterEffect
	{
		FILTER_EFFECT_NONE = -1,
		FILTER_EFFECT_WASHED_OUT,
		FILTER_EFFECT_LESS_WASHED_OUT,
		FILTER_EFFECT_WHITE,
		NUM_FILTER_EFFECTS,
	};

	enum ReanimationID
	{
		REANIMATIONID_NULL,
	};

	enum ReanimationType
	{
		REANIM_NONE = -1,
		REANIM_LOADBAR_SPROUT,
		REANIM_LOADBAR_ZOMBIEHEAD,
		REANIM_SODROLL,
		REANIM_FINAL_WAVE,
		REANIM_PEASHOOTER,
		REANIM_WALLNUT,
		REANIM_LILYPAD,
		REANIM_SUNFLOWER,
		REANIM_LAWNMOWER,
		REANIM_READYSETPLANT,
		REANIM_CHERRYBOMB,
		REANIM_SQUASH,
		REANIM_DOOMSHROOM,
		REANIM_SNOWPEA,
		REANIM_REPEATER,
		REANIM_SUNSHROOM,
		REANIM_TALLNUT,
		REANIM_FUMESHROOM,
		REANIM_PUFFSHROOM,
		REANIM_HYPNOSHROOM,
		REANIM_CHOMPER,
		REANIM_ZOMBIE,
		REANIM_SUN,
		REANIM_POTATOMINE,
		REANIM_SPIKEWEED,
		REANIM_SPIKEROCK,
		REANIM_THREEPEATER,
		REANIM_MARIGOLD,
		REANIM_ICESHROOM,
		REANIM_ZOMBIE_FOOTBALL,
		REANIM_ZOMBIE_NEWSPAPER,
		REANIM_ZOMBIE_ZAMBONI,
		REANIM_SPLASH,
		REANIM_JALAPENO,
		REANIM_JALAPENO_FIRE,
		REANIM_COIN_SILVER,
		REANIM_ZOMBIE_CHARRED,
		REANIM_ZOMBIE_CHARRED_IMP,
		REANIM_ZOMBIE_CHARRED_DIGGER,
		REANIM_ZOMBIE_CHARRED_ZAMBONI,
		REANIM_ZOMBIE_CHARRED_CATAPULT,
		REANIM_ZOMBIE_CHARRED_GARGANTUAR,
		REANIM_SCRAREYSHROOM,
		REANIM_PUMPKIN,
		REANIM_PLANTERN,
		REANIM_TORCHWOOD,
		REANIM_SPLITPEA,
		REANIM_SEASHROOM,
		REANIM_BLOVER,
		REANIM_FLOWER_POT,
		REANIM_CACTUS,
		REANIM_DANCER,
		REANIM_TANGLEKELP,
		REANIM_STARFRUIT,
		REANIM_POLEVAULTER,
		REANIM_BALLOON,
		REANIM_GARGANTUAR,
		REANIM_IMP,
		REANIM_DIGGER,
		REANIM_DIGGER_DIRT,
		REANIM_ZOMBIE_DOLPHINRIDER,
		REANIM_POGO,
		REANIM_BACKUP_DANCER,
		REANIM_BOBSLED,
		REANIM_JACKINTHEBOX,
		REANIM_SNORKEL,
		REANIM_BUNGEE,
		REANIM_CATAPULT,
		REANIM_LADDER,
		REANIM_PUFF,
		REANIM_SLEEPING,
		REANIM_GRAVE_BUSTER,
		REANIM_ZOMBIES_WON,
		REANIM_MAGNETSHROOM,
		REANIM_BOSS,
		REANIM_CABBAGEPULT,
		REANIM_KERNELPULT,
		REANIM_MELONPULT,
		REANIM_COFFEEBEAN,
		REANIM_UMBRELLALEAF,
		REANIM_GATLINGPEA,
		REANIM_CATTAIL,
		REANIM_GLOOMSHROOM,
		REANIM_BOSS_ICEBALL,
		REANIM_BOSS_FIREBALL,
		REANIM_COBCANNON,
		REANIM_GARLIC,
		REANIM_GOLD_MAGNET,
		REANIM_WINTER_MELON,
		REANIM_TWIN_SUNFLOWER,
		REANIM_POOL_CLEANER,
		REANIM_ROOF_CLEANER,
		REANIM_FIRE_PEA,
		REANIM_IMITATER,
		REANIM_YETI,
		REANIM_BOSS_DRIVER,
		REANIM_LAWN_MOWERED_ZOMBIE,
		REANIM_CRAZY_DAVE,
		REANIM_TEXT_FADE_ON,
		REANIM_HAMMER,
		REANIM_SLOT_MACHINE_HANDLE,
		REANIM_CREDITS_FOOTBALL,
		REANIM_CREDITS_JACKBOX,
		REANIM_SELECTOR_SCREEN,
		REANIM_PORTAL_CIRCLE,
		REANIM_PORTAL_SQUARE,
		REANIM_ZENGARDEN_SPROUT,
		REANIM_ZENGARDEN_WATERINGCAN,
		REANIM_ZENGARDEN_FERTILIZER,
		REANIM_ZENGARDEN_BUGSPRAY,
		REANIM_ZENGARDEN_PHONOGRAPH,
		REANIM_DIAMOND,
		REANIM_ZOMBIE_HAND,
		REANIM_STINKY,
		REANIM_RAKE,
		REANIM_RAIN_CIRCLE,
		REANIM_RAIN_SPLASH,
		REANIM_ZOMBIE_SURPRISE,
		REANIM_COIN_GOLD,
		REANIM_TREEOFWISDOM,
		REANIM_TREEOFWISDOM_CLOUDS,
		REANIM_TREEOFWISDOM_TREEFOOD,
		REANIM_CREDITS_MAIN,
		REANIM_CREDITS_MAIN2,
		REANIM_CREDITS_MAIN3,
		REANIM_ZOMBIE_CREDITS_DANCE,
		REANIM_CREDITS_STAGE,
		REANIM_CREDITS_BIGBRAIN,
		REANIM_CREDITS_FLOWER_PETALS,
		REANIM_CREDITS_INFANTRY,
		REANIM_CREDITS_THROAT,
		REANIM_CREDITS_CRAZYDAVE,
		REANIM_CREDITS_BOSSDANCE,
		REANIM_ZOMBIE_CREDITS_SCREEN_DOOR,
		REANIM_ZOMBIE_CREDITS_CONEHEAD,
		REANIM_CREDITS_ZOMBIEARMY1,
		REANIM_CREDITS_ZOMBIEARMY2,
		REANIM_CREDITS_TOMBSTONES,
		REANIM_CREDITS_SOLARPOWER,
		REANIM_CREDITS_ANYHOUR,
		REANIM_CREDITS_WEARETHEUNDEAD,
		REANIM_CREDITS_DISCOLIGHTS,
		REANIM_FLAG,
		NUM_REANIMS
	};

	enum
	{
		RENDER_GROUP_HIDDEN = -1,
		RENDER_GROUP_NORMAL = 0
	};

	enum ReanimFlags
	{
		REANIM_NO_ATLAS,
		REANIM_FAST_DRAW_IN_SW_MODE
	};

	enum AttachmentID;
	class MemoryImage;
	class Image;
	class Font;
	class TodTriangleGroup;
	class AttachEffect;
	class TodParticleSystem;
	class AttacherInfo;
	class ReanimationHolder;
	class Graphics;

	constexpr const float DEFAULT_FIELD_PLACEHOLDER = -10000.0f;

	struct ReanimAtlasImage
	{
		int		mX;
		int		mY;
		int		mWidth;
		int		mHeight;
		Image*	mOriginalImage;
	};

	class ReanimAtlas
	{
	public:
		ReanimAtlasImage	mImageArray[64];
		int					mImageCount;
		MemoryImage*		mMemoryImage;
	};

	class ReanimatorTransform
	{
	public:
		float			mTransX;
		float			mTransY;
		float			mSkewX;
		float			mSkewY;
		float			mScaleX;
		float			mScaleY;
		float			mFrame;
		float			mAlpha;
		Image*			mImage;
		Font*			mFont;
		const char*		mText;

	public:
		ReanimatorTransform();
	};

	struct ReanimatorTrack
	{
		char*					mName;
		ReanimatorTransform*	mTransforms;
		int						mTransformCount;
	};

	class ReanimatorDefinition
	{
	public:
		ReanimatorTrack*		mTracks;
		int						mTrackCount;
		float					mFPS;
		ReanimAtlas*			mReanimAtlas;
	};

	class ReanimationParams
	{
	public:
		ReanimationType				 mReanimationType;
		const char*					 mReanimFileName;
		int							 mReanimParamFlags;
	};

	class ReanimatorTrackInstance
	{
	public:
		int								mBlendCounter;
		int								mBlendTime;
		ReanimatorTransform				mBlendTransform;
		float							mShakeOverride;
		float							mShakeX;
		float							mShakeY;
		AttachmentID					mAttachmentID;
		Image*							mImageOverride;
		int								mRenderGroup;
		Color							mTrackColor;
		bool							mIgnoreClipRect;
		bool							mTruncateDisappearingFrames;
		bool							mIgnoreColorOverride;
		bool							mIgnoreExtraAdditiveColor;

	public:
		ReanimatorTrackInstance();
	};

	class ReanimatorFrameTime
	{
	public:
		float                           mFraction;           
		int                             mAnimFrameBeforeInt; 
		int                             mAnimFrameAfterInt;  
	};

	/// 【游戏类】动画。（原 `::%Reanimation`）
	class Reanimation
	{
	public:
		ReanimationType				mReanimationType;
		float						mAnimTime;
		float						mAnimRate;
		ReanimatorDefinition*		mDefinition;
		ReanimLoopType				mLoopType;
		bool						mDead;
		int							mFrameStart;
		int							mFrameCount;
		int							mFrameBasePose;
		SexyTransform2D				mOverlayMatrix;
		Color						mColorOverride;
		ReanimatorTrackInstance*	mTrackInstances;
		int							mLoopCount;
		ReanimationHolder*			mReanimationHolder;
		bool						mIsAttachment;
		int							mRenderOrder;
		Color						mExtraAdditiveColor;
		bool						mEnableExtraAdditiveDraw;
		Color						mExtraOverlayColor;
		bool						mEnableExtraOverlayDraw;
		float						mLastFrameTime;
		FilterEffect				mFilterEffect;

	public:
		Reanimation();
		~Reanimation();

		void                            ReanimationInitialize(float theX, float theY, ReanimatorDefinition* theDefinition);
		void						    ReanimationInitializeType(float theX, float theY, ReanimationType theReanimType);
		void                            ReanimationDie();
		void                            Update();
		void							Draw(Graphics* g);
		void                            DrawRenderGroup(Graphics* g, int theRenderGroup);
		bool                            DrawTrack(Graphics* g, int theTrackIndex, int theRenderGroup, TodTriangleGroup* theTriangleGroup);
		void                            GetCurrentTransform(int theTrackIndex, ReanimatorTransform* theTransformCurrent);
		void                            GetTransformAtTime(int theTrackIndex, ReanimatorTransform* theTransform, ReanimatorFrameTime* theFrameTime);
		void                            GetFrameTime(ReanimatorFrameTime* theFrameTime);
		int                             FindTrackIndex(const char* theTrackName);
		void                            AttachToAnotherReanimation(Reanimation* theAttachReanim, const char* theTrackName);
		void                            GetAttachmentOverlayMatrix(int theTrackIndex, SexyTransform2D& theOverlayMatrix);
		void							SetFramesForLayer(const char* theTrackName);
		static void                     MatrixFromTransform(const ReanimatorTransform& theTransform, SexyMatrix3& theMatrix);
		bool                            TrackExists(const char* theTrackName);
		void                            StartBlend(int theBlendTime);
		void							SetShakeOverride(const char* theTrackName, float theShakeAmount);
		void							SetPosition(float theX, float theY);
		void							OverrideScale(float theScaleX, float theScaleY);
		float                           GetTrackVelocity(const char* theTrackName);
		void							SetImageOverride(const char* theTrackName, Image* theImage);
		Image*							GetImageOverride(const char* theTrackName);
		void                            ShowOnlyTrack(const char* theTrackName);
		void                            GetTrackMatrix(int theTrackIndex, SexyTransform2D& theMatrix);
		void                            AssignRenderGroupToTrack(const char* theTrackName, int theRenderGroup);
		void                            AssignRenderGroupToPrefix(const char* theTrackName, int theRenderGroup);
		void                            PropogateColorToAttachments();
		bool                            ShouldTriggerTimedEvent(float theEventTime);
		void                            TodTriangleGroupDraw(Graphics* g, TodTriangleGroup* theTriangleGroup) { ; }
		Image*                          GetCurrentTrackImage(const char* theTrackName);
		AttachEffect*                   AttachParticleToTrack(const char* theTrackName, TodParticleSystem* theParticleSystem, float thePosX, float thePosY);
		void                            GetTrackBasePoseMatrix(int theTrackIndex, SexyTransform2D& theBasePosMatrix);
		bool                            IsTrackShowing(const char* theTrackName);
		void							SetTruncateDisappearingFrames(const char* theTrackName = nullptr, bool theTruncateDisappearingFrames = false);
		void							PlayReanim(const char* theTrackName, ReanimLoopType theLoopType, int theBlendTime, float theAnimRate);
		void                            ReanimationDelete();
		ReanimatorTrackInstance*        GetTrackInstanceByName(const char* theTrackName);
		void                            GetFramesForLayer(const char* theTrackName, int& theFrameStart, int& theFrameCount);
		void                            UpdateAttacherTrack(int theTrackIndex);
		static void                     ParseAttacherTrack(const ReanimatorTransform& theTransform, AttacherInfo& theAttacherInfo);
		void                            AttacherSynchWalkSpeed(int theTrackIndex, Reanimation* theAttachReanim, AttacherInfo& theAttacherInfo);
		bool							IsAnimPlaying(const char* theTrackName);
		void                            SetBasePoseFromAnim(const char* theTrackName);
		void                            ReanimBltMatrix(Graphics* g, Image* theImage, SexyMatrix3& theTransform, const Rect& theClipRect, const Color& theColor, int theDrawMode, const Rect& theSrcRect);
		Reanimation*                    FindSubReanim(ReanimationType theReanimType);
	};

	class ReanimationHolder
	{
	public:
		DataArray<Reanimation> mReanimations;
	};
}

#endif // !_PVZMOD_REANIMATOR_H_
