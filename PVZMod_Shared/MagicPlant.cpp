#include "PVZMod.h"
#include "Board.h"
#include "MagicPlant.h"
#include "TodCommon.h"
#include "TodParticle.h"
#include "Reanimator.h"
#include "LawnApp.h"
#include "TodFoley.h"
#include "Res.h"

using namespace PVZMod;

void MagicPlant::Binding_ExtendBase(InitPatch& patch, size_t thePlantSize, size_t theDataArraySize)
{
	patch.PatchTask("MagicPlant::Binding_ExtendBase", [&]
		{
			*(size_t*)0x4092A2 = thePlantSize * theDataArraySize;
			if (theDataArraySize != 1024)
			{
				static const auto _theDataArraySize = theDataArraySize;
				patch.mHook.InsertCode((void*)0x4092da, [](Hook::Regs* regs)
					{
						*(size_t*)(regs->ebp + 0xb4) = _theDataArraySize;
					});
			}
			Board::gExtraPlantSize = thePlantSize - sizeof(Plant);
			if (thePlantSize != sizeof(Plant))
			{
				static const DWORD addresslist[] = {
					//Í¼¼ø
					0x00401D8C,
					0x00402FE3,
					//Board::MouseDownWithPlant
					0x00411F2E,
					//Board::ProcessDeleteQueue
					0x0041D47D,
					0x0041D48F,
					0x0041D4A7,
					0x0041D4AE,
					0x0041D4C3,
					0x0041D4D5,
					//Board::IteratePlants
					0x0041E2F5,
					0x0041E301,
					0x0041E312,
					0x0041E319,
					//DataArray<Plant>::DataArrayAlloc
					0x0041F80D,
					0x0041F814,
					0x0041F81F,
					0x0041F826,
					0x0041F83C,
					//DataArray<Plant>::DataArrayTryToGet
					0x0041F881,
					0x0041F88B,
					//DataArray<Plant>::DataArrayFreeAll
					0x004201FA,
					0x00420203,
					0x00420212,
					0x0042021D,
					0x00420225,
					0x0042023A,
					0x00420246,
					//CursorObject::Draw
					0x0043A8DD,
					//CursorPreview::Draw
					0x0043AD44,
					//Plant::MouseDown
					0x00469C35,
					//SyncDataArray<Plant>
					0x0048612E,
					//FixBoardAfterLoad
					0x00485A2D,
					0x00485A39,
					0x00485A57,
					0x00485A5E,
					//ZenGarden::MouseDownWithTool
					0x00523B23,
					//Zombie::BungeeStealTarget
					0x005291A7,
					//Zombie::BungeeLiftTarget
					0x00529226,
					0x00529230,
					//Zombie::DrawBungeeReanim
					0x00531030,
					0x0053103E,
					//Zombie::BungeeDropPlant
					0x005348A3,
					0x005348AB,
					//Zombie::BungeeDie
					0x00534915,
					0x0053491D
				};
				for (DWORD addr : addresslist)
				{
					DWORD* addrwrite = (DWORD*)addr;
					*addrwrite += thePlantSize - sizeof(Plant);
				}
			}
		}, true, true);
}

