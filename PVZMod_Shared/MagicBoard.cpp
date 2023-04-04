#include "PVZMod.h"
#include "Board.h"
#include "LawnApp.h"
#include "MagicBoard.h"
#include "TodCommon.h"
#include "Challenge.h"
#include "Graphics.h"
#include "GameObjectPatch.h"
#include "WidgetPatch.h"
#include "TodStringFile.h"
#include "ChallengeScreen.h"
#include <format>

using namespace PVZMod;

void MagicBoard::Binding_ExtendBase(InitPatch& patch, size_t theBoardSize, bool autoSaveExtendedData)
{
	patch.PatchTask("MagicBoard::Binding_ExtendBase", [&]
		{
			*(int*)0x45243f = theBoardSize;

			if (autoSaveExtendedData)
				*(int*)0x485711 += theBoardSize - sizeof(Board);

		}, true, true);
}

void MagicBoard::Binding_MF_Constructor(InitPatch& patch, const std::function<void(Board* _this, LawnApp* theApp, Constructor_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_Constructor", [&]
		{
			static std::vector<std::function<void(Board* _this, LawnApp* theApp, Constructor_t& base)>> func_list;
			patch.PatchTask("MagicBoard::Binding_MF_Constructor(Hook)", [&]
				{
					using Raw_t = Board * (__fastcall*)(LawnApp* theApp, int, Board* _this);
					static Raw_t raw;
					Raw_t detour = [](LawnApp* theApp, int, Board* _this)
					{
						Constructor_t base;

						base.mFunction = [&](Board* __this, LawnApp* _theApp)
						{
							std::swap(_this, __this);
							std::swap(theApp, _theApp);
							base();
							_this = __this;
							theApp = _theApp;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								raw(theApp, 0, _this);
							else
							{
								i--;
								func_list[i](_this, theApp, base);
								i++;
							}
						};

						func_list.back()(_this, theApp, base);
						return _this;
					};
					raw = (Raw_t)patch.mHook.HookFunction((void*)0x409130, detour);
				});
			func_list.push_back(func);
		}, false);
}

void MagicBoard::Binding_MF_Destructor(InitPatch& patch, const std::function<void(Board* _this, Destructor_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_Destructor", [&]
		{
			static std::vector<std::function<void(Board* _this, Destructor_t& base)>> func_list;
			patch.PatchTask("MagicBoard::Binding_MF_Destructor(Hook)", [&]
				{
					using Raw_t = void(__fastcall*)(Board* _this);
					static Raw_t raw;
					Raw_t detour = [](Board* _this)
					{
						Destructor_t base;

						base.mFunction = [&](Board* __this)
						{
							std::swap(_this, __this);
							base();
							_this = __this;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								raw(_this);
							else
							{
								i--;
								func_list[i](_this, base);
								i++;
							}
						};

						func_list.back()(_this, base);
					};
					raw = (Raw_t)patch.mHook.HookFunction((void*)0x409bb0, detour);
				});
			func_list.push_back(func);
		}, false);
}

void MagicBoard::Binding_MF_InitLevel(InitPatch& patch, const std::function<void(Board* _this, InitLevel_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_InitLevel", [&]
		{
			static std::vector<std::function<void(Board* _this, InitLevel_t& base)>> func_list;
			patch.PatchTask("MagicBoard::Binding_MF_InitLevel(Hook)", [&]
				{
					using Raw_t = void(__stdcall*)(Board* _this);
					static Raw_t raw;
					Raw_t detour = [](Board* _this)
					{
						InitLevel_t base;

						base.mFunction = [&](Board* __this)
						{
							std::swap(_this, __this);
							base();
							_this = __this;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								raw(_this);
							else
							{
								i--;
								func_list[i](_this, base);
								i++;
							}
						};

						func_list.back()(_this, base);
					};
					raw = (Raw_t)patch.mHook.HookFunction((void*)0x40c4a0, detour);
				});
			func_list.push_back(func);
		}, false);
}

static void(__stdcall* _DisposeBoard_detour)(Board* _this);
static void* _DisposeBoard_raw_addr;

static void __declspec(naked) _DisposeBoard_naked_detour()
{
	__asm
	{
		push esi
		call _DisposeBoard_detour
		ret
	}
}
static void _DisposeBoard_raw(Board* _this)
{
	__asm
	{
		mov esi, _this
		call _DisposeBoard_raw_addr
	}
}

