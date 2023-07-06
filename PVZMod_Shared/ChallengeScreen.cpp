#include "ChallengeScreen.h"
#include "GameButton.h"
#include "Res.h"
#include "TodStringFile.h"
#include "ToolTipWidget.h"
#include "Music.h"
#include "PlayerInfo.h"
#include "TodCommon.h"
#include <cassert>

using namespace PVZMod;

ChallengeDefinition* PVZMod::gChallengeDefs = (ChallengeDefinition*)0x6b2b60;

ChallengeScreen::ChallengeScreen(LawnApp* theApp, ChallengePage thePage)
{
	mLockShakeX = 0;
	mLockShakeY = 0;
	mPageIndex = thePage;
	mApp = theApp;
	mClip = false;
	mCheatEnableChallenges = false;
	mUnlockState = UNLOCK_OFF;
	mUnlockChallengeIndex = -1;
	mUnlockStateCounter = 0;
	TodLoadResources("DelayLoad_ChallengeScreen");

	mBackButton = MakeNewButton(ChallengeScreen_Back, this, _S("[BACK_TO_MENU]"), nullptr, IMAGE_SEEDCHOOSER_BUTTON2,
		IMAGE_SEEDCHOOSER_BUTTON2_GLOW, IMAGE_SEEDCHOOSER_BUTTON2_GLOW);
	mBackButton->mTextDownOffsetX = 1;
	mBackButton->mTextDownOffsetY = 1;
	mBackButton->mColors[ButtonWidget::COLOR_LABEL] = Color(42, 42, 90);
	mBackButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(42, 42, 90);
	mBackButton->Resize(18, 568, 111, 26);

	for (int aPageIdx = CHALLENGE_PAGE_SURVIVAL; aPageIdx < MAX_CHALLANGE_PAGES; aPageIdx++)
	{
		ButtonWidget* aPageButton = new ButtonWidget(ChallengeScreen_Page + aPageIdx, this);
		aPageButton->mDoFinger = true;
		mPageButton[aPageIdx] = aPageButton;
		if (aPageIdx == CHALLENGE_PAGE_LIMBO)
			aPageButton->mLabel = TodStringTranslate(_S("Limbo Page"));
		else
			aPageButton->mLabel = TodReplaceNumberString(_S("[PAGE_X]"), _S("{PAGE}"), aPageIdx);
		aPageButton->mButtonImage = IMAGE_BLANK;
		aPageButton->mOverImage = IMAGE_BLANK;
		aPageButton->mDownImage = IMAGE_BLANK;
		aPageButton->SetFont(FONT_BRIANNETOD12);
		aPageButton->mColors[ButtonWidget::COLOR_LABEL] = Color(255, 240, 0);
		aPageButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(220, 220, 0);
		aPageButton->Resize(200 + 100 * aPageIdx, 540, 100, 75);
		if (!ShowPageButtons() || aPageIdx == CHALLENGE_PAGE_SURVIVAL || aPageIdx == CHALLENGE_PAGE_PUZZLE)
			aPageButton->mVisible = false;
	}

	for (int aChallengeMode = 0; aChallengeMode < NUM_CHALLENGE_MODES; aChallengeMode++)
	{
		ChallengeDefinition& aChlDef = GetChallengeDefinition(aChallengeMode);
		ButtonWidget* aChallengeButton = new ButtonWidget(ChallengeScreen_Mode + aChallengeMode, this);
		mChallengeButtons[aChallengeMode] = aChallengeButton;
		aChallengeButton->mDoFinger = true;
		aChallengeButton->mFrameNoDraw = true;
		if (aChlDef.mPage == CHALLENGE_PAGE_CHALLENGE || aChlDef.mPage == CHALLENGE_PAGE_LIMBO || aChlDef.mPage == CHALLENGE_PAGE_PUZZLE)
			aChallengeButton->Resize(38 + aChlDef.mCol * 155, 93 + aChlDef.mRow * 119, 104, 115);
		else
			aChallengeButton->Resize(38 + aChlDef.mCol * 155, 125 + aChlDef.mRow * 145, 104, 115);
		if (MoreTrophiesNeeded(aChallengeMode))
		{
			aChallengeButton->mDoFinger = false;
			aChallengeButton->mDisabled = true;
		}
	}

	mToolTip = new ToolTipWidget();
	mToolTip->mCenter = true;
	mToolTip->mVisible = false;
	UpdateButtons();

	if (mApp->mGameMode != GAMEMODE_UPSELL || mApp->mGameScene != SCENE_LEVEL_INTRO)
		mApp->mMusic->MakeSureMusicIsPlaying(MUSIC_TUNE_CHOOSE_YOUR_SEEDS);

	bool aIsIZombie = false;
	if (mPageIndex == CHALLENGE_PAGE_SURVIVAL && mApp->mPlayerInfo->mHasNewSurvival)
	{
		SetUnlockChallengeIndex(mPageIndex, false);
		mApp->mPlayerInfo->mHasNewSurvival = false;
	}
	else if (mPageIndex == CHALLENGE_PAGE_CHALLENGE && mApp->mPlayerInfo->mHasNewMiniGame)
	{
		SetUnlockChallengeIndex(mPageIndex, false);
		mApp->mPlayerInfo->mHasNewMiniGame = false;
	}
	else if (mPageIndex == CHALLENGE_PAGE_PUZZLE)
	{
		if (mApp->mPlayerInfo->mHasNewScaryPotter)
		{
			SetUnlockChallengeIndex(mPageIndex, false);
			mApp->mPlayerInfo->mHasNewScaryPotter = false;
		}
		else if (mApp->mPlayerInfo->mHasNewIZombie)
		{
			SetUnlockChallengeIndex(mPageIndex, true);
			mApp->mPlayerInfo->mHasNewIZombie = false;
		}
	}
}

