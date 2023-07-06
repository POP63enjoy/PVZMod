#include "PVZMod.h"
#include "Zombie.h"
#include "MagicZombie.h"
#include "Board.h"
#include "Reanimator.h"
#include "Attachment.h"
#include "LawnApp.h"
#include "TodParticle.h"
#include "Res.h"

using namespace PVZMod;

void MagicZombie::Binding_ExtendBase(InitPatch& patch, size_t theZombieSize, size_t theDataArraySize)
{
	patch.PatchTask("MagicZombie::Binding_ExtendBase", [&]
		{
			*(size_t*)0x40928a = theZombieSize * theDataArraySize;
			if (theDataArraySize != 1024)
			{
				static size_t _theDataArraySize = theDataArraySize;
				patch.mHook.InsertCode((void*)0x4092b2, [](Hook::Regs* regs)
					{
						*(size_t*)(regs->ebp + 0x98) = _theDataArraySize;
					});
			}
			Board::gExtraZombieSize = theZombieSize - sizeof(Zombie);
			if (theZombieSize != sizeof(Zombie))
			{
				static const DWORD addresslist[] = {
					//图鉴
					0x00402A79,
					0x00403039,
					//Board::ProcessDeleteQueue
					0x0041D4F6,
					0x0041D508,
					0x0041D514,
					0x0041D51C,
					0x0041D592,
					0x0041D5A4,
					//DataArray<Zombie>::DataArrayTryToGet
					0x0041E194,
					0x0041E1A2,
					//Board::IterateZombies,
					0x0041E295,
					0x0041E2A1,
					0x0041E2B2,
					0x0041E2B9,
					//DataArray<Zombie>::DataArrayAlloc
					0x0041F72D,
					0x0041F734,
					0x0041F73F,
					0x0041F746,
					0x0041F75C,
					//DataArray<Zombie>::DataArrayTryToGet
					0x0041F7A1,
					0x0041F7AB,
					//DataArray<Zombie>::DataArrayFreeAll
					0x00420130,
					0x00420139,
					0x00420145,
					0x00420154,
					0x0042015C,
					0x004201BE,
					0x004201CA,
					//Plant::UpdateTanglekelp
					0x004639D4,
					0x00463A0A,
					0x00463A14,
					0x00463B48,
					0x00463B52,
					//Plant::FindSquashTarget
					0x004641C2,
					//Plant::UpdateSquash
					0x0046424A,
					//Plant::Fire
					0x0046ABEC,
					//Plant::Die
					0x0046B237,
					0x0046B23F,
					//Projectile::UpdateNormalMotion
					0x004713E6,
					0x004713F0,
					//FixBoardAfterLoad
					0x00485A84,
					0x00485A90,
					0x00485AA2,
					0x00485AAA,
					//SyncDataArray<Zombie>
					0x0048603E,
					//Zombie::ZombieInitialize
					0x00527509,
					0x00527516,
					//Zombie::BungeeDropZombie
					0x00528E7D,
					//Zombie::IsTanglekelpTarget
					0x0052A632,
					//Zombie::BobsledCrash
					0x0052C428,
					//Zombie::UpdateZombieBobsled
					0x0052C50C,
					//Zombie::SummonBackupDancer
					0x0052CCFB,
					0x0052CDCF,
					//Zombie::SummonBackupDancers
					0x0052CE21,
					0x0052CE29,
					//Zombie::NeedsMoreBackupDancers
					0x0052CEE8,
					0x0052CEF4,
					//Zombie::DrawBobsledReanim
					0x00530B8D,
					//Zombie::DrawBungeeReanim
					0x00530F99,
					0x00530FA7,
					//Zombie::IsMovingAtChilledSpeed
					0x005333D0,
					0x005333DA,
					0x00533414,
					0x0053341C,
					//Zombie::StartMindControlled
					0x00533F3B,
					0x00533F43,
					0x00533F4C,
					0x00533F8E,
					0x00533F96,
					//Zombie::BobsledDie
					0x005347B7,
					0x005347ED,
					//Zombie::BobsledBurn
					0x00534836,
					0x00534861,
					//Zombie::BungeeDie
					0x00534950,
					0x00534958,
					//Zombie::IsTanglekelpTarge
					0x00536956,
					//Zombie::GetBobsledPosition
					0x00538B33,
					0x00538B41,
					//Zombie::BossBungeeSpawn
					0x005396F0,
					//Zombie::BossBungeeLeave
					0x0053975A,
					0x00539764,
					//Zombie::BossAreBungeesDone
					0x005397D6,
					0x005397DE
				};
				for (DWORD addr : addresslist)
				{
					DWORD* addrwrite = (DWORD*)addr;
					*addrwrite += theZombieSize - sizeof(Zombie);
				}
			}
		}, true, true);
}

// 初始化 - MF_ZombieInitialize

