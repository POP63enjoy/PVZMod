#include "CutScene.h"
#include "LawnApp.h"
#include "Reanimator.h"
#include "ChallengeScreen.h"

using namespace PVZMod;

CutScene::CutScene()
{
	mApp = gLawnApp;
	mBoard = mApp->mBoard;
	mCutsceneTime = 0;
	mSodTime = 0;
	mFogTime = 0;
	mBossTime = 0;
	mCrazyDaveTime = 0;
	mGraveStoneTime = 0;
	mReadySetPlantTime = 0;
	mLawnMowerTime = 0;
	mCrazyDaveDialogStart = -1;
	mSeedChoosing = false;
	mZombiesWonReanimID = REANIMATIONID_NULL;
	mPreloaded = false;
	mPlacedZombies = false;
	mPlacedLawnItems = false;
	mCrazyDaveCountDown = 0;
	mCrazyDaveLastTalkIndex = -1;
	mUpsellHideBoard = false;
	mUpsellChallengeScreen = nullptr;
	mPreUpdatingBoard = false;
}

CutScene::~CutScene()
{
	if (mUpsellChallengeScreen)
	{
		delete mUpsellChallengeScreen;
	}
	mApp->mMuteSoundsForCutscene = false;
}
