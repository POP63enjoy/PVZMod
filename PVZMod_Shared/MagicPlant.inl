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
		RegisterManager<T> RegisterMain(InitPatch& patch)
		{
			static_assert(std::is_base_of<Plant, T>::value, "MagicPlant::RegisterMain: T must based on Plant.");
			assert(("MagicPlant::RegisterMain: Do not define virtual functions in T.", (int)(Plant*)(T*)4 == 4));

			patch.PatchTask("MagicPlant::RegisterMain", [&]
				{
					using namespace __PRIVATE__;

					{
						size_t dataArraySize = 1024;
						PVZMOD_IF_MAGIC_SVAR_EXIST(MC_DATA_ARRAY_SIZE, const size_t, T,
							{
								dataArraySize = T::MC_DATA_ARRAY_SIZE;
							});
						Binding_ExtendBase(patch, sizeof(T), dataArraySize);
					}

					PVZMOD_GENERAL_MAGIC_FUNC(MF_PlantInitialize_InitMemberVariable, PlantDefinition&(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType, PlantInitialize_InitMemberVariable_t & base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_PlantInitialize_InitReanimation, Reanimation*(PlantDefinition& thePlantDef, PlantInitialize_InitReanimation& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_PlantInitialize_BeforeInitType, void(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_BeforeInitType& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_PlantInitialize_InitType, void(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_InitType& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_PlantInitialize_AfterInitType, void(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_AfterInitType& base), T);
				}, true, true);
			return {};
		}

		template <typename BaseClass>
		template <typename PlantClass>
		RegisterManager<BaseClass> RegisterManager<BaseClass>::RegisterPlant(InitPatch& patch, SeedType thePlantId, bool enableMultipleRegister)
		{
			static_assert(std::is_base_of<BaseClass, PlantClass>::value,	"MagicPlant::RegisterManager::RegisterPlant: PlantClass must based on BaseClass.");
			static_assert(sizeof(BaseClass) == sizeof(PlantClass),			"MagicPlant::RegisterManager::RegisterPlant: Do not define non-static member variables in PlantClass.");

			assert(("MagicPlant::RegisterManager::RegisterPlant: Do not define virtual functions in PlantClass.", (int)(Plant*)(PlantClass*)4 == 4));

			enableMultipleRegister |= Magic::IsEnableMultiReg<PlantClass>();

			patch.PatchTask("MagicPlant::RegisterManager::RegisterPlant(" + std::to_string(thePlantId) + "," + std::to_string(typeid(PlantClass).hash_code()) + ")", [&]
				{
					using namespace __PRIVATE__;

					Magic::IterateRef<PlantClass>([&] <typename T>
					{
						RegisterPlant<T>(patch, thePlantId);
					});

					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_PlantInitialize_InitMemberVariable, PlantDefinition&(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType, PlantInitialize_InitMemberVariable_t& base), PlantClass, BaseClass, thePlantId, PVZMOD_ARG(2) == thePlantId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_PlantInitialize_InitReanimation, Reanimation*(PlantDefinition & thePlantDef, PlantInitialize_InitReanimation & base), PlantClass, BaseClass, thePlantId, _this->mSeedType == thePlantId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_PlantInitialize_BeforeInitType, void(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_BeforeInitType& base), PlantClass, BaseClass, thePlantId, _this->mSeedType == thePlantId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_PlantInitialize_InitType, void(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_InitType& base), PlantClass, BaseClass, thePlantId, _this->mSeedType == thePlantId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_PlantInitialize_AfterInitType, void(PlantDefinition& thePlantDef, Reanimation* theBodyReanim, PlantInitialize_AfterInitType& base), PlantClass, BaseClass, thePlantId, _this->mSeedType == thePlantId);
				}, !enableMultipleRegister);
			return {};
		}
	}
}

#endif // !_PVZMOD_MAGIC_PLANT_INL_