static ZombieDefinition& _ZombieInitialize_InitMemberVariable_base(Zombie* _this, int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave)
{
	_this->mFromWave = theFromWave;
	_this->mRow = theRow;
	_this->mPosX = (float)(780 + Rand(40));
	_this->mPosY = _this->GetPosYBasedOnRow(theRow);
	_this->mVelX = 0.0f;
	_this->mVelZ = 0.0f;
	_this->mWidth = 120;
	_this->mHeight = 120;
	_this->mFrame = 0;
	_this->mPrevFrame = 0;
	_this->mZombieType = theType;
	_this->mVariant = theVariant;
	_this->mIsEating = false;
	_this->mJustGotShotCounter = 0;
	_this->mShieldJustGotShotCounter = 0;
	_this->mShieldRecoilCounter = 0;
	_this->mChilledCounter = 0;
	_this->mIceTrapCounter = 0;
	_this->mButteredCounter = 0;
	_this->mMindControlled = false;
	_this->mBlowingAway = false;
	_this->mHasHead = true;
	_this->mHasArm = true;
	_this->mHasObject = false;
	_this->mInPool = false;
	_this->mOnHighGround = false;
	_this->mHelmType = HELMTYPE_NONE;
	_this->mShieldType = SHIELDTYPE_NONE;
	_this->mYuckyFace = false;
	_this->mYuckyFaceCounter = 0;
	_this->mAnimCounter = 0;
	_this->mGroanCounter = RandRangeInt(300, 400);
	_this->mAnimTicksPerFrame = 12;
	_this->mAnimFrames = 12;
	_this->mZombieAge = 0;
	_this->mTargetCol = -1;
	_this->mZombiePhase = PHASE_ZOMBIE_NORMAL;
	_this->mZombieHeight = HEIGHT_ZOMBIE_NORMAL;
	_this->mPhaseCounter = 0;
	_this->mHitUmbrella = false;
	_this->mDroppedLoot = false;
	_this->mRelatedZombieID = ZOMBIEID_NULL;
	_this->mZombieRect = Rect(36, 0, 42, 115); 
	_this->mZombieAttackRect = Rect(50, 0, 20, 115);
	_this->mPlayingSong = false;
	_this->mZombieFade = -1;
	_this->mFlatTires = false;
	_this->mScaleZombie = 1.0f;
	_this->mUseLadderCol = -1;
	_this->mShieldHealth = 0;
	_this->mHelmHealth = 0;
	_this->mAltitude = 0.0f;
	_this->mFlyingHealth = 0;
	_this->mOrginalAnimRate = 0.0f;
	_this->mAttachmentID = ATTACHMENTID_NULL;
	_this->mSummonCounter = 0;
	_this->mBossStompCounter = -1;
	_this->mBossBungeeCounter = -1;
	_this->mBossHeadCounter = -1;
	_this->mBodyReanimID = REANIMATIONID_NULL;
	_this->mTargetPlantID = PLANTID_NULL;
	_this->mBossMode = 0;
	_this->mBossFireBallReanimID = ReanimationID::REANIMATIONID_NULL;
	_this->mSpecialHeadReanimID = ReanimationID::REANIMATIONID_NULL;
	_this->mTargetRow = -1;
	_this->mFireballRow = -1;
	_this->mIsFireBall = false;
	_this->mMoweredReanimID = ReanimationID::REANIMATIONID_NULL;
	_this->mLastPortalX = -1;

	for (int i = 0; i < 4; i++)
		_this->mFollowerZombieID[i] = ZombieID::ZOMBIEID_NULL;

	if (_this->mBoard && _this->mBoard->IsFlagWave(_this->mFromWave))
		_this->mPosX += 40.0f;

    _this->PickRandomSpeed();
	_this->mBodyHealth = 270;

	ZombieDefinition& aZombieDef = GetZombieDefinition(theType);
	return aZombieDef;
}

static auto _ZombieInitialize_InitMemberVariable = _ZombieInitialize_InitMemberVariable_base;

static void _ZombieInitialize_InitReanimation_base(Zombie* _this, ZombieDefinition& theZombieDef)
{
	_this->LoadReanim(theZombieDef.mReanimationType);
}

static auto _ZombieInitialize_InitReanimation = _ZombieInitialize_InitReanimation_base;

