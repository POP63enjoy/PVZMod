#include "LawnApp.h"
#include <Windows.h>
#include "EffectSystem.h"
#include "Reanimator.h"
#include "PlayerInfo.h"
#include "Dialog.h"
#include "WidgetManager.h"
#include "LawnDialog.h"
#include "GameButton.h"
#include "TodStringFile.h"
#include "ChallengeScreen.h"

using namespace PVZMod;

LawnApp*& PVZMod::gLawnApp = *(LawnApp**)0x6b9fe0;

Reanimation* LawnApp::ReanimationGet(ReanimationID theReanimID)
{
	return mEffectSystem->mReanimationHolder->mReanimations.DataArrayGet((size_t)theReanimID);
}

Reanimation* LawnApp::ReanimationTryToGet(ReanimationID theReanimationID)
{
	return mEffectSystem->mReanimationHolder->mReanimations.DataArrayTryToGet((unsigned int)theReanimationID);
}

ReanimationID LawnApp::ReanimationGetID(Reanimation* theReanimation)
{
	return (ReanimationID)mEffectSystem->mReanimationHolder->mReanimations.DataArrayGetId(theReanimation);
}

Reanimation* LawnApp::AddReanimation(float theX, float theY, int aRenderOrder, ReanimationType theReanimationType)
{
	int func = 0x456BD0;
	Reanimation* result;
	__asm
	{
		mov eax, this
		mov ebx, theReanimationType
		push aRenderOrder
		push theY
		push theX
		call func
		mov result, eax
	}
	return result;
}

void LawnApp::RemoveReanimation(ReanimationID theReanimationID)
{
	Reanimation* aReanim = ReanimationTryToGet(theReanimationID);
	if (aReanim)
	{
		aReanim->ReanimationDie();
	}
}

void LawnApp::ShowGameSelector()
{
	int func = 0x452710;
	__asm
	{
		mov ecx, this
		call func
	}
}

void LawnApp::KillGameSelector()
{
	int func = 0x452810;
	__asm
	{
		mov esi, this
		call func
	}
}

void LawnApp::ShowChallengeScreen(ChallengePage thePage)
{
	int func = 0x452a60;
	__asm
	{
		push thePage
		mov esi, this
		call func
	}
}

int LawnApp::GetCurrentChallengeIndex()
{
	return (int)mGameMode - (int)GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_1;
}

ChallengeDefinition& LawnApp::GetCurrentChallengeDef()
{
	return GetChallengeDefinition(GetCurrentChallengeIndex());
}

bool LawnApp::IsAdventureMode()
{
	return mGameMode == GAMEMODE_ADVENTURE;
}

bool LawnApp::IsWhackAZombieLevel()
{
	if (mBoard == nullptr)
		return false;

	if (mGameMode == GAMEMODE_CHALLENGE_WHACK_A_ZOMBIE)
		return true;

	return IsAdventureMode() && mPlayerInfo->mLevel == 15;
}

bool LawnApp::IsFirstTimeAdventureMode()
{
	return IsAdventureMode() && !HasFinishedAdventure();
}

bool LawnApp::HasFinishedAdventure()
{
	return mPlayerInfo && mPlayerInfo->mFinishedAdventure > 0;
}

bool LawnApp::IsMiniBossLevel()
{
	if (mBoard == nullptr)
		return false;

	return
		(IsAdventureMode() && mPlayerInfo->mLevel == 10) ||
		(IsAdventureMode() && mPlayerInfo->mLevel == 20) ||
		(IsAdventureMode() && mPlayerInfo->mLevel == 30);
}

bool LawnApp::IsSurvivalMode()
{
	return mGameMode >= GAMEMODE_SURVIVAL_NORMAL_STAGE_1 && mGameMode <= GAMEMODE_SURVIVAL_ENDLESS_STAGE_5;
}

bool LawnApp::IsSurvivalNormal(GameMode theGameMode)
{
	int aLevel = theGameMode - GAMEMODE_SURVIVAL_NORMAL_STAGE_1;
	return aLevel >= 0 && aLevel <= 4;
}

bool LawnApp::IsSurvivalHard(GameMode theGameMode)
{
	int aLevel = theGameMode - GAMEMODE_SURVIVAL_HARD_STAGE_1;
	return aLevel >= 0 && aLevel <= 4;
}

