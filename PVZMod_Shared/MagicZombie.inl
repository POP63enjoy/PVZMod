#pragma once
#ifndef _PVZMOD_MAGIC_ZOMBIE_INL_
#define _PVZMOD_MAGIC_ZOMBIE_INL_

namespace PVZMod
{
	namespace MagicZombie
	{
		namespace __PRIVATE__
		{
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombieInitialize_InitMemberVariable);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombieInitialize_InitReanimation);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombieInitialize_InitType);
			PVZMOD_CHECK_MAGIC_FUNC(MF_ZombieInitialize_AfterInitType);

			PVZMOD_CHECK_MAGIC_VAR(MC_DATA_ARRAY_SIZE);
		}

		template <typename T>
		RegisterManager<T> RegisterMain(InitPatch& patch)
		{
			static_assert(std::is_base_of<Zombie, T>::value, "MagicZombie::RegisterMain: T must based on Zombie.");
			assert(("MagicZombie::RegisterMain: Do not define virtual functions in T.", (int)(Zombie*)(T*)4 == 4));

			patch.PatchTask("MagicZombie::RegisterMain", [&]
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

					PVZMOD_GENERAL_MAGIC_FUNC(MF_ZombieInitialize_InitMemberVariable, ZombieDefinition&(int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave, ZombieInitialize_InitMemberVariable_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_ZombieInitialize_InitReanimation, void(ZombieDefinition& theZombieDef, ZombieInitialize_InitReanimation_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_ZombieInitialize_InitType, void(ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer& theRenderLayer, int& theRenderOffset, ZombieInitialize_InitType_t& base), T);
					PVZMOD_GENERAL_MAGIC_FUNC(MF_ZombieInitialize_AfterInitType, void(ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer theRenderLayer, int theRenderOffset, ZombieInitialize_AfterInitType_t& base), T);
				}, true, true);

			return {};
		}

		template<typename BaseClass>
		template<typename ZombieClass>
		RegisterManager<BaseClass> RegisterManager<BaseClass>::RegisterZombie(InitPatch& patch, ZombieType theZombieId, bool enableMultipleRegister)
		{
			static_assert(std::is_base_of<BaseClass, ZombieClass>::value,	"MagicZombie::RegisterManager::RegisterZombie: ZombieClass must based on BaseClass.");
			static_assert(sizeof(BaseClass) == sizeof(ZombieClass),			"MagicZombie::RegisterManager::RegisterZombie: Do not define non-static member variables in ZombieClass.");

			assert(("MagicZombie::RegisterManager::RegisterZombie: Do not define virtual functions in ZombieClass.", (int)(Zombie*)(ZombieClass*)4 == 4));

			enableMultipleRegister |= Magic::IsEnableMultiReg<ZombieClass>();

			patch.PatchTask("MagicZombie::RegisterManager::RegisterZombie(" + std::to_string(theZombieId) + "," + std::to_string(typeid(ZombieClass).hash_code()) + ")", [&]
				{
					using namespace __PRIVATE__;

					Magic::IterateRef<ZombieClass>([&] <typename T>
					{
						RegisterZombie<T>(patch, theZombieId);
					});

					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_ZombieInitialize_InitMemberVariable, ZombieDefinition&(int theRow, ZombieType theType, bool theVariant, Zombie* theParentZombie, int theFromWave, ZombieInitialize_InitMemberVariable_t& base), ZombieClass, BaseClass, theZombieId, PVZMOD_ARG(1) == theZombieId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_ZombieInitialize_InitReanimation, void(ZombieDefinition& theZombieDef, ZombieInitialize_InitReanimation_t& base), ZombieClass, BaseClass, theZombieId, _this->mZombieType == theZombieId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_ZombieInitialize_InitType, void(ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer& theRenderLayer, int& theRenderOffset, ZombieInitialize_InitType_t& base), ZombieClass, BaseClass, theZombieId, _this->mZombieType == theZombieId);
					PVZMOD_GENERAL_CHILD_MAGIC_FUNC(MF_ZombieInitialize_AfterInitType, void(ZombieDefinition& theZombieDef, Zombie* theParentZombie, RenderLayer theRenderLayer, int theRenderOffset, ZombieInitialize_AfterInitType_t& base), ZombieClass, BaseClass, theZombieId, _this->mZombieType == theZombieId);
				}, !enableMultipleRegister);
			return {};
		}
	}
}

#endif // !_PVZMOD_MAGIC_ZOMBIE_INL_
