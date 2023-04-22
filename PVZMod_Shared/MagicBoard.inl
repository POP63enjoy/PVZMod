#pragma once
#ifndef _PVZMOD_MAGIC_BOARD_INL_
#define _PVZMOD_MAGIC_BOARD_INL_

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
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombiePicker_CalculateNumWaves);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombiePicker_SpecialLevelPut);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombiePicker_CalculateBasicPoints);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombiePicker_PutBeforeMultiple);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombiePicker_CalculateMultiplePoints);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombiePicker_PutPreset);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombiePicker_PutRandom);
			PVZMOD_CHECK_MAGIC_VAR(mvOffsetX);
			PVZMOD_CHECK_MAGIC_VAR(mvOffsetY);
			PVZMOD_CHECK_MAGIC_VAR(MC_AUTO_SAVE_EXTENDED_DATA);
		}

		template <typename T>
		RegisterManager<T> RegisterMain(InitPatch& patch)
		{
			static_assert(std::is_base_of<Board, T>::value,	"MagicBoard::RegisterMain: T must based on Board.");

			patch.PatchTask("MagicBoard::RegisterMain", [&]
				{
					using namespace __PRIVATE__;

					{
						bool autoSaveExtendedData = true;
						PVZMOD_MAGIC_SVAR(MC_AUTO_SAVE_EXTENDED_DATA, const bool, T,
							{
								autoSaveExtendedData = T::MC_AUTO_SAVE_EXTENDED_DATA;
							});
						Binding_ExtendBase(patch, sizeof(T), autoSaveExtendedData);
					}

					PVZMOD_MAGIC_FUNC(MF_Constructor, void(LawnApp * theApp, Constructor_t & base), T,
						{
							Binding_MF_Constructor(patch, [](Board* _this, LawnApp* theApp, Constructor_t& base)
								{
									((T*)_this)->MF_Constructor(theApp, base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_Destructor, void(Destructor_t & base), T,
						{
							Binding_MF_Destructor(patch, [](Board* _this, Destructor_t& base)
								{
									((T*)_this)->MF_Destructor(base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_InitLevel, void(InitLevel_t & base), T,
						{
							Binding_MF_InitLevel(patch, [](Board* _this, InitLevel_t& base)
								{
									((T*)_this)->MF_InitLevel(base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_DisposeBoard, void(DisposeBoard_t & base), T,
						{
							Binding_MF_DisposeBoard(patch, [](Board* _this, DisposeBoard_t& base)
								{
									((T*)_this)->MF_DisposeBoard(base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_ZombiePicker_CalculateNumWaves, void(ZombiePicker_CalculateNumWaves_t & base), T,
						{
							Binding_MF_ZombiePicker_CalculateNumWaves(patch, [](Board* _this, ZombiePicker_CalculateNumWaves_t& base)
								{
									((T*)_this)->MF_ZombiePicker_CalculateNumWaves(base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_ZombiePicker_SpecialLevelPut, bool(ZombiePicker & theZombiePicker, int theWave, ZombiePicker_SpecialLevelPut_t & base), T,
						{
							Binding_MF_ZombiePicker_SpecialLevelPut(patch, [](Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_SpecialLevelPut_t& base)
								{
									return ((T*)_this)->MF_ZombiePicker_SpecialLevelPut(theZombiePicker, theWave, base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_ZombiePicker_CalculateBasicPoints, void(ZombiePicker & theZombiePicker, int theWave, ZombiePicker_CalculateBasicPoints_t & base), T,
						{
							Binding_MF_ZombiePicker_CalculateBasicPoints(patch, [](Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_CalculateBasicPoints_t& base)
								{
									((T*)_this)->MF_ZombiePicker_CalculateBasicPoints(theZombiePicker, theWave, base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_ZombiePicker_PutBeforeMultiple, void(ZombiePicker & theZombiePicker, int theWave, ZombiePicker_PutBeforeMultiple_t & base), T,
						{
							Binding_MF_ZombiePicker_PutBeforeMultiple(patch, [](Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutBeforeMultiple_t& base)
								{
									((T*)_this)->MF_ZombiePicker_PutBeforeMultiple(theZombiePicker, theWave, base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_ZombiePicker_CalculateMultiplePoints, void(ZombiePicker & theZombiePicker, int theWave, ZombiePicker_CalculateMultiplePoints_t & base), T,
						{
							Binding_MF_ZombiePicker_CalculateMultiplePoints(patch, [](Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_CalculateMultiplePoints_t& base)
								{
									((T*)_this)->MF_ZombiePicker_CalculateMultiplePoints(theZombiePicker, theWave, base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_ZombiePicker_PutPreset, void(ZombiePicker & theZombiePicker, int theWave, ZombiePicker_PutPreset_t & base), T,
						{
							Binding_MF_ZombiePicker_PutPreset(patch, [](Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutPreset_t& base)
								{
									((T*)_this)->MF_ZombiePicker_PutPreset(theZombiePicker, theWave, base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_ZombiePicker_PutRandom, void(ZombiePicker & theZombiePicker, int theWave, ZombiePicker_PutRandom_t & base), T,
						{
							Binding_MF_ZombiePicker_PutRandom(patch, [](Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutRandom_t& base)
								{
									((T*)_this)->MF_ZombiePicker_PutRandom(theZombiePicker, theWave, base);
								});
						});

					{
						int* xPtr = nullptr, * yPtr = nullptr;
						PVZMOD_MAGIC_SVAR(mvOffsetX, int, T,
							{
								xPtr = &T::mvOffsetX;
							});
						PVZMOD_MAGIC_SVAR(mvOffsetY, int, T,
							{
								yPtr = &T::mvOffsetY;
							});
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

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_Constructor, void(LawnApp * theApp, Constructor_t & base), LevelClass, BaseClass,
						{
							Binding_MF_Constructor(patch, [theLevelId](Board* _this, LawnApp* theApp, Constructor_t& base)
									{
										if (theApp->mGameMode == theLevelId)
											((LevelClass*)_this)->MF_Constructor(theApp, base);
										else
											base();
									});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_Destructor, void(Destructor_t & base), LevelClass, BaseClass,
						{
							Binding_MF_Destructor(patch, [theLevelId](Board* _this, Destructor_t& base)
								{
									if (_this->mApp->mGameMode == theLevelId)
										((LevelClass*)_this)->MF_Destructor(base);
									else
										base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_InitLevel, void(InitLevel_t & base), LevelClass, BaseClass,
						{
							Binding_MF_InitLevel(patch, [theLevelId](Board* _this, InitLevel_t& base)
								{
									if (_this->mApp->mGameMode == theLevelId)
										((LevelClass*)_this)->MF_InitLevel(base);
									else
										base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_DisposeBoard, void(DisposeBoard_t & base), LevelClass, BaseClass,
						{
							Binding_MF_DisposeBoard(patch, [theLevelId](Board* _this, DisposeBoard_t& base)
								{
									if (_this->mApp->mGameMode == theLevelId)
										((LevelClass*)_this)->MF_DisposeBoard(base);
									else
										base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_ZombiePicker_CalculateNumWaves, void(ZombiePicker_CalculateNumWaves_t & base), LevelClass, BaseClass,
						{
							Binding_MF_ZombiePicker_CalculateNumWaves(patch, [theLevelId](Board* _this, ZombiePicker_CalculateNumWaves_t& base)
								{
									if (_this->mApp->mGameMode == theLevelId)
										((LevelClass*)_this)->MF_ZombiePicker_CalculateNumWaves(base);
									else
										base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_ZombiePicker_SpecialLevelPut, bool(ZombiePicker & theZombiePicker, int theWave, MagicBoard::ZombiePicker_SpecialLevelPut_t & base), LevelClass, BaseClass,
						{
							Binding_MF_ZombiePicker_SpecialLevelPut(patch, [theLevelId](Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_SpecialLevelPut_t& base)
								{
									if (_this->mApp->mGameMode == theLevelId)
										return ((LevelClass*)_this)->MF_ZombiePicker_SpecialLevelPut(theZombiePicker, theWave, base);
									else
										return base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_ZombiePicker_CalculateBasicPoints, void(ZombiePicker & theZombiePicker, int theWave, MagicBoard::ZombiePicker_CalculateBasicPoints_t & base), LevelClass, BaseClass,
						{
							Binding_MF_ZombiePicker_CalculateBasicPoints(patch, [theLevelId](Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_CalculateBasicPoints_t& base)
								{
									if (_this->mApp->mGameMode == theLevelId)
										((LevelClass*)_this)->MF_ZombiePicker_CalculateBasicPoints(theZombiePicker, theWave, base);
									else
										return base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_ZombiePicker_PutBeforeMultiple, void(ZombiePicker & theZombiePicker, int theWave, MagicBoard::ZombiePicker_PutBeforeMultiple_t & base), LevelClass, BaseClass,
						{
							Binding_MF_ZombiePicker_PutBeforeMultiple(patch, [theLevelId](Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutBeforeMultiple_t& base)
								{
									if (_this->mApp->mGameMode == theLevelId)
										((LevelClass*)_this)->MF_ZombiePicker_PutBeforeMultiple(theZombiePicker, theWave, base);
									else
										return base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_ZombiePicker_CalculateMultiplePoints, void(ZombiePicker & theZombiePicker, int theWave, MagicBoard::ZombiePicker_CalculateMultiplePoints_t & base), LevelClass, BaseClass,
						{
							Binding_MF_ZombiePicker_CalculateMultiplePoints(patch, [theLevelId](Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_CalculateMultiplePoints_t& base)
								{
									if (_this->mApp->mGameMode == theLevelId)
										((LevelClass*)_this)->MF_ZombiePicker_CalculateMultiplePoints(theZombiePicker, theWave, base);
									else
										return base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_ZombiePicker_PutPreset, void(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_PutPreset_t& base), LevelClass, BaseClass,
						{
							Binding_MF_ZombiePicker_PutPreset(patch, [theLevelId](Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutPreset_t& base)
								{
									if (_this->mApp->mGameMode == theLevelId)
										((LevelClass*)_this)->MF_ZombiePicker_PutPreset(theZombiePicker, theWave, base);
									else
										return base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_ZombiePicker_PutRandom, void(ZombiePicker& theZombiePicker, int theWave, MagicBoard::ZombiePicker_PutRandom_t& base), LevelClass, BaseClass,
						{
							Binding_MF_ZombiePicker_PutRandom(patch, [theLevelId](Board* _this, ZombiePicker& theZombiePicker, int theWave, ZombiePicker_PutRandom_t& base)
								{
									if (_this->mApp->mGameMode == theLevelId)
										((LevelClass*)_this)->MF_ZombiePicker_PutRandom(theZombiePicker, theWave, base);
									else
										return base();
								});
						});
				}, !enableMultipleRegister);
			return {};
		}
	}
}

#endif // !_PVZMOD_MAGIC_BOARD_INL_