static PlantDefinition& _PlantInitialize_InitMemberVariable_base(Plant* _this, int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType)
{
	_this->mPlantCol = theGridX;
	_this->mRow = theGridY;
	if (_this->mBoard)
	{
		_this->mX = _this->mBoard->GridToPixelX(theGridX, theGridY);
		_this->mY = _this->mBoard->GridToPixelY(theGridX, theGridY);
	}
	_this->mAnimCounter = 0;
	_this->mAnimPing = true;
	_this->mFrame = 0;
	_this->mShootingCounter = 0;
	_this->mShakeOffsetX = 0.0f;
	_this->mShakeOffsetY = 0.0f;
	_this->mFrameLength = RandRangeInt(12, 18);
	_this->mTargetX = -1;
	_this->mTargetY = -1;
	_this->mStartRow = _this->mRow;
	_this->mNumFrames = 5;
	_this->mState = STATE_NOTREADY;
	_this->mDead = false;
	_this->mSquished = false;
	_this->mSeedType = theSeedType;
	_this->mImitaterType = theImitaterType;
	_this->mPlantHealth = 300;
	_this->mDoSpecialCountdown = 0;
	_this->mDisappearCountdown = 200;
	_this->mStateCountdown = 0;
	_this->mParticleID = PARTICLESYSTEMID_NULL;
	_this->mBodyReanimID = REANIMATIONID_NULL;
	_this->mHeadReanimID = REANIMATIONID_NULL;
	_this->mHeadReanimID2 = REANIMATIONID_NULL;
	_this->mHeadReanimID3 = REANIMATIONID_NULL;
	_this->mBlinkReanimID = REANIMATIONID_NULL;
	_this->mLightReanimID = REANIMATIONID_NULL;
	_this->mSleepingReanimID = REANIMATIONID_NULL;
	_this->mBlinkCountdown = 0;
	_this->mRecentlyEatenCountdown = 0;
	_this->mEatenFlashCountdown = 0;
	_this->mBeghouledFlashCountdown = 0;
	_this->mWidth = 80;
	_this->mHeight = 80;
	memset(_this->mMagnetItems, 0, sizeof(_this->mMagnetItems));
	_this->mIsAsleep = false;
	_this->mWakeUpCounter = 0;
	_this->mOnBungeeState = PLANT_NOT_ON_BUNGEE;
	_this->mPottedPlantIndex = -1;
	PlantDefinition& aPlantDef = GetPlantDefinition(theSeedType);
	_this->mLaunchRate = aPlantDef.mLaunchRate;
	_this->mSubclass = aPlantDef.mSubClass;
	_this->mRenderOrder = _this->CalcRenderOrder();
	return aPlantDef;
}

static auto _PlantInitialize_InitMemberVariable = _PlantInitialize_InitMemberVariable_base;

static Reanimation* _PlantInitialize_InitReanimation_base(Plant* _this, PlantDefinition& thePlantDef)
{
	Reanimation* aBodyReanim = nullptr;
	float aOffsetY = PlantDrawHeightOffset(_this->mBoard, _this, _this->mSeedType, _this->mPlantCol, _this->mRow);
	aBodyReanim = _this->mApp->AddReanimation(0.0f, aOffsetY, _this->mRenderOrder + 1, thePlantDef.mReanimationType);
	aBodyReanim->mLoopType = REANIM_LOOP;
	aBodyReanim->mAnimRate = RandRangeFloat(10.0f, 15.0f);

	if (aBodyReanim->TrackExists("anim_idle"))
		aBodyReanim->SetFramesForLayer("anim_idle");

	if (_this->mApp->IsWallnutBowlingLevel() && aBodyReanim->TrackExists("_ground"))
	{
		aBodyReanim->SetFramesForLayer("_ground");
		if (_this->mSeedType == SEED_WALLNUT || _this->mSeedType == SEED_EXPLODE_O_NUT)
			aBodyReanim->mAnimRate = RandRangeFloat(12.0f, 18.0f);
		else if (_this->mSeedType == SEED_GIANT_WALLNUT)
			aBodyReanim->mAnimRate = RandRangeFloat(6.0f, 10.0f);
	}

	aBodyReanim->mIsAttachment = true;
	_this->mBodyReanimID = _this->mApp->ReanimationGetID(aBodyReanim);
	_this->mBlinkCountdown = 400 + Rand(400);

	return aBodyReanim;
}

static auto _PlantInitialize_InitReanimation = _PlantInitialize_InitReanimation_base;

void _PlantInitialize_BeforeInitType_base(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim)
{
	if (_this->IsNocturnal(_this->mSeedType) && _this->mBoard && !_this->mBoard->StageIsNight())
		_this->SetSleeping(true);

	if (_this->mLaunchRate > 0)
	{
		if (_this->MakesSun())
			_this->mLaunchCounter = RandRangeInt(300, _this->mLaunchRate / 2);
		else
			_this->mLaunchCounter = RandRangeInt(0, _this->mLaunchRate);
	}
	else
		_this->mLaunchCounter = 0;
}

static auto _PlantInitialize_BeforeInitType = _PlantInitialize_BeforeInitType_base;