void _ZombieInitialize_InitType_base(Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer& theRenderLayer, int& theRenderOffset)
{
    switch (_this->mZombieType)
    {
    case ZOMBIE_NORMAL:
        _this->LoadPlainZombieReanim();
        break;

    case ZOMBIE_DUCKY_TUBE:
        _this->LoadPlainZombieReanim();
        break;

    case ZOMBIE_TRAFFIC_CONE:
        _this->LoadPlainZombieReanim();
        _this->ReanimShowPrefix("anim_cone", RENDER_GROUP_NORMAL);
        _this->ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);
        _this->mHelmType = HELMTYPE_TRAFFIC_CONE;
        _this->mHelmHealth = 370;
        break;

    case ZOMBIE_PAIL:
        _this->LoadPlainZombieReanim();
        _this->ReanimShowPrefix("anim_bucket", RENDER_GROUP_NORMAL);
        _this->ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);
        _this->mHelmType = HELMTYPE_PAIL;
        _this->mHelmHealth = 1100;
        break;

    case ZOMBIE_DOOR:
        _this->mShieldType = SHIELDTYPE_DOOR;
        _this->mShieldHealth = 1100;
        _this->LoadPlainZombieReanim();
        _this->AttachShield();
        break;

    case ZOMBIE_YETI:
        _this->mBodyHealth = 1350;
        _this->mPhaseCounter = RandRangeInt(1500, 2000);
        _this->mHasObject = true;
        _this->mZombieAttackRect = Rect(20, 0, 50, 115);
        break;

    case ZOMBIE_LADDER:
        _this->mBodyHealth = 500;
        _this->mShieldHealth = 500;
        _this->mShieldType = SHIELDTYPE_LADDER;
        _this->mZombieAttackRect = Rect(10, 0, 50, 115);
        if (_this->IsOnBoard())
        {
            _this->mZombiePhase = PHASE_LADDER_CARRYING;
            _this->StartWalkAnim(0);
        }
        _this->AttachShield();
        break;

    case ZOMBIE_BUNGEE:
    {
        _this->mBodyHealth = 450;
        _this->mAnimFrames = 4;
        _this->mAltitude = (float)(3000 + RandRangeInt(0, 150));
        _this->mVelX = 0.0f;

        if (_this->IsOnBoard())
        {
            _this->PickBungeeZombieTarget(-1);

            if (_this->mDead)
                return;

            _this->mZombiePhase = PHASE_BUNGEE_DIVING;
        }
        else
        {
            _this->mZombiePhase = PHASE_BUNGEE_CUTSCENE;
            _this->mPhaseCounter = RandRangeInt(0, 200);
        }

        _this->PlayZombieReanim("anim_drop", REANIM_LOOP, 0, 24.0f);
        Reanimation* aBodyReanim = _this->mApp->ReanimationGet(_this->mBodyReanimID);
        aBodyReanim->AssignRenderGroupToPrefix("Zombie_bungi_rightarm_lower2", 2);
        aBodyReanim->AssignRenderGroupToPrefix("Zombie_bungi_rightarm_hand2", 2);
        aBodyReanim->AssignRenderGroupToPrefix("Zombie_bungi_leftarm_lower2", 2);
        aBodyReanim->AssignRenderGroupToPrefix("Zombie_bungi_leftarm_hand2", 2);
        aBodyReanim->SetTruncateDisappearingFrames(nullptr, false);

        theRenderLayer = RENDER_LAYER_GRAVE_STONE;
        theRenderOffset = 7;
        _this->mZombieRect = Rect(-20, 22, 110, 94);
        _this->mZombieAttackRect = Rect(0, 0, 0, 0);
        _this->mVariant = false;
        break;
    }

    case ZOMBIE_FOOTBALL:
        _this->mZombieRect = Rect(50, 0, 57, 115);
        _this->ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);
        _this->mHelmType = HELMTYPE_FOOTBALL;
        _this->mHelmHealth = 1400;
        _this->mAnimTicksPerFrame = 6;
        _this->mVariant = false;
        break;

    case ZOMBIE_DIGGER:
    {
        _this->mHelmType = HELMTYPE_DIGGER;
        _this->mHelmHealth = 100;
        _this->mVariant = false;
        _this->mHasObject = true;
        _this->mZombieRect = Rect(50, 0, 28, 115);

        Reanimation* aBodyReanim = _this->mApp->ReanimationGet(_this->mBodyReanimID);
        aBodyReanim->SetTruncateDisappearingFrames(nullptr, false);

        if (!_this->IsOnBoard())
            _this->mZombiePhase = PHASE_DIGGER_CUTSCENE;
        else
        {
            _this->mZombiePhase = PHASE_DIGGER_TUNNELING;
            _this->AddAttachedParticle(60, 100, PARTICLE_DIGGER_TUNNEL);
            theRenderOffset = 7;
            _this->PlayZombieReanim("anim_dig", REANIM_LOOP_FULL_LAST_FRAME, 0, 12.0f);
            _this->PickRandomSpeed();
        }
        break;
    }

    case ZOMBIE_POLEVAULTER:
        _this->mBodyHealth = 500;
        _this->mAnimTicksPerFrame = 6;
        _this->mZombiePhase = PHASE_POLEVAULTER_PRE_VAULT;
        _this->mHasObject = true;
        _this->mVariant = false;
        _this->mPosX = (float)(800 + 70 + Rand(10));
        if (_this->IsOnBoard())
        {
            _this->PlayZombieReanim("anim_run", REANIM_LOOP, 0, 0.0f);
            _this->PickRandomSpeed();
        }
        _this->mZombieAttackRect = _this->mApp->IsWallnutBowlingLevel() ? Rect(-229, 0, 270, 115) : Rect(-29, 0, 70, 115);
        break;

    case ZOMBIE_DOLPHIN_RIDER:
        _this->mBodyHealth = 500;
        _this->mAnimTicksPerFrame = 6;
        _this->mZombiePhase = PHASE_DOLPHIN_WALKING;
        _this->mVariant = false;
        if (_this->IsOnBoard())
        {
            _this->PlayZombieReanim("anim_walkdolphin", REANIM_LOOP, 0, 0.0f);
            _this->PickRandomSpeed();
        }
        _this->SetupWaterTrack("zombie_dolphinrider_whitewater");
        _this->SetupWaterTrack("zombie_dolphinrider_dolphininwater");
        break;

    case ZOMBIE_GARGANTUAR:
    case ZOMBIE_REDEYE_GARGANTUAR:
    {
        _this->mWidth = 180;
        _this->mHeight = 180;
        _this->mBodyHealth = 3000;
        _this->mAnimFrames = 24;
        _this->mAnimTicksPerFrame = 8;
        _this->mPosX = (float)(800 + 45 + Rand(10));
        _this->mZombieRect = Rect(-17, -38, 125, 154);
        _this->mZombieAttackRect = Rect(-30, -38, 89, 154);
        _this->mVariant = false;
        theRenderOffset = 8;
        _this->mHasObject = true;

        int aPoleHit = Rand(100);
        int aPoleVariant;

        if (!_this->IsOnBoard() || _this->mBoard->mLevel == 48)
            aPoleVariant = 0;
        else
            aPoleVariant = aPoleHit < 10 ? 2 : aPoleHit < 35 ? 1 : 0;

        Reanimation* aBodyReanim = _this->mApp->ReanimationGet(_this->mBodyReanimID);

        if (aPoleVariant == 2)
            aBodyReanim->SetImageOverride("Zombie_gargantuar_telephonepole", IMAGE_REANIM_ZOMBIE_GARGANTUAR_ZOMBIE);
        else if (aPoleVariant == 1)
            aBodyReanim->SetImageOverride("Zombie_gargantuar_telephonepole", IMAGE_REANIM_ZOMBIE_GARGANTUAR_DUCKXING);

        if (_this->mZombieType == ZOMBIE_REDEYE_GARGANTUAR)
        {
            aBodyReanim->SetImageOverride("anim_head1", IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE);
            _this->mBodyHealth = 6000;
        }

        break;
    }

    case ZOMBIE_ZAMBONI:
        _this->mBodyHealth = 1350;
        _this->mAnimFrames = 2;
        _this->mAnimTicksPerFrame = 8;
        _this->mPosX = (float)(800 + Rand(10));
        theRenderOffset = 8;
        _this->PlayZombieReanim("anim_drive", REANIM_LOOP, 0, 12.0f);
        _this->mZombieRect = Rect(0, -13, 153, 140);
        _this->mZombieAttackRect = Rect(10, -13, 133, 140);
        _this->mVariant = false;
        break;

    case ZOMBIE_CATAPULT:
        _this->mBodyHealth = 850;
        _this->mPosX = (float)(800 + 25 + Rand(10));
        _this->mSummonCounter = 20;

        if (_this->IsOnBoard())
            _this->PlayZombieReanim("anim_walk", REANIM_LOOP, 0, 5.5f);
        else
            _this->PlayZombieReanim("anim_idle", REANIM_LOOP, 0, 8.0f);

        _this->mZombieRect = Rect(0, -13, 153, 140);
        _this->mZombieAttackRect = Rect(10, -13, 133, 140);
        _this->mVariant = false;
        break;

    case ZOMBIE_SNORKEL:
        _this->mZombieRect = Rect(12, 0, 62, 115);
        _this->mZombieAttackRect = Rect(-5, 0, 55, 115);
        _this->SetupWaterTrack("Zombie_snorkle_whitewater");
        _this->SetupWaterTrack("Zombie_snorkle_whitewater2");
        _this->mVariant = false;
        _this->mZombiePhase = PHASE_SNORKEL_WALKING;
        break;

    case ZOMBIE_JACK_IN_THE_BOX:
    {
        _this->mBodyHealth = 500;
        _this->mAnimTicksPerFrame = 6;

        int aDistance = 450 + Rand(300);

        if (Rand(20) == 0)  // 早爆的概率
            aDistance /= 3;

        _this->mPhaseCounter = (int)(aDistance / _this->mVelX) * 2;
        _this->mZombieAttackRect = Rect(20, 0, 50, 115);

        if (_this->mApp->IsScaryPotterLevel())
            _this->mPhaseCounter = 10;

        if (_this->IsOnBoard())
            _this->mZombiePhase = PHASE_JACK_IN_THE_BOX_RUNNING;

        break;
    }

    case ZOMBIE_BOBSLED:
    {
        theRenderOffset = 3;

        if (theParentZombie)
        {
            int aPosition = 0;
            while (aPosition < 3 && theParentZombie->mFollowerZombieID[aPosition] != ZombieID::ZOMBIEID_NULL)
                aPosition++;
            assert(aPosition < 3);
            theParentZombie->mFollowerZombieID[aPosition] = _this->mBoard->ZombieGetID(_this);
            _this->mRelatedZombieID = _this->mBoard->ZombieGetID(theParentZombie);

            _this->mPosX = theParentZombie->mPosX + (aPosition + 1) * 50;
            if (aPosition == 0)
            {
                theRenderOffset = 1;
                _this->mAltitude = 9.0f;
            }
            else if (aPosition == 1)
            {
                theRenderOffset = 2;
                _this->mAltitude = -7.0f;
            }
            else
            {
                theRenderOffset = 0;
                _this->mAltitude = 9.0f;
            }
        }
        else
        {
            _this->mPosX = 800 + 80;
            _this->mZombieRect = Rect(-50, 0, 275, 115);
            _this->mHelmType = HELMTYPE_BOBSLED;
            _this->mHelmHealth = 300;
            _this->mAltitude = -10.0f;
        }

        _this->mVelX = 0.6f;
        _this->mZombiePhase = PHASE_BOBSLED_SLIDING;
        _this->mPhaseCounter = 500;
        _this->mVariant = false;

        if (_this->mFromWave == ZOMBIE_WAVE_CUTSCENE)
        {
            _this->PlayZombieReanim("anim_jump", REANIM_PLAY_ONCE_AND_HOLD, 0, 20.0f);
            _this->mApp->ReanimationGet(_this->mBodyReanimID)->mAnimTime = 1.0f;
            _this->mAltitude = 18.0f;
        }
        else if (_this->IsOnBoard())
        {
            _this->PlayZombieReanim("anim_push", REANIM_LOOP, 0, 30.0f);
        }

        break;
    }

    case ZOMBIE_FLAG:
    {
        _this->mHasObject = true;
        _this->LoadPlainZombieReanim();

        Reanimation* aBodyReanim = _this->mApp->ReanimationGet(_this->mBodyReanimID);
        Reanimation* aFlagReanim = _this->mApp->AddReanimation(0.0f, 0.0f, 0, REANIM_FLAG);
        aFlagReanim->PlayReanim("Zombie_flag", REANIM_LOOP, 0, 15.0f);
        _this->mSpecialHeadReanimID = _this->mApp->ReanimationGetID(aFlagReanim);
        ReanimatorTrackInstance* aTrackInstance = aBodyReanim->GetTrackInstanceByName("Zombie_flaghand");
        AttachReanim(&aTrackInstance->mAttachmentID, aFlagReanim, 0.0f, 0.0f);
        aBodyReanim->mFrameBasePose = 0;

        _this->mPosX = 800;
        break;
    }

    case ZOMBIE_POGO:
        _this->mVariant = false;
        _this->mZombiePhase = PHASE_POGO_BOUNCING;
        _this->mPhaseCounter = Rand(80) + 1;
        _this->mHasObject = true;
        _this->mBodyHealth = 500;
        _this->mZombieAttackRect = Rect(10, 0, 30, 115);
        _this->PlayZombieReanim("anim_pogo", REANIM_PLAY_ONCE_AND_HOLD, 0, 40.0f);
        _this->mApp->ReanimationGet(_this->mBodyReanimID)->mAnimTime = 1.0f;
        break;

    case ZOMBIE_NEWSPAPER:
        _this->mZombieAttackRect = Rect(20, 0, 50, 115);
        _this->mZombiePhase = PHASE_NEWSPAPER_READING;
        _this->mShieldType = SHIELDTYPE_NEWSPAPER;
        _this->mShieldHealth = 150;
        _this->mVariant = false;
        _this->AttachShield();
        break;

    case ZOMBIE_BALLOON:
    {
        Reanimation* aBodyReanim = _this->mApp->ReanimationGet(_this->mBodyReanimID);
        aBodyReanim->SetTruncateDisappearingFrames(nullptr, false);

        if (_this->IsOnBoard())
        {
            _this->mAltitude = 25.0f;
            _this->mZombiePhase = PHASE_BALLOON_FLYING;
            _this->PlayZombieReanim("anim_idle", REANIM_LOOP, 0, aBodyReanim->mAnimRate);
        }
        else
            _this->SetAnimRate(RandRangeFloat(8.0f, 10.0f));

        Reanimation* aPropellerReanim = _this->mApp->AddReanimation(0.0f, 0.0f, 0, theZombieDef.mReanimationType);
        aPropellerReanim->SetFramesForLayer("Propeller");
        aPropellerReanim->mLoopType = REANIM_LOOP_FULL_LAST_FRAME;
        aPropellerReanim->AttachToAnotherReanimation(aBodyReanim, "hat");

        _this->mFlyingHealth = 20;
        _this->mZombieRect = Rect(36, 30, 42, 115);
        _this->mZombieAttackRect = Rect(20, 30, 50, 115);
        _this->mVariant = false;
        break;
    }

    case ZOMBIE_DANCER:
        if (!_this->IsOnBoard())
            _this->PlayZombieReanim("anim_moonwalk", REANIM_LOOP, 0, 12.0f);
        else
        {
            _this->mZombiePhase = PHASE_DANCER_DANCING_IN;
            _this->mVelX = 0.5f;
            _this->mPhaseCounter = 300 + Rand(12);
            _this->PlayZombieReanim("anim_moonwalk", REANIM_LOOP, 0, 24.0f);
        }
        _this->mBodyHealth = 500;
        _this->mVariant = false;
        break;

    case ZOMBIE_BACKUP_DANCER:
        if (!_this->IsOnBoard())
            _this->PlayZombieReanim("anim_armraise", REANIM_LOOP, 0, 12.0f);
        _this->mZombiePhase = PHASE_DANCER_DANCING_LEFT;
        _this->mVariant = false;
        break;

    case ZOMBIE_IMP:
        if (!_this->IsOnBoard())
            _this->PlayZombieReanim("anim_walk", REANIM_LOOP, 0, 12.0f);
        if (_this->mApp->IsIZombieLevel())
            _this->mBodyHealth = 70;
        break;

    case ZOMBIE_BOSS:
        _this->mPosX = 0.0f;
        _this->mPosY = 0.0f;
        _this->mZombieRect = Rect(700, 80, 90, 430);
        _this->mZombieAttackRect = Rect(0, 0, 0, 0);
        theRenderLayer = RENDER_LAYER_TOP;
        _this->mBodyHealth = _this->mApp->IsAdventureMode() ? 40000 : 60000;
        if (_this->IsOnBoard())
        {
            _this->PlayZombieReanim("anim_enter", REANIM_PLAY_ONCE_AND_HOLD, 0, 12.0f);
            _this->mSummonCounter = 500;
            _this->mBossHeadCounter = 5000;
            _this->mZombiePhase = PHASE_BOSS_ENTER;
        }
        else
            _this->PlayZombieReanim("anim_head_idle", REANIM_LOOP, 0, 12.0f);

        _this->BossSetupReanim();
        break;

    case ZOMBIE_PEA_HEAD:
    {
        _this->LoadPlainZombieReanim();
        _this->ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);
        _this->ReanimShowPrefix("anim_head2", RENDER_GROUP_HIDDEN);

        Reanimation* aBodyReanim = _this->mApp->ReanimationGet(_this->mBodyReanimID);

        if (_this->IsOnBoard())
            aBodyReanim->SetFramesForLayer("anim_walk2");

        ReanimatorTrackInstance* aTrackInstance = aBodyReanim->GetTrackInstanceByName("anim_head1");
        aTrackInstance->mImageOverride = IMAGE_BLANK;
        Reanimation* aHeadReanim = _this->mApp->AddReanimation(0.0f, 0.0f, 0, REANIM_PEASHOOTER);
        aHeadReanim->PlayReanim("anim_head_idle", REANIM_LOOP, 0, 15.0f);
        _this->mSpecialHeadReanimID = _this->mApp->ReanimationGetID(aHeadReanim);
        AttachEffect* aAttachEffect = AttachReanim(&aTrackInstance->mAttachmentID, aHeadReanim, 0.0f, 0.0f);
        aBodyReanim->mFrameBasePose = 0;
        TodScaleRotateTransformMatrix(&aAttachEffect->mOffset, 65.0f, -5.0f, 0.2f, -1.0f, 1.0f);

        _this->mPhaseCounter = 150;
        _this->mVariant = false;
        break;
    }

    case ZOMBIE_WALLNUT_HEAD:
    {
        _this->LoadPlainZombieReanim();
        _this->ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);
        _this->ReanimShowPrefix("anim_head", RENDER_GROUP_HIDDEN);
        _this->ReanimShowPrefix("Zombie_tie", RENDER_GROUP_HIDDEN);

        Reanimation* aBodyReanim = _this->mApp->ReanimationGet(_this->mBodyReanimID);
        ReanimatorTrackInstance* aTrackInstance = aBodyReanim->GetTrackInstanceByName("Zombie_body");
        Reanimation* aHeadReanim = _this->mApp->AddReanimation(0.0f, 0.0f, 0, REANIM_WALLNUT);
        aHeadReanim->PlayReanim("anim_idle", REANIM_LOOP, 0, 15.0f);
        _this->mSpecialHeadReanimID = _this->mApp->ReanimationGetID(aHeadReanim);
        AttachEffect* aAttachEffect = AttachReanim(&aTrackInstance->mAttachmentID, aHeadReanim, 0.0f, 0.0f);
        aBodyReanim->mFrameBasePose = 0;
        TodScaleRotateTransformMatrix(&aAttachEffect->mOffset, 50.0f, 0.0f, 0.2f, -0.8f, 0.8f);

        _this->mHelmType = HELMTYPE_WALLNUT;
        _this->mHelmHealth = 1100;
        _this->mVariant = false;
        break;
    }

    case ZOMBIE_TALLNUT_HEAD:
    {
        _this->LoadPlainZombieReanim();
        _this->ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);
        _this->ReanimShowPrefix("anim_head", RENDER_GROUP_HIDDEN);
        _this->ReanimShowPrefix("Zombie_tie", RENDER_GROUP_HIDDEN);

        Reanimation* aBodyReanim = _this->mApp->ReanimationGet(_this->mBodyReanimID);
        ReanimatorTrackInstance* aTrackInstance = aBodyReanim->GetTrackInstanceByName("Zombie_body");
        Reanimation* aHeadReanim = _this->mApp->AddReanimation(0.0f, 0.0f, 0, REANIM_TALLNUT);
        aHeadReanim->PlayReanim("anim_idle", REANIM_LOOP, 0, 15.0f);
        _this->mSpecialHeadReanimID = _this->mApp->ReanimationGetID(aHeadReanim);
        AttachEffect* aAttachEffect = AttachReanim(&aTrackInstance->mAttachmentID, aHeadReanim, 0.0f, 0.0f);
        aBodyReanim->mFrameBasePose = 0;
        TodScaleRotateTransformMatrix(&aAttachEffect->mOffset, 37.0f, 0.0f, 0.2f, -0.8f, 0.8f);

        _this->mHelmType = HELMTYPE_TALLNUT;
        _this->mHelmHealth = 2200;
        _this->mVariant = false;
        _this->mPosX += 30.0f;
        break;
    }

    case ZOMBIE_JALAPENO_HEAD:
    {
        _this->LoadPlainZombieReanim();
        _this->ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);
        _this->ReanimShowPrefix("anim_head", RENDER_GROUP_HIDDEN);
        _this->ReanimShowPrefix("Zombie_tie", RENDER_GROUP_HIDDEN);

        Reanimation* aBodyReanim = _this->mApp->ReanimationGet(_this->mBodyReanimID);
        ReanimatorTrackInstance* aTrackInstance = aBodyReanim->GetTrackInstanceByName("Zombie_body");
        Reanimation* aHeadReanim = _this->mApp->AddReanimation(0.0f, 0.0f, 0, REANIM_JALAPENO);
        aHeadReanim->PlayReanim("anim_idle", REANIM_LOOP, 0, 15.0f);
        _this->mSpecialHeadReanimID = _this->mApp->ReanimationGetID(aHeadReanim);
        AttachEffect* aAttachEffect = AttachReanim(&aTrackInstance->mAttachmentID, aHeadReanim, 0.0f, 0.0f);
        aBodyReanim->mFrameBasePose = 0;
        TodScaleRotateTransformMatrix(&aAttachEffect->mOffset, 55.0f, -5.0f, 0.2f, -1.0f, 1.0f);

        _this->mVariant = false;
        _this->mBodyHealth = 500;
        int aDistance = 275 + Rand(175);
        _this->mPhaseCounter = (int)(aDistance / _this->mVelX) * 2;
        break;
    }

    case ZOMBIE_GATLING_HEAD:
    {
        _this->LoadPlainZombieReanim();
        _this->ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);
        _this->ReanimShowPrefix("anim_head2", RENDER_GROUP_HIDDEN);

        Reanimation* aBodyReanim = _this->mApp->ReanimationGet(_this->mBodyReanimID);

        if (_this->IsOnBoard())
            aBodyReanim->SetFramesForLayer("anim_walk2");

        ReanimatorTrackInstance* aTrackInstance = aBodyReanim->GetTrackInstanceByName("anim_head1");
        aTrackInstance->mImageOverride = IMAGE_BLANK;
        Reanimation* aHeadReanim = _this->mApp->AddReanimation(0.0f, 0.0f, 0, REANIM_GATLINGPEA);
        aHeadReanim->PlayReanim("anim_head_idle", REANIM_LOOP, 0, 15.0f);
        _this->mSpecialHeadReanimID = _this->mApp->ReanimationGetID(aHeadReanim);
        AttachEffect* aAttachEffect = AttachReanim(&aTrackInstance->mAttachmentID, aHeadReanim, 0.0f, 0.0f);
        aBodyReanim->mFrameBasePose = 0;
        TodScaleRotateTransformMatrix(&aAttachEffect->mOffset, 65.0f, -5.0f, 0.2f, -1.0f, 1.0f);

        _this->mPhaseCounter = 150;
        _this->mVariant = false;
        break;
    }

    case ZOMBIE_SQUASH_HEAD:
    {
        _this->LoadPlainZombieReanim();
        _this->ReanimShowPrefix("anim_hair", RENDER_GROUP_HIDDEN);
        _this->ReanimShowPrefix("anim_head2", RENDER_GROUP_HIDDEN);

        Reanimation* aBodyReanim = _this->mApp->ReanimationGet(_this->mBodyReanimID);

        if (_this->IsOnBoard())
            aBodyReanim->SetFramesForLayer("anim_walk2");

        ReanimatorTrackInstance* aTrackInstance = aBodyReanim->GetTrackInstanceByName("anim_head1");
        aTrackInstance->mImageOverride = IMAGE_BLANK;
        Reanimation* aHeadReanim = _this->mApp->AddReanimation(0.0f, 0.0f, 0, ReanimationType::REANIM_SQUASH);
        aHeadReanim->PlayReanim("anim_idle", REANIM_LOOP, 0, 15.0f);
        _this->mSpecialHeadReanimID = _this->mApp->ReanimationGetID(aHeadReanim);
        AttachEffect* aAttachEffect = AttachReanim(&aTrackInstance->mAttachmentID, aHeadReanim, 0.0f, 0.0f);
        aBodyReanim->mFrameBasePose = 0;
        TodScaleRotateTransformMatrix(&aAttachEffect->mOffset, 55.0f, -15.0f, 0.2f, -0.75f, 0.75f);

        _this->mZombiePhase = PHASE_SQUASH_PRE_LAUNCH;
        _this->mVariant = false;
        break;
    }
    }
}

