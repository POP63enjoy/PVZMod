#include "PVZMod.h"
#include "Board.h"
#include "LawnApp.h"
#include "MagicBoard.h"
#include "MagicBoard_private.h"
#include "MagicLawnApp_private.h"
#include "TodCommon.h"
#include "Challenge.h"
#include "Graphics.h"
#include "GameObjectPatch.h"
#include "WidgetPatch.h"
#include "TodStringFile.h"
#include "ChallengeScreen.h"
#include "SaveGame.h"
#include "EffectSystem.h"
#include "Reanimator.h"
#include "TodParticle.h"
#include "Trail.h"
#include "CursorObject.h"
#include "CursorPreview.h"
#include "MessageWidget.h"
#include "SeedPacket.h"
#include "Music.h"
#include "Res.h"
#include <format>

using namespace PVZMod;

// 基本信息绑定

void MagicBoard::Binding_ExtendBase(InitPatch& patch, size_t theBoardSize, bool autoSaveExtendedData)
{
	patch.PatchTask("MagicBoard::Binding_ExtendBase", [&]
		{
			*(int*)0x45243f = theBoardSize;

			if (autoSaveExtendedData)
				*(int*)0x485711 += theBoardSize - sizeof(Board);
		}, true, true);
}

// 构造函数和析构函数 - MF_Constructor、MF_Destructor

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


// 关卡信息初始化 - MF_InitLevel

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


// 释放资源 - MF_DisposeBoard

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
					_DisposeBoard_raw_addr = patch.mHook.HookFunction((void*)0x409f80, &_DisposeBoard_naked_detour);
				});
			func_list.push_back(func);
		}, false);
}


// 关卡存读档 - MF_Sync、MF_FixAfterLoad

static void _Sync_SyncData_base(Board* _this, SaveGameContext& theContext)
{
	theContext.SyncBytes(&_this->mPaused, sizeof(Board) - offsetof(Board, mPaused));
}

static auto _Sync_SyncData = _Sync_SyncData_base;

static void _Sync_SyncDataArray_base(Board* _this, SaveGameContext& theContext)
{
	int func01 = 0x485F60;
	int func02 = 0x486050;
	int func03 = 0x486140;
	int func04 = 0x486230;
	int func05 = 0x486320;
	int func06 = 0x486420;
	int func07 = 0x486510;
	int func08 = 0x486600;
	int func09 = 0x4866F0;
	int func10 = 0x4866F0;
	int func11 = 0x486420;
	int func12 = 0x4867E0;

	__asm
	{
		mov esi, _this
		mov ebx, theContext
		lea eax, dword ptr ss : [esi + 0x90]
		push eax
		mov eax, ebx
		call func01
		lea ecx, dword ptr ss : [esi + 0xAC]
		add esp, 0x4
		push ecx
		mov eax, ebx
		call func02
		lea edx, dword ptr ss : [esi + 0xC8]
		add esp, 0x4
		push edx
		mov eax, ebx
		call func03
		lea eax, dword ptr ss : [esi + 0xE4]
		add esp, 0x4
		push eax
		mov eax, ebx
		call func04
		lea ecx, dword ptr ss : [esi + 0x100]
		add esp, 0x4
		push ecx
		mov eax, ebx
		call func05
		lea edx, dword ptr ss : [esi + 0x11C]
		add esp, 0x4
		push edx
		mov eax, ebx
		call func06
		mov eax, dword ptr ss : [esi + 0x8C]
		mov ecx, dword ptr ds : [eax + 0x820]
		mov edx, dword ptr ds : [ecx]
		add esp, 0x4
		push edx
		mov eax, ebx
		call func07
		mov eax, dword ptr ss : [esi + 0x8C]
		mov ecx, dword ptr ds : [eax + 0x820]
		mov edx, dword ptr ds : [ecx]
		add edx, 0x1C
		add esp, 0x4
		push edx
		mov eax, ebx
		call func08
		mov eax, dword ptr ss : [esi + 0x8C]
		mov ecx, dword ptr ds : [eax + 0x820]
		mov edx, dword ptr ds : [ecx]
		add edx, 0x38
		add esp, 0x4
		push edx
		mov eax, ebx
		call func09
		mov eax, dword ptr ss : [esi + 0x8C]
		mov ecx, dword ptr ds : [eax + 0x820]
		mov edx, dword ptr ds : [ecx + 0x8]
		add esp, 0x4
		push edx
		mov eax, ebx
		call func10
		mov eax, dword ptr ss : [esi + 0x8C]
		mov ecx, dword ptr ds : [eax + 0x820]
		mov edx, dword ptr ds : [ecx + 0x4]
		add esp, 0x4
		push edx
		mov eax, ebx
		call func11
		mov eax, dword ptr ss : [esi + 0x8C]
		mov ecx, dword ptr ds : [eax + 0x820]
		mov edx, dword ptr ds : [ecx + 0xC]
		add esp, 0x4
		push edx
		mov eax, ebx
		call func12
		add esp, 0x4
	}
}

