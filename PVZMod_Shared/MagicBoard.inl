#pragma once
#ifndef _PVZMOD_MAGIC_BOARD_INL_
#define _PVZMOD_MAGIC_BOARD_INL_

#include "LawnApp.h"

namespace PVZMod
{
	namespace MagicBoard
	{
		namespace __PRIVATE__
		{
			PVZMOD_CHECK_MAGIC_FUNC(MF_Constructor);
			PVZMOD_CHECK_MAGIC_FUNC(MF_Destructor);

			PVZMOD_CHECK_MAGIC_FUNC(MF_InitLevel);
			PVZMOD_CHECK_MAGIC_FUNC(MF_DisposeBoard);

			PVZMOD_CHECK_MAGIC_FUNC(MF_Sync_SyncData);
			PVZMOD_CHECK_MAGIC_FUNC(MF_Sync_SyncDataArray);
			PVZMOD_CHECK_MAGIC_FUNC(MF_Sync_SyncDataArrayObject);
			PVZMOD_CHECK_MAGIC_FUNC(MF_Sync_SyncOtherObject);
			PVZMOD_CHECK_MAGIC_FUNC(MF_Sync_SyncOther);
			PVZMOD_CHECK_MAGIC_FUNC(MF_FixAfterLoad);

			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombiePicker_CalculateNumWaves);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombiePicker_SpecialLevelPut);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombiePicker_CalculateBasicPoints);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombiePicker_PutBeforeMultiple);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombiePicker_CalculateMultiplePoints);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombiePicker_PutPreset);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombiePicker_PutRandom);

			PVZMOD_CHECK_MAGIC_VAR(MC_LEVEL_NAME);

			PVZMOD_CHECK_MAGIC_VAR(mvUseDynLevelName);
			PVZMOD_CHECK_MAGIC_VAR(mvDynLevelName);

			PVZMOD_CHECK_MAGIC_FUNC(MF_DrawLevel);

			PVZMOD_CHECK_MAGIC_VAR(mvOffsetX);
			PVZMOD_CHECK_MAGIC_VAR(mvOffsetY);
		}

		template <typename T>
		RegisterManager<T> RegisterMain(InitPatch& patch)
		{
			static_assert(std::is_base_of<Board, T>::value, "MagicBoard::RegisterMain: T must based on Board.");

			patch.PatchTask("MagicBoard::RegisterMain", [&]
				{
					using namespace __PRIVATE__;

					Binding_ExtendBase(patch, sizeof(T), true);

					PVZMOD_GENERAL_MAGIC_FUNC(MF_Constructor, void(LawnApp* theApp, Constructor_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_Destructor, void(Destructor_t& base), T);

					PVZMOD_GENERAL_MAGIC_FUNC(MF_InitLevel, void(InitLevel_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_DisposeBoard, void(DisposeBoard_t& base), T);

					PVZMOD_GENERAL_MAGIC_FUNC(MF_Sync_SyncData, void(SaveGameContext& theContext, Sync_SyncData_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_Sync_SyncDataArray, void(SaveGameContext& theContext, Sync_SyncDataArray_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_Sync_SyncDataArrayObject, void(SaveGameContext& theContext, Sync_SyncDataArrayObject_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_Sync_SyncOtherObject, void(SaveGameContext& theContext, Sync_SyncOtherObject_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_Sync_SyncOther, void(SaveGameContext& theContext, Sync_SyncOther_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_FixAfterLoad, void(FixAfterLoad_t& base), T);

					PVZMOD_GENERAL_MAGIC_FUNC(MF_ZombiePicker_CalculateNumWaves, void(ZombiePicker_CalculateNumWaves_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_ZombiePicker_SpecialLevelPut, bool(ZombiePicker& theZombiePicker, int theWave, ZombiePicker_SpecialLevelPut_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_ZombiePicker_CalculateBasicPoints, void(ZombiePicker& theZombiePicker, int theWave, ZombiePicker_CalculateBasicPoints_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_ZombiePicker_PutBeforeMultiple, void(ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutBeforeMultiple_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_ZombiePicker_CalculateMultiplePoints, void(ZombiePicker& theZombiePicker, int theWave, ZombiePicker_CalculateMultiplePoints_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_ZombiePicker_PutPreset, void(ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutPreset_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_ZombiePicker_PutRandom, void(ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutRandom_t& base), T);

					{
						bool* mvUseDynLevelNamePtr = nullptr;
						SexyString* mvDynLevelNamePtr = nullptr;

						PVZMOD_IF_MAGIC_SVAR_EXIST(mvUseDynLevelName, bool, T, { mvUseDynLevelNamePtr = &T::mvUseDynLevelName; });
						PVZMOD_IF_MAGIC_SVAR_EXIST(mvDynLevelName, SexyString, T, { mvDynLevelNamePtr = &T::mvDynLevelName; });

						static_assert((CheckV_mvUseDynLevelName<T, bool>::value == Magic::NOT_EXIST) == (CheckV_mvDynLevelName<T, bool>::value == Magic::NOT_EXIST), "\"mvUseDynLevelNamePtr\" and \"mvDynLevelNamePtr\" must both be defined.");
						
						if (mvUseDynLevelNamePtr != nullptr && mvDynLevelNamePtr != nullptr)
							Binding_mvDynLevelName(patch, mvUseDynLevelNamePtr, mvDynLevelNamePtr);
					}

					PVZMOD_GENERAL_MAGIC_FUNC(MF_DrawLevel, void(Graphics* g, const SexyString& theLevelName, int thePosX, int thePosY, DrawStringJustification theJustification, Font* theFont, const Color& theColor, DrawLevel_t& base), T);

					{
						int* xPtr = nullptr, * yPtr = nullptr;
						PVZMOD_IF_MAGIC_SVAR_EXIST(mvOffsetX, int, T, { xPtr = &T::mvOffsetX; });
						PVZMOD_IF_MAGIC_SVAR_EXIST(mvOffsetY, int, T, { yPtr = &T::mvOffsetY; });
						if (xPtr != nullptr || yPtr != nullptr)
							Binding_mvOffset(patch, xPtr, yPtr);
					}
				}, true, true);
			return {};
		}

		template <typename BaseClass>
		template <typename LevelClass>
		RegisterManager<BaseClass> RegisterManager<BaseClass>::RegisterLevel(InitPatch& patch, GameMode theLevelId, bool enableMultipleRegister)
		{
			static_assert(std::is_base_of<BaseClass, LevelClass>::value,	"MagicBoard::RegisterManager::RegisterLevel: LevelClass must based on BaseClass.");
			static_assert(sizeof(BaseClass) == sizeof(LevelClass),			"MagicBoard::RegisterManager::RegisterLevel: Do not define non-static member variables in LevelClass.");

			enableMultipleRegister |= Magic::IsEnableMultiReg<LevelClass>();

			patch.PatchTask("MagicBoard::RegisterManager::RegisterLevel(" + std::to_string(theLevelId) + "," + std::to_string(typeid(LevelClass).hash_code()) + ")", [&]
				{
					using namespace __PRIVATE__;

					Magic::IterateRef<LevelClass>([&] <typename T>
					{
						RegisterLevel<T>(patch, theLevelId);
					});

					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_Constructor, void(LawnApp* theApp, Constructor_t& base), LevelClass, BaseClass, theLevelId, PVZMOD_ARG(0)->mGameMode == theLevelId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_Destructor, void(Destructor_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);

					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_InitLevel, void(InitLevel_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_DisposeBoard, void(DisposeBoard_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);

					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_Sync_SyncData, void(SaveGameContext& theContext, Sync_SyncData_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_Sync_SyncDataArray, void(SaveGameContext& theContext, Sync_SyncDataArray_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_Sync_SyncDataArrayObject, void(SaveGameContext& theContext, Sync_SyncDataArrayObject_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_Sync_SyncOtherObject, void(SaveGameContext& theContext, Sync_SyncOtherObject_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_Sync_SyncOther, void(SaveGameContext& theContext, Sync_SyncOther_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_FixAfterLoad, void(FixAfterLoad_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);

					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_ZombiePicker_CalculateNumWaves, void(ZombiePicker_CalculateNumWaves_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_ZombiePicker_SpecialLevelPut, bool(ZombiePicker& theZombiePicker, int theWave, ZombiePicker_SpecialLevelPut_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_ZombiePicker_CalculateBasicPoints, void(ZombiePicker& theZombiePicker, int theWave, ZombiePicker_CalculateBasicPoints_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_ZombiePicker_PutBeforeMultiple, void(ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutBeforeMultiple_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_ZombiePicker_CalculateMultiplePoints, void(ZombiePicker& theZombiePicker, int theWave, ZombiePicker_CalculateMultiplePoints_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_ZombiePicker_PutPreset, void(ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutPreset_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_ZombiePicker_PutRandom, void(ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutRandom_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);

					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_DrawLevel, void(Graphics* g, const SexyString& theLevelName, int thePosX, int thePosY, DrawStringJustification theJustification, Font* theFont, const Color& theColor, DrawLevel_t& base), LevelClass, BaseClass, theLevelId, _this->mApp->mGameMode == theLevelId);

					PVZMOD_IF_MAGIC_SVAR_EXIST(MC_LEVEL_NAME, const SexyChar* const, LevelClass,
						{
							Binding_MC_LEVEL_NAME(patch, theLevelId, LevelClass::MC_LEVEL_NAME);
						});
				}, !enableMultipleRegister);
			return {};
		}
	}
}

#endif // !_PVZMOD_MAGIC_BOARD_INL_