static auto _ZombieInitialize_InitType = _ZombieInitialize_InitType_base;

void _ZombieInitialize_AfterInitType_base(Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer theRenderLayer, int theRenderOffset)
{
    if (_this->IsOnBoard() && _this->mApp->mGameMode == GAMEMODE_CHALLENGE_ZOMBIQUARIUM)
    {
        float aAnimRate = RandRangeFloat(8.0f, 10.0f);
        _this->PlayZombieReanim("anim_aquarium_swim", REANIM_LOOP, 0, aAnimRate);

        _this->mZombieHeight = HEIGHT_ZOMBIQUARIUM;
        _this->mZombiePhase = PHASE_ZOMBIQUARIUM_DRIFT;
        _this->mPhaseCounter = 200;
        _this->mBodyHealth = 200;
        _this->mSummonCounter = RandRangeInt(200, 400);
    }

    if (_this->mApp->IsLittleTroubleLevel() && (_this->IsOnBoard() || _this->mFromWave == ZOMBIE_WAVE_CUTSCENE))
    {
        _this->mScaleZombie = 0.5f;
        _this->mBodyHealth /= 4;
        _this->mHelmHealth /= 4;
        _this->mShieldHealth /= 4;
        _this->mFlyingHealth /= 4;
    }

    _this->UpdateAnimSpeed();

    if (_this->mVariant)
        _this->ReanimShowPrefix("anim_tongue", RENDER_GROUP_NORMAL);

    _this->mBodyMaxHealth = _this->mBodyHealth;
    _this->mHelmMaxHealth = _this->mHelmHealth;
    _this->mShieldMaxHealth = _this->mShieldHealth;
    _this->mFlyingMaxHealth = _this->mFlyingHealth;
    _this->mDead = false;
    _this->mX = (int)_this->mPosX;
    _this->mY = (int)_this->mPosY;
    _this->mRenderOrder = Board::MakeRenderOrder(theRenderLayer, _this->mRow, theRenderOffset);

    if (_this->mZombieHeight == HEIGHT_ZOMBIQUARIUM)
        _this->mBodyMaxHealth = 300;

    if (_this->IsOnBoard())
    {
        _this->PlayZombieAppearSound();
        _this->StartZombieSound();
    }

    _this->UpdateReanim();
}