static auto _Sync_SyncDataArray = _Sync_SyncDataArray_base;

static void _Sync_SyncDataArrayObject_base(Board* _this, SaveGameContext& theContext)
{
	TodParticleSystem* aParticle = nullptr;
	while (_this->mApp->mEffectSystem->mParticleHolder->mParticleSystems.IterateNext(aParticle))
		SyncParticleSystem(_this, aParticle, theContext);
	
	Reanimation* aReanimation = nullptr;
	while (_this->mApp->mEffectSystem->mReanimationHolder->mReanimations.IterateNext(aReanimation))
		SyncReanimation(_this, aReanimation, theContext);
	
	Trail* aTrail = nullptr;
	while (_this->mApp->mEffectSystem->mTrailHolder->mTrails.IterateNext(aTrail))
		SyncTrail(_this, aTrail, theContext);
}

static auto _Sync_SyncDataArrayObject = _Sync_SyncDataArrayObject_base;

static void _Sync_SyncOtherObject_base(Board* _this, SaveGameContext& theContext)
{
	theContext.SyncBytes(_this->mCursorObject, sizeof(CursorObject));
	theContext.SyncBytes(_this->mCursorPreview, sizeof(CursorPreview));
	theContext.SyncBytes(_this->mAdvice, sizeof(MessageWidget));
	theContext.SyncBytes(_this->mSeedBank, sizeof(SeedBank));
	theContext.SyncBytes(_this->mChallenge, sizeof(Challenge));
	theContext.SyncBytes(_this->mApp->mMusic, sizeof(Music));
}

static auto _Sync_SyncOtherObject = _Sync_SyncOtherObject_base;

static void _Sync_SyncOther_base(Board* _this, SaveGameContext& theContext)
{
	constexpr long SAVE_FILE_MAGIC_NUMBER = 0xFEEDDEAD;

	if (theContext.mReading)
	{
		if (theContext.ByteLeftToRead() < 4)
			theContext.mFailed = true;

		if (theContext.mFailed || theContext.mBuffer.ReadLong() != SAVE_FILE_MAGIC_NUMBER)
			theContext.mFailed = true;
	}
	else
		theContext.mBuffer.WriteLong(SAVE_FILE_MAGIC_NUMBER);
}

static auto _Sync_SyncOther = _Sync_SyncOther_base;

static void _PatchMF_Sync(InitPatch& patch)
{
	patch.PatchTask("_PatchMF_Sync", [&]
		{
			patch.mHook.InsertCodeAndJump((void*)0x485700, (void*)0x485a0b, [](Hook::Regs* regs)
				{
					auto _this = *(Board**)(regs->esp + 0x4);
					auto& theContext = *(SaveGameContext*)(regs->eax);
					_Sync_SyncData(_this, theContext);
					_Sync_SyncDataArray(_this, theContext);
					_Sync_SyncDataArrayObject(_this, theContext);
					_Sync_SyncOtherObject(_this, theContext);
					_Sync_SyncOther(_this, theContext);
				});
		});
}