ChallengeScreen::~ChallengeScreen()
{
	delete mBackButton;
	for (ButtonWidget* aPageButton : mPageButton)
		delete aPageButton;
	for (ButtonWidget* aChallengeButton : mChallengeButtons)
		delete aChallengeButton;
	delete mToolTip;
}

void ChallengeScreen::Draw(Graphics* g)
{
	int func = 0x430ed0;
	__asm
	{
		push g
		mov ecx, this
		call func
	}
}

void ChallengeScreen::Update()
{
	int func = 0x4312d0;
	__asm
	{
		mov ecx, this
		call func
	}
}

void ChallengeScreen::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
	AddWidget(mBackButton);
	for (ButtonWidget* aButton : mPageButton) AddWidget(aButton);
	for (ButtonWidget* aButton : mChallengeButtons) AddWidget(aButton);
}

void ChallengeScreen::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
	RemoveWidget(mBackButton);
	for (ButtonWidget* aButton : mPageButton) RemoveWidget(aButton);
	for (ButtonWidget* aButton : mChallengeButtons) RemoveWidget(aButton);
}

void ChallengeScreen::ButtonPress(int theId)
{
	mApp->PlaySample(SOUND_BUTTONCLICK);
}

void ChallengeScreen::ButtonDepress(int theId)
{
	int func = 0x431500;
	__asm
	{
		push theId
		mov ecx, this
		call func
	}
}

void ChallengeScreen::SetUnlockChallengeIndex(ChallengePage thePage, bool theIsIZombie)
{
	int func = 0x430080;
	int _theIsIZombie = theIsIZombie;
	__asm
	{
		push _theIsIZombie
		mov ebx, thePage
		push this
		call func
	}
}

int ChallengeScreen::MoreTrophiesNeeded(int theChallengeIndex)
{
	int func = 0x430100;
	int result;
	__asm
	{
		mov eax, theChallengeIndex
		mov ecx, this
		call func
		mov result, eax
	}
	return result;
}

bool ChallengeScreen::ShowPageButtons()
{
	return mApp->mTodCheatKeys && mPageIndex != CHALLENGE_PAGE_SURVIVAL && mPageIndex != CHALLENGE_PAGE_PUZZLE;
}

void ChallengeScreen::UpdateButtons()
{
	for (int aChallengeMode = 0; aChallengeMode < NUM_CHALLENGE_MODES; aChallengeMode++)
		mChallengeButtons[aChallengeMode]->mVisible = GetChallengeDefinition(aChallengeMode).mPage == mPageIndex;
	for (int aPage = 0; aPage < MAX_CHALLANGE_PAGES; aPage++)
	{
		ButtonWidget* aPageButton = mPageButton[aPage];
		if (aPage == mPageIndex)
		{
			aPageButton->mColors[ButtonWidget::COLOR_LABEL] = Color(64, 64, 64);
			aPageButton->mDisabled = true;
		}
		else
		{
			aPageButton->mColors[ButtonWidget::COLOR_LABEL] = Color(255, 240, 0);
			aPageButton->mDisabled = false;
		}
	}
}

ChallengeDefinition& PVZMod::GetChallengeDefinition(int theChallengeMode)
{
	assert(theChallengeMode >= 0 && theChallengeMode < NUM_CHALLENGE_MODES);

	ChallengeDefinition& aDef = gChallengeDefs[theChallengeMode];
	assert(aDef.mChallengeMode == theChallengeMode + GAMEMODE_SURVIVAL_NORMAL_STAGE_1);

	return gChallengeDefs[theChallengeMode];
}