bool LawnApp::IsSurvivalEndless(GameMode theGameMode)
{
	int aLevel = theGameMode - GAMEMODE_SURVIVAL_ENDLESS_STAGE_1;
	return aLevel >= 0 && aLevel <= 4;
}

bool LawnApp::IsSquirrelLevel()
{
	return mBoard && mGameMode == GAMEMODE_CHALLENGE_SQUIRREL;
}

bool LawnApp::IsStormyNightLevel()
{
	if (mBoard == nullptr)
		return false;

	if (mGameMode == GAMEMODE_CHALLENGE_STORMY_NIGHT)
		return true;

	return IsAdventureMode() && mPlayerInfo->mLevel == 40;
}

bool LawnApp::IsLittleTroubleLevel()
{
	return (mBoard && (mGameMode == GAMEMODE_CHALLENGE_LITTLE_TROUBLE || (mGameMode == GAMEMODE_ADVENTURE && mPlayerInfo->mLevel == 25)));
}

bool LawnApp::IsBungeeBlitzLevel()
{
	if (mBoard == nullptr)
		return false;

	if (mGameMode == GAMEMODE_CHALLENGE_BUNGEE_BLITZ)
		return true;

	return IsAdventureMode() && mPlayerInfo->mLevel == 45;
}

bool LawnApp::IsShovelLevel()
{
	return mBoard && mGameMode == GAMEMODE_CHALLENGE_SHOVEL;
}

bool LawnApp::IsWallnutBowlingLevel()
{
	if (mBoard == nullptr)
		return false;

	if (mGameMode == GAMEMODE_CHALLENGE_WALLNUT_BOWLING || mGameMode == GAMEMODE_CHALLENGE_WALLNUT_BOWLING_2)
		return true;

	return IsAdventureMode() && mPlayerInfo->mLevel == 5;
}

bool LawnApp::IsScaryPotterLevel()
{
	if (mGameMode >= GAMEMODE_SCARY_POTTER_1 && mGameMode <= GAMEMODE_SCARY_POTTER_ENDLESS)
		return true;

	return IsAdventureMode() && mPlayerInfo->mLevel == 35;
}

bool LawnApp::IsIZombieLevel()
{
	if (mBoard == nullptr)
		return false;

	return
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_1 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_2 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_3 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_4 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_5 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_6 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_7 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_8 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_9 ||
		mGameMode == GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS;
}

void LawnApp::PreNewGame(GameMode theGameMode, bool theLookForSavedGame)
{
	int func = 0x452390;
	int _theLookForSavedGame = theLookForSavedGame;
	__asm
	{
		mov esi, this
		push _theLookForSavedGame
		push theGameMode
		call func;
	}
}

void LawnApp::PlayFoley(FoleyType theFoleyType)
{
	int func = 0x4565d0;
	__asm
	{
		mov esi, theFoleyType
		mov eax, this
		call func
	}
}

void LawnApp::CenterDialog(Dialog* theDialog, int theWidth, int theHeight)
{
	theDialog->Resize((mWidth - theWidth) / 2, (mHeight - theHeight) / 2, theWidth, theHeight);
}

int LawnApp::LawnMessageBox(int theDialogId, const SexyChar* theHeaderName, const SexyChar* theLinesName, const SexyChar* theButton1Name, const SexyChar* theButton2Name, int theButtonMode)
{
	Widget* aOldFocus = mWidgetManager->mFocusWidget;

	LawnDialog* aDialog = (LawnDialog*)DoDialog(theDialogId, true, theHeaderName, theLinesName, theButton1Name, theButtonMode);
	if (aDialog->mYesButton)
	{
		aDialog->mYesButton->mLabel = TodStringTranslate(theButton1Name);
	}
	if (aDialog->mNoButton)
	{
		aDialog->mNoButton->mLabel = TodStringTranslate(theButton2Name);
	}
	//aDialog->CalcSize(0, 0);

	mWidgetManager->SetFocus(aDialog);
	int aResult = aDialog->WaitForResult(true);
	mWidgetManager->SetFocus(aOldFocus);

	return aResult;
}
