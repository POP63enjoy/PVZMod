#include "GameSelector.h"
#include <Windows.h>
#include "GameButton.h"
#include "Res.h"
#include "Image.h"
#include "Music.h"
#include "LawnCommon.h"
#include "Music.h"
#include "Reanimator.h"
#include "LawnApp.h"
#include "TodCommon.h"
#include "ToolTipWidget.h"
#include "TodParticle.h"

using namespace PVZMod;

void GameSelectorOverlay::Draw(Graphics* g)
{
	mParent->DrawOverlay(g);
}

GameSelectorOverlay::GameSelectorOverlay(GameSelector* theGameSelector)
{
	mParent = theGameSelector;
	mMouseVisible = false;
	mHasAlpha = true;
}

GameSelector::GameSelector(LawnApp* theApp)
{
	mApp = theApp;
	mLevel = 1;
	mLoading = false;
	mHasTrophy = false;
	mToolTip = new ToolTipWidget();

	mAdventureButton = MakeNewButton(
		Btn_Adventure,
		this,
		_S(""),
		nullptr,
		IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_BUTTON,
		IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_HIGHLIGHT,
		IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_HIGHLIGHT
	);
	mAdventureButton->Resize(0, 0, IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_BUTTON->mWidth, 125);
	mAdventureButton->mClip = false;
	mAdventureButton->mBtnNoDraw = true;
	mAdventureButton->mMouseVisible = false;
	mAdventureButton->mPolygonShape[0] = SexyVector2(7.0f, 1.0f);
	mAdventureButton->mPolygonShape[1] = SexyVector2(328.0f, 30.0f);
	mAdventureButton->mPolygonShape[2] = SexyVector2(314.0f, 125.0f);
	mAdventureButton->mPolygonShape[3] = SexyVector2(1.0f, 78.0f);
	mAdventureButton->mUsePolygonShape = true;

	mMinigameButton = MakeNewButton(
		Btn_Minigame,
		this,
		_S(""),
		nullptr,
		IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_BUTTON,
		IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_HIGHLIGHT,
		IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_HIGHLIGHT
	);
	mMinigameButton->Resize(0, 0, IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_BUTTON->mWidth, 130);
	mMinigameButton->mClip = false;
	mMinigameButton->mBtnNoDraw = true;
	mMinigameButton->mMouseVisible = false;
	mMinigameButton->mPolygonShape[0] = SexyVector2(4.0f, 2.0f);
	mMinigameButton->mPolygonShape[1] = SexyVector2(312.0f, 51.0f);
	mMinigameButton->mPolygonShape[2] = SexyVector2(296.0f, 130.0f);
	mMinigameButton->mPolygonShape[3] = SexyVector2(7.0f, 77.0f);
	mMinigameButton->mUsePolygonShape = true;

	mPuzzleButton = MakeNewButton(
		Btn_Puzzle,
		this,
		_S(""),
		nullptr,
		IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_BUTTON,
		IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_HIGHLIGHT,
		IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_HIGHLIGHT
	);
	mPuzzleButton->Resize(0, 0, IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_BUTTON->mWidth, 121);
	mPuzzleButton->mClip = false;
	mPuzzleButton->mBtnNoDraw = true;
	mPuzzleButton->mMouseVisible = false;
	mPuzzleButton->mPolygonShape[0] = SexyVector2(2.0f, 0.0f);
	mPuzzleButton->mPolygonShape[1] = SexyVector2(281.0f, 55.0f);
	mPuzzleButton->mPolygonShape[2] = SexyVector2(268.0f, 121.0f);
	mPuzzleButton->mPolygonShape[3] = SexyVector2(3.0f, 60.0f);
	mPuzzleButton->mUsePolygonShape = true;

	mSurvivalButton = MakeNewButton(
		Btn_Survival,
		this,
		_S(""),
		nullptr,
		IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_BUTTON,
		IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_HIGHLIGHT,
		IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_HIGHLIGHT
	);
	mSurvivalButton->Resize(0, 0, IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_BUTTON->mWidth, 124);
	mSurvivalButton->mClip = false;
	mSurvivalButton->mBtnNoDraw = true;
	mSurvivalButton->mMouseVisible = false;
	mSurvivalButton->mPolygonShape[0] = SexyVector2(7.0f, 1.0f);
	mSurvivalButton->mPolygonShape[1] = SexyVector2(267.0f, 62.0f);
	mSurvivalButton->mPolygonShape[2] = SexyVector2(257.0f, 124.0f);
	mSurvivalButton->mPolygonShape[3] = SexyVector2(7.0f, 57.0f);
	mSurvivalButton->mUsePolygonShape = true;

	mZenGardenButton = MakeNewButton(
		Btn_ZenGarden,
		this,
		_S(""),
		nullptr,
		IMAGE_SELECTORSCREEN_ZENGARDEN,
		IMAGE_SELECTORSCREEN_ZENGARDENHIGHLIGHT,
		IMAGE_SELECTORSCREEN_ZENGARDENHIGHLIGHT
	);
	mZenGardenButton->Resize(0, 0, 130, 130);
	mZenGardenButton->mMouseVisible = false;
	mZenGardenButton->mClip = false;

	mOptionsButton = MakeNewButton(
		Btn_Options,
		this,
		_S(""),
		nullptr,
		IMAGE_SELECTORSCREEN_OPTIONS1,
		IMAGE_SELECTORSCREEN_OPTIONS2,
		IMAGE_SELECTORSCREEN_OPTIONS2
	);
	mOptionsButton->Resize(0, 0, IMAGE_SELECTORSCREEN_OPTIONS1->mWidth, IMAGE_SELECTORSCREEN_OPTIONS1->mHeight + 23);
	mOptionsButton->mBtnNoDraw = true;
	mOptionsButton->mMouseVisible = false;
	mOptionsButton->mButtonOffsetY = 15;

	mHelpButton = MakeNewButton(
		Btn_Help,
		this,
		_S(""),
		nullptr,
		IMAGE_SELECTORSCREEN_HELP1,
		IMAGE_SELECTORSCREEN_HELP2,
		IMAGE_SELECTORSCREEN_HELP2
	);
	mHelpButton->Resize(0, 0, IMAGE_SELECTORSCREEN_HELP1->mWidth, IMAGE_SELECTORSCREEN_HELP1->mHeight + 33);
	mHelpButton->mBtnNoDraw = true;
	mHelpButton->mMouseVisible = false;
	mHelpButton->mButtonOffsetY = 30;

	mQuitButton = MakeNewButton(
		Btn_Quit,
		this,
		_S(""),
		nullptr,
		IMAGE_SELECTORSCREEN_QUIT1,
		IMAGE_SELECTORSCREEN_QUIT2,
		IMAGE_SELECTORSCREEN_QUIT2
	);
	mQuitButton->Resize(0, 0, IMAGE_SELECTORSCREEN_QUIT1->mWidth + 10, IMAGE_SELECTORSCREEN_QUIT1->mHeight + 10);
	mQuitButton->mBtnNoDraw = true;
	mQuitButton->mMouseVisible = false;
	mQuitButton->mButtonOffsetX = 5;
	mQuitButton->mButtonOffsetY = 5;

	mChangeUserButton = MakeNewButton(
		Btn_ChangeUser,
		this,
		_S(""),
		nullptr,
		IMAGE_BLANK,
		IMAGE_BLANK,
		IMAGE_BLANK
	);
	mChangeUserButton->Resize(0, 0, 250, 30);
	mChangeUserButton->mBtnNoDraw = true;
	mChangeUserButton->mMouseVisible = false;

	mOverlayWidget = new GameSelectorOverlay(this);
	mOverlayWidget->Resize(0, 0, BOARD_WIDTH, BOARD_HEIGHT);

	mStoreButton = MakeNewButton(
		Btn_Store,
		this,
		_S(""),
		nullptr,
		IMAGE_SELECTORSCREEN_STORE,
		IMAGE_SELECTORSCREEN_STOREHIGHLIGHT,
		IMAGE_SELECTORSCREEN_STOREHIGHLIGHT
	);
	mStoreButton->Resize(405, 484, IMAGE_SELECTORSCREEN_STORE->mWidth, IMAGE_SELECTORSCREEN_STORE->mHeight);
	mStoreButton->mMouseVisible = false;

	mAlmanacButton = MakeNewButton(
		Btn_Almanac,
		this,
		_S(""),
		nullptr,
		IMAGE_SELECTORSCREEN_ALMANAC,
		IMAGE_SELECTORSCREEN_ALMANACHIGHLIGHT,
		IMAGE_SELECTORSCREEN_ALMANACHIGHLIGHT
	);
	mAlmanacButton->Resize(327, 428, IMAGE_SELECTORSCREEN_ALMANAC->mWidth, IMAGE_SELECTORSCREEN_ALMANAC->mHeight);
	mAlmanacButton->mMouseVisible = false;

	mApp->mMusic->MakeSureMusicIsPlaying(MusicTune::MUSIC_TUNE_TITLE_CRAZY_DAVE_MAIN_THEME);

	mStartingGame = false;
	mStartingGameCounter = 0;
	mMinigamesLocked = false;
	mPuzzleLocked = false;
	mSurvivalLocked = false;
	mUnlockSelectorCheat = false;
	mTrophyParticleID = PARTICLESYSTEMID_NULL;
	mShowStartButton = false;

	Reanimation* aSelectorReanim = mApp->AddReanimation(0.5f, 0.5f, 0, REANIM_SELECTOR_SCREEN);
	aSelectorReanim->PlayReanim("anim_open", REANIM_PLAY_ONCE_AND_HOLD, 0, 30.0f);
	aSelectorReanim->AssignRenderGroupToPrefix("flower", RENDER_GROUP_HIDDEN);
	aSelectorReanim->AssignRenderGroupToPrefix("leaf", RENDER_GROUP_HIDDEN);
	aSelectorReanim->AssignRenderGroupToTrack("SelectorScreen_BG", 1);
	mSelectorReanimID = mApp->ReanimationGetID(aSelectorReanim);
	mSelectorState = SelectorAnimState::SELECTOR_OPEN;
	int aFrameStart, aFrameCount;
	aSelectorReanim->GetFramesForLayer("anim_sign", aFrameStart, aFrameCount);
	aSelectorReanim->mFrameBasePose = aFrameStart + aFrameCount - 1;

	for (int i = 0; i < 6; i++)
	{
		Reanimation* aCloudReanim = mApp->AddReanimation(0.5f, 0.5f, 0, REANIM_SELECTOR_SCREEN);
		String aAnimName = StrFormat("anim_cloud%d", (i > 1 ? i + 2 : i + 1));
		aCloudReanim->PlayReanim(aAnimName.c_str(), REANIM_PLAY_ONCE_AND_HOLD, 0, 0.0f);
		mCloudReanimID[i] = mApp->ReanimationGetID(aCloudReanim);
		mCloudCounter[i] = RandRangeInt(-6000, 2000);
		if (mCloudCounter[i] < 0)
		{
			aCloudReanim->mAnimTime = -mCloudCounter[i] / 6000.0f;
			aCloudReanim->mAnimRate = 0.5f;
			mCloudCounter[i] = 0;
		}
		else
			aCloudReanim->mAnimRate = 0.0f;
	}

	for (int i = 0; i < 3; i++)
	{
		Reanimation* aFlowerReanim = mApp->AddReanimation(0.5f, 0.5f, 0, REANIM_SELECTOR_SCREEN);
		String aAnimName = StrFormat("anim_flower%d", i + 1);
		aFlowerReanim->PlayReanim(aAnimName.c_str(), REANIM_PLAY_ONCE_AND_HOLD, 0, 0.0f);
		aFlowerReanim->mAnimRate = 0.0f;
		aFlowerReanim->AttachToAnotherReanimation(aSelectorReanim, "SelectorScreen_BG_Right");
		aFlowerReanim->mIsAttachment = false;
		mFlowerReanimID[i] = mApp->ReanimationGetID(aFlowerReanim);
	}

	Reanimation* aLeafReanim = mApp->AddReanimation(0.5f, 0.5f, 0, REANIM_SELECTOR_SCREEN);
	aLeafReanim->PlayReanim("anim_grass", REANIM_LOOP, 0, 6.0f);
	aLeafReanim->mAnimRate = 0.0f;
	mLeafReanimID = mApp->ReanimationGetID(aLeafReanim);
	mLeafCounter = 50;

	SyncProfile(false);
	mApp->PlaySample(SOUND_ROLL_IN);
}