static auto _ZombieInitialize_AfterInitType = _ZombieInitialize_AfterInitType_base;

static void _PatchMF_ZombieInitialize(InitPatch& patch)
{
	patch.PatchTask("_PatchMF_ZombieInitialize", [&]
		{
			patch.mHook.InsertCodeAndJump((void*)0x5269F0, (void*)0x5284AB, [](Hook::Regs* regs)
				{ 
					Zombie* _this = *(Zombie**)(regs->esp + 0x4);
					int aRow = (int)regs->eax;
					ZombieType aZombieType = *(ZombieType*)(regs->esp + 0x8);
					bool aVariant = *(bool*)(regs->esp + 0xc);
					Zombie* aParentZombie = *(Zombie**)(regs->esp + 0x10);
					int aFromWave = *(int*)(regs->esp + 0x14);

					ZombieDefinition& aZombieDef = _ZombieInitialize_InitMemberVariable(_this, aRow, aZombieType, aVariant, aParentZombie, aFromWave);

					if (aZombieDef.mReanimationType != REANIM_NONE)
						_ZombieInitialize_InitReanimation(_this, aZombieDef);

                    RenderLayer aRenderLayer = RENDER_LAYER_ZOMBIE;
                    int aRenderOffset = 4;

                    _ZombieInitialize_InitType(_this, aZombieDef, aParentZombie, aRenderLayer, aRenderOffset);
                    _ZombieInitialize_AfterInitType(_this, aZombieDef, aParentZombie, aRenderLayer, aRenderOffset);
				});
		});
}