void MagicBoard::Binding_MF_DisposeBoard(InitPatch& patch, const std::function<void(Board* _this, DisposeBoard_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_DisposeBoard", [&]
		{
			static std::vector<std::function<void(Board* _this, DisposeBoard_t& base)>> func_list;
			patch.PatchTask("MagicBoard::Binding_MF_DisposeBoard(Hook)", [&]
				{
					_DisposeBoard_detour = [](Board* _this)
					{
						DisposeBoard_t base;

						base.mFunction = [&](Board* __this)
						{
							std::swap(_this, __this);
							base();
							_this = __this;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_DisposeBoard_raw(_this);
							else
							{
								i--;
								func_list[i](_this, base);
								i++;
							}
						};

						func_list.back()(_this, base);
					};
					_DisposeBoard_raw_addr = patch.mHook.HookFunction((void*)0x409f80, &_DisposeBoard_raw);
				});
			func_list.push_back(func);
		}, false);
}

static void _ZombiePicker_CalculateNumWaves_base(Board* _this)
{
	if (_this->mApp->IsAdventureMode())
	{
		if (_this->mApp->IsWhackAZombieLevel())
		{
			_this->mNumWaves = 8;
		}
		else
		{
			_this->mNumWaves = gZombieWaves[ClampInt(_this->mLevel - 1, 0, 49)];
			if (!_this->mApp->IsFirstTimeAdventureMode() && !_this->mApp->IsMiniBossLevel())
			{
				_this->mNumWaves = _this->mNumWaves < 10 ? 20 : _this->mNumWaves + 10;
			}
		}
	}
	else
	{
		GameMode aGameMode = _this->mApp->mGameMode;
		if (_this->mApp->IsSurvivalMode() || aGameMode == GAMEMODE_CHALLENGE_LAST_STAND)
			_this->mNumWaves = _this->GetNumWavesPerSurvivalStage();
		else if (aGameMode == GAMEMODE_CHALLENGE_ZEN_GARDEN || aGameMode == GAMEMODE_TREE_OF_WISDOM || _this->mApp->IsSquirrelLevel())
			_this->mNumWaves = 0;
		else if (aGameMode == GAMEMODE_CHALLENGE_WHACK_A_ZOMBIE)
			_this->mNumWaves = 12;
		else if (aGameMode == GAMEMODE_CHALLENGE_WALLNUT_BOWLING || aGameMode == GAMEMODE_CHALLENGE_AIR_RAID ||
			aGameMode == GAMEMODE_CHALLENGE_GRAVE_DANGER || aGameMode == GAMEMODE_CHALLENGE_HIGH_GRAVITY ||
			aGameMode == GAMEMODE_CHALLENGE_PORTAL_COMBAT || aGameMode == GAMEMODE_CHALLENGE_WAR_AND_PEAS ||
			aGameMode == GAMEMODE_CHALLENGE_INVISIGHOUL)
			_this->mNumWaves = 20;
		else if (_this->mApp->IsStormyNightLevel() || _this->mApp->IsLittleTroubleLevel() || _this->mApp->IsBungeeBlitzLevel() ||
			aGameMode == GAMEMODE_CHALLENGE_COLUMN || _this->mApp->IsShovelLevel() || aGameMode == GAMEMODE_CHALLENGE_WAR_AND_PEAS_2 ||
			aGameMode == GAMEMODE_CHALLENGE_WALLNUT_BOWLING_2 || aGameMode == GAMEMODE_CHALLENGE_POGO_PARTY)
			_this->mNumWaves = 30;
		else
			_this->mNumWaves = 40;
	}
};

static auto _ZombiePicker_CalculateNumWaves = _ZombiePicker_CalculateNumWaves_base;

static bool _ZombiePicker_SpecialLevelPut_base(Board* _this, ZombiePicker& theZombiePicker, int theWave)
{
	bool aIsFlagWave = _this->IsFlagWave(theWave);
	bool aIsFinalWave = theWave == _this->mNumWaves - 1;

	if (_this->mApp->IsBungeeBlitzLevel() && aIsFlagWave)
	{
		// 蹦极闪电战关卡的每大波固定刷出 5 只蹦极僵尸
		for (int _i = 0; _i < 5; _i++)
			_this->PutZombieInWave(ZOMBIE_BUNGEE, theWave, &theZombiePicker);

		if (!aIsFinalWave)
			return true;
	}
	return false;
};