void _PlantInitialize_InitType_base(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim)
{
	switch (_this->mSeedType)
	{
	case SEED_BLOVER:
	{
		_this->mDoSpecialCountdown = 50;

		if (_this->IsInPlay())
		{
			theBodyReanim->SetFramesForLayer("anim_blow");
			theBodyReanim->mLoopType = REANIM_PLAY_ONCE_AND_HOLD;
			theBodyReanim->mAnimRate = 20.0f;
		}
		else
		{
			theBodyReanim->SetFramesForLayer("anim_idle");
			theBodyReanim->mAnimRate = 10.0f;
		}

		break;
	}
	case SEED_PEASHOOTER:
	case SEED_SNOWPEA:
	case SEED_REPEATER:
	case SEED_LEFTPEATER:
	case SEED_GATLINGPEA:
		if (theBodyReanim)
		{
			theBodyReanim->mAnimRate = RandRangeFloat(15.0f, 20.0f);
			Reanimation* aHeadReanim = _this->mApp->AddReanimation(0.0f, 0.0f, _this->mRenderOrder + 2, thePlantDef.mReanimationType);
			aHeadReanim->mLoopType = REANIM_LOOP;
			aHeadReanim->mAnimRate = theBodyReanim->mAnimRate;
			aHeadReanim->SetFramesForLayer("anim_head_idle");
			_this->mHeadReanimID = _this->mApp->ReanimationGetID(aHeadReanim);

			if (theBodyReanim->TrackExists("anim_stem"))
				aHeadReanim->AttachToAnotherReanimation(theBodyReanim, "anim_stem");
			else if (theBodyReanim->TrackExists("anim_idle"))
				aHeadReanim->AttachToAnotherReanimation(theBodyReanim, "anim_idle");
		}
		break;
	case SEED_SPLITPEA:
	{
		assert(theBodyReanim);

		theBodyReanim->mAnimRate = RandRangeFloat(15.0f, 20.0f);
		Reanimation* aHeadReanim1 = _this->mApp->AddReanimation(0.0f, 0.0f, _this->mRenderOrder + 2, thePlantDef.mReanimationType);
		aHeadReanim1->mLoopType = REANIM_LOOP;
		aHeadReanim1->mAnimRate = theBodyReanim->mAnimRate;
		aHeadReanim1->SetFramesForLayer("anim_head_idle");
		aHeadReanim1->AttachToAnotherReanimation(theBodyReanim, "anim_idle");
		_this->mHeadReanimID = _this->mApp->ReanimationGetID(aHeadReanim1);

		Reanimation* aHeadReanim2 = _this->mApp->AddReanimation(0.0f, 0.0f, _this->mRenderOrder + 2, thePlantDef.mReanimationType);
		aHeadReanim2->mLoopType = REANIM_LOOP;
		aHeadReanim2->mAnimRate = theBodyReanim->mAnimRate;
		aHeadReanim2->SetFramesForLayer("anim_splitpea_idle");
		aHeadReanim2->AttachToAnotherReanimation(theBodyReanim, "anim_idle");
		_this->mHeadReanimID2 = _this->mApp->ReanimationGetID(aHeadReanim2);

		break;
	}
	case SEED_THREEPEATER:
	{
		assert(theBodyReanim);

		theBodyReanim->mAnimRate = RandRangeFloat(15.0f, 20.0f);
		Reanimation* aHeadReanim1 = _this->mApp->AddReanimation(0.0f, 0.0f, _this->mRenderOrder + 2, thePlantDef.mReanimationType);
		aHeadReanim1->mLoopType = REANIM_LOOP;
		aHeadReanim1->mAnimRate = theBodyReanim->mAnimRate;
		aHeadReanim1->SetFramesForLayer("anim_head_idle1");
		aHeadReanim1->AttachToAnotherReanimation(theBodyReanim, "anim_head1");
		_this->mHeadReanimID = _this->mApp->ReanimationGetID(aHeadReanim1);

		Reanimation* aHeadReanim2 = _this->mApp->AddReanimation(0.0f, 0.0f, _this->mRenderOrder + 2, thePlantDef.mReanimationType);
		aHeadReanim2->mLoopType = REANIM_LOOP;
		aHeadReanim2->mAnimRate = theBodyReanim->mAnimRate;
		aHeadReanim2->SetFramesForLayer("anim_head_idle2");
		aHeadReanim2->AttachToAnotherReanimation(theBodyReanim, "anim_head2");
		_this->mHeadReanimID2 = _this->mApp->ReanimationGetID(aHeadReanim2);

		Reanimation* aHeadReanim3 = _this->mApp->AddReanimation(0.0f, 0.0f, _this->mRenderOrder + 2, thePlantDef.mReanimationType);
		aHeadReanim3->mLoopType = REANIM_LOOP;
		aHeadReanim3->mAnimRate = theBodyReanim->mAnimRate;
		aHeadReanim3->SetFramesForLayer("anim_head_idle3");
		aHeadReanim3->AttachToAnotherReanimation(theBodyReanim, "anim_head3");
		_this->mHeadReanimID3 = _this->mApp->ReanimationGetID(aHeadReanim3);

		break;
	}
	case SEED_WALLNUT:
		_this->mPlantHealth = 4000;
		_this->mBlinkCountdown = 1000 + Rand(1000);
		break;
	case SEED_EXPLODE_O_NUT:
		_this->mPlantHealth = 4000;
		_this->mBlinkCountdown = 1000 + Rand(1000);
		theBodyReanim->mColorOverride = Color(255, 64, 64);
		break;
	case SEED_GIANT_WALLNUT:
		_this->mPlantHealth = 4000;
		_this->mBlinkCountdown = 1000 + Rand(1000);
		break;
	case SEED_TALLNUT:
		_this->mPlantHealth = 8000;
		_this->mHeight = 80;
		_this->mBlinkCountdown = 1000 + Rand(1000);
		break;
	case SEED_GARLIC:
		assert(theBodyReanim);
		_this->mPlantHealth = 400;
		theBodyReanim->SetTruncateDisappearingFrames();
		break;
	case SEED_GOLD_MAGNET:
		assert(theBodyReanim);
		theBodyReanim->SetTruncateDisappearingFrames();
		break;
	case SEED_IMITATER:
		assert(theBodyReanim);
		theBodyReanim->mAnimRate = RandRangeFloat(25.0f, 30.0f);
		_this->mStateCountdown = 200;
		break;
	case SEED_CHERRYBOMB:
	case SEED_JALAPENO:
	{
		assert(theBodyReanim);

		if (_this->IsInPlay())
		{
			_this->mDoSpecialCountdown = 100;

			theBodyReanim->SetFramesForLayer("anim_explode");
			theBodyReanim->mLoopType = REANIM_PLAY_ONCE_AND_HOLD;

			_this->mApp->PlayFoley(FOLEY_REVERSE_EXPLOSION);
		}

		break;
	}
	case SEED_POTATOMINE:
	{
		assert(theBodyReanim);

		theBodyReanim->mAnimRate = 12.0f;

		if (_this->IsInPlay())
		{
			theBodyReanim->AssignRenderGroupToTrack("anim_glow", RENDER_GROUP_HIDDEN);
			_this->mStateCountdown = 1500;
		}
		else
		{
			theBodyReanim->SetFramesForLayer("anim_armed");
			_this->mState = STATE_POTATO_ARMED;
		}

		break;
	}
	case SEED_GRAVEBUSTER:
	{
		assert(theBodyReanim);

		if (_this->IsInPlay())
		{
			theBodyReanim->SetFramesForLayer("anim_land");
			theBodyReanim->mLoopType = REANIM_PLAY_ONCE_AND_HOLD;

			_this->mState = STATE_GRAVEBUSTER_LANDING;
			_this->mApp->PlayFoley(FOLEY_GRAVEBUSTERCHOMP);
		}

		break;
	}
	case SEED_SUNSHROOM:
	{
		assert(theBodyReanim);

		theBodyReanim->mFrameBasePose = 6;

		if (_this->IsInPlay())
		{
			_this->mX += Rand(10) - 5;
			_this->mY += Rand(10) - 5;
		}
		else if (_this->mIsAsleep)
			theBodyReanim->SetFramesForLayer("anim_bigsleep");
		else
			theBodyReanim->SetFramesForLayer("anim_bigidle");

		_this->mState = STATE_SUNSHROOM_SMALL;
		_this->mStateCountdown = 12000;

		break;
	}
	case SEED_PUFFSHROOM:
	case SEED_SEASHROOM:
		if (_this->IsInPlay())
		{
			_this->mX += Rand(10) - 5;
			_this->mY += Rand(6) - 3;
		}
		break;
	case SEED_PUMPKINSHELL:
	{
		_this->mPlantHealth = 4000;
		_this->mWidth = 120;

		assert(theBodyReanim);
		theBodyReanim->AssignRenderGroupToTrack("Pumpkin_back", 1);
		break;
	}
	case SEED_CHOMPER:
		_this->mState = STATE_READY;
		break;
	case SEED_PLANTERN:
	{
		_this->mStateCountdown = 50;

		if (!_this->IsOnBoard() || _this->mApp->mGameMode != GAMEMODE_CHALLENGE_ZEN_GARDEN)
		{
			_this->AddAttachedParticle(_this->mX + 40, _this->mY + 40, (int)RENDER_LAYER_FOG + 1, PARTICLE_LANTERN_SHINE);
		}
		if (_this->IsInPlay())
		{
			_this->mApp->PlaySample(SOUND_PLANTERN);
		}

		break;
	}
	case SEED_TORCHWOOD:
		break;
	case SEED_MARIGOLD:
		assert(theBodyReanim);
		theBodyReanim->mAnimRate = RandRangeFloat(15.0f, 20.0f);
		break;
	case SEED_CACTUS:
		_this->mState = STATE_CACTUS_LOW;
		break;
	case SEED_INSTANT_COFFEE:
		_this->mDoSpecialCountdown = 100;
		break;
	case SEED_SCAREDYSHROOM:
		_this->mState = STATE_READY;
		break;
	case SEED_COBCANNON:
		if (_this->IsInPlay())
		{
			_this->mState = STATE_COBCANNON_ARMING;
			_this->mStateCountdown = 500;

			assert(theBodyReanim);
			theBodyReanim->SetFramesForLayer("anim_unarmed_idle");
		}
		break;
	case SEED_KERNELPULT:
		assert(theBodyReanim);
		theBodyReanim->AssignRenderGroupToPrefix("Cornpult_butter", RENDER_GROUP_HIDDEN);
		break;
	case SEED_MAGNETSHROOM:
		assert(theBodyReanim);
		theBodyReanim->SetTruncateDisappearingFrames();
		break;
	case SEED_SPIKEROCK:
		_this->mPlantHealth = 450;
		assert(theBodyReanim);
		break;
	case SEED_SPROUT:
		break;
	case SEED_FLOWERPOT:
		if (_this->IsInPlay())
		{
			_this->mState = STATE_FLOWERPOT_INVULNERABLE;
			_this->mStateCountdown = 100;
		}
		break;
	case SEED_LILYPAD:
		if (_this->IsInPlay())
		{
			_this->mState = STATE_LILYPAD_INVULNERABLE;
			_this->mStateCountdown = 100;
		}
		break;
	case SEED_TANGLEKELP:
		assert(theBodyReanim);
		theBodyReanim->SetTruncateDisappearingFrames();
	}
}

