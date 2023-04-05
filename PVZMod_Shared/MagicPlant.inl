#pragma once
#ifndef _PVZMOD_MAGIC_PLANT_INL_
#define _PVZMOD_MAGIC_PLANT_INL_

namespace PVZMod
{
	namespace MagicPlant
	{
		namespace __PRIVATE__
		{
			PVZMOD_CHECK_MAGIC_FUNC(MF_PlantInitialize_InitMemberVariable);
			PVZMOD_CHECK_MAGIC_FUNC(MF_PlantInitialize_InitReanimation);
			PVZMOD_CHECK_MAGIC_FUNC(MF_PlantInitialize_BeforeInitType);
			PVZMOD_CHECK_MAGIC_FUNC(MF_PlantInitialize_InitType);
			PVZMOD_CHECK_MAGIC_FUNC(MF_PlantInitialize_AfterInitType);

			PVZMOD_CHECK_MAGIC_VAR(MC_DATA_ARRAY_SIZE);
		}

		template <typename T>
		RegisterManager<T> Extend(InitPatch& patch)
		{
			static_assert(std::is_base_of<Plant, T>::value);
			patch.PatchTask("MagicPlant::ExtendPlant", [&]
				{
					using namespace __PRIVATE__;

					{
						size_t dataArraySize = 1024;
						PVZMOD_MAGIC_SVAR(MC_DATA_ARRAY_SIZE, const size_t, T,
							{
								dataArraySize = T::MC_DATA_ARRAY_SIZE;
							});
						Binding_ExtendBase(patch, sizeof(T), dataArraySize);
					}

					PVZMOD_MAGIC_FUNC(MF_PlantInitialize_InitMemberVariable, PlantDefinition & (int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType, PlantInitialize_InitMemberVariable_t & base), T,
						{
							Binding_MF_PlantInitialize_InitMemberVariable(patch, [](Plant* _this, int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType, PlantInitialize_InitMemberVariable_t& base) -> PlantDefinition&
								{
									return ((T*)_this)->MF_PlantInitialize_InitMemberVariable(theGridX, theGridY, theSeedType, theImitaterType, base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_PlantInitialize_InitReanimation, Reanimation * (PlantDefinition & thePlantDef, PlantInitialize_InitReanimation & base), T,
						{
							Binding_MF_PlantInitialize_InitReanimation(patch, [](Plant* _this, PlantDefinition& thePlantDef, PlantInitialize_InitReanimation& base)
								{
									return ((T*)_this)->MF_PlantInitialize_InitReanimation(thePlantDef, base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_PlantInitialize_BeforeInitType, void(PlantDefinition & thePlantDef, Reanimation * theBodyReanim, PlantInitialize_BeforeInitType & base), T,
						{
							Binding_MF_PlantInitialize_BeforeInitType(patch, [](Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_BeforeInitType& base)
								{
									((T*)_this)->MF_PlantInitialize_BeforeInitType(thePlantDef, theBodyReanim, base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_PlantInitialize_InitType, void(PlantDefinition & thePlantDef, Reanimation * theBodyReanim, PlantInitialize_InitType & base), T,
						{
							Binding_MF_PlantInitialize_InitType(patch, [](Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_InitType& base)
								{
									((T*)_this)->MF_PlantInitialize_InitType(thePlantDef, theBodyReanim, base);
								});
						});

					PVZMOD_MAGIC_FUNC(MF_PlantInitialize_AfterInitType, void(PlantDefinition & thePlantDef, Reanimation * theBodyReanim, PlantInitialize_AfterInitType & base), T,
						{
							Binding_MF_PlantInitialize_AfterInitType(patch, [](Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_AfterInitType& base)
								{
									((T*)_this)->MF_PlantInitialize_AfterInitType(thePlantDef, theBodyReanim, base);
								});
						});
				}, true, true);
			return {};
		}

		template<typename BaseClass>
		template<SeedType thePlantId, typename PlantClass>
		RegisterManager<BaseClass> RegisterManager<BaseClass>::RegisterPlant(InitPatch& patch)
		{
			static_assert(std::is_base_of<BaseClass, PlantClass>::value);
			static_assert(sizeof(BaseClass) == sizeof(PlantClass));
			patch.PatchTask("MagicPlant::RegisterManager::RegisterPlant", [&]
				{
					using namespace __PRIVATE__;

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_PlantInitialize_InitMemberVariable, PlantDefinition & (int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType, PlantInitialize_InitMemberVariable_t & base), PlantClass, BaseClass,
						{
							Binding_MF_PlantInitialize_InitMemberVariable(patch, [](Plant* _this, int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType, PlantInitialize_InitMemberVariable_t& base)->PlantDefinition&
								{
									if (theSeedType == thePlantId)
										return ((PlantClass*)_this)->MF_PlantInitialize_InitMemberVariable(theGridX, theGridY, theSeedType, theImitaterType, base);
									else
										return base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_PlantInitialize_InitReanimation, Reanimation * (PlantDefinition & thePlantDef, PlantInitialize_InitReanimation & base), PlantClass, BaseClass,
						{
							Binding_MF_PlantInitialize_InitReanimation(patch, [](Plant* _this, PlantDefinition& thePlantDef, PlantInitialize_InitReanimation& base)
								{
									if (_this->mSeedType == thePlantId)
										return ((PlantClass*)_this)->MF_PlantInitialize_InitReanimation(thePlantDef, base);
									else
										return base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_PlantInitialize_BeforeInitType, void(PlantDefinition & thePlantDef, Reanimation * theBodyReanim, PlantInitialize_BeforeInitType & base), PlantClass, BaseClass,
						{
							Binding_MF_PlantInitialize_BeforeInitType(patch, [](Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_BeforeInitType& base)
								{
									if (_this->mSeedType == thePlantId)
										((PlantClass*)_this)->MF_PlantInitialize_BeforeInitType(thePlantDef, theBodyReanim, base);
									else
										base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_PlantInitialize_InitType, void(PlantDefinition & thePlantDef, Reanimation * theBodyReanim, PlantInitialize_InitType & base), PlantClass, BaseClass,
						{
							Binding_MF_PlantInitialize_InitType(patch, [](Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_InitType& base)
								{
									if (_this->mSeedType == thePlantId)
										((PlantClass*)_this)->MF_PlantInitialize_InitType(thePlantDef, theBodyReanim, base);
									else
										base();
								});
						});

					PVZMOD_MAGIC_FUNC_CHECK_BASE_CLASS(MF_PlantInitialize_AfterInitType, void(PlantDefinition & thePlantDef, Reanimation * theBodyReanim, PlantInitialize_AfterInitType & base), PlantClass, BaseClass,
						{
							Binding_MF_PlantInitialize_AfterInitType(patch, [](Plant* _this, PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_AfterInitType& base)
								{
									if (_this->mSeedType == thePlantId)
										((PlantClass*)_this)->MF_PlantInitialize_AfterInitType(thePlantDef, theBodyReanim, base);
									else
										base();
								});
						});
				}, false);
			return {};
		}
	}
}

#endif // !_PVZMOD_MAGIC_PLANT_INL_