static auto _ZombiePicker_SpecialLevelPut = _ZombiePicker_SpecialLevelPut_base;

static void _ZombiePicker_CalculateBasicPoints_base(Board* _this, ZombiePicker& theZombiePicker, int theWave)
{
	int& aZombiePoints = theZombiePicker.mZombiePoints;
	// 根据关卡计算本波的基础僵尸点数
	if (_this->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_LAST_STAND)
	{
		aZombiePoints = (_this->mChallenge->mSurvivalStage * _this->GetNumWavesPerSurvivalStage() + theWave + 10) * 2 / 5 + 1;
	}
	else if (_this->mApp->IsSurvivalMode() && _this->mChallenge->mSurvivalStage > 0)
	{
		aZombiePoints = (_this->mChallenge->mSurvivalStage * _this->GetNumWavesPerSurvivalStage() + theWave) * 2 / 5 + 1;
	}
	else if (_this->mApp->IsAdventureMode() && _this->mApp->HasFinishedAdventure() && _this->mLevel != 5)
	{
		aZombiePoints = theWave * 2 / 5 + 1;
	}
	else
	{
		aZombiePoints = theWave / 3 + 1;
	}
};

static auto _ZombiePicker_CalculateBasicPoints = _ZombiePicker_CalculateBasicPoints_base;

static void _ZombiePicker_PutBeforeMultiple_base(Board* _this, ZombiePicker& theZombiePicker, int theWave)
{
	bool aIsFlagWave = _this->IsFlagWave(theWave);
	int& aZombiePoints = theZombiePicker.mZombiePoints;
	// 旗帜波的特殊调整
	if (aIsFlagWave)
	{
		int aPlainZombiesNum = min(aZombiePoints, 8);
		aZombiePoints = (int)(aZombiePoints * 2.5f);
		if (_this->mApp->mGameMode != GAMEMODE_CHALLENGE_WAR_AND_PEAS && _this->mApp->mGameMode != GAMEMODE_CHALLENGE_WAR_AND_PEAS_2)
		{
			for (int _i = 0; _i < aPlainZombiesNum; _i++)
				_this->PutZombieInWave(ZombieType::ZOMBIE_NORMAL, theWave, &theZombiePicker);
			_this->PutZombieInWave(ZombieType::ZOMBIE_FLAG, theWave, &theZombiePicker);
		}
	}
}

static auto _ZombiePicker_PutBeforeMultiple = _ZombiePicker_PutBeforeMultiple_base;

static void _ZombiePicker_CalculateMultiplePoints_base(Board* _this, ZombiePicker& theZombiePicker, int theWave)
{
	int& aZombiePoints = theZombiePicker.mZombiePoints;
	// 部分关卡的多倍出怪
	if (_this->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_COLUMN)
		aZombiePoints *= 6;
	else if (_this->mApp->IsLittleTroubleLevel() || _this->mApp->IsWallnutBowlingLevel())
		aZombiePoints *= 4;
	else if (_this->mApp->IsMiniBossLevel())
		aZombiePoints *= 3;
	else if (_this->mApp->IsStormyNightLevel() && _this->mApp->IsAdventureMode())
		aZombiePoints *= 3;
	else if (_this->mApp->IsShovelLevel() || _this->mApp->IsBungeeBlitzLevel() ||
		_this->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_PORTAL_COMBAT || _this->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_INVISIGHOUL)
		aZombiePoints *= 2;
}

static auto _ZombiePicker_CalculateMultiplePoints = _ZombiePicker_CalculateMultiplePoints_base;