static auto _PlantInitialize_InitType = _PlantInitialize_InitType_base;

void _PlantInitialize_AfterInitType_base(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim)
{
	if ((_this->mApp->mGameMode == GAMEMODE_CHALLENGE_BIG_TIME) &&
		(_this->mSeedType == SEED_WALLNUT || _this->mSeedType == SEED_SUNFLOWER || _this->mSeedType == SEED_MARIGOLD))
	{
		_this->mPlantHealth *= 2;
	}
	_this->mPlantMaxHealth = _this->mPlantHealth;

	if (_this->mSeedType != SEED_FLOWERPOT && _this->IsOnBoard())
	{
		assert(_this->mBoard);
		Plant* aFlowerPot = _this->mBoard->GetFlowerPotAt(_this->mPlantCol, _this->mRow);
		if (aFlowerPot)
			_this->mApp->ReanimationGet(aFlowerPot->mBodyReanimID)->mAnimRate = 0.0f;
	}
}

static auto _PlantInitialize_AfterInitType = _PlantInitialize_AfterInitType_base;

static void _PatchMF_PlantInitialize(InitPatch& patch)
{
	patch.PatchTask("_PatchMF_PlantInitialize", [&]
		{
			patch.mHook.InsertCodeAndJump((void*)0x461330, (void*)0x461f80, [](Hook::Regs* regs)
				{
					Plant* _this = *(Plant**)(regs->esp + 0x4);
					int aGridX = (int)regs->ecx;
					int aGridY = (int)regs->eax;
					SeedType aSeedType = *(SeedType*)(regs->esp + 0x8);
					SeedType aImitaterType = *(SeedType*)(regs->esp + 0xc); 

					PlantDefinition& aPlantDef = _PlantInitialize_InitMemberVariable(_this, aGridX, aGridY, aSeedType, aImitaterType);

					Reanimation* aBodyReanim = nullptr;
					if (aPlantDef.mReanimationType != REANIM_NONE)
						aBodyReanim = _PlantInitialize_InitReanimation(_this, aPlantDef);

					_PlantInitialize_BeforeInitType(_this, aPlantDef, aBodyReanim);
					_PlantInitialize_InitType(_this, aPlantDef, aBodyReanim);
					_PlantInitialize_AfterInitType(_this, aPlantDef, aBodyReanim);
				});
		});
}