GameSelector::~GameSelector()
{
	if (mAdventureButton)
		delete mAdventureButton;
	if (mMinigameButton)
		delete mMinigameButton;
	if (mPuzzleButton)
		delete mPuzzleButton;
	if (mOptionsButton)
		delete mOptionsButton;
	if (mQuitButton)
		delete mQuitButton;
	if (mHelpButton)
		delete mHelpButton;
	if (mOverlayWidget)
		delete mOverlayWidget;
	if (mStoreButton)
		delete mStoreButton;
	if (mAlmanacButton)
		delete mAlmanacButton;
	if (mZenGardenButton)
		delete mZenGardenButton;
	if (mSurvivalButton)
		delete mSurvivalButton;
	if (mChangeUserButton)
		delete mChangeUserButton;

	delete mToolTip;
}

void GameSelector::SyncProfile(bool theShowLoading)
{
	int func = 0x44d0c0;
	int _theShowLoading = theShowLoading;
	__asm
	{
		push _theShowLoading
		mov ecx, this
		call func
	}
}

void GameSelector::AddedToManager(WidgetManager* theWidgetManager)
{
	int func = 0x44e9a0;
	__asm
	{
		push theWidgetManager
		mov ecx, this
		call func
	}
}

void GameSelector::RemovedFromManager(WidgetManager* theWidgetManager)
{
	int func = 0x44ea80;
	__asm
	{
		push theWidgetManager
		mov ecx, this
		call func
	}
}