static void _ZombiePicker_PutPreset_base(Board* _this, ZombiePicker& theZombiePicker, int theWave)
{
	ZombieType aIntroZombieType = _this->GetIntroducedZombieType();
	bool aIsFlagWave = _this->IsFlagWave(theWave);
	bool aIsFinalWave = theWave == _this->mNumWaves - 1;
	if (aIntroZombieType != ZombieType::ZOMBIE_INVALID && aIntroZombieType != ZombieType::ZOMBIE_DUCKY_TUBE)
	{
		bool aSpawnIntro = false;
		if ((aIntroZombieType == ZombieType::ZOMBIE_DIGGER || aIntroZombieType == ZombieType::ZOMBIE_BALLOON))
		{
			if (theWave + 1 == 7 || aIsFinalWave)
				aSpawnIntro = true;
		}
		else if (aIntroZombieType == ZombieType::ZOMBIE_YETI)
		{
			if (theWave == _this->mNumWaves / 2 && !_this->mApp->mKilledYetiAndRestarted)
				aSpawnIntro = true;
		}
		else if (theWave == _this->mNumWaves / 2 || aIsFinalWave)
			aSpawnIntro = true;

		if (aSpawnIntro)
			_this->PutZombieInWave(aIntroZombieType, theWave, &theZombiePicker);
	}

	// 5-10 关卡的最后一波加入一只伽刚特尔
	if (_this->mLevel == 50 && aIsFinalWave)
		_this->PutZombieInWave(ZombieType::ZOMBIE_GARGANTUAR, theWave, &theZombiePicker);

	// 冒险模式关卡的最后一波会出现本关卡可能出现的所有僵尸
	if (_this->mApp->IsAdventureMode() && aIsFinalWave)
		_this->PutInMissingZombies(theWave, &theZombiePicker);

	// 柱子关卡的特殊出怪
	if (_this->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_COLUMN)
	{
		// 每大波的第 5 小波，固定出现 10 只扶梯僵尸
		if (theWave % 10 == 5)
			for (int _i = 0; _i < 10; _i++)
				_this->PutZombieInWave(ZombieType::ZOMBIE_LADDER, theWave, &theZombiePicker);

		// 每大波的第 8 小波，固定出现 10 只玩偶匣僵尸
		if (theWave % 10 == 8)
			for (int _i = 0; _i < 10; _i++)
				_this->PutZombieInWave(ZombieType::ZOMBIE_JACK_IN_THE_BOX, theWave, &theZombiePicker);

		// 第 19/29 小波，固定出现 3/5 只伽刚特尔
		if (theWave == 19)
			for (int _i = 0; _i < 3; _i++)
				_this->PutZombieInWave(ZombieType::ZOMBIE_GARGANTUAR, theWave, &theZombiePicker);
		if (theWave == 29)
			for (int _i = 0; _i < 5; _i++)
				_this->PutZombieInWave(ZombieType::ZOMBIE_GARGANTUAR, theWave, &theZombiePicker);
	}
}

static auto _ZombiePicker_PutPreset = _ZombiePicker_PutPreset_base;

static void _ZombiePicker_PutRandom_base(Board* _this, ZombiePicker& theZombiePicker, int theWave)
{
	while (theZombiePicker.mZombiePoints > 0 && theZombiePicker.mZombieCount < 50)
	{
		ZombieType aZombieType = _this->PickZombieType(theZombiePicker.mZombiePoints, theWave, &theZombiePicker);
		_this->PutZombieInWave(aZombieType, theWave, &theZombiePicker);
	}
}

auto _ZombiePicker_PutRandom = _ZombiePicker_PutRandom_base;

static void _PatchMF_ZombiePicker(InitPatch& patch)
{
	patch.PatchTask("_PatchMF_ZombiePicker", [&]
		{
			patch.mHook.InsertCodeAndJump((void*)0x40a7f0, (void*)0x40b61f, [](Hook::Regs* regs)
				{
					Board* _this = (Board*)regs->edi;

					_ZombiePicker_CalculateNumWaves(_this);

					ZombiePicker aZombiePicker;
					ZombiePickerInit(&aZombiePicker);
					assert(_this->mNumWaves <= 100);

					for (int aWave = 0; aWave < _this->mNumWaves; aWave++)
					{
						ZombiePickerInitForWave(&aZombiePicker);
						_this->mZombiesInWave[aWave][0] = ZOMBIE_INVALID;

						if (_ZombiePicker_SpecialLevelPut(_this, aZombiePicker, aWave))
							continue;

						_ZombiePicker_CalculateBasicPoints(_this, aZombiePicker, aWave);
						_ZombiePicker_PutBeforeMultiple(_this, aZombiePicker, aWave);
						_ZombiePicker_CalculateMultiplePoints(_this, aZombiePicker, aWave);
						_ZombiePicker_PutPreset(_this, aZombiePicker, aWave);
						_ZombiePicker_PutRandom(_this, aZombiePicker, aWave);
					}
				});
		});
}

