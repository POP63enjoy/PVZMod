#include "TitleScreen.h"
#include "LawnApp.h"
#include "HyperlinkWidget.h"

using namespace PVZMod;

TitleScreen::TitleScreen(LawnApp* theApp)
{
	mCurBarWidth = 0.0f;
	mTotalBarWidth = 314.0f;
	mBarVel = 0.2f;
	mBarStartProgress = 0.0f;
	mPrevLoadingPercent = 0.0f;
	mApp = theApp;
	mTitleAge = 0;
	mNeedRegister = false;
	mRegisterClicked = false;
	mNeedShowRegisterBox = false;
	mLoadingThreadComplete = false;
	mDrawnYet = false;
	mNeedToInit = true;
	mQuickLoadKey = KEYCODE_UNKNOWN;
	mDisplayPartnerLogo = mApp->GetBoolean("DisplayPartnerLogo");
	mTitleState = TITLESTATE_WAITING_FOR_FIRST_DRAW;
	mTitleStateDuration = 0;
	mTitleStateCounter = 0;
	mLoaderScreenIsLoaded = false;

	mStartButton = new HyperlinkWidget(0, this);
	mStartButton->mColor = Color(218, 184, 33);
	mStartButton->mOverColor = Color(250, 90, 15);
	mStartButton->mUnderlineSize = 0;
	mStartButton->mDisabled = true;
	mStartButton->mVisible = false;
}

TitleScreen::~TitleScreen()
{
	delete mStartButton;
}

void TitleScreen::AddedToManager(WidgetManager* theWidgetManager)
{
	int func = 0x4927d0;
	__asm
	{
		push theWidgetManager
		mov ecx, this
		call func
	}
}

void TitleScreen::RemovedFromManager(WidgetManager* theWidgetManager)
{
	int func = 0x492800;
	__asm
	{
		push theWidgetManager
		mov ecx, this
		call func
	}
}

void TitleScreen::ButtonPress(int theId)
{
	int func = 0x492830;
	__asm
	{
		push theId
		mov ecx, this
		call func
	}
}

void TitleScreen::ButtonDepress(int theId)
{
	int func = 0x492850;
	__asm
	{
		push theId
		mov ecx, this
		call func
	}
}

void TitleScreen::MouseDown(int x, int y, int theClickCount)
{
	int func = 0x492880;
	__asm
	{
		push theClickCount
		push y
		push x
		mov ecx, this
		call func
	}
}

void TitleScreen::KeyDown(KeyCode theKey)
{
	int func = 0x4928c0;
	__asm
	{
		push theKey
		mov ecx, this
		call func
	}
}

void TitleScreen::Draw(Graphics* g)
{
	int func = 0x491830;
	__asm
	{
		push g
		mov ecx, this
		call func
	}
}

void TitleScreen::Update()
{
	int func = 0x491ee0;
	__asm
	{
		mov ecx, this
		call func
	}
}