void MagicPlant::Binding_MF_PlantInitialize_InitMemberVariable(InitPatch& patch, const std::function<PlantDefinition& (Plant* _this, int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType, PlantInitialize_InitMemberVariable_t& base)>& func)
{
	patch.PatchTask("MagicPlant::Binding_MF_PlantInitialize_InitMemberVariable", [&]
		{
			static std::vector<std::function<PlantDefinition& (Plant* _this, int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType, PlantInitialize_InitMemberVariable_t& base)>> func_list;
			patch.PatchTask("MagicPlant::Binding_MF_PlantInitialize_InitMemberVariable(Hook)", [&]
				{
					_PatchMF_PlantInitialize(patch);
					_PlantInitialize_InitMemberVariable = [](Plant* _this, int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType) -> PlantDefinition&
					{
						PlantInitialize_InitMemberVariable_t base;

						base.mFunction = [&](Plant* __this, int _theGridX, int _theGridY, SeedType _theSeedType, SeedType _theImitaterType) -> PlantDefinition&
						{
							std::swap(_this, __this);
							std::swap(theGridX, _theGridX);
							std::swap(theGridY, _theGridY);
							std::swap(theSeedType, _theSeedType);
							std::swap(theImitaterType, _theImitaterType);
							auto& result = base();
							_this = __this;
							theGridX = _theGridX;
							theGridY = _theGridY;
							theSeedType = _theSeedType;
							theImitaterType = _theImitaterType;
							return result;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable -> PlantDefinition&
						{
							if (i == 0)
								return _PlantInitialize_InitMemberVariable_base(_this, theGridX, theGridY, theSeedType, theImitaterType);
							else
							{
								i--;
								auto& result = func_list[i](_this, theGridX, theGridY, theSeedType, theImitaterType, base);
								i++;
								return result;
							}
						};

						return func_list.back()(_this, theGridX, theGridY, theSeedType, theImitaterType, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicPlant::Binding_MF_PlantInitialize_InitReanimation(InitPatch& patch, const std::function<Reanimation* (Plant* _this, PlantDefinition& thePlantDef, PlantInitialize_InitReanimation& base)>& func)
{
	patch.PatchTask("MagicPlant::Binding_MF_PlantInitialize_InitReanimation", [&]
		{
			static std::vector<std::function<Reanimation* (Plant* _this, PlantDefinition& thePlantDef, PlantInitialize_InitReanimation& base)>> func_list;
			patch.PatchTask("MagicPlant::Binding_MF_PlantInitialize_InitReanimation(Hook)", [&]
				{
					_PatchMF_PlantInitialize(patch);
					_PlantInitialize_InitReanimation = [](Plant* _this, PlantDefinition& thePlantDef)
					{
						PlantInitialize_InitReanimation base;
						auto p_thePlantDef = &thePlantDef;

						base.mFunction = [&](Plant* __this, PlantDefinition& _thePlantDef)
						{
							auto _p_thePlantDef = &_thePlantDef;
							std::swap(_this, __this);
							std::swap(p_thePlantDef, _p_thePlantDef);
							auto result = base();
							_this = __this;
							p_thePlantDef = _p_thePlantDef;
							return result;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								return _PlantInitialize_InitReanimation_base(_this, *p_thePlantDef);
							else
							{
								i--;
								auto result = func_list[i](_this, *p_thePlantDef, base);
								i++;
								return result;
							}
						};

						return func_list.back()(_this, thePlantDef, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicPlant::Binding_MF_PlantInitialize_BeforeInitType(InitPatch& patch, const std::function<void(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_BeforeInitType& base)>& func)
{
	patch.PatchTask("MagicPlant::Binding_MF_PlantInitialize_BeforeInitType", [&]
		{
			static std::vector<std::function<void(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_BeforeInitType& base)>> func_list;
			patch.PatchTask("MagicPlant::Binding_MF_PlantInitialize_BeforeInitType(Hook)", [&]
				{
					_PatchMF_PlantInitialize(patch);
					_PlantInitialize_BeforeInitType = [](Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim)
					{
						PlantInitialize_BeforeInitType base;
						auto p_thePlantDef = &thePlantDef;

						base.mFunction = [&](Plant* __this, PlantDefinition& _thePlantDef, Reanimation* _theBodyReanim)
						{
							auto _p_thePlantDef = &_thePlantDef;
							std::swap(_this, __this);
							std::swap(p_thePlantDef, _p_thePlantDef);
							std::swap(theBodyReanim, _theBodyReanim);
							base();
							_this = __this;
							p_thePlantDef = _p_thePlantDef;
							theBodyReanim = _theBodyReanim;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_PlantInitialize_BeforeInitType_base(_this, *p_thePlantDef, theBodyReanim);
							else
							{
								i--;
								func_list[i](_this, *p_thePlantDef, theBodyReanim, base);
								i++;
							}
						};

						func_list.back()(_this, thePlantDef, theBodyReanim, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicPlant::Binding_MF_PlantInitialize_InitType(InitPatch& patch, const std::function<void(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_InitType& base)>& func)
{
	patch.PatchTask("MagicPlant::Binding_MF_PlantInitialize_InitType", [&]
		{
			static std::vector<std::function<void(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_InitType& base)>> func_list;
			patch.PatchTask("MagicPlant::Binding_MF_PlantInitialize_InitType(Hook)", [&]
				{
					_PatchMF_PlantInitialize(patch);
					_PlantInitialize_InitType = [](Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim)
					{
						PlantInitialize_InitType base;
						auto p_thePlantDef = &thePlantDef;

						base.mFunction = [&](Plant* __this, PlantDefinition& _thePlantDef, Reanimation* _theBodyReanim)
						{
							auto _p_thePlantDef = &_thePlantDef;
							std::swap(_this, __this);
							std::swap(p_thePlantDef, _p_thePlantDef);
							std::swap(theBodyReanim, _theBodyReanim);
							base();
							_this = __this;
							p_thePlantDef = _p_thePlantDef;
							theBodyReanim = _theBodyReanim;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_PlantInitialize_InitType_base(_this, *p_thePlantDef, theBodyReanim);
							else
							{
								i--;
								func_list[i](_this, *p_thePlantDef, theBodyReanim, base);
								i++;
							}
						};

						func_list.back()(_this, thePlantDef, theBodyReanim, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicPlant::Binding_MF_PlantInitialize_AfterInitType(InitPatch& patch, const std::function<void(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_AfterInitType& base)>& func)
{
	patch.PatchTask("MagicPlant::Binding_MF_PlantInitialize_AfterInitType", [&]
		{
			static std::vector<std::function<void(Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_AfterInitType& base)>> func_list;
			patch.PatchTask("MagicPlant::Binding_MF_PlantInitialize_AfterInitType(Hook)", [&]
				{
					_PatchMF_PlantInitialize(patch);
					_PlantInitialize_AfterInitType = [](Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim)
					{
						PlantInitialize_AfterInitType base;
						auto p_thePlantDef = &thePlantDef;

						base.mFunction = [&](Plant* __this, PlantDefinition& _thePlantDef, Reanimation* _theBodyReanim)
						{
							auto _p_thePlantDef = &_thePlantDef;
							std::swap(_this, __this);
							std::swap(p_thePlantDef, _p_thePlantDef);
							std::swap(theBodyReanim, _theBodyReanim);
							base();
							_this = __this;
							p_thePlantDef = _p_thePlantDef;
							theBodyReanim = _theBodyReanim;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_PlantInitialize_AfterInitType_base(_this, *p_thePlantDef, theBodyReanim);
							else
							{
								i--;
								func_list[i](_this, *p_thePlantDef, theBodyReanim, base);
								i++;
							}
						};

						func_list.back()(_this, thePlantDef, theBodyReanim, base);
					};
				});
			func_list.push_back(func);
		}, false);
}