void MagicBoard::Binding_MF_ZombiePicker_CalculateNumWaves(InitPatch& patch, const std::function<void(Board* _this, ZombiePicker_CalculateNumWaves_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_ZombiePicker_CalculateNumWaves", [&]
		{
			static std::vector<std::function<void(Board* _this, ZombiePicker_CalculateNumWaves_t& base)>> func_list;
			patch.PatchTask("MagicBoard::Binding_MF_ZombiePicker_CalculateNumWaves(Hook)", [&]
				{
					_PatchMF_ZombiePicker(patch);
					_ZombiePicker_CalculateNumWaves = [](Board* _this)
					{
						ZombiePicker_CalculateNumWaves_t base;

						base.mFunction = [&](Board* __this)
						{
							std::swap(_this, __this);
							base();
							_this = __this;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_ZombiePicker_CalculateNumWaves_base(_this);
							else
							{
								i--;
								func_list[i](_this, base);
								i++;
							}
						};

						func_list.back()(_this, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicBoard::Binding_MF_ZombiePicker_SpecialLevelPut(InitPatch& patch, const std::function<bool(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_SpecialLevelPut_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_ZombiePicker_SpecialLevelPut", [&]
		{
			static std::vector<std::function<bool(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_SpecialLevelPut_t& base)>> func_list;
			patch.PatchTask("MagicBoard::Binding_MF_ZombiePicker_SpecialLevelPut(Hook)", [&]
				{
					_PatchMF_ZombiePicker(patch);
					_ZombiePicker_SpecialLevelPut = [](Board* _this, ZombiePicker& theZombiePicker, int theWave)
					{
						ZombiePicker_SpecialLevelPut_t base;
						auto p_theZombiePicker = &theZombiePicker;

						base.mFunction = [&](Board* __this, ZombiePicker& _theZombiePicker, int _theWave)
						{
							auto _p_theZombiePicker = &_theZombiePicker;
							std::swap(_this, __this);
							std::swap(p_theZombiePicker, _p_theZombiePicker);
							bool result = base();
							_this = __this;
							p_theZombiePicker = _p_theZombiePicker;
							return result;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								return _ZombiePicker_SpecialLevelPut_base(_this, *p_theZombiePicker, theWave);
							else
							{
								i--;
								bool result = func_list[i](_this, *p_theZombiePicker, theWave, base);
								i++;
								return result;
							}
						};

						return func_list.back()(_this, theZombiePicker, theWave, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicBoard::Binding_MF_ZombiePicker_CalculateBasicPoints(InitPatch& patch, const std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_CalculateBasicPoints_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_ZombiePicker_CalculateBasicPoints", [&]
		{
			static std::vector<std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_CalculateBasicPoints_t& base)>> func_list;
			patch.PatchTask("MagicBoard::Binding_MF_ZombiePicker_CalculateBasicPoints(Hook)", [&]
				{
					_PatchMF_ZombiePicker(patch);
					_ZombiePicker_CalculateBasicPoints = [](Board* _this, ZombiePicker& theZombiePicker, int theWave)
					{
						ZombiePicker_CalculateBasicPoints_t base;
						auto p_theZombiePicker = &theZombiePicker;

						base.mFunction = [&](Board* __this, ZombiePicker& _theZombiePicker, int _theWave)
						{
							auto _p_theZombiePicker = &_theZombiePicker;
							std::swap(_this, __this);
							std::swap(p_theZombiePicker, _p_theZombiePicker);
							base();
							_this = __this;
							p_theZombiePicker = _p_theZombiePicker;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_ZombiePicker_CalculateBasicPoints_base(_this, *p_theZombiePicker, theWave);
							else
							{
								i--;
								func_list[i](_this, *p_theZombiePicker, theWave, base);
								i++;
							}
						};

						func_list.back()(_this, theZombiePicker, theWave, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicBoard::Binding_MF_ZombiePicker_PutBeforeMultiple(InitPatch& patch, const std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutBeforeMultiple_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_ZombiePicker_PutBeforeMultiple", [&]
		{
			static std::vector<std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutBeforeMultiple_t& base)>> func_list;
			patch.PatchTask("MagicBoard::Binding_MF_ZombiePicker_PutBeforeMultiple(Hook)", [&]
				{
					_PatchMF_ZombiePicker(patch);
					_ZombiePicker_PutBeforeMultiple = [](Board* _this, ZombiePicker& theZombiePicker, int theWave)
					{
						ZombiePicker_PutBeforeMultiple_t base;
						auto p_theZombiePicker = &theZombiePicker;

						base.mFunction = [&](Board* __this, ZombiePicker& _theZombiePicker, int _theWave)
						{
							auto _p_theZombiePicker = &_theZombiePicker;
							std::swap(_this, __this);
							std::swap(p_theZombiePicker, _p_theZombiePicker);
							base();
							_this = __this;
							p_theZombiePicker = _p_theZombiePicker;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_ZombiePicker_PutBeforeMultiple_base(_this, *p_theZombiePicker, theWave);
							else
							{
								i--;
								func_list[i](_this, *p_theZombiePicker, theWave, base);
								i++;
							}
						};

						func_list.back()(_this, theZombiePicker, theWave, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicBoard::Binding_MF_ZombiePicker_CalculateMultiplePoints(InitPatch& patch, const std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_CalculateMultiplePoints_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_ZombiePicker_CalculateMultiplePoints", [&]
		{
			static std::vector<std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_CalculateMultiplePoints_t& base)>> func_list;
			patch.PatchTask("MagicBoard::Binding_MF_ZombiePicker_CalculateMultiplePoints(Hook)", [&]
				{
					_PatchMF_ZombiePicker(patch);
					_ZombiePicker_CalculateMultiplePoints = [](Board* _this, ZombiePicker& theZombiePicker, int theWave)
					{
						ZombiePicker_CalculateMultiplePoints_t base;
						auto p_theZombiePicker = &theZombiePicker;

						base.mFunction = [&](Board* __this, ZombiePicker& _theZombiePicker, int _theWave)
						{
							auto _p_theZombiePicker = &_theZombiePicker;
							std::swap(_this, __this);
							std::swap(p_theZombiePicker, _p_theZombiePicker);
							base();
							_this = __this;
							p_theZombiePicker = _p_theZombiePicker;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_ZombiePicker_CalculateMultiplePoints_base(_this, *p_theZombiePicker, theWave);
							else
							{
								i--;
								func_list[i](_this, *p_theZombiePicker, theWave, base);
								i++;
							}
						};

						func_list.back()(_this, theZombiePicker, theWave, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicBoard::Binding_MF_ZombiePicker_PutPreset(InitPatch& patch, const std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutPreset_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_ZombiePicker_PutPreset", [&]
		{
			static std::vector<std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutPreset_t& base)>> func_list;
			patch.PatchTask("MagicBoard::Binding_MF_ZombiePicker_PutPreset(Hook)", [&]
				{
					_PatchMF_ZombiePicker(patch);
					_ZombiePicker_PutPreset = [](Board* _this, ZombiePicker& theZombiePicker, int theWave)
					{
						ZombiePicker_PutPreset_t base;
						auto p_theZombiePicker = &theZombiePicker;

						base.mFunction = [&](Board* __this, ZombiePicker& _theZombiePicker, int _theWave)
						{
							auto _p_theZombiePicker = &_theZombiePicker;
							std::swap(_this, __this);
							std::swap(p_theZombiePicker, _p_theZombiePicker);
							base();
							_this = __this;
							p_theZombiePicker = _p_theZombiePicker;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_ZombiePicker_PutPreset_base(_this, *p_theZombiePicker, theWave);
							else
							{
								i--;
								func_list[i](_this, *p_theZombiePicker, theWave, base);
								i++;
							}
						};

						func_list.back()(_this, theZombiePicker, theWave, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicBoard::Binding_MF_ZombiePicker_PutRandom(InitPatch& patch, const std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutRandom_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_ZombiePicker_PutRandom", [&]
		{
			static std::vector<std::function<void(Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutRandom_t& base)>> func_list;
			patch.PatchTask("MagicBoard::Binding_MF_ZombiePicker_PutRandom(Hook)", [&]
				{
					_PatchMF_ZombiePicker(patch);
					_ZombiePicker_PutRandom = [](Board* _this, ZombiePicker& theZombiePicker, int theWave)
					{
						ZombiePicker_PutRandom_t base;
						auto p_theZombiePicker = &theZombiePicker;

						base.mFunction = [&](Board* __this, ZombiePicker& _theZombiePicker, int _theWave)
						{
							auto _p_theZombiePicker = &_theZombiePicker;
							std::swap(_this, __this);
							std::swap(p_theZombiePicker, _p_theZombiePicker);
							base();
							_this = __this;
							p_theZombiePicker = _p_theZombiePicker;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_ZombiePicker_PutRandom_base(_this, *p_theZombiePicker, theWave);
							else
							{
								i--;
								func_list[i](_this, *p_theZombiePicker, theWave, base);
								i++;
							}
						};

						func_list.back()(_this, theZombiePicker, theWave, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

static SexyString _GetLevelBasicName_base(Board* _this)
{
	if (_this->mApp->IsAdventureMode())
		return _S("[LEVEL]");
	else
	{
		if (_this->mApp->mGameMode < NUM_GAME_MODES)
			return _this->mApp->GetCurrentChallengeDef().mChallengeName;
		else
			return std::format(_S("[LEVEL_NAME_{}]"), (int)_this->mApp->mGameMode);
	}
}

static int _defaultOffsetX = 0, _defaultOffsetY = 0;

int* MagicBoard::mvOffsetXPtr = &_defaultOffsetX, * MagicBoard::mvOffsetYPtr = &_defaultOffsetY;

void MagicBoard::Binding_mvOffset(InitPatch& patch, int* theOffsetXPtr, int* theOffsetYPtr)
{
	patch.PatchTask("MagicBoard::Binding_mvOffset", [&]
		{
			if (theOffsetXPtr != nullptr)
				mvOffsetXPtr = theOffsetXPtr;

			if (theOffsetYPtr != nullptr)
				mvOffsetYPtr = theOffsetYPtr;

			{	// draw
				using Draw_t = void(__fastcall*)(Board* _this, int, Graphics* g);

				Draw_t& draw = *(Draw_t*)0x662fa0;
				static Draw_t drawRaw = draw;

				draw = [](Board* _this, int, Graphics* g)
				{
					g->Translate(*mvOffsetXPtr, *mvOffsetYPtr);
					drawRaw(_this, 0, g);
					g->Translate(-*mvOffsetXPtr, -*mvOffsetYPtr);
				};
			}
			{	// click
				using MouseMove_t = void(__fastcall*)(Board* _this, int, int x, int y);
				using MouseUpDown_t = void(__fastcall*)(Board* _this, int, int x, int y, int theClickCount);

				MouseMove_t& mouseMove = *(MouseMove_t*)0x663008;
				MouseUpDown_t& mouseDown = *(MouseUpDown_t*)0x663010;
				MouseUpDown_t& mouseUp = *(MouseUpDown_t*)0x663018;

				static MouseMove_t mouseMoveRaw = mouseMove;
				static MouseUpDown_t mouseDownRaw = mouseDown;
				static MouseUpDown_t mouseUpRaw = mouseUp;

				mouseMove = [](Board* _this, int, int x, int y)
				{
					mouseMoveRaw(_this, 0, x - *mvOffsetXPtr, y - *mvOffsetYPtr);
				};

				mouseDown = [](Board* _this, int, int x, int y, int theClickCount)
				{
					mouseDownRaw(_this, 0, x - *mvOffsetXPtr, y - *mvOffsetYPtr, theClickCount);
				};

				mouseUp = [](Board* _this, int, int x, int y, int theClickCount)
				{
					mouseUpRaw(_this, 0, x - *mvOffsetXPtr, y - *mvOffsetYPtr, theClickCount);
				};
			}

			GameObjectPatch::FixBoardToolTipPos(patch);
			GameObjectPatch::FixBoardCursorPos(patch);
			GameObjectPatch::FixBoardHighlightPos(patch);
			GameObjectPatch::FixCursorPreviewPos(patch);
			GameObjectPatch::FixCursorObjectPos(patch);
			WidgetPatch::FixGameButtonClickPos(patch);

		}, true, true);
}