void GameSelector::OrderInManagerChanged()
{
	int func = 0x44eb60;
	__asm
	{
		mov ecx, this
		call func
	}
}

void GameSelector::KeyDown(KeyCode theKey)
{
	int func = 0x44ec40;
	__asm
	{
		push theKey
		mov ecx, this
		call func
	}
}

void GameSelector::KeyChar(SexyChar theChar)
{
	int func = 0x44efe0;
	int _theChar = theChar;
	__asm
	{
		push _theChar
		mov ecx, this
		call func
	}
}

void GameSelector::ButtonMouseEnter(int theId)
{
	int func = 0x44f2a0;
	__asm
	{
		push theId
		mov ecx, this
		call func
	}
}

void GameSelector::ButtonPress(int theId, int theClickCount)
{
	int func = 0x44f320;
	__asm
	{
		push theClickCount
		push theId
		mov ecx, this
		call func
	};
}

void GameSelector::ButtonDepress(int theId)
{
	int func = 0x44f6a0;
	__asm
	{
		push theId
		mov ecx, this
		call func
	}
}

void GameSelector::MouseDown(int x, int y, int theClickCount)
{
	int func = 0x44f140;
	__asm
	{
		push theClickCount
		push y
		push x
		mov ecx, this
		call func
	}
}

void GameSelector::Update()
{
	int func = 0x44e080;
	__asm
	{
		mov ecx, this
		call func
	}
}

void GameSelector::Draw(Graphics* g)
{
	int func = 0x44d3f0;
	__asm
	{
		push g
		mov ecx, this
		call func
	}
}

void GameSelector::DrawOverlay(Graphics* g)
{
	int func = 0x44d930;
	__asm
	{
		push g
		mov ecx, this
		call func
	}
}

void GameSelector::TrackButton(DialogButton* theButton, const char* theTrackName, float theOffsetX, float theOffsetY)
{
	int func = 0x44e900;
	__asm
	{
		push theOffsetY
		push theOffsetX
		push theTrackName
		mov edi, theButton
		mov eax, this
		call func
	};
}