void MagicBoard::Binding_MF_Sync_SyncData(InitPatch& patch, const std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncData_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_Sync_SyncData", [&]
		{
			static std::vector<std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncData_t& base)>> func_list;
			_PatchMF_Sync(patch);
			patch.PatchTask("MagicBoard::Binding_MF_Sync_SyncData(Hook)", [&]
				{
					_Sync_SyncData = [](Board* _this, SaveGameContext& theContext)
					{
						Sync_SyncData_t base;
						auto p_theContext = &theContext;

						base.mFunction = [&](Board* __this, SaveGameContext& _theContext)
						{
							auto _p_theContext = &_theContext;
							std::swap(_this, __this);
							std::swap(p_theContext, _p_theContext);
							base();
							_this = __this;
							p_theContext = _p_theContext;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_Sync_SyncData_base(_this, *p_theContext);
							else
							{
								i--;
								func_list[i](_this, *p_theContext, base);
								i++;
							}
						};

						func_list.back()(_this, theContext, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicBoard::Binding_MF_Sync_SyncDataArray(InitPatch& patch, const std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncDataArray_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_Sync_SyncDataArray", [&]
		{
			static std::vector<std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncDataArray_t& base)>> func_list;
			_PatchMF_Sync(patch);
			patch.PatchTask("MagicBoard::Binding_MF_Sync_SyncDataArray(Hook)", [&]
				{
					_Sync_SyncDataArray = [](Board* _this, SaveGameContext& theContext)
					{
						Sync_SyncDataArray_t base;
						auto p_theContext = &theContext;

						base.mFunction = [&](Board* __this, SaveGameContext& _theContext)
						{
							auto _p_theContext = &_theContext;
							std::swap(_this, __this);
							std::swap(p_theContext, _p_theContext);
							base();
							_this = __this;
							p_theContext = _p_theContext;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_Sync_SyncDataArray_base(_this, *p_theContext);
							else
							{
								i--;
								func_list[i](_this, *p_theContext, base);
								i++;
							}
						};

						func_list.back()(_this, theContext, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicBoard::Binding_MF_Sync_SyncDataArrayObject(InitPatch& patch, const std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncDataArrayObject_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_Sync_SyncDataArrayObject", [&]
		{
			static std::vector<std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncDataArrayObject_t& base)>> func_list;
			_PatchMF_Sync(patch);
			patch.PatchTask("MagicBoard::Binding_MF_Sync_SyncDataArrayObject(Hook)", [&]
				{
					_Sync_SyncDataArrayObject = [](Board* _this, SaveGameContext& theContext)
					{
						Sync_SyncDataArrayObject_t base;
						auto p_theContext = &theContext;

						base.mFunction = [&](Board* __this, SaveGameContext& _theContext)
						{
							auto _p_theContext = &_theContext;
							std::swap(_this, __this);
							std::swap(p_theContext, _p_theContext);
							base();
							_this = __this;
							p_theContext = _p_theContext;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_Sync_SyncDataArrayObject_base(_this, *p_theContext);
							else
							{
								i--;
								func_list[i](_this, *p_theContext, base);
								i++;
							}
						};

						func_list.back()(_this, theContext, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicBoard::Binding_MF_Sync_SyncOtherObject(InitPatch& patch, const std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncOtherObject_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_Sync_SyncOtherObject", [&]
		{
			static std::vector<std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncOtherObject_t& base)>> func_list;
			_PatchMF_Sync(patch);
			patch.PatchTask("MagicBoard::Binding_MF_Sync_SyncOtherObject(Hook)", [&]
				{
					_Sync_SyncOtherObject = [](Board* _this, SaveGameContext& theContext)
					{
						Sync_SyncOtherObject_t base;
						auto p_theContext = &theContext;

						base.mFunction = [&](Board* __this, SaveGameContext& _theContext)
						{
							auto _p_theContext = &_theContext;
							std::swap(_this, __this);
							std::swap(p_theContext, _p_theContext);
							base();
							_this = __this;
							p_theContext = _p_theContext;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_Sync_SyncOtherObject_base(_this, *p_theContext);
							else
							{
								i--;
								func_list[i](_this, *p_theContext, base);
								i++;
							}
						};

						func_list.back()(_this, theContext, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

void MagicBoard::Binding_MF_Sync_SyncOther(InitPatch& patch, const std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncOther_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_Sync_SyncOther", [&]
		{
			static std::vector<std::function<void(Board* _this, SaveGameContext& theContext, Sync_SyncOther_t& base)>> func_list;
			_PatchMF_Sync(patch);
			patch.PatchTask("MagicBoard::Binding_MF_Sync_SyncOther(Hook)", [&]
				{
					_Sync_SyncOther = [](Board* _this, SaveGameContext& theContext)
					{
						Sync_SyncOther_t base;
						auto p_theContext = &theContext;

						base.mFunction = [&](Board* __this, SaveGameContext& _theContext)
						{
							auto _p_theContext = &_theContext;
							std::swap(_this, __this);
							std::swap(p_theContext, _p_theContext);
							base();
							_this = __this;
							p_theContext = _p_theContext;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_Sync_SyncOther_base(_this, *p_theContext);
							else
							{
								i--;
								func_list[i](_this, *p_theContext, base);
								i++;
							}
						};

						func_list.back()(_this, theContext, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

static void(__stdcall* _FixAfterLoad_detour)(Board* _this);
static void* _FixAfterLoad_raw_addr;

static void __declspec(naked) _FixAfterLoad_naked_detour()
{
	__asm
	{
		push edi
		call _FixAfterLoad_detour
		ret
	}
}
static void _FixAfterLoad_raw(Board* _this)
{
	__asm
	{
		mov edi, _this
		call _FixAfterLoad_raw_addr
	}
}

void MagicBoard::Binding_MF_FixAfterLoad(InitPatch& patch, const std::function<void(Board* _this, FixAfterLoad_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_FixAfterLoad", [&]
		{
			static std::vector<std::function<void(Board* _this, FixAfterLoad_t& base)>> func_list;
			patch.PatchTask("MagicBoard::Binding_MF_FixAfterLoad(Hook)", [&]
				{
					_FixAfterLoad_detour = [](Board* _this)
					{
						FixAfterLoad_t base;

						base.mFunction = [&](Board* __this)
						{
							std::swap(_this, __this);
							base();
							_this = __this;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_FixAfterLoad_raw(_this);
							else
							{
								i--;
								func_list[i](_this, base);
								i++;
							}
						};

						func_list.back()(_this, base);
					};
					_FixAfterLoad_raw_addr = patch.mHook.HookFunction((void*)0x485a10, &_FixAfterLoad_naked_detour);
				});
			func_list.push_back(func);
		}, false);
}


// 出怪计算 - MF_ZombiePicker

static void _ZombiePicker_CalculateNumWaves_base(Board* _this)
{
	if (_this->mApp->IsAdventureMode())
	{
		if (_this->mApp->IsWhackAZombieLevel())
			_this->mNumWaves = 8;
		else
		{
			_this->mNumWaves = gZombieWaves[ClampInt(_this->mLevel - 1, 0, 49)];

			if (!_this->mApp->IsFirstTimeAdventureMode() && !_this->mApp->IsMiniBossLevel())
				_this->mNumWaves = _this->mNumWaves < 10 ? 20 : _this->mNumWaves + 10;
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
		aZombiePoints = (_this->mChallenge->mSurvivalStage * _this->GetNumWavesPerSurvivalStage() + theWave + 10) * 2 / 5 + 1;
	else if (_this->mApp->IsSurvivalMode() && _this->mChallenge->mSurvivalStage > 0)
		aZombiePoints = (_this->mChallenge->mSurvivalStage * _this->GetNumWavesPerSurvivalStage() + theWave) * 2 / 5 + 1;
	else if (_this->mApp->IsAdventureMode() && _this->mApp->HasFinishedAdventure() && _this->mLevel != 5)
		aZombiePoints = theWave * 2 / 5 + 1;
	else
		aZombiePoints = theWave / 3 + 1;
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
				_this->PutZombieInWave(ZOMBIE_NORMAL, theWave, &theZombiePicker);
			_this->PutZombieInWave(ZOMBIE_FLAG, theWave, &theZombiePicker);
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

	if (aIntroZombieType != ZOMBIE_INVALID && aIntroZombieType != ZOMBIE_DUCKY_TUBE)
	{
		bool aSpawnIntro = false;
		if ((aIntroZombieType == ZOMBIE_DIGGER || aIntroZombieType == ZOMBIE_BALLOON))
		{
			if (theWave + 1 == 7 || aIsFinalWave)
				aSpawnIntro = true;
		}
		else if (aIntroZombieType == ZOMBIE_YETI)
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
		_this->PutZombieInWave(ZOMBIE_GARGANTUAR, theWave, &theZombiePicker);

	// 冒险模式关卡的最后一波会出现本关卡可能出现的所有僵尸
	if (_this->mApp->IsAdventureMode() && aIsFinalWave)
		_this->PutInMissingZombies(theWave, &theZombiePicker);

	// 柱子关卡的特殊出怪
	if (_this->mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_COLUMN)
	{
		// 每大波的第 5 小波，固定出现 10 只扶梯僵尸
		if (theWave % 10 == 5)
			for (int _i = 0; _i < 10; _i++)
				_this->PutZombieInWave(ZOMBIE_LADDER, theWave, &theZombiePicker);

		// 每大波的第 8 小波，固定出现 10 只玩偶匣僵尸
		if (theWave % 10 == 8)
			for (int _i = 0; _i < 10; _i++)
				_this->PutZombieInWave(ZOMBIE_JACK_IN_THE_BOX, theWave, &theZombiePicker);

		// 第 19/29 小波，固定出现 3/5 只伽刚特尔
		if (theWave == 19)
			for (int _i = 0; _i < 3; _i++)
				_this->PutZombieInWave(ZOMBIE_GARGANTUAR, theWave, &theZombiePicker);
		if (theWave == 29)
			for (int _i = 0; _i < 5; _i++)
				_this->PutZombieInWave(ZOMBIE_GARGANTUAR, theWave, &theZombiePicker);
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
							std::swap(theWave, _theWave);
							bool result = base();
							_this = __this;
							p_theZombiePicker = _p_theZombiePicker;
							theWave = _theWave;
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
							std::swap(theWave, _theWave);
							base();
							_this = __this;
							p_theZombiePicker = _p_theZombiePicker;
							theWave = _theWave;
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
							std::swap(theWave, _theWave);
							base();
							_this = __this;
							p_theZombiePicker = _p_theZombiePicker;
							theWave = _theWave;
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
							std::swap(theWave, _theWave);
							base();
							_this = __this;
							p_theZombiePicker = _p_theZombiePicker;
							theWave = _theWave;
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
							std::swap(theWave, _theWave);
							base();
							_this = __this;
							p_theZombiePicker = _p_theZombiePicker;
							theWave = _theWave;
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
							std::swap(theWave, _theWave);
							base();
							_this = __this;
							p_theZombiePicker = _p_theZombiePicker;
							theWave = _theWave;
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

// 静态关卡名称 - MC_LEVEL_NAME

static std::map<GameMode, const SexyChar*> _levelNameMap;

void MagicBoard::Binding_MC_LEVEL_NAME(InitPatch& patch, GameMode theLevelId, const SexyChar* theLevelName)
{
	patch.PatchTask("MagicBoard::Binding_MC_LEVEL_NAME", [&]
		{
			_levelNameMap[theLevelId] = theLevelName;
		}, false);
}

// 动态关卡名称 - mvUseDynLevelName、mvDynLevelName

static bool defaultUseDynLevelNamePtr = false;

bool* __MAGIC_BOARD_PRIVATE__::mvUseDynLevelNamePtr = &defaultUseDynLevelNamePtr;
SexyString* __MAGIC_BOARD_PRIVATE__::mvDynLevelNamePtr;

void MagicBoard::Binding_mvDynLevelName(InitPatch& patch, bool* theUseDynLevelNamePtr, SexyString* theDynLevelNamePtr)
{
	assert(theUseDynLevelNamePtr);
	assert(theDynLevelNamePtr);

	patch.PatchTask("MagicBoard::Binding_mvDynLevelName", [&]
		{
			using namespace __MAGIC_BOARD_PRIVATE__;

			mvUseDynLevelNamePtr = theUseDynLevelNamePtr;
			mvDynLevelNamePtr = theDynLevelNamePtr;
		}, true, true);
}

// 绘制关卡名称 - MF_DrawLevel

void _DrawLevel_GetPos_base(Board* _this, Graphics* g, const SexyString& theLevelName, int& thePosX, int& thePosY, DrawStringJustification& theJustification)
{
	thePosX = 780;
	thePosY = 595;

	if (_this->HasProgressMeter())
		thePosX = 593;

	if (_this->mChallenge->mChallengeState == STATECHALLENGE_ZEN_FADING)
		thePosY += TodAnimateCurve(50, 0, _this->mChallenge->mChallengeStateCounter, 0, 50, CURVE_EASE_IN_OUT);

	theJustification = DS_ALIGN_RIGHT;
}

auto _DrawLevel_GetPos = _DrawLevel_GetPos_base;

void _DrawLevel_base(Board* _this, Graphics* g, const SexyString& theLevelName, int thePosX, int thePosY, DrawStringJustification theJustification, Font* theFont, const Color& theColor)
{
	TodDrawString(g, theLevelName, thePosX, thePosY, theFont, theColor, theJustification);
}

auto _DrawLevel = _DrawLevel_base;

void _PatchMF_DrawLevel(InitPatch& patch)
{
	patch.PatchTask("_PatchMF_DrawLevel", [&]
		{
			using DrawLevel_t = void(__stdcall*)(Board* _this, Graphics* g);
			DrawLevel_t drawLevel = [](Board* _this, Graphics* g)
			{
				using namespace __MAGIC_BOARD_PRIVATE__;

				SexyString levelName;

				if (*mvUseDynLevelNamePtr)
					levelName = TodStringTranslate(*mvDynLevelNamePtr);
				else if (auto iter = _levelNameMap.find(_this->mApp->mGameMode); iter != _levelNameMap.end())
					levelName = TodStringTranslate(iter->second);
				else
					levelName = __MAGIC_LAWNAPP_PRIVATE__::GetAppLevelName(_this->mApp, _this->mApp->mGameMode, [&]
						{
							SexyString aLevelStr;
							if (_this->mApp->IsAdventureMode())
								aLevelStr = TodStringTranslate(_S("[LEVEL]")) + _S(" ") + _this->mApp->GetStageString(_this->mLevel);
							else if ((uintptr_t)_this->mApp->mGameMode < NUM_GAME_MODES)
							{
								aLevelStr = StringToSexyString(_this->mApp->GetCurrentChallengeDef().mChallengeName);
								if (_this->mApp->IsSurvivalMode() || _this->mApp->mGameMode == GAMEMODE_CHALLENGE_LAST_STAND)
								{
									int aFlags = _this->GetSurvivalFlagsCompleted();
									if (aFlags > 0)
									{
										SexyString aFlagStr = LawnApp::Pluralize(aFlags, _S("[ONE_FLAG]"), _S("[COUNT_FLAGS]"));
										SexyString aCompletedStr = TodReplaceString(_S("[FLAGS_COMPLETED]"), _S("{FLAGS}"), aFlagStr);
										aLevelStr = StrFormat(_S("%s - %s"), TodStringTranslate(aLevelStr).c_str(), aCompletedStr.c_str());
									}
								}
								else if (_this->mApp->IsEndlessIZombie(_this->mApp->mGameMode) || _this->mApp->IsEndlessScaryPotter(_this->mApp->mGameMode))
								{
									int aStreak = _this->mChallenge->mSurvivalStage;

									if (_this->mNextSurvivalStageCounter > 0)
										aStreak++;

									if (aStreak > 0)
									{
										SexyString aStreakStr = TodReplaceNumberString(_S("[ENDLESS_STREAK]"), _S("{STREAK}"), aStreak);
										aLevelStr = StrFormat(_S("%s - %s"), TodStringTranslate(aLevelStr).c_str(), aStreakStr.c_str());
									}
								}
							}
							else
								aLevelStr = TodStringTranslate(std::format(_S("[LEVEL_NAME_{}]"), (uintptr_t)_this->mApp->mGameMode));
							return aLevelStr;
						});

				int aPosX = 780, aPosY = 595;

				if (_this->HasProgressMeter())
					aPosX = 593;
				if (_this->mChallenge->mChallengeState == STATECHALLENGE_ZEN_FADING)
					aPosY += TodAnimateCurve(50, 0, _this->mChallenge->mChallengeStateCounter, 0, 50, CURVE_EASE_IN_OUT);

				_DrawLevel(_this, g, levelName, aPosX, aPosY, DS_ALIGN_RIGHT, FONT_HOUSEOFTERROR16, Color(224, 187, 98));
			};
			patch.mHook.HookFunction((void*)0x419340, drawLevel);
		});
}

void MagicBoard::Binding_MF_DrawLevel(InitPatch& patch, const std::function<void(Board* _this, Graphics* g, const SexyString& theLevelName, int thePosX, int thePosY, DrawStringJustification theJustification, Font* theFont, const Color& theColor, DrawLevel_t& base)>& func)
{
	patch.PatchTask("MagicBoard::Binding_MF_DrawLevel", [&]
		{
			static std::vector<std::function<void(Board* _this, Graphics* g, const SexyString& theLevelName, int thePosX, int thePosY, DrawStringJustification theJustification, Font* theFont, const Color& theColor, DrawLevel_t& base)>> func_list;
			patch.PatchTask("MagicBoard::Binding_MF_DrawLevel(Hook)", [&]
				{
					_DrawLevel = [](Board* _this, Graphics* g, const SexyString& theLevelName, int thePosX, int thePosY, DrawStringJustification theJustification, Font* theFont, const Color& theColor)
					{
						DrawLevel_t base;
						auto p_theLevelName = &theLevelName;
						auto p_theColor = &theColor;

						base.mFunction = [&](Board* __this, Graphics* _g, const SexyString& _theLevelName, int _thePosX, int _thePosY, DrawStringJustification _theJustification, Font* _theFont, const Color& _theColor)
						{
							auto _p_theLevelName = &_theLevelName;
							auto _p_theColor = &_theColor;
							std::swap(_this, __this);
							std::swap(g, _g);
							std::swap(p_theLevelName, _p_theLevelName);
							std::swap(thePosX, _thePosX);
							std::swap(thePosY, _thePosY);
							std::swap(theJustification, _theJustification);
							std::swap(theFont, _theFont);
							std::swap(p_theColor, _p_theColor);
							base();
							_this = __this;
							g = _g;
							p_theLevelName = _p_theLevelName;
							thePosX = _thePosX;
							thePosY = _thePosY;
							theJustification = _theJustification;
							theFont = _theFont;
							p_theColor = _p_theColor;
						};
						base.mDefaultFunction = [&, i = func_list.size() - 1]() mutable
						{
							if (i == 0)
								_DrawLevel_base(_this, g, *p_theLevelName, thePosX, thePosY, theJustification, theFont, *p_theColor);
							else
							{
								i--;
								func_list[i](_this, g, *p_theLevelName, thePosX, thePosY, theJustification, theFont, *p_theColor, base);
								i++;
							}
						};

						func_list.back()(_this, g, *p_theLevelName, thePosX, thePosY, theJustification, theFont, theColor, base);
					};
				});
			func_list.push_back(func);
		}, false);
}

// 画面偏移 - mvOffsetX、mvOffsetY

static int _defaultOffsetX = 0, _defaultOffsetY = 0;

int* __MAGIC_BOARD_PRIVATE__::mvOffsetXPtr = &_defaultOffsetX, * __MAGIC_BOARD_PRIVATE__::mvOffsetYPtr = &_defaultOffsetY;

void MagicBoard::Binding_mvOffset(InitPatch& patch, int* theOffsetXPtr, int* theOffsetYPtr)
{
	patch.PatchTask("MagicBoard::Binding_mvOffset", [&]
		{
			using namespace __MAGIC_BOARD_PRIVATE__;

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


// private

void __MAGIC_BOARD_PRIVATE__::LevelNamePatch(InitPatch& patch)
{
	patch.PatchTask("__MAGIC_BOARD_PRIVATE__::LevelNamePatch", [&]
		{
			_PatchMF_DrawLevel(patch);

			patch.mHook.InsertCode((void*)0x409130, [](Hook::Regs* regs)
				{
					*mvUseDynLevelNamePtr = false;
				});
		});
}