void MagicZombie::Binding_MF_ZombieInitialize_InitMemberVariable(InitPatch& patch, const std::function<ZombieDefinition& (Zombie* _this, int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave, ZombieInitialize_InitMemberVariable_t& base)>& func)
{
	patch.PatchTask("MagicZombie::Binding_MF_ZombieInitialize_InitMemberVariable", [&]
		{
			static std::vector<std::function<ZombieDefinition& (Zombie* _this, int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave, ZombieInitialize_InitMemberVariable_t& base)>> func_list;
			patch.PatchTask("MagicZombie::Binding_MF_ZombieInitialize_InitMemberVariable(Hook)", [&]
				{
					_PatchMF_ZombieInitialize(patch);
					_ZombieInitialize_InitMemberVariable = [](Zombie* _this, int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave) -> ZombieDefinition&
					{
						ZombieInitialize_InitMemberVariable_t base;

						base.mFunction = [&](Zombie* __this, int _theRow, ZombieType _theType, bool _theVariant, Zombie* _theParentZombie, int _theFromWave) -> ZombieDefinition&
						{
							std::swap(_this, __this);
							std::swap(theRow, _theRow);
							std::swap(theType, _theType);
							std::swap(theVariant, _theVariant);
							std::swap(theParentZombie, _theParentZombie);
							std::swap(theFromWave, _theFromWave);
							auto& result = base();
							_this = __this;
							theRow = _theRow;
							theType = _theType;
							theVariant = _theVariant;
							theParentZombie = _theParentZombie;
							theFromWave = _theFromWave;
							return result;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable -> ZombieDefinition&
						{
							if (i == 0)
								return _ZombieInitialize_InitMemberVariable_base(_this, theRow, theType, theVariant, theParentZombie, theFromWave);
							else
							{
								i--;
								auto& result = func_list[i](_this, theRow, theType, theVariant, theParentZombie, theFromWave, base);
								i++;
								return result;
							}
						};

						return func_list.back()(_this, theRow, theType, theVariant, theParentZombie, theFromWave, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicZombie::Binding_MF_ZombieInitialize_InitReanimation(InitPatch& patch, const std::function<void(Zombie* _this, ZombieDefinition& theZombieDef, ZombieInitialize_InitReanimation_t& base)>& func)
{
    patch.PatchTask("MagicZombie::Binding_MF_ZombieInitialize_InitReanimation", [&]
        {
            static std::vector<std::function<void(Zombie* _this, ZombieDefinition& theZombieDef, ZombieInitialize_InitReanimation_t& base)>> func_list;
            patch.PatchTask("MagicZombie::Binding_MF_ZombieInitialize_InitReanimation(Hook)", [&]
                {
                    _PatchMF_ZombieInitialize(patch);
                    _ZombieInitialize_InitReanimation = [](Zombie* _this, ZombieDefinition& theZombieDef)
                    {
                        ZombieInitialize_InitReanimation_t base;
                        auto p_theZombieDef = &theZombieDef;

                        base.mFunction = [&](Zombie* __this, ZombieDefinition& _theZombieDef)
                        {
                            auto _p_theZombieDef = &_theZombieDef;
                            std::swap(_this, __this);
                            std::swap(p_theZombieDef, _p_theZombieDef);
                            base();
                            _this = __this;
                            p_theZombieDef = _p_theZombieDef;
                        };
                        base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
                        {
                            if (i == 0)
                                return _ZombieInitialize_InitReanimation_base(_this, *p_theZombieDef);
                            else
                            {
                                i--;
                                func_list[i](_this, *p_theZombieDef, base);
                                i++;
                            }
                        };

                        func_list.back()(_this, theZombieDef, base);
                    };
                });
            func_list.push_back(func);
        }, false);
}

void MagicZombie::Binding_MF_ZombieInitialize_InitType(InitPatch& patch, const std::function<void(Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer& theRenderLayer, int& theRenderOffset, ZombieInitialize_InitType_t& base)>& func)
{
    patch.PatchTask("MagicZombie::Binding_MF_ZombieInitialize_InitType", [&]
        {
            static std::vector<std::function<void(Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer& theRenderLayer, int& theRenderOffset, ZombieInitialize_InitType_t& base)>> func_list;
            patch.PatchTask("MagicZombie::Binding_MF_ZombieInitialize_InitType(Hook)", [&]
                {
                    _PatchMF_ZombieInitialize(patch);
                    _ZombieInitialize_InitType = [](Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer& theRenderLayer, int& theRenderOffset)
                    {
                        ZombieInitialize_InitType_t base;

                        auto p_theZombieDef = &theZombieDef;
                        auto p_theRenderLayer = &theRenderLayer;
                        auto p_theRenderOffset = &theRenderOffset;

                        base.mFunction = [&](Zombie* __this, ZombieDefinition& _theZombieDef, Zombie* _theParentZombie, RenderLayer& _theRenderLayer, int& _theRenderOffset)
                        {
                            auto _p_theZombieDef = &_theZombieDef;
                            auto _p_theRenderLayer = &_theRenderLayer;
                            auto _p_theRenderOffset = &_theRenderOffset;

                            std::swap(_this, __this);
                            std::swap(p_theZombieDef, _p_theZombieDef);
                            std::swap(theParentZombie, _theParentZombie);
                            std::swap(p_theRenderLayer, _p_theRenderLayer);
                            std::swap(p_theRenderOffset, _p_theRenderOffset);
                            base();
                            _this = __this;
                            p_theZombieDef = _p_theZombieDef;
                            theParentZombie = _theParentZombie;
                            p_theRenderLayer = p_theRenderLayer;
                            p_theRenderOffset = _p_theRenderOffset;
                        };
                        base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
                        {
                            if (i == 0)
                                _ZombieInitialize_InitType_base(_this, *p_theZombieDef, theParentZombie, *p_theRenderLayer, *p_theRenderOffset);
                            else
                            {
                                i--;
                                func_list[i](_this, *p_theZombieDef, theParentZombie, *p_theRenderLayer, *p_theRenderOffset, base);
                                i++;
                            }
                        };

                        func_list.back()(_this, theZombieDef, theParentZombie, theRenderLayer, theRenderOffset, base);
                    };
                });
            func_list.push_back(func);
        }, false);
}

void MagicZombie::Binding_MF_ZombieInitialize_AfterInitType(InitPatch& patch, const std::function<void(Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer theRenderLayer, int theRenderOffset, ZombieInitialize_AfterInitType_t& base)>& func)
{
    patch.PatchTask("MagicZombie::Binding_MF_ZombieInitialize_AfterInitType", [&]
        {
            static std::vector<std::function<void(Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer theRenderLayer, int theRenderOffset, ZombieInitialize_AfterInitType_t& base)>> func_list;
            patch.PatchTask("MagicZombie::Binding_MF_ZombieInitialize_AfterInitType(Hook)", [&]
                {
                    _PatchMF_ZombieInitialize(patch);
                    _ZombieInitialize_AfterInitType = [](Zombie* _this, ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer theRenderLayer, int theRenderOffset)
                    {
                        ZombieInitialize_AfterInitType_t base;
                        auto p_theZombieDef = &theZombieDef;

                        base.mFunction = [&](Zombie* __this, ZombieDefinition& _theZombieDef, Zombie* _theParentZombie, RenderLayer _theRenderLayer, int _theRenderOffset)
                        {
                            auto _p_theZombieDef = &_theZombieDef;
                            std::swap(_this, __this);
                            std::swap(p_theZombieDef, _p_theZombieDef);
                            std::swap(theParentZombie, _theParentZombie);
                            std::swap(theRenderLayer, _theRenderLayer);
                            std::swap(theRenderOffset, _theRenderOffset);
                            base();
                            _this = __this;
                            p_theZombieDef = _p_theZombieDef;
                            theParentZombie = _theParentZombie;
                            theRenderLayer = _theRenderLayer;
                            theRenderOffset = _theRenderOffset;
                        };
                        base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
                        {
                            if (i == 0)
                                _ZombieInitialize_AfterInitType_base(_this, *p_theZombieDef, theParentZombie, theRenderLayer, theRenderOffset);
                            else
                            {
                                i--;
                                func_list[i](_this, *p_theZombieDef, theParentZombie, theRenderLayer, theRenderOffset, base);
                                i++;
                            }
                        };

                        func_list.back()(_this, theZombieDef, theParentZombie, theRenderLayer, theRenderOffset, base);
                    };
                });
            func_list.push_back(func);
        }, false);
}
